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
namespace slp{namespace log{

        enum level{
            error = 0,
            warning = 1,
            debug = 2,
            print = 3
        };
        using std::mutex;
        using std::lock_guard;
        class log{
            public:
                log(){};
                ~log(){};
                static mutex m;
                static std::string time_now(time_t tt);
                static bool trace(time_t tt,std::string func,std::string msg,level l); 

        };
}};
#endif  /* _LIBSLP_LOG_H */
