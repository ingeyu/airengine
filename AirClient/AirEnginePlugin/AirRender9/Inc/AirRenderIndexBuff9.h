#ifndef RENDERINDEXBUFF_HEAD_FILE
#define RENDERINDEXBUFF_HEAD_FILE

#include "AirRenderHeader9.h"
#include "AirRenderFactory9.h"
#include "AirCommonFile.h"
namespace Air{
	
	namespace Client{
	
		namespace	Render{
			namespace	Index{
				/**	\brief	Ë÷Òý»º³å
				*
				*	Ë÷Òý»º³å
				*
				***/
				class Buff	:	
					public	Buffer{
				public:
	
				public:
					Buff(CAString&	strName,Info*	pInfo);
					/**	\brief	´Ý»Ù
					*   
					*	@remarks 	´Ý»Ù
					*	@see		Buff
					*	@return   	U1
					*	@note
					*
					**/
					virtual	U1	Destroy();


					virtual	void*	GetBuffer();
				protected:
					DxIndexBuff*	m_pBuffer;
				};
			}
		}
	
	};
};
#endif // RENDERINDEXBUFF_HEAD_FILE