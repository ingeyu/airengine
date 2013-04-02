#ifndef ENGINECHARACTERTEXTUREANIMATIONMODEL_HEAD_FILE
#define ENGINECHARACTERTEXTUREANIMATIONMODEL_HEAD_FILE

#include "AirEngineCharacterAnimationModel.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Render{
			class	ITexture;
		}
	
	
		namespace	Character{
			namespace	Animation{
				/**	\brief	基于顶点纹理拾取的动画模型类
				*
				*	基于顶点纹理拾取的动画模型类
				*
				***/
				class	TextureModel	:
					public	Model{
				public:
					TextureModel(CAString&	strName,Info* pInfo);
	
	
					/**	\brief	创建
					*   
					*	@remarks 	创建
					*	@see		Model
					*	@return   	U1
					*	@note
					*
					**/
					virtual U1				Create();
					/**	\brief	摧毁
					*   
					*	@remarks 	摧毁
					*	@see		Model
					*	@return   	U1
					*	@note
					*
					**/
					virtual U1				Destroy();
					/**	\brief	更新
					*   
					*	@remarks 	更新
					*	@see		Model
					*	@return   	void
					*	@note
					*
					**/
					virtual void			Updata();
					/**	\brief	硬件渲染
					*   
					*	@remarks 	硬件渲染
					*	@see		Model
					*	@return   	void
					*	@note
					*
					**/
					virtual	void			RenderHardWare();
				protected:
					Render::Texture*		m_pBoneTexture;		///<	骨骼动画纹理
					Render::Texture*		m_pTempBoneTexture;	///<	骨骼动画缓冲纹理
				};
				/**	\brief	基于纹理拾取的模型工厂
				*
				*	基于纹理拾取的模型工厂
				*
				***/
				class	TextureModelFactory	:
					public	IFactory{
				public:
					TextureModelFactory();
	
					/**	\brief	创建产品
					*   
					*	@remarks 	创建产品
					*	@see		TextureModelFactory
					*	@return   	IProduct*
					*	@param		CAString& strName
					*	@param		IFactoryParamList * lstParam
					*	@note
					*
					**/
					virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam /* = NULL */);
				};
			}
		}
	
	};
};
#endif // ENGINECHARACTERTEXTUREANIMATIONMODEL_HEAD_FILE