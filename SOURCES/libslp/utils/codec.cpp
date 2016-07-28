/************************************
*
*此源文件
*filename : /root/git/libslp/SOURCES/libslp/utils/codec.cpp
*author   : sleeping
*email    : csleeping@163.com
*date     : 2016年07月28日 星期四 15时49分46秒
*
************************************/
#include "codec.h"


namespace slp{namespace codec{


const char* base64char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char* codec_base64::decode(const unsigned char* src,char* dst) 
{
    return this->base64_decode(src,dst);
}

char* codec_base64::encode(const unsigned char* src,char* dst,int length)
{
    return this->base64_encode(src,dst,length);
}

int   codec_base64::find_index(char* pchar)
{
    char* pbase64 = (char*)base64char;
    unsigned int index = 0;
    while (*pbase64) {
        if (*pchar ==  *pbase64) {
            return index;
        }
        ++index,++pbase64;
    }

    return -1;
}

char* codec_base64::base64_decode(const unsigned char* src,char* dst)
{
    if (!src || !dst) { return NULL; }

    for (int i=0,j=0; src[i] != '\0' ; i+=4,j+=3) {
        /*
         *取出4个base64编码过的字符对应的int数值
         */
        int tmp[4] = {0};
        for (int len=0; len < sizeof(tmp)/sizeof(tmp[0]); ++len) {
            tmp[len] = find_index((char*)src+i+len);
        }
    
        /*
         *复原第一个原字符
         */
        int i2c = tmp[0]<<2;
        i2c |= tmp[1]>>4;
        dst[j] = (char)i2c;

        /*
         *只有一个原字符可解码
         */
        if (src[i+2] == '=' && src[i+3] == '=') {
            dst[j+1] = '\0';
            break;
        }
        /*
         *复原第二个原字符
         */
        i2c = tmp[1]<<4;
        i2c |= tmp[2]>>2;
        dst[j+1] = (char)i2c;

        /*
         *只有两个原字符可解码
         */
        if (src[i+3] == '=') {
            dst[j+2] = '\0';
            break;
        }
        /*
         *复原第三个原字符
         */
        i2c = tmp[2]<<6;
        i2c |=  tmp[3];
        dst[j+2] = (char)i2c; 
    }

    return dst;
}

char* codec_base64::base64_encode(const unsigned char* src,char* dst,int length)
{
    if (!src || !dst) { return NULL; }

    for (int i=0,j=0; i<length; i+=3,++j) {
        unsigned int index = 0;
        /* 4个字符的第一个base64字符 */
        index = src[i]>>2;
        dst[j] = base64char[index];
       
        /* 原字符串余下一个字符 */
        if (i+1 >= length) {
            index = src[i]<<4 & 0x30;
            dst[++j] = base64char[index];
            dst[++j] = '=';
            dst[++j] = '=';
            break;
        }

        /* 4个字符的第二个base64字符 */
        index = (src[i]<<4 & 0x30);
        index |= src[i+1]>>4;
        dst[++j] = base64char[index];

        /* 原字符串余下2个字符 */
        if (i+2 >= length) {
            index = (src[i+1]<<2 & 0x3f);
            dst[++j] = base64char[index];
            dst[++j] = '=';
            break;
        }

        /* 4个字符的第三个base64字符 */
        index = (src[i+1]<<2) & 0x3c;
        index |= src[i+2]>>6;
        dst[++j] = base64char[index];

        /* 4个字符的第四个base64字符 */
        index = (src[i+2] & 0x3f);
        dst[++j] = base64char[index];
    } 
    return dst;
}

}}
