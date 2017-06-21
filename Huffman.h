#pragma once


// CHuffman 对话框

class CHuffman : public CDialogEx
{
	DECLARE_DYNAMIC(CHuffman)

public:
	CHuffman(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHuffman();

// 对话框数据
	enum { IDD = IDD_Huffman };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString filepath;
};
