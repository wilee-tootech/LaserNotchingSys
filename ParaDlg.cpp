// ParaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MK.h"
#include "ParaDlg.h"
// 2003.06.04 Parameter Detail Set 관련
#include "MainFrm.h"
#include "MKDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ParaDlg dialog
#include "def.h"

ParaDlg::ParaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ParaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ParaDlg)
	m_nFPS_DELAY = 0;
	m_nJUMP_DELAY = 0;
	m_nJUMP_STEP = 0;
	m_fLAMP_POWER = 0.0f;
	m_nLASER_OFF_DELAY = 0;
	m_nLASER_ON_DELAY = 0;
	m_nMARK_DELAY = 0;
	m_bPOWER_AUTO = FALSE;
	m_sLASER_POWER = _T("");
	m_fPULSE_WIDTH = 0.0f;
	m_fQSW_FREQ = 0.0f;
	m_nSTEP_PERIOD = 0;
	m_nSTROKE_DELAY = 0;
	m_nMARK_STEP = 0;
	m_FileName = _T("");
	m_SavedAperture = 0.0f;
	m_SavedPower = 0.0f;
	m_SavedCurrent = 0.0f;
	m_SavedDate = _T("");
	//}}AFX_DATA_INIT
}

void ParaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ParaDlg)
	DDX_Text(pDX, IDC_FPS_DELAY, m_nFPS_DELAY);
	DDV_MinMaxInt(pDX, m_nFPS_DELAY, 1, 1000);
	DDX_Text(pDX, IDC_JUMP_DELAY, m_nJUMP_DELAY);
	DDV_MinMaxInt(pDX, m_nJUMP_DELAY, 1, 1000);
	DDX_Text(pDX, IDC_JUMP_STEP, m_nJUMP_STEP);
	DDV_MinMaxInt(pDX, m_nJUMP_STEP, 1, 1000);
	DDX_Text(pDX, IDC_LAMP_POWER, m_fLAMP_POWER);
	DDV_MinMaxFloat(pDX, m_fLAMP_POWER, 0.f, 100.f);
	DDX_Text(pDX, IDC_LASER_OFF_DELAY, m_nLASER_OFF_DELAY);
	DDV_MinMaxInt(pDX, m_nLASER_OFF_DELAY, 1, 21000);
	DDX_Text(pDX, IDC_LASER_ON_DELAY, m_nLASER_ON_DELAY);
	DDV_MinMaxInt(pDX, m_nLASER_ON_DELAY, 1, 21000);
	DDX_Text(pDX, IDC_MARK_DELAY, m_nMARK_DELAY);
	DDV_MinMaxInt(pDX, m_nMARK_DELAY, 1, 1000);
	DDX_Check(pDX, IDC_POWER_AUTO, m_bPOWER_AUTO);
	DDX_Text(pDX, IDC_LASER_POWER, m_sLASER_POWER);
	DDX_Text(pDX, IDC_PULSE_WIDTH, m_fPULSE_WIDTH);
	DDV_MinMaxFloat(pDX, m_fPULSE_WIDTH, 1.f, 100.f);
	DDX_Text(pDX, IDC_QSW_FREQ, m_fQSW_FREQ);
	DDV_MinMaxFloat(pDX, m_fQSW_FREQ, 1.f, 100.f);
	DDX_Text(pDX, IDC_STEP_PERIOD, m_nSTEP_PERIOD);
	DDV_MinMaxInt(pDX, m_nSTEP_PERIOD, 1, 1000);
	DDX_Text(pDX, IDC_STROKE_DELAY, m_nSTROKE_DELAY);
	DDV_MinMaxInt(pDX, m_nSTROKE_DELAY, 1, 1000);
	DDX_Text(pDX, IDC_MARK_STEP, m_nMARK_STEP);
	DDV_MinMaxInt(pDX, m_nMARK_STEP, 1, 1000);
	DDX_Text(pDX, IDC_FILE_NAME, m_FileName);
	DDX_Text(pDX, IDC_SAVED_APERTURE, m_SavedAperture);
	DDX_Text(pDX, IDC_SAVED_POWER, m_SavedPower);
	DDX_Text(pDX, IDC_SAVED_CURRENT, m_SavedCurrent);
	DDX_Text(pDX, IDC_SAVED_DATE, m_SavedDate);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ParaDlg, CDialog)
	//{{AFX_MSG_MAP(ParaDlg)
	ON_BN_CLICKED(IDC_FILE_OPEN, OnFileOpen)
	ON_BN_CLICKED(IDC_FILE_SAVE, OnFileSave)
	ON_CBN_SELCHANGE(IDC_BITMAP_COMBO, OnSelchangeBitmapCombo)
	ON_CBN_EDITCHANGE(IDC_BITMAP_COMBO, OnEditchangeBitmapCombo)
	ON_BN_CLICKED(IDC_PARA_EDIT, OnParaEdit)
	ON_BN_CLICKED(IDC_FILE_NAME, OnFileName)
	ON_BN_CLICKED(IDC_RECORDING_MODE, OnRecordingMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

// ParaDlg message handlers
void ParaDlg::OnFileOpen() 
{
	// TODO: Add your control notification handler code here
	CString filepath;
	char filepathname[256];
	int i;

	// 2003.07.02 권한 부분 수정 start
	if (FALSE == m_pDoc->m_user.VerifyWork(OPEN_SCR))
	{
//		AfxMessageBox("Not have authority.", MB_OK);
		AfxMessageBox(IDS_AUTHORITY, MB_OK);
		return;
	}
	// 2003.07.02 권한 부분 수정 end

	// 화일 선택 dialog box 를 올린다
	CFileDialog dlgfileopen(TRUE, "scr", m_pDoc->m_scribeFilePath+"\\"+"*.scr" /*NULL*/, OFN_OVERWRITEPROMPT, "Scribe File (*.scr)",NULL);
	if (dlgfileopen.DoModal()==IDOK)
	{	
		// 선택된 파일 이름을 얻는다
		m_pDoc->m_scribeFile = dlgfileopen.GetFileName();
		filepath = dlgfileopen.GetPathName();

		for( i=0; i<filepath.GetLength(); i++)
			filepathname[i] = filepath.GetAt(i); 

		filepathname[filepath.GetLength()] = '\0';

		// 화일을 로드 한다	
		m_pDoc->loadfile(filepathname, SCRIBE1);

		for(i=0; i < MAXPARA; i++)
		{
			strcpy(m_Parameter[i].n, m_pParameter[i].n);
			m_Parameter[i].ss = m_pParameter[i].ss;
			m_Parameter[i].js = m_pParameter[i].js;
			m_Parameter[i].sp = m_pParameter[i].sp;
			m_Parameter[i].md = m_pParameter[i].md;
			m_Parameter[i].jd = m_pParameter[i].jd;
			m_Parameter[i].sd = m_pParameter[i].sd;
			m_Parameter[i].lod= m_pParameter[i].lod;
			m_Parameter[i].lfd= m_pParameter[i].lfd;
			m_Parameter[i].lcd= m_pParameter[i].lcd;
			m_Parameter[i].num= m_pParameter[i].num;
			m_Parameter[i].c = m_pParameter[i].c;
			m_Parameter[i].lc = m_pParameter[i].lc;
			m_Parameter[i].qspw = m_pParameter[i].qspw;
			m_Parameter[i].qsf = m_pParameter[i].qsf;
			m_Parameter[i].ba = m_pParameter[i].ba;
			m_Parameter[i].as = m_pParameter[i].as;
			m_Parameter[i].kpc = m_pParameter[i].kpc;
			m_Parameter[i].fps = m_pParameter[i].fps;
			m_Parameter[i].dw = m_pParameter[i].dw;
			m_Parameter[i].df = m_pParameter[i].df;
		}

		m_BitmapCombo.SetCurSel(0);
		m_CurrComboIndex = 0;

		m_nMARK_STEP	= m_Parameter[0].ss ;
		m_nJUMP_STEP	= m_Parameter[0].js ;
		m_nSTEP_PERIOD	= m_Parameter[0].sp ;
		m_nMARK_DELAY	= m_Parameter[0].md ;
		m_nJUMP_DELAY	= m_Parameter[0].jd ;
		m_nSTROKE_DELAY	= m_Parameter[0].sd ;
		m_fQSW_FREQ		= float(m_Parameter[0].qsf);
		m_fPULSE_WIDTH	= float(m_Parameter[0].qspw);
		m_fLAMP_POWER	= float(m_Parameter[0].lc);
		m_nLASER_ON_DELAY	= m_Parameter[0].lod ;
		m_nLASER_OFF_DELAY	= m_Parameter[0].lfd ;
		m_nFPS_DELAY		= m_Parameter[0].fps ;
		strcpy(m_ParaName, m_Parameter[0].n);

		m_FileName = filepath;
		m_pDoc->tempParaDatapath = filepath;///로드한 파라데이터를 저장한다.

		// 2003.07.08 파워 저장 인덱스 start
		m_SavedAperture = m_pDoc->DocSavedAperture;
		m_SavedPower = m_pDoc->DocSavedPower;
		m_SavedCurrent = m_pDoc->DocSavedCurrent;
		m_SavedDate = m_pDoc->DocSavedDate;
		// 2003.07.08 파워 저장 인덱스 end

		UpdateData(FALSE);
	}
}

void ParaDlg::OnFileSave() 
{
	// TODO: Add your control notification handler code here
	CString filepath;
	char filepathname[256];
	int i;

	// 2003.07.02 권한 부분 수정 start
	if (FALSE == m_pDoc->m_user.VerifyWork(SAVE_SCR))
	{
//		AfxMessageBox("Not have authority.", MB_OK);
		AfxMessageBox(IDS_AUTHORITY, MB_OK);
		return;
	}
	// 2003.07.02 권한 부분 수정 end

	CFileDialog dlgfileopen(FALSE, "scr", m_pDoc->m_scribeFilePath+"\\"+"*.scr", OFN_OVERWRITEPROMPT, "Scribe File (*.scr)",NULL);
	if (dlgfileopen.DoModal() == IDOK)
	{
		m_pDoc->m_scribeFile = dlgfileopen.GetFileName();
		// 현재의 변화를 파라미터 변수에 반영한다
		UpdateData(TRUE);
		strcpy(m_Parameter[m_CurrComboIndex].n, m_ParaName);
		m_Parameter[m_CurrComboIndex].ss  = m_nMARK_STEP;
		m_Parameter[m_CurrComboIndex].js  = m_nJUMP_STEP;
		m_Parameter[m_CurrComboIndex].sp =  m_nSTEP_PERIOD;
		m_Parameter[m_CurrComboIndex].md =  m_nMARK_DELAY;
		m_Parameter[m_CurrComboIndex].jd =  m_nJUMP_DELAY;
		m_Parameter[m_CurrComboIndex].sd =  m_nSTROKE_DELAY;
		m_Parameter[m_CurrComboIndex].qsf=  int(m_fQSW_FREQ);
		m_Parameter[m_CurrComboIndex].qspw = int(m_fPULSE_WIDTH);
		m_Parameter[m_CurrComboIndex].lc =  int(m_fLAMP_POWER);
		m_Parameter[m_CurrComboIndex].lod = m_nLASER_ON_DELAY;
		m_Parameter[m_CurrComboIndex].lfd = m_nLASER_OFF_DELAY;
		m_Parameter[m_CurrComboIndex].fps = m_nFPS_DELAY;

		for(i=0; i < MAXPARA; i++)
		{
			strcpy(m_pParameter[i].n, m_Parameter[i].n);
			m_pParameter[i].ss = m_Parameter[i].ss;
			m_pParameter[i].js = m_Parameter[i].js;
			m_pParameter[i].sp = m_Parameter[i].sp;
			m_pParameter[i].md = m_Parameter[i].md;
			m_pParameter[i].jd = m_Parameter[i].jd;
			m_pParameter[i].sd = m_Parameter[i].sd;
			m_pParameter[i].lod= m_Parameter[i].lod;
			m_pParameter[i].lfd= m_Parameter[i].lfd;
			m_pParameter[i].lcd= m_Parameter[i].lcd;
			m_pParameter[i].num= m_Parameter[i].num;
			m_pParameter[i].c = m_Parameter[i].c;
			m_pParameter[i].lc = m_Parameter[i].lc;
			m_pParameter[i].qspw = m_Parameter[i].qspw;
			m_pParameter[i].qsf = m_Parameter[i].qsf;
			m_pParameter[i].ba = m_Parameter[i].ba;
			m_pParameter[i].as = m_Parameter[i].as;
			m_pParameter[i].kpc = m_Parameter[i].kpc;
			m_pParameter[i].fps = m_Parameter[i].fps;
			m_pParameter[i].dw = m_Parameter[i].dw;
			m_pParameter[i].df = m_Parameter[i].df;
		}

		// 2003.07.08 파워 저장 인덱스 start
		m_pDoc->DocSavedAperture = m_SavedAperture;
		m_pDoc->DocSavedPower = m_SavedPower;
		m_pDoc->DocSavedCurrent = m_SavedCurrent;
		m_pDoc->DocSavedDate = m_SavedDate;
		// 2003.07.08 파워 저장 인덱스 end

		// 맴버 변수의 내용을 구조체에 쓴다
		filepath = dlgfileopen.GetPathName();

		for(i=0; i<filepath.GetLength(); i++)
			filepathname[i] = filepath.GetAt(i);

		filepathname[filepath.GetLength()] = '\0';

		m_pDoc->savefile(filepathname, SCRIBE1);
		m_FileName = filepath;

		UpdateData(FALSE);
	} else
		return;
}

BOOL ParaDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	m_BitmapCombo.SubclassDlgItem(IDC_BITMAP_COMBO, this);
	m_BitmapCombo.LimitText(9);

	m_bitmap[0].LoadBitmap(IDB_01);		m_bitmap[1].LoadBitmap(IDB_02);
	m_bitmap[2].LoadBitmap(IDB_03);		m_bitmap[3].LoadBitmap(IDB_04);
	m_bitmap[4].LoadBitmap(IDB_05);		m_bitmap[5].LoadBitmap(IDB_06);
	m_bitmap[6].LoadBitmap(IDB_07);		m_bitmap[7].LoadBitmap(IDB_08);
	m_bitmap[8].LoadBitmap(IDB_09);		m_bitmap[9].LoadBitmap(IDB_10);
	m_bitmap[10].LoadBitmap(IDB_11);	m_bitmap[11].LoadBitmap(IDB_12);
	m_bitmap[12].LoadBitmap(IDB_13);	m_bitmap[13].LoadBitmap(IDB_14);
	m_bitmap[14].LoadBitmap(IDB_15);	m_bitmap[15].LoadBitmap(IDB_16);
	m_bitmap[16].LoadBitmap(IDB_17);	m_bitmap[17].LoadBitmap(IDB_18);
	m_bitmap[18].LoadBitmap(IDB_19);	m_bitmap[19].LoadBitmap(IDB_20);

	int i;
	// 파라미터 카피 하기
	for(i=0; i < MAXPARA; i++)
	{
		strcpy(m_Parameter[i].n, m_pParameter[i].n);
		m_Parameter[i].ss = m_pParameter[i].ss;
		m_Parameter[i].js = m_pParameter[i].js;
		m_Parameter[i].sp = m_pParameter[i].sp;
		m_Parameter[i].md = m_pParameter[i].md;
		m_Parameter[i].jd = m_pParameter[i].jd;
		m_Parameter[i].sd = m_pParameter[i].sd;
		m_Parameter[i].lod= m_pParameter[i].lod;
		m_Parameter[i].lfd= m_pParameter[i].lfd;
		m_Parameter[i].lcd= m_pParameter[i].lcd;
		m_Parameter[i].num= m_pParameter[i].num;
		m_Parameter[i].c = m_pParameter[i].c;
		m_Parameter[i].lc = m_pParameter[i].lc;
		m_Parameter[i].qspw = m_pParameter[i].qspw;
		m_Parameter[i].qsf = m_pParameter[i].qsf;
		m_Parameter[i].ba = m_pParameter[i].ba;
		m_Parameter[i].as = m_pParameter[i].as;
		m_Parameter[i].kpc = m_pParameter[i].kpc;
		m_Parameter[i].fps = m_pParameter[i].fps;
		m_Parameter[i].dw = m_pParameter[i].dw;
		m_Parameter[i].df = m_pParameter[i].df;
	}

	// 콤보 박스에 대입
	for (i = 0 ; i < MAXPARA; i++)
		m_BitmapCombo.AddBitmap(&m_bitmap[i], m_Parameter[i].n);

	m_BitmapCombo.SetCurSel(0);
	m_CurrComboIndex = 0;

	m_nMARK_STEP	= m_Parameter[0].ss ;
	m_nJUMP_STEP	= m_Parameter[0].js ;
	m_nSTEP_PERIOD	= m_Parameter[0].sp ;
	m_nMARK_DELAY	= m_Parameter[0].md ;
	m_nJUMP_DELAY	= m_Parameter[0].jd ;
	m_nSTROKE_DELAY	= m_Parameter[0].sd ;
	m_fQSW_FREQ		= float(m_Parameter[0].qsf);
	m_fPULSE_WIDTH	= float(m_Parameter[0].qspw);
	m_fLAMP_POWER	= float(m_Parameter[0].lc);
	m_nLASER_ON_DELAY	= m_Parameter[0].lod ;
	m_nLASER_OFF_DELAY	= m_Parameter[0].lfd ;
	m_nFPS_DELAY		= m_Parameter[0].fps ;
	strcpy(m_ParaName, m_Parameter[0].n);
	UpdateData(FALSE);
//if(m_pDoc->tempParaDatapath)
//{
	GetDlgItem(IDC_FILE_NAME)->SetWindowText(m_pDoc->m_scribeFilePath+"\\"+m_pDoc->m_scribeFile);     
//	MessageBox(m_pDoc->m_scribeFilePath+"\\"+m_pDoc->m_scribeFile);
	//////tempParaDatapath);
//}m

//	CRect rect;
//	int Width, Height;
//	GetWindowRect(&rect);
//	Width = rect.Width();
//	Height = rect.Height();
//	SetWindowPos(NULL, 0, 0, Width, Height*0.835, SWP_NOMOVE|SWP_NOZORDER);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void ParaDlg::OnSelchangeBitmapCombo() 
{
	// TODO: Add your control notification handler code here
	int index = m_BitmapCombo.GetCurSel();

	UpdateData(TRUE);
	m_Parameter[m_CurrComboIndex].ss = m_nMARK_STEP;
	m_Parameter[m_CurrComboIndex].js = m_nJUMP_STEP;
	m_Parameter[m_CurrComboIndex].sp = m_nSTEP_PERIOD;
	m_Parameter[m_CurrComboIndex].md = m_nMARK_DELAY;
	m_Parameter[m_CurrComboIndex].jd = m_nJUMP_DELAY;
	m_Parameter[m_CurrComboIndex].sd = m_nSTROKE_DELAY;
	m_Parameter[m_CurrComboIndex].qsf= int(m_fQSW_FREQ);
	m_Parameter[m_CurrComboIndex].qspw = int(m_fPULSE_WIDTH);
	m_Parameter[m_CurrComboIndex].lc = int(m_fLAMP_POWER);
	m_Parameter[m_CurrComboIndex].lod = m_nLASER_ON_DELAY;
	m_Parameter[m_CurrComboIndex].lfd = m_nLASER_OFF_DELAY;
	m_Parameter[m_CurrComboIndex].fps = m_nFPS_DELAY;
	strcpy(m_Parameter[m_CurrComboIndex].n, m_ParaName);

	m_BitmapCombo.ReplaceText(m_CurrComboIndex, &m_bitmap[m_CurrComboIndex], m_ParaName);

	m_CurrComboIndex = index;

	CString indexStr;
	indexStr.Format("%d",m_CurrComboIndex+1);
	CWnd *indexWnd = GetDlgItem(IDC_PARA_INDEX);
	indexWnd->SetWindowText(indexStr);
	
	m_nMARK_STEP	= m_Parameter[m_CurrComboIndex].ss ;
	m_nJUMP_STEP	= m_Parameter[m_CurrComboIndex].js ;
	m_nSTEP_PERIOD	= m_Parameter[m_CurrComboIndex].sp ;
	m_nMARK_DELAY	= m_Parameter[m_CurrComboIndex].md ;
	m_nJUMP_DELAY	= m_Parameter[m_CurrComboIndex].jd ;
	m_nSTROKE_DELAY	= m_Parameter[m_CurrComboIndex].sd ;
	m_fQSW_FREQ		= float(m_Parameter[m_CurrComboIndex].qsf);
	m_fPULSE_WIDTH	= float(m_Parameter[m_CurrComboIndex].qspw);
	m_fLAMP_POWER	= float(m_Parameter[m_CurrComboIndex].lc);
	m_nLASER_ON_DELAY	= m_Parameter[m_CurrComboIndex].lod ;
	m_nLASER_OFF_DELAY	= m_Parameter[m_CurrComboIndex].lfd ;
	m_nFPS_DELAY		= m_Parameter[m_CurrComboIndex].fps ;
	strcpy(m_ParaName, m_Parameter[m_CurrComboIndex].n);
	UpdateData(FALSE);
}

void ParaDlg::OnEditchangeBitmapCombo() 
{
	// TODO: Add your control notification handler code here
	TCHAR  name[9];

	if (m_CurrComboIndex < 0)
		return;

	m_BitmapCombo.GetWindowText(name, 9);
	strcpy(m_ParaName, name);
}

void ParaDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel();
}

// 2003.06.04 Parameter Detail Setting
void ParaDlg::OnParaEdit() 
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMKDoc *pDoc = (CMKDoc*)pFrame->GetActiveDocument();
	if (pDoc->m_user.VerifyWork(OPEN_SCR) == FALSE)
	{
//		AfxMessageBox("Not have authority.");
		AfxMessageBox(IDS_AUTHORITY, MB_OK);
		return ;
	}
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_JUMP_DELAY);
	pWnd->EnableWindow(true);
    pWnd = GetDlgItem(IDC_STROKE_DELAY);
	pWnd->EnableWindow(true);
	pWnd = GetDlgItem(IDC_LASER_ON_DELAY);
	pWnd->EnableWindow(true);
	pWnd = GetDlgItem(IDC_LASER_OFF_DELAY);
	pWnd->EnableWindow(true);	
}

void ParaDlg::OnFileName() 
{
//	CStatic *pStatic;
//	pStatic = GetDlgItem(IDC_FILE_NAME);
//	pStatic->GetCursor();
//	AfxMessageBox("test");	
}

// 2003.07.08 파워 저장 인덱스
void ParaDlg::OnRecordingMode() 
{
	if (m_pDoc->m_user.m_userType < 2)
	{
//		AfxMessageBox("Not have authority.", MB_OK);
		AfxMessageBox(IDS_AUTHORITY, MB_OK);
		return;
	}
	GetDlgItem(IDC_SAVED_APERTURE)->EnableWindow(TRUE);
	GetDlgItem(IDC_SAVED_POWER)  ->EnableWindow(TRUE);
	GetDlgItem(IDC_SAVED_CURRENT)->EnableWindow(TRUE);
	GetDlgItem(IDC_SAVED_DATE)  ->EnableWindow(TRUE);
	GetDlgItem(IDC_SAVED_APERTURE)->SetFocus();	
}




