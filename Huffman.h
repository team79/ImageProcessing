#pragma once


// CHuffman �Ի���

class CHuffman : public CDialogEx
{
	DECLARE_DYNAMIC(CHuffman)

public:
	CHuffman(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHuffman();

// �Ի�������
	enum { IDD = IDD_Huffman };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString filepath;
};
