#include "AirRenderVertexBuff9.h"
//#include "AirRenderBuffPool9.h"
#include "AirRenderVertexDeclarationManager9.h"
#include "AirRenderGlobal9.h"


namespace Air{
	
	namespace	Client{
		namespace	Render{
			namespace	Vertex{
				
	
				Buff9::Buff9( CAString& strName,Info* pInfo )
					:Buffer(strName,pInfo){
					//m_iStart	=	-1;
				}
	
	
				U1 Buff9::Destroy( ){
					//BufferPoolManager::GetSingleton()->DestroyBuffer(m_Info.type,m_iStart);
					SAFE_RELEASE(m_pBuffer);
					SAF_DA(m_Info.InitData);
					return	true;
				}

				void* Buff9::GetBuffer(){
					if(m_pBuffer==NULL){
						U32		uiLength	=	GetBufferSize();
						if(uiLength==0)
							return	false;

						D3DPOOL		pool	=	(	m_Info.usage		==	enUSAGE_DYNAMIC	)?D3DPOOL_DEFAULT	:D3DPOOL_MANAGED;
						DWORD		dwUsage	=	(	m_Info.usage		==	enUSAGE_DYNAMIC	)?D3DUSAGE_DYNAMIC	:0;


						GetGlobal().m_pDevice->CreateVertexBuffer(	uiLength,
																	dwUsage,
																	0,
																	pool,
																	&m_pBuffer,
																	NULL);
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
					}else if(m_Info.pCB!=NULL){
						if(m_Info.pCB->IsLoad(this)){
							void*	pDest	=	NULL;
							enumBufferFillState	state	=	enBFS_OK;
							HRESULT	hr	=	m_pBuffer->Lock(0,GetBufferSize(),(void**)&pDest,D3DLOCK_DISCARD);
							if(hr == S_OK){
								state	=	m_Info.pCB->OnFill(pDest,GetBufferSize(),this);
								m_pBuffer->Unlock();
								m_bDirty	=	false;
								return	m_pBuffer;
							}
						}
					}
					
					return	NULL;
				}
	
				Declare9::Declare9( CAString& strName,Info* pInfo )
					:	IDeclare(strName,pInfo){
					m_pDeclare	=	NULL;
				}
	
				void* Declare9::GetDeclare(){
					if(m_pDeclare==NULL){
						m_pDeclare	=	VertexDeclarationManager::GetSingleton()->CreateVD(m_Info.m_vectorElement);
						if (m_pDeclare!=NULL){
							m_Info.m_vectorElement	=	ElementVector();
						}
					}
					return	m_pDeclare;
				}

				Declare9Factory::Declare9Factory(){
					m_strTypeName	=	"VertexDeclare";
				}
	
				IProduct* Declare9Factory::NewProduct( CAString& strName,IFactoryParamList* lstParam /*= NULL*/ ){
					if(lstParam==NULL)
						return NULL;
					Declare9::Info*	pInfo	=	(Declare9::Info*)lstParam;
					Declare9*		pBuff	=	new	Declare9(strName,pInfo);
	
					return pBuff;		
				}
			}
		}
	}
};