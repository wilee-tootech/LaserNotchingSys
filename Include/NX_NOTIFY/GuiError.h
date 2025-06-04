#pragma once


#ifdef NX_NOTIFY_EXPORTS
#define DLL_ERROR_EXPORTS __declspec(dllexport)
#else
#define DLL_ERROR_EXPORTS __declspec(dllimport)
#endif

#define ERROR_DLG_TIMER_ID		1
#define DIRECTORY_NAME			"\\Config\\"
#define JAM_DIRECTORY_NAME		"\\JAM\\"

#define ERROR_CONFIG_FILE_NAME "Error.ini"
#define ALARM_CONFIG_FILE_NAME "Alarm.ini"

// CGuiError ��ȭ �����Դϴ�.

class DLL_ERROR_EXPORTS CGuiError : public CDialogEx
{
	DECLARE_DYNAMIC(CGuiError)

public:
	CGuiError(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGuiError();

private:
	BOOL    m_bError;
	BOOL    m_bAlarm;
	int		m_nDispCount;
	int		m_nTimerDelayTime;
	BOOL	m_bDisp;
	HBRUSH	m_brsDlg;

	void SetStatusDescription(void);

public:
	int m_nErrorNo;
	int m_nAlarmNo;
	CString m_strErrorMsg;

	BOOL Create(CWnd* pParentWnd);
	void SetErrorNumber(int nErrorrNo);
	void SetAlarmNumber(int nAlarmNo);
	void SetError(BOOL bFlag);
	void SetAlarm(BOOL bFlag);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};

extern DLL_ERROR_EXPORTS CGuiError* GuiError;
