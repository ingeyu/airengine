#ifndef AirPipelineVoxelGen_h__
#define AirPipelineVoxelGen_h__

#include "AirRenderSystem.h"

namespace	Air{
	namespace	Engine{
		class Pipeline;
		class	VoxelGenerator	:	public	MemoryObject{
		public:
			VoxelGenerator();

			U1		Initialize(Render::Window*	pMainWindow);
			U1		Release();
			void	Update(Renderable* pRenderable,Pipeline* pPipeline);
			void	Build(Pipeline* pPipeline);

			void	SetParam(U32 uiDepth,float fScale);
			void	ShowSVO(U1 bShow);
		protected:
			Render::Buffer*	m_pVoxel;
			Render::Buffer*	m_pNodeTree;
			Material*		m_pGenVoxelTree;
			Material*		m_pMipVoxelTree;
			Camera*			m_pCamera;
			RenderTarget*	m_pRT;

			Render::Buffer*	m_pDebugSVO;
			Renderable*		m_pDebugSVORenderable;
			Material*		m_pDebugSVOMaterial;

			Float4			m_SVOParam;//x Depth y Bound z HalfBound w Scale
			U1				m_bDebugSVO;
		};
	}
}
#endif // AirPipelineVoxelGen_h__
