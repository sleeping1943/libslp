#include "asynclog.h"

namespace slp { namespace utils {
		asynclog* asynclog::instance() 
		{
			static asynclog c;
			return &c;
		};

		void asynclog::init (std::string bn,std::string path,unsigned short ss,unsigned int rs,unsigned int rc)
		{
			is_init 		= true;
			log_name 		= bn;
			log_path 		= path;
			sleep_seconds 	= ss;
			record_size 	= rs;
			record_count 	= rc;

			start();
		};

		asynclog::~asynclog () { stop(); };

		bool asynclog::append (std::string content) 
		{
			if (!is_init || content.empty() || content.size() > record_size) {
				return false; 
			}

			unique_lock<mutex> _lock(m_mutex);
			char buf[64];
			bzero(buf,sizeof(buf));
			slp::utils::get_time_str(buf);
			string str = buf;
			str += " ";
			str += content;
			q_log.push(str);
			//++wcount;

			if (q_log.size() >= record_count && q_reserve_log.empty()) {
				std::swap(q_log,q_reserve_log);	
				cond.notify_one();
			} else {
				return false;	
			}

			return true;	
		};


		void asynclog::start()
		{
			thread t(&asynclog::thread_func,this);
			t.detach();
		}

		void asynclog::stop()
		{
			is_init = false;
		}

		void asynclog::thread_func()
		{
			queue<string> buf;
			while (true) {
				unique_lock<mutex> _lock(m_mutex);
				cond.wait_for(_lock,std::chrono::seconds(sleep_seconds), [] () { return false;} );
				if (!q_log.empty() && q_reserve_log.empty()) {
					std::swap(q_log,q_reserve_log);	
				}

				if (!q_reserve_log.empty()) {
					/* 根据日期和文件名构建日志文件名*/
					char name_buf[64];
					bzero(name_buf,sizeof(name_buf));
					slp::utils::get_time_str(name_buf,false);
					string fname = log_path;
					fname += name_buf;
					fname += "-";
					fname += log_name;
					fstream f(fname,std::ios::out | std::ios::app);

					if (!f.is_open())  { 
						//cout << "\033[31m 打开文件失败" << "!!\033[m\n";
						continue; 
					}
					std::swap(q_reserve_log,buf);

					while (!buf.empty()) {
						f << buf.front() << endl;
						buf.pop();
					}

					if (f.is_open()) { f.close(); }
				} 
				_lock.unlock();
			}
		}
}};
