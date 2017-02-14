/************************************
*
*此源文件
*filename : src/main.cpp
*author   : sleeping
*email    : csleeping@163.com
*date     : 2017年 02月 14日 星期二 15:05:31 CST
*
************************************/
#include <stdio.h>
#include <iostream>
#include <string>
#include <libshelper/log.h>
#include <libshelper/utils.h>

using std::cout;
using std::endl;
using std::string;
using slp::log::log;
using slp::log::level;
using slp::utils::credis;


int main()
{
	credis c;
	if (!c.connect("127.0.0.1",6379)) {
		log::trace(time(NULL),__func__,"连接错误!",level::error);	
		return -1;
	}

	std::string str(31457280,'\0');
	if (!c.sendbin("lpush","iseal",str)) {
		getchar();
		if (!c.isalive()) {
			log::trace(time(NULL),__func__,"连接无效!",level::error);	
		} else {
			log::trace(time(NULL),__func__,"连接有效!",level::print);	
		}		
	}
	getchar();
	return 0;
}
