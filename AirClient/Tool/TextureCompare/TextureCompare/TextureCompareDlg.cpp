
// TextureCompareDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TextureCompare.h"
#include "TextureCompareDlg.h"
#include "afxdialogex.h"
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <list>
#include <functional>  
#include <vector>
#include "d3d9.h"
#include "d3dx9.h"

IDirect3D9* g_pD3D=NULL;
IDirect3DDevice9* g_pd3dDevice=NULL;

#pragma comment(lib,"d3d9")
#pragma comment(lib,"d3dx9")

std::wstring strFileType[]={
	L"BMP",
	L"JPG",
	L"TGA",
	L"PNG",
	L"DDS",
	L"PPM",
	L"DIB",
	L"HDR",       //high dynamic range formats
	L"PFM",       //
};

std::tr1::unordered_map<D3DFORMAT,std::wstring> strTextureFormat;
std::tr1::unordered_map<int,std::wstring> strTextureSize;
#define INSERT_TEXTURE_FORMAT(x)	strTextureFormat[x]	=	L#x;


int iTextureNameListSortOrder[8]={
	0,0,0,0,
	0,0,0,0
};
int iTextureCompareListSortOrder[2]={
	0,0
};


void InitString(){
	INSERT_TEXTURE_FORMAT(D3DFMT_UNKNOWN);
	INSERT_TEXTURE_FORMAT(D3DFMT_R8G8B8              );
	INSERT_TEXTURE_FORMAT(D3DFMT_A8R8G8B8            );
	INSERT_TEXTURE_FORMAT(D3DFMT_X8R8G8B8            );
	INSERT_TEXTURE_FORMAT(D3DFMT_R5G6B5              );
	INSERT_TEXTURE_FORMAT(D3DFMT_X1R5G5B5            );
	INSERT_TEXTURE_FORMAT(D3DFMT_A1R5G5B5            );
	INSERT_TEXTURE_FORMAT(D3DFMT_A4R4G4B4            );
	INSERT_TEXTURE_FORMAT(D3DFMT_R3G3B2              );
	INSERT_TEXTURE_FORMAT(D3DFMT_A8                  );
	INSERT_TEXTURE_FORMAT(D3DFMT_A8R3G3B2            );
	INSERT_TEXTURE_FORMAT(D3DFMT_X4R4G4B4            );
	INSERT_TEXTURE_FORMAT(D3DFMT_A2B10G10R10         );
	INSERT_TEXTURE_FORMAT(D3DFMT_A8B8G8R8            );
	INSERT_TEXTURE_FORMAT(D3DFMT_X8B8G8R8            );
	INSERT_TEXTURE_FORMAT(D3DFMT_G16R16              );
	INSERT_TEXTURE_FORMAT(D3DFMT_A2R10G10B10         );
	INSERT_TEXTURE_FORMAT(D3DFMT_A16B16G16R16        );
	INSERT_TEXTURE_FORMAT(D3DFMT_A8P8                );
	INSERT_TEXTURE_FORMAT(D3DFMT_P8                  );
	INSERT_TEXTURE_FORMAT(D3DFMT_L8                  );
	INSERT_TEXTURE_FORMAT(D3DFMT_A8L8                );
	INSERT_TEXTURE_FORMAT(D3DFMT_A4L4                );
	INSERT_TEXTURE_FORMAT(D3DFMT_V8U8                );
	INSERT_TEXTURE_FORMAT(D3DFMT_L6V5U5              );
	INSERT_TEXTURE_FORMAT(D3DFMT_X8L8V8U8            );
	INSERT_TEXTURE_FORMAT(D3DFMT_Q8W8V8U8            );
	INSERT_TEXTURE_FORMAT(D3DFMT_V16U16              );
	INSERT_TEXTURE_FORMAT(D3DFMT_A2W10V10U10         );
	INSERT_TEXTURE_FORMAT(D3DFMT_UYVY                );
	INSERT_TEXTURE_FORMAT(D3DFMT_R8G8_B8G8           );
	INSERT_TEXTURE_FORMAT(D3DFMT_YUY2                );
	INSERT_TEXTURE_FORMAT(D3DFMT_G8R8_G8B8           );
	INSERT_TEXTURE_FORMAT(D3DFMT_DXT1                );
	INSERT_TEXTURE_FORMAT(D3DFMT_DXT2                );
	INSERT_TEXTURE_FORMAT(D3DFMT_DXT3                );
	INSERT_TEXTURE_FORMAT(D3DFMT_DXT4                );
	INSERT_TEXTURE_FORMAT(D3DFMT_DXT5                );
	INSERT_TEXTURE_FORMAT(D3DFMT_D16_LOCKABLE        );
	INSERT_TEXTURE_FORMAT(D3DFMT_D32                 );
	INSERT_TEXTURE_FORMAT(D3DFMT_D15S1               );
	INSERT_TEXTURE_FORMAT(D3DFMT_D24S8               );
	INSERT_TEXTURE_FORMAT(D3DFMT_D24X8               );
	INSERT_TEXTURE_FORMAT(D3DFMT_D24X4S4             );
	INSERT_TEXTURE_FORMAT(D3DFMT_D16                 );
	INSERT_TEXTURE_FORMAT(D3DFMT_D32F_LOCKABLE       );
	INSERT_TEXTURE_FORMAT(D3DFMT_D24FS8              );
	INSERT_TEXTURE_FORMAT(D3DFMT_D32_LOCKABLE        );
	INSERT_TEXTURE_FORMAT(D3DFMT_S8_LOCKABLE         );
	INSERT_TEXTURE_FORMAT(D3DFMT_L16                 );
	INSERT_TEXTURE_FORMAT(D3DFMT_VERTEXDATA          );
	INSERT_TEXTURE_FORMAT(D3DFMT_INDEX16             );
	INSERT_TEXTURE_FORMAT(D3DFMT_INDEX32             );
	INSERT_TEXTURE_FORMAT(D3DFMT_Q16W16V16U16        );
	INSERT_TEXTURE_FORMAT(D3DFMT_MULTI2_ARGB8        );
	INSERT_TEXTURE_FORMAT(D3DFMT_R16F                );
	INSERT_TEXTURE_FORMAT(D3DFMT_G16R16F             );
	INSERT_TEXTURE_FORMAT(D3DFMT_A16B16G16R16F       );
	INSERT_TEXTURE_FORMAT(D3DFMT_R32F                );
	INSERT_TEXTURE_FORMAT(D3DFMT_G32R32F             );
	INSERT_TEXTURE_FORMAT(D3DFMT_A32B32G32R32F       );
	INSERT_TEXTURE_FORMAT(D3DFMT_CxV8U8              );

	for(int i=0;i<4096;i++){
		wchar_t str[32];
		wsprintf(str,L"%d",i);
		strTextureSize[i]	=	str;
	}
};

typedef std::vector<unsigned char>	FileData;
bool Load(const wchar_t* strName,FileData& data){
	FILE* pFile = NULL;
	_wfopen_s(&pFile,strName,L"rb");
	if(pFile==NULL)
		return false;
	fseek(pFile,0,SEEK_END);
	size_t uiSize = ftell(pFile);
	fseek(pFile,0,SEEK_SET);
	if(uiSize!=0){
		data.resize(uiSize);
		fread(&data[0],uiSize,1,pFile);
	}
	fclose(pFile);
	return true;
};

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int FileFormat	=	0;
int Width		=	0;
int Height		=	0;
int WH			=	0;
int Format		=	0;
int	Type		=	0;
int Color		=	0;
int Brightness	=	0;
int	MinWeight	=	95;
float fTotal	=	0.0f;
float vb[12]={
	-1,1,
	1,1,
	-1,-1,

	-1,-1,
	1,1,
	1,-1
};

struct TextureInfo{
	TextureInfo(){
		pTexture=NULL;
		memset(&imgInfo,0,sizeof(imgInfo));
	};
	void	LoadTexture(){
		FileData data ;
		if(!Load(strName.c_str(),data))
			return;
		D3DXGetImageInfoFromFileInMemory(&data[0],data.size(),&imgInfo);

		//D3DXCreateTextureFromFileInMemory(g_pd3dDevice,&data[0],data.size(),&pTexture);

	}
	void	UnLoadTexture(){
		if(pTexture){
			//pTexture->Release();
			pTexture=NULL;
		}
	}
	float	Compare(const TextureInfo& info){
		float weight	=0;
		
		if(imgInfo.Width	>	info.imgInfo.Width){
			weight+=	Width*(float)info.imgInfo.Width/(float)imgInfo.Width;
		}else{
			weight+=	Width*(float)imgInfo.Width/(float)info.imgInfo.Width;
		}
		if(imgInfo.Height	>	info.imgInfo.Height){
			weight+=	Height*(float)info.imgInfo.Height/(float)imgInfo.Height;
		}else{
			weight+=	Height*(float)imgInfo.Height/(float)info.imgInfo.Height;
		}
		float	wh0	=	((float)imgInfo.Width/(float)imgInfo.Height);
		float	wh1	=	((float)info.imgInfo.Width/(float)info.imgInfo.Height);
		if(wh0 > wh1){
			weight+=	WH*wh1/wh0;
		}else{
			weight+=	WH*wh0/wh1;
		}

		weight	+=	Format*(imgInfo.Format	==	info.imgInfo.Format);

		weight	+=	Type*(imgInfo.ResourceType	==	info.imgInfo.ResourceType);

		weight	+=	FileFormat*(imgInfo.ImageFileFormat	==	info.imgInfo.ImageFileFormat);

		weight	+=	Color;
		weight	+=	Brightness;
		//g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,2,vb,8);
		

		return 100*weight/fTotal;
	}
	std::wstring		strName;
	IDirect3DTexture9*	pTexture;
	D3DXIMAGE_INFO		imgInfo;
	std::tr1::unordered_map<int,float>	weight;
};


typedef	std::vector<TextureInfo>					TextureInfoVector;
TextureInfoVector settex;

typedef	std::tr1::unordered_set<std::wstring>	wstrset;
typedef	std::tr1::unordered_map<std::wstring,int>	wstrmap;

struct MyData{
	CListCtrl *listctrl;
	int isub;
	int seq;
};


int CALLBACK CompareFunc(LPARAM lParam1,LPARAM lParam2,LPARAM lParamSort)
{
		MyData *p=(MyData *)lParamSort;
		CListCtrl* list =p->listctrl;
		int isub=p->isub;
		LVFINDINFO findInfo;
		findInfo.flags = LVFI_PARAM;
		findInfo.lParam = lParam1;
		int iItem1 = list->FindItem(&findInfo, -1);
		findInfo.lParam = lParam2;
		int iItem2 = list->FindItem(&findInfo, -1);
		wchar_t strItem1[512];
		list->GetItemText(iItem1,isub,strItem1,512);
		wchar_t strItem2[512];
		list->GetItemText(iItem2,isub,strItem2,512);
		int iSign = p->seq?1:-1;

		return iSign*wcscmp(strItem2, strItem1);
}



void	InitD3D(HWND hWnd){
	// Create the D3D object.
	if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return;

	// Set up the structure used to create the D3DDevice. Since we are now
	// using more complex geometry, we will create a device with a zbuffer.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof( d3dpp ) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// Create the D3DDevice
	if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice ) ) )
	{
		return;
	}


};

void	ReleaseD3D(){
	g_pd3dDevice->Release();
	g_pD3D->Release();
};



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTextureCompareDlg 对话框




CTextureCompareDlg::CTextureCompareDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTextureCompareDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	bLoad	=	false;
	m_BMP	=	0;
	m_BMPCOMPARE	=	0;
	bUpdateCompare	=	true;
}

void CTextureCompareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTextureCompareDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTextureCompareDlg::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST_TEXTURE_NAME, &CTextureCompareDlg::OnLvnItemActivateListTextureName)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_TEXTURE_NAME, &CTextureCompareDlg::OnHdnItemclickListTextureName)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_TEXTURE_COMPARE, &CTextureCompareDlg::OnHdnItemclickListTextureCompare)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_TEXTURE_NAME, &CTextureCompareDlg::OnLvnColumnclickListTextureName)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_TEXTURE_COMPARE, &CTextureCompareDlg::OnLvnColumnclickListTextureCompare)
END_MESSAGE_MAP()


// CTextureCompareDlg 消息处理程序

BOOL CTextureCompareDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//CMFCEditBrowseCtrl* pEdit =  (CMFCEditBrowseCtrl*)GetDlgItem(IDC_MFCEDITBROWSE1);
	//pEdit->
	InitD3D(GetSafeHwnd());

	

	FileFormat	=	GetPrivateProfileInt(L"Weight",L"FileFormat",0,L".\\compare.ini");
	Width		=	GetPrivateProfileInt(L"Weight",L"Width",0,L".\\compare.ini");
	Height		=	GetPrivateProfileInt(L"Weight",L"Height",0,L".\\compare.ini");
	WH			=	GetPrivateProfileInt(L"Weight",L"WH",0,L".\\compare.ini");
	Format		=	GetPrivateProfileInt(L"Weight",L"Format",0,L".\\compare.ini");
	Type		=	GetPrivateProfileInt(L"Weight",L"Type",0,L".\\compare.ini");
	Color		=	GetPrivateProfileInt(L"Weight",L"Color",0,L".\\compare.ini");
	Brightness	=	GetPrivateProfileInt(L"Weight",L"Brightness",0,L".\\compare.ini");
	MinWeight	=	GetPrivateProfileInt(L"Weight",L"MinWeight",0,L".\\compare.ini");

	fTotal	=	FileFormat+Width+Height+WH+Format+Type+Color+Brightness;

	CListCtrl* pCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_TEXTURE_NAME);
	pCtrl->InsertColumn( 0, _T("Name"), LVCFMT_LEFT, 450 ); 
	pCtrl->InsertColumn( 1, _T("File"), LVCFMT_LEFT, 50 ); 
	pCtrl->InsertColumn( 2, _T("Width"), LVCFMT_LEFT, 50 ); 
	pCtrl->InsertColumn( 3, _T("Height"), LVCFMT_LEFT, 50 ); 
	pCtrl->InsertColumn( 4, _T("Depth"), LVCFMT_LEFT, 50 ); 
	pCtrl->InsertColumn( 5, _T("Format"), LVCFMT_LEFT, 150 ); 
	pCtrl->InsertColumn( 6, _T("Mipmap"), LVCFMT_LEFT, 50 ); 
	pCtrl->InsertColumn( 7, _T("Type"), LVCFMT_LEFT, 50 ); 
	//pCtrl->InsertColumn( 0, _T("WH"), LVCFMT_LEFT, 100 ); 
	//pCtrl->InsertColumn( 0, _T("Color"), LVCFMT_LEFT, 100 ); 
	//pCtrl->InsertColumn( 0, _T("Brightness"), LVCFMT_LEFT, 100 ); 

	CListCtrl* pCtrl2 = (CListCtrl*)GetDlgItem(IDC_LIST_TEXTURE_COMPARE);
	pCtrl2->InsertColumn(0, _T("Name"), LVCFMT_LEFT, 450 ); 
	pCtrl2->InsertColumn(1, _T("Similarity"), LVCFMT_LEFT,150 ); 
	InitString();
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTextureCompareDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTextureCompareDlg::OnPaint()
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

		CRect rt;
		GetDlgItem(IDC_PICTURE)->GetWindowRect(rt);
		ScreenToClient(rt);
		CClientDC dc(this);
		CPictureHolder ShowBmp;

		ShowBmp.CreateFromBitmap(m_BMP);
		ShowBmp.Render ((CDC*)&dc,&rt,0);

		GetDlgItem(IDC_PICTURE_COMPARE)->GetWindowRect(rt);
		ScreenToClient(rt);
		CPictureHolder ShowBmp2;

		ShowBmp2.CreateFromBitmap(m_BMPCOMPARE);
		ShowBmp2.Render ((CDC*)&dc,&rt,0);
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTextureCompareDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void ToLower(std::wstring& str){
	int iSize = str.size();
	for(int i=0;i<iSize;i++){
		str[i]	=	tolower(str[i]);
	}
};
bool EndWith(const std::wstring& strSrc,std::wstring& strCmp){
	int iSize = strCmp.size();
	int iSrcSize = strSrc.size();
	if(iSrcSize<iSize || iSize==0)
		return false;
	return memcmp(&strSrc[iSrcSize - iSize],&strCmp[0],sizeof(wchar_t)*iSize)==0;
};

std::wstring strCmpArray[]={
	L".tga",
	L".dds",
	L".png",
	L".bmp",
	L".jpg",
	L".jpeg",
};

void	FindAllTextureName(TextureInfoVector& mapTexName,std::wstring currentPath){
	WIN32_FIND_DATA FindFileData;  
	currentPath+=L"\\";
	std::wstring	findfile = currentPath+L"*";

	std::wstring strtemp;
	HANDLE hFile;

	DWORD errorcode = 0;

	
	{
		hFile=FindFirstFile(findfile.c_str(),&FindFileData);
		while(hFile!=INVALID_HANDLE_VALUE)
		{
			if(	wcscmp(FindFileData.cFileName,L".")!=0	&&
				wcscmp(FindFileData.cFileName,L"..")!=0)
			{
				strtemp=currentPath+FindFileData.cFileName;
				if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
					FindAllTextureName(mapTexName,strtemp);
				}else	if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE){
					std::wstring strfile = FindFileData.cFileName;
					ToLower(strfile);

					for(int i=0;i<6;i++){
						
						if(EndWith(strfile,strCmpArray[i])){
							TextureInfo info;
							info.strName	=strtemp;
							mapTexName.push_back(info);
						}
					}
					
				}
			}
			if(!FindNextFile(hFile,&FindFileData))
				break;
		}

		FindClose(hFile);
	}

}



void CTextureCompareDlg::OnBnClickedOk()
{
	settex.clear();
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();

	bLoad	=	true;

	wchar_t str[512];
	GetDlgItemText(IDC_MFCEDITBROWSE1,str,512);

	
	FindAllTextureName(settex,str);

	SetDlgItemText(IDC_STATIC_TOTAL,strTextureSize[settex.size()].c_str());
	SetDlgItemText(IDC_STATIC_COMPLATE,strTextureSize[0].c_str());
	CProgressCtrl* pPC = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1); 
	if(pPC!=NULL){
		pPC->SetRange(0,settex.size());
		pPC->SetPos(0);
	}

	int iSize= settex.size();
	for(int i=0;i<iSize;i++){
		TextureInfo& info = settex[i];
		info.LoadTexture();
		if(pPC!=NULL){
			pPC->SetPos(i);
			SetDlgItemText(IDC_STATIC_COMPLATE,strTextureSize[i].c_str());
		}
	};
	for(int i=0;i<iSize;i++){
		TextureInfo& info = settex[i];
#if 1
		for(int j=i+1;j<iSize;j++){
			TextureInfo& dstInfo = settex[j];
			float w = info.Compare(dstInfo);
			if(w > 0){
				info.weight[j]=w;
			}
		}

		
#endif

		if(pPC!=NULL){
			pPC->SetPos(i);
			SetDlgItemText(IDC_STATIC_COMPLATE,strTextureSize[i].c_str());
		}
	}
	if(pPC!=NULL){
		pPC->SetPos(settex.size());
		SetDlgItemText(IDC_STATIC_COMPLATE,strTextureSize[settex.size()].c_str());
	}
	CListCtrl* pCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_TEXTURE_NAME);
	pCtrl->DeleteAllItems();

	for(int i=0;i<settex.size();i++){
		TextureInfo& info = settex[i];
		int iItemID = pCtrl->InsertItem(i,info.strName.c_str());
		pCtrl->SetItemText(iItemID,1,strFileType[info.imgInfo.ImageFileFormat].c_str());
		pCtrl->SetItemText(iItemID,2,strTextureSize[info.imgInfo.Width].c_str());
		pCtrl->SetItemText(iItemID,3,strTextureSize[info.imgInfo.Height].c_str());
		pCtrl->SetItemText(iItemID,4,strTextureSize[info.imgInfo.Depth].c_str());
		pCtrl->SetItemText(iItemID,5,strTextureFormat[info.imgInfo.Format].c_str());
		pCtrl->SetItemText(iItemID,6,strTextureSize[info.imgInfo.MipLevels].c_str());
		pCtrl->SetItemText(iItemID,7,L"2D");
		pCtrl->SetItemData(iItemID,(DWORD_PTR)&info);
		//pCtrl->SetItemText(i,6,settex[i].strName.c_str());
		//pCtrl->SetItemText(i,7,settex[i].strName.c_str());
	}

	bLoad	=	false;
	pCtrl->SetHotItem(0);

	AfxMessageBox(L"Sreach Complate!\n");
}


void CTextureCompareDlg::OnLvnItemActivateListTextureName(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	*pResult = 0;
}


void CTextureCompareDlg::OnHdnItemclickListTextureName(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);

	// TODO: 在此添加控件通知处理程序代码
	CListCtrl* pCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_TEXTURE_NAME);
	TextureInfo* pInfo = (TextureInfo*)pCtrl->GetItemData(phdr->iItem);
	if(pInfo!=NULL&& !bLoad){
		bUpdateCompare	=	false;

		CListCtrl* pCtrl2 = (CListCtrl*)GetDlgItem(IDC_LIST_TEXTURE_COMPARE);
		pCtrl2->DeleteAllItems();
		int iCount = 0;
		std::tr1::unordered_map<int,float>::iterator i = pInfo->weight.begin();
		for(;i!=pInfo->weight.end();i++){
			TextureInfo& info = settex[i->first];
			int iItemID = pCtrl2->InsertItem(iCount++,info.strName.c_str());
			int iValue = i->second;
			pCtrl2->SetItemText(iItemID,1,strTextureSize[iValue].c_str());
			pCtrl2->SetItemData(iItemID,(DWORD_PTR)&info);
		}
		//m_BMP.DeleteObject();
		DeleteObject(m_BMP);
		D3DXIMAGE_INFO imginfo;
		D3DXGetImageInfoFromFile(pInfo->strName.c_str(),&imginfo);
		int w	=	imginfo.Width;
		int h	=	imginfo.Height;

		IDirect3DTexture9* pTexture=NULL;
		D3DXCreateTextureFromFileEx(g_pd3dDevice,pInfo->strName.c_str(),w,h,1,0,D3DFMT_A8R8G8B8,D3DPOOL_SYSTEMMEM,D3DX_FILTER_NONE,D3DX_FILTER_NONE,0,&imginfo,0,&pTexture);
		//CDC* dc	=	GetDlgItem(IDC_PICTURE)->GetDC();


		

		RECT rect;
		GetDlgItem(IDC_PICTURE)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		//rect.right	=	rect.left	+	w;
		//rect.bottom	=	rect.top	+	h;
		//GetDlgItem(IDC_PICTURE)->MoveWindow(&rect);
		D3DLOCKED_RECT r;
		if(SUCCEEDED(pTexture->LockRect(0,&r,0,D3DLOCK_READONLY))){
			m_BMP	=	CreateBitmap(w,h,1,32,r.pBits);
			//dc->StretchBlt(0,0,256,256,)
			pTexture->UnlockRect(0);
		}
		pTexture->Release();
		//CPicture* pPicture = (CPictureHolder*)GetDlgItem(IDC_STATIC4);

		bUpdateCompare	=	true;
		//RedrawWindow(&rect);
	}
	
	*pResult = 0;
}
void CTextureCompareDlg::OnHdnItemclickListTextureCompare(NMHDR *pNMHDR, LRESULT *pResult){
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CListCtrl* pCtrl = (CListCtrl*)GetDlgItem(IDC_LIST_TEXTURE_COMPARE);
	TextureInfo* pInfo = (TextureInfo*)pCtrl->GetItemData(phdr->iItem);
	if(pInfo!=NULL&& bUpdateCompare){
		//m_BMP.DeleteObject();
		DeleteObject(m_BMPCOMPARE);
		D3DXIMAGE_INFO imginfo;
		D3DXGetImageInfoFromFile(pInfo->strName.c_str(),&imginfo);
		int w	=	imginfo.Width;
		int h	=	imginfo.Height;

		IDirect3DTexture9* pTexture=NULL;
		D3DXCreateTextureFromFileEx(g_pd3dDevice,pInfo->strName.c_str(),w,h,1,0,D3DFMT_A8R8G8B8,D3DPOOL_SYSTEMMEM,D3DX_FILTER_NONE,D3DX_FILTER_NONE,0,&imginfo,0,&pTexture);
		//CDC* dc	=	GetDlgItem(IDC_PICTURE)->GetDC();




		RECT rect;
		GetDlgItem(IDC_PICTURE_COMPARE)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		//rect.right	=	rect.left	+	w;
		//rect.bottom	=	rect.top	+	h;
		//GetDlgItem(IDC_PICTURE_COMPARE)->MoveWindow(&rect);
		D3DLOCKED_RECT r;
		if(SUCCEEDED(pTexture->LockRect(0,&r,0,D3DLOCK_READONLY))){
			m_BMPCOMPARE	=	CreateBitmap(w,h,1,32,r.pBits);
			//dc->StretchBlt(0,0,256,256,)
			pTexture->UnlockRect(0);
		}
		pTexture->Release();

		RedrawWindow(&rect);

	}
	*pResult = 0;
};


void CTextureCompareDlg::OnLvnColumnclickListTextureName(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	MyData tmpp;

	tmpp.listctrl=(CListCtrl*)GetDlgItem(IDC_LIST_TEXTURE_NAME);


	tmpp.isub=pNMLV->iSubItem;
	int& order = iTextureNameListSortOrder[tmpp.isub];
	order++;
	order=order&0x1;
	tmpp.seq	=	order;

	tmpp.listctrl->SortItems(CompareFunc,(LPARAM)&tmpp);

	*pResult = 0;
}


void CTextureCompareDlg::OnLvnColumnclickListTextureCompare(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	MyData tmpp;

	tmpp.listctrl=(CListCtrl*)GetDlgItem(IDC_LIST_TEXTURE_COMPARE);


	tmpp.isub=pNMLV->iSubItem;
	int& order = iTextureCompareListSortOrder[tmpp.isub];
	order++;
	order=order&0x1;
	tmpp.seq	=	order;

	tmpp.listctrl->SortItems(CompareFunc,(LPARAM)&tmpp);
	*pResult = 0;
}
