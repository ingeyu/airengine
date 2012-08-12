#include "stdafx.h"
#include "EngineCommon.h"
#include "EngineEffect.h"
#include "EngineCamera.h"
#include "EnginePhase.h"
#include "EnginePass.h"
#include "EngineRenderTexture.h"
#include "EngineMesh.h"
#include "EngineTexture.h"
#include "EnginePass.h"
#include "EngineRenderState.h"
#include "EngineShader.h"
#include "EngineModel.h"

#include "PropertiesStruct.h"


TreeObj::TreeObj( const TCHAR*	strName,TreeObj* parent,CTreeCtrl*	pTree,enumTreeObjType	t )
{
	m_pTree		=	pTree;
	m_pParent	=	parent;
	int iImg	=	t;
	iImg	-=	enTOT_Phase;
	if(m_pParent==NULL){
		m_Item	=	pTree->InsertItem(_T("Solution"));
	}else{
		m_Item	=	pTree->InsertItem(strName,iImg,iImg,m_pParent->GetItem());	
	}
	pTree->SetItemData(m_Item,(DWORD_PTR)this);
	m_Type			=	t;
	m_bEnableEdit	=	false;
	m_bEnableBind	=	false;

	m_pBindObj		=	NULL;
	m_bEnableActive	=	false;
	m_bIsResource	=	false;
}


std::wstring TreeObj::GetName()
{
	return	m_pTree->GetItemText(m_Item).GetBuffer();
}
HTREEITEM TreeObj::GetItem()
{
	return	m_Item;
}

enumTreeObjType TreeObj::GetType()
{
	return	m_Type;
}


CTreeCtrl* TreeObj::GetTree()
{
	return	m_pTree;
}

void TreeObj::DeleteSelf()
{
	if(m_pParent!=NULL){
		m_pParent->DestroyChild(this);
	}else{
// 		Destroy();
// 		delete this;
	}
}

bool TreeObj::Create()
{
	return		true;
}

bool TreeObj::Destroy()
{
	if(m_Item!=NULL){
		m_pTree->DeleteItem(m_Item);
		m_Item	=	NULL;
	}
	m_pTree	=	NULL;
	DestroyAllChild();
	return	true;
}

void TreeObj::DestroyChild( TreeObj* pChild )
{
	if(pChild==NULL)
		return;

	std::vector<TreeObj*>::iterator	i	=	m_vecChild.begin();
	for(;i!=m_vecChild.end();i++){
		if(*i	==	pChild){
			m_vecChild.erase(i);
			pChild->Destroy();
			delete pChild;
			return;
		}
	}
}

void TreeObj::AddChild( TreeObj* pChild )
{
	if(pChild==NULL)
		return;
	std::vector<TreeObj*>::iterator	i	=	m_vecChild.begin();
	for(;i!=m_vecChild.end();i++){
		if(*i	==	pChild){
			return;
		}
	}
	m_vecChild.push_back(pChild);
	m_pTree->Expand(m_Item,TVE_EXPAND);
}

TreeObj* TreeObj::AddChild( const TCHAR* strName,enumTreeObjType t )
{
	TreeObj*	pChild	=	NULL;
	switch(t){
	case 	enTOT_RState		:
	case	enTOT_DState		:
	case	enTOT_BState		:
	case	enTOT_SState		:{
		pChild		=	new RenderState(strName,this,t);
		break;};
	case	enTOT_VShader		:
	case	enTOT_GShader		:
	case	enTOT_PShader		:
	case	enTOT_CShader		:
	case	enTOT_HShader		:
	case	enTOT_DShader		:{
		pChild		=	new EShader(strName,this,t);
		break;};
	case	enTOT_ConstantBuffer:{break;};
	case	enTOT_Pass			:{
		pChild		=	new EPass(strName,this);
		break;};
	case	enTOT_Texture		:{
		pChild		=	new ETexture(strName,this);
		break;};
	case	enTOT_TextureRef		:{
		//pChild		=	new ETexture(strName,this);
		break;};
	case	enTOT_Mesh			:{
		pChild		=	new Mesh(strName,this);
		break;};
	case	enTOT_Model			:{
		pChild		=	new Model(strName,this);
		break;};
	case	enTOT_ModelRef			:{
		pChild		=	new ModelRef(strName,this);
		break;};
	case	enTOT_RenderTexture	:{
		pChild	=	new	RenderTexture(strName,this);
		break;};
	case	enTOT_RenderTarget	:{break;};
	case	enTOT_Phase			:{
		pChild	=	new	Phase(strName,this);
		break;};
	case	enTOT_Effect		:{
		pChild	=	new	Effect(strName,this);
		break;};
	case	enTOT_Camera		:{
		pChild	=	new	ECamera(strName,this);
		break;};
	case	enTOT_EffectorFile	:{

		break;};

	}
	if(pChild!=NULL){
		AddChild(pChild);
	}
	return	pChild;
}

TreeObj::~TreeObj()
{
	if(m_Item!=NULL){
		m_pTree->DeleteItem(m_Item);
		m_Item	=	NULL;
	}
}

void TreeObj::DestroyAllChild()
{
	std::vector<TreeObj*>::iterator	i	=	m_vecChild.begin();
	for(;i!=m_vecChild.end();i++){
		TreeObj*	p	=	(*i);
		p->Destroy();
		delete p;
	}
	m_vecChild.clear();
}

void TreeObj::SaveToFile( FILE* pFile )
{
	std::wstring	str	=	GetName();
	unsigned long	uiNameLength	=	str.size();
	fwrite(&uiNameLength,sizeof(unsigned long),1,pFile);
	fwrite(str.c_str(),uiNameLength*sizeof(wchar_t),1,pFile);
	fwrite(&m_Type,sizeof(enumTreeObjType),1,pFile);
	SaveSelf(pFile);
	SaveChild(pFile);
}

void TreeObj::RemoveChild( TreeObj* pChild )
{
	std::vector<TreeObj*>::iterator	i	=	m_vecChild.begin();
	for(;i!=m_vecChild.end();i++){
		TreeObj*	p	=	(*i);
		if(p==pChild){
			m_vecChild.erase(i);
			return;
		}
	}
}

TreeObj* TreeObj::GetParent()
{
	return	m_pParent;
}

void TreeObj::SetName( const TCHAR* str )
{
	m_pTree->SetItemText(m_Item,str);
}

bool TreeObj::IsEnableEdit()
{
	return	m_bEnableEdit;
}

void TreeObj::Parse( unsigned char*& pData )
{
	ParseSelf(pData);
	ParseChild(pData);
}

void TreeObj::ParseChild( unsigned char*& pData )
{
	unsigned long	uiEffectCount	=	0;
	uiEffectCount	=	*(unsigned long*)pData;pData+=sizeof(unsigned long);
	for(unsigned long	i=0;i<uiEffectCount;i++){
		std::wstring	str;
		unsigned long	uiNameLength	=	*(unsigned long*)pData;pData+=sizeof(unsigned long);
		str.resize(uiNameLength);
		memcpy(&str[0],pData,uiNameLength*sizeof(wchar_t));
		pData+=uiNameLength*sizeof(wchar_t);
		enumTreeObjType	t	=	*(enumTreeObjType*)pData;pData+=sizeof(enumTreeObjType);

		TreeObj*	pChild	=	AddChild(str.c_str(),t);
		if(pChild!=NULL){
			pChild->SetType(t);
			pChild->Parse(pData);
		}
	}
}

void TreeObj::ParseSelf( unsigned char*& pData )
{
	if(m_bIsResource){
		ReadString(m_strResourceName,pData);
		if(!m_strResourceName.empty()){
			Destroy();

			Create();
		}
	}
}

void TreeObj::SaveSelf( FILE* pFile )
{
	if(m_bIsResource){
		WriteString(m_strResourceName,pFile);
	}
}

void TreeObj::SaveChild( FILE* pFile )
{
	unsigned long	uiChildCount	=	m_vecChild.size();
	fwrite(&uiChildCount,sizeof(unsigned long),1,pFile);

	for(unsigned long i=0;i<uiChildCount;i++){
		TreeObj*	pEffect	=	m_vecChild[i];
		pEffect->SaveToFile(pFile);
	}
}

void TreeObj::SetType( enumTreeObjType t )
{
	m_Type	=	t;
}

std::vector<TreeObj*> TreeObj::GetChildByType( enumTreeObjType t )
{
	std::vector<TreeObj*>	vec;

	std::vector<TreeObj*>::iterator	i	=	m_vecChild.begin();
	for(;i!=m_vecChild.end();i++){
		if((*i)->GetType()	==	t){
			vec.push_back(*i);
		}
	}
	return	vec;
}

bool TreeObj::IsEnableBind()
{
	return	m_bEnableBind;
}

void TreeObj::SetBindObj( TreeObj* pObj )
{
	m_pBindObj	=	pObj;
}

bool TreeObj::ReLoad()
{
	return	false;
}

bool TreeObj::IsEnableActive()
{
	return	m_bEnableActive;
}

TreeObj* TreeObj::GetBindObj()
{
	return	m_pBindObj;
}

bool TreeObj::IsResource()
{
	return	m_bIsResource;
}

void TreeObj::SetResourceName( const std::wstring& strName )
{
	m_strResourceName	=	strName;
}

const std::wstring& TreeObj::GetResourceName()
{
	return	m_strResourceName;
}

void TreeObj::WriteString( const std::wstring& str,FILE* pFile )
{
	unsigned long	uiStringSize	=	str.size();
	fwrite(&uiStringSize,sizeof(unsigned long),1,pFile);
	if(uiStringSize!=0)
		fwrite(&str[0],uiStringSize*sizeof(wchar_t),1,pFile);
}

void TreeObj::ReadString( std::wstring& str,unsigned char*& pData )
{
	unsigned long	uiStringSize	=	*(unsigned long*)pData;
	pData+=sizeof(unsigned long);
	if(uiStringSize!=0){
		str.resize(uiStringSize);
		memcpy(&str[0],pData,uiStringSize*sizeof(wchar_t));
		pData+=uiStringSize*sizeof(wchar_t);
	}
}

void TreeObj::OnShowProperty( CMFCPropertyGridProperty* pGroup )
{
	AddMember(pGroup,_T("ObjectType"),GetNameString(GetType()).c_str(),_T("Tree	Object Type. (Example Mesh Texture Shader......)"),FALSE);
	AddMember(pGroup,_T("IsCanReName"),(BOOL)IsEnableEdit(),_T("This Object Can/Can't ReName! (Some Can't ReName Example RS BS DS SS)"),FALSE);
	AddMember(pGroup,_T("IsCanBind"),(BOOL)IsEnableBind(),_T("This Object Can/Can't Bind Another Object! (Some Example CameraRef TextureRef Phase Model)"),FALSE);
	if(IsEnableBind()){
		std::wstring	str;
		if(GetBindObj()!=NULL)
			str	=	GetBindObj()->GetName();
		AddMember(pGroup,_T("BindObject"),str.c_str(),_T("This Binded Object Name!"),FALSE);
	}
	AddMember(pGroup,_T("IsResource"),(BOOL)IsResource(),_T("This Object Is Resource From File! (Mesh Texture Shader...)"),FALSE);
	if(IsResource()){
		std::wstring	str	=	GetResourceName();
		//AddMember(pGroup,_T("ResourceName"),str.c_str(),_T("This Object Linked Resource Name!"),FALSE);
		static const TCHAR szFilter[] = _T("所有文件(*.*)|*.*||");
		//new CMFCPropertyGridFileProperty(_T("图标"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("指定窗口图标")));
		CMFCPropertyGridFileProperty*	pFileProp	=	new CMFCPropertyGridFileProperty(_T("ResourceName"),TRUE,str.c_str(),_T(""),0,szFilter,_T("指定窗口图标"));
		pGroup->AddSubItem(pFileProp);
	}
}

void TreeObj::OnPropertyChanged( CMFCPropertyGridProperty* pProperty )
{

}

unsigned int TreeObj::GetChildCountByType(enumTreeObjType	t)
{
	unsigned int uiCount	=	0;
	std::vector<TreeObj*>::iterator	i	=	m_vecChild.begin();
	for(;i!=m_vecChild.end();i++){
		if((*i)->GetType()	==	t){
			uiCount++;
		}
	}
	return	uiCount;
}

TreeObj* TreeObj::GetChild( enumTreeObjType t,unsigned long uiIndex )
{
	unsigned int uiCount	=	0;
	std::vector<TreeObj*>::iterator	i	=	m_vecChild.begin();
	for(;i!=m_vecChild.end();i++){
		if((*i)->GetType()	==	t){
			if(uiIndex	==	uiCount){
				return	*i;
			}
			uiCount++;
		}
	}
	return	NULL;
}

std::wstring GetNameString( enumTreeObjType val )
{
	static	std::map<enumTreeObjType,std::wstring>	mapString;
	static	bool	bInit	=	false;
	if(!bInit){
		mapString[enTOT_Unknown]			=_T("Unknown");
		mapString[enTOT_RState]				=_T("RasterizerState");
		mapString[enTOT_DState]				=_T("DepthStencilState");
		mapString[enTOT_BState]				=_T("BlendState");
		mapString[enTOT_SState]				=_T("SamplerState");
		mapString[enTOT_VShader]			=_T("VertexShader");
		mapString[enTOT_GShader]			=_T("GeometryShader");
		mapString[enTOT_PShader]			=_T("PixelShader");
		mapString[enTOT_CShader]			=_T("ComputerShader");
		mapString[enTOT_HShader]			=_T("HullShader");
		mapString[enTOT_DShader]			=_T("DomainShader");
		mapString[enTOT_ConstantBuffer]		=_T("ConstantBuffer");
		mapString[enTOT_Pass]				=_T("Pass");
		mapString[enTOT_Texture]			=_T("Texture");
		mapString[enTOT_TextureRef]			=_T("TextureRef");
		mapString[enTOT_Mesh]				=_T("Mesh");
		mapString[enTOT_Model]				=_T("Model");
		mapString[enTOT_RenderTexture]		=_T("RenderTexture");
		mapString[enTOT_RenderTarget]		=_T("RenderTarget");
		mapString[enTOT_Phase]				=_T("Phase");
		mapString[enTOT_Effect]				=_T("Effect");
		mapString[enTOT_Camera]				=_T("Camera");
		mapString[enTOT_CameraRef]			=_T("CameraRef");
		mapString[enTOT_EffectorFile]		=_T("EffectorFile");
		bInit	=	true;
	}
	return	mapString[val];
}

std::wstring GetNameString( Air::Client::enumTextureFormat val )
{
	static	std::map<Air::Client::enumTextureFormat,std::wstring>	mapString;
	static	bool	bInit	=	false;
	if(!bInit){
		mapString[Air::Client::enTFMT_UNKNOWN				       ]	=	_T("enTFMT_UNKNOWN                         ");     
		mapString[Air::Client::enTFMT_R32G32B32A32_TYPELESS        ]	=	_T("enTFMT_R32G32B32A32_TYPELESS     	   ");
		mapString[Air::Client::enTFMT_R32G32B32A32_FLOAT           ]	=	_T("enTFMT_R32G32B32A32_FLOAT        	   ");
		mapString[Air::Client::enTFMT_R32G32B32A32_UINT            ]	=	_T("enTFMT_R32G32B32A32_UINT         	   ");
		mapString[Air::Client::enTFMT_R32G32B32A32_SINT            ]	=	_T("enTFMT_R32G32B32A32_SINT         	   ");
		mapString[Air::Client::enTFMT_R32G32B32_TYPELESS           ]	=	_T("enTFMT_R32G32B32_TYPELESS        	   ");
		mapString[Air::Client::enTFMT_R32G32B32_FLOAT              ]	=	_T("enTFMT_R32G32B32_FLOAT           	   ");
		mapString[Air::Client::enTFMT_R32G32B32_UINT               ]	=	_T("enTFMT_R32G32B32_UINT            	   ");
		mapString[Air::Client::enTFMT_R32G32B32_SINT               ]	=	_T("enTFMT_R32G32B32_SINT            	   ");
		mapString[Air::Client::enTFMT_R16G16B16A16_TYPELESS        ]	=	_T("enTFMT_R16G16B16A16_TYPELESS     	   ");
		mapString[Air::Client::enTFMT_R16G16B16A16_FLOAT           ]	=	_T("enTFMT_R16G16B16A16_FLOAT        	   ");
		mapString[Air::Client::enTFMT_R16G16B16A16_UNORM           ]	=	_T("enTFMT_R16G16B16A16_UNORM        	   ");
		mapString[Air::Client::enTFMT_R16G16B16A16_UINT            ]	=	_T("enTFMT_R16G16B16A16_UINT         	   ");
		mapString[Air::Client::enTFMT_R16G16B16A16_SNORM           ]	=	_T("enTFMT_R16G16B16A16_SNORM        	   ");
		mapString[Air::Client::enTFMT_R16G16B16A16_SINT            ]	=	_T("enTFMT_R16G16B16A16_SINT         	   ");
		mapString[Air::Client::enTFMT_R32G32_TYPELESS              ]	=	_T("enTFMT_R32G32_TYPELESS           	   ");
		mapString[Air::Client::enTFMT_R32G32_FLOAT                 ]	=	_T("enTFMT_R32G32_FLOAT              	   ");
		mapString[Air::Client::enTFMT_R32G32_UINT                  ]	=	_T("enTFMT_R32G32_UINT               	   ");
		mapString[Air::Client::enTFMT_R32G32_SINT                  ]	=	_T("enTFMT_R32G32_SINT               	   ");
		mapString[Air::Client::enTFMT_R32G8X24_TYPELESS            ]	=	_T("enTFMT_R32G8X24_TYPELESS         	   ");
		mapString[Air::Client::enTFMT_D32_FLOAT_S8X24_UINT         ]	=	_T("enTFMT_D32_FLOAT_S8X24_UINT      	   ");
		mapString[Air::Client::enTFMT_R32_FLOAT_X8X24_TYPELESS     ]	=	_T("enTFMT_R32_FLOAT_X8X24_TYPELESS  	   ");
		mapString[Air::Client::enTFMT_X32_TYPELESS_G8X24_UINT      ]	=	_T("enTFMT_X32_TYPELESS_G8X24_UINT   	   ");
		mapString[Air::Client::enTFMT_R10G10B10A2_TYPELESS         ]	=	_T("enTFMT_R10G10B10A2_TYPELESS      	   ");
		mapString[Air::Client::enTFMT_R10G10B10A2_UNORM            ]	=	_T("enTFMT_R10G10B10A2_UNORM         	   ");
		mapString[Air::Client::enTFMT_R10G10B10A2_UINT             ]	=	_T("enTFMT_R10G10B10A2_UINT          	   ");
		mapString[Air::Client::enTFMT_R11G11B10_FLOAT              ]	=	_T("enTFMT_R11G11B10_FLOAT           	   ");
		mapString[Air::Client::enTFMT_R8G8B8A8_TYPELESS            ]	=	_T("enTFMT_R8G8B8A8_TYPELESS         	   ");
		mapString[Air::Client::enTFMT_R8G8B8A8_UNORM               ]	=	_T("enTFMT_R8G8B8A8_UNORM            	   ");
		mapString[Air::Client::enTFMT_R8G8B8A8_UNORM_SRGB          ]	=	_T("enTFMT_R8G8B8A8_UNORM_SRGB       	   ");
		mapString[Air::Client::enTFMT_R8G8B8A8_UINT                ]	=	_T("enTFMT_R8G8B8A8_UINT             	   ");
		mapString[Air::Client::enTFMT_R8G8B8A8_SNORM               ]	=	_T("enTFMT_R8G8B8A8_SNORM            	   ");
		mapString[Air::Client::enTFMT_R8G8B8A8_SINT                ]	=	_T("enTFMT_R8G8B8A8_SINT             	   ");
		mapString[Air::Client::enTFMT_R16G16_TYPELESS              ]	=	_T("enTFMT_R16G16_TYPELESS           	   ");
		mapString[Air::Client::enTFMT_R16G16_FLOAT                 ]	=	_T("enTFMT_R16G16_FLOAT              	   ");
		mapString[Air::Client::enTFMT_R16G16_UNORM                 ]	=	_T("enTFMT_R16G16_UNORM              	   ");
		mapString[Air::Client::enTFMT_R16G16_UINT                  ]	=	_T("enTFMT_R16G16_UINT               	   ");
		mapString[Air::Client::enTFMT_R16G16_SNORM                 ]	=	_T("enTFMT_R16G16_SNORM              	   ");
		mapString[Air::Client::enTFMT_R16G16_SINT                  ]	=	_T("enTFMT_R16G16_SINT               	   ");
		mapString[Air::Client::enTFMT_R32_TYPELESS                 ]	=	_T("enTFMT_R32_TYPELESS              	   ");
		mapString[Air::Client::enTFMT_D32_FLOAT                    ]	=	_T("enTFMT_D32_FLOAT                 	   ");
		mapString[Air::Client::enTFMT_R32_FLOAT                    ]	=	_T("enTFMT_R32_FLOAT                 	   ");
		mapString[Air::Client::enTFMT_R32_UINT                     ]	=	_T("enTFMT_R32_UINT                  	   ");
		mapString[Air::Client::enTFMT_R32_SINT                     ]	=	_T("enTFMT_R32_SINT                  	   ");
		mapString[Air::Client::enTFMT_R24G8_TYPELESS               ]	=	_T("enTFMT_R24G8_TYPELESS            	   ");
		mapString[Air::Client::enTFMT_D24_UNORM_S8_UINT            ]	=	_T("enTFMT_D24_UNORM_S8_UINT         	   ");
		mapString[Air::Client::enTFMT_R24_UNORM_X8_TYPELESS        ]	=	_T("enTFMT_R24_UNORM_X8_TYPELESS     	   ");
		mapString[Air::Client::enTFMT_X24_TYPELESS_G8_UINT         ]	=	_T("enTFMT_X24_TYPELESS_G8_UINT      	   ");
		mapString[Air::Client::enTFMT_R8G8_TYPELESS                ]	=	_T("enTFMT_R8G8_TYPELESS             	   ");
		mapString[Air::Client::enTFMT_R8G8_UNORM                   ]	=	_T("enTFMT_R8G8_UNORM                	   ");
		mapString[Air::Client::enTFMT_R8G8_UINT                    ]	=	_T("enTFMT_R8G8_UINT                 	   ");
		mapString[Air::Client::enTFMT_R8G8_SNORM                   ]	=	_T("enTFMT_R8G8_SNORM                	   ");
		mapString[Air::Client::enTFMT_R8G8_SINT                    ]	=	_T("enTFMT_R8G8_SINT                 	   ");
		mapString[Air::Client::enTFMT_R16_TYPELESS                 ]	=	_T("enTFMT_R16_TYPELESS              	   ");
		mapString[Air::Client::enTFMT_R16_FLOAT                    ]	=	_T("enTFMT_R16_FLOAT                 	   ");
		mapString[Air::Client::enTFMT_D16_UNORM                    ]	=	_T("enTFMT_D16_UNORM                 	   ");
		mapString[Air::Client::enTFMT_R16_UNORM                    ]	=	_T("enTFMT_R16_UNORM                 	   ");
		mapString[Air::Client::enTFMT_R16_UINT                     ]	=	_T("enTFMT_R16_UINT                  	   ");
		mapString[Air::Client::enTFMT_R16_SNORM                    ]	=	_T("enTFMT_R16_SNORM                 	   ");
		mapString[Air::Client::enTFMT_R16_SINT                     ]	=	_T("enTFMT_R16_SINT                  	   ");
		mapString[Air::Client::enTFMT_R8_TYPELESS                  ]	=	_T("enTFMT_R8_TYPELESS               	   ");
		mapString[Air::Client::enTFMT_R8_UNORM                     ]	=	_T("enTFMT_R8_UNORM                  	   ");
		mapString[Air::Client::enTFMT_R8_UINT                      ]	=	_T("enTFMT_R8_UINT                   	   ");
		mapString[Air::Client::enTFMT_R8_SNORM                     ]	=	_T("enTFMT_R8_SNORM                  	   ");
		mapString[Air::Client::enTFMT_R8_SINT                      ]	=	_T("enTFMT_R8_SINT                   	   ");
		mapString[Air::Client::enTFMT_A8_UNORM                     ]	=	_T("enTFMT_A8_UNORM                  	   ");
		mapString[Air::Client::enTFMT_R1_UNORM                     ]	=	_T("enTFMT_R1_UNORM                  	   ");
		mapString[Air::Client::enTFMT_R9G9B9E5_SHAREDEXP           ]	=	_T("enTFMT_R9G9B9E5_SHAREDEXP        	   ");
		mapString[Air::Client::enTFMT_R8G8_B8G8_UNORM              ]	=	_T("enTFMT_R8G8_B8G8_UNORM           	   ");
		mapString[Air::Client::enTFMT_G8R8_G8B8_UNORM              ]	=	_T("enTFMT_G8R8_G8B8_UNORM           	   ");
		mapString[Air::Client::enTFMT_BC1_TYPELESS                 ]	=	_T("enTFMT_BC1_TYPELESS              	   ");
		mapString[Air::Client::enTFMT_BC1_UNORM                    ]	=	_T("enTFMT_BC1_UNORM                 	   ");
		mapString[Air::Client::enTFMT_BC1_UNORM_SRGB               ]	=	_T("enTFMT_BC1_UNORM_SRGB            	   ");
		mapString[Air::Client::enTFMT_BC2_TYPELESS                 ]	=	_T("enTFMT_BC2_TYPELESS              	   ");
		mapString[Air::Client::enTFMT_BC2_UNORM                    ]	=	_T("enTFMT_BC2_UNORM                 	   ");
		mapString[Air::Client::enTFMT_BC2_UNORM_SRGB               ]	=	_T("enTFMT_BC2_UNORM_SRGB            	   ");
		mapString[Air::Client::enTFMT_BC3_TYPELESS                 ]	=	_T("enTFMT_BC3_TYPELESS              	   ");
		mapString[Air::Client::enTFMT_BC3_UNORM                    ]	=	_T("enTFMT_BC3_UNORM                 	   ");
		mapString[Air::Client::enTFMT_BC3_UNORM_SRGB               ]	=	_T("enTFMT_BC3_UNORM_SRGB            	   ");
		mapString[Air::Client::enTFMT_BC4_TYPELESS                 ]	=	_T("enTFMT_BC4_TYPELESS              	   ");
		mapString[Air::Client::enTFMT_BC4_UNORM                    ]	=	_T("enTFMT_BC4_UNORM                 	   ");
		mapString[Air::Client::enTFMT_BC4_SNORM                    ]	=	_T("enTFMT_BC4_SNORM                 	   ");
		mapString[Air::Client::enTFMT_BC5_TYPELESS                 ]	=	_T("enTFMT_BC5_TYPELESS              	   ");
		mapString[Air::Client::enTFMT_BC5_UNORM                    ]	=	_T("enTFMT_BC5_UNORM                 	   ");
		mapString[Air::Client::enTFMT_BC5_SNORM                    ]	=	_T("enTFMT_BC5_SNORM                 	   ");
		mapString[Air::Client::enTFMT_B5G6R5_UNORM                 ]	=	_T("enTFMT_B5G6R5_UNORM              	   ");
		mapString[Air::Client::enTFMT_B5G5R5A1_UNORM               ]	=	_T("enTFMT_B5G5R5A1_UNORM            	   ");
		mapString[Air::Client::enTFMT_B8G8R8A8_UNORM               ]	=	_T("enTFMT_B8G8R8A8_UNORM            	   ");
		mapString[Air::Client::enTFMT_B8G8R8X8_UNORM               ]	=	_T("enTFMT_B8G8R8X8_UNORM            	   ");
		mapString[Air::Client::enTFMT_R10G10B10_XR_BIAS_A2_UNORM   ]	=	_T("enTFMT_R10G10B10_XR_BIAS_A2_UNORM	   ");
		mapString[Air::Client::enTFMT_B8G8R8A8_TYPELESS            ]	=	_T("enTFMT_B8G8R8A8_TYPELESS         	   ");
		mapString[Air::Client::enTFMT_B8G8R8A8_UNORM_SRGB          ]	=	_T("enTFMT_B8G8R8A8_UNORM_SRGB       	   ");
		mapString[Air::Client::enTFMT_B8G8R8X8_TYPELESS            ]	=	_T("enTFMT_B8G8R8X8_TYPELESS         	   ");
		mapString[Air::Client::enTFMT_B8G8R8X8_UNORM_SRGB          ]	=	_T("enTFMT_B8G8R8X8_UNORM_SRGB       	   ");
		mapString[Air::Client::enTFMT_BC6H_TYPELESS                ]	=	_T("enTFMT_BC6H_TYPELESS             	   ");
		mapString[Air::Client::enTFMT_BC6H_UF16                    ]	=	_T("enTFMT_BC6H_UF16                 	   ");
		mapString[Air::Client::enTFMT_BC6H_SF16                    ]	=	_T("enTFMT_BC6H_SF16                 	   ");
		mapString[Air::Client::enTFMT_BC7_TYPELESS                 ]	=	_T("enTFMT_BC7_TYPELESS              	   ");
		mapString[Air::Client::enTFMT_BC7_UNORM                    ]	=	_T("enTFMT_BC7_UNORM                 	   ");
		mapString[Air::Client::enTFMT_BC7_UNORM_SRGB               ]	=	_T("enTFMT_BC7_UNORM_SRGB            	   ");
		mapString[Air::Client::enTFMT_FORCE_UINT                   ]	=	_T("enTFMT_FORCE_UINT                	   ");


		bInit	=	true;
	}
	return	mapString[val];
}

std::wstring GetNameString( Air::Client::enumTextureType val )
{
	static	std::map<Air::Client::enumTextureType,std::wstring>	mapString;
	static	bool	bInit	=	false;
	if(!bInit){
			mapString[Air::Client::enTT_Unknown			]	=_T("enTT_Unknown			");
			mapString[Air::Client::enTT_Texture1D		]	=_T("enTT_Texture1D			");
			mapString[Air::Client::enTT_Texture2D		]	=_T("enTT_Texture2D			");
			mapString[Air::Client::enTT_Texture3D		]	=_T("enTT_Texture3D			");
			mapString[Air::Client::enTT_TextureCUBE		]	=_T("enTT_TextureCUBE		");
			mapString[Air::Client::enTT_Texture1DArray	]	=_T("enTT_Texture1DArray	");
			mapString[Air::Client::enTT_Texture2DArray	]	=_T("enTT_Texture2DArray	");
			mapString[Air::Client::enTT_Texture3DArray	]	=_T("enTT_Texture3DArray	");
			mapString[Air::Client::enTT_TextureCUBEArray]	=_T("enTT_TextureCUBEArray	");

		bInit	=	true;
	}
	return	mapString[val];
}

void AddMember( CMFCPropertyGridProperty* pGroup,const TCHAR* strName,const Air::Float3& v ,BOOL bEdit)
{
	CMFCPropertyGridProperty*	pNewGroup	=	AddGroup(pGroup,strName);
	AddMember(pNewGroup,_T("x"),v.x,_T("float value!"),bEdit);
	AddMember(pNewGroup,_T("y"),v.y,_T("float value!"),bEdit);
	AddMember(pNewGroup,_T("z"),v.z,_T("float value!"),bEdit);
}

void AddMember( CMFCPropertyGridProperty* pGroup,const TCHAR* strName,const Air::BoundingBox& b,BOOL bEdit )
{
	CMFCPropertyGridProperty*	pNewGroup	=	AddGroup(pGroup,strName);
	AddMember(pNewGroup,_T("min"),b.vMin,bEdit);
	AddMember(pNewGroup,_T("max"),b.vMax,bEdit);
}

void AddMember( CMFCPropertyGridProperty* pGroup,const TCHAR* strName,const Air::Float4& v,BOOL bEdit /*= FALSE*/ )
{
	CMFCPropertyGridProperty*	pNewGroup	=	AddGroup(pGroup,strName);
	AddMember(pNewGroup,_T("x"),v.x,_T("float value!"),bEdit);
	AddMember(pNewGroup,_T("y"),v.y,_T("float value!"),bEdit);
	AddMember(pNewGroup,_T("z"),v.z,_T("float value!"),bEdit);
	AddMember(pNewGroup,_T("w"),v.z,_T("float value!"),bEdit);
}

// void AddMember( CMFCPropertyGridProperty* pGroup,const TCHAR* strName,const TCHAR* strValue,BOOL bEdit /*= FALSE*/ )
// {
// 	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty( (strName), (_variant_t) strValue, strDesc );
// 	pProp->AllowEdit( bEdit );
// 	pGroup->AddSubItem( pProp );
// }

CMFCPropertyGridProperty* AddGroup( CMFCPropertyGridProperty* pGroup,const TCHAR* strName )
{
	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty( (strName));
	pGroup->AddSubItem( pProp );
	return	pProp;
}

void AddCombo( CMFCPropertyGridProperty* pGroup,const TCHAR* strName,const TCHAR** strEnum,int iSize,int T_Value,const TCHAR* strDesc,BOOL bIsEdit /*= FALSE*/ )
{
	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty( strName, strEnum[T_Value], strDesc );
	for ( int i = 0; i < iSize; i++ )
	{
		pProp->AddOption( strEnum[i] );
	}
	pProp->AllowEdit( bIsEdit );
	pGroup->AddSubItem( pProp );
}
