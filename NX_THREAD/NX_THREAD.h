// NX_THREAD.h : NX_THREAD DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CNX_THREADApp
// �� Ŭ������ ������ ������ NX_THREAD.cpp�� �����Ͻʽÿ�.
//

class CNX_THREADApp : public CWinApp
{
public:
	CNX_THREADApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
