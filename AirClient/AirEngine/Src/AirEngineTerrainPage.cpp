#include "AirEngineTerrainPage.h"
#include "AirCommonFile.h"
#include "AirCommonIniFile.h"
#include "AirRenderSystem.h"

namespace Air{
	
	namespace	Client{
		
			namespace	Terrain{
	
				SInt	Page::Size	= 32;
	
	
				Page::Page(){
					//_ZERO(m_ParentInfo);
					m_pMaterial		=	NULL;
					m_VertexBuff	=	NULL;
					m_Height		=	new	U8[(Size+1)*(Size+1)];
	
	
				}
	
				Page::~Page(){
					SAF_DA(m_Height);
	
				}
	
				U1 Page::GetHeight( Real x,Real y,Real* z ){
					SInt	iX	=	x,iY	=	y;
					if(iX	<	0)iX	=	0;
					if(iY	<	0)iY	=	0;
					if(iX	>	Size)	iX	=	Size	+	1;
					if(iY	>	Size)	iY	=	Size	+	1;
					if(z!=NULL)
						*z	=	(Real)(UInt)(m_Height[iX+iY*(Size+1)]);
					return true;
				}
				void Page::Updata(){
	// 				Real fDistance	=	0;
	// 				Real*	pLodDis	=	GetGlobalSetting().m_LodDistance;
	// 				//计算LOD
	// 				if(fDistance	>	pLodDis[3]){
	// 					m_uiLod	=	4;
	// 					m_bInView	=	false;
	// 					return;
	// 					SetVisiable(false);
	// 				}else if(fDistance	>	pLodDis[2]){
	// 					m_uiLod	=	3;
	// 				}else if(fDistance	>	pLodDis[1]){
	// 					m_uiLod	=	2;
	// 				}else if(fDistance	>	pLodDis[0]){
	// 					m_uiLod	=	1;
	// 				}else{
	// 					m_uiLod	=	0;
	// 				}
	// 				if(!m_bIsLoad){
	// 					Load();
	// 				}
	// 				
	// 				CheckIsInView(GetGlobalSetting().m_lstCullPlane);
	// 				if(!IsInView())
	// 					return;
	
	// 				m_DrawBuff.m_pIndexBuff		=	m_ParentInfo->pIndexBuff;
	// 				m_DrawBuff.m_pVertexDeclare	=	m_ParentInfo->pVertexDeclare;
					
					
					//计算包围盒
					//GetBoundBox()
	
	
				};
	
				U1 Page::Load(){
	// 				if(m_bIsLoad)
	// 					return true;
	// 				AChar strPageName[MAX_NAME];
	// 				sprintf(strPageName,"%s/Page_%d_%d/",m_ParentInfo->strName,m_uiID.width,m_uiID.height);
	// 
	// 				Real fWidth		=	m_uiID.width*Size;
	// 				Real fHeight	=	m_uiID.height*Size;
	// 
	// 				m_Bound.SetMin(Float3(fWidth,		fHeight,		0.0f));
	// 				m_Bound.SetMax(Float3(fWidth+Size,	fHeight+Size,	0.0f));
	
					///CreateHeight(strPageName);
					//CreateMaterial(strPageName);
	
	/*				m_bIsLoad	=	true;*/
	
					return true;
				}
	
				U1 Page::UnLoad(){
	
					if(m_pMaterial!=NULL)
	 					Render::System::GetSingleton()->DestroyProduct(m_pMaterial);
					m_pMaterial	=	NULL;
	// 				if(m_DrawBuff.m_pVertexBuff!=NULL){
	// 					Render::System::GetSingleton()->DestroyProduct(m_DrawBuff.m_pVertexBuff);
	// 					m_DrawBuff.m_pVertexBuff	=	NULL;
	// 				}
	// 				m_DrawBuff.m_pIndexBuff		=	NULL;
	// 				m_DrawBuff.m_pVertexDeclare	=	NULL;
	
					return true;
				}		
				void Page::CreateHeight(AString strPageName){
	// 				AString	strPageHeightName	=	strPageName + "Page.raw";
	// 				File file(strPageHeightName);
	// 				file.Open();
	// 
	// 				File::Data*	pData	=	file.GetData();
	// 				U8*	pHeight	=	pData->GetBuff();
	// 				VertexBuff::Info info(32,(Size+1)*((Size+1)));
	// 				m_DrawBuff.m_pVertexBuff	=	Render::System::GetSingleton()->Create<VertexBuff*>(strPageHeightName,"VertexBuff",&info);
	// 
	// 				VertexBuff::PNTData*	pVertexBuff	=	NULL;
	// 				Client::Render::LockOption option(0,info.count*info.size,(void**)&pVertexBuff);
	// 				m_DrawBuff.m_pVertexBuff->Lock(option);
	// 				ComputeTerrain(pHeight,pVertexBuff);
	// 				m_DrawBuff.m_pVertexBuff->Unlock();
	// 
	// 				m_DrawBuff.m_DrawOption.m_uiBaseVertexIndex	=	0;
	// 				m_DrawBuff.m_DrawOption.m_uiVertexCount		=	(Size+1)*(Size+1);
	// 				m_DrawBuff.m_DrawOption.m_uiFaceCount		=	Size*Size*2;
	// 				m_DrawBuff.m_DrawOption.m_uiStartIndex		=	0;
				}
	
				void Page::CreateMaterial( AString strPageName ){
					m_pMaterial	=	Render::System::GetSingleton()->CreateProduct<Material*>(strPageName+"Page.Material",AString("Material"));
				}
	
				void Page::CreateObject( AString strPageName ){
					AString	strObjectName	=	strPageName	+	"Page.obj";
					File file(strObjectName);
					file.Open();
	
					IniFile	cfgfile;
					cfgfile.LoadFileFromMemory(file.GetData());
	
				}
	
				Float3 Page::ComputeNormal( Float4 vHeight ,Real	fScale	/*=	1.0f*/){
					Float3	normal;
	
					float h[4];
	
					h[0] = vHeight.x;//GetHeightFromHMapFast(X-1,Y,0);
	
					h[1] = vHeight.y;//GetHeightFromHMapFast(X+1,Y,0);
	
					h[2] = vHeight.z;//GetHeightFromHMapFast(X,Y-1,0);
	
					h[3] = vHeight.w;//GetHeightFromHMapFast(X,Y+1,0);
	
					float rot = atan2f((h[0]-h[1]),fScale);
	
					normal.x = sin(rot);
	
					normal.z = cos(rot);
	
					rot = atan2f((h[2]-h[3]),fScale);
	
					normal.y = sin(rot);
	
					normal.z += cos(rot);
	
					return normal;
	
				}
	
				void Page::ComputeTerrain( U8* pHeight,Render::P*	pVertexBuff){
					Real	fMaxHeight	=	0.0f,fMinHeight	=	0.0f;
					//读取高度图
	
	// 				for(UInt j=0;j<Size;j++)
	// 					for(UInt i=0;i<Size;i++){
	// 						VertexBuff::PNTData v;
	// 						//获取周围四个顶点高度
	// 						Float4	height;
	// 						GetHeight(i-1,j,&height.x);
	// 						GetHeight(i+1,j,&height.y);
	// 						GetHeight(i,j-1,&height.z);
	// 						GetHeight(i,j+1,&height.w);
	// 						//计算法线
	// 						Float3	normal	=	ComputeNormal(height);
	// 						v.fArray[0]	=	i	+	m_uiID.width*Size;
	// 						v.fArray[1] =	j	+	m_uiID.height*Size;
	// 						v.fArray[2]	=	pHeight[j*Size+i];
	// 						v.fArray[3] =	normal.x;
	// 						v.fArray[4] =	normal.y;
	// 						v.fArray[5] =	normal.z;
	// 						v.fArray[6] =	(Real)i/Size;
	// 						v.fArray[7] =	(Real)j/Size;
	// 
	// 						
	// 
	// 						pVertexBuff[j*Size+i]	=	v;
	// 						
	// 						//计算包围盒的最高点和最低点
	// 						if(pHeight[j*Size+i]	>	fMaxHeight)fMaxHeight	=	pHeight[j*Size+i];
	// 						if(pHeight[j*Size+i]	<	fMinHeight)fMinHeight	=	pHeight[j*Size+i];
	// 					
	// 					}
	// 
	// 					//更新包围盒
	// 					m_Bound.SetMaxHeight(fMaxHeight);
	// 					m_Bound.SetMinHeight(fMinHeight);
				}
			}
	
	
		
	}
};