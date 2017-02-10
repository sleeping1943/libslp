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
	/*pc->dump();*/

	slp::utils::transtype tt = pc->get_generic_value("worker_queue_host");
	/*printf("\033[32mis_server_fork=%s\033[m\n",is_server_fork ? "true" : "false");*/
	printf("\033[32mworker_queue_host.to_string()=%s type=%s\033[m\n",tt.to_string().data(),tt.get_type_str().data());
	slp::utils::transtype tt2 = pc->get_generic_value("worker_queue_port");
	printf("\033[32mworker_queue_host.to_string()=%d type=%s\033[m\n",tt2.to_int(),tt2.get_type_str().data());
	slp::utils::transtype tt3 = pc->get_generic_value("smtp_enablement");
	printf("\033[32msmtp_enablement.to_string()=%d type=%s\033[m\n",tt3.to_bool()?1:0,tt3.get_type_str().data());
	return 0;
}

