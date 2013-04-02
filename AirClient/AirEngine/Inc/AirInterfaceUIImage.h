#ifndef INTERFACEUIIMAGE_HEAD_FILE
#define INTERFACEUIIMAGE_HEAD_FILE

#include "AirInterfaceUICommon.h"
namespace Air{
	
	namespace Engine{
		namespace	Render{
			class	ITexture;
		}
	
		namespace	UI{
			/**	\brief	UI图片类
			*
			*	UI图片类
			*
			***/
	// 		class	IImage{
	// 		public:
	// 			IImage(AString	strName,Float4	vUV){
	// 				m_strName			=	strName;
	// 				m_UVPositionSize	=	vUV;
	// 			};
	// 			AString				m_strName;				///<	图片名字
	// 			Float4				m_UVPositionSize;		///<	最终纹理纹理
	// 		};
			//typedef		Float4		Image;	
	
	
			/**	\brief	图片集
			*
			*	图片接
			*
			***/
			class	ENGINE_EXPORT	IImageSet	:
				public	IProduct{
			public:
				typedef	std::map<AString,Float4>	ImageMap;
				typedef	ImageMap::iterator			ImageMapItr;
				typedef	ImageMap::value_type		ImageMapPair;
	
				/**	\brief	创建信息
				*
				*	创建信息
				*
				***/
				struct	Info{
					Float2	vTextureSize;
				};
			public:
				IImageSet(AString	strName,Info*	pInfo);
	
				/**	\brief	创建
				*   
				*	@remarks 	创建
				*	@see		IImageSet
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Create();
				/**	\brief	摧毁图片集
				*   
				*	@remarks 	摧毁图片集
				*	@see		IImageSet
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1	Destroy();
				/**	\brief	获取图片坐标
				*   
				*	@remarks 	获取图片坐标
				*	@see		Float4
				*	@return   	Float4
				*	@param		AString strName
				*	@note
				*
				**/
				Float4	GetImage(AString	strName,Float4*	pVectorInt	=	NULL);
				/**	\brief	获取纹理数量
				*   
				*	@remarks 	获取图片数量
				*	@see		IImageSet
				*	@return   	UInt
				*	@note
				*
				**/
				inline	UInt	GetImageCount(){
					return	m_mapImage.size();
				};
				/**	\brief	获取纹理尺寸
				*   
				*	@remarks 	获取纹理尺寸
				*	@see		IImageSet
				*	@return   	Float2
				*	@note
				*
				**/
				Float2				GetTextureSize();
			protected:
				ImageMap			m_mapImage;
				//Render::ITexture*	m_pTexture;
				Float2				m_vTextureSize;
			};
		}
	
	};
};
#endif // INTERFACEUIIMAGE_HEAD_FILE