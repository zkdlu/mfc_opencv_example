
// MFC_OpenCVDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// CMFC_OpenCVDlg 대화 상자
class CMFC_OpenCVDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFC_OpenCVDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_OPENCV_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_picture;
	CStatic m_pictureResult;
	afx_msg void OnDestroy();

	Mat src;
	Mat dst;
	VideoCapture capture;
	VideoWriter writer;

	void DrawImage(Mat mat, CWnd& picture);

	afx_msg void OnClickedOpen();
	afx_msg void OnClickedSave();
	afx_msg void OnClickedColor();
	afx_msg void OnClickedSobel();
	afx_msg void OnClickedCanny();
	afx_msg void OnClickedBinary();
	afx_msg void OnClickedDilate();
	afx_msg void OnClickedErode();
	afx_msg void OnClickedCircle();
	afx_msg void OnClickedRectangle();
	afx_msg void OnClickedLine();
	afx_msg void OnClickedEllipse();
	afx_msg void OnClickedText();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClickedVideo();
};
