#pragma once


// CGetAngle �Ի���

class CGetAngle : public CDialog
{
	DECLARE_DYNAMIC(CGetAngle)

public:
	CGetAngle(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGetAngle();

// �Ի�������
	enum { IDD = IDD_GetAngle };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int angle;
	afx_msg void OnBnClickedOk();
};
