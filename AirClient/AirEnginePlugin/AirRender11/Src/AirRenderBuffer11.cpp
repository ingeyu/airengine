#include "AirRenderBuffer11.h"
#include "AirRenderDevice11.h"


namespace Air{
	
	namespace	Engine{
		extern	Render::Device11*	pDevice;
		namespace	Render{

				
	

			Buffer11::Buffer11( CAString& strName,Info* pInfo ):Buffer(strName,pInfo)
			{
				m_pBuffer		=	NULL;
				m_pBufferSRV	=	NULL;
				m_pBufferUAV	=	NULL;
			}

			Air::U1 Buffer11::Destroy()
			{
				SAFE_RELEASE(m_pBufferSRV);
				SAFE_RELEASE(m_pBufferUAV);
				SAFE_RELEASE(m_pBuffer);
				//SAF_DA(m_Info.InitData);
				return	true;
			}

			void* Buffer11::GetBuffer()
			{
				//if(m_Info.pCB!=NULL){
				//	if(m_Info.pCB->IsLoad(this)){
				//		//m_Info.pCB->OnFill()
				//	}
				//}
				//if(IsDirty()	&&	m_pBuffer!=NULL	&&	m_Info.InitData!=NULL){
				//	DxContext*	pContext	=	(DxContext*)pDevice->GetContext();
				//	pContext->UpdateSubresource(m_pBuffer,0,0,m_Info.InitData,0,0);
				//	//SAF_DA(m_Info.InitData);
				//	m_bDirty	=	false;
				//}

				return	m_pBuffer;
			}

			void* Buffer11::GetSRV()
			{
				return	m_pBufferSRV;
			}

			void* Buffer11::GetUAV()
			{
				return	m_pBufferUAV;
			}

			Air::U1 Buffer11::UpdateData( void* pData )
			{
				if(m_pBuffer!=NULL	&&	pData!=NULL){
					DxContext*	pContext	=	(DxContext*)pDevice->GetContext();
					pContext->UpdateSubresource(m_pBuffer,0,0,pData,0,0);
				}
				return	true;
			}
			void Buffer11::CopyBufferTo( Buffer* pDest )
			{
				if(pDest==NULL)
					return;
				DxContext*	pContext	=	(DxContext*)(pDevice->GetContext());
				ID3D11Resource*	pSrcResource	=	(ID3D11Resource*)GetBuffer();
				ID3D11Resource*	pDestResource	=	(ID3D11Resource*)pDest->GetBuffer();
				if(pSrcResource	==	NULL	||	pDestResource	==	NULL)
					return;
				pContext->CopyResource(pDestResource,pSrcResource);
			}

			Air::U1 Buffer11::Write( U32 uiOffset,U32 uiSize,const void* pSourceData )
			{
				DxContext*	pContext	=	(DxContext*)(pDevice->GetContext());
				ID3D11Resource*	pResource	=	(ID3D11Resource*)GetBuffer();
				D3D11_MAPPED_SUBRESOURCE res;
				
				HRESULT	hr	=	pContext->Map(pResource,0,D3D11_MAP_WRITE_DISCARD,0,&res);
				if(SUCCEEDED(hr)){
					U8*	pDst	=	(U8*)res.pData;
					memcpy(&pDst[uiOffset],pSourceData,uiSize);
					pContext->Unmap(pResource,0);
				}
				return	true;
			}

			Air::U1 Buffer11::Create()
			{
				if(m_pBuffer==NULL){
					DxDevice*	pDxDevice	=	(DxDevice*)pDevice->GetDevice();
					D3D11_BUFFER_DESC	desc;
					MemoryZero(desc);
					switch(m_Info.type){
					case enBT_VB:{
						desc.BindFlags	|=	D3D11_BIND_VERTEX_BUFFER;
						break;}
					case enBT_IB:{
						desc.BindFlags	|=	D3D11_BIND_INDEX_BUFFER;
						break;}
					case enBT_CB:{
						desc.BindFlags	|=	D3D11_BIND_CONSTANT_BUFFER;
						break;}
					case enBT_SB:{
						if(m_Info.Flag	&	enVF_SRV){
							desc.BindFlags	|=	D3D11_BIND_SHADER_RESOURCE;
						}
						if(m_Info.Flag	&	enVF_UAV){
							desc.BindFlags	|=	D3D11_BIND_UNORDERED_ACCESS;
						}
						desc.MiscFlags	|=	D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
						desc.StructureByteStride	=	m_Info.uiElementSize;
						break;}
					case enBT_BAB:{
						if(m_Info.Flag	&	enVF_SRV){
							desc.BindFlags	|=	D3D11_BIND_SHADER_RESOURCE;
						}
						if(m_Info.Flag	&	enVF_UAV){
							desc.BindFlags	|=	D3D11_BIND_UNORDERED_ACCESS;
						}
						//The UAV bound to this resource must have been created with the D3D11_BUFFER_UAV_FLAG_RAW.
						desc.MiscFlags	|=	D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS;
						desc.StructureByteStride	=	m_Info.uiElementSize;
						break;}
					case enBT_SMB:{
						desc.Usage			=	D3D11_USAGE_STAGING;
						desc.CPUAccessFlags	=	D3D11_CPU_ACCESS_WRITE|D3D11_CPU_ACCESS_READ;
						break;}
					}
					desc.ByteWidth	=	m_Info.uiElementCount*m_Info.uiElementSize;
					if(m_Info.usage	==	enUSAGE_DYNAMIC){
						desc.Usage			=	D3D11_USAGE_DYNAMIC;
						desc.CPUAccessFlags	=	D3D11_CPU_ACCESS_WRITE;
					}

					if(m_Info.InitData!=NULL){
					 	D3D11_SUBRESOURCE_DATA	data;
					 	data.pSysMem			=	m_Info.InitData;
					 	data.SysMemPitch		=	0;
					 	data.SysMemSlicePitch	=	0;
					 	pDxDevice->CreateBuffer(&desc,&data,&m_pBuffer);
					}
					else
					{
						pDxDevice->CreateBuffer(&desc,NULL,&m_pBuffer);
					}

					if(m_Info.Flag	&	enVF_SRV){
						D3D11_SHADER_RESOURCE_VIEW_DESC	srvDesc;
						MemoryZero(srvDesc);
						srvDesc.Buffer.NumElements	=	m_Info.uiElementCount;
						srvDesc.ViewDimension		=	D3D11_SRV_DIMENSION_BUFFER;
						if(m_Info.type	==	enBT_BAB){
							srvDesc.Format				=	DXGI_FORMAT_R32_UINT;
						}else{
							srvDesc.Format				=	DXGI_FORMAT_UNKNOWN;
						}

						pDxDevice->CreateShaderResourceView( m_pBuffer, &srvDesc, &m_pBufferSRV );
					}

					if(m_Info.Flag	&	enVF_UAV){
						D3D11_UNORDERED_ACCESS_VIEW_DESC	uavDesc;
						MemoryZero(uavDesc);
						uavDesc.Buffer.NumElements	=	m_Info.uiElementCount;
						uavDesc.ViewDimension		=	D3D11_UAV_DIMENSION_BUFFER;
						//The UAV format bound to RWByteAddressBuffer needs to be created with the DXGI_FORMAT_R32_TYPELESS format.
						if(m_Info.type	==	enBT_BAB){
							uavDesc.Format				=	DXGI_FORMAT_R32_TYPELESS;
							uavDesc.Buffer.Flags		|=	D3D11_BUFFER_UAV_FLAG_RAW;
						}else if(m_Info.type	==	enBT_SB){
							uavDesc.Format				=	DXGI_FORMAT_UNKNOWN;
						}
						if(m_Info.Flag	&	enVF_Counter){
							uavDesc.Buffer.Flags		=	D3D11_BUFFER_UAV_FLAG_COUNTER;
						}

						HRESULT	hr	=	pDxDevice->CreateUnorderedAccessView( m_pBuffer, &uavDesc, &m_pBufferUAV );
						if(hr!=S_OK){
							return false;
						}
					}
				}
				return	true;
			}

			Air::U1 Buffer11::Read( U32 uiOffset,U32 uiSize,void* pData )
			{

				DxContext*	pContext	=	(DxContext*)(pDevice->GetContext());
				ID3D11Resource*	pResource	=	(ID3D11Resource*)GetBuffer();
				D3D11_MAPPED_SUBRESOURCE res;

				HRESULT	hr	=	pContext->Map(pResource,0,D3D11_MAP_READ,0,&res);
				if(SUCCEEDED(hr)){
					U8*	pDst	=	(U8*)res.pData;
					memcpy(pData,&pDst[uiOffset],uiSize);
					pContext->Unmap(pResource,0);
				}
				return true;
			}

		}
	}
};