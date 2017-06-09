// GetAngle.cpp : 实现文件
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "GetAngle.h"
#include "afxdialogex.h"


// CGetAngle 对话框

IMPLEMENT_DYNAMIC(CGetAngle, CDialog)

CGetAngle::CGetAngle(CWnd* pParent /*=NULL*/)
	: CDialog(CGetAngle::IDD, pParent)
	, angle(0)
{

}

CGetAngle::~CGetAngle()
{
}

void CGetAngle::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, angle);
	DDV_MinMaxInt(pDX, angle, 0, 360);
}


BEGIN_MESSAGE_MAP(CGetAngle, CDialog)
	ON_BN_CLICKED(IDOK, &CGetAngle::OnBnClickedOk)
END_MESSAGE_MAP()


// CGetAngle 消息处理程序


void CGetAngle::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CDialog::OnOK();
}
