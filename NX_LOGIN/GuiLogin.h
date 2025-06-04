#pragma once
#include "./EXTERN/ShadeButtonST.h"
#include "./EXTERN/fpspread_bci.h"
#include "Login.h"

#ifdef NX_USER_LOGIN_EXPORTS
	#define DLL_USER_LOGIN_EXPORTS __declspec(dllexport)
#else
	#define DLL_USER_LOGIN_EXPORTS __declspec(dllimport)
#endif

#define MAX_LOGIN_BTN 7

// CLogin 대화 상자입니다.
class DLL_USER_LOGIN_EXPORTS CGuiLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CGuiLogin)

public:
	CGuiLogin(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGuiLogin();

// 대화 상자 데이터입니다.

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()


private:
	CString			m_strUserName;
	CString			m_strUserPWD;
	CShadeButtonST	m_StyleButton[MAX_LOGIN_BTN];
	BOOL m_bLoginSuccess;

private:
	void LoginInit(void);
	void LoginOpen(void);
	void LoginSave(void);

public:
	BOOL GetLoginResult(void ) { return m_bLoginSuccess; };
	BOOL Create(CWnd *pParentWnd=NULL);
public:
	virtual BOOL OnInitDialog();
	virtual INT_PTR DoModal();

	afx_msg void OnBnClickedBtnUserLoginOk();
	afx_msg void OnBnClickedBtnUserLoginCancel();
	afx_msg void OnBnClickedBtnUserLoginApply();
	afx_msg void OnBnClickedBtnUserLoginAdd();
	afx_msg void OnBnClickedBtnUserLoginDelete();
	afx_msg void OnBnClickedBtnUserLoginModify();
	afx_msg void OnBnClickedBtnUserLoginSave();
	CString m_strNewUserID;
	CString m_strNewUserPWD;
	CString m_strNewDescription;
	CFpspread_bci m_spreadLogin;
	CComboBox m_comboLevel;
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_EVENTSINK_MAP()
	void ClickCttextctrlUserId();
	void ClickCttextctrlUserPwd();
	void ClickFpspreadBci(long Col, long Row);

	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNcPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

