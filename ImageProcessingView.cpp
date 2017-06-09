
// ImageProcessingView.cpp : CImageProcessingView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"
#include "ImageProcessingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessingView

IMPLEMENT_DYNCREATE(CImageProcessingView, CScrollView)

BEGIN_MESSAGE_MAP(CImageProcessingView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageProcessingView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_ReadImage, &CImageProcessingView::OnReadimage)
	ON_COMMAND(ID_ImageInv, &CImageProcessingView::OnImageinv)
END_MESSAGE_MAP()

// CImageProcessingView 构造/析构

CImageProcessingView::CImageProcessingView()
{
	// TODO: 在此处添加构造代码

}

CImageProcessingView::~CImageProcessingView()
{
	if(image != NULL )	
		cvReleaseImage(&image);
}

BOOL CImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	FLAG = false;
	image = NULL;
	return CScrollView::PreCreateWindow(cs);
}

// CImageProcessingView 绘制

void CImageProcessingView::OnDraw(CDC* pDC)
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//CBitmap bitmap;     //定义位图变量
	//bitmap.LoadBitmap(IDB_CLASS_VIEW);  //获得位图ID
	//BITMAP bmp;
	// bitmap.GetBitmap(&bmp);
	//CDC dc;
	//dc.CreateCompatibleDC(pDC);         //创建DC
	//dc.SelectObject(&bitmap);         //选择DC设备描述表
	//CRect rect;
	//GetClientRect(&rect);
	//pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);

	//HRESULT hr;
 //    CFile file;
 //    file.Open("F:\\813358355578758264.bmp", CFile::modeRead | CFile::shareDenyNone ); // 读入文件内容
 //    DWORD dwSize = file.GetLength();
 //    HGLOBAL hMem = ::GlobalAlloc( GMEM_MOVEABLE, dwSize );
 //    LPVOID lpBuf = ::GlobalLock( hMem );
 //    file.Read( lpBuf, dwSize );
 //    file.Close();
 //    ::GlobalUnlock( hMem );
 //
 //    IStream * pStream = NULL;
 //    IPicture * pPicture = NULL;
 //
 //    // 由HGLOBAL 得到IStream，参数TRUE 表示释放IStream 的同时，释放内存
 //    hr = ::CreateStreamOnHGlobal( hMem, TRUE, &pStream );
 //    ASSERT ( SUCCEEDED(hr) );
 //
 //    hr = ::OleLoadPicture( pStream, dwSize, TRUE, IID_IPicture, ( LPVOID * )&pPicture );
 //    ASSERT(hr==S_OK);
 //
 //    long nWidth,nHeight; // 宽高，MM_HIMETRIC 模式，单位是.01毫米
 //    pPicture->get_Width( &nWidth ); // 宽
 //    pPicture->get_Height( &nHeight ); // 高
 //    ////////原大显示//////
 //    CSize sz( nWidth, nHeight );
 //    pDC->HIMETRICtoDP( &sz ); // 转换MM_HIMETRIC 模式单位为MM_TEXT 像素单位
 //    pPicture->Render(pDC->m_hDC,0,0,sz.cx,sz.cy,
 //                  0,nHeight,nWidth,-nHeight,NULL);
 //
     ////////按窗口尺寸显示////////
     // CRect rect; GetClientRect(&rect);
     // pPicture->Render(pDc->m_hDC,0,0,rect.Width(),rect.Height(),
     //   0,nHeight,nWidth,-nHeight,NULL);
/////////////////////////////////
// 
//     if ( pPicture ) pPicture->Release();// 释放IPicture 指针
//     if ( pStream ) pStream->Release(); // 释放IStream 指针，同时释放了hMem
	// CPictureDoc* pDoc = GetDocument();
//显示位图
	//CDC *pDC = GetDlgItem(ID)->GetDC();
	if( FLAG ){
		HDC hDC= pDC->GetSafeHdc();
		CRect rect;
		pDC->GetBoundsRect(&rect,1);
		//IplImage* ipl = cvLoadImage( "F:\\1.png", 1 );
		CvvImage cimg;
		cimg.CopyOf( image ); // 复制图片
		SetRect(rect,0,0,0+image->width,0+image->height);
		cimg.DrawToHDC( hDC, &rect ); // 将图片绘制到显示控件的指定区域内
		ReleaseDC( pDC );
	}	
}

void CImageProcessingView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	SIZE size={3000,1500};
    SetScrollSizes(MM_TEXT,size);//滚动窗口的最大区域
}

// CImageProcessingView 打印


void CImageProcessingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CImageProcessingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageProcessingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageProcessingView 诊断

#ifdef _DEBUG
void CImageProcessingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProcessingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProcessingDoc* CImageProcessingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingDoc)));
	return (CImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessingView 消息处理程序


void CImageProcessingView::OnReadimage()
{
	CString strFile = "";  
      
    CFileDialog    dlgFile(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("PNG(*.png)|*.png|位图文件(*.BMP)|*.BMP|jpg文件(*.jpg)|*.jpg|All Files (*.*)|*.*||")); 
    if (dlgFile.DoModal())
    {  
        strFile = dlgFile.GetPathName();
		if( strFile == "" ){
			return;
		}
		if(FLAG){
			cvReleaseImage(&image);
			FLAG = false;
		}
		image = cvLoadImage( strFile, 1 );	
		CSize sizeTotal;
		// TODO: 计算此视图的合计大小
		SIZE size={image->width,image->height};
		SetScrollSizes(MM_TEXT,size);
		if( image != NULL ){
			FLAG = true;
		}
    }
	UpdateWindow();
	// TODO: 在此添加命令处理程序代码
}


void CImageProcessingView::OnImageinv()
{
	// TODO: 在此添加命令处理程序代码
	FLAG = false;
	IplImage *img=image,*outImage=0;  
    int height,width,step,channels;  
    uchar *data;  
	height=img->height;  
    width=img->width;  
    step=img->widthStep;  
    channels=img->nChannels;  
    data=(uchar*)img->imageData; 
	for (int i=0;i<height;++i)  
    {  
        for (int j=0;j<width;++j)  
        {  
            for (int k=0;k<channels;++k)  
            {  
                data[i*step + j*channels + k]=255-data[i*step + j*channels + k];  //每个通道每个像素取反  
            }  
        }  
    }  
	FLAG = true;
	UpdateWindow();
}


void CImageProcessingView::UpdateWindow(void)
{
	CDC *m_pDC;
	m_pDC=GetDC();
	OnDraw(m_pDC);
}
