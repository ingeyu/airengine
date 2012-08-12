#ifndef EngineCommon_h__
#define EngineCommon_h__

enum	enumTreeObjType{
	enTOT_Unknown,
	enTOT_RState,
	enTOT_DState,
	enTOT_BState,
	enTOT_SState,
	enTOT_VShader,
	enTOT_GShader,
	enTOT_PShader,
	enTOT_CShader,
	enTOT_HShader,
	enTOT_DShader,
	enTOT_ConstantBuffer,
	enTOT_Pass,
	enTOT_Texture,
	enTOT_TextureRef,
	enTOT_Mesh,
	enTOT_Model,
	enTOT_ModelRef,
	enTOT_RenderTexture,
	enTOT_RenderTarget,
	enTOT_Phase,
	enTOT_Effect,
	enTOT_Camera,
	enTOT_CameraRef,
	enTOT_EffectorFile,
	enTOT_MAX
};

template<typename T>
void AddMember(CMFCPropertyGridProperty* pGroup,const TCHAR* strName,const T& T_Value,const TCHAR*	strDesc,BOOL	bIsEdit){
	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty( (strName), (_variant_t) T_Value, strDesc );
	pProp->AllowEdit( bIsEdit );
	pGroup->AddSubItem( pProp );
}
CMFCPropertyGridProperty*	AddGroup(CMFCPropertyGridProperty* pGroup,const TCHAR* strName);
void	AddMember(CMFCPropertyGridProperty* pGroup,const TCHAR* strName,const Air::Float3& v,BOOL	bEdit	=	FALSE);
void	AddMember(CMFCPropertyGridProperty* pGroup,const TCHAR* strName,const Air::Float4& v,BOOL	bEdit	=	FALSE);
void	AddMember(CMFCPropertyGridProperty* pGroup,const TCHAR* strName,const Air::BoundingBox& b,BOOL bEdit	=	FALSE);
//void	AddMember(CMFCPropertyGridProperty* pGroup,const TCHAR* strName,const TCHAR* strValue,BOOL bEdit	=	FALSE);
void	AddCombo(CMFCPropertyGridProperty* pGroup,const TCHAR* strName,const TCHAR** strEnum,int iSize,int T_Value,const TCHAR* strDesc,BOOL bIsEdit	=	FALSE);

std::wstring	GetNameString(enumTreeObjType	val);

std::wstring	GetNameString(Air::Client::enumTextureFormat	val);
std::wstring	GetNameString(Air::Client::enumTextureType		val);

class	TreeObj{
public:
	TreeObj(const TCHAR*	strName,TreeObj* parent,CTreeCtrl*	pTree,enumTreeObjType	t	=	enTOT_Unknown);
	virtual	~TreeObj();
	std::wstring	GetName();
	void			SetName(const TCHAR*	str);
	HTREEITEM		GetItem();
	enumTreeObjType	GetType();
	void			SetType(enumTreeObjType	t);
	CTreeCtrl*		GetTree();
	void			DeleteSelf();
	TreeObj*		GetParent();
	virtual	bool	Create();
	virtual	bool	Destroy();
	virtual	void	DestroyChild(TreeObj*	pChild);
	virtual	void	DestroyAllChild();
	virtual	void	RemoveChild(TreeObj*	pChild);
	virtual	void	AddChild(TreeObj*	pChild);
	virtual	TreeObj*	AddChild(const TCHAR*	strName,enumTreeObjType	t);
	virtual	bool	ReLoad();

	virtual	void	SaveToFile(FILE*	pFile);
	virtual	void	Parse(unsigned char*& pData);

	bool			IsEnableEdit();
	bool			IsEnableBind();
	bool			IsEnableActive();
	bool			IsResource();
	void			SetBindObj(TreeObj*	pObj);
	TreeObj*		GetBindObj();
	void				SetResourceName(const std::wstring&	strName);
	const std::wstring&	GetResourceName();
	std::vector<TreeObj*>	GetChildByType(enumTreeObjType	t);
	TreeObj*				GetChild(enumTreeObjType	t,unsigned long uiIndex	=	0);
	unsigned int	GetChildCountByType(enumTreeObjType	t);

	static	void			WriteString(const std::wstring&	str,FILE*	pFile);
	static	void			ReadString(std::wstring&	str,unsigned char*&	pData);
	template<typename T>
	static	void			Write(const T& val,FILE*	pFile){
		fwrite(&val,sizeof(T),1,pFile);
	};
	template<typename T>
	static	T	Read(unsigned char*&	pData){
		T t	=	*(T*)pData;
		pData+=sizeof(T);
	};

	virtual	void			OnShowProperty(CMFCPropertyGridProperty*	pGroup);
	virtual	void			OnPropertyChanged(CMFCPropertyGridProperty*	pProperty);
protected:
	virtual	void	ParseSelf(unsigned char*&	pData);
	virtual	void	ParseChild(unsigned char*& pData);
	virtual	void	SaveSelf(FILE*	pFile);
	virtual	void	SaveChild(FILE*	pFile);

	
protected:
	HTREEITEM		m_Item;
	TreeObj*		m_pParent;
	CTreeCtrl*		m_pTree;
	enumTreeObjType	m_Type;
	std::vector<TreeObj*>	m_vecChild;
	bool			m_bEnableEdit;
	bool			m_bEnableBind;
	bool			m_bEnableActive;
	bool			m_bIsResource;
	TreeObj*		m_pBindObj;
	std::wstring	m_strResourceName;
};




#endif // EngineCommon_h__
