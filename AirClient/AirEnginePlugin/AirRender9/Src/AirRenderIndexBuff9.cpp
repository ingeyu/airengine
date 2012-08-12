#include "AirRenderIndexBuff9.h"
//#include "AirRenderBuffPool9.h"
#include "AirRenderSystem9.h"

namespace Air{
	
	namespace	Client{
		namespace	Render{
	
			namespace	Index{
				Buff::Buff( CAString& strName,Info* pInfo )
					:	Buffer(strName,pInfo){
					m_pBuffer	=	NULL;
				}
	
				U1 Buff::Destroy( ){
					SAF_R(m_pBuffer);
					SAF_DA(m_Info.InitData);
					return true;
				}
				void* Buff::GetBuffer()
				{
 					if(m_pBuffer==NULL){
						System*	pSys	=	static_cast<System*>(m_pFactoryMgr);

						D3DFORMAT	fmt		=	(	GetElementSize()	==	4				)?D3DFMT_INDEX32	:D3DFMT_INDEX16;
						D3DPOOL		pool	=	(	m_Info.usage		==	enUSAGE_DYNAMIC	)?D3DPOOL_DEFAULT	:D3DPOOL_MANAGED;
						DWORD		dwUsage	=	(	m_Info.usage		==	enUSAGE_DYNAMIC	)?D3DUSAGE_DYNAMIC	:0;

						HRESULT	hr	=	pSys->GetDevice()->CreateIndexBuffer(GetBufferSize(),dwUsage,fmt,pool,&m_pBuffer,NULL);
						
					}
					if(!m_bDirty)
						return	m_pBuffer;
					
					if(m_Info.InitData!=NULL){
						void*	pDest	=	NULL;
						enumBufferFillState	state	=	enBFS_OK;
						HRESULT	hr	=	m_pBuffer->Lock(0,GetBufferSize(),(void**)&pDest,D3DLOCK_DISCARD);
						if(hr == S_OK){
							memcpy(pDest,m_Info.InitData,GetBufferSize());
							m_pBuffer->Unlock();
							SAF_DA(m_Info.InitData);
							m_bDirty	=	false;
							return	m_pBuffer;
						}

					}else	if(m_Info.pCB!=NULL){
						if(m_Info.pCB->IsLoad(this)){
							void*	pOutBuffer		=	NULL;
							U32		uiBufferSize	=	GetBufferSize();
							HRESULT	hr	=	m_pBuffer->Lock(0,uiBufferSize,(void**)&pOutBuffer,D3DLOCK_DISCARD);
							if(SUCCEEDED(hr)){
								m_Info.pCB->OnFill(pOutBuffer,uiBufferSize,this);
								m_pBuffer->Unlock();
								m_bDirty	=	false;
								return	m_pBuffer;
							}
						}
					}
					return	NULL;
				}
			}
	
		}
	}
};