
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
#include "GetAngle.h"
#include <algorithm>
#include <algorithm>
#include "Huffman.h"
using namespace cv;
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
	ON_COMMAND(ID_RotateImage, &CImageProcessingView::OnRotateimage)
	ON_COMMAND(ID_Mirror, &CImageProcessingView::OnMirror)
	ON_COMMAND(ID_FFT, &CImageProcessingView::OnFft)
	ON_COMMAND(ID_HistImage, &CImageProcessingView::OnHistimage)
	ON_COMMAND(ID_PowerEnhance, &CImageProcessingView::OnPowerenhance)
	ON_COMMAND(ID_SobelImage, &CImageProcessingView::OnSobelimage)
	ON_COMMAND(ID_LaplaceEnhance, &CImageProcessingView::OnLaplaceenhance)
	ON_COMMAND(ID_Medianfilter, &CImageProcessingView::OnMedianfilter)
	ON_COMMAND(ID_HUFFMAN_Read, &CImageProcessingView::OnHuffmanRead)
	ON_COMMAND(ID_Roberts, &CImageProcessingView::OnRoberts)
	ON_COMMAND(ID_Sobel, &CImageProcessingView::OnSobel)
	ON_COMMAND(ID_Prewitt, &CImageProcessingView::OnPrewitt)
	ON_COMMAND(ID_Laplace, &CImageProcessingView::OnLaplace)
	ON_COMMAND(ID_LinearDetection, &CImageProcessingView::OnLineardetection)
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
		CSize sizeTotal;
		// TODO: 计算此视图的合计大小
		SIZE size={image->width,image->height};
		SetScrollSizes(MM_TEXT,size);
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

//*******************************************************************
//                      输入图像
//*******************************************************************
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

//*******************************************************************
//                      取反
//*******************************************************************
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

//*******************************************************************
//                      旋转
//*******************************************************************
void CImageProcessingView::OnRotateimage()
{
	// TODO: 在此添加命令处理程序代码
	CGetAngle x;
	x.DoModal();
	int degree = x.angle;
	//int degree =  30;
	IplImage *img = image;
	double angle = degree  * CV_PI / 180.;   
    double a = sin(angle), b = cos(angle);   
    int width=img->width, height=img->height;  
    //旋转后的新图尺寸  
    int width_rotate= int(height * fabs(a) + width * fabs(b));    
    int height_rotate=int(width * fabs(a) + height * fabs(b));    
    IplImage* img_rotate = cvCreateImage(cvSize(width_rotate, height_rotate), img->depth, img->nChannels);    
    cvZero(img_rotate);    
    //保证原图可以任意角度旋转的最小尺寸  
    int tempLength = sqrt((double)width * width + (double)height *height) + 10;    
    int tempX = (tempLength + 1) / 2 - width / 2;    
    int tempY = (tempLength + 1) / 2 - height / 2;    
    IplImage* temp = cvCreateImage(cvSize(tempLength, tempLength), img->depth, img->nChannels);    
    cvZero(temp);    
    //将原图复制到临时图像tmp中心  
    cvSetImageROI(temp, cvRect(tempX, tempY, width, height));    
    cvCopy(img, temp, NULL);    
    cvResetImageROI(temp);    
    //旋转数组map  
    // [ m0  m1  m2 ] ===>  [ A11  A12   b1 ]  
    // [ m3  m4  m5 ] ===>  [ A21  A22   b2 ]  
    float m[6];    
    int w = temp->width;    
    int h = temp->height;    
    m[0] = b;    
    m[1] = a;    
    m[3] = -m[1];
    m[4] = m[0];    
    // 将旋转中心移至图像中间    
    m[2] = w * 0.5f;    
    m[5] = h * 0.5f;    
    CvMat M = cvMat(2, 3, CV_32F, m);    
    cvGetQuadrangleSubPix(temp, img_rotate, &M);    
    cvReleaseImage(&temp); 
	cvReleaseImage(&image);
	image = img_rotate;
	UpdateWindow();
}

//*******************************************************************
//                      镜像
//*******************************************************************
void CImageProcessingView::OnMirror()
{
	// TODO: 在此添加命令处理程序代码
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
				outImage->imageData[i*step + j*channels + k]=img->imageData[i*step + (width - j - 1)*channels + k];  //每个通道每个像素取反  
            }  
        }  
    }
	image = outImage;
	cvReleaseImage(&img);
	FLAG = true;
	UpdateWindow();
}

//*******************************************************************
//                      FFT变换
//*******************************************************************
void CImageProcessingView::OnFft()
{
	// TODO: 在此添加命令处理程序代码
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

//*******************************************************************
//                      直方图均衡化
//*******************************************************************
void CImageProcessingView::OnHistimage()
{
// TODO: 在此添加命令处理程序代码
	FLAG = false;
	//IplImage* gray;
    IplImage* gray = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
    
	if(image->nChannels == 3){
		cvCvtColor(image, gray, CV_RGB2GRAY);
	}
	else{
		cvCopy(image,gray);
	}
	cv::Mat src(gray);
	cv::Mat res;
	
	equalizeHist(src, res);
	gray = image;
	IplImage temp(res);
	image = cvCloneImage(&temp);;
	cvReleaseImage(&gray);
	//image = outImage;
	//cvReleaseImage(&img);
	FLAG = true;
	UpdateWindow();
}

//*******************************************************************
//                      指数增强
//*******************************************************************
void CImageProcessingView::OnPowerenhance()
{
	// TODO: 在此添加命令处理程序代码
	FLAG = false;
    //IplImage* gray = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
    IplImage* gray;
	//if(image->nChannels == 3){
	//	cvCvtColor(image, gray, CV_RGB2GRAY);
	//}
	//else{
	//	cvCopy(image,gray);
	//}
	cv::Mat src(image);
	cv::Mat res;


	Mat imageLog(src.size(), CV_32FC3);
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			imageLog.at<Vec3f>(i, j)[0] = std::log( (double)( 1 + src.at<Vec3b>(i, j)[0]));
			imageLog.at<Vec3f>(i, j)[1] = std::log( (double)( 1 + src.at<Vec3b>(i, j)[1]));
			imageLog.at<Vec3f>(i, j)[2] = std::log( (double)( 1 + src.at<Vec3b>(i, j)[2]) );
		}
	}
	//归一化到0~255    
	normalize(imageLog, imageLog, 0, 255, CV_MINMAX);
	//转换成8bit图像显示    
	convertScaleAbs(imageLog, imageLog);
	
	gray = image;
	IplImage temp(imageLog);
	image = cvCloneImage(&temp);
	cvReleaseImage(&gray);
	//image = outImage;
	//cvReleaseImage(&img);
	FLAG = true;
	UpdateWindow();
}

//*******************************************************************
//                      Sobel边缘检测
//*******************************************************************
void CImageProcessingView::OnSobelimage()
{
	// TODO: 在此添加命令处理程序代码
	FLAG = false;
    IplImage* gray = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
    
	if(image->nChannels == 3){
		cvCvtColor(image, gray, CV_RGB2GRAY);
	}
	else{
		cvCopy(image,gray);
	}
	cv::Mat src(gray);
	cv::Mat res;


	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	/// Convert it to gray
	Mat src_gray = src, grad;
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;

	/// Gradient X
	//Scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT );
	Sobel(src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	/// Gradient Y
	//Scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, BORDER_DEFAULT );
	Sobel(src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	/// Total Gradient (approximate)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
	
	gray = image;
	IplImage temp(grad);
	image = cvCloneImage(&temp);;
	cvReleaseImage(&gray);
	//image = outImage;
	//cvReleaseImage(&img);
	FLAG = true;
	UpdateWindow();
}

//*******************************************************************
//                      Laplace增强
//*******************************************************************
void CImageProcessingView::OnLaplaceenhance()
{
	// TODO: 在此添加命令处理程序代码
	FLAG = false;
	if(image->nChannels == 3 ){
		IplImage* gray = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,3);
    
		//if(image->nChannels == 3){
		//	cvCvtColor(image, gray, CV_RGB2GRAY);
		//}
		//else{
			cvCopy(image,gray);
		//}
		cv::Mat src(gray);
		cv::Mat res;


		Mat imageEnhance;
		Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, 0, 5, 0, 0, -1, 0);
		filter2D(src, imageEnhance, CV_8UC3, kernel);
		
		gray = image;
		IplImage temp(imageEnhance);
		image = cvCloneImage(&temp);;
		cvReleaseImage(&gray);
	}else{
		IplImage* gray = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
    
		//if(image->nChannels == 3){
		//	cvCvtColor(image, gray, CV_RGB2GRAY);
		//}
		//else{
			cvCopy(image,gray);
		//}
		cv::Mat src(gray);
		cv::Mat res;


		Mat imageEnhance;
		Mat kernel = (Mat_<float>(3, 3) << 0, -1, 0, 0, 5, 0, 0, -1, 0);
		filter2D(src, imageEnhance, CV_8UC1, kernel);
		
		gray = image;
		IplImage temp(imageEnhance);
		image = cvCloneImage(&temp);;
		cvReleaseImage(&gray);
	}
    
	//image = outImage;
	//cvReleaseImage(&img);
	FLAG = true;
	UpdateWindow();
}

//*******************************************************************
//                      中值滤波
//*******************************************************************
void CImageProcessingView::OnMedianfilter()
{
	// TODO: 在此添加命令处理程序代码
	int step = image->widthStep;
	int height = image->height;
	int width = image->width;
	int channel = image->nChannels;
	for( int i = 1; i < height - 1; i++ ){
		for( int j = 1; j < width - 1; j++ ){
			for( int k = 0; k < channel; k++ ){
				int temp[9];
				temp[0] = image->imageData[( i - 1 ) * step + ( j - 1 ) * channel + k ];
				temp[1] = image->imageData[( i - 1 ) * step + ( j ) * channel + k ];
				temp[2] = image->imageData[( i - 1 ) * step + ( j + 1 ) * channel + k ];
				temp[3] = image->imageData[( i ) * step + ( j - 1 ) * channel + k ];
				temp[4] = image->imageData[( i ) * step + ( j ) * channel + k ];
				temp[5] = image->imageData[( i ) * step + ( j + 1 ) * channel + k ];
				temp[6] = image->imageData[( i + 1 ) * step + ( j - 1 ) * channel + k ];
				temp[7] = image->imageData[( i + 1 ) * step + ( j ) * channel + k ];	
				temp[8] = image->imageData[( i + 1 ) * step + ( j + 1 ) * channel + k ];
				std::sort( temp, temp + 9 );
				image->imageData[( i ) * step + ( j ) * channel + k ] = temp[4];
			}
		}
	}
}

//*******************************************************************
//                      Huffman编码
//*******************************************************************
void CImageProcessingView::OnHuffmanRead()
{
	// TODO: 在此添加命令处理程序代码
	CString strFile = "";
	CFileDialog    dlgFile(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("All Files (*.*)|*.*||")); 
    if (dlgFile.DoModal())
    {  
        strFile = dlgFile.GetPathName();
		if( strFile == "" ){
			return;
		}
		CHuffman hu;
		hu.filepath = strFile;
		hu.DoModal();	
    }
}

//*******************************************************************
//                      Robert边缘检测
//*******************************************************************
void CImageProcessingView::OnRoberts()
{
	// TODO: 在此添加命令处理程序代码
	FLAG = false;

	IplImage* gray;
	if(image->nChannels==3){
		gray = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
		cvCvtColor(image, gray, CV_RGB2GRAY);
	}else{
		gray = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
		cvCopy(image,gray);
	}
	
	cvReleaseImage(&image);
	image = cvCreateImage(cvGetSize(gray),IPL_DEPTH_8U,1);
	cvCopy(gray,image);

	int step = image->widthStep;
	int height = image->height;
	int width = image->width;
	int channel = image->nChannels;
	for( int i = 1; i < height; i++ ){
		for( int j = 1; j < width; j++ ){
			for( int k = 0; k < channel; k++ ){
				int t1 = 0, t2 = 0;
				t1 += -1 * image->imageData[( i - 1 ) * step + ( j - 1 ) * channel + k ];
				t1 += 1 * image->imageData[( i ) * step + ( j ) * channel + k ];

				t2 += -1 * image->imageData[( i - 1 ) * step + ( j ) * channel + k ];
				t2 += 1 * image->imageData[( i ) * step + ( j - 1 ) * channel + k ];

				gray->imageData[( i ) * step + ( j ) * channel + k ] = ( (int)std::sqrt((double)t1*t1+t2*t2) );
			}
		}
	}
	//image = outImage;
	//cvReleaseImage(&img);
	cvReleaseImage(&image);
	image = gray;
	FLAG = true;
	UpdateWindow();
}



	//// TODO: 在此添加命令处理程序代码
	//FLAG = false;

	//IplImage* gray;
	//if(image->nChannels==3){
	//	gray = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
	//	cvCvtColor(image, gray, CV_RGB2GRAY);
	//}else{
	//	gray = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
	//	cvCopy(image,gray);
	//}
	//
	//cvReleaseImage(&image);
	//image = gray;

	//int step = image->widthStep;
	//int height = image->height;
	//int width = image->width;
	//int channel = image->nChannels;
	//for( int i = 1; i < height - 1; i++ ){
	//	for( int j = 1; j < width - 1; j++ ){
	//		for( int k = 0; k < channel; k++ ){
	//			int t1 = 0, t2 = 0;
	//			t1 += -1 * image->imageData[( i - 1 ) * step + ( j - 1 ) * channel + k ];
	//			t1 += -2 * image->imageData[( i - 1 ) * step + ( j ) * channel + k ];
	//			t1 += -1 * image->imageData[( i - 1 ) * step + ( j + 1 ) * channel + k ];
	//			t1 += -0 * image->imageData[( i ) * step + ( j - 1 ) * channel + k ];
	//			t1 += -0 * image->imageData[( i ) * step + ( j ) * channel + k ];
	//			t1 += -0 * image->imageData[( i ) * step + ( j + 1 ) * channel + k ];
	//			t1 += 1 * image->imageData[( i + 1 ) * step + ( j - 1 ) * channel + k ];
	//			t1 += 2 * image->imageData[( i + 1 ) * step + ( j ) * channel + k ];	
	//			t1 += 1 * image->imageData[( i + 1 ) * step + ( j + 1 ) * channel + k ];
	//			t2 += -1 * image->imageData[( i - 1 ) * step + ( j - 1 ) * channel + k ];
	//			t2 += 0 * image->imageData[( i - 1 ) * step + ( j ) * channel + k ];
	//			t2 += 1 * image->imageData[( i - 1 ) * step + ( j + 1 ) * channel + k ];
	//			t2 += -2 * image->imageData[( i ) * step + ( j - 1 ) * channel + k ];
	//			t2 += -0 * image->imageData[( i ) * step + ( j ) * channel + k ];
	//			t2 += 2 * image->imageData[( i ) * step + ( j + 1 ) * channel + k ];
	//			t2 += -1 * image->imageData[( i + 1 ) * step + ( j - 1 ) * channel + k ];
	//			t2 += 0 * image->imageData[( i + 1 ) * step + ( j ) * channel + k ];	
	//			t2 += 1 * image->imageData[( i + 1 ) * step + ( j + 1 ) * channel + k ];
	//			image->imageData[( i ) * step + ( j ) * channel + k ] = (int)std::sqrt((double)t1*t1+t2*t2);
	//		}
	//	}
	//}
	////image = outImage;
	////cvReleaseImage(&img);

	//FLAG = true;
//UpdateWindow();

//*******************************************************************
//                      Sobel边缘检测
//*******************************************************************
void CImageProcessingView::OnSobel()
{
	// TODO: 在此添加命令处理程序代码
		FLAG = false;

	IplImage* gray;
	if(image->nChannels==3){
		gray = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
		cvCvtColor(image, gray, CV_RGB2GRAY);
	}else{
		gray = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
		cvCopy(image,gray);
	}
	
	cvReleaseImage(&image);
	image = cvCreateImage(cvGetSize(gray),IPL_DEPTH_8U,1);
	cvCopy(gray,image);

	int step = image->widthStep;
	int height = image->height;
	int width = image->width;
	int channel = image->nChannels;
	for( int i = 1; i < height - 1; i++ ){
		for( int j = 1; j < width - 1; j++ ){
			for( int k = 0; k < channel; k++ ){
				int t1 = 0, t2 = 0;
				t1 += 1 * image->imageData[( i - 1 ) * step + ( j - 1 ) * channel + k ];
				t1 += 2 * image->imageData[( i - 1 ) * step + ( j ) * channel + k ];
				t1 += 1 * image->imageData[( i - 1 ) * step + ( j + 1 ) * channel + k ];
				t1 += -0 * image->imageData[( i ) * step + ( j - 1 ) * channel + k ];
				t1 += -0 * image->imageData[( i ) * step + ( j ) * channel + k ];
				t1 += -0 * image->imageData[( i ) * step + ( j + 1 ) * channel + k ];
				t1 += -1 * image->imageData[( i + 1 ) * step + ( j - 1 ) * channel + k ];
				t1 += -2 * image->imageData[( i + 1 ) * step + ( j ) * channel + k ];	
				t1 += -1 * image->imageData[( i + 1 ) * step + ( j + 1 ) * channel + k ];
				t2 += -1 * image->imageData[( i - 1 ) * step + ( j - 1 ) * channel + k ];
				t2 += 0 * image->imageData[( i - 1 ) * step + ( j ) * channel + k ];
				t2 += 1 * image->imageData[( i - 1 ) * step + ( j + 1 ) * channel + k ];
				t2 += -2 * image->imageData[( i ) * step + ( j - 1 ) * channel + k ];
				t2 += -0 * image->imageData[( i ) * step + ( j ) * channel + k ];
				t2 += 2 * image->imageData[( i ) * step + ( j + 1 ) * channel + k ];
				t2 += -1 * image->imageData[( i + 1 ) * step + ( j - 1 ) * channel + k ];
				t2 += 0 * image->imageData[( i + 1 ) * step + ( j ) * channel + k ];	
				t2 += 1 * image->imageData[( i + 1 ) * step + ( j + 1 ) * channel + k ];
				gray->imageData[( i ) * step + ( j ) * channel + k ] = (int)std::sqrt((double)t1*t1+t2*t2);
			}
		}
	}
	//image = outImage;
	//cvReleaseImage(&img);
	cvReleaseImage(&image);
	image = gray;
	FLAG = true;
	UpdateWindow();
}

//*******************************************************************
//                      Prewitt边缘检测
//*******************************************************************
void CImageProcessingView::OnPrewitt()
{
	// TODO: 在此添加命令处理程序代码
		FLAG = false;

	IplImage* gray;
	if(image->nChannels==3){
		gray = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
		cvCvtColor(image, gray, CV_RGB2GRAY);
	}else{
		gray = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
		cvCopy(image,gray);
	}
	
	cvReleaseImage(&image);
	image = cvCreateImage(cvGetSize(gray),IPL_DEPTH_8U,1);
	cvCopy(gray,image);

	int step = image->widthStep;
	int height = image->height;
	int width = image->width;
	int channel = image->nChannels;
	for( int i = 1; i < height - 1; i++ ){
		for( int j = 1; j < width - 1; j++ ){
			for( int k = 0; k < channel; k++ ){
				int t1 = 0, t2 = 0;
				t1 += 1 * image->imageData[( i - 1 ) * step + ( j - 1 ) * channel + k ];
				t1 += 1 * image->imageData[( i - 1 ) * step + ( j ) * channel + k ];
				t1 += 1 * image->imageData[( i - 1 ) * step + ( j + 1 ) * channel + k ];
				t1 += -0 * image->imageData[( i ) * step + ( j - 1 ) * channel + k ];
				t1 += -0 * image->imageData[( i ) * step + ( j ) * channel + k ];
				t1 += -0 * image->imageData[( i ) * step + ( j + 1 ) * channel + k ];
				t1 += -1 * image->imageData[( i + 1 ) * step + ( j - 1 ) * channel + k ];
				t1 += -1 * image->imageData[( i + 1 ) * step + ( j ) * channel + k ];	
				t1 += -1 * image->imageData[( i + 1 ) * step + ( j + 1 ) * channel + k ];
				t2 += -1 * image->imageData[( i - 1 ) * step + ( j - 1 ) * channel + k ];
				t2 += 0 * image->imageData[( i - 1 ) * step + ( j ) * channel + k ];
				t2 += 1 * image->imageData[( i - 1 ) * step + ( j + 1 ) * channel + k ];
				t2 += -1 * image->imageData[( i ) * step + ( j - 1 ) * channel + k ];
				t2 += -0 * image->imageData[( i ) * step + ( j ) * channel + k ];
				t2 += 1 * image->imageData[( i ) * step + ( j + 1 ) * channel + k ];
				t2 += -1 * image->imageData[( i + 1 ) * step + ( j - 1 ) * channel + k ];
				t2 += 0 * image->imageData[( i + 1 ) * step + ( j ) * channel + k ];	
				t2 += 1 * image->imageData[( i + 1 ) * step + ( j + 1 ) * channel + k ];
				gray->imageData[( i ) * step + ( j ) * channel + k ] = (int)std::sqrt((double)t1*t1+t2*t2);
			}
		}
	}
	//image = outImage;
	//cvReleaseImage(&img);
	cvReleaseImage(&image);
	image = gray;
	FLAG = true;
	UpdateWindow();
}

//*******************************************************************
//                      Laplace边缘检测
//*******************************************************************
void CImageProcessingView::OnLaplace()
{
	// TODO: 在此添加命令处理程序代码
		FLAG = false;

	IplImage* gray;
	if(image->nChannels==3){
		gray = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
		cvCvtColor(image, gray, CV_RGB2GRAY);
	}else{
		gray = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
		cvCopy(image,gray);
	}
	
	cvReleaseImage(&image);
	image = cvCreateImage(cvGetSize(gray),IPL_DEPTH_8U,1);
	cvCopy(gray,image);

	int step = image->widthStep;
	int height = image->height;
	int width = image->width;
	int channel = image->nChannels;
	for( int i = 1; i < height - 1; i++ ){
		for( int j = 1; j < width - 1; j++ ){
			for( int k = 0; k < channel; k++ ){
				int t1 = 0, t2 = 0;
				/*t1 += 0 * image->imageData[( i - 1 ) * step + ( j - 1 ) * channel + k ];
				t1 += 1 * image->imageData[( i - 1 ) * step + ( j ) * channel + k ];
				t1 += 0 * image->imageData[( i - 1 ) * step + ( j + 1 ) * channel + k ];
				t1 += 1 * image->imageData[( i ) * step + ( j - 1 ) * channel + k ];
				t1 += 4 * image->imageData[( i ) * step + ( j ) * channel + k ];
				t1 += 1 * image->imageData[( i ) * step + ( j + 1 ) * channel + k ];
				t1 += 0 * image->imageData[( i + 1 ) * step + ( j - 1 ) * channel + k ];
				t1 += 1 * image->imageData[( i + 1 ) * step + ( j ) * channel + k ];	
				t1 += 0 * image->imageData[( i + 1 ) * step + ( j + 1 ) * channel + k ];*/
				t2 += 1 * image->imageData[( i - 1 ) * step + ( j - 1 ) * channel + k ];
				t2 += 1 * image->imageData[( i - 1 ) * step + ( j ) * channel + k ];
				t2 += 1 * image->imageData[( i - 1 ) * step + ( j + 1 ) * channel + k ];
				t2 += 1 * image->imageData[( i ) * step + ( j - 1 ) * channel + k ];
				t2 += -8 * image->imageData[( i ) * step + ( j ) * channel + k ];
				t2 += 1 * image->imageData[( i ) * step + ( j + 1 ) * channel + k ];
				t2 += 1 * image->imageData[( i + 1 ) * step + ( j - 1 ) * channel + k ];
				t2 += 1 * image->imageData[( i + 1 ) * step + ( j ) * channel + k ];	
				t2 += 1 * image->imageData[( i + 1 ) * step + ( j + 1 ) * channel + k ];
				gray->imageData[( i ) * step + ( j ) * channel + k ] = (int)std::sqrt((double)t1*t1+t2*t2);
			}
		}
	}
	//image = outImage;
	//cvReleaseImage(&img);
	cvReleaseImage(&image);
	image = gray;
	FLAG = true;
	UpdateWindow();
}

//*******************************************************************
//                      直线检测
//*******************************************************************
void CImageProcessingView::OnLineardetection()
{
	// TODO: 在此添加命令处理程序代码
}
