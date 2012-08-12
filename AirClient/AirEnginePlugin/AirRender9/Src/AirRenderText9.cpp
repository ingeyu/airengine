#include "AirRenderText9.h"
#include "AirRenderGlobal9.h"
namespace Air{
	
	namespace	Client{
		namespace	Render{
	
	
			Text::Text( CAString& strName,Info* pInfo )	:Product(strName){
				m_Info			=	*pInfo;
				m_Pool			=	POOL_MANAGED;
				m_Rect.left		=	0;
				m_Rect.top		=	0;
				m_Rect.right	=	500;
				m_Rect.bottom	=	500;//, 0, 100, 100};
				m_Color			=	0xDDDDDDDD;
			}
	
			Text::~Text(){
	
			}
	
			U1 Text::Create( ){
	
				DxFont*	pFont	=	NULL;
				//
				// Create an ID3DXFont based on 'lf'.
				//
				if(FAILED(D3DXCreateFontIndirectA(GetGlobal().m_pDevice, (DxFontDesc*)&m_Info, &pFont))){
	
					return false;
				}
	
				m_pObject	=	pFont;
	
				return true;
			}
	
			U1 Text::Destroy( ){
				return	DirectXDestroy<DxFont*>();
			}
	
	
			U1 Text::OnLostDevice(){
				return	DirectXOnLostDevice<DxFont*>();
			}
	
			U1 Text::OnResetDevice(){
				return	DirectXOnResetDevice<DxFont*>();
			}
	
			void Text::SetText( AString str ){
				m_strInfo	=	str;
			}
	
			void Text::SetColor( Float4 vColor ){
				m_Color	=	D3DCOLOR_COLORVALUE(vColor.x,vColor.y,vColor.z,vColor.w);
			}
	
			void Text::Render(){
	
				if(m_pObject!=NULL){
					DxFont*	pFont	=	(DxFont*)m_pObject;
					HRESULT	hr	=	pFont->DrawTextA(NULL,m_strInfo.c_str(),-1,&m_Rect,DT_TOP | DT_LEFT,m_Color);
					if(FAILED(hr)){
						RENDER_DEBUG_INFO(hr);
					}
				}
			}
			TextFactory::TextFactory(){
				m_strTypeName	=	"Text";
			}
	
			IProduct* TextFactory::NewProduct( CAString& strName,IFactoryParamList* lstParam /*= NULL*/ ){
				if(lstParam==NULL)
					return NULL;
				Text::Info*	pInfo	=	(Text::Info*)lstParam;
				Text*	pBuff	=	new	Text(strName,pInfo);
	
				return pBuff;
			}
		}
	}
};