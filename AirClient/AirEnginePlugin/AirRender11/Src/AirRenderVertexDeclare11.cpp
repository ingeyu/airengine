#include "AirRenderVertexDeclare11.h"
#include "AirRenderDevice11.h"

namespace	Air{
	namespace	Client{
		extern	Render::Device11*	pDevice;
		namespace	Render{

			static AString	strSemanticName[]={
				"POSITION",
				"BLENDWEIGHT",
				"BLENDINDICES",
				"NORMAL",				
				"PSIZE",
				"TEXCOORD",				
				"TANGENT",
				"BINORMAL",
				"TESSFACTOR",
				"POSITIONT",
				"COLOR",
				"FOG",
				"DEPTH",
				"SAMPLE",
				"CUSTOM"
			};


			VertexDeclare11::VertexDeclare11( CAString& strName,Info* pInfo ):Vertex::IDeclare(strName,pInfo)
			{
				m_pDeclare	=	NULL;
			}

			void* VertexDeclare11::GetDeclare()
			{
				if(m_pDeclare==NULL){
					DxDevice*	pDxDevice	=	(DxDevice*)pDevice->GetDevice();

					std::vector<D3D11_INPUT_ELEMENT_DESC>	vecDesc;
					U32	uiSize	=	m_Info.m_vectorElement.size();
					vecDesc.resize(uiSize);
					memcpy(&vecDesc[0],&m_Info.m_vectorElement[0],sizeof(DeclareElement)*uiSize);
					for(U32 i=0;i<uiSize;i++){
						vecDesc[i].SemanticName	=	strSemanticName[m_Info.m_vectorElement[i].SemanticName].c_str();
					}

					void*	pBinaryCode			=	NULL;
					U32		uiBinaryCodeSize	=	0;
					pDevice->GetShader(enVS)->GetBinaryCode(pBinaryCode,uiBinaryCodeSize);
					pDxDevice->CreateInputLayout(&vecDesc[0],uiSize,pBinaryCode,uiBinaryCodeSize,&m_pDeclare);

				}
				return	m_pDeclare;
			}

		}
	}
}