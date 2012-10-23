#ifndef AirRenderTexture_h__
#define AirRenderTexture_h__

#include "AirRenderCommon.h"

namespace	Air{
	namespace	Client{
		namespace	Render{
			

			/**	\brief	纹理基类接口
			*
			*	纹理基类
			*
			***/
			class	ENGINE_EXPORT	Texture
				:	public	IProduct{


			public:

	
				/**	\brief	纹理信息
				*
				*	用于创建的时候的参数
				*
				***/
				struct Info{
					Info(){
						type	=	enTT_Texture2D;
						format	=	enTFMT_UNKNOWN;
						usage	=	enUSAGE_RENDERTARGET;
						width	=	1;
						height	=	1;
						depth	=	1;
						fScreenScale	=	-1;
						viewFlag	=	0;
						mipmap		=	1;
						bAutoMipMap	=	false;
					};
					void	SetRenderToTexture(UInt	uiWidth,UInt uiHeight,enumTextureFormat	fmt	=	enTFMT_R8G8B8A8_UNORM){
						width	=	uiWidth;
						height	=	uiHeight;
						usage	=	enUSAGE_RENDERTARGET;
						format	=	fmt;
						fScreenScale	=	-1.0f;
					};
					void	SetRenderToTexture(Real fScale	=	1.0f,enumTextureFormat	fmt	=	enTFMT_R8G8B8A8_UNORM){
						width	=	1;
						height	=	1;
						usage	=	enUSAGE_RENDERTARGET;
						format	=	fmt;
						fScreenScale	=	fScale;
					};
					void	SetCubeTexture(){
						type	=	enTT_TextureCUBE;
					};
					void	SetVolumeTexture(){
						type	=	enTT_Texture3D;
					};
					void	SetRenderToCubeTexture(UInt	uiSize,enumTextureFormat	fmt	=	enTFMT_R8G8B8A8_UNORM){
						type	=	enTT_TextureCUBE;
						format	=	fmt;
						width	=	uiSize;
						height	=	uiSize;
						depth	=	uiSize;
					};
					void	SetDynamicTexture(UInt	uiWidth,UInt uiHeight,enumTextureFormat	fmt	=	enTFMT_R8G8B8A8_UNORM){
						usage	=	enUSAGE_DYNAMIC;
						width	=	uiWidth;
						height	=	uiHeight;
						format	=	fmt;
					};
					void	SetManageTexture(UInt	uiWidth,UInt uiHeight,enumTextureFormat	fmt	=	enTFMT_R8G8B8A8_UNORM)
					{
						usage	=	enUSAGE_MANAGED;
						width	=	uiWidth;
						height	=	uiHeight;
						format	=	fmt;
					};
					void	SetViewFlag(U32	flag	=	enVF_SRV){
						viewFlag	=	flag;
					}
					enumTextureType		type;					///<	纹理类型
					enumTextureFormat	format;					///<	纹理格式
					enumUsage			usage;					///<	纹理用途
					U32					width;					///<	纹理宽度
					U32					height;					///<	纹理高度
					U32					depth;					///<	纹理深度
					Real				fScreenScale;			///<	是否与屏幕对齐
					U32					mipmap;					///<	mipmap数量
					U32					viewFlag;				///<	ShaderResourceView RenderTargetView enumViewFlag
					U1					bAutoMipMap;
				};
			public:
				Texture(CAString&	strName,Info*	pInfo);
				virtual	~Texture();

				virtual	bool			Write(void* pData,U32	uiPitch,RECT* pRect=NULL){return false;};

				virtual	void*			GetBuffer(){return	NULL;};
				virtual	void*			GetRTV(){return	NULL;};
				virtual	void*			GetUAV(){return	NULL;};
				virtual	void*			GetSRV(){return	NULL;};
				virtual	void			CopyBufferTo(Texture*	pDest)=NULL;
				virtual	void			GenMipMap()=NULL;

				inline	U32						GetWidth()			{return	m_Info.width;};
				inline	U32						GetHeight()			{return	m_Info.height;};
				inline	U32						GetDepth()			{return	m_Info.depth;};
				inline	U32						GetMipmapCount()	{return	m_Info.mipmap;};
				inline	enumTextureFormat		GetFormat()			{return	m_Info.format;};
				inline	enumTextureType			GetType()			{return	m_Info.type;};
				inline	U1						IsAbsWidthHeight()	{return	m_Info.fScreenScale	>0.0f;};
				inline	U1						IsAutoMipmap()		{return	m_Info.bAutoMipMap;};
				const	Info&					GetInfo()			{return	m_Info;};
			protected:
				Info			m_Info;					///<	创建信息
			};
		}
	}
}
#endif // AirRenderTexture_h__