// DlgTestCut.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgTestCut.h"
#include "afxdialogex.h"
#include "FieldParameter.h"
#include "Dsp.h"
#include "PointerManager.h"
#include "PointerContainer.h"
#include "InitialTable.h"
#include <sstream>
#include <fstream>
#include <io.h>
#include <iostream>
#include <vector>
#include "Include\EXTERN\cttextctrl.h"


// CDlgTestCut 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgTestCut, CDialogEx)

CDlgTestCut::CDlgTestCut(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTestCut::IDD, pParent)
{

}

CDlgTestCut::~CDlgTestCut()
{
}

void CDlgTestCut::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOk);

}


BEGIN_MESSAGE_MAP(CDlgTestCut, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_MANNUAL_CUT, &CDlgTestCut::OnBnClickedButtonMannualCut)
	ON_BN_CLICKED(IDC_BUTTON_FLAG_CUT, &CDlgTestCut::OnBnClickedButtonFlagCut)
	ON_BN_CLICKED(IDC_LGSAMPLEGUT, &CDlgTestCut::OnBnClickedLgsamplegut)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_GUIDE1, &CDlgTestCut::OnBnClickedCheckGuide1)
	
	ON_BN_CLICKED(IDOK, &CDlgTestCut::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgTestCut 메시지 처리기입니다.


void CDlgTestCut::OnBnClickedButtonMannualCut()
{
	CDsp *pDsp = CDsp::GetInstance();
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	CDualScannerParameter *CDualScannerParameter = CDualScannerParameter::GetInstance();
	CInitialTable *pInitialTable = pInitialTable->GetInstance();

	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();


	SingleScannerParameter HEAD2Parameter = CDualScannerParameter->GetHEAD2Parameter();
	SingleScannerParameter HEAD1Parameter = CDualScannerParameter->GetHEAD1Parameter();
	double dScale = pInitialTable->GetFieldScale();

	double dMmSize, dFieldSize;
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	double m_dMaxField;
	double m_dMaxMM;
	m_dMaxField = dFieldSize;
	m_dMaxMM    = dMmSize;

	pDsp->SetFieldValue(m_dMaxField,m_dMaxMM);
	double dScaleFactorX,dScaleFactorY;

	if( pFieldParameter->GetKX() != 0)
		dScaleFactorX = (m_dMaxField / m_dMaxMM) / pFieldParameter->GetKX();
	if( pFieldParameter->GetKY() != 0)
		dScaleFactorY = (m_dMaxField / m_dMaxMM) / pFieldParameter->GetKY();

	double cs,sn,pi = 3.141592;
	cs = cos(pi * pFieldParameter->GetFieldAngle() / 180);
	sn = sin(pi * pFieldParameter->GetFieldAngle() / 180);
	//pDsp->Set_Matrix(cs,sn);
	//n_set_matrix(2,1,cs,-sn,sn,cs,1);

	double dOffsetX, dOffsetY;
	dOffsetX = pFieldParameter->GetMasterX() / m_dMaxField * m_dMaxMM;
	dOffsetY = pFieldParameter->GetMasterY() / m_dMaxField * m_dMaxMM;
	
	double dSlaveOffsetX, dSlaveOffsetY;
	dSlaveOffsetX = pFieldParameter->GetSlaveX() / m_dMaxField * m_dMaxMM;
	dSlaveOffsetY = pFieldParameter->GetSlaveY() / m_dMaxField * m_dMaxMM;


	pDsp->SetOffsetData((int)pFieldParameter->GetMasterX(), (int)pFieldParameter->GetMasterY() ,
		(int)pFieldParameter->GetSlaveX() , (int)pFieldParameter->GetSlaveY() );

	CString strTemp;
	UINT uPrevTime,uVmax;
	UINT upPrevTime,upVmax;
	double uAmax,upAmax;
	UINT Error;

	int nManualWidth = GetDlgItemInt(IDC_EDIT_MANUAL_WIDTH);
	int nManualHeight = GetDlgItemInt(IDC_EDIT_MANUAL_HEIGHT);
	

	double dManualWidthField = nManualWidth * dFieldSize / dMmSize;
	double nManualHeightField = nManualHeight * dFieldSize / dMmSize;
	SetTimer(1,100,0);

	
	// sky writing and variable Polygon Delay
	/*n_set_delay_mode( RTC_CARD_NUM_1,VariablePolygonDelay, 0, 2^30, 0, 0 );
	n_set_sky_writing_para( RTC_CARD_NUM_1,Timelag, LaserOnShift, Nprev, Npost ); 
	//n_set_sky_writing_mode( RTC_CARD_NUM_1,3 ); 
	n_set_sky_writing_mode( RTC_CARD_NUM_1,1 ); 
	n_set_sky_writing_limit( RTC_CARD_NUM_1,0.5 ); */


	int nCardNo = RTC_CARD_NUM_1;
	
	if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
	{
		//2023.08.03 테스트장비IPG LASER BEAM 새는것때문에 
		pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_PROGRESS, TRUE);

		pDsp->SetMatrixHEAD2(cs,sn);
		nCardNo = RTC_CARD_NUM_2;
		pDsp->SetGotoXYHEAD2(0,0);
		pDsp->EnableLaserHEAD2();
		pDsp->SetStartListHEAD2(1);


#ifdef _RTC_Test_		
		enable_laser();
		CParameter *pParameter = iterator->GetCurrentItem();
		double dCurrent = pParameter->GetLaserPowerSet();
		if(pDsp->GetInitialStatus())
		{
			write_8bit_port((unsigned short)(dCurrent));
			write_8bit_port_list((unsigned short)(dCurrent));


			//write_8bit_port((unsigned short)((para.GetRTCVoltage() / 100) *255));
			pDsp->OutputIOList(RTCIO_O_MO, true);
			pDsp->OutputIOList(RTCIO_O_GUIDEBEAM_ENABLE, false);
		}
#endif
		//pDsp->nSaveAndRestartTimer(nCardNo);
		pDsp->nWriteDA1List(RTC_CARD_NUM_2,HEAD2Parameter.flagPower);
		pDsp->nSetFrequency(RTC_CARD_NUM_2,HEAD2Parameter.flagFreq, HEAD2Parameter.pulsewidth );
		pDsp->nSetScannerParameter(RTC_CARD_NUM_2,HEAD2Parameter.flagSpeed,HEAD2Parameter);
	
	}
	else
	{
		//2023.08.03 테스트장비IPG LASER BEAM 새는것때문에 
		pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_PROGRESS, TRUE);

		pDsp->SetMatrixHEAD1(cs,sn);
		nCardNo = RTC_CARD_NUM_1;
		pDsp->SetGotoXYHEAD1(0,0);
		pDsp->EnableLaserHEAD1();
		pDsp->SetStartListHEAD1(1);

		//pDsp->nSaveAndRestartTimer(nCardNo);
#ifdef _RTC_Test_		
		enable_laser();
		CParameter *pParameter = iterator->GetCurrentItem();
		double dCurrent = pParameter->GetLaserPowerSet();
		if(pDsp->GetInitialStatus())
		{
			write_8bit_port((unsigned short)(dCurrent));
			write_8bit_port_list((unsigned short)(dCurrent));


			//write_8bit_port((unsigned short)((para.GetRTCVoltage() / 100) *255));
			pDsp->OutputIOList(RTCIO_O_MO, true);
			pDsp->OutputIOList(RTCIO_O_GUIDEBEAM_ENABLE, false);
		}
#endif
		pDsp->nWriteDA1List(RTC_CARD_NUM_1,HEAD1Parameter.flagPower);
		pDsp->nSetFrequency(RTC_CARD_NUM_1,HEAD1Parameter.flagFreq, HEAD1Parameter.pulsewidth );
		pDsp->nSetScannerParameter(RTC_CARD_NUM_1,HEAD1Parameter.flagSpeed,HEAD1Parameter);
	}

	double dMarkSpeed = 0.0;
	
	//if(dSpeedTemp < 0) dSpeedTemp = 1.0;

	//CDsp *pDsp = CDsp::GetInstance();
	dMarkSpeed = pDsp->GetSettedMarkSpeed();

	//n_set_mark_speed_ctrl(nCardNo,dMarkSpeed);


	//n_enable_laser(nCardNo);
	

	//n_set_start_list(nCardNo,1);
	



	double dOverflowField = m_dMaxMM / 2 *  m_dMaxField / m_dMaxMM; 

	//double dOverflowField = 20 / 2 *  m_dMaxField / m_dMaxMM; 


	//double dOverflowField = ((nManualWidth+10/*10mm 마진*/+xOffset)  / 2) *  m_dMaxField / m_dMaxMM; 
	int nLoopCnt = GetDlgItemInt(IDC_EDIT_LOOP_CNT);
	
	if(nLoopCnt <= 0) nLoopCnt = 1;
	
	if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
	{
		pDsp->ClearFlyOverflowHEAD2();
		pDsp->SetFlyLimitsHEAD2(-dOverflowField ,dOverflowField , -50000,50000);

		pDsp->SetFlyYHEAD2(1.0);pDsp->SetFlyYHEAD2(0.0);
		pDsp->SetFlyXHEAD2(1.0);pDsp->SetFlyXHEAD2(0.0);

		if(IsDlgButtonChecked(IDC_CHECK_MOTF))
			pDsp->SetFlyXHEAD2(dScaleFactorX);

		pDsp->nSaveAndRestartTimer(nCardNo);


		CString tmpX, tmpY;
		GetDlgItemText(IDC_EDIT1_x, tmpX);
		GetDlgItemText(IDC_EDIT2_y, tmpY);


		for(int i = 0; i < nLoopCnt; i++)
		{   
			/*
			pDsp->N_Jump_Abs(RTC_CARD_NUM_2,-dManualWidthField / 2 ,-nManualHeightField / 2 );
			pDsp->N_Mark_Abs(RTC_CARD_NUM_2,-dManualWidthField / 2 ,nManualHeightField / 2 );
			pDsp->N_Mark_Abs(RTC_CARD_NUM_2,dManualWidthField / 2 ,nManualHeightField / 2 );
			pDsp->N_Mark_Abs(RTC_CARD_NUM_2,dManualWidthField / 2 ,-nManualHeightField / 2 );
			pDsp->N_Jump_Abs(RTC_CARD_NUM_2,0,0);
			*/
			pDsp->N_Jump_Abs(RTC_CARD_NUM_2,-dManualWidthField / 2 , 0 );

			n_arc_rel(RTC_CARD_NUM_2, 0, (_ttoi(tmpY) * dFieldSize / dMmSize), -90);

			//pDsp->nIf_Cond(RTC_CARD_NUM_2, RTC_SIG_I_MASK0_SKIP_MODE, RTC_SIG_I_MASK1_SKIP_MODE);//SKIP MODE CHECK
			pDsp->N_Mark_Rel(RTC_CARD_NUM_2,0 ,nManualHeightField );

			//pDsp->nIf_Cond(RTC_CARD_NUM_2, RTC_SIG_I_MASK0_SKIP_MODE, RTC_SIG_I_MASK1_SKIP_MODE);//SKIP MODE CHECK
			pDsp->N_Mark_Rel(RTC_CARD_NUM_2,dManualWidthField / 2 ,0 );

			//pDsp->nIf_Cond(RTC_CARD_NUM_2, RTC_SIG_I_MASK0_SKIP_MODE, RTC_SIG_I_MASK1_SKIP_MODE);//SKIP MODE CHECK
			pDsp->N_Mark_Rel(RTC_CARD_NUM_2,0 , -nManualHeightField );

			n_arc_rel(RTC_CARD_NUM_2,  (_ttoi(tmpX) * dFieldSize / dMmSize),  0, -90);

			pDsp->N_Jump_Abs(RTC_CARD_NUM_2,0,0);
		}

		pDsp->nSaveAndRestartTimer(nCardNo);

		pDsp->SetEndOfListHEAD2();
		pDsp->nExecuteList(RTC_CARD_NUM_2, 1);

/*
		pDsp->SetStartListHEAD2(2);
		pDsp->N_Jump_Abs(RTC_CARD_NUM_2,-dManualWidthField / 2 ,-nManualHeightField / 2 );
		pDsp->N_Mark_Abs(RTC_CARD_NUM_2,-dManualWidthField / 2 ,nManualHeightField / 2 );
		pDsp->N_Mark_Abs(RTC_CARD_NUM_2,dManualWidthField / 2 ,nManualHeightField / 2 );
		pDsp->N_Mark_Abs(RTC_CARD_NUM_2,dManualWidthField / 2 ,-nManualHeightField / 2 );
		pDsp->N_Jump_Abs(RTC_CARD_NUM_2,0,0);
		pDsp->SetEndOfListHEAD2();
		pDsp->nExecuteList(RTC_CARD_NUM_2, 2);*/
	}
	else
	{
		pDsp->SetFlyLimitsHEAD1(-dOverflowField ,dOverflowField , -50000,50000);

		pDsp->SetFlyYHEAD1(1.0);pDsp->SetFlyYHEAD1(0.0);
		pDsp->SetFlyXHEAD1(1.0);pDsp->SetFlyXHEAD1(0.0);

		if(IsDlgButtonChecked(IDC_CHECK_MOTF))
			pDsp->SetFlyXHEAD1(dScaleFactorX);

		pDsp->nSaveAndRestartTimer(nCardNo);

		
		//n_set_scanahead_params_list(RTC_CARD_NUM_1, 1, 1, 1, uPrevTime, uVmax, uAmax );// place anywhere after load_correction_file
		


		for(int i = 0; i < nLoopCnt; i++)
		{
#ifdef _RTC_Test_	
			//pDsp->nIf_not_Cond(RTC_CARD_NUM_1,  0x10, 0);
			pDsp->nIf_Cond(RTC_CARD_NUM_1,  0x03, 0x00);
			pDsp->nListJumpRel(RTC_CARD_NUM_1, -1);
#endif

			pDsp->N_Jump_Abs(RTC_CARD_NUM_1,-dManualWidthField / 2 , 0 );
			//pDsp->nIf_Cond(RTC_CARD_NUM_2, RTC_SIG_I_MASK0_SKIP_MODE, RTC_SIG_I_MASK1_SKIP_MODE);//SKIP MODE CHECK
			pDsp->N_Mark_Rel(RTC_CARD_NUM_1,0 ,-nManualHeightField );

			//pDsp->nIf_Cond(RTC_CARD_NUM_2, RTC_SIG_I_MASK0_SKIP_MODE, RTC_SIG_I_MASK1_SKIP_MODE);//SKIP MODE CHECK
			pDsp->N_Mark_Rel(RTC_CARD_NUM_1,dManualWidthField / 2 ,0 );

			//pDsp->nIf_Cond(RTC_CARD_NUM_2, RTC_SIG_I_MASK0_SKIP_MODE, RTC_SIG_I_MASK1_SKIP_MODE);//SKIP MODE CHECK
			pDsp->N_Mark_Rel(RTC_CARD_NUM_1,0 , nManualHeightField );

			pDsp->N_Jump_Abs(RTC_CARD_NUM_1,0,0);
		}

		pDsp->nSaveAndRestartTimer(nCardNo);

		pDsp->SetEndOfListHEAD1();
		pDsp->nExecuteList(RTC_CARD_NUM_1, 1);

	}


	/* 사각형 자르기 */
	/*n_set_start_list(1,1);

	pDsp->nSetScannerParameter(1,HEAD2Parameter.flagSpeed,HEAD2Parameter);

	n_jump_abs(1,-dManualWidthField / 2 + xOffset,-nManualHeightField  + yOffset);
	n_mark_abs(1,-dManualWidthField / 2 + xOffset,nManualHeightField / 2 + yOffset);
	n_mark_abs(1,dManualWidthField / 2 + xOffset,nManualHeightField / 2 + yOffset);
	n_mark_abs(1,dManualWidthField / 2 + xOffset,-nManualHeightField / 2 + yOffset);
	n_mark_abs(1,-dManualWidthField  + xOffset,-nManualHeightField / 2 + yOffset);
	n_jump_abs(1,0,0);
	n_set_end_of_list(1);
	n_execute_list(1,1);*/


	// CString strTemp;
	// UINT Busy, Pos;
	// CString str;
	////   //  Wait for no list busy
	//   do
	//   {
	//       pDsp->nGetstatus(nCardNo, Busy, Pos );
	//	//str.Format("busy:%d_Pos:%d sec", Busy, Pos);
	//	//SetDlgItemText(IDC_CTTEXT_CUTTIME, str);
	//	Sleep(1);
	//   }
	//   while ( Busy );
	//
	//


	//KillTimer(1);

	/*
	m_fSpeed = ((m_nMARK_STEP * (m_pDoc->Maxmm/m_pDoc->MaxField)) / ((float)m_nSTEP_PERIOD/1000000)) / 10;
	m_strSpeed.Format("%.3f mm/sec",m_fSpeed);
	SetDlgItemText(IDC_STATIC_SPEED,m_strSpeed);
	*/

}


void CDlgTestCut::OnBnClickedButtonFlagCut()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	CDsp *pDsp = CDsp::GetInstance();

	double dMmSize, dFieldSize;
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);

	double cs,sn,pi = 3.141592;
	cs = cos(pi * pFieldParameter->GetFieldAngle() / 180);
	sn = sin(pi * pFieldParameter->GetFieldAngle() / 180);
	pDsp->Set_Matrix(cs,sn);

	int nFlagCount = GetDlgItemInt(IDC_EDIT_MANUAL_FLAG_COUNT);
	CString sTabWidth;
	GetDlgItemText(IDC_EDIT_MANUAL_TabWidth,sTabWidth);

	
	double dTabWidthField = atof(sTabWidth)* dFieldSize / dMmSize ;

	_NOTCH_PATTERN_DATA data = pFieldParameter->GetHEAD2PatternDataOfKoem();

	double dFlagLengthField = data.dTabHeight * dFieldSize / dMmSize;
	double dNotchRootField = (data.dNotchRoot - data.dHEAD2Width ) * dFieldSize / dMmSize;
	
	int xOffset = pFieldParameter->GetMasterX();
	int yOffset = pFieldParameter->GetMasterY();


	pDsp->Enable_Laser();

	set_start_list(1);


	pDsp->SetParameterNumber(PARA_INDEX_FLAG);
	pDsp->SetParameterDataList_Change();


	double dFlagAddAmount = 0;
	jump_abs(dFlagAddAmount + xOffset, -dFlagLengthField + yOffset);
	for(int i=0;i<nFlagCount;++i)
	{
		mark_abs(dFlagAddAmount + xOffset,-dNotchRootField + yOffset);
		dFlagAddAmount += dTabWidthField;
		jump_abs(dFlagAddAmount + xOffset, -dFlagLengthField + yOffset);
	}

	jump_abs(0,0);
	set_end_of_list();
	execute_list(1);



}


void CDlgTestCut::OnBnClickedLgsamplegut()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	CDsp *pDsp = CDsp::GetInstance();
	// CInformationView* a = CPointerContainer::GetInformationView();
	// a->UpdateInfo();
	double dMmSize, dFieldSize;
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);

	double cs,sn,pi = 3.141592;
	cs = cos(pi * pFieldParameter->GetFieldAngle() / 180);
	sn = sin(pi * pFieldParameter->GetFieldAngle() / 180);
	pDsp->Set_Matrix(cs,sn);


	_NOTCH_PATTERN_DATA data = pFieldParameter->GetHEAD2PatternDataOfKoem();
	_BMW_DATA_ bData = pFieldParameter->GetBMWData();

	int nUnTabWidth = GetDlgItemInt(IDC_EDIT_MANUAL_WIDTH);
	int nEncoderSuimulDivide = GetDlgItemInt(IDC_EDIT_MANUAL_TabWidth);
	int nFlagCount = GetDlgItemInt(IDC_EDIT_MANUAL_FLAG_COUNT);
	double dUnflagWidhtField = nUnTabWidth * dFieldSize / dMmSize;

	double dNotchRootField = (bData.dInsertSegmentDeepHeight - bData.dGraphiteHeight) * dFieldSize / dMmSize;
	double dFlagLengthField = bData.dFlagHeight * dFieldSize / dMmSize;
	double dFlagDeepLengthField = bData.dFlagDeepLength * dFieldSize / dMmSize;
	double dFlagWaitLangthField = bData.dFlagWaitLength * dFieldSize / dMmSize;



	double inoutLengthField = bData.dFlagInoutLength * dFieldSize / dMmSize;

	int xOffset = pFieldParameter->GetMasterX();
	int yOffset = pFieldParameter->GetMasterY();

	pDsp->Enable_Laser();


	set_start_list(1);
	pDsp->SetParameterNumber(PARA_INDEX_FLAG);
	pDsp->SetParameterDataList_Change();


	double dScaleFactorX = dFieldSize / dMmSize /  pFieldParameter->GetKX() / (double)nEncoderSuimulDivide; 
	pDsp->SetFlyX(dScaleFactorX);
	/*double dFlagAddAmount = 0;
	jump_abs(dFlagAddAmount + xOffset, -dFlagLengthField + yOffset);
	for(int i=0;i<nFlagCount;++i)
	{
		mark_abs(dFlagAddAmount + xOffset,-dNotchRootField + yOffset);
		dFlagAddAmount += dTabWidthField;
		jump_abs(dFlagAddAmount + xOffset, -dFlagLengthField + yOffset);
	}*/

	double xTotalLengthField = 0;
	jump_abs(xOffset, -dFlagLengthField + yOffset);

	xTotalLengthField += inoutLengthField;

	mark_abs(xTotalLengthField + xOffset, -dNotchRootField + yOffset); // Unflag 시작

	xTotalLengthField += dUnflagWidhtField;

	mark_abs(xTotalLengthField + xOffset, -dNotchRootField + yOffset);

	
	for(int i=0;i<nFlagCount;++i)
	{
		xTotalLengthField += inoutLengthField;

		mark_abs(xTotalLengthField + xOffset, (-dFlagLengthField) * 0.35  + yOffset); // 1/4플래그

		xTotalLengthField += dFlagWaitLangthField;

		mark_abs(xTotalLengthField + xOffset, (-dFlagLengthField) * 0.35  + yOffset);

		xTotalLengthField += inoutLengthField;

		mark_abs(xTotalLengthField + xOffset, -dNotchRootField + yOffset);

		xTotalLengthField += dFlagDeepLengthField;

		mark_abs(xTotalLengthField + xOffset, -dNotchRootField + yOffset);
	}

	for(int i=0;i<nFlagCount;++i)
	{
		xTotalLengthField += inoutLengthField;

		mark_abs(xTotalLengthField + xOffset, (-dFlagLengthField) * 0.5  + yOffset); // 1/4플래그

		xTotalLengthField += dFlagWaitLangthField;

		mark_abs(xTotalLengthField + xOffset, (-dFlagLengthField) * 0.5  + yOffset);

		xTotalLengthField += inoutLengthField;

		mark_abs(xTotalLengthField + xOffset, -dNotchRootField + yOffset);

		xTotalLengthField += dFlagDeepLengthField;

		mark_abs(xTotalLengthField + xOffset, -dNotchRootField + yOffset);
	}

	for(int i=0;i<nFlagCount;++i)
	{
		xTotalLengthField += inoutLengthField;

		mark_abs(xTotalLengthField + xOffset, (-dFlagLengthField) * 0.75  + yOffset); // 1/4플래그

		xTotalLengthField += dFlagWaitLangthField;

		mark_abs(xTotalLengthField + xOffset, (-dFlagLengthField) * 0.75  + yOffset);

		xTotalLengthField += inoutLengthField;

		mark_abs(xTotalLengthField + xOffset, -dNotchRootField + yOffset);

		xTotalLengthField += dFlagDeepLengthField;

		mark_abs(xTotalLengthField + xOffset, -dNotchRootField + yOffset);
	}


	mark_abs(xTotalLengthField + xOffset,(-dFlagLengthField) + yOffset);


	jump_abs(0,0);
	set_end_of_list();
	execute_list(1);

}



BOOL CDlgTestCut::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_btnOk.SetIcon(IDI_ICON256_OK);
	m_btnCancel.SetIcon(IDI_ICON256_CANCEL);

	//SetActiveWindow();



	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgTestCut::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nIDEvent == 1)
	{
		CDsp *pDsp = CDsp::GetInstance();
		TListExeStat stStat; stStat.clear();
		UINT uErrorbit = -1;
		BOOL bErrorCheck = FALSE;
		UINT Busy, Pos;
		CString strTemp;
		int nCardNo = RTC_CARD_NUM_2;

		if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
			nCardNo = RTC_CARD_NUM_2;	
		else
			nCardNo = RTC_CARD_NUM_1;	

		 pDsp->nGetstatus(nCardNo, Busy, Pos );

		stStat = pDsp->ReadStatusHEAD2();
		uErrorbit = n_get_marking_info(RTC_CARD_NUM_2);

		CCttextctrl* ctBusy = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_STATUS));
	
		if(Busy)
		{
			SetDlgItemText(IDC_CTTEXT_STATUS, "Busy");
			ctBusy->SetBackColor(255);
			strTemp.Format("%.3f", pDsp->nGetTime(nCardNo));
			SetDlgItemText(IDC_CTTEXT_CUTTIME, strTemp);
		}
		else
		{
			SetDlgItemText(IDC_CTTEXT_STATUS, "Ready");
			ctBusy->SetBackColor(0);
			strTemp.Format("%.3f", pDsp->nGetTime(nCardNo));
			SetDlgItemText(IDC_CTTEXT_CUTTIME, strTemp);
			KillTimer(1);


			//2023.08.03 테스트장비IPG LASER BEAM 새는것때문에 
			pDsp->nOutputIO(nCardNo, RTC_SIG_O_PROGRESS, FALSE);
		}

		/*
		Bit #0(LSB)= 1: Processing-on-the-fly underflow in X direction (X < –524288).
		Bit #1 = 1: Processing-on-the-fly overflow in X direction (X > +524287).
		Bit #2 = 1: Processing-on-the-fly underflow in Y direction (Y < –524288).
		Bit #3 = 1: Processing-on-the-fly overflow in Y direction (Y > +524287).
		Bit #4 = 1: Processing-on-the-fly underflow in X direction (X < Xmin).
		Bit #5 = 1: Processing-on-the-fly overflow in X direction (X > Xmax).
		Bit #6 = 1: Processing-on-the-fly underflow in Y direction (Y < Ymin).
		Bit #7 = 1: Processing-on-the-fly overflow in Y direction (Y > Ymin).
		*/
		UINT nGetMarkingInfo = get_marking_info();
		
		/*UINT nXUnderFlowCheckBit  = 0x0003;
		UINT nXOverFlowCheckBit  = 0x0030;
		UINT nYUnderFlowCheckBit  = 0x000C;
		UINT nYOverFlowCheckBit  = 0x00C0;*/
		UINT nXUnderFlowCheckBit  = 0x10;
		UINT nXOverFlowCheckBit  = 0x20;
		UINT nYUnderFlowCheckBit  = 0x40;
		UINT nYOverFlowCheckBit  = 0x80;


		if(getAbit(nGetMarkingInfo, 4) != 0)
		//if((nGetMarkingInfo & nXUnderFlowCheckBit) != 0)
		{
			if(bErrorCheck == FALSE)
			{
				KillTimer(1);
				pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);
				//pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_SCANNER_OVERFLOW);			
				bErrorCheck = TRUE;
				if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
					pDsp->StopExcutionHEAD2();
				else
					pDsp->StopExcutionHEAD1();

				TRACE("XUnderFlow");
				AfxMessageBox("XUnderflow");
			}
		}
		if(getAbit(nGetMarkingInfo, 5) != 0 )
		//if((nGetMarkingInfo & nXOverFlowCheckBit) != 0)
		{
			KillTimer(1);
			if(bErrorCheck == FALSE)
			{

				pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);
				pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_READY, FALSE);
				//pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_SCANNER_OVERFLOW);			
				bErrorCheck = TRUE;
				if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
					pDsp->StopExcutionHEAD2();
				else
					pDsp->StopExcutionHEAD1();
				
				AfxMessageBox("XOverflow");
				TRACE("XOverFlow");
			}
		}
		
		//if((nGetMarkingInfo & nYUnderFlowCheckBit) != 0)
		if(getAbit(nGetMarkingInfo, 6) != 0 )
		{
			if(bErrorCheck == FALSE)
			{
				KillTimer(1);
				pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);
				pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_READY, FALSE);
				//pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_SCANNER_OVERFLOW);			
				bErrorCheck = TRUE;
				if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
					pDsp->StopExcutionHEAD2();
				else
					pDsp->StopExcutionHEAD1();
				TRACE("YUnderFlow");
				AfxMessageBox("YUnderFlow");
			}
		}
		
		//if((nGetMarkingInfo & nYOverFlowCheckBit) != 0)
		if(getAbit(nGetMarkingInfo, 7) != 0 )
		{
			if(bErrorCheck == FALSE)
			{
				KillTimer(1);
				pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);
				pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_READY, FALSE);
				//pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_SCANNER_OVERFLOW);			
				bErrorCheck = TRUE;
				if(IsDlgButtonChecked(IDC_RADIO_HEAD2))
					pDsp->StopExcutionHEAD2();
				else
					pDsp->StopExcutionHEAD1();
				TRACE("YOverFlow");
				AfxMessageBox("YOverflow");
			}
		}

	}

	CDialogEx::OnTimer(nIDEvent);
}


int CDlgTestCut::getAbit(unsigned short x, int n) { // getbit()
 int nRet = -1;
 nRet = (x & (1 << n)) >> n;
return  nRet;
}

void CDlgTestCut::OnBnClickedCheckGuide1()
{
	CDsp *pDsp = CDsp::GetInstance();
	#ifdef	_RTC_Test_
	if (IsDlgButtonChecked(IDC_CHECK_GUIDE1))
		pDsp->OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
	else
		pDsp->OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, FALSE);
	return;
#endif

}





void CDlgTestCut::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnClose();
	CDialogEx::OnOK();
}
