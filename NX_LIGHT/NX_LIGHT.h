// NX_LIGHT.h : NX_LIGHT DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CNX_LIGHTApp
// �� Ŭ������ ������ ������ NX_LIGHT.cpp�� �����Ͻʽÿ�.
//

class CNX_LIGHTApp : public CWinApp
{
public:
	CNX_LIGHTApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
