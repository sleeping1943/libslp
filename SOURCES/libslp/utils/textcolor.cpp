#include "textcolor.h"

namespace slp{

	void textout(const char* pstr,const int num, const char* color, bool is_output){
#ifndef	NOOUTPUT
		if (true == is_output) printf("%s%s%d\033[m", color, pstr, num);
#endif
	}

	void textout(const char* pstr,const char* color, bool is_output){
#ifndef	NOOUTPUT
		if (true == is_output) printf("%s%s\033[m", color, pstr);
#endif
	}

	void textout(const std::string label,const std::string str,const std::string color,bool is_output){
#ifndef	NOOUTPUT
		if (true == is_output) std::cout << color << label << str << NONE << std::endl;
#endif
	}

	void textout(const std::string label,const int num,const std::string color,bool is_output){
#ifndef	NOOUTPUT
		if (true == is_output) std::cout << color << label << num << NONE << std::endl;
#endif
	}
};

