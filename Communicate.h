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

	// Init시에 필요한 Data를 멤버에 넣어볼까 ex) RS232.에서는 port, parity, stop 등등, ex) Lan에서는 폴더 경로
	virtual UINT InitCommnicate() = 0;

	// 실제 연결에 들가보자
	virtual UINT StartCommunicate() = 0;

	// 연결 끊자
	virtual UINT StopCommunicate() = 0;

	// 연결되어 있는지 아닌지 여부 가져오기
	virtual UINT GetConnectStatus() = 0;

	// 232에서는 SendString, Lan에서는 쓸 string
	virtual UINT WriteData(BYTE *SendString, DWORD Stringlength) = 0; // 데이터 써주기
	virtual char *ReadData() = 0; // 데이터 읽어오기

	virtual BOOL GetIsConnect();
	virtual void SetIsConnect(BOOL bIsConnect);



protected:
	BOOL m_bIsConnect;
};

#endif // !defined(AFX_COMMUNICATE_H__883BEB0F_D88A_42CD_BC5B_5722BEF399B4__INCLUDED_)
