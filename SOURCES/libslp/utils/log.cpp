#include "log.h"
#include "textcolor.h"
#include <sstream>
#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;
using std::stringstream;
namespace slp{namespace log{
    
        std::string log::time_now(time_t tt){
            static time_t t_last = 0;
            static std::string str_last_time;
            if (t_last == tt && !str_last_time.empty()) return str_last_time;
            struct tm *t = ::localtime(&tt);
            if (NULL == t) {
               t_last = 0; 
               str_last_time.clear();
               return "";
            }

            t_last = tt;
            stringstream ss;
            ss << std::setfill('0') << std::setw(4) << (1900 + t->tm_year) << "-"
               << std::setw(2) << 1+t->tm_mon << "-" << std::setw(2) << t->tm_mday
               << " " << std::setw(2) << t->tm_hour << ":" << std::setw(2) << t->tm_min
               << ";" << std::setw(2) << t->tm_sec;
            str_last_time = ss.str();
            return str_last_time;
        }


        bool log::trace(time_t tt,std::string func,std::string msg,level l) {
            switch (l) {
                case error:         
                    cout << slp::RED << log::time_now(tt) << "[" << func <<"]" << msg << slp::NONE << endl;
                    break;
                case warning:         
                    cout << slp::YELLOW << log::time_now(tt) << "[" << func <<"]" << msg << slp::NONE << endl;
                    break;
                case debug:         
                    cout << slp::CYAN << log::time_now(tt) << "[" << func <<"]" << msg << slp::NONE << endl;
                    break;
                case print:         
                    cout << slp::GREEN << log::time_now(tt) << "[" << func <<"]" << msg << slp::NONE << endl;
                    break;
                default:
                    cout << slp::LIGHT_GRAY << log::time_now(tt) << "[" << func <<"]" << msg << slp::NONE << endl;
                    break;
            }
            return true;
        }
}};
