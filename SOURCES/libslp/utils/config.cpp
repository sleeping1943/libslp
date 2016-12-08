#include "config.h"
#include <fstream>
#include <iostream>

namespace slp { namespace util {

        std::string trim(const std::string& str);

        config* config::instance()
        {
            static config c;
            return &c;
        }


        bool config::set_filename(const std::string &path)
        {
            this->m_filename = path;
            return true;
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
                        str = trim(str);
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
                    m[it.substr(0,delim)] = trim(it.substr(delim));
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
                std::cout << "first:" << it.first << " second:" << get_value(it.first) << std::endl; 
            }
        }

        std::string trim(const std::string& str) 
        {
            std::string::size_type beg = str.find_first_not_of(' ');
            std::string::size_type end = str.find_last_not_of(' ');
            if (beg != std::string::npos && end != std::string::npos)  {
                return str.substr(beg,end-beg+1); 
            }
            return str;
        }
}}
