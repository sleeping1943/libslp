/*******************************************************

定义linux终端字体颜色

定义  (_NO_OUT_COLOR_)  宏禁止输出

*******************************************************/
#ifndef _TEXTCOLOR_H
#define _TEXTCOLOR_H
#include <stdio.h>
#include <string>
#include <iostream>
/*
#define 	NONE         "\033[m" 
#define  	RED          "\033[0;32;31m" 
#define 	LIGHT_RED    "\033[1;31m" 
#define  	GREEN        "\033[0;32;32m" 
#define  	LIGHT_GREEN  "\033[1;32m" 
#define  	BLUE         "\033[0;32;34m" 
#define  	LIGHT_BLUE   "\033[1;34m" 
#define  	DARY_GRAY    "\033[1;30m" 
#define  	CYAN         "\033[0;36m" 
#define  	LIGHT_CYAN   "\033[1;36m" 
#define  	PURPLE       "\033[0;35m" 
#define  	LIGHT_PURPLE "\033[1;35m" 
#define  	BROWN        "\033[0;33m" 
#define 	YELLOW       "\033[1;33m" 
#define 	LIGHT_GRAY   "\033[0;37m" 
#define  	WHITE        "\033[1;37m"
*/

namespace slp{

	const std::string 	NONE        =  "\033[m" 		;   /* 默认 */
	const std::string  	RED         =  "\033[0;31m" 	;   /* 红色 */
	const std::string 	LIGHT_RED   =  "\033[1;31m" 	;   /* 浅红 */
	const std::string  	GREEN       =  "\033[0;32m" 	;   /* 绿色 */
	const std::string  	LIGHT_GREEN =  "\033[1;32m" 	;   /* 浅绿 */
	const std::string  	BLUE        =  "\033[0;34m" 	;   /* 蓝色 */
	const std::string  	LIGHT_BLUE  =  "\033[1;34m" 	;   /* 浅蓝 */
	const std::string  	DARY_GRAY   =  "\033[1;30m" 	;   /* 深灰 */
	const std::string  	CYAN        =  "\033[0;36m" 	;   /* 青色 */
	const std::string  	LIGHT_CYAN  =  "\033[1;36m" 	;   /* 淡青 */
	const std::string  	PURPLE      =  "\033[0;35m" 	;   /* 紫色 */
	const std::string  	LIGHT_PURPLE=  "\033[1;35m" 	;   /* 淡紫 */
	const std::string  	BROWN       =  "\033[0;33m" 	;   /* 棕色 */
	const std::string 	YELLOW      =  "\033[0;33m" 	;   /* 黄色 */
	const std::string 	LIGHT_YELLOW =  "\033[1;33m" 	;   /* 浅黄色 */
	const std::string 	LIGHT_GRAY  =  "\033[0;37m" 	;   /* 浅灰 */
	const std::string  	WHITE       =  "\033[1;37m"		;   /* 白色 */

	void textout(const char* pstr,const int num,const char* color,bool is_output=true);
	void textout(const char* pstr,const char* color,bool is_output=true);
	void textout(const std::string label,const std::string str,const std::string color=NONE,bool is_output=true);
	void textout(const std::string label,const int num,const std::string color=NONE,bool is_output=true);
};

/*
int main(void){

	textout("text",RED);
	return 0;
}
*/
#endif	//_TEXTCOLOR_H


