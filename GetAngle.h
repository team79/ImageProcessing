#pragma once


// CGetAngle 对话框

class CGetAngle : public CDialog
{
	DECLARE_DYNAMIC(CGetAngle)

public:
	CGetAngle(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGetAngle();

// 对话框数据
	enum { IDD = IDD_GetAngle };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int angle;
	afx_msg void OnBnClickedOk();
};
