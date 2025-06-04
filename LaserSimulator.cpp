// LaserSimulator.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "LaserSimulator.h"
#include "afxdialogex.h"
#include "PointerManager.h"
#include "Dsp.h"

#include "afxdialogex.h"
#include "define.h"

#include "FieldParameter.h"
#include "PointerManager.h"
#include <algorithm>
#include "MainFrm.h"
#include "InitialTable.h"


#define PI	3.1415926535


// CLaserSimulator 대화 상자입니다.

IMPLEMENT_DYNAMIC(CLaserSimulator, CDialogEx)

	CLaserSimulator::CLaserSimulator(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLaserSimulator::IDD, pParent)
	, m_nFLagRollSpeed(100)
	, m_nUnflagRollSpeed(100)
	, m_nFlagToUnflagAcc(15000)
	, m_nUnflagToFlagDec(15000)
{
	m_dCenterX = 200;
	m_dCenterY = 200;


	m_nBoundaryWidth = 100;
	m_nBoundaryHeight = 300;
	m_nNotchAreaHeight = 260;

	m_vLaserPos.x = m_dCenterX;
	m_vLaserPos.y = m_dCenterY;

	m_dLaserSpeed = 10;

	m_dZoomScale = 1.2;
	m_dLaserSize = 10;

	m_dPoleWidth = 10;
	m_dPoleHeight = 300;

	m_dEncoder = 0;
	m_dTotalEncoder = 0;

	m_speedDiv = 50;
	count = 0;

	isSimulate = false;

	CDsp* pDsp = pDsp->GetInstance();
	int rtcCount = pDsp->GetBoardCount();

	if(rtcCount <= 0)
	{
		bRTCIsReady = false;
	}
	else
	{
		bRTCIsReady = true;
	}

	


}

CLaserSimulator::~CLaserSimulator()
{
}

void CLaserSimulator::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FLAG_ROLL_SPEED, m_nFLagRollSpeed);
	DDX_Text(pDX, IDC_EDIT_UNFLAG_ROLL_SPEED, m_nUnflagRollSpeed);
	DDX_Text(pDX, IDC_EDIT_FLAGTOUNFLAG_ACC, m_nFlagToUnflagAcc);
	DDX_Text(pDX, IDC_EDIT_UNFLAGTOFLAG_DEC, m_nUnflagToFlagDec);
	DDX_Text(pDX, IDC_SIMUL_SPEED, m_speedDiv);
	DDX_Control(pDX, IDC_LASERPATTERN_VIEWER, m_LaserViewer);
}


BEGIN_MESSAGE_MAP(CLaserSimulator, CDialogEx)

	ON_WM_TIMER()
	//	ON_WM_PAINT()
	//	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDOK, &CLaserSimulator::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLaserSimulator::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLaserSimulator 메시지 처리기입니다.






BOOL CLaserSimulator::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	UpdateData(FALSE);
	SetTimer(FIRST_SHOW_GRAPH,1,NULL);
	SetTimer(FIRST_SHOW_GRAPH,300,NULL);
	return true;
}

void CLaserSimulator::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	switch (nIDEvent)
	{
	case TIMER_DRAW_SIMUL:
		DrawLaserArea(&m_LaserViewer);
		break;
	case FIRST_SHOW_GRAPH:
		KillTimer(FIRST_SHOW_GRAPH);
		FirstShowGrapbh(&m_LaserViewer);
		
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}








BEGIN_EVENTSINK_MAP(CLaserSimulator, CDialogEx)

	ON_EVENT(CLaserSimulator, IDC_CTPUSH_SIMULSTART, DISPID_CLICK, CLaserSimulator::ClickCtpushSimulstart, VTS_NONE)
	ON_EVENT(CLaserSimulator, IDC_CTPUSH_SIMULSTOP, DISPID_CLICK, CLaserSimulator::ClickCtpushSimulstop, VTS_NONE)
	ON_EVENT(CLaserSimulator, IDC_CTPUSH_SIMULPAUSE, DISPID_CLICK, CLaserSimulator::ClickCtpushSimulGuideOnly, VTS_NONE)
END_EVENTSINK_MAP()




void CLaserSimulator::ClickCtpushSimulstart()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CDsp* pDsp = pDsp->GetInstance();
	TListExeStat stStat; stStat.clear();

	

	stStat = pDsp->ReadStatus();

	/*if(stStat.bBusy1 != FALSE || stStat.bBusy2 != FALSE)
	{
		return;
	}*/


	UpdateData(TRUE);
	CFieldParameter* pFieldParameter = CFieldParameter::GetInstance();
	double dMaxMM,dMaxFieldSize;
	pFieldParameter->GetSize(&dMaxMM,&dMaxFieldSize);
	_BMW_DATA_ bmwData = pFieldParameter->GetBMWData();


	SingleScannerParameter HEAD2ScannerParameter = CDualScannerParameter::GetInstance()->GetHEAD2Parameter();


	bmwData.SetFieldSizeAndMmSize(dMaxFieldSize,dMaxMM);
	bmwLaserSimulPoints.clear();
	bmwLaserSimulPoints.emplace_back(0, - bmwData.FieldValue(bmwData.dFlagHeight * 2));



	//첫번째 플래그 (In)

	double inoutLength =  sqrt(bmwData.dFlagInoutLength * bmwData.dFlagInoutLength + bmwData.dFlagHeight * bmwData.dFlagHeight);
	double inoutTime = inoutLength / HEAD2ScannerParameter.flagSpeed;
	double inoutOntheflyAmount =  sqrt(bmwData.dFlagInoutLength * bmwData.dFlagInoutLength + bmwData.dFlagHeight * bmwData.dFlagHeight) / ( HEAD2ScannerParameter.flagSpeed ) * m_nFLagRollSpeed;
	double inoutMM = bmwData.dFlagInoutLength - inoutOntheflyAmount;

	double deepOntheflyAmount = bmwData.dFlagDeepLength  / HEAD2ScannerParameter.flagSpeed * m_nFLagRollSpeed;
	double deepMM = bmwData.dFlagDeepLength - deepOntheflyAmount;

	double flagJumpOntheflyAmount = bmwData.dFlagWaitLength /  HEAD2ScannerParameter.jumpSpeed * m_nFLagRollSpeed;
	double flagJumpOntheflyMM = bmwData.dFlagWaitLength - flagJumpOntheflyAmount;

	double feawbui = 10;

	auto listIter = bmwLaserSimulPoints.begin();
	
	for(int i=0;i<bmwData.dTabCount;++i)
	{
		
		bmwLaserSimulPoints.emplace_back(listIter -> x + bmwData.FieldValue(inoutMM),0); // FlagIn
		listIter++;

		
		bmwLaserSimulPoints.emplace_back(listIter -> x + bmwData.FieldValue(deepMM),0);// flagDeep
		listIter++;
		
		bmwLaserSimulPoints.emplace_back(listIter -> x + bmwData.FieldValue(inoutMM),- bmwData.FieldValue(bmwData.dFlagHeight) );// flagDeep
		listIter++;

		
		bmwLaserSimulPoints.emplace_back(listIter -> x + bmwData.FieldValue(flagJumpOntheflyMM),- bmwData.FieldValue(bmwData.dFlagHeight) );// flagDeep
		listIter++;
	}


	//////////////////Nonflag////////////////

	double unflagInoutOntheflyAmount =  bmwData.FieldValue(sqrt(bmwData.dFlagInoutLength * bmwData.dFlagInoutLength + bmwData.dFlagHeight * bmwData.dFlagHeight)) / HEAD2ScannerParameter.nonflagLineSpeed * m_nUnflagRollSpeed;
	double unflagInoutOntheflyMM = bmwData.dFlagInoutLength - bmwData.FieldValueToMM(unflagInoutOntheflyAmount);

	double unflagEndSegOntheflyAmount = bmwData.FieldValue(bmwData.dEndSegmentLength)  / HEAD2ScannerParameter.nonflagLineSpeed * m_nUnflagRollSpeed;
	double unflagEndSegOntheflyMM = bmwData.dEndSegmentLength - bmwData.FieldValueToMM(unflagEndSegOntheflyAmount);

	double unflagInsertSegOntheflyAmount =  bmwData.FieldValue(bmwData.dInsertSegmentLength)  / HEAD2ScannerParameter.nonflagLineSpeed * m_nUnflagRollSpeed;
	double unflagInsertSegOntheflyMM = bmwData.dInsertSegmentLength - bmwData.FieldValueToMM(unflagInsertSegOntheflyAmount);


	bmwLaserSimulPoints.emplace_back(listIter -> x + bmwData.FieldValue(unflagInoutOntheflyMM),0); // UnFlagIn
	listIter++;

	bmwLaserSimulPoints.emplace_back(listIter -> x + bmwData.FieldValue(unflagEndSegOntheflyMM),0); // EndSeg
	listIter++;


	bmwLaserSimulPoints.emplace_back(listIter -> x + bmwData.FieldValue(unflagInsertSegOntheflyMM),0); // InsertSeg
	listIter++;


	bmwLaserSimulPoints.emplace_back(listIter -> x + bmwData.FieldValue(unflagInoutOntheflyMM),- bmwData.FieldValue(bmwData.dFlagHeight)); // UnflagOut
	listIter++;

	int listCount = 0;

	patternDataY.clear();
	patternDataX.clear();

	for(const Vector2& v : bmwLaserSimulPoints)
	{
		patternDataY.push_back(bmwData.FieldValueToMM(v.x));
		patternDataX.push_back(bmwData.FieldValueToMM(-v.y));
	}

	DrawLaserArea(&m_LaserViewer);

	///////Overflow & Underflow Check/////////
	for(auto iter = bmwLaserSimulPoints.begin(); iter!= bmwLaserSimulPoints.end();++iter)
	{
		if(bmwData.FieldValueToMM(iter->x) > 30 )
		{
			double flowValue = bmwData.FieldValueToMM(iter->x);

			AfxMessageBox(_T("Laser Over Flow expected!! \n Decrease Laser Speed Or Increase Roll Speed")); 
			return;
		}

		if(bmwData.FieldValueToMM(iter->x) < -30 )
		{

			double flowValue = bmwData.FieldValueToMM(iter->x);
			AfxMessageBox(_T("Laser Under Flow expected!! \n Increase Laser Speed Or Decrease Roll Speed")); 
			return;
		}
		listCount++;
	}


	AfxMessageBox(_T("Simulation Complete\nOver Flow and Under Flow Isn't Expected")); 


	//if(!isSimulate)
	//{
	//	UpdateData(TRUE);
	//	int tempSimulSpeed = GetDlgItemInt(IDC_SIMUL_SPEED);
	//	if(tempSimulSpeed != 0)
	//	{
	//		m_speedDiv = tempSimulSpeed;
	//	}
	//	
	//	
	//	if(MakeSimulateDate())
	//	{
	//		count = 0;
	//		m_vLaserPos.SetPos(8,130);
	//		t_LastTime = clock();
	//		m_vDir.SetPos(-1,0);
	//		MakeRealPatternData();
	//		m_dTotalEncoder = 0;
	//		m_dCurrRollSpeed = m_nFLagRollSpeed;
	//		
	//		

	//		SetTimer(TIMER_DRAW_SIMUL,1,NULL);
	//		isSimulate = true;


	///*		m_nFLagRollSpeed / m_speedDiv;
	//		m_nUnflagRollSpeed/ m_speedDiv;
	//		m_nFlagToUnflagAcc/ m_speedDiv;
	//		m_nUnflagToFlagDec/ m_speedDiv;*/
	//	}	
	//	else
	//	{
	//		MessageBox("dsadsadas","dsadsad");
	//	}

	//	
	//	
	//	
	//}
}

void CLaserSimulator::ClickCtpushSimulstop()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	StopLaserSimulation();
	if(isSimulate)
	{
		KillTimer(TIMER_DRAW_SIMUL);
		isSimulate = false;
		count = 0;
		
	}

}


void CLaserSimulator::ClickCtpushSimulGuideOnly()
{
	CDsp* pDsp = pDsp->GetInstance();
	TListExeStat stStat; stStat.clear();

	stStat = pDsp->ReadStatus();

	if(stStat.bBusy1 != FALSE || stStat.bBusy2 != FALSE)
	{
		return;
	}


	if(bRTCIsReady)
	{
		stop_execution();
	}
	else
	{
		return;
	}




	if(!isSimulate)
	{
		UpdateData(TRUE);
		if(MakeSimulateDate())
		{
			CFieldParameter* pFieldParameter = pFieldParameter->GetInstance();
			double dMmSize, dFieldSize;
			CInitialTable* pInitialTable = pInitialTable->GetInstance();
			pFieldParameter->GetSize(&dMmSize, &dFieldSize);
			CPointerManager *pPointerManager = pPointerManager->GetInstance();
			Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
			CParameter *pParameter = iterator->GetCurrentItem();
			CDsp* pDsp = CDsp::GetInstance();

			SingleScannerParameter HEAD2ScannerParameter = CDualScannerParameter::GetInstance()->GetHEAD2Parameter();

			HEAD2ScannerParameter.jumpSpeed /= 10;
			
			set_start_list(1);

			//pDsp->SetRTCJumpSpeed(1,HEAD2ScannerParameter.flagSpeed );
			for(Vector2 d : bmwLaserSimulPoints)
			{
				
				/*double jumpstep = ((double)d.speed * (10 / 1000000.)) * 10 / ((double)pInitialTable->GetMMSize() / (double)pInitialTable->GetFieldSize());
				double stepPeriod = pParameter->GetStepPeriod();

				double simulJumpSpeed = jumpstep * 100 / stepPeriod;
				set_jump_speed(simulJumpSpeed);*/

				



				jump_abs(d.x ,d.y );

			}


			set_end_of_list();
			execute_list(1);
		}
	}

}



void CLaserSimulator::DrawLaserArea(CChartViewer* viewer)
{
	CFieldParameter* pFieldParameter = pFieldParameter->GetInstance();
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
	CParameter *pParameter = iterator->GetCurrentItem();
	_NOTCH_PATTERN_DATA data = pFieldParameter->GetHEAD2PatternDataOfKoem();


	CRect rect;
	GetClientRect(&rect);


	//그래프 배경색 글자색
	XYChart *c = new XYChart(rect.left + 400,rect.bottom - 30 , 0x0000CD, 0x000000, 1);
	c->setBackground(c->linearGradientColor(0, 0, 0, c->getHeight() / 2, 0x313e50,0x313e50), Chart::Transparent);
	c->setRoundedFrame();
	//c->setDropShadow();
	c->setPlotArea(30, 30, rect.left + 400 - 30 ,rect.bottom -90, c->linearGradientColor(0, 55, 0, 335, 0x313e50,
		0x313e50), -1,  0x313e50, 0x313e50);
	c->setClipping();
	c->addTitle("KOEM LASER NOTCH SIMULATOR", "timesbi.ttf", 15
		)->setBackground(0xdddddd, 0x000000, Chart::glassEffect());
	/*c->xAxis()->setTitle("Length (mm)", "arialbd.ttf",10);
	c->yAxis()->setTitle("Height (cm)", "arialbd.ttf",10);*/
	c->xAxis()->setWidth(2);
	c->yAxis()->setWidth(2);
	c->xAxis()->setColors(0xc5c5c5,0xc5c5c5,0xc5c5c5,0xc5c5c5);
	c->yAxis()->setColors(0xc5c5c5,0xc5c5c5,0xc5c5c5,0xc5c5c5);
	//그래프 배경색 글자색






	//시간 계산
	clock_t currtime = clock();
	double deltaTime = (currtime - t_LastTime) / 1000.0;
	//시간 계산






	//CalculateLaserPointerPos(deltaTime);






	////레이저 가이드 그리기
	//double dataX[1] = {m_vLaserPos.x};
	//double dataY[1] = {m_vLaserPos.y};
	//int laserColor[2] = {0xff0000,0x00ff00};
	//ScatterLayer *scatterlayer = c->addScatterLayer(DoubleArray(dataX,
	//	sizeof(dataX)/sizeof(dataX[0])), DoubleArray(dataY,
	//	sizeof(dataY)/sizeof(dataY[0])), "", Chart::GlassSphere2Shape, 11, laserColor[iter->laserState],
	//	0xff3333);
	//double tempX[1] = {15};
	//double tempY[1] = {130};
	//ScatterLayer *scatterlayer1 = c->addScatterLayer(DoubleArray(tempX,
	//	sizeof(tempX)/sizeof(tempX[0])), DoubleArray(dataY,
	//	sizeof(tempY)/sizeof(tempY[0])), "", Chart::GlassSphere2Shape, 0, 0xff0000,
	//	0xff3333);
	////레이저 가이드 그리기

	//레이저 경로 그리기
	LineLayer *layer1 = c->addLineLayer();
	/*double deltaRollAmount = m_dCurrRollSpeed * deltaTime / m_speedDiv;
	std::for_each(patternDataY.begin(),patternDataY.end(),[&deltaRollAmount](double& d) { d -= deltaRollAmount  ;});
	auto ystart = std::find_if(patternDataY.begin(),patternDataY.end(),[](const double& d) { return d > -150.0;});
	auto yend = std::find_if_not(patternDataY.begin(),patternDataY.end(),[](const double& d) { return d < 150.0;});
	auto ydistance = std::distance(ystart,yend);*/

	/*if (ystart == patternDataY.end())
	{
		KillTimer(TIMER_DRAW_SIMUL);
		isSimulate = false;
		return;
	}

	int startIndex = std::distance(patternDataY.begin(),ystart);*/
	//layer1->addDataSet(DoubleArray(&(*ystart), /*sizeof(dataX2)/sizeof(dataX2[0]))*/ ydistance), 0xFF0000, "HEAD2 Pattern");
	layer1->addDataSet(DoubleArray(&patternDataY[0],patternDataY.size() ), 0xFF0000, "HEAD2 Pattern");
	layer1->setXData(DoubleArray(&patternDataX[0], patternDataY.size()));//XData한번만 지정하면됨
	layer1->setLineWidth(1);

	//레이저 경로 그리기





	//흑연그리기
	LineLayer *graphiteLayer = c->addLineLayer();
	double graphiteUpperYData[] = {30,30};
	double graphiteLowerYData[] ={-30,-30};
	double graphiteXData[] = {-20,0};

	graphiteLayer->addDataSet(DoubleArray(graphiteUpperYData, 2), 0x5a5a5a);
	graphiteLayer->addDataSet(DoubleArray(graphiteLowerYData, 2), 0x5a5a5a);
	graphiteLayer->setXData(DoubleArray(graphiteXData, 2));
	c->addInterLineLayer(graphiteLayer->getLine(0), graphiteLayer->getLine(1),  0x5a5a5a, -1);
	//흑연그리기







	//극 그리기
	LineLayer* electrodeLayer = c->addLineLayer();
	//double electrodeUpperYData[2] = {150,150};
	double electrodeLowerYData[2] = {-30,-30};
	double electrodeXData[] = {0,5};

	std::vector<double> electrodeUpperYData; // 벡터도잘되네
	electrodeUpperYData.push_back(30);
	electrodeUpperYData.push_back(30);

	electrodeLayer->addDataSet(DoubleArray(electrodeUpperYData.data(), 2), 0xb87333); //나중에 음극 양극에 따라서 색이 바뀌어야겠지?
	electrodeLayer->addDataSet(DoubleArray(electrodeLowerYData, 2), 0xb87333);
	electrodeLayer->setXData(DoubleArray(electrodeXData, 2));	
	c->addInterLineLayer(electrodeLayer->getLine(0), electrodeLayer->getLine(1),  0xb87333, -1);
	//극 그리기





	//그래프 그리기
	viewer->setChart(c);
	viewer->ShowWindow(TRUE);
	//그래프 그리기



	//할당받은 객체들 해제
	delete c;
	t_LastTime = currtime;
	

}




void CLaserSimulator::CalculateLaserPointerPos(double deltaTime)
{
	if(iter->state == NotchingState::Flag)
	{
		m_dCurrRollSpeed = m_dCurrRollSpeed + ( -m_nUnflagToFlagDec / m_speedDiv * deltaTime);
		if(m_dCurrRollSpeed < m_nFLagRollSpeed)
		{
			m_dCurrRollSpeed = m_nFLagRollSpeed;
		}
	}
	else if(iter->state == NotchingState::Unflag)
	{
		m_dCurrRollSpeed = m_dCurrRollSpeed + ( m_nFlagToUnflagAcc / m_speedDiv * deltaTime);
		if(m_dCurrRollSpeed > m_nUnflagRollSpeed)
		{
			m_dCurrRollSpeed = m_nUnflagRollSpeed;
		}
	}


	m_dTotalEncoder += m_dCurrRollSpeed * deltaTime / m_speedDiv;


	Vector2 temppos = iter->pos;
	double speed = abs(iter->speed);
	double dEncoderAmount = iter->encoderAmount;
	bool fixstate = iter->isWait;


	Vector2 normalDir = m_vDir.Normalize() ;
	normalDir = normalDir * deltaTime * (speed / m_speedDiv);
	m_vLaserPos.Move(normalDir);

	
	



	Vector2 destDir = temppos - m_vLaserPos;
	if(m_vDir.Dot(destDir) <= 0) // 목적지에 도착했다면
	{
		if(fixstate && dEncoderAmount > m_dTotalEncoder)
		{
			m_vLaserPos = temppos;
		}
		else
		{
			++iter;
			if(iter == dataList.end())
			{
				iter--;
				KillTimer(TIMER_DRAW_SIMUL);
				isSimulate = false;
				return;
			}
			m_vLaserPos = temppos;
			m_vDir = iter->pos - m_vLaserPos;
		}
	}
	double guideBeamPosX = m_vLaserPos.x;
	double guideBeamPosY = m_vLaserPos.y;
	CFieldParameter* pFieldParameter = pFieldParameter->GetInstance();

	double dMmSize, dFieldSize;

	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	if(bRTCIsReady)
	{	
#ifndef _RTC_Test_
			goto_xy(guideBeamPosX * dFieldSize / dMmSize,guideBeamPosY  * dFieldSize / dMmSize);
#else
			goto_xy(guideBeamPosY  * dFieldSize / dMmSize,guideBeamPosX * dFieldSize / dMmSize);
#endif
	}

}


bool CLaserSimulator::MakeSimulateDate()
{
	dataList.clear();

	CFieldParameter* pFieldParameter = pFieldParameter->GetInstance();
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
	CParameter *pParameter = iterator->GetCurrentItem();
	_NOTCH_PATTERN_DATA data = pFieldParameter->GetHEAD2PatternDataOfKoem();
	CDsp* pDsp= pDsp->GetInstance();

	double dFlagLaserSpeed = pParameter->GetFlagSpeed();
	double dFlagLaserJumpSpeed = pParameter->GetFlagJumpSpeed();
	double dFlagTotalLength = (data.dTabHeight + (data.dHEAD2Width - data.dNotchRoot));
	double dFlagTime = QuadraticFormulaForSimul(
		dFlagLaserSpeed *dFlagLaserSpeed - m_nFLagRollSpeed * m_nFLagRollSpeed,
		2 * 0 * m_nFLagRollSpeed,
		-(data.dTabHeight * data.dTabHeight + 0*0));

	double dUnderflyAmount = dFlagTime * m_nFLagRollSpeed;






	double totalY =0;

	//1차 플래그
	for(int i=0;i<data.dTabCount;++i)
	{
		PatternData flagStartPos(Vector2(data.dTabHeight,130),dFlagLaserJumpSpeed,true,totalY,NotchingState::Flag,LaserState::On);
		totalY += data.dTabWidth;
		PatternData flagEndPos(Vector2(data.dNotchRoot - data.dHEAD2Width,130 - dUnderflyAmount ),dFlagLaserSpeed ,false,totalY,NotchingState::Flag,LaserState::Off);
		dataList.push_back(flagStartPos);
		dataList.push_back(flagEndPos);
		

	}

	double dUnflagInoutSpeed = pParameter->GetUnflagInoutSpeed();
	double dUnflagInoutLength = (data.dTabHeight + (data.dHEAD2Width - data.dBuriedHeight));
	double dUnflagInoutTime = QuadraticFormulaForSimul(
		m_nUnflagRollSpeed * m_nUnflagRollSpeed - dUnflagInoutSpeed *dUnflagInoutSpeed,
		2 * 0 * m_nUnflagRollSpeed,
		dUnflagInoutLength * dUnflagInoutLength + 0*0);


	double dUnflagInoutUndefly = m_nUnflagRollSpeed * dUnflagInoutTime;

	double dUnflagLineLength = data.dBuriedRegion;
	double dUnflagLineSpeed = pParameter->GetUnflagLineSpeed();
	double dUnflagLineTime = dUnflagLineLength / (dUnflagLineSpeed);
	double dUnflagLineUnderfly = (dUnflagLineSpeed - m_nUnflagRollSpeed) * dUnflagLineTime;

	totalY += 260;
	PatternData UnflagPatternPos(Vector2(data.dTabHeight,-130),dFlagLaserJumpSpeed ,true,totalY,NotchingState::Unflag,LaserState::On);
	dataList.push_back(UnflagPatternPos);
	UnflagPatternPos.setData(Vector2(data.dBuriedHeight - data.dHEAD2Width,-130 - dUnflagInoutUndefly),dUnflagInoutSpeed ,false,totalY,NotchingState::Unflag,LaserState::Off);
	dataList.push_back(UnflagPatternPos);
	UnflagPatternPos.setData(Vector2(data.dBuriedHeight - data.dHEAD2Width,-130 - dUnflagInoutUndefly + dUnflagLineUnderfly),(dUnflagLineSpeed - m_nUnflagRollSpeed),false,totalY,NotchingState::Unflag,LaserState::Off);
	dataList.push_back(UnflagPatternPos);
	UnflagPatternPos.setData(Vector2(data.dTabHeight,-130 - dUnflagInoutUndefly + dUnflagLineUnderfly - dUnflagInoutUndefly),dUnflagInoutSpeed,true,totalY,NotchingState::Unflag,LaserState::Off);
	dataList.push_back(UnflagPatternPos);


	double unflagToFlagCurrSpeed = m_nUnflagRollSpeed;

	totalY += data.dBuriedRegion;
	totalY -= 260;


	for(int i=0;i<data.dTabCount;++i)
	{
		totalY += data.dTabWidth;
		Vector2 lastPos = dataList.rbegin()->pos;
		Vector2 jumpDestPos = lastPos;
		jumpDestPos.x = data.dTabHeight;

		//점프 위치 계산
		double jumpXLength = abs(lastPos.x - jumpDestPos.x);
		double jumpTime =  CalculateLaserTime(dFlagLaserJumpSpeed,unflagToFlagCurrSpeed,jumpXLength,data.dTabWidth);
		double jumpUnderflyAmount = unflagToFlagCurrSpeed * jumpTime;	
		jumpDestPos.y = lastPos.y - jumpUnderflyAmount + data.dTabWidth;

		unflagToFlagCurrSpeed -= m_nUnflagToFlagDec * jumpTime;
		
		if(jumpDestPos.y > 130.0)
		{
			jumpDestPos.y = 130.0;
		}

		if(unflagToFlagCurrSpeed < m_nFLagRollSpeed)
		{
			unflagToFlagCurrSpeed = m_nFLagRollSpeed;
		}


		PatternData flagStartPos(jumpDestPos,dFlagLaserJumpSpeed,true,totalY,NotchingState::Flag,LaserState::On);
		dataList.push_back(flagStartPos);

		//마킹끝나는위치계산
		double makringTime = CalculateLaserTime(dFlagLaserSpeed,unflagToFlagCurrSpeed,dFlagTotalLength,0);
		double markUnderflyAmount = unflagToFlagCurrSpeed * makringTime;
		Vector2 markDestPos = jumpDestPos;
		markDestPos.SetPos(data.dNotchRoot - data.dHEAD2Width,jumpDestPos.y - (markUnderflyAmount));
		unflagToFlagCurrSpeed -= m_nUnflagToFlagDec * makringTime;

		if(unflagToFlagCurrSpeed < m_nFLagRollSpeed)
		{
			unflagToFlagCurrSpeed = m_nFLagRollSpeed;
		}


		PatternData flagEndPos(markDestPos,dFlagLaserSpeed,false,totalY,NotchingState::Flag,LaserState::Off);
		dataList.push_back(flagEndPos);
	}




	double accTime = (-m_nFLagRollSpeed + sqrt(m_nFLagRollSpeed * m_nFLagRollSpeed + 2 * 260 * m_nFlagToUnflagAcc)) / m_nFlagToUnflagAcc;
	double destTime = (m_nUnflagRollSpeed - m_nFLagRollSpeed ) / (double)m_nFlagToUnflagAcc;

	if(accTime < destTime)
	{
		return false;
	}

	double dMmSize, dFieldSize;
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);


	// 2021.10.05 시뮬레이션시 Emission 강제로 끄고 가이드빔 켜기
#ifdef _RTC_Test_
	pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);
#else
	CFiberLaser* pLaserControl = static_cast<CFiberLaser*>( pPointerManager->GetLaserControl());	
	pLaserControl->SendDataToPort("EMOFF");
	pLaserControl->SendDataToPort("ABN");
#endif

	double cs = cos(PI * pFieldParameter->GetFieldAngle() / 180);
	double sn = sin(PI * pFieldParameter->GetFieldAngle() / 180);

	if(bRTCIsReady)
	{
		pDsp->Set_Matrix(cs,sn);
	}



	iter = dataList.begin();
	m_vLaserPos = iter->pos;
	
	auto tempiter = ++iter;
	--iter;
	m_vDir = tempiter->pos - iter->pos;
	return true;

}


void CLaserSimulator::MakeRealPatternData()
{
	CFieldParameter* pFieldParameter = pFieldParameter->GetInstance();
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
	CParameter *pParameter = iterator->GetCurrentItem();
	_NOTCH_PATTERN_DATA data = pFieldParameter->GetHEAD2PatternDataOfKoem();

	
	patternDataX.clear();
	patternDataY.clear();
	patternDataX.reserve(data.dTabCount * 5); // 대충 계산해두자
	patternDataY.reserve(data.dTabCount * 5);
	double yOffset = 130;

	double dNotchRoot = data.dNotchRoot - data.dHEAD2Width;
	double totalY = yOffset;

	//플래그부분 List1
	for(int i=0;i<data.dTabCount;++i)
	{
		patternDataX.push_back(data.dTabHeight);//밖에서
		patternDataY.emplace_back(yOffset + i*data.dTabWidth);

		patternDataX.push_back(dNotchRoot);//안으로
		patternDataY.emplace_back(yOffset + i*data.dTabWidth);

		totalY += data.dTabWidth;
	}

	//Unflag부분
	patternDataX.push_back(data.dTabHeight);
	patternDataY.push_back(totalY);

	patternDataX.emplace_back(data.dBuriedHeight - data.dHEAD2Width);
	patternDataY.push_back(totalY);
	
	
	//
	//while(currlength < data.dBuriedRegion)
	//{
	//	patternDataX.emplace_back(data.dBuriedHeight - data.dHEAD2Width);
	//	patternDataY.push_back(totalY);
	//	totalY += 1;
	//	currlength += 1;
	//}
	int currlength = 0;
	for(int i=0;i<data.dBuriedRegion;++i)
	{

		patternDataX.emplace_back(data.dBuriedHeight - data.dHEAD2Width);
		patternDataY.push_back(totalY);
		totalY += 1;
		currlength += 1;
	}



	patternDataX.push_back(data.dTabHeight);
	patternDataY.push_back(totalY);

	for(int i=0;i<data.dTabCount;++i)
	{
		totalY += data.dTabWidth;
		patternDataX.push_back(data.dTabHeight);
		patternDataY.push_back(totalY);

		patternDataX.emplace_back(data.dNotchRoot - data.dHEAD2Width);
		patternDataY.push_back(totalY);
	}


}


void CLaserSimulator::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nID == SC_CLOSE)
	{
		StopLaserSimulation();
	}

	CDialogEx::OnSysCommand(nID, lParam);
}


void CLaserSimulator::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	StopLaserSimulation();
	CDialogEx::OnOK();
}


void CLaserSimulator::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	StopLaserSimulation();
	CDialogEx::OnCancel();
}

void CLaserSimulator::FirstShowGrapbh(CChartViewer* viewer)
{
	CRect rect;
	GetClientRect(&rect);



	XYChart *c = new XYChart(rect.left + 400,rect.bottom - 30 , 0x0000CD, 0x000000, 1);
	c->setBackground(c->linearGradientColor(0, 0, 0, c->getHeight() / 2, 0x313e50,0x313e50), Chart::Transparent);
	c->setRoundedFrame();
	//c->setDropShadow();
	c->setPlotArea(30, 30, rect.left + 400 - 30 ,rect.bottom -90, c->linearGradientColor(0, 55, 0, 335, 0x000000,
		0x000000), -1,  0x000000, 0x000000);
	c->setClipping();
	c->addTitle("KOEM LASER NOTCH SIMULATOR", "timesbi.ttf", 15
		)->setBackground(0xdddddd, 0x000000, Chart::glassEffect());
	/*c->xAxis()->setTitle("Length (mm)", "arialbd.ttf",10);
	c->yAxis()->setTitle("Height (cm)", "arialbd.ttf",10);*/
	c->xAxis()->setWidth(2);
	c->yAxis()->setWidth(2);
	c->xAxis()->setColors(0xc5c5c5,0xc5c5c5,0xc5c5c5,0xc5c5c5);
	c->yAxis()->setColors(0xc5c5c5,0xc5c5c5,0xc5c5c5,0xc5c5c5);

	viewer->setChart(c);
	viewer->ShowWindow(TRUE);

	delete c;
}


double CLaserSimulator::QuadraticFormulaForSimul(double a,double b,double c)
{
	if(a<0)
	{
		a *= -1;
		b *= -1;
		c *= -1;
	}



	return (-b+sqrt(b*b - 4.0*a*c)) / (2.0*a);
}

void CLaserSimulator::StopLaserSimulation()
{
	if(bRTCIsReady)
	{
		stop_execution();
	}
}



double  CLaserSimulator::CalculateLaserTime(double laserSpeed,double rollSpeed, double x,double y)
{
	double retTime = QuadraticFormulaForSimul((laserSpeed * laserSpeed) - (rollSpeed * rollSpeed), 2 * rollSpeed * y, - ( x * x + y * y));

	return retTime;
}
