// PowerControlView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "PowerControlView.h"
#include "afxdialogex.h"
#include "Parameter.h"



// PowerControlView 대화 상자입니다.

IMPLEMENT_DYNAMIC(PowerControlView, CDialogEx)

PowerControlView::PowerControlView(CWnd* pParent /*=NULL*/)
	: CDialogEx(PowerControlView::IDD, pParent)
{
	
	nonflagStart_IntervalCount = 280;                 // 반복횟수 웬만하면 수정하지 마세요
	nonflagEnd_IntervalCount = 280;
	nonflagStart_Destvolt = 10.0f;
	nonflagStart_Currvolt = 3.0f;	
	nonflagEnd_Destvolt = 3.0f;
	nonflagEnd_Currvolt = 10.f;


	isIncrease = true;
	nonflagStart_TotalTime = 280; //ms
	nonflagEnd_TotalTime = 280;

	nonflagEnd_DelayTime = 112;
	nonflagStart_DelayTime = 112;
	currState = 0;
	
	
	
}

PowerControlView::~PowerControlView()
{
}

void PowerControlView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}



BEGIN_MESSAGE_MAP(PowerControlView, CDialogEx)
//	ON_WM_PAINT()
	//ON_WM_PAINT()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	
	ON_BN_CLICKED(IDC_POWERCTRL_APPLY, &PowerControlView::OnBnClickedPowerctrlApply)
	ON_BN_CLICKED(IDC_PCOKBUTTON, &PowerControlView::OnBnClickedOk)
	ON_BN_CLICKED(IDC_PCINCREASE_CHECK, &PowerControlView::OnBnClickedPcincreaseCheck)
	
	ON_CBN_SELCHANGE(IDC_PC_COMBO, &PowerControlView::OnCbnSelchangePcCombo)
END_MESSAGE_MAP()


// PowerControlView 메시지 처리기입니다.


//void PowerControlView::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//	@TG
//#3073
//		// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//		// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
//}



void PowerControlView::OnPaint()
{
	
}


BOOL PowerControlView::OnInitDialog()
{
	//CDialogEx::OnInitDialog();
	CString setValueString;

	
	
	
	setValueString.Format("%d",nonflagStart_TotalTime); 
	SetDlgItemText(IDC_PCDELAYTIME_EDIT,setValueString);
	//setValueString.Format("%f.3f",maxVolt); // 3자리로 안잘리고 뒤에 3f가 붙는다 ㅠㅠ
	setValueString.Format("%.5f",nonflagStart_Destvolt);
	SetDlgItemText(IDC_PCMAXVOLT_EDIT,setValueString);	
	setValueString.Format("%.5f",nonflagStart_Currvolt);
	SetDlgItemText(IDC_PCSETVOLT_EDIT,setValueString);

	
	CheckDlgButton(IDC_PCINCREASE_CHECK, isIncrease);

	
	((CComboBox*)GetDlgItem(IDC_PC_COMBO))->InsertString(0,"NonFlagStart");
	((CComboBox*)GetDlgItem(IDC_PC_COMBO))->InsertString(1,"NonFlagEnd");	
	((CComboBox*)GetDlgItem(IDC_PC_COMBO))->SetCurSel(currState);


	
	DrawGraph();

	return true;
}


void PowerControlView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC cDC(this);

	CString pointString;
	pointString.Format("X = %d, Y = %d",point.x,point.y);

	cDC.TextOutA(600,100,pointString);


	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void PowerControlView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	CDialogEx::OnLButtonDown(nFlags, point);
}

void PowerControlView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void PowerControlView::OnBnClickedPowerctrlApply()
{
	





	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString getValueString;

	if(currState)
	{	
		GetDlgItemText(IDC_PCDELAYTIME_EDIT,getValueString);
		nonflagEnd_TotalTime = atoi(getValueString);
		nonflagEnd_IntervalCount = nonflagEnd_TotalTime;
	
		GetDlgItemText(IDC_PCMAXVOLT_EDIT,getValueString);
		nonflagEnd_Destvolt = atof(getValueString);
	
		GetDlgItemText(IDC_PCSETVOLT_EDIT,getValueString);
		nonflagEnd_Currvolt = atof(getValueString);


	}

	else
	{
		GetDlgItemText(IDC_PCDELAYTIME_EDIT,getValueString);
		nonflagStart_TotalTime = atoi(getValueString);	
		nonflagStart_IntervalCount = nonflagStart_TotalTime;
	
		GetDlgItemText(IDC_PCMAXVOLT_EDIT,getValueString);
		nonflagStart_Destvolt = atof(getValueString);
	
		GetDlgItemText(IDC_PCSETVOLT_EDIT,getValueString);
		nonflagStart_Currvolt = atof(getValueString);
	}

	DrawGraph();
	
	
}


void PowerControlView::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	//여기서 파라미터값 설정하는 객체에 접근하여 현재 변수들을 넣어주면 된다.

	CDialogEx::OnOK();
}



void PowerControlView::OnEnChangePcmaxvoltEdit()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void PowerControlView::DrawGraph()
{
	Invalidate(true);

	//현재 클라이언트의 DC를 얻어옵니다.
	CClientDC cDC(this);
	cDC.SetBkMode(TRANSPARENT);
	

	//SetWindowPos(NULL,0,0,985,562,0); //윈도우 사이즈를 강제로 지정합니다.

	
	//현재 클라이언트의 윈도우 사이즈를 가져옵니다.
	RECT currWindowRect;
	GetClientRect(&currWindowRect);

	//GDI객체를 생성 및 초기화합니다.
	CPen blackSolidPen,whiteSolidPen,blackDashPen,redSolidPen,*oldPen;
	blackSolidPen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	blackDashPen.CreatePen(PS_DOT,1,RGB(0,0,0));
	whiteSolidPen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	redSolidPen.CreatePen(PS_SOLID,2,RGB(255,0,0));
	CBrush whiteBrush(RGB(255,255,255)), *oldBursh;	
	


	// 표를 그리기 위한 변수들
	int bottomBlank = 112;
	int rightBlankArea = 235;
	int leftTopBlankArea = 50;
	int myScreenLeft = currWindowRect.left + leftTopBlankArea;
	int myScreenTop = currWindowRect.top + leftTopBlankArea;
	int myScreenRight = currWindowRect.right - rightBlankArea;
	int myScreenBottom = currWindowRect.bottom - bottomBlank;

	int myScreenWidth = myScreenRight - myScreenLeft;
	int myScreenHeight = myScreenBottom - myScreenTop;

	int axisMarkDistance = 15;
	int yOffset = 0;
	float devideCount = 10.0;
	float yAxisCount = (myScreenBottom - myScreenTop) / devideCount;
	float xAxisCount = (myScreenRight - myScreenLeft) / devideCount;
	xAxisCount *= yAxisCount / xAxisCount;
	
	//배경 그리기
	oldBursh = cDC.SelectObject(&whiteBrush);
	cDC.Rectangle(myScreenLeft,myScreenTop ,myScreenRight,myScreenBottom);
	

	//세로줄 그리기
	int voltValue = 10;
	int tableVoltVariation = 1;
	cDC.SetTextAlign(TA_RIGHT);
	for(int i=myScreenTop ;i <= myScreenBottom; i += yAxisCount, voltValue -= tableVoltVariation)
	{
		cDC.MoveTo(myScreenLeft,i);
		oldPen = cDC.SelectObject(&blackSolidPen);
		cDC.LineTo(myScreenLeft - axisMarkDistance + 3,i); // 일의자리가 겹칩니다 
		CString voltValueToString;
		voltValueToString.Format(_T("%dV"), voltValue);
		cDC.TextOutA(myScreenLeft - axisMarkDistance - 5,i - 5,voltValueToString,voltValueToString.GetLength());
		oldPen = cDC.SelectObject(&blackDashPen);
		cDC.MoveTo(myScreenLeft,i);
		cDC.LineTo(myScreenRight,i);	
	}

	//가로줄 그리기
	int msValue = 0;
	int tableUsValueVariation = 25;
	cDC.SetTextAlign(TA_CENTER);
	for(int i = myScreenLeft; i < myScreenRight; i += xAxisCount, msValue += tableUsValueVariation)
	{
		cDC.MoveTo(i,myScreenBottom);
		oldPen = cDC.SelectObject(&blackSolidPen);
		cDC.LineTo(i,myScreenBottom + axisMarkDistance);
		CString usValueToString;
		usValueToString.Format(_T("%d"), msValue);
		cDC.TextOutA(i,myScreenBottom + axisMarkDistance,usValueToString,usValueToString.GetLength());
		oldPen = cDC.SelectObject(&blackDashPen);
		cDC.MoveTo(i,myScreenBottom);
		cDC.LineTo(i,leftTopBlankArea);
	}

	cDC.TextOutA(766,465,"ms",2);

	

	//파워 변화량 그리기	
	oldPen = cDC.SelectObject(&redSolidPen);
	if(currState)
	{
		float destX = myScreenLeft + (xAxisCount / 25.0 * nonflagEnd_TotalTime);
		float destVoltToGraphAxis = myScreenBottom - nonflagEnd_Destvolt * yAxisCount ;
		float currVoltToGraphAxis = myScreenBottom - nonflagEnd_Currvolt * yAxisCount;


		float fDelayTime = destX / (float)nonflagEnd_IntervalCount / xAxisCount * (float)tableUsValueVariation * 100.0f;
		if(((int)(fDelayTime * 10)) % 10 <5) // 반올림작업 왜 라이브러리에이쓴 함수를 못쓰지
		{
			nonflagEnd_DelayTime = (int)fDelayTime;
		}
		else
		{
			nonflagEnd_DelayTime = (int)fDelayTime + 1;
		}
		
			
	
		cDC.MoveTo(myScreenLeft,currVoltToGraphAxis);
		cDC.LineTo((int)destX,destVoltToGraphAxis);
	}
	else
	{
		float destX = myScreenLeft + (xAxisCount / 25.0 * nonflagStart_TotalTime);
		float destVoltToGraphAxis = myScreenBottom - nonflagStart_Destvolt * yAxisCount;
		float currVoltToGraphAxis = myScreenBottom - nonflagStart_Currvolt * yAxisCount;


		float fDelayTime = destX / (float)nonflagStart_IntervalCount / xAxisCount * (float)tableUsValueVariation * 100.0f;
		if(((int)(fDelayTime * 10)) % 10 <5) // 반올림작업 왜 라이브러리에이쓴 함수를 못쓰지
		{
			nonflagStart_DelayTime = (int)fDelayTime;
		}
		else
		{
			nonflagStart_DelayTime = (int)fDelayTime + 1;
		}




		

		cDC.MoveTo(myScreenLeft,currVoltToGraphAxis);
		cDC.LineTo((int)destX,destVoltToGraphAxis);
	}


	


	//GDI객체,DC Relese해주기 언젠간반드시해야함 메모리가 새니깐
	blackSolidPen.DeleteObject();
	whiteSolidPen.DeleteObject();
	blackDashPen.DeleteObject();
	redSolidPen.DeleteObject();
	whiteBrush.DeleteObject();

	cDC.ReleaseAttribDC();


}



void PowerControlView::OnBnClickedPcincreaseCheck()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}


BOOL PowerControlView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if(pMsg -> message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN)
		{
			return true;
		}

		else if(pMsg->wParam == VK_ESCAPE)
		{
			return  true;
		}


	}


	return CDialogEx::PreTranslateMessage(pMsg);
}






void PowerControlView::OnCbnSelchangePcCombo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	currState = ((CComboBox*)GetDlgItem(IDC_PC_COMBO))->GetCurSel();

	CString setValueString;
	if(currState) // nonFlagEnd
	{	
		isIncrease = true;
		
		setValueString.Format("%d",nonflagEnd_TotalTime); 
		SetDlgItemText(IDC_PCDELAYTIME_EDIT,setValueString);
		//setValueString.Format("%f.3f",maxVolt); // 3자리로 안잘리고 뒤에 3f가 붙는다 ㅠㅠ
		setValueString.Format("%.5f",nonflagEnd_Destvolt);
		SetDlgItemText(IDC_PCMAXVOLT_EDIT,setValueString);	
		setValueString.Format("%.5f",nonflagEnd_Currvolt);
		SetDlgItemText(IDC_PCSETVOLT_EDIT,setValueString);
	}
	else // NonfloatStart
	{
		isIncrease = false;
		setValueString.Format("%d",nonflagStart_TotalTime); 
		SetDlgItemText(IDC_PCDELAYTIME_EDIT,setValueString);
		//setValueString.Format("%f.3f",maxVolt); // 3자리로 안잘리고 뒤에 3f가 붙는다 ㅠㅠ
		setValueString.Format("%.5f",nonflagStart_Destvolt);
		SetDlgItemText(IDC_PCMAXVOLT_EDIT,setValueString);	
		setValueString.Format("%.5f",nonflagStart_Currvolt);
		SetDlgItemText(IDC_PCSETVOLT_EDIT,setValueString);
	}

	DrawGraph();


}
