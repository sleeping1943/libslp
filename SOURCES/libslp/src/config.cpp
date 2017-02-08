#include "config.h"
#include <fstream>
#include <iostream>

namespace slp { namespace utils {

		char ctrl2asc (char);	

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

        std::string config::get_value(std::string key)
        {
            if (m.find(key) != m.end()) {
                return m[key]; 
            }
            return "";
        }

        void config::dump()
        {
            std::cout << "m.size():" << m.size() << std::endl;
            for (const auto &it : m) {
				std::cout << slp::GREEN << it.first << slp::RED << ":" << slp::YELLOW << "["
									<< get_value(it.first) << "]" <<  slp::NONE << std::endl; 
            }
        }

		char ctrl2asc (char c) {
			return std::iscntrl(c) ? ' ' : c;	
		}
}}

