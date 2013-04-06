#ifndef AirPipelineVoxelGen_h__
#define AirPipelineVoxelGen_h__

#include "AirRenderSystem.h"

namespace	Air{
	namespace	Engine{
		class	VoxelGenerator{
		public:
			VoxelGenerator();

			U1		Initialize(Render::Window*	pMainWindow);
			U1		Release();
			void	Update(Renderable* pRenderable);

			Render::Buffer*	m_pVoxel;
			Render::Buffer*	m_pNodeTree;
			Material*		m_pGenVoxelTree;
			Material*		m_pMipVoxelTree;
			Camera*			m_pCamera;
			RenderTarget*	m_pRT;
		};
	}
}
#endif // AirPipelineVoxelGen_h__
