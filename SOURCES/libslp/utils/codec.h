/**
 * @file codec.h
 * @brief 此类用于各种编解码
 * @author sleeping
 * @version 1.0.0 
 * @date 2016-09-21
 */
#ifndef _SLP_CODEC_H
#define _SLP_CODEC_H

#include <iostream>
#include <map>
#include <string>


namespace slp{namespace codec{

    class codec;

    /**
     * @brief 编码类的构造器
     *
     * @param 无
     *
     * @return 构造好的编解码器
     */
    typedef codec* (*creator)();
    static std::map<std::string,creator> m;
   /**
    * @brief 此类主要用作各种编码和解码
    */
    class codec {
        public:
            virtual char* decode(const unsigned char* src,char* dst)=0;
            virtual char* encode(const unsigned char* src,char* dst,int length)=0;
            virtual ~codec(){};
    };

    class codec_base64 : public codec {
        public:
            char* decode(const unsigned char* src,char* dst);
            char* encode(const unsigned char* src,char* dst,int length);

            static inline codec* getter(){ 
                    static codec_base64 cb;
                    return &cb; 
            };
        private:
            int find_index(char* pchar);
            char* base64_decode(const unsigned char* src,char* dst);
            char* base64_encode(const unsigned char* src,char* dst,int length);
    };

    class codec_url : public codec {
        public:
            char* decode(const unsigned char* src,char* dst);
            char* encode(const unsigned char* src,char* dst,int length);

            static inline codec* getter() {
                    static codec_url cu;
                    return &cu;
            }
        private:
            inline unsigned char char_to_hex( unsigned char x ) {   
                return (unsigned char)(x > 9 ? x + 55: x + 48);   
            }   
  
            inline int is_alpha_number_char( unsigned char c ) {   
                if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') )   
                    return 1;   
                return 0;   
            }
            unsigned char* urldecode(const unsigned char* encd,unsigned char* decd);
            char*  urlencode(const unsigned char * src, unsigned char * dest, int  dest_len );
    };
    
    /**
     * @brief 单例获取编解码器
     *
     * @param name 编解码器的名称
     *
     * @return 编解码器类指针，无对应编解码器返回NULL
     */
    codec* instance(std::string name); 

    /**
     * @brief 注册编解码器
     *
     * @param name 编解码器名称
     * @param ctr 对应编解码器构造器
     *
     * @return true 注册成功，false 此类编解码器已注册过
     */
    static bool regist(std::string name,creator ctr);

}}

#endif /*_SLP_CODEC_H*/
