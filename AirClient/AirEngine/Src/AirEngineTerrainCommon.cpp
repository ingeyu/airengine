#include "AirEngineTerrainCommon.h"
#include "AirEngineTerrainTitle.h"
#include "AirEngineSystem.h"
#include "AirEngineSceneNode.h"
namespace Air{
	
	namespace Engine{
	
		
			namespace	Terrain{
	
	
				Engine::Terrain::ID GetTitleIDByPosition( Real x,Real y ){
					SInt	iX			= x;
					SInt	iY			= y;
					ID	index;
					index.width	= iX/(Title::Size*Page::Size);
					index.height	= iY/(Title::Size*Page::Size);
					return index;
				}
	
				Engine::Terrain::ID GetPageIDByPosition( Real x,Real y ){
					SInt	iX	= x;
					SInt	iY	= y;
					ID index;
					index.width		= iX/(Page::Size);
					index.height	= iY/(Page::Size);
					return index;
				}
				AString IPage::ProductTypeName="IPage";
				IPage::IPage(AString strName,Info*	pInfo):Common::IProduct(strName){
					m_Info	=	*pInfo;
					//AChar	strPageName[MAX_NAME];
					//sprintf(strPageName,"%s\\Page_%d_%d\\",m_Info.strMapPath.c_str(),m_Info.uiID.height,m_Info.uiID.width);
				};
	
				Engine::Terrain::ID IPage::GetID(){
					return m_Info.uiID;
				}
				U1 IPage::Destroy(){
// 					if(m_DrawBuff.m_pXObject!=NULL){
// 						Render::System::GetSingleton()->DestroyProduct(m_DrawBuff.m_pXObject);
// 						m_DrawBuff.m_pXObject	=	NULL;
// 					}
// 					if(m_pMaterial!=NULL){
// 						EngineSystem::GetSingleton()->DestroyProduct(m_pMaterial);
// 						m_pMaterial	=	NULL;
// 					}
					m_pObject	=	NULL;
					return	true;
				}
	
				U1 IPage::Create(){
	
					AString	strPageMeshName		=	m_strProductName	+	"Page.x";	
					//创建网格
// 					m_DrawBuff.m_pXObject		=	Render::System::GetSingleton()->CreateProduct<Client::Render::IXObject*>(strPageMeshName,AString("XObject"));
// 					if(m_DrawBuff.m_pXObject==NULL){
// 						m_DrawBuff.m_pXObject	=	Render::System::GetSingleton()->CreateProduct<Client::Render::IXObject*>(AString("Model\\Page.X"),AString("XObject"));
// 					}				
					AString	strPageMaterialName	=	m_strProductName	+	"Page.Material";
					//创建材质
// 					m_pMaterial					=	EngineSystem::GetSingleton()->CreateProduct<Client::Render::IMaterial*>(strPageMaterialName,AString("Material"));
// 					if(m_pMaterial==NULL){
// 						m_pMaterial	=	EngineSystem::GetSingleton()->CreateProduct<Client::Render::IMaterial*>(AString("Material\\Page.Material"),AString("Material"));
// 					}
	
// 					m_Bound		=	m_DrawBuff.m_pXObject->ComputeBoundBox();
// 					m_DrawBuff.m_DrawOption.m_DrawFuncType	=	Render::Draw::FUNC_TYPE_DS;
					//m_pObject	=	(UInt*)m_DrawBuff.m_pXObject;
	
					return true;
				}
	
				void IPage::Update(){
					
				}
	
				IPage::~IPage(){
	
				}
	
				Float3 IPage::BrushHeight(){
// 					//获取当前鼠标所在位置的射线
// 					Ray	ray	=	GetGlobalSetting().GetCursorPostionRay();
// 					//将射线转换到本地空间
// 					Float3	pos		=	ray.getOrigin();
// 					//Float3	lookat	=	pos	+	ray.getDirection();
// 	
// 					//ray.setOrigin(m_ResultMatrix*pos);
// 					//ray.setDirection(m_ResultMatrix*lookat	-	ray.getOrigin());
// 					//计算是否相交,相交则返回交点数据
// 					Render::InterSectResult result;
// 					if(m_DrawBuff.m_pXObject->Intersect(ray,&result)){
// 	#ifdef	_DEBUG
// 						AChar	str[MAX_NAME];
// 						sprintf_s(str,MAX_NAME,"distance=%f face=%d ",result.fDist,result.uiFace);
// 						::OutputDebugStringA(str);
// 						::OutputDebugStringA("Hit	Terrain\n");
// 	#endif
// 					}else{
// 	#ifdef	_DEBUG
// 						::OutputDebugStringA("Hit	Nothing\n");
// 	#endif
// 					}
// 	
// 					Float3	v	=	ray.getPoint(result.fDist);
	
					return Float3(0,0,0);
				}

			}
		
	};
};