
// UARTDebug.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CUARTDebugApp:
// �� Ŭ������ ������ ���ؼ��� UARTDebug.cpp�� �����Ͻʽÿ�.
//

class CUARTDebugApp : public CWinAppEx
{
public:
	CUARTDebugApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CUARTDebugApp theApp;