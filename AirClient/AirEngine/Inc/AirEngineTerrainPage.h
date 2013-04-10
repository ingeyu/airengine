#ifndef ENGINETERRAINPAGE_HEAD_FILE
#define ENGINETERRAINPAGE_HEAD_FILE


#include "AirEngineTerrainCommon.h"

namespace Air{
	
	
	namespace Engine{
	
	
			namespace	Terrain{
	
	
				/**	\brief	地形页
				*
				*	地形页
				*
				***/
				class ENGINE_EXPORT	Page{
				public:
					Page();
					virtual	~Page();
	
					
	
					/**	\brief	获取高度
					*   
					*	@remarks 	获取高度
					*	@see		Page
					*	@return   	U1
					*	@param		Real x
					*	@param		Real y
					*	@param		Real * z
					*	@note
					*
					**/
					U1				GetHeight(Real	x,Real	y,Real*	z);
	
					/**	\brief	载入
					*   
					*	@remarks 	载入
					*	@see		Page
					*	@return   	U1
					*	@note
					*
					**/
					virtual U1		Load();
					/**	\brief	卸载
					*   
					*	@remarks 	卸载
					*	@see		Page
					*	@return   	U1
					*	@note
					*
					**/
					virtual U1		UnLoad();
	
					/**	\brief	更新
					*   
					*	@remarks 	更新
					*	@see		Page
					*	@return   	void
					*	@note
					*
					**/
					virtual void	Update();
	
					
				public:
					static	SInt			Size;
				protected:
					void	CreateHeight(AString strPageName);
					void	CreateMaterial(AString strPageName);
					void	CreateObject(AString strPageName);
				private:
					void			ComputeTerrain(U8* pHeight,	Render::P*	pVertexBuff);
					Float3			ComputeNormal(Float4 vHeight,Real	fScale	=	1.0f);
	
					Material*				m_pMaterial;
					VertexBuffer*			m_VertexBuff;
	
					U8*						m_Height;
	
	
				};
	
			}
		
	
	};
};
#endif // RENDERTERRAINPAGE_HEAD_FILE