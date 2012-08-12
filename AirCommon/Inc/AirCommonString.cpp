#include "AirCommonString.h"

namespace	Air{
	namespace	Common{


		U1 StartWith( CAString& strWhole,CAString& strPart ){
			if(strWhole.empty())
				return	false;
			if(strPart.empty())
				return	true;

			int iWSize	=	strWhole.size();
			int	iPSize	=	strPart.size();

			if(	iWSize	<	iPSize)
				return	false;

			for(int i=0;i<iPSize;i++){
				if(strPart[i]	!=	strWhole[i])
					return	false;
			}

			return	true;
		}

		U1 EndWith( CAString& strWhole,CAString& strPart ){
			if(strWhole.empty())
				return	false;
			if(strPart.empty())
				return	true;

			int iWSize	=	strWhole.size();
			int	iPSize	=	strPart.size();

			if(	iWSize	<	iPSize)
				return	false;

			for(int i=0;i<iPSize;i++){
				if(	strPart[iPSize-1-i]	!=	
					strWhole[iWSize-1-i])
					return	false;
			}

			return	true;
		}

		AString GetPostfix( CAString& strName ){
			if(strName.empty()	||
				strName.size()<2){
					return	"";
			}

			int iSize	=	strName.size();
			for(int i=iSize-1;i>=0;i--){
				if(strName[i]	==	'.'){
					if(i!=iSize-1)
						return	&strName[i+1];
				}
			}
			return	"";
		}
	}
}