// #include "AirRenderLine.h"
// #include "AirRenderGlobal.h"
// 
// namespace	Client{
// 	namespace	Render{
// 
// 
// 		Line::Line( AString& strName,Info* pInfo ):Product(strName){
// 			
// 		}
// 
// 		U1 Line::Create(){
// 			//LPD3DXLINE	pLine	=	NULL;
// 			HRESULT		hr		=	S_OK;
// 			hr	=	D3DXCreateLine(GetGlobal().m_pDevice,&m_pLine);
// 			if(FAILED(hr)){
// 				return	false;
// 			}
// 			return	true;
// 		}
// 
// 		U1 Line::Destroy(){
// 			SAFE_RELEASE(m_pLine)
// 			return	true;
// 		}
// 
// 		U1 Line::OnLostDevice(){
// 			return	DirectXOnLostDevice<LPD3DXLINE>();
// 		}
// 
// 		U1 Line::OnResetDevice(){
// 			return	DirectXOnResetDevice<LPD3DXLINE>();
// 		}
// 
// 		void Line::Render(){
// 			if(m_Info.m_LineArray.empty())
// 				return;
// 			m_pLine->Begin();
// 			m_pLine->DrawTransform((D3DXVECTOR3*)&m_Info.m_LineArray[0].vSrc,m_Info.m_LineArray.size(),(D3DXMATRIX*)&GetGlobalSetting().m_ShaderParam.m_matWorldViewProj,m_Info.uiColor);
// 			m_pLine->End();
// 		}
// 
// 		void Line::SetColor( Real r,Real g,Real	b ){
// 			m_Info.uiColor	=	0xFF000000	|	(UInt)(r*255)<<16	|	(UInt)(g*255)<<8	|	(UInt)(b*255);
// 		}
// 
// 		void Line::SetWidth( Real fWidth ){
// 			m_Info.fWidth	=	fWidth;
// 			m_pLine->SetWidth(fWidth);
// 		}
// 
// 		void Line::SetLineArray( LineArray& lArray ){
// 
// 		}
// 	}
// }