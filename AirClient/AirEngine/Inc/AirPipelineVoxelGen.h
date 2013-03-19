#ifndef AirPipelineVoxelGen_h__
#define AirPipelineVoxelGen_h__

#include "AirRenderSystem.h"

namespace	Air{
	namespace	Client{
		class	VoxelGenerator{
		public:
			VoxelGenerator();

			U1		Initialize(Render::Window*	pMainWindow);
			U1		Release();
			void	Update(Renderable* pRenderable);

			Render::Buffer*	m_pVoxelNodeTree;
			Render::Buffer*	m_pBrick;
			Material*		m_pGenVoxelTree;
			Material*		m_pMipVoxelTree;
		};
	}
}
#endif // AirPipelineVoxelGen_h__
