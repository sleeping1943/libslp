/************************************
*
*此源文件
*filename : src/main.cpp
*author   : sleeping
*email    : csleeping@163.com
*date     : 2017年02月07日 星期二 15时18分07秒
*
************************************/
#include <stdio.h>
#include <string>
#include <libshelper/config.h>

#include <algorithm>
#include <libshelper/utils.h>

int main (int argc, char** argv)
{
	if (argc != 2) {
		printf("\033[31mUsage: test_config <filename>\033[m\n");
		return -1;
	}
	using slp::utils::config;

	config *pc = config::instance();
	pc->parser_config(argv[1]);
	pc->dump();

	bool is_server_fork = std::atoi(pc->get_value("is_server_fork").data());
	printf("\033[32mis_server_fork=%s\033[m\n",is_server_fork ? "true" : "false");
	printf("\033[32mwork_db_host=%s1\033[m\n",pc->get_value("worker_db_host").data());
	return 0;
}

