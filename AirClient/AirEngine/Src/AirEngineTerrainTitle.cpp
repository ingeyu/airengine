#include "AirEngineTerrainTitle.h"

namespace Air{
	
	namespace	Engine{
	
		
	
			namespace	Terrain{
	
				SInt	Title::Size	= 3;
				Title::Title(){
					m_pPageArray	= NULL;
	
				}
	
				Title::~Title(){
	
				}
	
				bool Title::GetHeight( Real x,Real y, Real* z ){
					ID index = GetPageIDByPosition(x,y);
	
					if(	index.width	>=	Size	||
						index.height>=	Size	||
						index.width	<	0		||
						index.height<	0){
							return	false;
					}
	
					Page&	pPage	= m_pPageArray[index.height*Size	+ index.width];
					return	pPage.GetHeight(x	-	(Real)index.width*Page::Size,
											y	-	(Real)index.height*Page::Size,
											z);
	
				}
	
				U1 Title::Load(){
	// 				if(m_bIsLoad)
	// 					return true;
	// 				m_pPageArray	= new	Page[Size*Size];
	// 
	// 				for(SInt j=0;j<Size;j++){
	// 					for(SInt i=0;i<Size;i++){
	// 						Page& pPage = m_pPageArray[j*Size + i];
	// 						//设置为全局的ID
	// 						pPage.SetInfo(m_ParentInfo,ID(i+m_uiID.width*Size,j+m_uiID.height*Size));
	// 					}
	// 				}
	// 
	// 
	// 				m_bIsLoad	= true;
					return true;
				}
	
				U1 Title::UnLoad(){
					SAF_DA(m_pPageArray);
					//m_bIsLoad	=	false;
					return true;
				}
	
				U1 Title::IsLoad(){
					if(m_pPageArray==NULL)
						return false;
					for(SInt j=0;j<Size;j++){
						for(SInt i=0;i<Size;i++){
	// 						if(m_pPageArray[j*Size + i].IsLoad()){
	// 							return true;
	// 						}
						}
					}
					return false;
				}	
	
				void Title::Updata(){
	// 				//是否为当前地形块
	// 				if(m_ParentInfo->CurrentTitleID.index	==	m_uiID.index){
	// 					Float3	pos	=	GetGlobalSetting().m_vCurrentPosition;
	// 					//更新地形页ID(获取的是全局ID  不是相对于Title的ID)
	// 					m_ParentInfo->CurrentPageID	=	GetPageIDByPosition(pos.x,pos.z);
	// 				}
	
	
	// 				CheckIsInView(GetGlobalSetting().m_lstCullPlane);
	// 				if(!IsInView())
	// 					return; 
	// 				if(!IsLoad()){
	// 					Load();
	// 				}
	// 				//更新页
	// 				for(UInt j=0;j<Size;j++){
	// 					for(UInt i=0;i<Size;i++){
	// 						Page& page	=	m_pPageArray[j*Size + i];
	// 						if(page.IsLoad()){
	// 							page.Updata();
	// 						}
	// 					}
	// 				}
	
	
				}
	
				void Title::Render(){
					if(m_pPageArray==NULL)
						return;
					for(SInt j=0;j<Size;j++){
						for(SInt i=0;i<Size;i++){
	// 						Page& page	=	m_pPageArray[j*Size + i];
	// 						if(page.IsVisiable() && page.IsLoad() && page.IsInView()){
	// 							page.Render();
	// 						}
						}
					}
				}
			}
		
	}
};