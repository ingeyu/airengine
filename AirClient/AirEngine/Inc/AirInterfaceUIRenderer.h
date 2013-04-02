#ifndef INTERFACEUIRENDERER_HEAD_FILE
#define INTERFACEUIRENDERER_HEAD_FILE

#include "AirRenderTarget.h"
#include "AirInterfaceUIElement.h"
#include "AirEngineRenderable.h"
namespace Air{
	
	namespace Engine{
		class	ScreenEntity;

	
		namespace	UI{
			namespace	Window{
				class	IControl;
			}
	#define	MAX_WINDOW	60
			/**	\brief	UI渲染
			*
			*	UI渲染
			*
			***/
			class	ENGINE_EXPORT	Renderer	:
				public	Renderable,
				public	Render::TargetManager{
			public:
				Renderer();
	
				/**	\brief	初始化
				*   
				*	@remarks 	初始化
				*	@see		Renderer
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		InitEffect();
				/**	\brief	释放
				*   
				*	@remarks 	释放
				*	@see		Renderer
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	ReleaseEffect();
	
				/**	\brief	存入需要渲染的UI
				*   
				*	@remarks 	存入需要渲染的UI
				*	@see		Renderer
				*	@return   	void
				*	@param		IElement*	pElement
				*	@note
				*
				**/
				virtual	void	Push(IElement*	pElement);
	
	
				/**	\brief	开始渲染
				*   
				*	@remarks 	开始渲染
				*	@see		Renderer
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	StartRender();
	
				/**	\brief	渲染一个UI
				*   
				*	@remarks 	
				*	@see		Renderer
				*	@return   	void
				*	@param		Window::IControl*	pControl
				*	@note
				*
				**/
				virtual	void	RenderControl(Window::IControl*	pControl);
	
				/**	\brief	更换材质
				*   
				*	@remarks 	更换材质
				*	@see		Renderer
				*	@return   	void
				*	@param		AString strMaterialName
				*	@note
				*
				**/
				void			SetMaterialName(AString	strMaterialName);
	
				/**	\brief	获取纹理大小
				*   
				*	@remarks 	获取纹理大小
				*	@see		Renderer
				*	@return   	Client::Float4
				*	@note
				*
				**/
				inline	Float4*	GetTextureSize(){
					return	&m_vTextureSize;
				};
				/**	\brief	获取图片集设置
				*   
				*	@remarks 	获取图片集设置
				*	@see		Renderer
				*	@return   	IImageSet*
				*	@note
				*
				**/
				inline	IImageSet*		GetImageSet(){
					return	m_pImageSet;
				};
	
				/**	\brief	获取图片
				*   
				*	@remarks 	获取图片
				*	@see		Renderer
				*	@return   	Client::Float4
				*	@param		AString strName
				*	@note
				*
				**/
				Float4	GetImage(AString	strName){
					if(m_pImageSet!=NULL){
						return	m_pImageSet->GetImage(strName);
					}
					return Float4(0,0,0,0);
				}
				/**	\brief	渲染窗口目标到缓存
				*   
				*	@remarks 	渲染窗口目标到缓存
				*	@see		Renderer
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	RenderTarget();
			protected:
				VectorArray				m_vPositionSizeArray;
				VectorArray				m_vUVPositionSizeArray;
				VectorArray				m_vColorArray;
				VectorArray				m_vCustomArray;
				UInt					m_uiSize;
				Float4					m_vTextureSize;
				IImageSet*				m_pImageSet;
	
				ScreenEntity*			m_pScreenEnt;
			};
		}
	
	};
};
#endif // INTERFACEUIRENDER_HEAD_FILE