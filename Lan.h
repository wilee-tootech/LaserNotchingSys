// Lan.h: interface for the CLan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAN_H__744D7C72_8E93_462A_810E_BC047897482E__INCLUDED_)
#define AFX_LAN_H__744D7C72_8E93_462A_810E_BC047897482E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Communicate.h"

class CLan : public CCommunicate
{
public:
	CLan();
	CLan(CString Owner);
	virtual ~CLan();

	char *ReadData();
	void Connect(CString folderPath); //  �̸� ����Ǿ� ���� ������ ��..���� ���¸� üũ�ϰ� �ȵǾ� ������ �ٽ� �����ϴ� ��� �˾ƺ���
	void WriteInFile(CString contents); // ���� �� ���� ��� device file name ����
	void OnCheckNetwork(CString LocalDevice, CString NetPath);
	void OnAddNetwork(CString LocalDevice, CString NetPath);
	UINT InitCommnicate();
	UINT StartCommunicate();
	UINT StopCommunicate(); 
	UINT GetConnectStatus(); // ����Ǿ� �ִ��� �ƴ��� ���� ��������
	UINT WriteData(BYTE *SendString, DWORD Stringlength); 	// 232������ SendString, Lan������ �� string

private:
	BOOL	m_bConnect; // �������� �ƴ���..
	CString m_strOwner;
};

#endif // !defined(AFX_LAN_H__744D7C72_8E93_462A_810E_BC047897482E__INCLUDED_)
