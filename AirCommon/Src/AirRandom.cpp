#include "AirRandom.h"
#include "AirCommonHeader.h"
#include "mmsystem.h"
#include "math.h"
#include "xnamath.h"
namespace Air{
	
	namespace Common{
		static UInt	g_iIncreaseNumber = 0;
		Real Number::Random(Real fMin,Real fMax){
			Real f,i;
			//随机浮点数 取小数部分
			f = modf((float)rand()*0.0001f,&i);
			Real fOffset = fMax - fMin;
			return f*fOffset + fMin;
		}
		SInt Number::Random(SInt iMin,SInt iMax){
			//InitSrand();
			SInt iOffset = iMax - iMin + 1;
			return rand()%iOffset + iMin;
		}
		unsigned int Number::Increase(){
			return g_iIncreaseNumber++;
		}
		AString Number::Increase(const AString& strName){
			CHAR buff[MAX_NAME];
			sprintf_s(buff,MAX_NAME,"%s[%d]",strName.c_str(),Increase());
			return AString(buff);
		}
		void Number::InitSrand(){
			srand(timeGetTime());
		}
	};
};