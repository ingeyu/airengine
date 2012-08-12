#include "AirRenderVertexDeclarationManager9.h"
#include "AirRenderGlobal9.h"

namespace	Air{
	namespace	Client{
		namespace	Render{


			VertexDeclarationManager::~VertexDeclarationManager(){
				DestroyAllVD();
			}

			IDirect3DVertexDeclaration9* VertexDeclarationManager::CreateVD(VDElementVector&	vecElement){
				UInt uiSize	=	m_vecVD_Data.size();

				for(UInt i=0;i<uiSize;i++){
					VD_Data& data	=	m_vecVD_Data[i];
					UInt uiEArraySize	=	min(vecElement.size(),data.vecElement.size())*sizeof(D3DVERTEXELEMENT9);
					if(Common::Memcmp4(&data.vecElement[0],&vecElement[0],uiEArraySize)){
						return	data.pVD;
					}
				}
				VD_Data	vddata;
				

				DxResult	hr	=	GetGlobal().m_pDevice->CreateVertexDeclaration((DxElement*)&vecElement[0],&vddata.pVD);
				if(FAILED(hr)){
					return NULL;
				}
				
				m_vecVD_Data.push_back(vddata);
				VD_Data&	data	=	m_vecVD_Data[m_vecVD_Data.size()-1];
				data.vecElement	=	vecElement;

				return	data.pVD;
			}

			void VertexDeclarationManager::DestroyAllVD(){
				UInt uiSize	=	m_vecVD_Data.size();

				for(UInt i=0;i<uiSize;i++){
					VD_Data& data	=	m_vecVD_Data[i];
					SAFE_RELEASE(data.pVD);
				}
				m_vecVD_Data	=	VD_DataVector();
			}
		}
	}
}