/**
* @file config.h
* @brief 此头文件定义了日志工具类，异步把日志写入硬盘
* @author sleeping
* @version 1.0
* @date 2016-12-12
*/
#ifndef _SLP_SRC_CONFIG_H
#define _SLP_SRC_CONFIG_H
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <strings.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <queue>
#include <functional>
#include <condition_variable>


#include "utils.h"

using std::cout;
using std::endl;
using std::mutex;
using std::queue;
using std::string;
using std::thread;
using std::fstream;
using std::lock_guard;
using std::unique_lock;
using std::condition_variable;


namespace slp { namespace utils {
		class config {
			public:

				/**
				 * @brief config的单例函数
				 *
				 * @return config指针
				 */
				static config* instance();


				/**
				 * @brief 执行初始化操作并开启线程(异步写入硬盘)
				 *
				 * @param bn 	日志文件名称
				 * @param path  日志文件路径,默认当前路径下
				 * @param ss 	每次写入硬盘的时间间隔,默认5秒
				 * @param rs 	每条日志记录最大值,默认1k
				 * @param rc 	日志记录条数最大值,默认1000条
				 */
				void init (std::string bn,std::string path="./",unsigned short ss=5,unsigned int rs=1024,unsigned int rc=1000);
				virtual ~config ();


				/**
				 * @brief 把含有当前时间的日志信息存入日志缓存
				 *
				 * @param content 日志信息
				 *
				 * @return true 成功 false 失败
				 */
				bool append (std::string content) ;

			private:
				config ():is_init(false) {};
				void start();
				void stop();

				/**
				 * @brief 异步写日志的线程函数,使用C++11的线程库时，需传入this指针做参数
				 */
				void thread_func();
				
				bool			is_init;				/*是否执行了初始化操作*/
				unsigned short 	sleep_seconds;			/*异步写入硬盘的时间间隔*/
				unsigned int 	record_size;			/*每条日志记录最大值*/
				unsigned int 	record_count;			/*日志记录条数最大值*/

				mutex m_mutex;
				queue<string> 	q_log;					/*日志缓冲区*/
				std::string 	log_path;				/*日志文件的路径*/
				std::string 	log_name;				/*日志文件的名字*/
				queue<string> 		q_reserve_log;    	/*写满日志缓冲区后转移到此缓冲，异步写入硬盘*/
				condition_variable 	cond;
		};
}};
#endif /*_SLP_SRC_CONFIG_H*/
