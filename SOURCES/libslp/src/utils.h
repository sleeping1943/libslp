/**
 * @file utils.h
 * @brief 常用的工具函数和工具类
 * @author sleeping
 * @version 1.0
 * @date 2016-09-01
 */

#ifndef _SLP_UTILS_H
#define _SLP_UTILS_H

#include <stdlib.h>
#include <unistd.h>

#include <string>
#include <hiredis/hiredis.h>

/**
 * @brief 工具类的命名空间
 */
namespace slp{namespace utils{
    
    using std::string;

	/**
	 * @brief 获取当前时间的字符串
	 *
	 * @param buf 当前时间字符串缓冲区
	 * @param is_exact 是否精确到时分秒
	 *
	 * @return 
	 */
    bool get_time_str(char* buf,bool is_exact=true);


	/**
	 * @brief 去除左侧和右侧的空白字符，字符串中的字符
	 *
	 * @param str 待处理的字符串
	 *
	 * @return  true 成功 false 失败
	 */
	bool trim (std::string &str);

	/**
	 * @brief 去除左侧空白字符串
	 *
	 * @param str 待处理字符串
	 *
	 * @return  true 成功 false 失败
	 */
	bool ltrim (std::string &str);

	/**
	 * @brief 去除右侧空白字符串
	 *
	 * @param str 待处理字符串
	 *
	 * @return  true 成功 false 失败
	 */
	bool rtrim (std::string &str);

    /**
     * @brief  此类用于和redis服务器通信，包装了hiredis库,
     * NOTE:由于hiredis库不是线程安全的,所以单例模式不适合
     */
    class credis {
        public:
            credis();
            ~credis();
            /**
             * @brief 建立和服务器的连接
             *
             * @param ip redis服务器主机地址
             * @param port redis服务器主机端口
             *
             * @return true:成功 false:失败
             */
            bool connect(const string& ip,const int& port);

            /**
             * @brief  发送一个redis命令(用于存储文本数据) 
             *
             * @param cmd 发送给redis服务器的命令
             * @param key 要执行命令的对象
             * @param data  发送的命令(可包含数据)
             *
             * @return true:成功 false:失败
             */
            bool sendstr(const string& cmd,const string& key,const string& data);

            /**
             * @brief   发送一个redis命令(用于存储二进制数据)
             *
             * @param cmd 发送给redis服务器的命令
             * @param key 要执行命令的对象
             * @param data  发送的命令(可包含二进制数据)
             *
             * @return true:成功 false:失败
             */
            bool sendbin(const string& cmd,const string& key,const string& data);

            /**
             * @brief 发送一个redis命令(用于获取二进制数据)
             *
             * @param cmd 发送给redis服务器的命令
             * @param key 要执行命令的对象
             * @param data 用于接收二进制数据的string对象
             *
             * @return  true:成功 false:失败
             */
            bool getbin(const string& cmd,const string& key,string& data);

            /**
             * @brief 断开服务器的连接
             */
            void disconnect();

            /**
             * @brief 判断与redis服务器的通信是否畅通
             *
             * @return true:连接畅通 false:连接断开
             */
            bool isconnected();


			/**
			 * @brief 设置redis命令的超时时间
			 *
			 * @param tv 超时时间
			 *
			 * @return true 成功 false 失败
			 */
			bool set_timeout(const struct timeval& tv);

			/**
			 * @brief 检测与redis-server的连接是否正常
			 *
			 * @return true 正常 false 出现异常，需要断开重连
			 */
			bool isalive();
        private:
            redisContext* m_conn;
            bool m_isconn;
    };

}};
#endif /*_SLP_UTILS_H*/
