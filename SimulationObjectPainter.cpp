// SimulationObjectPainter.cpp: implementation of the CSimulationObjectPainter class.
//
//////////////////////////////////////////////////////////////////////-33333333333333333333333333

#include "stdafx.h"
#include "beameditor6.h"
#include "SimulationObjectPainter.h"
#include "MathUtil.h"
#include "return.h"
#include "ParameterColor.h"
#include "MainFrm.h"
#include "BeamEditor6Doc.h"

#include "stdafx.h"
#include "BeamEditor6.h"
#include "TabStandardPara.h"
#include "LoadString.h"
#include "FieldParameter.h"
#include "PointerContainer.h"
#include "PointerManager.h"
#include "InitialTable.h"
#include "RS232.h"
#include "TimeChecker.h"
#include "DlgFiber.h"
#include "Dsp.h"


#include "Device.h"
#include "DeviceArea.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define PI	3.1415926535
#define STEP_DIST_VECTOR 3
#define DELAY_TIME       1

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSimulationObjectPainter::CSimulationObjectPainter()
{
}

CSimulationObjectPainter::~CSimulationObjectPainter()
{

}

void CSimulationObjectPainter::SetDelayTime()
{
	DWORD dwTick = GetTickCount();
	while(m_bIsSimulation == TRUE && (int(GetTickCount() - dwTick) < DELAY_TIME))	
	{
		if (m_bIsSimulation == FALSE)
			break;
		
		/*if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			
			TranslateMessage(&msg);
			DispatchMessage(&msg);
				
		}*/
		//Sleep(0);
	}
}


UINT CSimulationObjectPainter::Draw(CDC *pDC, CDPoint ptPosition, CDSize size, Vector *pVecData, int iNumberofVector, int iObjWidth, int iObjHeight, double dAngle, BOOL bKoemPattern)
{
	

	return R_DEFAULT;
}


UINT CSimulationObjectPainter::Draw(CDC *pDC, CDPoint ptPosition, CDSize size, Vector *pVecData, int iNumberofVector, int iObjWidth, int iObjHeight, double dAngle)
{
	CPoint ptPoint;
	CPen LinePen(PS_SOLID,2,m_colLine );
	CPen MovePen(PS_DOT,2,m_colMove );
	CPen LinePen0(PS_SOLID,1,CParameterColor::Instance().GetParaCol( 19));
	BOOL bFirst = TRUE;

	//CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	//CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	//ptPosition.x = 0; ptPosition.y = 0;

	pDC->SelectObject(MovePen);
	//pDC->MoveTo(ptPosition);
	pDC->LineTo(ptPosition);

	double px=ptPosition.x , py=ptPosition.y;

	double dScreenMagX = (double)size.cx / (double) iObjWidth;   // ( 그려질 영역의 너비 / 진짜 데이타 너비 )
	double dScreenMagY = (double)size.cy / (double) iObjHeight; //  ( 그려질 영역의 높이 / 진짜 데이타 높이 )

	double tx, ty;

	double dpx = 0, dpy = 0;

	double markspeed = 0, RollSpeed = 0;

	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
	CParameter *pParameter = iterator->GetCurrentItem();
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	_NOTCH_PATTERN_DATA m_stNotchPatternData = pFieldParameter->GetHEAD2PatternDataOfKoem();

	double dMmSize, dFieldSize;
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	double m_dMaxField;
	double m_dMaxMM;
	int zeroIndex = 0;
	m_dMaxField = dFieldSize;
	m_dMaxMM    = dMmSize;

	dAngle = pFieldParameter->GetFieldAngle();

	double Xoffset = 0, Yoffset = 0;

	if(dAngle==0)
	{
		Xoffset = pFieldParameter -> GetMasterX();
		Yoffset = pFieldParameter -> GetMasterY();
	}
	else if(dAngle == 90)
	{
		Yoffset = pFieldParameter -> GetMasterX();
		Xoffset = pFieldParameter -> GetMasterY();
	}
	dAngle=0;

	Xoffset = Xoffset * dScreenMagX;
	Yoffset = Yoffset * dScreenMagY;

	double fSpeed;
	CString strSpeed;
	double m_iMarkStep, m_iStepPeriod, m_iJumpStep;
	double markingtime = 0;
	double relmarkdistance = 0;
	double stepdistance = 0;
	double x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	double mark_stip[10];
	int A = 0;
	int Paraindex = 0;
	m_iStepPeriod = 0;
	bool bLineFlag,bExtendFlag, bMoveFlag, bDisExtFlag, bFirstVectorFlag;
	bLineFlag = false;bExtendFlag= false;bMoveFlag = false;bDisExtFlag=false;bFirstVectorFlag=false;
	long GoX = 0, GoY = 0;
	int GoXx[200], GoYy[200];

	m_iMarkStep = pParameter->GetMarkStep();
	m_iJumpStep = pParameter->GetJumpStep();
	m_iStepPeriod = pParameter->GetStepPeriod();
	RollSpeed = pFieldParameter->GetRollSpeed();

	double MMSize = 0, FieldSize = 0, Period = 0;
	MMSize = (double)pInitialTable->GetMMSize();
	FieldSize = (double)pInitialTable->GetFieldSize();
	Period = ((double)m_iStepPeriod / 1000000.) * 10;
	double dSloopWidth = 0;
	dSloopWidth = pFieldParameter->GetSloopWidth();

	//---------------------------------------------------------------------------------------------------------------------

	/*iterator->SetFirst();

	while (iterator->HasNext()) {

	CParameter *pParameter = iterator->GetCurrentItem();
	if (pParameter->GetIndex()+1 < 10) 
	{
	mark_stip[Paraindex] = pParameter->GetMarkStep();
	jump_stip[Paraindex] = pParameter->GetJumpStep();
	index_stip[Paraindex] = pParameter->GetIndex();

	mark_stip[Paraindex] = ((double)mark_stip[Paraindex] * ((double)pInitialTable->GetMMSize() / (double)pInitialTable->GetFieldSize()) 
	/ (10 / 1000000.)) / 10;
	jump_stip[Paraindex] = ((double)jump_stip[Paraindex] * ((double)pInitialTable->GetMMSize() / (double)pInitialTable->GetFieldSize()) 
	/ (10 / 1000000.)) / 10;

	Paraindex++;
	iterator->SetNext();


	}
	else {
	break;
	}
	}*/

	mark_stip[0] = pParameter->GetUnflagLineSpeed();
	mark_stip[1] = pParameter->GetFlagSpeed();
	mark_stip[2] = pParameter->GetUnflagInoutSpeed();
	mark_stip[3] = pParameter->GetUnflagLineSpeed();
	mark_stip[4] = pParameter->GetUnflagLineSpeed();


	//--------------------------------------------MiniVector 관련------------------------------------------------------

	double dX = 0, dMoveX = 0;
	int iAdjustVector = 0;
	int iStep = 0;
	dX = STEP_DIST_VECTOR;
	dX = dX * m_dMaxField / m_dMaxMM;
	Vector *NewVector = new Vector[iNumberofVector*5];
	memcpy(NewVector, pVecData,  sizeof(Vector) * iNumberofVector*5);

	double dMarkSpeed, dJumpSpeed;

	dMarkSpeed = (double)pParameter->GetMarkStep()*100/pParameter->GetStepPeriod(); 
	dJumpSpeed = (double)pParameter->GetJumpStep()*100/pParameter->GetStepPeriod();

	//----------------------------------------------------Tap.Gap 적용-------------------------------------------
	CDsp *pDsp = CDsp::GetInstance();
	CDeviceManager *DeviceManager=CDeviceManager::Instance();
	CDeviceData *pDeviceData = DeviceManager->GetDeviceData();
	st_Tap_PositionData st_Tap_Data;
	int nTapPositionTestCnt = pDeviceData->Get_TapPositionCount();

	//------------------------------------------ IAdjustVector 갯수 계산 ----------------------------------------------------

	for(int i = 0; i < iNumberofVector ; i++)
	{
		x1 = pVecData[i].d.x;
		y1 = pVecData[i].d.y;

		x2 = x1 + pVecData[i].d.x;
		y2 = y1 + pVecData[i].d.y;

		stepdistance = sqrt(pow((double)x2 - (double)x1, 2) + pow((double)y2 - (double)y1, 2));

		dpy += stepdistance;
	}

	dpy = dpy +1;

	//----------------------------------------------------------- n루프 시작 ------------------------------------------------
	for(int n = 1; n < nTapPositionTestCnt; n++)
	{
#ifdef	_RTC_Test_
		pDsp->OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, TRUE);
#endif
		set_start_list(1);
		pDsp->SetParameterNumber(PARA_INDEX_SIMUL);
		pDsp->SetParameterDataList_Change();

		st_Tap_Data = pDeviceData->Get_TapPosition(n);
		iAdjustVector = 0;
		px = 0;
		py = 0;
		GoX = 0;
		GoY = 0;
		dpx = 0;
		dMoveX = 0;
		bLineFlag = false;
		bExtendFlag= false;
		bMoveFlag = false;
		bDisExtFlag=false;
		bFirstVectorFlag = false;
		for(int i = 0; i < 200 ; i++)
		{
			GoXx[i] = 0;
			GoYy[i] = 0;
		}

		//-------------------------------------------------------미니벡터링시작-------------------------------------------------
		for(int i = 0; i < iNumberofVector; i++)
		{
			if(pVecData[i].t == 8) // Get_TapPosition 적용
			{
				pVecData[i].d.x = 0;
				pVecData[i].d.x = (st_Tap_Data.dGap * m_dMaxField / m_dMaxMM) - (m_stNotchPatternData.dWidth * m_dMaxField / m_dMaxMM) - dSloopWidth; // Gap에 CellWidth 빼주기.
			}

			x1 = pVecData[i].d.x;
			y1 = pVecData[i].d.y;

			x2 = x1 + pVecData[i].d.x;
			y2 = y1 + pVecData[i].d.y;

			stepdistance = sqrt(pow((double)x2 - (double)x1, 2) + pow((double)y2 - (double)y1, 2));

			iStep = stepdistance / dX; // stepdistance 거리가 dX보다 클 경우의 각 거리 계산

			for(int j = iAdjustVector; j < (int)dpy ; j++)
			{
				if(i == iNumberofVector-1)
				{
					iAdjustVector = j + 1;
					break;
				}
				if(i == 0)
				{
					NewVector[j].d.x = pVecData[i].d.x;
					NewVector[j].d.y = pVecData[i].d.y;
					NewVector[j].t =  pVecData[i].t;
					iAdjustVector = j + 1;
					break;
				}
				if(i == 1 && stepdistance < dX)// ExpendDist 길이가 dX보다 짧을때 제대로 벡터가 생성되지 않던 현상 수정을 위해
				{
					if(m_stNotchPatternData.dExpendDist > 0)
					{
						NewVector[j].d.x = pVecData[i].d.x;
						NewVector[j].d.y = pVecData[i].d.y;
						NewVector[j].t =  pVecData[i].t;
						iAdjustVector = j + 1;
						break;
					}
				}
				if(stepdistance > dX && bFirstVectorFlag == false) // stepdistance 가 dX보다 클 경우 && 작을때의 마지막 벡터에서 다시 진입하는것 방지.
				{
					NewVector[j].d.x = (pVecData[i].d.x / iStep); // X 차이
					NewVector[j].d.y = (pVecData[i].d.y / iStep); // Y 차이
					NewVector[j].t =  pVecData[i].t;
					dpx += NewVector[j].d.x;

					if(dpx < pVecData[i].d.x -5) // (-5 = 계산 오차 방지) pVecData[i].d.x 까지의 거리 계산
					{
						iAdjustVector = j + 1;
						continue;
					}

					else
					{
						dpx = 0; // 벡터 누적 초기화
						iAdjustVector = j + 1;
						break;
					}
				}
				else
				{
					if(bFirstVectorFlag == false) // 처음 진입했을때 벡터 초기화.
					{
						NewVector[j].d.x = 0;
						NewVector[j].d.y = 0;
						dMoveX = 0;
					}
					dMoveX += stepdistance; // 거리 누적
					if(dMoveX > dX) // 누적거리가 dX 초과시
					{
						bFirstVectorFlag = false;// 최초 벡터설정을 위해
						NewVector[j].t = 4;
						iAdjustVector = j + 1;
						i = i - 1; // 벡터 초과시 버려지는 데이터 회수.
						break;
					}
					NewVector[j].d.x += pVecData[i].d.x; // X벡터 누적
					NewVector[j].d.y += pVecData[i].d.y; // Y벡터 누적
					bFirstVectorFlag = true; // 벡터 초기화 방지.
					break;
				}

			}
		}

		//--------------------------------------------------------------------------------------------------------------------------------------

		if( dAngle == 0 )
		{
			for( int i = 0 ; i < iAdjustVector ; i++)
			{
				x1 = 0;
				y1 = 0;

				x2 = pVecData[1].d.x;
				y2 = pVecData[1].d.y;

				stepdistance = sqrt(pow((double)x2 - (double)x1, 2) + pow((double)y2 - (double)y1, 2));

				iStep = stepdistance / dX; //Expend 벡터갯수 계산
				if(iStep == 0)// ExpendDIst가 있지만 stepdistance가 짧아서 iStep이 0이 되는경우 수정.
				{
					iStep = 1;
				}

				//-------------------------------파라메터 변환 할 곳 정의 -----------------------------------------------
				if( i == 0 && bExtendFlag == false)
				{
					fSpeed = mark_stip[0];
					bLineFlag = true;
				}

				else if(i <= iStep && m_stNotchPatternData.dExpendDist > 0 )
				{
					bExtendFlag = true;
					fSpeed = mark_stip[0];
					bLineFlag = true;
				}

				else
				{
					fSpeed = mark_stip[1];
				}

				if(NewVector[i].t == 8)
				{
					fSpeed = mark_stip[2];
					bLineFlag = false;
				}

				if(NewVector[i].t == 4 && bLineFlag == false)
				{
					fSpeed = mark_stip[3];
					if(stepdistance / dX >= 1)// 그냥 1을 추가하면, stepdistance가 dX보다 짧을때 제대로 파라메터가 적용되지 않아서 만듦
					{
						iStep = iStep + 1;
					}
					if (bExtendFlag == true && i >= iAdjustVector-(iStep))
					{
						fSpeed = mark_stip[4];
					}
				}

				//fSpeed = 1000;
				//----------------------------------------------------------- 미니벡터 적용 전 파라메타 변환 적용 --------------------------------------------------------
				/*if( i == 0 && bExtendFlag == false)
				{
				fSpeed = mark_stip[0];
				bLineFlag = true;
				}

				else if(i == 1 && m_stNotchPatternData.dExpendDist > 0 )
				{
				bExtendFlag = true;
				fSpeed = mark_stip[0];
				bLineFlag = true;
				}

				else
				{
				fSpeed = mark_stip[1];
				}

				if(pVecData[i].t == 8)
				{
				fSpeed = mark_stip[2];
				bLineFlag = false;
				}

				if(pVecData[i].t == 4 && bLineFlag == false)
				{
				fSpeed = mark_stip[3];

				if (bExtendFlag == true && i == iNumberofVector-2)
				{
				fSpeed = mark_stip[4];
				}
				}*/
				//------------------------------------------------------------- 스캐너 속도 적용 -----------------------------------------------------
				x1 = NewVector[i].d.x;
				y1 = NewVector[i].d.y;

				x2 = x1 + NewVector[i].d.x;
				y2 = y1 + NewVector[i].d.y;

				stepdistance = sqrt(pow((double)x2 - (double)x1, 2) + pow((double)y2 - (double)y1, 2)); 

				markspeed = fSpeed;

				markingtime = stepdistance / markspeed;

				relmarkdistance = RollSpeed * markingtime; 

				GoX += (NewVector[i].d.x - relmarkdistance);
				GoY += (NewVector[i].d.y);
				GoXx[i] = GoX;
				GoYy[i] = GoY;

				px += (NewVector[i].d.x *dScreenMagX);
				if(pFieldParameter->GetPatternFlipY() == true)
				{
					py -= (NewVector[i].d.y *(-dScreenMagY));
				}
				else
				{
					py += (NewVector[i].d.y *(-dScreenMagY));
				}
				px = px - (relmarkdistance * dScreenMagX);

				if(i == 0) // Offset 적용
				{
					px = 0; // 시작위치 고정
					py = py - Yoffset;
					px = px + Xoffset;
					if(pFieldParameter->GetPatternFlipY() == true)
					{
						py = py - iObjHeight;
						py = py + (m_stNotchPatternData.dExpendDist * m_dMaxField / m_dMaxMM);
					}

				}
				if(n != 1)
				{
					pDsp->Jump_Abs(GoX,GoY);
				}
				//------------------------------------------------------------ simulation Draw Start -------------------------------------------------------------

				//ptPoint.x = (long)floor(px+0.5);
				//ptPoint.y = (long)floor(py+0.5);
				ptPoint.x = (long)floor(px);
				ptPoint.y = (long)floor(py);


				if( NewVector[i].t == 4) {
					pDC->SelectObject(LinePen);
					//SetDelayTime();
					pDC->LineTo(ptPoint);
				}
				else if( NewVector[i].t == 1) {
					// 2007.05.01  
					//if (pDoc->m_bHotLife == LIFE_OLD && m_colLine == RGB(127,127,127))
					//	pDC->SelectObject(LinePen);
					//else
					pDC->SelectObject(LinePen0);

					///if(m_bIsSimulation == TRUE)
					//	SetDelayTime();
					pDC->LineTo(ptPoint);
				}
				else if(NewVector[i].t == 8){
					pDC->SelectObject(LinePen);
					//SetDelayTime();
					pDC->LineTo(ptPoint);
				}
				else {
					pDC->SelectObject(MovePen);
					//SetDelayTime();
					//if(!bFirst)
					pDC->LineTo(ptPoint);
					bFirst = FALSE;
				}
				Sleep(1);
				//SetDelayTime();


			}
			if(n == 1)
			{
				for(int i = 0 ; i < iAdjustVector ; i++)
				{
					GoX = GoXx[i];
					GoY = GoYy[i];
					pDsp->Jump_Abs(GoX,GoY);
				}
			}

			//SetDelayTime();
		}
		else 
		{
			double cs,sn;
			cs = cos(PI * dAngle / 180);
			sn = sin(PI * dAngle / 180);

			for( int i = 0 ; i < iNumberofVector ; i++)
			{
				CMathUtil::GetRotatePoint( pVecData[i].d.x * dScreenMagX, pVecData[i].d.y *(-dScreenMagY), -dAngle, tx,ty);
				// -dAngle인 이유 : -dScreenMagY를 곱해주는 순간 화면상의 좌표계로 바뀐다. 그런데 화면상의 좌표계는 Y축이 뒤집혀있다. 따라서 시계방향으로 돌리고 싶으면
				// 실제로는 -dAngle을 넣어줘야 시계방향으로 dAngle만큼 이동한다.
				//tx = (cs * pVecData[i].d.x * dScreenMagX) + (sn * pVecData[i].d.y *(-dScreenMagY));
				//ty = -(sn * pVecData[i].d.x * dScreenMagX) + (cs * pVecData[i].d.y *(-dScreenMagY));

				px += tx;
				py += ty;

				ptPoint.x = (long)floor(px + 0.5);
				ptPoint.y = (long)floor(py + 0.5);

				if( pVecData[i].t == 4) {
					pDC->SelectObject(LinePen);
					SetDelayTime();
					pDC->LineTo(ptPoint);
				}
				else if( pVecData[i].t == 1) {
					// 2007.05.01  
					//if (pDoc->m_bHotLife == LIFE_OLD && m_colLine == RGB(127,127,127))
					//	pDC->SelectObject(LinePen);
					//else
					pDC->SelectObject(LinePen0);

					if(m_bIsSimulation == TRUE)
						SetDelayTime();
					pDC->LineTo(ptPoint);
				}
				else {
					pDC->SelectObject(MovePen);
					SetDelayTime();
					//if(!bFirst)
					pDC->LineTo(ptPoint);
					bFirst = FALSE;
				}
			}
		}
		set_end_of_list();
		execute_list(1);
		Sleep(1);
		TListExeStat stStat;
		while(1)
		{
			stStat = pDsp->ReadStatus();
			if(stStat.bBusy1 == FALSE && stStat.bBusy2 == FALSE)
			{
				break;
			}
			Sleep(0);
		}
#ifdef	_RTC_Test_
				pDsp->OutputIO(RTCIO_O_GUIDEBEAM_ENABLE, FALSE);
#endif		
	}

	//set_end_of_list();
	//execute_list_1();

	//pDC->SelectObject(pOldPen);
	
	return R_DEFAULT;

}

UINT CSimulationObjectPainter::Draw(CDC *pDC, CDPoint ptPosition, CDSize size, Vector *pVecData, int iNumberofVector, double dAngle)
{
	CPoint ptPoint;
	CPen LinePen(PS_SOLID,1,m_colLine );
	CPen MovePen(PS_DOT,1,m_colMove );
	CPen LinePen0(PS_SOLID,1,CParameterColor::Instance().GetParaCol( 19) );
    
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 

	pDC->SelectObject(MovePen);
	pDC->LineTo(ptPosition);

	double px = 0 , py = 0;

	double dScreenMagX = 1;   // ( 그려질 영역의 너비 / 진짜 데이타 너비 )
	double dScreenMagY = 1; //  ( 그려질 영역의 높이 / 진짜 데이타 높이 )

	double tx, ty;

	if( dAngle == 0 )
	{
		for( int i = 0 ; i < iNumberofVector ; i++)
		{		
			px += (pVecData[i].d.x *dScreenMagX);
			py += (pVecData[i].d.y *(-dScreenMagY));
			
			ptPoint.x = (long)floor(px+0.5);
			ptPoint.y = (long)floor(py+0.5);
			
			if( pVecData[i].t == 4) {
				pDC->SelectObject(LinePen);
				SetDelayTime();
				pDC->LineTo(ptPoint);
			}
			else if( pVecData[i].t == 1) {
				// 2007.05.01  
				if (pDoc->m_bHotLife == LIFE_OLD && m_colLine == RGB(127,127,127))
					pDC->SelectObject(LinePen);
				else
					pDC->SelectObject(LinePen0);

				if(m_bIsSimulation == TRUE)
				SetDelayTime();
				pDC->LineTo(ptPoint);
			}
			else {
				pDC->SelectObject(MovePen);
				SetDelayTime();
				pDC->LineTo(ptPoint);
			}
		}
	}
	else 
	{
		double cs,sn;
		cs = cos(PI * dAngle / 180);
		sn = sin(PI * dAngle / 180);

		for( int i = 0 ; i < iNumberofVector ; i++)
		{
			CMathUtil::GetRotatePoint( pVecData[i].d.x * dScreenMagX, pVecData[i].d.y *(-dScreenMagY), -dAngle, tx,ty);
			// -dAngle인 이유 : -dScreenMagY를 곱해주는 순간 화면상의 좌표계로 바뀐다. 그런데 화면상의 좌표계는 Y축이 뒤집혀있다. 따라서 시계방향으로 돌리고 싶으면
			// 실제로는 -dAngle을 넣어줘야 시계방향으로 dAngle만큼 이동한다.
			//tx = (cs * pVecData[i].d.x * dScreenMagX) + (sn * pVecData[i].d.y *(-dScreenMagY));
			//ty = -(sn * pVecData[i].d.x * dScreenMagX) + (cs * pVecData[i].d.y *(-dScreenMagY));
			
			px += tx;
			py += ty;
			
			ptPoint.x = (long)floor(px + 0.5);
			ptPoint.y = (long)floor(py + 0.5);
			
			if( pVecData[i].t == 4) {
				pDC->SelectObject(LinePen);
				SetDelayTime();
				pDC->LineTo(ptPoint);
			}
			else if( pVecData[i].t == 1) {
				// 2007.05.01  
				if (pDoc->m_bHotLife == LIFE_OLD && m_colLine == RGB(127,127,127))
					pDC->SelectObject(LinePen);
				else
					pDC->SelectObject(LinePen0);

				if(m_bIsSimulation == TRUE)
				SetDelayTime();
				pDC->LineTo(ptPoint);
			}
			else {
				pDC->SelectObject(MovePen);
				SetDelayTime();
				pDC->LineTo(ptPoint);
			}
		}
	}

		
	//pDC->SelectObject(pOldPen);

	return R_DEFAULT;
}

UINT CSimulationObjectPainter::Draw(CDC *pDC, CDPoint ptPosition, CDSize size, Vector *pVecData, int iNumberofVector, int iObjWidth, int iObjHeight)
{
	return Draw(pDC, ptPosition, size, pVecData, iNumberofVector, iObjWidth, iObjHeight, 0);
}

UINT CSimulationObjectPainter::Draw(CDC *pDC, CDPoint ptPosition, CDSize Size, char *psrcDib, SIZE srcSize, int iObjWidth, int iObjHeight)
{
	return R_DEFAULT;
}

// Arc를 벡터 아닌 Arc로 그리는 페인터 추가 
UINT CSimulationObjectPainter::Draw(CDC *pDC, CDPoint ptPosition, CRect rtRect, CPoint ptStart, CPoint ptEnd, int iObjWidth, int iObjHeight, double dAngle)
{
	// 여기서 그리기는 부분
	return R_DEFAULT;
}

// Line을 벡터 아닌 Line으로 그리는 페인터 추가 
UINT CSimulationObjectPainter::Draw(CDC *pDC, CDPoint ptPosition, CPoint ptStart, CPoint ptEnd, int iObjWidth, int iObjHeight)
{
	// 여기서 그리기는 부분
	return R_DEFAULT;
}

void CSimulationObjectPainter::SetLineRGB(COLORREF _rgb)
{
	m_colLine = _rgb;
}

void CSimulationObjectPainter::SetMoveRGB(COLORREF _rgb)
{
	m_colMove = _rgb;
}

COLORREF CSimulationObjectPainter::GetLineRGB()
{
	return m_colLine;
}
		
COLORREF CSimulationObjectPainter::GetMoveRGB()
{
	return m_colMove;
}

void CSimulationObjectPainter::SetLineWidth(int iLineWidth)
{
	m_iLineWidth = iLineWidth;
}

int CSimulationObjectPainter::GetLineWidth()
{
	return m_iLineWidth;
}

void CSimulationObjectPainter::SetSimulation(BOOL bIsSimulation)
{
	m_bIsSimulation = bIsSimulation;
}	

void CSimulationObjectPainter::SetSimulationSpeed(int iSpeed)
{
	m_iSpeed = iSpeed;
}	