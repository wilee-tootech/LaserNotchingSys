#pragma once
#include "Communicate.h"
#include "RS232.h"
#include "TabPageSSL.h"

// CDustTrap 대화 상자입니다.

class CDustTrap : public CTabPageSSL
{
	DECLARE_DYNAMIC(CDustTrap)

public:
	CDustTrap(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDustTrap();
	static CDustTrap* GetInstance();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_DUSTTRAP };

private:
	static CDustTrap* m_pDustTrap;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CRS232 *m_pSockComm;
	afx_msg void OnBnClickedOk();
	void ReceiveData(WPARAM wParam, LPARAM lParam);
	void SendData(CString msg);
};
