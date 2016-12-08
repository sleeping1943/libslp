/************************************
*
*此头文件...
*filename : config.h
*author   : sleeping
*email    : csleeping@163.com
*date     : 2016年12月07日 星期三 21时11分28秒
*
************************************/
#ifndef _SLP_CONFIG_H
#define _SLP_CONFIG_H

#include <string>
#include <unordered_map>
#include <forward_list>
#include <strings.h>

namespace slp { namespace util {


        class config {
            public:
                virtual ~config(){};
                static config* instance();
                bool set_filename(const std::string &path);
                bool parser_config(const std::string &fname);
                std::string get_value(std::string key);
                void dump();
            private:
                config(){};
                bool is_setpath() { return !m_filename.empty(); }
                bool str2map(std::forward_list<std::string> l);
                std::string m_filename;
                std::unordered_map<std::string,std::string> m;
        };
}}; 
#endif /*_SLP_CONFIG_H*/
