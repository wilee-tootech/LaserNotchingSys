// NX_COMM.h : NX_COMM DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CNX_COMMApp
// �� Ŭ������ ������ ������ NX_COMM.cpp�� �����Ͻʽÿ�.
//

class CNX_COMMApp : public CWinApp
{
public:
	CNX_COMMApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
