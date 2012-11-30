#ifndef RENDERVERTEXBUFF_HEAD_FILE
#define RENDERVERTEXBUFF_HEAD_FILE

#include "AirRenderHeader11.h"


namespace Air{
	
	namespace Client{
	
		namespace	Render{
	
	

			/**	\brief	¶¥µã»º³å
			*
			*	¶¥µã»º³å
			*
			***/
			class Buffer11	:	
				public	Buffer{
			public:
	
			public:
				Buffer11(CAString&	strName,Info*	pInfo);
				
				virtual	U1	Create();
				/**	\brief	´Ý»Ù
				*   
				*	@remarks 	´Ý»Ù
				*	@see		Buff
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		Destroy();
				virtual	U1		UpdateData(void*	pData);
	
				virtual	void*	GetBuffer();
				virtual	void*	GetSRV();
				virtual	void*	GetUAV();

				virtual	void	CopyBufferTo(Buffer*	pDest);
				virtual	U1		Write(U32	uiOffset,U32	uiSize,const void*	pSourceData);

				DxVertexBuff*	m_pBuffer;
				DxSRV*			m_pBufferSRV;
				DxUAV*			m_pBufferUAV;
			};

		}
	
	};
};
#endif // RENDERVERTEXBUFF_HEAD_FILE