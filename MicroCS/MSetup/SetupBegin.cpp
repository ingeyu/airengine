// SetupBegin.cpp : 实现文件
//

#include "stdafx.h"
#include "MSetup.h"
#include "SetupBegin.h"
#include "afxdialogex.h"


// CSetupBegin 对话框

IMPLEMENT_DYNAMIC(CSetupBegin, CDialogEx)

CSetupBegin::CSetupBegin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetupBegin::IDD, pParent)
{

}

CSetupBegin::~CSetupBegin()
{
}

void CSetupBegin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetupBegin, CDialogEx)
END_MESSAGE_MAP()


// CSetupBegin 消息处理程序
