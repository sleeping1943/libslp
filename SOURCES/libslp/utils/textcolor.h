/**
 * @file textcolor.h
 * @brief 此文件存放一些打印函数和颜色
 * @author sleeping
 * @version 1.0.1
 * @email csleeping@163.com
 * @date 2016-07-04
 */

#ifndef _TEXTCOLOR_H
#define _TEXTCOLOR_H
#include <stdio.h>
#include <string>
#include <iostream>

/**
   @mainpage

  @section intro Introduction

  此函数库用于sleeping编程帮助类库 

  Finally, you call event_base_dispatch() to loop and dispatch events.
  You can also use event_base_loop() for more fine-grained control.

  Currently, only one thread can be dispatching a given event_base at a
  time.  If you want to run events in multiple threads at once, you can
  either have a single event_base whose events add work to a work queue,
  or you can create multiple event_base objects.

   @section api API Reference

  To browse the complete documentation of the libevent API, click on any of
  the following links.

  utils/log.h
  A framework for creating RPC servers and clients

 */

namespace slp{
    
    /**
     * @brief 默认颜色
    */
	const std::string 	NONE        =  "\033[m";  
    
    /**
     * @brief 红色
     */
	const std::string  	RED         =  "\033[0;31m"; 


    /**
     * @brief 浅红
     */
	const std::string 	LIGHT_RED   =  "\033[1;31m"; 
    
    /**
     * @brief 绿色
     */
	const std::string  	GREEN       =  "\033[0;32m";  

    /**
     * @brief 浅绿
     */
	const std::string  	LIGHT_GREEN =  "\033[1;32m"; 

    /**
     * @brief 蓝色
     */
	const std::string  	BLUE        =  "\033[0;34m";

    /**
     * @brief 浅蓝
     */
	const std::string  	LIGHT_BLUE  =  "\033[1;34m"; 

    /**
     * @brief 深灰
     */
	const std::string  	DARY_GRAY   =  "\033[1;30m";

    /**
     * @brief 青色
     */
	const std::string  	CYAN        =  "\033[0;36m"; 

    /**
     * @brief 淡青
     */
	const std::string  	LIGHT_CYAN  =  "\033[1;36m";

    /**
     * @brief 紫色
     */
	const std::string  	PURPLE      =  "\033[0;35m"; 

    /**
     * @brief 淡紫
     */
	const std::string  	LIGHT_PURPLE=  "\033[1;35m";

    /**
     * @brief 棕色
     */
	const std::string  	BROWN       =  "\033[0;33m"; 

    /**
     * @brief  黄色
     */
	const std::string 	YELLOW      =  "\033[0;33m";

    /**
     * @brief 浅黄色
     */
	const std::string 	LIGHT_YELLOW =  "\033[1;33m";  

    /**
     * @brief 浅灰
     */
	const std::string 	LIGHT_GRAY  =  "\033[0;37m"; 

    /**
     * @brief 白色
     */
	const std::string  	WHITE       =  "\033[1;37m"; 


    /**
     * @brief 打印
     *
     * @param pstr 1
     * @param num 2
     * @param color 3
     * @param is_output 4
     */
	void textout(const char* pstr,const int num,const char* color,bool is_output=true);
	void textout(const char* pstr,const char* color,bool is_output=true);
	void textout(const std::string label,const std::string str,const std::string color=NONE,bool is_output=true);
	void textout(const std::string label,const int num,const std::string color=NONE,bool is_output=true);
};
#endif	//_TEXTCOLOR_H


