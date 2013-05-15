#ifndef AirParticleEmitter_h__
#define AirParticleEmitter_h__

#include "AirEngineHeader.h"
#include "AirParticleElement.h"
namespace	Air{
	namespace	Engine{
		class	Particle;

		class	ENGINE_EXPORT	ParticleEmitter	:	public	IProduct{
		public:
			struct Info{
				float		fFreq;
				float		fElementLife;
				Float3		vVelocityDir;
				float		fVelocityAngle;
			};
			static	AString	ProductTypeName;
			static	void*	ScriptParser(StringVector& vecWord,U32& i);
			ParticleEmitter(CAString& strName,Info* pInfo);
			virtual	U1		Create();
			virtual	U1		Destroy();
			virtual	void	Update(const FrameTime& frameTime,Particle* pParticle);
			virtual	void	ElementBorn(const FrameTime& frameTime,PElementList& lst);
		public:
			inline	U1				IsEnable(){return m_bEnable;};
			inline	void			SetEnable(U1 bEnable){m_bEnable = bEnable;};
		protected:
			virtual	ParticleElement*	NewElement(double dTotalTime);
			virtual	void				RandomVelocity(Float3& vVelocity);
			virtual	void				RandomPosition(Float3& vPos);
			virtual	void				RandomSize(float& fSize);
		protected:
			float			m_fUpdateTime;
			Info*			m_pInfo;
			U1				m_bEnable;
		};

		class	ENGINE_EXPORT	BoxEmitter	:	public ParticleEmitter
		{
		public:
			struct Info	:	ParticleEmitter::Info{
				Float3	vCenter;
				Float3	vHalfSize;
			};
			static	AString	ProductTypeName;
			static	void*	ScriptParser(StringVector& vecWord,U32& i);
			BoxEmitter(CAString& strName,BoxEmitter::Info* pInfo);
			//virtual	void	ElementBorn(const FrameTime& frameTime,PElementList& lst);
			virtual	void				RandomPosition(Float3& vPos);
		protected:
			Float3	m_vCenter;
			Float3	m_vHalfSize;
		};

		class ENGINE_EXPORT	SphereEmitter	:	public ParticleEmitter{
		public:
			struct Info	:	ParticleEmitter::Info{
				Float3	vCenter;
				float	fRadius;
			};
			static	AString	ProductTypeName;
			SphereEmitter(CAString& strName,SphereEmitter::Info* pInfo);
			virtual	void	ElementBorn(const FrameTime& frameTime,PElementList& lst);
		protected:
			Float3	m_vCenter;
			float	m_fRadius;
		};

	}
}
#endif // AirParticleEmitter_h__