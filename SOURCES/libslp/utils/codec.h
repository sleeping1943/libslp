/************************************
*
*此头文件...
*filename : /root/git/libslp/SOURCES/libslp/utils/codec.h
*author   : sleeping
*email    : csleeping@163.com
*date     : 2016年07月28日 星期四 15时49分30秒
*
************************************/
#ifndef _SLP_CODEC_H
#define _SLP_CODEC_H

#include <iostream>

namespace slp{namespace codec{

    class codec {
        public:
            virtual char* decode(const unsigned char* src,char* dst)=0;
            virtual char* encode(const unsigned char* src,char* dst,int length)=0;
    };

    class codec_base64 : public codec {
        public:
            char* decode(const unsigned char* src,char* dst);
            char* encode(const unsigned char* src,char* dst,int length);
        private:
            int find_index(char* pchar);
            char* base64_decode(const unsigned char* src,char* dst);
            char* base64_encode(const unsigned char* src,char* dst,int length);
    };
}}

#endif /*_SLP_CODEC_H*/
