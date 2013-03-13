#ifndef RENDERDEVICE_HEAD_FILE
#define RENDERDEVICE_HEAD_FILE

#include "AirRenderHeader11.h"
namespace Air{
	
	namespace Client{
	
		namespace	Render{

			/**	\brief	DX11设备类
			*
			*	DX11设备类
			*
			***/
			class	Device11	:	
				public	Device{
			public:
				Device11();
				virtual	~Device11();
	
				/**	\brief	创建
				*   
				*	@remarks 	创建
				*	@see		Device11
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Create();
				/**	\brief	摧毁
				*   
				*	@remarks 	摧毁
				*	@see		Device11
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Destroy();

				

				virtual	void*	GetDevice();
				virtual	void*	GetContext();
				virtual	U32		GetAdapterCount();
				virtual	AString	GetAdapterName(U32	uiAdapterIndex);
				virtual	void	SelectAdapter(U32	uiSelectIndex);

				DxFactory1*		GetFactory1();
				DxFactory*		GetFactory();

				virtual	void		SetShader(enumShaderType	type,Shader*		pShader);
				virtual	Shader*		GetShader(enumShaderType	type);
				virtual	void		SetVB(U32	uiIndex,Buffer*	pBuffer);
				virtual	void		SetIB(Buffer*	pBuffer);
				virtual	void		SetVD(Vertex::IDeclare*	pDeclare);
				virtual void		SetCB(U32	uiIndex,Buffer*		pBuffer);
				virtual void		SetCB(enumShaderType	type,U32	uiIndex,Buffer*		pBuffer);
				virtual	void		SetVP(Viewport* pVP);
				virtual	void		SetSS(enumShaderType	type,U32	uiRegister,State*	pState);
				virtual	void		SetRS(State*	pState);
				virtual	void		SetDSS(State*	pState);
				virtual	void		SetBS(State*	pState);

				virtual	void		SetSRV(enumShaderType	type,U32	uiIndex,void*	pSRV);
				virtual	void		SetRTV_DSV(U32	uiCount,void**	pRTV,void*	pDSV);
				virtual	void		SetRTV_DSV_UAV(U32	uiCount,void**	pRTV,void*	pDSV,U32 uiUAVCount,void** pUAV);
				virtual	void		SetUAV(U32	uiCount,void**	pUAV);
				virtual	void		ClearUAV(void* pUAV,U32* uiClear);
				virtual	void		ClearUAV(void* pUAV,float* fClear);
				virtual	void		DrawOpt(const DrawOption&	opt);
			private:
				DxFactory*		m_pFactory;
				DxFactory1*		m_pFactory1;
				U32				m_uiAdapterCount;
				U32				m_uiCurrentAdapter;
	
				DxDevice*		m_pDevice;
				DxContext*		m_pContext;

				Shader*			m_pShaderArray[6];
			};
		}
	};
};
#endif // RENDERDEVICE_HEAD_FILE