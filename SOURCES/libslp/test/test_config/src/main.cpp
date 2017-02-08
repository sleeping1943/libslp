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

	return 0;
}

