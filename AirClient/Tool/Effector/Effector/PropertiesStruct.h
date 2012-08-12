#pragma once

// static const int nenumBlendCount = 20;
// static const LPCTSTR strnenumBlend[nenumBlendCount] = {
// 	_T("enB_NONE"),
// 	_T("enB_ZERO"),
// 	_T("enB_ONE"),
// 	_T("enB_SRC_COLOR"),
// 	_T("enB_INV_SRC_COLOR"),
// 	_T("enB_SRC_ALPHA"),
// 	_T("enB_INV_SRC_ALPHA"),
// 	_T("enB_DEST_ALPHA"),
// 	_T("enB_INV_DEST_ALPHA"),
// 	_T("enB_DEST_COLOR"),
// 	_T("enB_INV_DEST_COLOR"),
// 	_T("enB_SRC_ALPHA_SAT"),
// 	_T("enB_NONE"),
// 	_T("enB_NONE"),
// 	_T("enB_BLEND_FACTOR"),
// 	_T("enB_INV_BLEND_FACTOR"),
// 	_T("enB_SRC1_COLOR"),
// 	_T("enB_INV_SRC1_COLOR"),
// 	_T("enB_SRC1_ALPHA"),
// 	_T("enB_INV_SRC1_ALPHA")
// };
// 
// static const int nenumBlendOPCount = 6;
// static const LPCTSTR strenumBlendOP[nenumBlendOPCount] = {
// 	_T("enBOP_NONE"),
// 	_T("enBOP_ADD"),
// 	_T("enBOP_SUBTRACT"),
// 	_T("enBOP_REV_SUBTRACT"),
// 	_T("enBOP_MIN"),
// 	_T("enBOP_MAX")
// };
// 
// static const int nenumStencileOPCount = 9;
// static const LPCTSTR strenumStencileOP[nenumStencileOPCount] = {
// 	_T("enSOP_NONE"),
// 	_T("enSOP_KEEP"),
// 	_T("enSOP_ZERO"),
// 	_T("enSOP_REPLACE"),
// 	_T("enSOP_INCR_SAT"),
// 	_T("enSOP_DECR_SAT"),
// 	_T("enSOP_INVERT"),
// 	_T("enSOP_INCR"),
// 	_T("enSOP_DECR")
// };
// 
// static const int nenumCompareCount = 9;
// static const LPCTSTR strenumCompare[nenumCompareCount] = {
// 	_T("enC_NONE")
// 	_T("enC_NEVER"),
// 	_T("enC_LESS"),
// 	_T("enC_EQUAL"),
// 	_T("enC_LESS_EQUAL"),
// 	_T("enC_GREATER"),
// 	_T("enC_NOT_EQUAL"),
// 	_T("enC_GREATER_EQUAL"),
// 	_T("enC_ALWAYS")
// };
// 
// static const int nenumDepthWriteMaskCount = 2;
// static const LPCTSTR strenumDepthWriteMask[nenumDepthWriteMaskCount] = {
// 	_T("enDWM_ZERO"),
// 	_T("enDWM_ALL")
// };
// 
// static const int nenumFillModeCount = 4;
// static const LPCTSTR strenumFillMode[nenumFillModeCount] = {
// 	_T("enFM_NONE"),
// 	_T("enFM_POINT"),
// 	_T("enFM_WIREFRAME"),
// 	_T("enFM_SOILD")
// };
// 
// static const int nenumCullModeCount = 3;
// static const LPCTSTR strenumCullMode[nenumCullModeCount] = {
// 	_T("enCM_NONE"),
// 	_T("enCM_CW"),
// 	_T("enCM_CCW")
// };
// 
// static const int nenumTextureFilterCount = 19;
// static const LPCTSTR strenumTextureFilter[nenumTextureFilterCount] = {
// 	_T("enTF_MIN_MAG_MIP_POINT"),
// 	_T("enTF_MIN_MAG_POINT_MIP_LINEAR"),
// 	_T("enTF_MIN_POINT_MAG_LINEAR_MIP_POINT"),
// 	_T("enTF_MIN_POINT_MAG_MIP_LINEAR"),
// 	_T("enTF_MIN_LINEAR_MAG_MIP_POINT"),
// 	_T("enTF_MIN_LINEAR_MAG_POINT_MIP_LINEAR"),
// 	_T("enTF_MIN_MAG_LINEAR_MIP_POINT"),
// 	_T("enTF_MIN_MAG_MIP_LINEAR"),
// 	_T("enTF_ANISOTROPIC"),
// 	_T("enTF_COMPARISON_MIN_MAG_MIP_POINT"),
// 	_T("enTF_COMPARISON_MIN_MAG_POINT_MIP_LINEAR"),
// 	_T("enTF_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT"),
// 	_T("enTF_COMPARISON_MIN_POINT_MAG_MIP_LINEAR"),
// 	_T("enTF_COMPARISON_MIN_LINEAR_MAG_MIP_POINT"),
// 	_T("enTF_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR"),
// 	_T("enTF_COMPARISON_MIN_MAG_LINEAR_MIP_POINT"),
// 	_T("enTF_COMPARISON_MIN_MAG_MIP_LINEAR"),
// 	_T("enTF_COMPARISON_ANISOTROPIC"),
// 	_T("enTF_TEXT_1BIT")
// };
// 
// static const int nenumTextureAddressCount = 7;
// static const LPCTSTR strenumTextureAddress[nenumTextureAddressCount] = {
// 	_T("enTA_NONE"),
// 	_T("enTA_WRAP"),
// 	_T("enTA_MIRROR"),
// 	_T("enTA_CLAMP"),
// 	_T("enTA_BORDER"),
// 	_T("enTA_MIRROR_ONCE"),
// 	_T("enTA_UNKNOWN")
// };
// 
// #define ADD_ETYPE( pGroup, eTypeName, eTypeValueCurr, bIsEdit )\
// 	PropertiesGrid* pProp##eTypeName = new PropertiesGrid( _T( #eTypeName ), str##eTypeName[eTypeValueCurr], _T( #eTypeName ) );\
// 	for ( int n##eTypeName##Index = 0; n##eTypeName##Index < n##eTypeName##Count; n##eTypeName##Index++ )\
// 	{\
// 		pProp##eTypeName->AddOption( str##eTypeName[n##eTypeName##Index] );\
// 	}\
// 	pProp##eTypeName->AllowEdit( bIsEdit );\
// 	pGroup->AddSubItem( pProp##eTypeName )\
// 
// #define ADD_MEMBER( pGroup, MemberName, MemberValue, Note, bIsEdit )\
// 	PropertiesGrid* pProp##MemberName = new PropertiesGrid( _T(#MemberName), (_variant_t) MemberValue, _T(#Note) );\
// 	pProp##MemberName->AllowEdit( bIsEdit );\
// 	pGroup->AddSubItem( pProp##MemberName )\


//void AddCombo(CMFCPropertyGridProperty* pGroup,const TCHAR* strName,const LPCTSTR* strEnum,int iSize,int T_Value,const TCHAR*	strDesc,BOOL	bIsEdit);

// template<typename T>
// void AddMember(CMFCPropertyGridProperty* pGroup,const TCHAR* strName,const T& T_Value,const TCHAR*	strDesc,BOOL	bIsEdit){
// 	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty( (strName), (_variant_t) T_Value, strDesc );
// 	pProp->AllowEdit( bIsEdit );
// 	pGroup->AddSubItem( pProp );
// }

class PropertiesStruct
{
public:
	PropertiesStruct(void);
	~PropertiesStruct(void);
};

