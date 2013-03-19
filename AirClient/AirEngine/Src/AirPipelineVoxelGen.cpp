#include "AirPipelineVoxelGen.h"

namespace	Air{
	namespace	Client{


		VoxelGenerator::VoxelGenerator()
		{
			m_pVoxelNodeTree	=	NULL;
			m_pBrick			=	NULL;
			m_pGenVoxelTree		=	NULL;
			m_pMipVoxelTree		=	NULL;
		}

		Air::U1 VoxelGenerator::Initialize( Render::Window* pMainWindow )
		{

			return true;
		}

		Air::U1 VoxelGenerator::Release()
		{
			return true;
		}

		void VoxelGenerator::Update( Renderable* pRenderable )
		{

		}

	}
}