
// ImageProcessingView.cpp : CImageProcessingView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageProcessingView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_ReadImage, &CImageProcessingView::OnReadimage)
	ON_COMMAND(ID_ImageInv, &CImageProcessingView::OnImageinv)
END_MESSAGE_MAP()

// CImageProcessingView ����/����

CImageProcessingView::CImageProcessingView()
{
	// TODO: �ڴ˴���ӹ������

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

// CImageProcessingView ����

void CImageProcessingView::OnDraw(CDC* pDC)
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	//CBitmap bitmap;     //����λͼ����
	//bitmap.LoadBitmap(IDB_CLASS_VIEW);  //���λͼID
	//BITMAP bmp;
	// bitmap.GetBitmap(&bmp);
	//CDC dc;
	//dc.CreateCompatibleDC(pDC);         //����DC
	//dc.SelectObject(&bitmap);         //ѡ��DC�豸������
	//CRect rect;
	//GetClientRect(&rect);
	//pDC->StretchBlt(0,0,rect.Width(),rect.Height(),&dc,0,0,bmp.bmWidth,bmp.bmHeight,SRCCOPY);

	//HRESULT hr;
 //    CFile file;
 //    file.Open("F:\\813358355578758264.bmp", CFile::modeRead | CFile::shareDenyNone ); // �����ļ�����
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
 //    // ��HGLOBAL �õ�IStream������TRUE ��ʾ�ͷ�IStream ��ͬʱ���ͷ��ڴ�
 //    hr = ::CreateStreamOnHGlobal( hMem, TRUE, &pStream );
 //    ASSERT ( SUCCEEDED(hr) );
 //
 //    hr = ::OleLoadPicture( pStream, dwSize, TRUE, IID_IPicture, ( LPVOID * )&pPicture );
 //    ASSERT(hr==S_OK);
 //
 //    long nWidth,nHeight; // ��ߣ�MM_HIMETRIC ģʽ����λ��.01����
 //    pPicture->get_Width( &nWidth ); // ��
 //    pPicture->get_Height( &nHeight ); // ��
 //    ////////ԭ����ʾ//////
 //    CSize sz( nWidth, nHeight );
 //    pDC->HIMETRICtoDP( &sz ); // ת��MM_HIMETRIC ģʽ��λΪMM_TEXT ���ص�λ
 //    pPicture->Render(pDC->m_hDC,0,0,sz.cx,sz.cy,
 //                  0,nHeight,nWidth,-nHeight,NULL);
 //
     ////////�����ڳߴ���ʾ////////
     // CRect rect; GetClientRect(&rect);
     // pPicture->Render(pDc->m_hDC,0,0,rect.Width(),rect.Height(),
     //   0,nHeight,nWidth,-nHeight,NULL);
/////////////////////////////////
// 
//     if ( pPicture ) pPicture->Release();// �ͷ�IPicture ָ��
//     if ( pStream ) pStream->Release(); // �ͷ�IStream ָ�룬ͬʱ�ͷ���hMem
	// CPictureDoc* pDoc = GetDocument();
//��ʾλͼ
	//CDC *pDC = GetDlgItem(ID)->GetDC();
	if( FLAG ){
		HDC hDC= pDC->GetSafeHdc();
		CRect rect;
		pDC->GetBoundsRect(&rect,1);
		//IplImage* ipl = cvLoadImage( "F:\\1.png", 1 );
		CvvImage cimg;
		cimg.CopyOf( image ); // ����ͼƬ
		SetRect(rect,0,0,0+image->width,0+image->height);
		cimg.DrawToHDC( hDC, &rect ); // ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
		ReleaseDC( pDC );
	}	
}

void CImageProcessingView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: �������ͼ�ĺϼƴ�С
	SIZE size={3000,1500};
    SetScrollSizes(MM_TEXT,size);//�������ڵ��������
}

// CImageProcessingView ��ӡ


void CImageProcessingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CImageProcessingView ���

#ifdef _DEBUG
void CImageProcessingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProcessingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProcessingDoc* CImageProcessingView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingDoc)));
	return (CImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessingView ��Ϣ�������


void CImageProcessingView::OnReadimage()
{
	CString strFile = "";  
      
    CFileDialog    dlgFile(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("PNG(*.png)|*.png|λͼ�ļ�(*.BMP)|*.BMP|jpg�ļ�(*.jpg)|*.jpg|All Files (*.*)|*.*||")); 
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
		// TODO: �������ͼ�ĺϼƴ�С
		SIZE size={image->width,image->height};
		SetScrollSizes(MM_TEXT,size);
		if( image != NULL ){
			FLAG = true;
		}
    }
	UpdateWindow();
	// TODO: �ڴ���������������
}


void CImageProcessingView::OnImageinv()
{
	// TODO: �ڴ���������������
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
                data[i*step + j*channels + k]=255-data[i*step + j*channels + k];  //ÿ��ͨ��ÿ������ȡ��  
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
