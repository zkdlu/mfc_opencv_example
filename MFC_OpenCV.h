
// MFC_OpenCV.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFC_OpenCVApp:
// �� Ŭ������ ������ ���ؼ��� MFC_OpenCV.cpp�� �����Ͻʽÿ�.
//

class CMFC_OpenCVApp : public CWinApp
{
public:
	CMFC_OpenCVApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFC_OpenCVApp theApp;
