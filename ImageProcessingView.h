
// ImageProcessingView.h : CImageProcessingView 类的接口
//

#pragma once
#include "highgui.h"
#include <opencv2/opencv.hpp> 
#include "opencv.hpp"
#include "CvvImage.h"

class CImageProcessingView : public CScrollView
{
protected: // 仅从序列化创建
	CImageProcessingView();
	DECLARE_DYNCREATE(CImageProcessingView)

// 特性
public:
	CImageProcessingDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CImageProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // ImageProcessingView.cpp 中的调试版本
inline CImageProcessingDoc* CImageProcessingView::GetDocument() const
   { return reinterpret_cast<CImageProcessingDoc*>(m_pDocument); }
#endif

