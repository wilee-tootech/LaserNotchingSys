#pragma once
#include "./EXTERN/ShadeButtonST.h"

#ifdef NX_KEY_PAD_EXPORTS
#define Dll_KEY_ALPHA_PAD_EXPORTS __declspec( dllexport)
#else
#define Dll_KEY_ALPHA_PAD_EXPORTS __declspec( dllimport)
#endif


#define MAX_ALPHA_KEY_BTN 43



// CAlphaKeyPad 대화 상자입니다.

class Dll_KEY_ALPHA_PAD_EXPORTS CAlphaKeyPad : public CDialogEx
{
	DECLARE_DYNAMIC(CAlphaKeyPad)

public:
	CAlphaKeyPad(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CAlphaKeyPad();


// 대화 상자 데이터입니다.

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	//void ForcusClear(void);
	CShadeButtonST m_StyleButton[MAX_ALPHA_KEY_BTN];
public:
	BOOL Create(CWnd* pParentWnd = NULL);
public:
	CString m_strOldData;
	CString m_strNewData;
	CString m_strNewDataAsterisk;
	BOOL    m_bAsterisk;

	
	void OnKeyInput( UINT nID);

	afx_msg void OnBnClickedBtnEnter();
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnCancel();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual INT_PTR DoModal();
	
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	afx_msg void OnClose();
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);


	void SetStrOldData(CString value);
	CString GetStrOldData();

	CString GetStrNewData();
	void SetAsterisk(BOOL isuse);

};
