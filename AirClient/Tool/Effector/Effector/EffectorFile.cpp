#include "stdafx.h"
#include "EffectorFile.h"
#include "EngineCamera.h"
#include "EngineMesh.h"

EffectorFile::EffectorFile(CTreeCtrl*	pTree):TreeObj(_T("EffectorFile"),NULL,pTree,enTOT_EffectorFile)
{
	m_bLoaded	=	false;
}

bool EffectorFile::New()
{
	Close();


	m_bLoaded	=	true;
	return	true;
}

bool EffectorFile::Open( const TCHAR* strName )
{
	if(strName==NULL)
		return	false;
	Close();

	//m_pTree->SetItemText(m_Item,strName);

	FILE*	pFile	=	_wfopen(strName,_T("rb"));
	if(pFile!=NULL){
		unsigned	long	uiVersion	=	'0FFE';
		fread(&uiVersion,sizeof(unsigned	long),1,pFile);
		if(uiVersion	!=	'0FFE'){
			fclose(pFile);
			return	false;
		}
		unsigned long uiSize	=	0;
		fseek(pFile,0,SEEK_END);
		uiSize	=	ftell(pFile);
		fseek(pFile,0,SEEK_SET);
		unsigned char*	pData	=	new unsigned char[uiSize];
		fread(pData,uiSize,1,pFile);
		fclose(pFile);

		unsigned char*	pTemp	=	pData;
		pTemp+=sizeof(unsigned long);
		Parse(pTemp);
		delete[] pData;
	}

	return	true;
}

bool EffectorFile::Save()
{
	//Close();

	return	true;
}

bool EffectorFile::SaveAs( const TCHAR* strName )
{
	FILE*	pFile	=	_wfopen(strName,_T("wb"));
	if(pFile!=NULL){
		unsigned long uiVersion	=	'0FFE';
		fwrite(&uiVersion,sizeof(unsigned	long),1,pFile);

		SaveChild(pFile);

		fclose(pFile);
	}

	return	true;
}

bool EffectorFile::ParseEffect(Effect*	p, unsigned char* pData )
{


	return	true;
}

void EffectorFile::Close()
{
	//if(m_bLoaded){
		DestroyAllChild();
	//	m_bLoaded	=	false;
	//}
}

void EffectorFile::AddEffect( const TCHAR* strName )
{
	if(strName==NULL){
		return;
	}
	Effect*	pEffect	=	new Effect(strName,this);
	pEffect->Create();
	AddChild(pEffect);
}

EffectorFile::~EffectorFile()
{
	Destroy();
}

void EffectorFile::AddCamera( const TCHAR* strName )
{
	if(strName==NULL){
		return;
	}
	ECamera*	p	=	new ECamera(strName,this);
	p->Create();
	AddChild(p);
}

void EffectorFile::AddMesh( const TCHAR* strName )
{
	if(strName==NULL){
		return;
	}
	Mesh*	p	=	new Mesh(strName,this);
	p->Create();
	AddChild(p);
}

void EffectorFile::DrawActiveEffect()
{
	std::vector<TreeObj*>	vecObj	=	GetChildByType(enTOT_Effect);
	if(vecObj.empty())
		return;
	TreeObj*	pEffect	=	NULL;
	int iSize	=	vecObj.size();
	for(int i=0;i<iSize;i++){
		if(vecObj[i]->IsEnableActive()){
			pEffect	=	vecObj[i];
			break;
		}
	}

	if(pEffect!=NULL){
		((Effect*)pEffect)->Draw();
	}
}
