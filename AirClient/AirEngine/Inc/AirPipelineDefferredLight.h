#ifndef AirPipelineDefferredLight_h__
#define AirPipelineDefferredLight_h__

#include "AirRenderSystem.h"

namespace	Air{
	namespace	Engine{
		class	CSRenderable;
		class	Pipeline;
		class	MeshEntity;
		class	Material;
		struct PointLightInfo{
			Float3	vPos;
			float	fSize;
			Float3	vColor;
		};
		typedef		STD_VECTOR<PointLightInfo>	PointLightVector;
		class	DefferredLight	:	public	MemoryObject
		{
		public:
			DefferredLight();

			virtual	U1		Initialization( Pipeline* pPipeline);
			virtual	U1		Release();
			virtual	void	Update(const FrameTime& frameTime);
			virtual	void	AddPointLight(const Float3& pos,float fSize,const Float3& vColor);
		protected:
			Material*			m_pPointMaterial;
			MeshEntity*			m_pSphere;
			RenderTarget*		m_pLightBuffer;
			PointLightVector	m_vecPointLight;
			Pipeline*			m_pPipeline;
		};

		class	TileBaseLight	:	public	DefferredLight{
		public:
			TileBaseLight();
			virtual	U1		Initialization( Pipeline* pPipeline);
			virtual	U1		Release();
			virtual	void	Update(const FrameTime& frameTime);
			CSRenderable*	m_pCSRenderable;
		};
	}
}
#endif // AirPipelineDefferredLight_h__
