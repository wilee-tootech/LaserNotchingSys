// InforSetup_IOPanel.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "InforSetup_IOPanel.h"
#include "Dsp.h"

#include "./RUN_MODULE/RunMgr.h"
//#include "./RUN_MODULE/RunningDefine.h"

//#include "./Include/EXTERN/CColorDefine.h"
#include "./Include/EXTERN/FileMgr.h"
//#include "./DIGITAL/Digital.h"


#include "NX_KEYPAD/InputEditPad.h"

#include "NX_CONFIRM/Confirm.h"


#define MAX_IO_CH					16
#define MAX_IO_INPUT			    16
#define MAX_IO_OUTPUT			    16
// CInforSetup_IOPanel

IMPLEMENT_DYNCREATE(CInforSetup_IOPanel, CDialogEx)

CInforSetup_IOPanel::CInforSetup_IOPanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInforSetup_IOPanel::IDD, pParent)
{
	//m_pCurWnd = NULL;
	m_nTimerID = 1;
	m_nTimerDelay = 500;
}

CInforSetup_IOPanel::~CInforSetup_IOPanel()
{
}

void CInforSetup_IOPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_FPSPREAD_INPUT, m_spreadInput);
	DDX_Control(pDX, IDC_FPSPREAD_OUTPUT, m_spreadOutput);
}

BEGIN_MESSAGE_MAP(CInforSetup_IOPanel, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RADIO_HEAD1, &CInforSetup_IOPanel::OnBnClickedRadioHead1)
	ON_BN_CLICKED(IDC_RADIO_HEAD2, &CInforSetup_IOPanel::OnBnClickedRadioHead2)
END_MESSAGE_MAP()


// CInforSetup_IOPanel �����Դϴ�.

#ifdef _DEBUG
void CInforSetup_IOPanel::AssertValid() const
{
	CDialogEx::AssertValid();
}

#ifndef _WIN32_WCE
void CInforSetup_IOPanel::Dump(CDumpContext& dc) const
{
	CDialogEx::Dump(dc);
}
#endif
#endif //_DEBUG


// CInforSetup_IOPanel �޽��� ó�����Դϴ�.


BOOL CInforSetup_IOPanel::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if(!m_background.m_hObject) return TRUE;

	CRect rect;
	GetClientRect(&rect);

	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = dc.SelectObject(&m_background);

	BITMAP bmap;
	m_background.GetBitmap(&bmap);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, bmap.bmWidth, bmap.bmHeight, SRCCOPY);

	dc.SelectObject(pOldBitmap);
	return TRUE;
	//return CProjectBaseView::OnEraseBkgnd(pDC);
}

/*
void CInforSetup_IOPanel::OnInitialUpdate()
{
	CProjectBaseView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	LOGFONT LogFont;

	this->GetFont()->GetLogFont(&LogFont);

	wsprintf(LogFont.lfFaceName, _T("%s"), TEXT("Tahoma"));

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

	//
	m_background.LoadBitmap(IDB_BITMAP_MAIN_BG);
}
*/



void CInforSetup_IOPanel::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	static BOOL bFirstConnected = FALSE;
	if(bShow == SW_SHOW || bShow == SW_SHOWNORMAL)
	{
		if(bFirstConnected)
		{
			Init_Input();
			Init_Output();
		}
		else
			bFirstConnected = TRUE;
	}
}


void CInforSetup_IOPanel::Display()
{
	Display_Input();
	Display_Output();

}


//////////////////////////////////////////////////////////////////////////
//Intput
//{{
void CInforSetup_IOPanel::Init_Input()
{

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);

	m_spreadInput.SetReDraw(FALSE);	
	m_spreadInput.SetMaxRows(MAX_IO_INPUT); //�� ����
	m_spreadInput.SetMaxCols(2);	  //�� ����

	CString strTemp = TEXT("");
	int i = 0;

	m_spreadInput.SetFontBold(TRUE);

	m_spreadInput.SetCol(0);
	m_spreadInput.SetRow(0);
	m_spreadInput.SetText(_T("NO"));
	m_spreadInput.SetCol(1);
	m_spreadInput.SetText(_T("STATUS"));
	m_spreadInput.SetCol(2);
	m_spreadInput.SetText(_T("I/O INPUT NAME"));


	for(i = 0; i < MAX_IO_INPUT+1; i++)
	{
		m_spreadInput.SetRowHeight(i,24);
	}
	for(i = 0; i < 3; i++)
	{
		if(i == 0)
			m_spreadInput.SetColWidth(i,12);  //9 -> 12
		else if(i == 1)
			m_spreadInput.SetColWidth(i,20);  //9 -> 20
		else
		{
			if(screenWidth <= 1500)
			{
				m_spreadInput.SetColWidth(i,40);  //46 -> 60
			} else
			{
				m_spreadInput.SetColWidth(i,72);  //46 -> 60
			}
		}
	}

	m_spreadInput.SetCol(0);
	for(i = 0; i < MAX_IO_INPUT ;i++)
	{
		m_spreadInput.SetRow(i+1);
		strTemp.Format(_T("X_%02d"),i);
		m_spreadInput.SetText(strTemp);
	}
	Open_Input();
	m_spreadInput.SetReDraw(TRUE);
}

void CInforSetup_IOPanel::Open_Input()
{
	CFileMgr* FileMgr = new CFileMgr;
	//���� ���� ���� ������ ��θ� �����´�.
	CString strPath = FileMgr->GetNowExePath();
	strPath += DIRECTORY_NAME;

	//���丮 ���� Ȯ��
	if(FileMgr->GetDirExists(strPath) == false)
	{
		//���丮�� ���� ��� ����.
		FileMgr->CreateUserDir(strPath);
	}

	strPath += DIGITAL_CONFIG_FILE_NAME;
	//���� ���� Ȯ��
	if(FileMgr->GetFileExists(strPath) == false)
	{
		//������ ���� ��� ���� ����.
		bool GetFileExists(CString a_strPath);
		if(FileMgr->CreateUserFile(strPath) == false)
		{
			delete FileMgr;
			return;
		}
	}

	CString strSection		= TEXT("");
	CString strEelemnet		= TEXT("");
	CString strReturnValue	= TEXT("");

	strSection = _T("Input");

	int i;

	m_spreadInput.SetCol(2);
	for(i = 0; i < MAX_IO_INPUT; i++)
	{
		m_spreadInput.SetRow(i+1);
		strEelemnet.Format(_T("X%02d"),i);
		strReturnValue = FileMgr->ReadString(strSection,strEelemnet,strPath);
		m_spreadInput.SetText(strReturnValue);
	}

	if(FileMgr) delete FileMgr;
}

void CInforSetup_IOPanel::Save_Input()
{
	CFileMgr* FileMgr = new CFileMgr;
	//���� ���� ���� ������ ��θ� �����´�.
	CString strPath = FileMgr->GetNowExePath();
	strPath += DIRECTORY_NAME;

	//���丮 ���� Ȯ��
	if(FileMgr->GetDirExists(strPath) == false)
	{
		//���丮�� ���� ��� ����.
		FileMgr->CreateUserDir(strPath);
	}

	strPath += DIGITAL_CONFIG_FILE_NAME;
	//���� ���� Ȯ��
	if(FileMgr->GetFileExists(strPath) == false)
	{
		//������ ���� ��� ���� ����.
		if(FileMgr->CreateUserFile(strPath) == false)
		{
			delete FileMgr;
			return;
		}
	}

	CString strSection		= TEXT("");
	CString strEelemnet		= TEXT("");
	VARIANT	varInputData;
	int i;

	strSection = "Input";


	for(i = 0; i < MAX_IO_INPUT; i++)
	{
		m_spreadInput.GetText(2,i+1,&varInputData);
		strEelemnet.Format(_T("X%02d"),i);
		FileMgr->WriteString(strSection,(LPCTSTR)(_bstr_t)varInputData.bstrVal,strEelemnet,strPath);
	}

	if(FileMgr) delete FileMgr;

	VariantClear(&varInputData);
}

//////////////////////////////////////////////////////////////////////////

//output
//{{
void CInforSetup_IOPanel::Init_Output()
{

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);

	m_spreadOutput.SetReDraw(FALSE);	
	m_spreadOutput.SetMaxRows(MAX_IO_OUTPUT); //�� ����
	m_spreadOutput.SetMaxCols(3);	  // �� ���� //NO, STATUS, I/O OUTPUT NAME, ACTION

	CString strTemp = TEXT("");
	int i = 0;

	m_spreadOutput.SetFontBold(TRUE);

	m_spreadOutput.SetCol(0);
	m_spreadOutput.SetRow(0);
	m_spreadOutput.SetText(_T("NO"));
	m_spreadOutput.SetCol(1);
	m_spreadOutput.SetText(_T("STATUS"));
	m_spreadOutput.SetCol(2);
	m_spreadOutput.SetText(_T("I/O OUTPUT NAME"));
	m_spreadOutput.SetCol(3);
	m_spreadOutput.SetText(_T("ACTION"));




	for(i = 0;i < MAX_IO_OUTPUT + 1; i++)
	{
		m_spreadOutput.SetRowHeight(i,24);
	}
	for(i=0;i<4;i++)
	{
		if(i == 0)
			m_spreadOutput.SetColWidth(i,12);
		else if(i == 1)
			m_spreadOutput.SetColWidth(i,20);

		else if(i == 3)
			m_spreadOutput.SetColWidth(i,16);

		else
		{
			if(screenWidth <= 1500)
			{
				m_spreadOutput.SetColWidth(i,30);  //46 -> 60
			} else
			{
				m_spreadOutput.SetColWidth(i,60);  //46 -> 60
			}
		}
	}

	m_spreadOutput.SetCol(0);
	for(i = 0;i < MAX_IO_OUTPUT; i++)
	{
		m_spreadOutput.SetRow(i+1);
		strTemp.Format(_T("Y_%02d"),i);
		m_spreadOutput.SetText(strTemp);
	}

	Open_Output();

	m_spreadOutput.SetReDraw(TRUE);	
}

void CInforSetup_IOPanel::Open_Output()
{
	CFileMgr* FileMgr = new CFileMgr;
	//���� ���� ���� ������ ��θ� �����´�.
	CString strPath = FileMgr->GetNowExePath();
	strPath += DIRECTORY_NAME;

	//���丮 ���� Ȯ��
	if(FileMgr->GetDirExists(strPath) == false)
	{
		//���丮�� ���� ��� ����.
		FileMgr->CreateUserDir(strPath);
	}

	strPath += DIGITAL_CONFIG_FILE_NAME;
	//���� ���� Ȯ��
	if(FileMgr->GetFileExists(strPath) == false)
	{
		//������ ���� ��� ���� ����.
		if(FileMgr->CreateUserFile(strPath) == false)
		{
			delete FileMgr;
			return;
		}
	}

	CString strSection		= TEXT("");
	CString strEelemnet		= TEXT("");
	CString strReturnValue	= TEXT("");

	strSection = "Output";

	int i;

	m_spreadOutput.SetCol(2);
	for(i = 0; i < MAX_IO_OUTPUT; i++)
	{
		m_spreadOutput.SetRow(i+1);
		strEelemnet.Format(_T("Y%02d"),i);
		strReturnValue = FileMgr->ReadString(strSection,strEelemnet,strPath);
		m_spreadOutput.SetText(strReturnValue);
	}
	if(FileMgr) delete FileMgr;
}

void CInforSetup_IOPanel::Save_Output()
{
	CFileMgr* FileMgr = new CFileMgr;
	//���� ���� ���� ������ ��θ� �����´�.
	CString strPath = FileMgr->GetNowExePath();
	strPath += DIRECTORY_NAME;

	//���丮 ���� Ȯ��
	if(FileMgr->GetDirExists(strPath) == false)
	{
		//���丮�� ���� ��� ����.
		FileMgr->CreateUserDir(strPath);
	}

	strPath += DIGITAL_CONFIG_FILE_NAME;
	//���� ���� Ȯ��
	if(FileMgr->GetFileExists(strPath) == false)
	{
		//������ ���� ��� ���� ����.
		if(FileMgr->CreateUserFile(strPath) == false)
		{
			delete FileMgr;
			return;
		}
	}

	CString strSection		= TEXT("");
	CString strEelemnet		= TEXT("");
	VARIANT	varOutputData;
	int i;

	strSection = "Output";


	for(i = 0; i < MAX_IO_OUTPUT; i++)
	{
		m_spreadOutput.GetText(2,i+1,&varOutputData);
		strEelemnet.Format(_T("Y%02d"),i);
		FileMgr->WriteString(strSection,(LPCTSTR)(_bstr_t)varOutputData.bstrVal,strEelemnet,strPath);
	}

	if(FileMgr) delete FileMgr;
	VariantClear(&varOutputData);
}

//////////////////////////////////////////////////////////////////////////

void CInforSetup_IOPanel::Display_Input()
{
	CDsp *pRTC = CDsp::GetInstance();
	//unsigned short status = pRTC->ReadIoPort();
    unsigned short status = 0;
	unsigned short value = 0;
	COLORREF color = clWhite;
	int bd = 0;
	int ch = 0;

	
	if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
	{
		status = pRTC->n_ReadIoPort(RTC_CARD_NUM_2);
		value = 0;
	}
	else
	{
		status = pRTC->n_ReadIoPort(RTC_CARD_NUM_1);
		value = 0;
	}
	m_bfInput[bd].Data = status;

	//input
	//{{
#ifndef _DIGITAL_
	m_spreadInput.SetReDraw(FALSE);
	m_spreadInput.SetActiveCell(0,0);
	for(int i = 0; i < MAX_IO_INPUT; i++)
	{
		bd = i/MAX_IO_CH;
		ch = i%MAX_IO_CH;

		
		//m_spreadInput.SetInteger(1,i+1,(int)(Digital->m_bfInput[bd].Data >> ch) & 0x01);
		//m_spreadInput.SetInteger(1,i+1,(int)(m_bfInput[bd].Data >> ch) & 0x01);
		//(int)(Digital->m_bfInput[bd].Data >> ch) & 0x01
		//color	  = clLime;
		//m_spreadInput.SetInteger(1,i+1,1);

		if((m_bfInput[bd].Data >> ch) & 0x01)
		{
			//strStatus = TEXT("STATUS : ON");
			color	  = clLime;
			m_spreadInput.SetInteger(1,i+1,1);
		}
		else
		{
			//strStatus = TEXT("STATUS : OFF");
			color	  = clWhite;
			m_spreadInput.SetInteger(1,i+1,0);
		}
		m_spreadInput.SetBackColor(color);

	}

	m_spreadInput.SetReDraw(TRUE);
#endif
	//}}
}

void CInforSetup_IOPanel::Display_Output()
{

	CDsp *pRTC = CDsp::GetInstance();
	

	unsigned short status = 0;
	unsigned short value = 0;

	if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
	{
		status = pRTC->n_ReadIoPort(RTC_CARD_NUM_2);
		value = 0;
		status = n_get_io_status(RTC_CARD_NUM_2);
	}
	else
	{
		status = pRTC->n_ReadIoPort(RTC_CARD_NUM_1);
		value = 0;
		status = pRTC->n_GetIoStatus(RTC_CARD_NUM_1);
	}

	//unsigned short status = pRTC->ReadIoPort();
	//unsigned short value = 0;

	//status = pRTC->GetIoStatus();

	

	//value = status & (unsigned short)((double)pow(2.0, nPortNum));
	//value = value >> nPortNum;


	////pRTC->OutputIO(0, value);

	//
	//if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
	//{
	//	if(value)
	//		pRTC->nOutputIO(RTC_CARD_NUM_2,nPortNum, FALSE);
	//	else
	//		pRTC->nOutputIO(RTC_CARD_NUM_2,nPortNum, TRUE);
	//}
	//else
	//{
	//	if(value)
	//		pRTC->nOutputIO(RTC_CARD_NUM_1,nPortNum, FALSE);
	//	else
	//		pRTC->nOutputIO(RTC_CARD_NUM_1,nPortNum, TRUE);
	//}

#ifndef _DIGITAL_
	m_spreadOutput.SetReDraw(FALSE);
	m_spreadOutput.SetActiveCell(0,0);
	CString strStatus = TEXT("");
	COLORREF color = clWhite;

	VARIANT var;
	BSTR bstrValue;

	//UpdateData(TRUE);
	int bd = 0;
	int ch = 0;

	m_bfOutput[bd].Data  =  status;

	for(int i = 0; i < MAX_IO_OUTPUT ; i++)
	{


		bd = i/MAX_IO_CH;
		ch = i%MAX_IO_CH;

		//{{
		//bd += IO_OUTPUT_START_MODULE_NUM;
		//}}

		m_spreadOutput.SetCol(1);
		m_spreadOutput.SetRow(i+1);

		//if((Digital->m_bfOutput[bd].Data >> ch) & 0x01)
		if((m_bfOutput[bd].Data >> ch) & 0x01)
		{
			strStatus = TEXT("STATUS : ON");
			color	  = clLime;
			m_spreadOutput.SetInteger(1,i+1,1);
		}
		else
		{
			strStatus = TEXT("STATUS : OFF");
			color	  = clWhite;
			m_spreadOutput.SetInteger(1,i+1,0);
		}


		bstrValue = strStatus.AllocSysString();
		V_VT(&var) = VT_BSTR; 
		V_BSTR(&var) = bstrValue;
		m_spreadOutput.SetText(1,i+1,var);
		SysFreeString(bstrValue);


		m_spreadOutput.SetBackColor(color);



		m_spreadOutput.SetCol(3);
		m_spreadOutput.SetRow(i+1);

		//if((Digital->m_bfOutput[bd].Data >> ch) & 0x01)

		if((m_bfOutput[bd].Data >> ch) & 0x01)//if( 0x01)
		{
			color = clLime;	
			strStatus = "ON";
		}
		else
		{
			color = clWhite;
			strStatus = "OFF";
		}

		bstrValue		= strStatus.AllocSysString();
		V_VT(&var)		= VT_BSTR;
		V_BSTR(&var)	= bstrValue;
		m_spreadOutput.SetText(3,i+1,var);
		m_spreadOutput.SetBackColor(color);	
	}
	m_spreadOutput.SetReDraw(TRUE);

	SysFreeString(bstrValue);
	VariantClear(&var);
#endif

}

//////////////////////////////////////////////////////////////////////////BEGIN_EVENTSINK_MAP(CInforSetup_IOPanel, CProjectBaseView)
BEGIN_EVENTSINK_MAP(CInforSetup_IOPanel, CProjectBaseView)
	ON_EVENT(CInforSetup_IOPanel, IDC_FPSPREAD_INPUT, 5, CInforSetup_IOPanel::ClickFpspreadInput, VTS_I4 VTS_I4)
	ON_EVENT(CInforSetup_IOPanel, IDC_BTN_INFO_INPUT_OPEN, DISPID_CLICK, CInforSetup_IOPanel::ClickBtnInfoInputOpen, VTS_NONE)
	ON_EVENT(CInforSetup_IOPanel, IDC_BTN_INFO_INPUT_SAVE, DISPID_CLICK, CInforSetup_IOPanel::ClickBtnInfoInputSave, VTS_NONE)
	ON_EVENT(CInforSetup_IOPanel, IDC_FPSPREAD_OUTPUT, 5, CInforSetup_IOPanel::ClickFpspreadOutput, VTS_I4 VTS_I4)
	ON_EVENT(CInforSetup_IOPanel, IDC_BTN_INFO_OUTPUT_OPEN, DISPID_CLICK, CInforSetup_IOPanel::ClickBtnInfoOutputOpen, VTS_NONE)
	ON_EVENT(CInforSetup_IOPanel, IDC_BTN_INFO_OUTPUT_SAVE, DISPID_CLICK, CInforSetup_IOPanel::ClickBtnInfoOutputSave, VTS_NONE)
END_EVENTSINK_MAP()


void CInforSetup_IOPanel::ClickFpspreadInput(long Col, long Row)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if(Col != 2) return;
	if(Row <  1) return;

	CInputEditPad InputEditPad;
	VARIANT		   varOldData;

	m_spreadInput.SetCol(Col);
	m_spreadInput.SetRow(Row);

	m_spreadInput.GetText(Col,Row,&varOldData);
	InputEditPad.m_strOldData = varOldData.bstrVal;

	if(InputEditPad.DoModal() == IDOK)
	{
		m_spreadInput.SetText(InputEditPad.m_strNewData);
	}

	VariantClear(&varOldData);
}





void CInforSetup_IOPanel::ClickBtnInfoInputOpen()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if(RunMgr->GetRunMode() != RUN_MODE::STOP) return;

	CConfirm confirm;

	confirm.SetCaption(_T("IO - Input List�� ���ڽ��ϱ�?"), FALSE, CConfirm::E_QUESTION);

	if(confirm.DoModal() == IDOK)
	{
		Open_Input();
	}
}


void CInforSetup_IOPanel::ClickBtnInfoInputSave()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if(RunMgr->GetRunMode() != STOP) return;

	CConfirm confirm;

	confirm.SetCaption(_T("IO - Input List�� �����Ͻðڽ��ϱ�?"), FALSE, CConfirm::E_QUESTION);

	if(confirm.DoModal() == IDOK)
	{
		Save_Input();
	}
}


void CInforSetup_IOPanel::ClickFpspreadOutput(long Col, long Row)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if(RunMgr->GetRunMode() != RUN_MODE::STOP) return;

	int bd = 0;
	int ch = 0;
	CDsp *pRTC = CDsp::GetInstance();

	m_spreadOutput.SetReDraw(FALSE);

	unsigned short status = 0;
	unsigned short value = 0;
	if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
	{
		status = pRTC->n_ReadIoPort(RTC_CARD_NUM_2);
		value = 0;
		status = n_get_io_status(RTC_CARD_NUM_2);
	}
	else
	{
		status = pRTC->n_ReadIoPort(RTC_CARD_NUM_1);
		value = 0;
		status = pRTC->n_GetIoStatus(RTC_CARD_NUM_1);
	}

	m_bfOutput[bd].Data = status;

	
	if(Col == 3 && Row > 0)
	{
		bd = (Row-1)/MAX_IO_CH;
		ch = (Row-1)%MAX_IO_CH;

		//pRTC->nOutputIO(RTC_CARD_NUM_1,nPortNum, TRUE);
		//Digital->m_bfOutput[bd].Data ^= (0x01 << ch);
		m_bfOutput[bd].Data ^= (0x01 << ch);
		
	}

	n_write_io_port(RTC_CARD_NUM_1,m_bfOutput[bd].Data);
	if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
	{
		status = pRTC->n_GetIoStatus(RTC_CARD_NUM_2);
	} else
	{
		status = pRTC->n_GetIoStatus(RTC_CARD_NUM_1);
	}


	if(Col != 2) return;
	if(Row <  1) return;


	CInputEditPad  InputEdit;
	VARIANT		   varOldData;
	VARIANT		   varNewData;
	BSTR		   bstr;
	CString		   strTemp;

	m_spreadOutput.GetText(Col,Row,&varOldData);
	InputEdit.m_strOldData = varOldData.bstrVal;

	if(InputEdit.DoModal() == IDOK)
	{
		bstr = InputEdit.m_strNewData.AllocSysString();
		V_VT(&varNewData) = VT_BSTR; V_BSTR(&varNewData) = bstr;
		m_spreadOutput.SetText(Col,Row,varNewData);
		SysFreeString(bstr);
	}
	m_spreadOutput.SetReDraw(TRUE);

	VariantClear(&varOldData);
	VariantClear(&varNewData);
}


void CInforSetup_IOPanel::ClickBtnInfoOutputOpen()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if(RunMgr->GetRunMode() != RUN_MODE::STOP) return;

	CConfirm confirm;

	confirm.SetCaption(_T("IO - Output List�� ���ڽ��ϱ�?"), FALSE, CConfirm::E_QUESTION);

	if(confirm.DoModal() == IDOK)
	{
		Open_Output();
	}
}


void CInforSetup_IOPanel::ClickBtnInfoOutputSave()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if(RunMgr->GetRunMode() != RUN_MODE::STOP) return;

	CConfirm confirm;

	confirm.SetCaption(_T("IO - Output List�� �����Ͻðڽ��ϱ�?"), FALSE, CConfirm::E_QUESTION);

	if(confirm.DoModal() == IDOK)
	{
		Save_Output();
	}	
}


BOOL CInforSetup_IOPanel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

    ShowScrollBar(SB_BOTH, FALSE);

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    if (screenWidth < 1500)
    {
        // 70% ����
        double scale = 0.75;

        // ���̾�α� ũ�� ����
        CRect dlgRect;
        GetWindowRect(&dlgRect);
        int newWidth = static_cast<int>(dlgRect.Width() * scale);
        int newHeight = static_cast<int>(dlgRect.Height() * scale);
        MoveWindow(dlgRect.left, dlgRect.top, newWidth, newHeight);

        // ���� ��Ʈ�� ũ�� ����
        CWnd* pWnd = GetWindow(GW_CHILD);
        while (pWnd)
        {
            CRect rect;
            pWnd->GetWindowRect(&rect);
            ScreenToClient(&rect); // ���̾�α� ��ǥ�� ��ȯ

            int newCtrlWidth = static_cast<int>(rect.Width() * scale);
            int newCtrlHeight = static_cast<int>(rect.Height() * scale);
            int newCtrlX = static_cast<int>(rect.left * scale);
            int newCtrlY = static_cast<int>(rect.top * scale);

            pWnd->MoveWindow(newCtrlX, newCtrlY, newCtrlWidth, newCtrlHeight);

            pWnd = pWnd->GetNextWindow();
        }
    }

	LOGFONT LogFont;

	this->GetFont()->GetLogFont(&LogFont);

	wsprintf(LogFont.lfFaceName, _T("%s"), TEXT("Tahoma"));

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

	//
	m_background.LoadBitmap(IDB_BITMAP_MAIN_BG);

	Init_Input();
	Init_Output();

	SetTimer(m_nTimerID,m_nTimerDelay,NULL);

	SetDlgItemText(IDC_IOPANEL_TITLE, _T("HEAD1 SETUP I/O"));

//	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	if(screenWidth <= 1500)
	{
		CWnd* pInputWnd = GetDlgItem(IDC_FPSPREAD_INPUT);
		if (pInputWnd)
		{
			// IDC_FPSPREAD_INPUT ��Ʈ���� ���� ũ�� ���
			CRect inputRect;
			pInputWnd->GetWindowRect(&inputRect);
			ScreenToClient(&inputRect); // Ŭ���̾�Ʈ ��ǥ�� ��ȯ

			// ũ�� ���̱� (��: 70%�� ���̱�)
			int inputWidth = static_cast<int>(inputRect.Width() * 0.7);
			int inputHeight = static_cast<int>(inputRect.Height() );

			// �� ũ��� IDC_FPSPREAD_INPUT ��Ʈ�� ũ�� ����
			pInputWnd->MoveWindow(inputRect.left, inputRect.top, inputWidth, inputHeight);

			// IDC_FPSPREAD_OUTPUT�� �������� �̵���Ű��
			CWnd* pOutputWnd = GetDlgItem(IDC_FPSPREAD_OUTPUT);
			if (pOutputWnd)
			{
				// IDC_FPSPREAD_OUTPUT�� ���� ��ġ�� ũ�� ���
				CRect outputRect;
				pOutputWnd->GetWindowRect(&outputRect);
				ScreenToClient(&outputRect); // Ŭ���̾�Ʈ ��ǥ�� ��ȯ

				// IDC_FPSPREAD_INPUT�� ũ�Ⱑ �پ�� ��ŭ, IDC_FPSPREAD_OUTPUT�� �������� �̵�
				int newOutputLeft = outputRect.left - (inputRect.Width() - inputWidth); // ũ�� ���̸�ŭ �������� �̵�

				// ���ο� ��ġ�� ũ��� IDC_FPSPREAD_OUTPUT �̵�
				pOutputWnd->MoveWindow(newOutputLeft, outputRect.top, outputRect.Width(), outputRect.Height());
			}

			CWnd* pInputDisplayWnd = GetDlgItem(1002); // CText
			if (pInputDisplayWnd)
			{
				// IDC_INPUT_DISPLAY�� ���� ũ�� ���
				CRect inputDisplayRect;
				pInputDisplayWnd->GetWindowRect(&inputDisplayRect);
				ScreenToClient(&inputDisplayRect); // Ŭ���̾�Ʈ ��ǥ�� ��ȯ

				// CText ��Ʈ�ѵ� �����ϰ� ũ�� ���̱�
				int inputDisplayWidth = static_cast<int>(inputDisplayRect.Width() * 0.7);
				int inputDisplayHeight = static_cast<int>(inputDisplayRect.Height());

				// �� ũ��� IDC_INPUT_DISPLAY ũ�� ����
				pInputDisplayWnd->MoveWindow(inputDisplayRect.left, inputDisplayRect.top, inputDisplayWidth, inputDisplayHeight);
			}

			CWnd* pOutputDisplayWnd = GetDlgItem(1003); // CText
			if (pOutputDisplayWnd)
			{
				// IDC_OUTPUT_DISPLAY�� ���� ��ġ�� ũ�� ���
				CRect outputDisplayRect;
				pOutputDisplayWnd->GetWindowRect(&outputDisplayRect);
				ScreenToClient(&outputDisplayRect); // Ŭ���̾�Ʈ ��ǥ�� ��ȯ

				// IDC_FPSPREAD_INPUT�� �پ�� ��ŭ, IDC_OUTPUT_DISPLAY�� �������� �̵�
				int newOutputDisplayLeft = outputDisplayRect.left - (inputRect.Width() - inputWidth); // ũ�� ���̸�ŭ �������� �̵�

				// ���ο� ��ġ�� IDC_OUTPUT_DISPLAY �̵�
				pOutputDisplayWnd->MoveWindow(newOutputDisplayLeft, outputDisplayRect.top, outputDisplayRect.Width(), outputDisplayRect.Height());
			}
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
}


void CInforSetup_IOPanel::OnTimer(UINT_PTR nIDEvent)
{
	KillTimer(nIDEvent);

	Display();
	CDialogEx::OnTimer(nIDEvent);

	SetTimer(m_nTimerID,m_nTimerDelay,NULL);
}


void CInforSetup_IOPanel::OnBnClickedRadioHead1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SetDlgItemText(IDC_IOPANEL_TITLE, _T("HEAD1 SETUP I/O"));
}


void CInforSetup_IOPanel::OnBnClickedRadioHead2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SetDlgItemText(IDC_IOPANEL_TITLE, _T("HEAD2 SETUP I/O"));
}
