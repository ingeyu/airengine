#include "stdafx.h"
#include "EngineRenderState.h"

const TCHAR*	strEnable[]={
	_T("FALSE"),
	_T("TRUE")
};
const TCHAR*	strStencilOP[]={
	_T("enSOP_UNKNOWN   "),
	_T("enSOP_KEEP      "),
	_T("enSOP_ZERO      "),
	_T("enSOP_REPLACE   "),
	_T("enSOP_INCR_SAT  "),
	_T("enSOP_DECR_SAT  "),
	_T("enSOP_INVERT    "),
	_T("enSOP_INCR      "),
	_T("enSOP_DECR      "),
};

static const int strFillModeCount = 4;
static const TCHAR* strFillMode[strFillModeCount] = {
	_T("enFM_NONE"),
	_T("enFM_POINT"),
	_T("enFM_WIREFRAME"),
	_T("enFM_SOILD")
};

static const int strCullModeCount = 3;
static const TCHAR* strCullMode[strCullModeCount] = {
	_T("enCM_NONE"),
	_T("enCM_CW"),
	_T("enCM_CCW")
};
static const int strCompareCount = 9;
static const TCHAR* strCompare[strCompareCount] = {
	_T("enC_UNKNOWN        "),
	_T("enC_NEVER          "),
	_T("enC_LESS           "),
	_T("enC_EQUAL          "),
	_T("enC_LESS_EQUAL     "),
	_T("enC_GREATER        "),
	_T("enC_NOT_EQUAL      "),
	_T("enC_GREATER_EQUAL  "),
	_T("enC_ALWAYS         "),
};

static TCHAR*	strRTB[]={
	_T("RENDER_TARGET_BLEND<0>"),
	_T("RENDER_TARGET_BLEND<1>"),
	_T("RENDER_TARGET_BLEND<2>"),
	_T("RENDER_TARGET_BLEND<3>"),
	_T("RENDER_TARGET_BLEND<4>"),
	_T("RENDER_TARGET_BLEND<5>"),
	_T("RENDER_TARGET_BLEND<6>"),
	_T("RENDER_TARGET_BLEND<7>"),
};
const TCHAR*	strBlend[]={
	_T("enB_UNKNOWN			   "),
	_T("enB_ZERO               "),
	_T("enB_ONE                "),
	_T("enB_SRC_COLOR          "),
	_T("enB_INV_SRC_COLOR      "),
	_T("enB_SRC_ALPHA          "),
	_T("enB_INV_SRC_ALPHA      "),
	_T("enB_DEST_ALPHA         "),
	_T("enB_INV_DEST_ALPHA     "),
	_T("enB_DEST_COLOR         "),
	_T("enB_INV_DEST_COLOR     "),
	_T("enB_SRC_ALPHA_SAT      "),
	_T("enB_UNKNOWN			   "),
	_T("enB_UNKNOWN			   "),
	_T("enB_BLEND_FACTOR       "),
	_T("enB_INV_BLEND_FACTOR   "),
	_T("enB_SRC1_COLOR         "),
	_T("enB_INV_SRC1_COLOR     "),
	_T("enB_SRC1_ALPHA         "),
	_T("enB_INV_SRC1_ALPHA     "),
};
const TCHAR*	strBlendOP[]={
	_T("enBOP_UNKNOWN		 "),
	_T("enBOP_ADD            "),
	_T("enBOP_SUBTRACT       "),
	_T("enBOP_REV_SUBTRACT   "),
	_T("enBOP_MIN            "),
	_T("enBOP_MAX            ") 

};

RenderState::RenderState( const TCHAR* strName,TreeObj* pParent ,enumTreeObjType	t):TreeObj(strName,pParent,pParent->GetTree(),t)
{
	m_pState=NULL;
	switch(m_Type){
		case enTOT_RState:{
			info.type	=	Air::Client::enRST_RS;
			break;}
		case enTOT_DState:{
			info.type	=	Air::Client::enRST_DS;
			break;}
		case enTOT_BState:{
			info.type	=	Air::Client::enRST_BS;
			break;}
		case enTOT_SState:{
			info.type	=	Air::Client::enRST_SS;
			break;}
	}
}

bool RenderState::Create()
{
	m_pState	=	Air::Client::Render::System::GetSingleton()->CreateProduct<Air::Client::Render::State*>(Air::Common::Number::Increase(""),"State",&info);
	return	true;
}

bool RenderState::Destroy()
{
	if(m_pState!=NULL){
		m_pState->ReleaseRef();
		m_pState=NULL;
	}
	return	true;
}
void RenderState::OnShowProperty( CMFCPropertyGridProperty* pGroup )
{
	__super::OnShowProperty(pGroup);

	switch(info.type){
	case Air::Client::enRST_RS:{
		AddCombo( pGroup, _T("FillMode"), strFillMode,strFillModeCount,info.rs.FillMode, _T("Note"),TRUE );
		AddCombo( pGroup, _T("CullMode"),strCullMode,strCullModeCount, info.rs.CullMode, _T("Note"),TRUE );
		AddMember( pGroup, _T("FrontCounterClockwise"), info.rs.FrontCounterClockwise, _T("Note"), TRUE );
		AddMember( pGroup, _T("DepthBias"), info.rs.DepthBias, _T("Note"), TRUE );
		AddMember( pGroup, _T("DepthBiasClamp"), info.rs.DepthBiasClamp, _T("Note"), TRUE );
		AddMember( pGroup, _T("SlopeScaledDepthBias"), info.rs.SlopeScaledDepthBias, _T("Note"), TRUE );
		AddMember( pGroup, _T("DepthClipEnable"), info.rs.DepthClipEnable, _T("Note"), TRUE );
		AddCombo( pGroup, _T("ScissorEnable"), strEnable,2,info.rs.ScissorEnable, _T("Note"), TRUE );
		AddMember( pGroup, _T("MultisampleEnable"), info.rs.MultisampleEnable, _T("Note"), TRUE );
		AddMember( pGroup, _T("AntialiasedLineEnable"), info.rs.AntialiasedLineEnable, _T("Note"), TRUE );
		break;}
	case	Air::Client::enRST_DS:{
		AddCombo( pGroup, _T("DepthEnable"), strEnable,2,info.ds.DepthEnable, _T("Note"), TRUE );
		AddCombo( pGroup, _T("DepthWriteMask"), strEnable,2,info.ds.DepthWriteMask, _T("Note"), TRUE );
		AddCombo( pGroup, _T("DepthFunc"), strCompare,strCompareCount,info.ds.DepthFunc, _T("Note"), TRUE );
		AddCombo( pGroup, _T("StencilEnable"), strEnable,2,(BOOL)info.ds.StencilEnable, _T("Note"), TRUE );
		AddMember( pGroup, _T("StencilReadMask"), (UINT)info.ds.StencilReadMask, _T("Note"), TRUE );
		AddMember( pGroup, _T("StencilWriteMask"), (UINT)info.ds.StencilWriteMask, _T("Note"), TRUE );
		CMFCPropertyGridProperty*	pFront	=	AddGroup(pGroup,_T("FrontFace"));

		AddCombo( pFront, _T("StencilFailOp"),			strStencilOP,9,info.ds.FrontFace.StencilFailOp,		_T("Note"), TRUE );
		AddCombo( pFront, _T("StencilDepthFailOp"),		strStencilOP,9,info.ds.FrontFace.StencilDepthFailOp,	_T("Note"), TRUE );
		AddCombo( pFront, _T("StencilPassOp"),			strStencilOP,9,info.ds.FrontFace.StencilPassOp,		_T("Note"), TRUE );
		AddCombo( pFront, _T("StencilFunc"),			strCompare,strCompareCount,info.ds.FrontFace.StencilFunc,			_T("Note"), TRUE );

		CMFCPropertyGridProperty*	pBack	=	AddGroup(pGroup,_T("BackFace"));

		AddCombo( pBack, _T("StencilFailOp"),			strStencilOP,9,info.ds.BackFace.StencilFailOp,		_T("Note"), TRUE );
		AddCombo( pBack, _T("StencilDepthFailOp"),		strStencilOP,9,info.ds.BackFace.StencilDepthFailOp,	_T("Note"), TRUE );
		AddCombo( pBack, _T("StencilPassOp"),			strStencilOP,9,info.ds.BackFace.StencilPassOp,		_T("Note"), TRUE );
		AddCombo( pBack, _T("StencilFunc"),				strCompare,strCompareCount,info.ds.BackFace.StencilFunc,			_T("Note"), TRUE );

		break;}
	case	Air::Client::enRST_BS:{
		AddCombo( pGroup, _T("AlphaToCoverageEnable"), strEnable,2,info.bs.AlphaToCoverageEnable, _T("Note"), TRUE );
		AddCombo( pGroup, _T("IndependentBlendEnable"), strEnable,2,info.bs.AlphaToCoverageEnable, _T("Note"), TRUE );

		for(unsigned long	i=0;i<8;i++){
			
			CMFCPropertyGridProperty*	pRTB	=	AddGroup(pGroup,strRTB[i]);
			AddCombo( pRTB, _T("BlendEnable"),				strEnable,2,info.bs.Blend[i].BlendEnable, _T("Note"), TRUE );
			AddCombo( pRTB, _T("SrcBlend"),					strBlend,20,info.bs.Blend[i].SrcBlend, _T("Note"), TRUE );
			AddCombo( pRTB, _T("DestBlend"),					strBlend,20,info.bs.Blend[i].DestBlend, _T("Note"), TRUE );
			AddCombo( pRTB, _T("BlendOp"),					strBlendOP,6,info.bs.Blend[i].BlendOp, _T("Note"), TRUE );
			AddCombo( pRTB, _T("SrcBlendAlpha"),				strBlend,20,info.bs.Blend[i].SrcBlendAlpha, _T("Note"), TRUE );
			AddCombo( pRTB, _T("DestBlendAlpha"),				strBlend,20,info.bs.Blend[i].DestBlendAlpha, _T("Note"), TRUE );
			AddCombo( pRTB, _T("BlendOpAlpha"),				strBlendOP,6,info.bs.Blend[i].BlendOpAlpha, _T("Note"), TRUE );
			AddMember( pRTB, _T("RenderTargetWriteMask"),		 (UINT)info.bs.Blend[i].RenderTargetWriteMask, _T("Note"), TRUE );
		}
		break;}
	case	Air::Client::enRST_SS:{

		break;}
	}
}

void RenderState::OnPropertyChanged( CMFCPropertyGridProperty* pProperty )
{

}