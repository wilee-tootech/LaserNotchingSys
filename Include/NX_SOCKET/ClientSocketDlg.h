#pragma once

#include "SocketManager.h"
#include "ExtDllState.h"
#ifdef NX_SOCKET_EXPORTS
#define DLL_SOCKET_EXPORTS __declspec(dllexport)
#else
#define DLL_SOCKET_EXPORTS __declspec(dllimport)
#endif

// CClientSocketDlg ��ȭ �����Դϴ�.

class DLL_SOCKET_EXPORTS CClientSocketDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CClientSocketDlg)

private:
	int m_nTimerID;
	int m_nTimerDelay;
protected:
	CSocketManager m_SocketManager;
	SockAddrIn		m_SockPeer;
public:
	
	CEdit	m_ctlMessage;
	CSpinButtonCtrl	m_ctlPortInc;
	CEdit	m_ctlMsgList;
	CIPAddressCtrl	m_ctlIPAddress;
	CString	m_strPort;
	int		m_nSockType;
public:
	CClientSocketDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CClientSocketDlg();

// ��ȭ ���� �������Դϴ�.
	//enum { IDD = IDD_DLG_CLIENT };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickCtpushctrlConnection();
	void ClickCtpushctrlDisconnection();
	void ClickCtpushctrlSend();

	virtual BOOL OnInitDialog();
	void ClickCtpushctrlSocketType();
public:
	virtual INT_PTR DoModal();
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	BOOL Create(CWnd* pParentWnd);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg LRESULT OnUpdateConnection(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

extern DLL_SOCKET_EXPORTS CClientSocketDlg* ClientSocketDlg;