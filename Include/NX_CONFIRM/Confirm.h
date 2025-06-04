#pragma once


#ifdef NX_CONFIRM_EXPORTS
	#define Dll_Confirm_EXPORTS __declspec( dllexport )
#else
	#define Dll_Confirm_EXPORTS __declspec( dllimport )
#endif

// CConfirm 대화 상자입니다.

#define DEF_COLOR_NONE	   RGB(0,0,0);
#define DEF_COLOR_QUESTION RGB(0,0,200);
#define DEF_COLOR_WARNING  RGB(190,0,0);
#define DEF_COLOR_ERROR    RGB(255,0,0);

#define DEF_IMAGE_QUESTION	_T("\\Image\\question.bmp")
#define DEF_IMAGE_WARNING	_T("\\Image\\gnome_warning.bmp")
#define DEF_IMAGE_ERROR		_T("\\Image\\error.bmp")

struct stTitle
{
	CString  m_strImagePath;
	CString  m_strTitle;
	COLORREF m_ColorTilte;	
};

class Dll_Confirm_EXPORTS CConfirm : public CDialogEx
{
	DECLARE_DYNAMIC(CConfirm)

public:
	CConfirm(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CConfirm();

	enum 
	{
		E_NONE  = 0,
		E_QUESTION ,  
		E_WARNING  ,
		E_ERROR	   ,
	};

public:
	void SetCaption( CString strTemp, bool bOnlyOk = false, /*COLORREF a_ColorCaption = 0x000000,*/ UINT a_MsgStatus = 0 );
	virtual INT_PTR DoModal();
	BOOL Create(CWnd* pParentWnd = NULL);

private:
	CString  m_strCaption;
	bool	 m_bOnlyOk;
	//COLORREF m_ColorCaption;

	stTitle  m_stTitle;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	DECLARE_EVENTSINK_MAP()

	void ClickButtonConfirmYes();
	void ClickButtonConfirmNo();

	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);



	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
};
