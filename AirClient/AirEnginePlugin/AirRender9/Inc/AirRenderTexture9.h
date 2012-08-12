#ifndef RENDERTEXTURE_HEAD_FILE
#define RENDERTEXTURE_HEAD_FILE

#include "AirRenderHeader9.h"
#include "AirRenderFactory9.h"
namespace Air{
	
	
	namespace Client{
	
		namespace	Render{
			/**	\brief	基本纹理
			*
			*	基本纹理
			*
			***/
			class	Texture9	:
				public	ITexture{
			public:
	
			public:
				Texture9(CAString&	strTextureName,Info*	pInfo);
				/**	\brief	创建
				*   
				*	@remarks 	创建
				*	@see		Texture
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Create( );
				/**	\brief	摧毁
				*   
				*	@remarks 	摧毁
				*	@see		Texture
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Destroy( );
				/**	\brief	获取纹理类型
				*   
				*	@remarks 	获取纹理类型
				*	@see		Texture
				*	@return   	SInt
				*	@note
				*
				**/
				inline	enumType	GetTextureType(){return	m_Info.type;};
	
				/**	\brief	保存纹理到文件
				*   
				*	@remarks 	保存纹理到文件
				*	@see		Texture
				*	@return   	U1
				*	@param		AString strName
				*	@note
				*
				**/
				virtual U1	SaveToFile(AString	strName);
				/**	\brief	保存纹理到内存
				*   
				*	@remarks 	保存纹理到内存
				*	@see		Texture
				*	@return   	U1
				*	@param		MemoryData * * ppData
				*	@note
				*
				**/
				virtual U1	SaveToMemery(MemoryData**	ppData);

				/**	\brief	重建
				*   
				*	@remarks 	重建
				*	@see		Target
				*	@return   	void
				*	@param		Info & info
				*	@note
				*
				**/
				virtual	void		ReCreate(Info&	info);
				/**	\brief	锁定纹理
				*   
				*	@remarks 	锁定纹理
				*	@see		ITexture
				*	@return   	U1
				*	@param		LockRect * rect
				*	@param		DWORD flag
				*	@note
				*
				**/
				virtual	U1	Lock(LockRectOption*	p,DWORD flag	=	LOCK_DISCARD );
				/**	\brief	解锁纹理
				*   
				*	@remarks 	解锁纹理
				*	@see		ITexture
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	UnLock();
				
				/**	\brief	使用HDC绘制
				*   
				*	@remarks 	使用HDC绘制
				*	@see		Texture
				*	@return   	void
				*	@param		DrawDCCallback * pCallback
				*	@note
				*
				**/
				virtual	HDC	GetHDC();
				virtual	void*					GetTexture();
				virtual	void*					GetSurface(enumCubeFaceType	uiFaceType);

				virtual	void	OnLostDevice();
				virtual	void	OnResetDevice();

				IDirect3DTexture9*			m_pTexture2D;
				IDirect3DCubeTexture9*		m_pTextureCube;
				IDirect3DVolumeTexture9*	m_pTexture3D;
				IDirect3DSurface9*			m_pSurface;

				MemoryData*					m_pTextureData;

				Resource::IStream*			m_pStream;
			};
	
			class	Texture9Factory	:	public	Factory{
			public:
				Texture9Factory();
	
				/**	\brief	创建产品
				*   
				*	@remarks 	创建产品
				*	@see		TextureFactory
				*	@return   	IProduct*
				*	@param		AString strName
				*	@param		IFactoryParamList * lstParam
				*	@note
				*
				**/
				virtual IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam = NULL);
			};
	
		}
	};
};
#endif // RENDERTEXTURE_HEAD_FILE