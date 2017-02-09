#include "config.h"
#include <fstream>
#include <iostream>
#include <iterator>

namespace slp { namespace utils {

		char ctrl2asc (char);	

		transtype::operator int() const {
			if (type_ == t_int) {
				return std::atoi(str_.data());	
			}

			return 0;
		};

		transtype::operator bool() const {
			if (type_ == t_bool && str_== "true") {
				return true;
			}

			return false;
		};

		transtype::operator std::string() const {
			if (type_ == t_str)	return str_;
			
			return "";
		};


		std::string transtype::operator =(const std::string& that) {
			if (that.empty()) return "";
			this->str_ = that;	
			set_type(t_str);
			/*set_type(get_type_from_string(str_));*/
			return str_;
		};

		transtype transtype::operator =(const transtype& that) {
			using std::swap;	/*在此处声明让编译器自动推导swap版本*/
			transtype tt(that);
			swap(*this,tt);
			return *this;
		};

		std::string transtype::get_type_str() {
			switch (this->type_) {
			case t_int:
				return "int";
			case t_str:
				return "string";
			case t_bool:
				return "bool";
			case t_other:
			default:
				return "unknow";
			};

			return "";
		}

        config* config::instance()
        {
            static config c;
            return &c;
        }

        bool config::parser_config(const std::string &fname)
        {
            if (!fname.empty()) {
                std::fstream f(fname); 
                if (f.is_open()) {
                    m.clear();
                    std::forward_list<std::string> l;
                    char buf[1024*4];
                    while (!f.eof()) {
                        bzero(buf,sizeof(buf)-1);
                        f.getline(buf,sizeof(buf)-1);

                        std::string str(buf);
						std::transform(str.begin(),str.end(),str.begin(),ctrl2asc);
                        trim(str);
                        if (!str.empty() && '#' != str[0])
                            l.push_front(str);
                    }

                    f.close();
                    str2map(l);
                    return true;
                }
            }
            return false;
        }


        bool config::str2map(std::forward_list<std::string> l)
        {
            for (const auto &it : l) {
                std::string::size_type delim = it.find_first_of(' ');
                if (std::string::npos != delim) {
					std::string value = it.substr(delim);
					trim(value);

					m[it.substr(0,delim)] = value;
                }

            }
            return true;
        }


		std::string config::get_value(std::string key) {
	        if (m.find(key) != m.end()) {
                return m[key];
            }
            return "";
	
		};

        transtype config::get_generic_value(std::string key)
        {
			std::string value = get_value(key);
			type t = get_type_from_string(value);
			transtype tt;
			tt.set_type(t);
			if (t_str == t) {
				std::vector<char> vec(value.begin(),value.end());
				auto it_begin = vec.begin();
				auto it_end = vec.end();
				int offset = std::distance(it_begin,--it_end);
				value.assign(it_begin+1,it_begin+offset);		
				tt = value;
			} else {
				tt.set_str(value);	
			}
			return tt;
        }

        void config::dump()
        {
            std::cout << "m.size():" << m.size() << std::endl;
            for (const auto &it : m) {
				std::cout << slp::GREEN << it.first << slp::RED << ":" << slp::YELLOW << "["
									<< get_value(it.first) << "]" <<  slp::NONE << std::endl; 
            }
        }

		bool config::empty () {
			return this->m.empty();	
		};

		type get_type_from_string (const string& str) {
			if (std::isdigit(str[0])) {
				return t_int;
			}

			if (str == "true" || str == "false") {
				return t_bool;
			}

			std::vector<char> vec(str.begin(),str.end());
			if (vec.front() == '\"' && vec.back() == '\"') {
				return t_str;
			}
			std::vector<char>().swap(vec);	/*立刻销毁vec的内存*/

			return t_other;
		}

		char ctrl2asc (char c) {
			return std::iscntrl(c) ? ' ' : c;	
		}
}}

