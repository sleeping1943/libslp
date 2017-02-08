/************************************
*
*此头文件定义了配置工具类
*filename : config.h
*author   : sleeping
*email    : csleeping@163.com
*date     : 2016年12月07日 星期三 21时11分28秒
*
************************************/
#ifndef _SLP_CONFIG_H
#define _SLP_CONFIG_H

#include <string>
#include <algorithm>
#include <unordered_map>
#include <forward_list>
#include <strings.h>

#include "textcolor.h"
#include "utils.h"

namespace slp { namespace utils {


	/**
	 * @brief 读取配置文件，以键值对形式存储内存中
	 */
        class config {
            public:
                virtual ~config(){};

				/**
				 * @brief 获取配置文件类指针
				 *
				 * @return 
				 */
                static config* instance();


				/**
				 * @brief 解析配置文件，并存入内存map中
				 *
				 * @param fname 配置文件完整路径
				 *
				 * @return true 成功 false 失败
				 */
                bool parser_config(const std::string &fname);


				/**
				 * @brief 获取指定key的值
				 *
				 * @param key 配置文件选项值
				 *
				 * @return  key的值
				 */
                std::string get_value(std::string key);


				/**
				 * @brief 输出map中存储的key-value
				 */
                void dump();
            private:
                config(){};
                bool str2map(std::forward_list<std::string> l);
                std::string m_filename;
                std::unordered_map<std::string,std::string> m;
        };
}}; 
#endif /*_SLP_CONFIG_H*/
