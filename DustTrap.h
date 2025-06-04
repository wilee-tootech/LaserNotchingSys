#pragma once
#include "Communicate.h"
#include "RS232.h"
#include "TabPageSSL.h"

// CDustTrap ��ȭ �����Դϴ�.

class CDustTrap : public CTabPageSSL
{
	DECLARE_DYNAMIC(CDustTrap)

public:
	CDustTrap(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDustTrap();
	static CDustTrap* GetInstance();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_DUSTTRAP };

private:
	static CDustTrap* m_pDustTrap;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CRS232 *m_pSockComm;
	afx_msg void OnBnClickedOk();
	void ReceiveData(WPARAM wParam, LPARAM lParam);
	void SendData(CString msg);
};
