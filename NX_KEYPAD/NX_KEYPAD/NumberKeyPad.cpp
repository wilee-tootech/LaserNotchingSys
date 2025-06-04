// NumberKeyPad.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "NumberKeyPad.h"
#include "afxdialogex.h"
#include <math.h>
#include "resource.h"



// CNumberKeyPad 대화 상자입니다.

IMPLEMENT_DYNAMIC(CNumberKeyPad, CDialogEx)

CNumberKeyPad::CNumberKeyPad(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NUMBER_KEYPAD_DLG, pParent)
{
	CExtDllState State;
	m_strMinData	= _T("");
	m_strMaxData	= _T("");
	m_strOldData	= _T("");
	m_strSumData	= _T("");
	m_strSumCaption = _T("");
	m_strNewData	= _T("");


	m_fMinValue		= 0.0;
	m_fMaxValue		= 0.0;
	m_fFinalData	= 0.0;
	m_nArithmetic	= 0;

	m_nMinValue		= 0;
	m_nMaxValue     = 0;
	m_nFinalData	= 0;

	m_bDoubleOfDataType = TRUE;
}

CNumberKeyPad::~CNumberKeyPad()
{
}

void CNumberKeyPad::DoDataExchange(CDataExchange* pDX)
{
	CExtDllState State;

	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_NUM_MIN, m_strMinData);
	DDX_Text(pDX, IDC_STATIC_NUM_MAX, m_strMaxData);
	DDX_Text(pDX, IDC_STATIC_NUM_OLD, m_strOldData);
	DDX_Text(pDX, IDC_STATIC_NUM_SUM, m_strSumData);
	DDX_Text(pDX, IDC_STATIC_NUM_NEW, m_strNewData);
	DDX_Text(pDX, IDC_STATIC_SUM_CAPTION, m_strSumCaption);

	DDX_Control(pDX,IDC_BTN_NUM_0			,m_StyleButton[0]);
	DDX_Control(pDX,IDC_BTN_NUM_1			,m_StyleButton[1]);
	DDX_Control(pDX,IDC_BTN_NUM_2			,m_StyleButton[2]);
	DDX_Control(pDX,IDC_BTN_NUM_3			,m_StyleButton[3]);
	DDX_Control(pDX,IDC_BTN_NUM_4			,m_StyleButton[4]);//5
	DDX_Control(pDX,IDC_BTN_NUM_5			,m_StyleButton[5]);
	DDX_Control(pDX,IDC_BTN_NUM_6			,m_StyleButton[6]);
	DDX_Control(pDX,IDC_BTN_NUM_7			,m_StyleButton[7]);
	DDX_Control(pDX,IDC_BTN_NUM_8			,m_StyleButton[8]);
	DDX_Control(pDX,IDC_BTN_NUM_9			,m_StyleButton[9]);//10
	DDX_Control(pDX,IDC_BTN_NUM_PLUS		,m_StyleButton[10]);
	DDX_Control(pDX,IDC_BTN_NUM_MINUS		,m_StyleButton[11]);
	DDX_Control(pDX,IDC_BTN_NUM_MULTIPLE	,m_StyleButton[12]);
	DDX_Control(pDX,IDC_BTN_NUM_DIVIDE		,m_StyleButton[13]);
	DDX_Control(pDX,IDC_BTN_NUM_DOT			,m_StyleButton[14]);//15
	DDX_Control(pDX,IDC_BTN_NUM_SIGN		,m_StyleButton[15]);
	DDX_Control(pDX,IDC_BTN_NUM_BACK		,m_StyleButton[16]);
	DDX_Control(pDX,IDC_BTN_NUM_CLEAR		,m_StyleButton[17]);
	DDX_Control(pDX,IDC_BTN_NUM_CANCEL		,m_StyleButton[18]);
	DDX_Control(pDX,IDC_BTN_NUM_ENTER		,m_StyleButton[19]);//20
}


BEGIN_MESSAGE_MAP(CNumberKeyPad, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_NUM_ENTER, &CNumberKeyPad::OnBnClickedBtnNumEnter)
	ON_BN_CLICKED(IDC_BTN_NUM_CANCEL, &CNumberKeyPad::OnBnClickedBtnNumCancel)
	ON_BN_CLICKED(IDC_BTN_NUM_CLEAR, &CNumberKeyPad::OnBnClickedBtnNumClear)
	ON_BN_CLICKED(IDC_BTN_NUM_BACK, &CNumberKeyPad::OnBnClickedBtnNumBack)
	ON_BN_CLICKED(IDC_BTN_NUM_SIGN, &CNumberKeyPad::OnBnClickedBtnNumSign)
	ON_BN_CLICKED(IDC_BTN_NUM_DOT, &CNumberKeyPad::OnBnClickedBtnNumDot)

	ON_COMMAND_RANGE(IDC_BTN_NUM_0,IDC_BTN_NUM_9,OnKeyInput)
	ON_COMMAND_RANGE(IDC_BTN_NUM_MINUS,IDC_BTN_NUM_PLUS,OnCalculation)
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CNumberKeyPad 메시지 처리기입니다.


void CNumberKeyPad::OnBnClickedBtnNumEnter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CExtDllState State;
	double  fValue = 0.0;
	int		nValue = 0;

	if(m_nArithmetic !=0 )	
	{
		Calculation();
	}
	else
	{
		UpdateData(TRUE);
		if(m_bDoubleOfDataType)
		{
			fValue = _ttof(m_strNewData);
			if(fValue >= m_fMinValue && fValue <= m_fMaxValue)
			{
				m_fFinalData = fValue;
				OnOK();
			}
			else
			{
				CString ErrMSG;
				ErrMSG.Format(_T("세팅 값이 올바르지않습니다.\nMin : %.3lf  , Max :%.3lf\nCurrentValue=%.3lf "),m_fMinValue,m_fMaxValue,fValue);
				MessageBox(ErrMSG,_T("Error Massage"),MB_OK);
			}
		}
		else
		{
			nValue = _ttoi(m_strNewData);
			if(nValue >= m_nMinValue && nValue <= m_nMaxValue)
			{
				m_nFinalData = nValue;
				OnOK();
			}
			else
			{
				CString ErrMSG;
				ErrMSG.Format(_T("세팅 값이 올바르지않습니다.\nMin : %d  , Max :%d\nCurrentValue=%d ")
					,m_nMinValue
					,m_nMaxValue
					,nValue);

				MessageBox(ErrMSG,_T("Error Massage"),MB_OK);
			}
		}
	}
	m_nArithmetic = 0;
}


void CNumberKeyPad::OnBnClickedBtnNumCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CExtDllState State;
	OnCancel();
}


void CNumberKeyPad::OnBnClickedBtnNumClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CExtDllState State;
	m_strNewData = TEXT("0");
	m_strSumData = TEXT("0");
	m_strSumCaption = TEXT("SUM DATA");
	m_nArithmetic = 0;

	UpdateData(FALSE);


}


void CNumberKeyPad::OnBnClickedBtnNumBack()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CExtDllState State;
	UpdateData(TRUE);
	
	if(m_strNewData.IsEmpty()) return;
	m_strNewData.Delete(m_strNewData.GetLength()-1,1);

	UpdateData(FALSE);
}


void CNumberKeyPad::OnBnClickedBtnNumSign()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CExtDllState State;
	UpdateData(TRUE);
	if(m_strNewData.IsEmpty()) return;

	CString strFormat = _T("");

	if(m_bDoubleOfDataType)
	{
		double fValue = 0.0;
		fValue = _ttof(m_strNewData);

		if(m_strNewData.Find(_T(".")) != -1)
		{
			//11.1
			int nDotPosition = m_strNewData.Find(_T("."));   //2
			int nLength		 = m_strNewData.GetLength() -1; //4 -1
			int nSel		 = nLength - nDotPosition;

			strFormat.Format(_T("%%.%df"),nSel);
			m_strNewData.Format(strFormat, fValue*-1);
		}
		else
		{
			m_strNewData.Format(_T("%.3f"),fValue*-1);
		}
	}
	else
	{
		int nValue = 0;
		nValue = _ttoi(m_strNewData);
		m_strNewData.Format(_T("%d"),nValue*-1);
	}
	UpdateData(FALSE);
}


void CNumberKeyPad::OnBnClickedBtnNumDot()
{
	CExtDllState State;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if(m_strNewData.IsEmpty()) return;
	if(m_strNewData.Find(_T(".")) != -1) return;

	m_strNewData += _T(".");
	UpdateData(FALSE);
}


BOOL CNumberKeyPad::OnInitDialog()
{
	CExtDllState State;

	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	for(int i = 0; i < MAX_NUMBER_KEY_BTN; i++)
	{
		m_StyleButton[i].SetShade(CShadeButtonST::SHS_SOFTBUMP);
		m_StyleButton[i].SetAlign(CButtonST::ST_ALIGN_HORIZ);
	}

	LOGFONT UserLogFont;

	this->GetFont()->GetLogFont(&UserLogFont);
	wsprintf(UserLogFont.lfFaceName, _T("%s"), TEXT("Tahoma"));

	UserLogFont.lfHeight = 15;
	UserLogFont.lfWeight = FW_BOLD;

	CFont UserFont;
	UserFont.CreateFontIndirect(&UserLogFont);


	CWnd* pWnd = this->GetWindow(GW_CHILD);

	while(pWnd)
	{
		pWnd->SetFont(&UserFont);
		pWnd = pWnd->GetNextWindow();
	}

	UserFont.Detach();






	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CNumberKeyPad::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CExtDllState State;
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	OnBnClickedBtnNumClear();
}

void CNumberKeyPad::Calculation()
{
	CExtDllState State;
	UpdateData(TRUE);

	if(m_strNewData.IsEmpty()) return;
	if(m_strSumData.IsEmpty()) return;

	double fValue1,fValue2;
	fValue1 = fValue2 = 0.0;

	fValue1 = _ttof(m_strSumData);
	fValue2 = _ttof(m_strNewData);

	switch(m_nArithmetic)
	{
	case 1: fValue1 += fValue2; break;
	case 2: fValue1 -= fValue2; break;
	case 3: fValue1 *= fValue2; break;
	case 4: fValue1 /= fValue2; break;
	}

	CString strFormat = _T("");

	if(m_strSumData.Find(_T(".")) != -1)
	{
		//11.1
		int nDotPosition = m_strSumData.Find(_T("."));   //2
		int nLength		 = m_strSumData.GetLength() + m_strNewData.GetLength() -2; //4 -1
		int nSel		 = nLength - nDotPosition;

		strFormat.Format(_T("%%.%df"),nSel);
		m_strNewData.Format(strFormat ,fValue1	 ); 
	}
	else
	{
		m_strNewData.Format(_T("%.3f") ,fValue1	 );
	}


	UpdateData(FALSE);
}

void CNumberKeyPad::OnKeyInput(UINT nID)
{
	CExtDllState State;
	switch (nID)
	{
	case IDC_BTN_NUM_1: m_strNewData += _T("1"); break;
	case IDC_BTN_NUM_2:	m_strNewData += _T("2"); break;
	case IDC_BTN_NUM_3:	m_strNewData += _T("3"); break;
	case IDC_BTN_NUM_4: m_strNewData += _T("4"); break;
	case IDC_BTN_NUM_5:	m_strNewData += _T("5"); break;
	case IDC_BTN_NUM_6:	m_strNewData += _T("6"); break;
	case IDC_BTN_NUM_7: m_strNewData += _T("7"); break;
	case IDC_BTN_NUM_8: m_strNewData += _T("8"); break;
	case IDC_BTN_NUM_9: m_strNewData += _T("9"); break;
 	case IDC_BTN_NUM_0: m_strNewData += _T("0"); break;
	}

	if(m_bDoubleOfDataType)
		OnKeyInputDouble(m_strNewData);
	else
		OnKeyInputDouble(m_strNewData);

	
}

void CNumberKeyPad::OnKeyInputDouble(CString strValue)
{
	double m_fNewValue = 0.0;
	m_fNewValue = _ttof ( m_strNewData );

	int nDotPosition = m_strNewData.Find(_T("."));
	int nLength      = m_strNewData.GetLength();
	int nSel = nLength - nDotPosition;

	if( nDotPosition < 0 )
		nSel = 0;


	TCHAR Format[MAX_PATH];

	if(nSel==0 || nSel==1)
		_stprintf_s(Format,_T("%%.%df"),0);
	else
		_stprintf_s(Format,_T("%%.%df"),nSel-1);  

	m_strNewData.Format( Format ,m_fNewValue); 

	UpdateData(FALSE);	
}

void CNumberKeyPad::OnKeyInputInteger(CString strValue)
{
	int m_nNewValue = 0;
	m_nNewValue = _ttoi ( m_strNewData );

	m_strNewData.Format( _T("%d") ,m_nNewValue); 

	UpdateData(FALSE);	
}

void CNumberKeyPad::OnCalculation(UINT nID)
{
	CExtDllState State;
	UpdateData(TRUE);
	if(m_strNewData == "") return;
	CString strSelectKey = TEXT("");
	switch (nID)
	{
	case IDC_BTN_NUM_PLUS	 :	strSelectKey = _T("+"); m_nArithmetic = 1; break;
	case IDC_BTN_NUM_MINUS	 :	strSelectKey = _T("-"); m_nArithmetic = 2; break;
	case IDC_BTN_NUM_MULTIPLE:	strSelectKey = _T("*"); m_nArithmetic = 3; break;
	case IDC_BTN_NUM_DIVIDE	 :	strSelectKey = _T("/"); m_nArithmetic = 4; break;
	}
	m_strSumCaption = strSelectKey;
	m_strSumData = m_strNewData;
	m_strNewData = TEXT("0");

	UpdateData(FALSE);
}

void CNumberKeyPad::SetRange( double fMin, double fMax, double oldValue /* = 0.0 */ )
{
	//CExtDllState State;

	m_bDoubleOfDataType = TRUE;

	m_fMaxValue	= fMax;
	m_fMinValue = fMin;


	m_strOldData.Format( _T("%.3f"), oldValue ) ;
	m_strMinData.Format( _T("%.3f"), fMin ) ;
	m_strMaxData.Format( _T("%.3f"), fMax ) ;
}

void CNumberKeyPad::SetRange(int nMin, int nMax, int nOldValue /* = 0 */)
{
	//CExtDllState State;

	m_bDoubleOfDataType = FALSE;

	m_nMaxValue	= nMax;
	m_nMinValue = nMin;
	
	m_strOldData.Format( _T("%d"), nOldValue ) ;
	m_strMinData.Format( _T("%d"), nMin ) ;
	m_strMaxData.Format( _T("%d"), nMax ) ;

}

INT_PTR CNumberKeyPad::DoModal()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CExtDllState State;
	return CDialogEx::DoModal();
}

double CNumberKeyPad::GetResultDouble( UINT RoundOff )
{
	CExtDllState State;

	double Ret=0.0;
	if( m_fFinalData >  m_fMaxValue)
		Ret= m_fMaxValue;
	else if( m_fFinalData < m_fMinValue )
		Ret= m_fMinValue;
	else Ret= m_fFinalData;
	if(RoundOff>-1)
		return Math_RoundOffValue(Ret,RoundOff); // 수정 부분 
	return Ret;
}

int CNumberKeyPad::GetResultInteger(void)
{
	CExtDllState State;

	int nRet=0;
	if( m_nFinalData >  m_nMaxValue)
		nRet= m_nMaxValue;
	else if( m_nFinalData < m_nMinValue )
		nRet= m_nMinValue;
	else nRet= m_nFinalData;

	return nRet;
}
TCHAR* CNumberKeyPad::GetResultStringDouble( int nNumberOfPoint )
{
	CExtDllState State;
	static TCHAR szTemp[MAX_PATH];
	static TCHAR Format[MAX_PATH];

	double fData = GetResultDouble(-1);
	if(nNumberOfPoint>-1)
	{
		_stprintf_s(Format,_T("%%.%df"),nNumberOfPoint);
		_stprintf_s( szTemp, Format, fData );

	}
	else
	{
		_stprintf_s( szTemp, _T("%.3f"), fData );
	}
	return szTemp;
}

TCHAR* CNumberKeyPad::GetResultStringInteger(void)
{
	CExtDllState State;
	static TCHAR szTemp[MAX_PATH];
	static TCHAR Format[MAX_PATH];

	int nData = GetResultInteger();
	_stprintf_s( szTemp, _T("%d"), nData );

	return szTemp;
}

double CNumberKeyPad::Math_RoundOffValue(double Value,int Cipher)
{
	CExtDllState State;
	double Ret =floor((Value*pow(10.0,Cipher-1))+0.5)/pow(10.0,Cipher-1);  
	return Ret;
}

BOOL CNumberKeyPad::Create(CWnd* pParentWnd )
{
	 return Create(MAKEINTRESOURCE(IDD_NUMBER_KEYPAD_DLG),pParentWnd);
}
BOOL CNumberKeyPad::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CExtDllState State;
	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}


HBRUSH CNumberKeyPad::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.

// 	switch (nCtlColor)
// 	{
// 	case CTLCOLOR_DLG:
// 		if(*pWnd == *this)
// 		{
// 			hbr = static_cast<HBRUSH>(GetStockObject((3)));
// 		}
// 		break;
// 
// 	case CTLCOLOR_STATIC:
// 		{
// 			pDC->SetTextColor(RGB(0, 0, 0));
// 			pDC->SetBkMode(TRANSPARENT);
// 
// 			//hbr = static_cast<HBRUSH>(GetStockObject((3)));
// 
// 		}
// 		break;
// 	}

	return hbr;
}


BOOL CNumberKeyPad::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if(pMsg->message == WM_KEYDOWN)
	{
		int nKey  = pMsg->wParam;
		if(nKey == VK_SPACE || nKey == VK_F12)
		{
				return TRUE;
		}

		else if(nKey == VK_RETURN)
		{
			//return false;
			OnBnClickedBtnNumEnter();
			OnOK();
		}
	}


	return CDialogEx::PreTranslateMessage(pMsg);
}
