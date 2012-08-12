#ifndef AirRenderDevice_h__
#define AirRenderDevice_h__

#include "AirRenderCommon.h"

namespace	Air{
	namespace	Client{
		class	Shader;
		class	Viewport;
		namespace	Render{
			class	Buffer;
			class	Texture;
			class	State;
			class	ENGINE_EXPORT	Device	:	
				public	IProduct{
			public:
				Device();
				virtual	enumSystemVersion	GetHWVersion();

				virtual void		SetVD(VertexDeclare*	pDeclare);
				virtual void		SetVB(U32	uiIndex,Buffer*	pBuffer);
				virtual void		SetIB(Buffer*		pBuffer);
				virtual void		SetCB(U32	uiIndex,Buffer*		pBuffer);
				virtual void		SetCB(enumShaderType	type,U32	uiIndex,Buffer*		pBuffer);
				
				virtual	void		SetShader(enumShaderType	type,Shader*	pShader);
				virtual	void		SetSS(enumShaderType	type,U32	uiRegister,State*	pState);
				virtual	void		SetRS(State*	pState);
				virtual	void		SetDSS(State*	pState);
				virtual	void		SetBS(State*	pState);
				virtual	void		SetVP(Viewport* pVP);
				virtual	void		SetSRV(enumShaderType	type,U32	uiIndex,void*	pSRV);
				virtual	void		SetRTV_DSV(U32	uiCount,void**	pRTV,void*	pDSV);
				virtual	void		SetUAV(U32	uiCount,void**	pUAV);

				virtual	void		DrawObject(Renderable*	pObj,U1	bSkin	=	false);
				virtual	void		DrawOpt(const DrawOption&	opt);

				void				ResetCounter(){
					m_uiDrawBatch			=	0;
					m_uiDrawTriangleCount	=	0;
				};
				U32					GetDrawBatch(){return m_uiDrawBatch;};
				U32					GetDrawTriangleCount(){return m_uiDrawTriangleCount;};
			protected:
				enumSystemVersion	m_HWVersion;
				U32					m_uiDrawBatch;
				U32					m_uiDrawTriangleCount;
			};
			typedef	std::vector<Device*>	DeviceVector;
		}
	}
}
#endif // AirRenderDevice_h__