#ifndef AirParticle_h__
#define AirParticle_h__

#include "AirEngineMovableObject.h"
#include "AirParticleElement.h"

namespace	Air{
	namespace	Engine{
		
		class ParticleTemplate;

		class ENGINE_EXPORT	Particle	:	
			public	IProduct,
			public	MovableObject,
			public	Renderable{
		public:
			static AString ProductTypeName;
			struct Info{
				Info(){
					strTemplate=NULL;
					strMaterial=NULL;
				}
				AChar* strTemplate;
				AChar* strMaterial;
			};

			Particle(CAString& str,Info* pInfo);

			virtual	U1	Create();
			virtual	U1	Destroy();
			virtual	void				Update(const FrameTime& frameTime);
			virtual	void				ProcessRenderObject(U32	uiPhaseFlag);

			virtual	Matrix*				GetWorldMatrix();
			virtual	void				OnRender(Render::Device* pDevice);
			
			inline	U32					GetElementCount()const	{return m_lstElement.size();};
			inline	PElementList&		GetElementList()		{return m_lstElement;};
			
		protected:
			float							m_fBornTime;
			PElementList					m_lstElement;
			ParticleTemplate*				m_pTemplate;
			Info*							m_pInfo;
		};

		class ENGINE_EXPORT	ParticleSystem	:	
			public	IFactoryManager,
			public Singleton<ParticleSystem>
		{
		public:
			ParticleSystem();

			virtual	U1	Initialization();
			virtual	U1	Release();

			void		Update(const FrameTime& frameTime);

			U1		Compile(CAString&	strScript);
			U1		Compile(Data&		data);
			U1		Compile(U8*	pData,U32 uiSize);
			void*	GetTemplateInfo(CAString&	strName);
		protected:
			void*	PTAlloc(U32 uiSize);
			void*	PTAlloc(const void* pData,U32 uiSize);
		protected:
			STD_HASHMAP<AString,void*>	m_mapTemplateInfo;
			Data						m_TemplateData;
			U32							m_uiDataUsed;
		};
	}
}
#endif // AirParticle_h__