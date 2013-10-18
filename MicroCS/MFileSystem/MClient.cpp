#include "MClient.h"
#include "MFileSystem.h"
#include "MFile.h"

AString	MClient::ProductTypeName="MClient";
MClient::MClient( CAString& strName,Info* pInfo ):Air::Common::IProduct(strName),m_FSWaitClient(strName.c_str())
{
	if(pInfo!=NULL)
		m_ProcessID	=	*pInfo;
	m_pFile	=	NULL;
	m_bProcessExist	=	0;
}

U1 MClient::Create()
{
	Air::FileMapping::Info	info;
	info.type	=	Air::FileMapping::enFMT_Open;
	info.uiFileSize	=	16*1048576;
	m_pFile	=	MFileSystem::GetSingleton()->CreateProduct<Air::FileMapping>(m_strProductName+"FileMapping",&info);
	StartThread();
	return	true;
}

U1 MClient::Destroy()
{
	StopThreadWaitForExit();
	SAFE_RELEASE_REF(m_pFile);
	return true;
}


void MClient::OnFileLoadComplated( U32 uiOffset,MFile* pFile )
{
	CSInfo*	pInfo		=	(CSInfo*)m_pFile->GetLockedBuffer();

	U8* pBuffer = (U8*)pInfo;//+1;
	pBuffer+=sizeof(CSInfo);
	
	memcpy(pBuffer,pFile->GetData(),pFile->GetDataSize());//pBuffer,0xffffffff);
	pInfo->ret		=	1;
	pInfo->uiSize	=	pFile->GetDataSize();
	pInfo->mark		=	0xFFFFFFFF;
}

void MClient::OnFileLoadFailed( U32 uiOffset,MFile* pFile )
{
	CSInfo*	pInfo		=	(CSInfo*)m_pFile->GetLockedBuffer();
	pInfo->ret		=	0;
	pInfo->uiSize	=	0;
	pInfo->mark		=	0xFFFFFFFF;
}

void MClient::Update( float fTimeDelta )
{
	m_FSWaitClient.Wait(100);
	CSInfo*	pInfo		=	(CSInfo*)m_pFile->GetLockedBuffer();
	if(pInfo->mark==1){
		LoadFile(pInfo->FileID);
	}
}

void MClient::LoadFile( U64 fileID )
{
	MFile*	pFile	=	MFileSystem::GetSingleton()->CreateMFile(fileID);
	if(pFile!=NULL){
		NotifyInfo info;
		info.pClient	=	this;
		info.uiOffset	=	0;
		pFile->AddNotify(info);
		pFile->ReleaseRef();
	}
}

bool MClient::RepetitionRun()
{
	Update(0);
	return true;
}

void MClient::SetProcessExistFrame( U32 iFrame )
{
	m_bProcessExist	=	iFrame;
}

U1 MClient::IsProcessExist(U32 iFrame)
{
	return iFrame==m_bProcessExist;
}
