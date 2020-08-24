
// MFC_OpenCVDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFC_OpenCV.h"
#include "MFC_OpenCVDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_OpenCVDlg 대화 상자



CMFC_OpenCVDlg::CMFC_OpenCVDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_OPENCV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_OpenCVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, m_picture);
	DDX_Control(pDX, IDC_PICTURE_RESULT, m_pictureResult);
}

BEGIN_MESSAGE_MAP(CMFC_OpenCVDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_OPEN, &CMFC_OpenCVDlg::OnClickedOpen)
	ON_BN_CLICKED(IDC_SAVE, &CMFC_OpenCVDlg::OnClickedSave)
	ON_BN_CLICKED(IDC_COLOR, &CMFC_OpenCVDlg::OnClickedColor)
	ON_BN_CLICKED(IDC_SOBEL, &CMFC_OpenCVDlg::OnClickedSobel)
	ON_BN_CLICKED(IDC_CANNY, &CMFC_OpenCVDlg::OnClickedCanny)
	ON_BN_CLICKED(IDC_BINARY, &CMFC_OpenCVDlg::OnClickedBinary)
	ON_BN_CLICKED(IDC_DILATE, &CMFC_OpenCVDlg::OnClickedDilate)
	ON_BN_CLICKED(IDC_ERODE, &CMFC_OpenCVDlg::OnClickedErode)
	ON_BN_CLICKED(IDC_CIRCLE, &CMFC_OpenCVDlg::OnClickedCircle)
	ON_BN_CLICKED(IDC_RECTANGLE, &CMFC_OpenCVDlg::OnClickedRectangle)
	ON_BN_CLICKED(IDC_LINE, &CMFC_OpenCVDlg::OnClickedLine)
	ON_BN_CLICKED(IDC_ELLIPSE, &CMFC_OpenCVDlg::OnClickedEllipse)
	ON_BN_CLICKED(IDC_TEXT, &CMFC_OpenCVDlg::OnClickedText)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_VIDEO, &CMFC_OpenCVDlg::OnClickedVideo)
END_MESSAGE_MAP()


// CMFC_OpenCVDlg 메시지 처리기

BOOL CMFC_OpenCVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFC_OpenCVDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFC_OpenCVDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFC_OpenCVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_OpenCVDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CMFC_OpenCVDlg::DrawImage(Mat mat, CWnd& picture)
{
	int bpp = 8 * mat.elemSize();

	int padding = 0;
	if (bpp < 32)
		padding = 4 - (mat.cols % 4);

	if (padding == 4)
		padding = 0;

	int border = 0;
	if (bpp < 32)
	{
		border = 4 - (mat.cols % 4);
	}

	Mat mat_temp;
	if (border > 0 || mat.isContinuous() == false)
	{
		cv::copyMakeBorder(mat, mat_temp, 0, 0, 0, border, cv::BORDER_CONSTANT, 0);
	}
	else
	{
		mat_temp = mat;
	}

	RECT r;
	picture.GetClientRect(&r);
	cv::Size winSize(r.right, r.bottom);

	CImage image;
	image.Create(winSize.width, winSize.height, 24);

	BITMAPINFO *bitInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));
	bitInfo->bmiHeader.biBitCount = bpp;
	bitInfo->bmiHeader.biWidth = mat_temp.cols;
	bitInfo->bmiHeader.biHeight = -mat_temp.rows;
	bitInfo->bmiHeader.biPlanes = 1;
	bitInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitInfo->bmiHeader.biCompression = BI_RGB;
	bitInfo->bmiHeader.biClrImportant = 0;
	bitInfo->bmiHeader.biClrUsed = 0;
	bitInfo->bmiHeader.biSizeImage = 0;
	bitInfo->bmiHeader.biXPelsPerMeter = 0;
	bitInfo->bmiHeader.biYPelsPerMeter = 0;

	if (bpp == 8)
	{
		RGBQUAD* palette = bitInfo->bmiColors;
		for (int i = 0; i < 256; i++)
		{
			palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
			palette[i].rgbReserved = 0;
		}
	}

	if (mat_temp.cols == winSize.width  && mat_temp.rows == winSize.height)
	{
		SetDIBitsToDevice(image.GetDC(),
			0, 0, winSize.width, winSize.height,
			0, 0, 0, mat_temp.rows,
			mat_temp.data, bitInfo, DIB_RGB_COLORS);
	}
	else
	{
		int destx = 0, desty = 0;
		int destw = winSize.width;
		int desth = winSize.height;

		int imgx = 0, imgy = 0;
		int imgWidth = mat_temp.cols - border;
		int imgHeight = mat_temp.rows;

		StretchDIBits(image.GetDC(),
			destx, desty, destw, desth,
			imgx, imgy, imgWidth, imgHeight,
			mat_temp.data, bitInfo, DIB_RGB_COLORS, SRCCOPY);
	}

	HDC dc = ::GetDC(picture.m_hWnd);
	image.BitBlt(dc, 0, 0);

	::ReleaseDC(picture.m_hWnd, dc);

	image.ReleaseDC();
	image.Destroy();
}

void CMFC_OpenCVDlg::OnClickedOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LPCTSTR filter = _T("image file(*.jpg;*.bmp;*.png;)|*.jpg;*.bmp;*.png;|All Files(*.*)|*.*||");
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY, filter);
	if (fileDlg.DoModal() == IDOK)
	{
		CString path = fileDlg.GetPathName();
		CT2CA pszString(path);
		std::string strPath(pszString);

		src = imread(strPath);
		dst = src;
		
		DrawImage(src, m_picture);
		DrawImage(dst, m_pictureResult);
	}
}


void CMFC_OpenCVDlg::OnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	imwrite("./result.jpg", dst);
	MessageBox(_T("result.jpg 저장"), _T("저장"), MB_OK);
}

void CMFC_OpenCVDlg::OnClickedColor()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	cvtColor(src, dst, COLOR_BGR2GRAY);

	DrawImage(dst, m_pictureResult);
}


void CMFC_OpenCVDlg::OnClickedSobel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Mat edge;
	Canny(src, edge, 120, 210);
	dst = edge;

	DrawImage(dst, m_pictureResult);
}


void CMFC_OpenCVDlg::OnClickedCanny()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Mat edge;
	Sobel(src, edge, CV_8U, 2, 0, 1, 1, 0, BORDER_DEFAULT);
	dst = edge;

	DrawImage(dst, m_pictureResult);
}


void CMFC_OpenCVDlg::OnClickedBinary()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Mat binary;
	cvtColor(src, binary, COLOR_RGB2GRAY);
	threshold(binary, binary, 120, 255, THRESH_BINARY);
	dst = binary;

	DrawImage(dst, m_pictureResult);
}


void CMFC_OpenCVDlg::OnClickedDilate()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Mat mask = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(1, 1));
	Mat dilated;
	dilate(src, dilated, mask, cv::Point(-1, -1), 3);
	dst = dilated;

	DrawImage(dst, m_pictureResult);
}


void CMFC_OpenCVDlg::OnClickedErode()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Mat mask = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(1, 1));
	Mat eroded;
	erode(src, eroded, mask, cv::Point(-1, -1), 3);
	dst = eroded;

	DrawImage(dst, m_pictureResult);
}


void CMFC_OpenCVDlg::OnClickedCircle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	dst = Mat(100, 100, CV_8UC3, Scalar(0, 0, 0));
	circle(dst, cv::Point(50, 50), 5, cv::Scalar(255, 255, 255), 2);

	DrawImage(dst, m_pictureResult);
}


void CMFC_OpenCVDlg::OnClickedRectangle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	dst = Mat(100, 100, CV_8UC3, Scalar(0, 0, 0));
	rectangle(dst, cv::Rect(10, 10, 50, 50), cv::Scalar(255, 255, 255), 2);

	DrawImage(dst, m_pictureResult);
}


void CMFC_OpenCVDlg::OnClickedLine()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	dst = Mat(100, 100, CV_8UC3, Scalar(0, 0, 0));
	line(dst, cv::Point(0, 0), cv::Point(100, 100), cv::Scalar(255, 255, 255), 2);

	DrawImage(dst, m_pictureResult);
}


void CMFC_OpenCVDlg::OnClickedEllipse()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	dst = Mat(100, 100, CV_8UC3, Scalar(0, 0, 0));
	ellipse(dst, cv::Point(50, 50), cv::Size(50, 30), 0, 0, 360, cv::Scalar(255, 255, 255), 2);

	DrawImage(dst, m_pictureResult);
}


void CMFC_OpenCVDlg::OnClickedText()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	dst = Mat(100, 100, CV_8UC3, Scalar(0, 0, 0));
	putText(dst, cv::String("Test Text"), cv::Point(0, 50), 1, 1, cv::Scalar(255, 255, 255), 1);

	DrawImage(dst, m_pictureResult);
}

void CMFC_OpenCVDlg::OnClickedVideo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	LPCTSTR filter = _T("video file(*.mp4;*.avi;)|*.mp4;*.avi;|All Files(*.*)|*.*||");
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_READONLY, filter);
	if (fileDlg.DoModal() == IDOK)
	{
		CString path = fileDlg.GetPathName();
		CT2CA pszString(path);
		std::string strPath(pszString);

		capture = VideoCapture(strPath);
		
		
		Size size = Size((int)capture.get(CAP_PROP_FRAME_WIDTH), (int)capture.get(CAP_PROP_FRAME_HEIGHT));
		double fps = 30.0;

		writer = VideoWriter("result.avi", CV_FOURCC('M', 'J', 'P', 'G'), 10, size);

		SetTimer(1000, 30, NULL);
	}
}


void CMFC_OpenCVDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	capture.read(dst);
	if (dst.empty())
	{
		KillTimer(1000);

		capture.release();
		writer.release();
		MessageBox(_T("result.avi 저장"), _T("저장"), MB_OK);
		return;
	}

	writer.write(dst);

	DrawImage(dst, m_pictureResult);

	CDialogEx::OnTimer(nIDEvent);
}
