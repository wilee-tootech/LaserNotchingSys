#pragma once

#ifdef NX_KEY_PAD_EXPORTS
	#define Dll_KEY_NUMBER_PAD_EXPORTS __declspec (dllexport)
#else
	#define Dll_KEY_NUMBER_PAD_EXPORTS __declspec (dllimport)
#endif

#include "./ExtDllState.h"
#include "./EXTERN/ShadeButtonST.h"
// CNumberKeyPad 대화 상자입니다.

#define MAX_NUMBER_KEY_BTN 20

class Dll_KEY_NUMBER_PAD_EXPORTS CNumberKeyPad : public CDialogEx
{
	DECLARE_DYNAMIC(CNumberKeyPad)

public:
	CNumberKeyPad(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CNumberKeyPad();

// 대화 상자 데이터입니다.

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	BOOL Create(CWnd* pParentWnd = NULL);
private:
	CShadeButtonST m_StyleButton[MAX_NUMBER_KEY_BTN];



private:
protected:
public:
	CString m_strMinData;
	CString m_strMaxData;
	CString m_strOldData;
	CString m_strSumData;
	CString m_strSumCaption;
	CString m_strNewData;

	double	m_fMinValue;
	double	m_fMaxValue;
	double	m_fFinalData;
	int		m_nArithmetic;

	int		m_nMinValue;
	int		m_nMaxValue;
	int     m_nFinalData;

	BOOL	m_bDoubleOfDataType;


private:
	void Calculation();   
	double Math_RoundOffValue(double Value,int Cipher);
public:
	void OnKeyInput(UINT nID);
	void OnKeyInputDouble(CString strValue);
	void OnKeyInputInteger(CString strValue);

	void OnCalculation(UINT nID);

	void SetRange( double fMin, double fMax, double oldValue = 0.0 );
	void SetRange( int nMin, int nMax, int nOldValue = 0);

	double GetResultDouble(UINT RoundOff=-1);
	int	   GetResultInteger(void);
	TCHAR* GetResultStringDouble(  int nNumberOfPoint=-1  );
	TCHAR* GetResultStringInteger(void);



	afx_msg void OnBnClickedBtnNumEnter();
	afx_msg void OnBnClickedBtnNumCancel();
	afx_msg void OnBnClickedBtnNumClear();
	afx_msg void OnBnClickedBtnNumBack();
	afx_msg void OnBnClickedBtnNumSign();
	afx_msg void OnBnClickedBtnNumDot();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	virtual INT_PTR DoModal();
	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
