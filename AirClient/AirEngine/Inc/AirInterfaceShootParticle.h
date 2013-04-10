#ifndef INTERFACESHOOTPARTICLE_HEAD_FILE
#define INTERFACESHOOTPARTICLE_HEAD_FILE

#include "AirInterfaceParticle.h"
namespace Air{
	
	namespace Engine{
	
		class	ShootParticle	:
			public	IParticle{
		public:
			static AString	ProductTypeName;
			ShootParticle(CAString&	strName,Info*	pInfo);
	
			/**	\brief	设置参数
			*   
			*	@remarks 	设置参数
			*	@see		ShootParticle
			*	@return   	void
			*	@note
			*
			**/
			virtual	void	SetParticleParam();
	
			virtual	void	Updata();
	
			virtual void	SetPosition(Float3 vSrcPos,Float3 vDstPos);
	
		};
		class	ShootParticleFactory	:
			public	IFactory{
		public:
			ShootParticleFactory();
	
			/**	\brief	创建粒子效果
			*   
			*	@remarks 	创建粒子效果
			*	@see		IParticleFactory
			*	@return   	IProduct*
			*	@param		AString strName
			*	@param		IFactoryParamList * lstParam
			*	@note
			*
			**/
			virtual	IProduct*	NewProduct(CAString& strName,IFactoryParamList* lstParam /* = NULL */);
		};
	};
};
#endif // INTERFACESHOOTPARTICLE_HEAD_FILE