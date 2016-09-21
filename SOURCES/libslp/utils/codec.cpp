/************************************
*
*此源文件
*filename : /root/git/libslp/SOURCES/libslp/utils/codec.cpp
*author   : sleeping
*email    : csleeping@163.com
*date     : 2016年07月28日 星期四 15时49分46秒
*
************************************/

/*
 *for C library
 */
#include <string.h>

/*
 *for C++ library
 */
#include <map>

/*
 *for user library
 */
#include "codec.h"
#include "log.h"


namespace slp{namespace codec{

using slp::log::log;
using slp::log::level;
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


char* codec_url::decode(const unsigned char* src,char* dst)
{
    return (char*)this->urldecode(src,(unsigned char*)dst);
}

char* codec_url::encode(const unsigned char* src,char* dst,int length)
{
    return (char*)this->urlencode(src,(unsigned char*)dst,length);
}

unsigned char* codec_url::urldecode(const unsigned char* encd,unsigned char* decd)
{
    int j,i;   
    char *cd =(char*) encd;   
    char p[2];   
    j=0;   
  
    int len = strlen(cd);
    for( i = 0; i < len; i++ ) {   
        memset( p, '\0', 2 );   
        if( cd[i] != '%' ) {   
            decd[j++] = cd[i];   
            continue;   
        }   
        p[0] = cd[++i];   
        p[1] = cd[++i];   
        p[0] = p[0] - 48 - ((p[0] >= 'A') ? 7 : 0) - ((p[0] >= 'a') ? 32 : 0);   
        p[1] = p[1] - 48 - ((p[1] >= 'A') ? 7 : 0) - ((p[1] >= 'a') ? 32 : 0);   
        decd[j++] = (unsigned char)(p[0] * 16 + p[1]);   
    }   
    decd[j] = '\0';   
    return decd;   
}

char*  codec_url::urlencode(const unsigned char * src, unsigned char * dest, int  dest_len )
{
   unsigned char ch;   
   int  len = 0;   
    
   while (len < (dest_len - 4) && *src)   
   {   
       ch = (unsigned char)*src;   
       if (*src == ' ') {   
           *dest++ = '+';   
       }   
       else if (is_alpha_number_char(ch) || strchr("=!~*'()", ch)) {   
           *dest++ = *src;   
       }   
       else {   
           *dest++ = '%';   
           *dest++ = char_to_hex( (unsigned char)(ch >> 4) );   
           *dest++ = char_to_hex( (unsigned char)(ch % 16) );   
       }    
       ++src;   
       ++len;   
   }   
   *dest = 0;   
   return (char*)dest;   

}


codec* instance(std::string name)
{
    auto it = m.find(name);
    if (it == m.end()) {
        return NULL;
    }

    return it->second();
}


bool regist(std::string name,creator ctr)
{
    if (m.find(name) == m.end()) {
        m[name] = ctr; 
        char buf[64];
        snprintf(buf,sizeof(buf),"%s编码解析注册成功",name.c_str());
        log::trace(time(NULL),__FUNCTION__,std::string(buf),level::print);
        return false;
    }

    return true;
}

bool regist_url = regist("url",codec_url::getter);
}}
