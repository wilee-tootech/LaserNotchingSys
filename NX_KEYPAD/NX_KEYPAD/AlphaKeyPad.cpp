// AlphaKeyPad.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "AlphaKeyPad.h"
#include "afxdialogex.h"
#include "ExtDllState.h"
#include "resource.h"



// CAlphaKeyPad 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAlphaKeyPad, CDialogEx)

CAlphaKeyPad::CAlphaKeyPad(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ALPHA_KEYPAD_DLG, pParent)
	,m_strOldData(_T(""))
	,m_strNewData(_T(""))
	,m_strNewDataAsterisk(_T(""))
	,m_bAsterisk(FALSE)
{
	CExtDllState State;
	
}

CAlphaKeyPad::~CAlphaKeyPad()
{
	CExtDllState State;
}

void CAlphaKeyPad::DoDataExchange(CDataExchange* pDX)
{
	CExtDllState State;
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_STATIC_OLDDATA, m_strOldData);
	DDX_Text(pDX, IDC_STATIC_NEWDATA, m_strNewDataAsterisk);

	DDX_Control(pDX,IDC_BTN_1		,m_StyleButton[0]);
	DDX_Control(pDX,IDC_BTN_2		,m_StyleButton[1]);
	DDX_Control(pDX,IDC_BTN_3		,m_StyleButton[2]);
	DDX_Control(pDX,IDC_BTN_4		,m_StyleButton[3]);
	DDX_Control(pDX,IDC_BTN_5		,m_StyleButton[4]);//5
	DDX_Control(pDX,IDC_BTN_6		,m_StyleButton[5]);
	DDX_Control(pDX,IDC_BTN_7		,m_StyleButton[6]);
	DDX_Control(pDX,IDC_BTN_8		,m_StyleButton[7]);
	DDX_Control(pDX,IDC_BTN_9		,m_StyleButton[8]);
	DDX_Control(pDX,IDC_BTN_0		,m_StyleButton[9]);//10
	DDX_Control(pDX,IDC_BTN_HYPHEN	,m_StyleButton[10]);
	DDX_Control(pDX,IDC_BTN_UNDERBAR,m_StyleButton[11]);
	DDX_Control(pDX,IDC_BTN_Q		,m_StyleButton[12]);
	DDX_Control(pDX,IDC_BTN_W		,m_StyleButton[13]);
	DDX_Control(pDX,IDC_BTN_E		,m_StyleButton[14]);//15
	DDX_Control(pDX,IDC_BTN_R		,m_StyleButton[15]);
	DDX_Control(pDX,IDC_BTN_T		,m_StyleButton[16]);
	DDX_Control(pDX,IDC_BTN_Y		,m_StyleButton[17]);
	DDX_Control(pDX,IDC_BTN_U		,m_StyleButton[18]);
	DDX_Control(pDX,IDC_BTN_I		,m_StyleButton[19]);//20
	DDX_Control(pDX,IDC_BTN_O		,m_StyleButton[20]);
	DDX_Control(pDX,IDC_BTN_P		,m_StyleButton[21]);
	DDX_Control(pDX,IDC_BTN_A		,m_StyleButton[22]);
	DDX_Control(pDX,IDC_BTN_S		,m_StyleButton[23]);
	DDX_Control(pDX,IDC_BTN_D		,m_StyleButton[24]);//25
	DDX_Control(pDX,IDC_BTN_F		,m_StyleButton[25]);
	DDX_Control(pDX,IDC_BTN_G		,m_StyleButton[26]);
	DDX_Control(pDX,IDC_BTN_H		,m_StyleButton[27]);
	DDX_Control(pDX,IDC_BTN_J		,m_StyleButton[28]);
	DDX_Control(pDX,IDC_BTN_K		,m_StyleButton[29]);//30
	DDX_Control(pDX,IDC_BTN_L		,m_StyleButton[30]);
	DDX_Control(pDX,IDC_BTN_Z		,m_StyleButton[31]);
	DDX_Control(pDX,IDC_BTN_X		,m_StyleButton[32]);
	DDX_Control(pDX,IDC_BTN_C		,m_StyleButton[33]);
	DDX_Control(pDX,IDC_BTN_V		,m_StyleButton[34]);//35
	DDX_Control(pDX,IDC_BTN_B		,m_StyleButton[35]);
	DDX_Control(pDX,IDC_BTN_N		,m_StyleButton[36]);
	DDX_Control(pDX,IDC_BTN_M		,m_StyleButton[37]);
	DDX_Control(pDX,IDC_BTN_COMMA	,m_StyleButton[38]);
	DDX_Control(pDX,IDC_BTN_DOT		,m_StyleButton[39]);//40
	DDX_Control(pDX,IDC_BTN_CLEAR	,m_StyleButton[40]);
	DDX_Control(pDX,IDC_BTN_CANCEL	,m_StyleButton[41]);
	DDX_Control(pDX,IDC_BTN_ENTER	,m_StyleButton[42]);
}


BEGIN_MESSAGE_MAP(CAlphaKeyPad, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ENTER, &CAlphaKeyPad::OnBnClickedBtnEnter)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CAlphaKeyPad::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CAlphaKeyPad::OnBnClickedBtnCancel)
	ON_COMMAND_RANGE(IDC_BTN_1,IDC_BTN_ENTER,OnKeyInput)
	ON_WM_CLOSE()
//	ON_WM_TIMER()
ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CAlphaKeyPad 메시지 처리기입니다.


void CAlphaKeyPad::OnBnClickedBtnEnter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CExtDllState State;
	OnOK();

}


void CAlphaKeyPad::OnBnClickedBtnClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CExtDllState State;
	/*m_strNewData = TEXT("");
	m_strNewDataAsterisk = TEXT("");
	UpdateData(FALSE);*/


	m_strNewData = _T("");
	m_strNewDataAsterisk = _T("");
	UpdateData(FALSE);
}


void CAlphaKeyPad::OnBnClickedBtnCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CExtDllState State;
	OnCancel();
}

void CAlphaKeyPad::OnKeyInput(UINT nID)
{
	CExtDllState State;
	CString strSelectKey = _T("");
	switch (nID)
	{
	case IDC_BTN_1:			strSelectKey = "1"; break;
	case IDC_BTN_2:			strSelectKey = "2"; break;
	case IDC_BTN_3:			strSelectKey = "3"; break;
	case IDC_BTN_4:         strSelectKey = "4"; break;
	case IDC_BTN_5:			strSelectKey = "5"; break;
	case IDC_BTN_6:			strSelectKey = "6"; break;
	case IDC_BTN_7:         strSelectKey = "7"; break;
	case IDC_BTN_8:         strSelectKey = "8"; break;
	case IDC_BTN_9:         strSelectKey = "9"; break;
	case IDC_BTN_0:         strSelectKey = "0"; break;
	case IDC_BTN_HYPHEN:    strSelectKey = "-"; break;
	case IDC_BTN_UNDERBAR:  strSelectKey = "_"; break;
	case IDC_BTN_Q:         strSelectKey = "Q"; break;
	case IDC_BTN_W:         strSelectKey = "W"; break;
	case IDC_BTN_E:         strSelectKey = "E"; break;
	case IDC_BTN_R:         strSelectKey = "R"; break;
	case IDC_BTN_T:         strSelectKey = "T"; break;
	case IDC_BTN_Y:         strSelectKey = "Y"; break;
	case IDC_BTN_U:         strSelectKey = "U"; break;
	case IDC_BTN_I:         strSelectKey = "I"; break;
	case IDC_BTN_O:         strSelectKey = "O"; break;
	case IDC_BTN_P:         strSelectKey = "P"; break;
	case IDC_BTN_A:         strSelectKey = "A"; break;
	case IDC_BTN_S:         strSelectKey = "S"; break;
	case IDC_BTN_D:         strSelectKey = "D"; break;
	case IDC_BTN_F:         strSelectKey = "F"; break;
	case IDC_BTN_G:         strSelectKey = "G"; break;
	case IDC_BTN_H:         strSelectKey = "H"; break;
	case IDC_BTN_J:         strSelectKey = "J"; break;
	case IDC_BTN_K:         strSelectKey = "K"; break;
	case IDC_BTN_L:         strSelectKey = "L"; break;
	case IDC_BTN_Z:         strSelectKey = "Z"; break;
	case IDC_BTN_X:         strSelectKey = "X"; break;
	case IDC_BTN_C:         strSelectKey = "C"; break;
	case IDC_BTN_V:         strSelectKey = "V"; break;
	case IDC_BTN_B:         strSelectKey = "B"; break;
	case IDC_BTN_N:         strSelectKey = "N"; break;
	case IDC_BTN_M:         strSelectKey = "M"; break;
	case IDC_BTN_COMMA:     strSelectKey = ","; break;
	case IDC_BTN_DOT:       strSelectKey = "."; break;
	}


	/*if(m_bAsterisk)
	{
		for(int i = 0; i < m_strNewData.GetLength(); i++)
			m_strNewDataAsterisk += _T("*");
	}
	else*/
	{
		m_strNewData += strSelectKey; 
		m_strNewDataAsterisk = m_strNewData;
	}

	UpdateData(FALSE);

}


BOOL CAlphaKeyPad::OnInitDialog()
{
	CExtDllState State;
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	int i = 0;
	for(i = 0; i < MAX_ALPHA_KEY_BTN; i++)
	{	
		m_StyleButton[i].SetShade(CShadeButtonST::SHS_SOFTBUMP);
		m_StyleButton[i].SetAlign(CButtonST::ST_ALIGN_HORIZ);

	}


	LOGFONT LogFont;

	this->GetFont()->GetLogFont(&LogFont);

	wsprintf(LogFont.lfFaceName, _T("%s"), _T("Tahoma"));

	LogFont.lfHeight = 15;
	LogFont.lfWeight = FW_BOLD;

	CFont Font;
	Font.CreateFontIndirect(&LogFont);

	CWnd* pWnd = this->GetWindow(GW_CHILD);

	while(pWnd)
	{
		pWnd->SetFont(&Font);
		pWnd = pWnd->GetNextWindow();
	}


	Font.Detach();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


BOOL CAlphaKeyPad::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CExtDllState State;

	


	if(pMsg->message == WM_KEYDOWN)
	{
		int nKey  = pMsg->wParam;
		char cKey = nKey;
		m_strNewDataAsterisk = _T("");

		// 2021.09.17 김준혁 
		// Space바 입력시 기존에 누른 키가 있다면 동일한 키가 입력되고
		// 아무 키를 입력하지 않았다면 Default값으로 '1'이 넘어온다
		// 고치기는 했지만 왜 고쳐진지는 모르겠다.
		if(nKey == VK_SPACE || nKey == VK_F12)
		{
			return TRUE;
		}



		BOOL bShift = ((GetKeyState(VK_SHIFT	) & 0x8000) != 0); // Shift 키가 눌렸는지의 여부 저장
		BOOL bCtrl  = ((GetKeyState(VK_CONTROL	) & 0x8000) != 0); // Control 키가 눌렸는지의 여부 저장
		BOOL bAlt   = ((GetKeyState(VK_MENU		) & 0x8000) != 0);

		//caps lock == VK_CAPITAL
		if( (nKey >= 48 && nKey <= 57) || (nKey >=65 && nKey <= 90) || (bShift && nKey == 189 ) || (nKey == 189) || (nKey == 190) || (nKey == 188))
		{
			if		(nKey == 188			)	cKey = ',';
			else if	(bShift && nKey == 189	)	cKey = '_';
			else if	(nKey == 189			)	cKey = '-';
			else if	(nKey == 190			)	cKey = '.';

			m_strNewData += cKey;

			if(m_bAsterisk)
			{
				for(int i = 0; i < m_strNewData.GetLength(); i++)
					m_strNewDataAsterisk += _T("*");
			}
			else
			{
				m_strNewDataAsterisk = m_strNewData;
			}

			UpdateData(FALSE);
		}


		else if(nKey == VK_BACK) //BackSpace
		{
			if(!m_strNewData.IsEmpty())
			{
				int nLength = m_strNewData.GetLength();
				if(nLength == 1) m_strNewData = _T("");
				else			 m_strNewData.Delete(nLength-1,1);

				if(m_bAsterisk)
				{
					for(int i = 0; i < m_strNewData.GetLength(); i++)
						m_strNewDataAsterisk += _T("*");
				}
				else
				{
					m_strNewDataAsterisk = m_strNewData;
				}

				UpdateData(FALSE);
			}
		}
		else if(nKey == VK_RETURN)
		{
			//return false;
			OnOK();
		}

		




	}
 	return CDialogEx::PreTranslateMessage(pMsg);
}


INT_PTR CAlphaKeyPad::DoModal()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CExtDllState State;
	return CDialogEx::DoModal();
}


BOOL CAlphaKeyPad::Create(CWnd* pParentWnd )
{
	return Create(MAKEINTRESOURCE(IDD_ALPHA_KEYPAD_DLG),pParentWnd);
}

BOOL CAlphaKeyPad::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CExtDllState State;
	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}


void CAlphaKeyPad::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
}


//void CAlphaKeyPad::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//
//	CDialogEx::OnTimer(nIDEvent);
//}


//void CAlphaKeyPad::OnOK()
//{
//	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//
//	CDialogEx::OnOK();
//}


HBRUSH CAlphaKeyPad::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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



 void CAlphaKeyPad::SetStrOldData(CString value)
 {

	 m_strOldData = value;

 }


 CString CAlphaKeyPad::GetStrOldData()
 {

	 return m_strOldData;
 }

 CString CAlphaKeyPad::GetStrNewData()
 {
	 return m_strNewData;
 }

 void CAlphaKeyPad::SetAsterisk(BOOL isuse)
 {
	 m_bAsterisk = isuse;
 }

