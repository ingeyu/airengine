#ifndef ENGINEPARTICLEENTITY_HEAD_FILE
#define ENGINEPARTICLEENTITY_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirRenderSystem.h"
#include "AirEngineMovableObject.h"
namespace Air{
	
	namespace Engine{
	
		/**	\brief	屏幕后期渲染物体
		*
		*	屏幕后期渲染物体
		*
		***/
		class	ENGINE_EXPORT	ParticleEntity	:
			public	TProduct<ParticleEntity>,
			public	MovableObject
		{
		public:
			struct	Info{
				Info(AString	strName	=	""){strParticleName	=	strName;};
				AString	strParticleName;
				Float3	vPosition;
				Float3	vVelocity;
				Real	fLife;
			};
		public:
			ParticleEntity(CAString&	strName,Info*	pInfo);
			/**	\brief	创建
			*   
			*	@remarks 	创建
			*	@see		ScreenEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual U1	Create();
			/**	\brief	摧毁
			*   
			*	@remarks 	摧毁
			*	@see		ScreenEntity
			*	@return   	U1
			*	@note
			*
			**/
			virtual U1	Destroy();
	
			/**	\brief	更新
			*   
			*	@remarks 	更新
			*	@see		ScreenEntity
			*	@return   	void
			*	@note
			*
			**/
			virtual void	Update();
	
	// 		/**	\brief	渲染
	// 		*   
	// 		*	@remarks 	渲染
	// 		*	@see		ScreenEntity
	// 		*	@return   	void
	// 		*	@note
	// 		*
	// 		**/
	// 		virtual	void	Render();
		protected:
			Info			m_Info;
	
		};
	
		class	ParticleEntityFactory	:
			public	IFactory{
		public:
			ParticleEntityFactory();
			/**	\brief	创建
			*   
			*	@remarks 	创建
			*	@see		BuffFactory
			*	@return   	IProduct*
			*	@param		AString strName
			*	@param		IFactoryParamList * lstParam
			*	@note
			*
			**/
			virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam =	NULL);
		};
	
	};
};
#endif // ENGINESCREENENTITY_HEAD_FILE