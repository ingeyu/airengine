#include "AirPipelineVoxelGen.h"

namespace	Air{
	namespace	Client{
		struct Voxel{
			Voxel(){
				uiMask		=	0;
				uiOffset	=	0;
				uiColor		=	0;
			};
			U32 uiMask:8;
			U32	uiOffset:24;
			U32	uiColor;
		};


		struct VoxelTree{
			VoxelTree(){
				vecVoxel.resize(1);
			};
			U32	Add(const Float3& vPos,U32	uiColor,Voxel* pVoxle	=	NULL,BoundingBox*	pBoundingBox=NULL,int iLevel	=	0){

				if(iLevel	==	0){
					pVoxle	=	&vecVoxel[0];
				}
				if(iLevel>15){
					if(pVoxle->uiColor==0)
						pVoxle->uiColor	=	uiColor;
					return iLevel;
				}
				if(pBoundingBox==NULL)
					pBoundingBox	=	&m_Bound;
				Float3 vSize	=	pBoundingBox->GetHalfSize();
				Float3 vCenter	=	pBoundingBox->GetCenter();
				int x	=	vPos.x > vCenter.x;
				int y	=	vPos.y > vCenter.y;
				int z	=	vPos.z > vCenter.z;
				int idx	=	(x<<2) | (y <<1) | z;

				if(pVoxle->uiMask==0){
					pVoxle->uiOffset	=	vecVoxel.size();
					pVoxle->uiMask|=idx;
					int Offset	=	pVoxle->uiOffset;
					pVoxle=NULL;
					vecVoxel.resize(Offset + 8);
					pVoxle	=	&vecVoxel[Offset+idx];
				}else{
					pVoxle->uiMask|=idx;
					int Offset	=	pVoxle->uiOffset;
					pVoxle	=	&vecVoxel[Offset+idx];
				}

				Float3 vHalfSize	=	vSize*0.5f;
				Float3 vMin			=	(vCenter-vSize)+vSize*Float3(x,y,z);

				BoundingBox box(vMin,vMin+vSize);
				Add(vPos,uiColor,pVoxle,&box,iLevel+1);

			};
			std::vector<Voxel>	vecVoxel;;
			BoundingBox			m_Bound;
		};

		VoxelGenerator::VoxelGenerator()
		{
			m_pVoxelNodeTree	=	NULL;
			m_pBrick			=	NULL;
			m_pGenVoxelTree		=	NULL;
			m_pMipVoxelTree		=	NULL;
		}

		Air::U1 VoxelGenerator::Initialize( Render::Window* pMainWindow )
		{
			Render::Buffer::Info info;
			info.SetStructureBuffer(1048576,sizeof(Voxel));
			info.SetViewFlag(enVF_SRV|enVF_UAV|enVF_Counter);
			m_pVoxelNodeTree	=	RenderSystem::GetSingleton()->CreateProduct<Render::Buffer*>("SVO_Counter","Buffer",&info);
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