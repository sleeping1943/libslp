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

#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <forward_list>
#include <strings.h>
#include <vector>
#include <exception>

#include "textcolor.h"
#include "utils.h"

namespace slp { namespace utils {

		enum type {
			t_int	=	0,
			t_str	=	1,
			t_bool	=	2,
			t_other	=	3
		};

		class typexception;
		type get_type_from_string (const string& str);


		class transtype final {
			public:
				transtype() {};
				transtype(const transtype &tt) {
					this->str_ = tt.get_str();
					this->set_type(tt.get_type());
				};
				transtype(const std::string& str) { 
					if (str.empty()) return;

					str_.assign(str.begin(),str.end());
					set_type(get_type_from_string(str_));
				};
				~transtype() {};

				bool isvalid () { return !str_.empty(); };
				type get_type () const { return type_; };
				void set_type (type t) { type_ = t; };
				std::string get_str () const { return str_; };
				void set_str (const std::string &str) { str_ = str; };
				std::string get_type_str();

				operator int() const;
				operator bool() const;
				operator std::string() const;
				std::string operator =(const std::string& that);
				transtype operator =(const transtype& that);

				int to_int ();
				bool to_bool();
				std::string to_string();

				friend std::ostream& operator <<(std::ostream& os,transtype &tt) {
					os << tt.str_;
					return os;
				};
			private:
				type type_;
				std::string str_;
		};

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
				 * @brief 获取字符串包装类便于转换
				 *
				 * @param key 配置文件中的key
				 *
				 * @return  value的包装类
				 */
        		transtype get_generic_value(std::string key);
				/**
				 * @brief 输出map中存储的key-value
				 */
                void dump();


				/**
				 * @brief 是否已经解析过配置文件，map中收否有值
				 *
				 * @return 已解析过配置，map中有值
				 */
				bool empty ();
            private:
                config(){};
                bool str2map(std::forward_list<std::string> l);
                std::string m_filename;
                std::unordered_map<std::string,std::string> m;

				/**
				 * @brief 获取指定key的值,包含字符串前后的"
				 *
				 * @param key 配置文件选项值
				 *
				 * @return  key的值
				 */
				std::string get_value(std::string key);
        };

		class typexception : public std::exception {
			public:
				typexception() {};	
				~typexception() {};	
				typexception(const std::string &str);
				const char* what () const throw();
			private: 
				std::string err_str_;
		};
}}; 
#endif /*_SLP_CONFIG_H*/
