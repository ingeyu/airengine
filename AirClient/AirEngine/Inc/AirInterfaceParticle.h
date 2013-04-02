#ifndef INTERFACEPARTICLE_HEAD_FILE
#define INTERFACEPARTICLE_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineMovableObject.h"
namespace Air{
	
	namespace Engine{
		//namespace	Particle{
	
		/**	\brief	基本粒子
		*
		*	基本粒子
		*
		***/
		class	IParticle	:	
			public	MovableObject,
			public	Common::IProduct{
		public:
			struct	Info{
				Info(){
					vVelocity	=	Float3(0,0,0);
					vPosition	=	Float3(0,0,0);
				}
				AString	strParticleFile;
				Float3	vVelocity;
				Float3	vPosition;
			};
		public:
			IParticle(CAString&	strName,Info*	pInfo);
	
			/**	\brief	创建粒子
			*   
			*	@remarks 	创建粒子
			*	@see		IParticle
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Create();
	
			/**	\brief	摧毁粒子
			*   
			*	@remarks 	摧毁粒子
			*	@see		IParticle
			*	@return   	U1
			*	@note
			*
			**/
			virtual	U1	Destroy();
			/**	\brief	更新
			*   
			*	@remarks 	更新
			*	@see		IParticle
			*	@return   	void
			*	@note
			*
			**/
			virtual	void	Updata();
	
			/**	\brief	渲染
			*   
			*	@remarks 	渲染
			*	@see		IParticle
			*	@return   	void
			*	@note
			*
			**/
			virtual	void	Render();
			/**	\brief	渲染alpha
			*   
			*	@remarks 	渲染alpha
			*	@see		IParticle
			*	@return   	void
			*	@note
			*
			**/
			virtual void	RenderAlpha();
	
			/**	\brief	设置粒子参数
			*   
			*	@remarks 	设置粒子参数
			*	@see		IParticle
			*	@return   	void
			*	@note
			*
			**/
			virtual	void	SetParticleParam();
	
			inline	U1		IsDeath(){
				return	m_bDeath;
			}
		protected:
			Info		m_Info;
			Real		m_fLife;
			Real		m_fCreateTime;
			U1			m_bDeath;
			Real&		m_fTotalTime;
			//Float3		m_vVelocity;
		};
	
		class	IParticleFactory	:
			public	IFactory{
		public:
			IParticleFactory();
	
			/**	\brief	创建粒子效果
			*   
			*	@remarks 	创建粒子效果
			*	@see		IParticleFactory
			*	@return   	IProduct*
			*	@param		AString& strName
			*	@param		IFactoryParamList * lstParam
			*	@note
			*
			**/
			virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam /* = NULL */);
		};
		//}
	
	};
};
#endif // INTERFACEPARTICLE_HEAD_FILE