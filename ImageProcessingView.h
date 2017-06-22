
// ImageProcessingView.h : CImageProcessingView ��Ľӿ�
//

#pragma once
#include "highgui.h"
#include <opencv2/opencv.hpp> 
#include "opencv.hpp"
#include "CvvImage.h"

class CImageProcessingView : public CScrollView
{
protected: // �������л�����
	CImageProcessingView();
	DECLARE_DYNCREATE(CImageProcessingView)

// ����
public:
	CImageProcessingDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CImageProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnReadimage();

public:
	IplImage* image;
	bool FLAG;
	afx_msg void OnImageinv();
	void UpdateWindow(void);
	afx_msg void OnRotateimage();
	afx_msg void OnMirror();
	afx_msg void OnFft();
	afx_msg void OnHistimage();
	afx_msg void OnPowerenhance();
	afx_msg void OnSobelimage();
	afx_msg void OnLaplaceenhance();
	afx_msg void OnMedianfilter();
	afx_msg void OnHuffmanRead();
	afx_msg void OnRoberts();
	afx_msg void OnSobel();
	afx_msg void OnPrewitt();
	afx_msg void OnLaplace();
	afx_msg void OnLineardetection();
public:
	IplImage* SearchLine(IplImage* img, double Through);
	void HoughLineDetect(IplImage* binaryimage, IplImage* lpDst, int threshold);
};

#ifndef _DEBUG  // ImageProcessingView.cpp �еĵ��԰汾
inline CImageProcessingDoc* CImageProcessingView::GetDocument() const
   { return reinterpret_cast<CImageProcessingDoc*>(m_pDocument); }
#endif

