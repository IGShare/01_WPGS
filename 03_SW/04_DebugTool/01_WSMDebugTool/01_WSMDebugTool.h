
// 01_WSMDebugTool.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMy01_WSMDebugToolApp:
// �� Ŭ������ ������ ���ؼ��� 01_WSMDebugTool.cpp�� �����Ͻʽÿ�.
//

class CMy01_WSMDebugToolApp : public CWinAppEx
{
public:
	CMy01_WSMDebugToolApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMy01_WSMDebugToolApp theApp;