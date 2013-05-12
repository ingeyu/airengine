#ifndef INTERFACEBASEPARTICLE_HEAD_FILE
#define INTERFACEBASEPARTICLE_HEAD_FILE

#include "AirEngineHeader.h"
#include "AirEngineMovableObject.h"
namespace Air{
	
	namespace Engine{
	
		namespace	Particle{
			/**	\brief	创建信息
			*
			*	创建信息
			*
			***/
			struct	Info{
				Info(AString	str	=	""){
					strConfigName	=	str;
				};
				AString	strConfigName;
			};
			/**	\brief	基本粒子类
			*
			*	基本粒子类
			*
			***/
			class	ENGINE_EXPORT	IBaseObject	:
				public	Common::IProduct,
				public	MovableObject
				{
			public:
				IBaseObject(CAString&	strName,Info*	pInfo);
	
				virtual	void	SetProperty(AString	strName,SInt&			iParam);
				virtual	void	SetProperty(AString	strName,Real&			fParam);
//				virtual	void	SetProperty(AString	strName,Vector2&		vParam);
//				virtual	void	SetProperty(AString	strName,Float3&		vParam);
				virtual	void	SetProperty(AString	strName,Float4&		vParam);
//				virtual	void	SetProperty(AString	strName,Float4&		qParam);
				virtual	void	SetProperty(AString	strName,Float44&		mParam);
				virtual	void	SetProperty(AString strName,void*			pParam);
	
				
				virtual	void	GetProperty(AString	strName,SInt&			iParam);
				virtual	void	GetProperty(AString	strName,Real&			fParam);
				//virtual	void	GetProperty(AString	strName,Vector2&		vParam);
				//virtual	void	GetProperty(AString	strName,Float3&		vParam);
				virtual	void	GetProperty(AString	strName,Float4&		vParam);
				//virtual	void	GetProperty(AString	strName,Float4&		qParam);
				virtual	void	GetProperty(AString	strName,Float44&		mParam);
				virtual	void*	GetProperty(AString strName);
	
				/**	\brief	设置生命
				*   
				*	@remarks 	设置生命
				*	@see		IBaseObject
				*	@return   	void
				*	@param		Real fLife
				*	@note
				*
				**/
				virtual	void	SetLife(Real	fLife);
	
				/**	\brief	设置为无限生命
				*   
				*	@remarks 	设置为无限生命
				*	@see		IBaseObject
				*	@return   	void
				*	@param		U1 bEnable
				*	@note
				*
				**/
				virtual	void	SetInfiniteLife(U1	bEnable);
	
				/**	\brief	判断是否已经死亡
				*   
				*	@remarks 	判断是否已经死亡
				*	@see		IBaseObject
				*	@return   	U1
				*	@note
				*
				**/
				virtual	U1		IsDead();
	
				/**	\brief	更新
				*   
				*	@remarks 	更新
				*	@see		IBaseObject
				*	@return   	void
				*	@note
				*
				**/
				virtual	void	Update(const FrameTime& frameTime);
	
			protected:
				Info			m_Info;				///<	创建信息
				U1				m_bIsDead;			///<	是否已经死亡
				Real			m_fLife;			///<	生命
				Real			m_fBornTime;		///<	出生时间
				U1				m_bInfiniteLife;	///<	无限生命
			};
		}
	
	};
};
#endif // INTERFACEBASEPARTICLE_HEAD_FILE