// GetAngle.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "GetAngle.h"
#include "afxdialogex.h"


// CGetAngle �Ի���

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


// CGetAngle ��Ϣ�������


void CGetAngle::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CDialog::OnOK();
}
