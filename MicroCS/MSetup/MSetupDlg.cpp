
// MSetupDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "net/AirCommonNetClient.h"
#include "MSetup.h"
#include "MSetupDlg.h"
#include "afxdialogex.h"

#include "MNetData.h"
#include "mmsystem.h"
#pragma comment(lib,"winmm")

//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif


// CMSetupDlg 对话框

void	DownloadFunc(void*	p){
	CMSetupDlg* pDlg	=	(CMSetupDlg*)p;
	if(pDlg!=NULL){
		pDlg->ThreadFunc();
	}
}


CMSetupDlg::CMSetupDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMSetupDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pClient	=	NULL;
	m_Event		=	NULL;
	m_pLog		=	NULL;

	m_pNakedClinet		=	NULL;


	m_dwPathLength		=	0;
	memset(m_strSetupPath,0,sizeof(wchar_t)*1024);

	m_Total		=	100*104876;
	m_Complated	=	0;

	Air::Common::InitNet();
}

void CMSetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMSetupDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CMSetupDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CMSetupDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMSetupDlg 消息处理程序

BOOL CMSetupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_Event	=	CreateEvent(0,0,0,0);
	m_pLog	=	(CListBox*)GetDlgItem(IDC_LIST_LOG);

	if(m_pLog!=NULL){
		m_pLog->InsertString(0,L"开始安装");
	}
	wchar_t temp0[1024];
	swprintf_s(temp0,L"%stemp",m_strSetupPath);
	m_pNakedClinet	=	_wfopen(temp0,L"wb");


	Air::Common::NetClient::Info info;
	info.strIP		=	"127.0.0.1";
	info.usPort		=	54322;
	info.pListener	=	this;
	AString strName	=	"Downloader";
	m_pClient		=	new Air::Common::NetClient(strName,&info);
	m_pClient->AddRef();

	_beginthread(DownloadFunc,1048576,this);

	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMSetupDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMSetupDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMSetupDlg::OnBnClickedCancel()
{
	if(m_pNakedClinet!=NULL){
		fclose(m_pNakedClinet);
		m_pNakedClinet=NULL;
	}

	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CMSetupDlg::OnBnClickedOk()
{
	if(m_pNakedClinet!=NULL){
		fclose(m_pNakedClinet);
		m_pNakedClinet=NULL;
	}


	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

CMSetupDlg::~CMSetupDlg()
{
	if(m_pClient!=NULL){
		m_pClient->ReleaseRef();
		m_pClient=NULL;
	}
}

void CMSetupDlg::ThreadFunc()
{
	
	int iCount	=	0;
	while(!m_pClient->IsConnected()){
		if(m_pClient!=NULL){
			Air::Common::NetClient::Info	info;
			info.pListener	=	this;
			info.strIP		=	"10.240.38.103";
			info.usPort		=	54322;
			if(m_pLog!=NULL){
				m_pLog->InsertString(0,L"连接服务器中");
			}
			if(m_pClient->Connect(info)){
				if(m_pLog!=NULL){
					m_pLog->InsertString(0,L"连接服务器成功");
					m_pLog->InsertString(0,L"开始下载裸客户端");
				}
				enNetType	t=	enNT_FS_Hello;
				m_pClient->Send(&t,sizeof(t));
			}
		}
		Sleep(1000);
	}
	SYSTEMTIME startTime;
	GetLocalTime(&startTime);
	CProgressCtrl* pMain	=	(CProgressCtrl*)GetDlgItem(IDC_PROGRESS_MAIN);
	CProgressCtrl* pSub		=	(CProgressCtrl*)GetDlgItem(IDC_PROGRESS_SUB);

	U32			begin=timeGetTime();
	//SetEvent(m_Event);
	//下载客户端
	while(1){
		if(m_pNakedClinet==NULL){
			break;
		}else{
			U32		end		=	timeGetTime();
			U32	usedTime	=	(end	-	begin)*0.001f;
			U32	usedHour	=	usedTime/3600;
			U32	usedMin		=	(usedTime%3600)/60;
			U32	usedSec		=	(usedTime%3600)%60;

			

			wchar_t strTime[1024];
			if(m_Complated==0){
				swprintf_s(strTime,L"0/2 已使用%02d:%02d:%02d 剩余??:??:??",usedHour,usedMin,usedSec);
			}else{
				double	needTime	=	usedTime*((double)m_Total/(double)m_Complated) - usedTime;
				U32	uiNeedTime		=	needTime;
				U32	needHour		=	uiNeedTime/3600;
				U32	needMin			=	(uiNeedTime%3600)/60;
				U32	needSec			=	(uiNeedTime%3600)%60;
				swprintf_s(strTime,L"0/2 已使用%02d:%02d:%02d 剩余%02d:%02d:%02d",usedHour,usedMin,usedSec,needHour,needMin,needSec);
			}
			//float	f	=	m_Complated
			GetDlgItem(IDC_STATIC_TIME)->SetWindowTextW(strTime);

			CProgressCtrl* pSub	=	(CProgressCtrl*)GetDlgItem(IDC_PROGRESS_SUB);
			float	fPercent	=	100*(float)m_Complated/(float)m_Total;
			pSub->SetPos((U32)fPercent);
		}
		Sleep(100);
	}
	pSub->SetPos(100);
	pMain->SetPos(25);


	//下载客户端
}

U1 CMSetupDlg::OnConnected( U32 socket,CAString& strIP,CAString& strPort )
{
	
	return true;
}

U1 CMSetupDlg::OnClose( U32 uiSocket )
{
	//if(m_pLog!=NULL){
	//	m_pLog->InsertString(0,L"与服务器断开连接");
	//}
	return true;
}

U1 CMSetupDlg::OnReceive( U32 uiSocket,AChar* pData,U32 uiSize )
{
	NetHeader*	pHeader	=	(NetHeader*)pData;
	switch(pHeader->t){
		case	enNT_Return:{
			NT_Return* pRet	=	(NT_Return*)pData;
			if(pRet->lastType	==	enNT_FS_Hello){
				NT_ReturnT<NT_SF_Hello>* pHello	=	(NT_ReturnT<NT_SF_Hello>*)pData;
				memcpy(m_PkgSize,pHello->data.pkgSize,sizeof(U32)*16);
				m_Total	=	m_PkgSize[15];
			}

			NT_Data<FileDataInfo> data(enNT_FS_LoadFile);
			data.t		=	enNT_FS_LoadFile;
			
			data.data.idx		=	15;
			data.data.uiOffset	=	0;
			data.data.uiSize	=	m_PkgSize[15];
			m_pClient->Send(&data,sizeof(data));

						  }break;
		case	enNT_SF_FileData:{
			NT_Data<NT_FS_FileData>* pFileData	=	(NT_Data<NT_FS_FileData>*)pData;
			OnDownloading(&pFileData->data);
						  }break;
	}
	return true;
}

void CMSetupDlg::OnDownloading( NT_FS_FileData* pFileData )
{

	long long uiOffset	=	pFileData->uiOffset;
	_fseeki64(m_pNakedClinet,uiOffset,SEEK_SET);
	m_Complated+=pFileData->uiSize;
	fwrite(pFileData->data,pFileData->uiSize,1,m_pNakedClinet);
	if(pFileData->uiComplated){
		if(m_pNakedClinet!=NULL){
			fclose(m_pNakedClinet);
			m_pNakedClinet=NULL;
		}
		if(m_pLog!=NULL){
			m_pLog->InsertString(0,L"裸客户端下载完成");
		}

	}

}
