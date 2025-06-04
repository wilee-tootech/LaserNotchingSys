#pragma once

// CInputEditPad ��ȭ �����Դϴ�.

#ifdef NX_KEY_PAD_EXPORTS
	#define Dll_KEY_INPUT_EDIT_PAD_EXPORTS __declspec( dllexport)
#else
	#define Dll_KEY_INPUT_EDIT_PAD_EXPORTS __declspec( dllimport)
#endif

class Dll_KEY_INPUT_EDIT_PAD_EXPORTS CInputEditPad : public CDialogEx
{
	DECLARE_DYNAMIC(CInputEditPad)

public:
	CInputEditPad(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CInputEditPad();

// ��ȭ ���� �������Դϴ�.
//	enum { IDD = IDD_INPUT_EDIT_DLG };
public:
	CString m_strOldData;
	CString m_strNewData;

	void Init(void);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editNewData;

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	DECLARE_EVENTSINK_MAP()
	void ClickCtpushctrlApply();
	void ClickCtpushctrlCancel();
	
	virtual BOOL OnInitDialog();
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	BOOL Create(CWnd* pParentWnd = NULL);


public:
	virtual INT_PTR DoModal();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
