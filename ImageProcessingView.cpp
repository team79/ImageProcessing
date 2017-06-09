
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
#include "GetAngle.h"
using namespace cv;
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
	ON_COMMAND(ID_RotateImage, &CImageProcessingView::OnRotateimage)
	ON_COMMAND(ID_Mirror, &CImageProcessingView::OnMirror)
	ON_COMMAND(ID_FFT, &CImageProcessingView::OnFft)
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
		CSize sizeTotal;
		// TODO: �������ͼ�ĺϼƴ�С
		SIZE size={image->width,image->height};
		SetScrollSizes(MM_TEXT,size);
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


void CImageProcessingView::OnRotateimage()
{
	// TODO: �ڴ���������������
	CGetAngle x;
	x.DoModal();
	int degree = x.angle;
	//int degree =  30;
	IplImage *img = image;
	double angle = degree  * CV_PI / 180.;   
    double a = sin(angle), b = cos(angle);   
    int width=img->width, height=img->height;  
    //��ת�����ͼ�ߴ�  
    int width_rotate= int(height * fabs(a) + width * fabs(b));    
    int height_rotate=int(width * fabs(a) + height * fabs(b));    
    IplImage* img_rotate = cvCreateImage(cvSize(width_rotate, height_rotate), img->depth, img->nChannels);    
    cvZero(img_rotate);    
    //��֤ԭͼ��������Ƕ���ת����С�ߴ�  
    int tempLength = sqrt((double)width * width + (double)height *height) + 10;    
    int tempX = (tempLength + 1) / 2 - width / 2;    
    int tempY = (tempLength + 1) / 2 - height / 2;    
    IplImage* temp = cvCreateImage(cvSize(tempLength, tempLength), img->depth, img->nChannels);    
    cvZero(temp);    
    //��ԭͼ���Ƶ���ʱͼ��tmp����  
    cvSetImageROI(temp, cvRect(tempX, tempY, width, height));    
    cvCopy(img, temp, NULL);    
    cvResetImageROI(temp);    
    //��ת����map  
    // [ m0  m1  m2 ] ===>  [ A11  A12   b1 ]  
    // [ m3  m4  m5 ] ===>  [ A21  A22   b2 ]  
    float m[6];    
    int w = temp->width;    
    int h = temp->height;    
    m[0] = b;    
    m[1] = a;    
    m[3] = -m[1];
    m[4] = m[0];    
    // ����ת��������ͼ���м�    
    m[2] = w * 0.5f;    
    m[5] = h * 0.5f;    
    CvMat M = cvMat(2, 3, CV_32F, m);    
    cvGetQuadrangleSubPix(temp, img_rotate, &M);    
    cvReleaseImage(&temp); 
	cvReleaseImage(&image);
	image = img_rotate;
	UpdateWindow();
}


void CImageProcessingView::OnMirror()
{
	// TODO: �ڴ���������������
	FLAG = false;
	IplImage *img=image;
	IplImage *outImage=cvCreateImage(cvSize(img->width, img->height), img->depth, img->nChannels);  
    int height,width,step,channels;  
	height=img->height;  
    width=img->width;  
    step=img->widthStep;  
    channels=img->nChannels;  
	for (int i=0;i<height;++i)
    {
        for (int j=0;j<width;++j)
        {  
            for (int k=0;k<channels;++k)
            {  
				outImage->imageData[i*step + j*channels + k]=img->imageData[i*step + (width - j - 1)*channels + k];  //ÿ��ͨ��ÿ������ȡ��  
            }  
        }  
    }
	image = outImage;
	cvReleaseImage(&img);
	FLAG = true;
	UpdateWindow();
}


void CImageProcessingView::OnFft()
{
	// TODO: �ڴ���������������
		FLAG = false;
    IplImage* gray = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
    
	if(image->nChannels == 3)cvCvtColor(image, gray, CV_RGB2GRAY);
	cv::Mat src(gray);
	cv::Mat dest;
	Mat padded;                            //expand input image to optimal size
	int m = getOptimalDFTSize(src.rows);
	int n = getOptimalDFTSize(src.cols); // on the border add zero values
	copyMakeBorder(src, padded, 0, m - src.rows, 0, n - src.cols, BORDER_CONSTANT, Scalar::all(0));


	Mat planes[2];// = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) }; //!!!!
	planes[0] = Mat_<float>(padded);
	planes[1] = Mat::zeros(padded.size(), CV_32F);
	Mat complexI;
	merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

	dft(complexI, complexI);            // this way the result may fit in the source matrix

										// compute the magnitude and switch to logarithmic scale
										// => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
	split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
	Mat magI = planes[0];

	magI += Scalar::all(1);                    // switch to logarithmic scale
	log(magI, magI);

	// crop the spectrum, if it has an odd number of rows or columns
	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

	// rearrange the quadrants of Fourier image  so that the origin is at the image center
	int cx = magI.cols / 2;
	int cy = magI.rows / 2;

	Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
	Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
	Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

	Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);

	normalize(magI, magI, 0, 1, NORM_MINMAX); // Transform the matrix with float values into a
											  // viewable image form (float between values 0 and 1).
	
	gray = image;
	IplImage temp(magI);
	image = cvCloneImage(&temp);;
	cvReleaseImage(&gray);
	//image = outImage;
	//cvReleaseImage(&img);
	FLAG = true;
	UpdateWindow();
}
