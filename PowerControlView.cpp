// PowerControlView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "PowerControlView.h"
#include "afxdialogex.h"
#include "Parameter.h"



// PowerControlView ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(PowerControlView, CDialogEx)

PowerControlView::PowerControlView(CWnd* pParent /*=NULL*/)
	: CDialogEx(PowerControlView::IDD, pParent)
{
	
	nonflagStart_IntervalCount = 280;                 // �ݺ�Ƚ�� �����ϸ� �������� ������
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


// PowerControlView �޽��� ó�����Դϴ�.


//void PowerControlView::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//	@TG
//#3073
//		// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
//		// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
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
	//setValueString.Format("%f.3f",maxVolt); // 3�ڸ��� ���߸��� �ڿ� 3f�� �ٴ´� �Ф�
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CClientDC cDC(this);

	CString pointString;
	pointString.Format("X = %d, Y = %d",point.x,point.y);

	cDC.TextOutA(600,100,pointString);


	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void PowerControlView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.


	CDialogEx::OnLButtonDown(nFlags, point);
}

void PowerControlView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}


void PowerControlView::OnBnClickedPowerctrlApply()
{
	





	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	//���⼭ �Ķ���Ͱ� �����ϴ� ��ü�� �����Ͽ� ���� �������� �־��ָ� �ȴ�.

	CDialogEx::OnOK();
}



void PowerControlView::OnEnChangePcmaxvoltEdit()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void PowerControlView::DrawGraph()
{
	Invalidate(true);

	//���� Ŭ���̾�Ʈ�� DC�� ���ɴϴ�.
	CClientDC cDC(this);
	cDC.SetBkMode(TRANSPARENT);
	

	//SetWindowPos(NULL,0,0,985,562,0); //������ ����� ������ �����մϴ�.

	
	//���� Ŭ���̾�Ʈ�� ������ ����� �����ɴϴ�.
	RECT currWindowRect;
	GetClientRect(&currWindowRect);

	//GDI��ü�� ���� �� �ʱ�ȭ�մϴ�.
	CPen blackSolidPen,whiteSolidPen,blackDashPen,redSolidPen,*oldPen;
	blackSolidPen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	blackDashPen.CreatePen(PS_DOT,1,RGB(0,0,0));
	whiteSolidPen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	redSolidPen.CreatePen(PS_SOLID,2,RGB(255,0,0));
	CBrush whiteBrush(RGB(255,255,255)), *oldBursh;	
	


	// ǥ�� �׸��� ���� ������
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
	
	//��� �׸���
	oldBursh = cDC.SelectObject(&whiteBrush);
	cDC.Rectangle(myScreenLeft,myScreenTop ,myScreenRight,myScreenBottom);
	

	//������ �׸���
	int voltValue = 10;
	int tableVoltVariation = 1;
	cDC.SetTextAlign(TA_RIGHT);
	for(int i=myScreenTop ;i <= myScreenBottom; i += yAxisCount, voltValue -= tableVoltVariation)
	{
		cDC.MoveTo(myScreenLeft,i);
		oldPen = cDC.SelectObject(&blackSolidPen);
		cDC.LineTo(myScreenLeft - axisMarkDistance + 3,i); // �����ڸ��� ��Ĩ�ϴ� 
		CString voltValueToString;
		voltValueToString.Format(_T("%dV"), voltValue);
		cDC.TextOutA(myScreenLeft - axisMarkDistance - 5,i - 5,voltValueToString,voltValueToString.GetLength());
		oldPen = cDC.SelectObject(&blackDashPen);
		cDC.MoveTo(myScreenLeft,i);
		cDC.LineTo(myScreenRight,i);	
	}

	//������ �׸���
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

	

	//�Ŀ� ��ȭ�� �׸���	
	oldPen = cDC.SelectObject(&redSolidPen);
	if(currState)
	{
		float destX = myScreenLeft + (xAxisCount / 25.0 * nonflagEnd_TotalTime);
		float destVoltToGraphAxis = myScreenBottom - nonflagEnd_Destvolt * yAxisCount ;
		float currVoltToGraphAxis = myScreenBottom - nonflagEnd_Currvolt * yAxisCount;


		float fDelayTime = destX / (float)nonflagEnd_IntervalCount / xAxisCount * (float)tableUsValueVariation * 100.0f;
		if(((int)(fDelayTime * 10)) % 10 <5) // �ݿø��۾� �� ���̺귯�����̾� �Լ��� ������
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
		if(((int)(fDelayTime * 10)) % 10 <5) // �ݿø��۾� �� ���̺귯�����̾� �Լ��� ������
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


	


	//GDI��ü,DC Relese���ֱ� �������ݵ���ؾ��� �޸𸮰� ���ϱ�
	blackSolidPen.DeleteObject();
	whiteSolidPen.DeleteObject();
	blackDashPen.DeleteObject();
	redSolidPen.DeleteObject();
	whiteBrush.DeleteObject();

	cDC.ReleaseAttribDC();


}



void PowerControlView::OnBnClickedPcincreaseCheck()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

}


BOOL PowerControlView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	currState = ((CComboBox*)GetDlgItem(IDC_PC_COMBO))->GetCurSel();

	CString setValueString;
	if(currState) // nonFlagEnd
	{	
		isIncrease = true;
		
		setValueString.Format("%d",nonflagEnd_TotalTime); 
		SetDlgItemText(IDC_PCDELAYTIME_EDIT,setValueString);
		//setValueString.Format("%f.3f",maxVolt); // 3�ڸ��� ���߸��� �ڿ� 3f�� �ٴ´� �Ф�
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
		//setValueString.Format("%f.3f",maxVolt); // 3�ڸ��� ���߸��� �ڿ� 3f�� �ٴ´� �Ф�
		setValueString.Format("%.5f",nonflagStart_Destvolt);
		SetDlgItemText(IDC_PCMAXVOLT_EDIT,setValueString);	
		setValueString.Format("%.5f",nonflagStart_Currvolt);
		SetDlgItemText(IDC_PCSETVOLT_EDIT,setValueString);
	}

	DrawGraph();


}
