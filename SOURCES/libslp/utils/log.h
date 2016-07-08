/**
 * @file log.h
 * @brief 此类用与应用程序输出日志
 * @author sleeping
 * @version 1.0.0
 * @email csleeping@163.com
 * @date 2016-06-17
 */

#ifndef _LIBSLP_LOG_H
#define _LIBSLP_LOG_H
#include <time.h>
#include <string>
#include <mutex>

/**
 * @brief 日志类命名空间
 */
namespace slp{namespace log{

        
        /**
         * @brief error 红色 warning 黄色 debug 青色 print 绿色 default 淡青色
         */
        enum level{
            error = 0,
            warning = 1,
            debug = 2,
            print = 3
        };
        using std::mutex;
        using std::lock_guard;

        /**
         * @brief 此类用于打印一些日志信息
         */
        class log{
            public:
                log(){};
                ~log(){};

                /**
                 * @brief 打印锁
                 */
                static mutex m;

                /**
                 * @brief 获取当前时间
                 *
                 * @param tt 当前时间的time_t值
                 *
                 * @return 当前时间的字符串形式
                 */
                static std::string time_now(time_t tt);

                /**
                 * @brief 带锁的打印函数
                 *
                 * @param tt 当前时间
                 * @param func 所属函数
                 * @param msg 打印的信息
                 * @param l 打印等级
                 *
                 * @return true 成功 false 失败
                 */
                static bool trace(time_t tt,std::string func,std::string msg,level l); 

        };
}};
#endif  /* _LIBSLP_LOG_H */
