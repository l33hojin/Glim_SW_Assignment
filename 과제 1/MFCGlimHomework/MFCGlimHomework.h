
// MFCGlimHomework.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMFCGlimHomeworkApp:
// �� Ŭ������ ������ ���ؼ��� MFCGlimHomework.cpp�� �����Ͻʽÿ�.
//

class CMFCGlimHomeworkApp : public CWinApp
{
public:
	CMFCGlimHomeworkApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMFCGlimHomeworkApp theApp;