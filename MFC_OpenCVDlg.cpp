
// MFC_OpenCVDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFC_OpenCV.h"
#include "MFC_OpenCVDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CMFC_OpenCVDlg ��ȭ ����



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


// CMFC_OpenCVDlg �޽��� ó����

BOOL CMFC_OpenCVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.


	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFC_OpenCVDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMFC_OpenCVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_OpenCVDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	imwrite("./result.jpg", dst);
	MessageBox(_T("result.jpg ����"), _T("����"), MB_OK);
}

void CMFC_OpenCVDlg::OnClickedColor()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	cvtColor(src, dst, COLOR_BGR2GRAY);

	DrawImage(dst, m_pictureResult);
}


void CMFC_OpenCVDlg::OnClickedSobel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Mat edge;
	Canny(src, edge, 120, 210);
	dst = edge;

	DrawImage(dst, m_pictureResult);
}


void CMFC_OpenCVDlg::OnClickedCanny()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Mat edge;
	Sobel(src, edge, CV_8U, 2, 0, 1, 1, 0, BORDER_DEFAULT);
	dst = edge;

	DrawImage(dst, m_pictureResult);
}


void CMFC_OpenCVDlg::OnClickedBinary()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Mat binary;
	cvtColor(src, binary, COLOR_RGB2GRAY);
	threshold(binary, binary, 120, 255, THRESH_BINARY);
	dst = binary;

	DrawImage(dst, m_pictureResult);
}


void CMFC_OpenCVDlg::OnClickedDilate()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Mat mask = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(1, 1));
	Mat dilated;
	dilate(src, dilated, mask, cv::Point(-1, -1), 3);
	dst = dilated;

	DrawImage(dst, m_pictureResult);
}


void CMFC_OpenCVDlg::OnClickedErode()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Mat mask = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3), cv::Point(1, 1));
	Mat eroded;
	erode(src, eroded, mask, cv::Point(-1, -1), 3);
	dst = eroded;

	DrawImage(dst, m_pictureResult);
}


void CMFC_OpenCVDlg::OnClickedCircle()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	dst = Mat(100, 100, CV_8UC3, Scalar(0, 0, 0));
	circle(dst, cv::Point(50, 50), 5, cv::Scalar(255, 255, 255), 2);

	DrawImage(dst, m_pictureResult);
}


void CMFC_OpenCVDlg::OnClickedRectangle()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	dst = Mat(100, 100, CV_8UC3, Scalar(0, 0, 0));
	rectangle(dst, cv::Rect(10, 10, 50, 50), cv::Scalar(255, 255, 255), 2);

	DrawImage(dst, m_pictureResult);
}


void CMFC_OpenCVDlg::OnClickedLine()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	dst = Mat(100, 100, CV_8UC3, Scalar(0, 0, 0));
	line(dst, cv::Point(0, 0), cv::Point(100, 100), cv::Scalar(255, 255, 255), 2);

	DrawImage(dst, m_pictureResult);
}


void CMFC_OpenCVDlg::OnClickedEllipse()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	dst = Mat(100, 100, CV_8UC3, Scalar(0, 0, 0));
	ellipse(dst, cv::Point(50, 50), cv::Size(50, 30), 0, 0, 360, cv::Scalar(255, 255, 255), 2);

	DrawImage(dst, m_pictureResult);
}


void CMFC_OpenCVDlg::OnClickedText()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	dst = Mat(100, 100, CV_8UC3, Scalar(0, 0, 0));
	putText(dst, cv::String("Test Text"), cv::Point(0, 50), 1, 1, cv::Scalar(255, 255, 255), 1);

	DrawImage(dst, m_pictureResult);
}

void CMFC_OpenCVDlg::OnClickedVideo()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	capture.read(dst);
	if (dst.empty())
	{
		KillTimer(1000);

		capture.release();
		writer.release();
		MessageBox(_T("result.avi ����"), _T("����"), MB_OK);
		return;
	}

	writer.write(dst);

	DrawImage(dst, m_pictureResult);

	CDialogEx::OnTimer(nIDEvent);
}
