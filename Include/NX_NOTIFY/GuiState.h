#pragma once



// CGuiState 대화 상자입니다.

#ifdef NX_NOTIFY_EXPORTS
#define DLL_ALARM_EXPORTS __declspec(dllexport)
#else
#define DLL_ALARM_EXPORTS __declspec(dllimport)
#endif


#define DIRECTORY_NAME						"\\Config\\"
#define ALARM_CONFIG_FILE_NAME				"State.ini"

class DLL_ALARM_EXPORTS CGuiState : public CDialogEx
{
	DECLARE_DYNAMIC(CGuiState)

public:
	CGuiState(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGuiState();

// 대화 상자 데이터입니다.
// 		enum { IDD = IDD_ALARM_DLG };
private:
	int m_nStep;
	int m_nTimerID;
	int m_nTimerDelay;
	HBRUSH m_brsDlg;


	void SetStatusDescription(void);
public:
	int m_nStateNo;
	CString m_strMsg;

	BOOL Create(CWnd* pParentWnd);
	void SetStateNumber(int nStateNo);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
};

extern DLL_ALARM_EXPORTS CGuiState*  GuiState;

