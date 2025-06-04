// Communicate.h: interface for the CCommunicate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMUNICATE_H__883BEB0F_D88A_42CD_BC5B_5722BEF399B4__INCLUDED_)
#define AFX_COMMUNICATE_H__883BEB0F_D88A_42CD_BC5B_5722BEF399B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCommunicate
{
public:
	CCommunicate();
	virtual ~CCommunicate();

	// Init�ÿ� �ʿ��� Data�� ����� �־�� ex) RS232.������ port, parity, stop ���, ex) Lan������ ���� ���
	virtual UINT InitCommnicate() = 0;

	// ���� ���ῡ �鰡����
	virtual UINT StartCommunicate() = 0;

	// ���� ����
	virtual UINT StopCommunicate() = 0;

	// ����Ǿ� �ִ��� �ƴ��� ���� ��������
	virtual UINT GetConnectStatus() = 0;

	// 232������ SendString, Lan������ �� string
	virtual UINT WriteData(BYTE *SendString, DWORD Stringlength) = 0; // ������ ���ֱ�
	virtual char *ReadData() = 0; // ������ �о����

	virtual BOOL GetIsConnect();
	virtual void SetIsConnect(BOOL bIsConnect);



protected:
	BOOL m_bIsConnect;
};

#endif // !defined(AFX_COMMUNICATE_H__883BEB0F_D88A_42CD_BC5B_5722BEF399B4__INCLUDED_)
