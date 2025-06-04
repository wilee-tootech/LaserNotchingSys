#pragma once

#include "SocketManager.h"
#include "./ExtDllState.h"


#ifdef NX_SOCKET_EXPORTS
#define DLL_SOCKET_EXPORTS __declspec(dllexport)
#else
#define DLL_SOCKET_EXPORTS __declspec(dllimport)
#endif


// CServerSocketDlg ��ȭ �����Դϴ�.

class DLL_SOCKET_EXPORTS CServerSocketDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CServerSocketDlg)
public:
	CServerSocketDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CServerSocketDlg();

private:
	int m_nTimerID;
	int m_nTimerDelay;
protected:
	CSocketManager m_SocketManager[MAX_CONNECTION];
	CSocketManager* m_pCurServer;

	void PickNextAvailable();
	bool StartServer();
public:
	//{{AFX_DATA(CServerSocketDlg)
	CEdit	m_ctlMessage;
	CEdit	m_ctlMsgList;
	CSpinButtonCtrl	m_ctlPortInc;
	CString	m_strPort;
	int		m_nSockType;
	//}}AFX_DATA


// ��ȭ ���� �������Դϴ�.
//	eum { IDD = IDD_DLG_SERVER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	afx_msg LRESULT OnUpdateConnection(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	void ClickCtpushctrlConnection();
	void ClickCtpushctrlDisconnection();
	void ClickCtpushctrlSend();
	afx_msg void OnDeltaposSvrPortinc(NMHDR *pNMHDR, LRESULT *pResult);
	void ClickCtpushctrlSocketType();
public:
	virtual INT_PTR DoModal();
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	BOOL Create(CWnd* pParentWnd);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

extern DLL_SOCKET_EXPORTS CServerSocketDlg* ServerSocketDlg;
