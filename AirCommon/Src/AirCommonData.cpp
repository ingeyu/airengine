#include "AirCommonData.h"

namespace	Air{
	namespace	Common{


		Data::Data( void* p,U32 uiSize )
		{
			Fill(p,uiSize);
		}

		Data::Data():buff(0),size(0)
		{

		}

		void Data::Fill( void* p,U32 uiSize )
		{
			ReSize(uiSize);
			memcpy(buff,p,uiSize);
		}

		Data::~Data()
		{
			Clear();
		}

		Data* Data::Clone()
		{
			if(IsNull())
				return	NULL;
			return	new	Data(buff,size);
		}

		U8* Data::ReSize( U32 s )
		{
			Clear();
			size	= s;
			//如果S==0表面为清空
			if(s==0)
				return	NULL;

			buff	=	(U8*)__Alloc(size);
			return buff;
		}

		void Data::Clear()
		{
			if(buff!=NULL){
				__Free(buff);
				buff=NULL;
			}
			_ZERO(size);
		}

	}
}