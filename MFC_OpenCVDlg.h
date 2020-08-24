
// MFC_OpenCVDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CMFC_OpenCVDlg ��ȭ ����
class CMFC_OpenCVDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMFC_OpenCVDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_OPENCV_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
