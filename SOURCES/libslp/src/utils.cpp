/**
 * @file utils.cpp
 * @brief 
 * @author sleeping
 * @version 1.0
 * @date 2016-09-01
 */
#include "utils.h"
#include <time.h>
#include <stdio.h>
#include "log.h"
#include <algorithm>

namespace slp{namespace utils{

    using slp::log::log;
    using slp::log::level;
	using std::unique;

	struct is_both_blank {
		bool operator () (const char& x, const char& y) {
			return x == ' ' && y == ' ';	
		};	
	};

    bool get_time_str(char* buf,bool is_exact) {
        time_t t = time(NULL); 
        struct tm* tt = localtime(&t); 
		if (is_exact) {
      		sprintf(buf, "%d-%02d-%02d %02d:%02d:%02d", 1900 + tt->tm_year,1 + tt->tm_mon, 
					tt->tm_mday, tt->tm_hour, tt->tm_min,tt->tm_sec);
		} else {
      		sprintf(buf, "%d-%02d-%02d", 1900 + tt->tm_year,1 + tt->tm_mon, tt->tm_mday);
		}
	    return true;
    }



    credis::credis():m_isconn(false) {};

    credis::~credis() {
        this->disconnect();
    }

    bool credis::connect(const string& ip,const int& port) {
        m_conn = redisConnect(ip.c_str(),port);
        if (m_conn->err) {
	        redisFree(m_conn);
	        string str_err;
	        str_err = "连接服务器失败,IP:";
	        str_err += ip;
	        str_err += " PORT:";
	        str_err += std::to_string(port);
    
	        log::trace(time(NULL),__FUNCTION__ ,str_err,level::error);
	        return false;
        }
        this->m_isconn = true;
        log::trace(time(NULL),__FUNCTION__ ,string("连接redis服务器成功[connect to redis-server succesfully]"),level::print);
        return true;
    }

    void credis::disconnect() {
        /* 释放与服务器的连接 */
        if (!m_conn) {
			redisFree(m_conn);
			m_conn = NULL;
			this->m_isconn = false;
			log::trace(time(NULL),__FUNCTION__ ,string("断开与redis服务器的连接[close socket with redis server]"),level::error);	
		}
	}

    bool credis::sendstr(const string& cmd,const string& key,const string& data) {
        string str_send = cmd;
        str_send += " ";
        str_send += key;
        str_send += " ";
        str_send += "%s";
        redisReply* preply = (redisReply*)redisCommand(m_conn,str_send.c_str(),data.c_str());
        if (NULL == preply) {	return false; }

        if (preply->type == REDIS_REPLY_ERROR) {
	        string str_err = "redis执行命令失败!";
	        str_err += "err_msg:";
	        str_err.append(preply->str,preply->len);
	        log::trace(time(NULL),__FUNCTION__ ,str_err,level::error);
	        freeReplyObject(preply);
	        return false;
        }

        freeReplyObject(preply);
        return true;
    }

    bool credis::sendbin(const string& cmd,const string& key,const string& data) {
        string str_send = cmd;
        str_send += " ";
        str_send += key;
        str_send += " ";
        str_send += "%b";
        redisReply* preply = (redisReply*)redisCommand(m_conn,str_send.c_str(),
                                                    data.c_str(),data.length());
        if (NULL == preply) {	return false; }

        if (preply->type == REDIS_REPLY_ERROR) {
	        string str_err = "redis执行命令失败!";
	        str_err += "err_msg:";
	        str_err.append(preply->str,preply->len);
	        log::trace(time(NULL),__FUNCTION__ ,str_err,level::error);
	        freeReplyObject(preply);
	        return false;
        }
        freeReplyObject(preply);
        return true;
    }

    bool credis::isconnected() {
        return this->m_isconn;
    }

    bool credis::getbin(const string& cmd,const string& key,string& data) {
        string str_send = cmd;
        str_send += " ";
        str_send += key;
        str_send += " ";
        redisReply* preply = (redisReply*)redisCommand(m_conn,str_send.c_str(),
                                                    data.c_str(),data.length());
        if (NULL == preply) {	return false; }
        
        /* 没有数据可以使用 */
        if (!(preply->type == REDIS_REPLY_NIL) == 0) {
	        freeReplyObject(preply);
	        return false;
        } else {
	        data.append(preply->str,preply->len);
            freeReplyObject(preply);
	        return true;
        }
        return true;
    }


	bool credis::set_timeout(const struct timeval& tv) {
		if (!isconnected()) {
        	log::trace(time(NULL),__FUNCTION__ ,string("未连接到服务器!"),level::error);
			return false;	
		}
		return REDIS_OK == redisSetTimeout(m_conn,tv);
	}

	bool credis::isalive() {
		std::string data(32,'\0');
		unsigned int len = data.size();
		redisReply* preply = (redisReply*)redisCommand(m_conn,"ping",data.data(),len);
        if (NULL == preply) {	return false; }
        
        /* 没有数据可以使用 */
        if (!(preply->type == REDIS_REPLY_NIL) == 0) {
	        freeReplyObject(preply);
	        return false;
        } else {
	        data.append(preply->str,(preply->len > (int)len) ? len : preply->len);
            freeReplyObject(preply);
			std::transform(data.begin(),data.end(),data.begin(),tolower);
			if (data == "pong") return true;
        }

		return true;	
	}

	bool trim (std::string &str) { 
		ltrim(str);
		rtrim(str);
		str.erase(unique(str.begin(),str.end(), is_both_blank()),str.end());
		return true;
	}

	bool ltrim (std::string &str) { 
		string::size_type pos = str.find_first_not_of(" ");
		if (pos != string::npos) {
			string::iterator it = str.begin();
			str.erase(it, it+pos);	
			return true;
		}
		return false;
	}

	bool rtrim (std::string &str) {
		string::size_type pos_blank = str.find_last_of(" ");	
		string::size_type pos_char 	= str.find_last_not_of(" ");	
	
		if (pos_blank != string::npos && pos_char != string::npos && pos_blank > pos_char) {
			str.erase(pos_char+1);	
			return true;
		}
		return false;
	}


}};
