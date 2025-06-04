// StaticPic.cpp : implementation file
//

#include "stdafx.h"
#include "MK.h"
#include "StaticPic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticPic
#include "DeviceDlg.h"
// eunah 2003.01.04
#include "DlgDevicePitch.h"

CStaticPic::CStaticPic()
{
	m_DrawFlag = FALSE;
}

CStaticPic::~CStaticPic()
{
}
 
BEGIN_MESSAGE_MAP(CStaticPic, CStatic)
	//{{AFX_MSG_MAP(CStaticPic)
	ON_WM_PAINT()
//	ON_WM_NCHITTEST()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticPic message handlers

void CStaticPic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CBrush tempbrush;
	tempbrush.CreateSolidBrush(RGB(255,255,255));


	// TODO: Add your message handler code here
	RECT clientrect;
	GetClientRect(&clientrect);

	dc.FillRect(&clientrect,&tempbrush);
	m_CalculateValue();
	m_DrawWnd(&dc);
	// Do not call CStatic::OnPaint() for painting messages
}

void CStaticPic::m_SetDeviePt(DeviceDlg *devicedlg)
{
	m_pDeviceDlg = devicedlg;
}

// Part 1개용
/*
void CStaticPic::m_CalculateValue()
{
	RECT clientrect;
	GetClientRect(&clientrect);

//	CDlgDevicePitch DevicePitch;

	//   2003.01.06
	float m_Xpitch_Trim;
	float m_Ypitch_Trim;
	//   2003.01.06

	//   2003.01.06
	m_Xpitch_Trim = float(atoi(m_pDeviceDlg->m_Xpitch2) - (atoi(m_pDeviceDlg->m_Xpitch) * (atoi(m_pDeviceDlg->m_SmallXNum) - 1)));
	m_Ypitch_Trim = float(atoi(m_pDeviceDlg->m_Ypitch2) - (atoi(m_pDeviceDlg->m_Ypitch) * (atoi(m_pDeviceDlg->m_SmallYNum) - 1)));
	//   2003.01.06

	if (atoi(m_pDeviceDlg->m_LeadWidth) != 0 && atoi(m_pDeviceDlg->m_LeadHeight) != 0)
	{
		if (m_pDeviceDlg->detailFlag == false) {
			// 화면상의 디바이스 크기를 구한다
			// 화면 전체 크기 * 디바이스 크기 / 리드크기
//			m_deviceX = clientrect.right * atoi(m_pDeviceDlg->m_ChipWidth) / atoi(m_pDeviceDlg->m_LeadWidth);
			m_deviceX = float(clientrect.right * atoi(m_pDeviceDlg->m_ChipWidth) / atoi(m_pDeviceDlg->m_LeadWidth));

			m_deviceY = float(clientrect.bottom* atoi(m_pDeviceDlg->m_ChipHeight)/ atoi(m_pDeviceDlg->m_LeadHeight));
			
			// 화면상에서의 피치의 크기를 구한다
			// 화면 전체 크기 * 피치크기 / 리드크기
//			m_pitchX = clientrect.right * atoi(m_pDeviceDlg->m_Xpitch) / atoi(m_pDeviceDlg->m_LeadWidth);
			m_pitchX = float(clientrect.right * atoi(m_pDeviceDlg->m_Xpitch) / atoi(m_pDeviceDlg->m_LeadWidth));

			m_pitchY = float(clientrect.bottom* atoi(m_pDeviceDlg->m_Ypitch) / atoi(m_pDeviceDlg->m_LeadHeight));
			m_Size.cx = atoi(m_pDeviceDlg->m_Xnum);
			m_Size.cy = atoi(m_pDeviceDlg->m_Ynum);
			
			// 화면 크기 - ((모든 피치의 크기 - 디바이스 크기)*(갯수-1) + 디바이스 크기 * 갯수 )
//			m_StartPoint.x = clientrect.right -  ((m_pitchX - m_deviceX)
			m_StartPoint.x = long(clientrect.right -  ((m_pitchX - m_deviceX) 
				* (m_Size.cx -1) + m_deviceX * m_Size.cx));
			m_StartPoint.x /= 2;
			m_StartPoint.y = long(clientrect.bottom - ((m_pitchY - m_deviceY)
				* (m_Size.cy -1) + m_deviceY * m_Size.cy));
			m_StartPoint.y /= 2;
		}
		//   2003.01.04
		else {
			// 화면상의 디바이스 크기를 구한다
			// 화면 전체 크기 * 디바이스 크기 / 리드크기
//			m_deviceX = clientrect.right * atoi(m_pDeviceDlg->m_ChipWidth) / atoi(m_pDeviceDlg->m_LeadWidth);
			m_deviceX = float(clientrect.right * atoi(m_pDeviceDlg->m_ChipWidth) / atoi(m_pDeviceDlg->m_LeadWidth));

			m_deviceY = float(clientrect.bottom* atoi(m_pDeviceDlg->m_ChipHeight)/ atoi(m_pDeviceDlg->m_LeadHeight));
			
			// 화면상에서의 피치의 크기를 구한다
			// 화면 전체 크기 * 피치크기 / 리드크기
			// 원본
//			m_pitchX = clientrect.right * atoi(m_pDeviceDlg->m_Xpitch) / atoi(m_pDeviceDlg->m_LeadWidth);
			m_pitchX = float(clientrect.right * atoi(m_pDeviceDlg->m_Xpitch) / atoi(m_pDeviceDlg->m_LeadWidth));
			m_pitchY = float(clientrect.bottom * atoi(m_pDeviceDlg->m_Ypitch) / atoi(m_pDeviceDlg->m_LeadHeight));
			
			//   2003.01.04
//			m_pitchX2 = clientrect.right * m_Xpitch_Trim / atoi(m_pDeviceDlg->m_LeadWidth);
			m_pitchX2 = clientrect.right * m_Xpitch_Trim / atoi(m_pDeviceDlg->m_LeadWidth);
			m_pitchY2 = clientrect.bottom * m_Ypitch_Trim / atoi(m_pDeviceDlg->m_LeadHeight);
			//   2003.01.04
			
			m_Size.cx = atoi(m_pDeviceDlg->m_Xnum);
			m_Size.cy = atoi(m_pDeviceDlg->m_Ynum);
			
			// 화면 크기 - ((모든 피치의 크기 - 디바이스 크기)*(갯수-1) + 디바이스 크기 * 갯수 )
			// eunah 2003.01.04
			//		DevicePitch.SetNumOfPitch();
//			m_StartPoint.x = clientrect.right - ( (m_pitchX - m_deviceX) * m_pDeviceDlg->NumOfXPitch1 
			m_StartPoint.x = long(clientrect.right - ( (m_pitchX - m_deviceX) * m_pDeviceDlg->NumOfXPitch1 
				+ (m_pitchX2 - m_deviceX) * m_pDeviceDlg->NumOfXPitch2 + m_deviceX * m_Size.cx ));
			m_StartPoint.x /= 2;
			
			m_StartPoint.y = long(clientrect.bottom - ( (m_pitchY - m_deviceY) * m_pDeviceDlg->NumOfYPitch1 
				+ (m_pitchY2 - m_deviceY) * m_pDeviceDlg->NumOfYPitch2 + m_deviceY * m_Size.cy ));
			m_StartPoint.y /= 2;
		}
	} 
	else
	{
		m_DrawFlag = FALSE;
		m_pDeviceDlg->m_ErrorCode = 2; // 스트립의 크기를 넓히세요!
	}
}
*/

// Part 2개 용
void CStaticPic::m_CalculateValue()
{
	RECT clientrect;
	GetClientRect(&clientrect);

//	CDlgDevicePitch DevicePitch;

	//   2003.01.06
	float m_Xpitch_Trim;
	float m_Ypitch_Trim;
	//   2003.01.06

	//   2003.01.06
	m_Xpitch_Trim = atoi(m_pDeviceDlg->m_Xpitch2) - (atoi(m_pDeviceDlg->m_Xpitch) * (atoi(m_pDeviceDlg->m_SmallXNum) - 1));
	m_Ypitch_Trim = atoi(m_pDeviceDlg->m_Ypitch2) - (atoi(m_pDeviceDlg->m_Ypitch) * (atoi(m_pDeviceDlg->m_SmallYNum) - 1));
	//   2003.01.06

	if (atoi(m_pDeviceDlg->m_LeadWidth) != 0 && atoi(m_pDeviceDlg->m_LeadHeight) != 0)
	{
		if (m_pDeviceDlg->detailFlag == false) {
			// 화면상의 디바이스 크기를 구한다
			// 화면 전체 크기 * 디바이스 크기 / 리드크기
//			m_deviceX = clientrect.right * atoi(m_pDeviceDlg->m_ChipWidth) / atoi(m_pDeviceDlg->m_LeadWidth);
			m_deviceX = clientrect.right/2 * atoi(m_pDeviceDlg->m_ChipWidth) / atoi(m_pDeviceDlg->m_LeadWidth);

			m_deviceY = clientrect.bottom* atoi(m_pDeviceDlg->m_ChipHeight)/ atoi(m_pDeviceDlg->m_LeadHeight);
			
			// 화면상에서의 피치의 크기를 구한다
			// 화면 전체 크기 * 피치크기 / 리드크기
//			m_pitchX = clientrect.right * atoi(m_pDeviceDlg->m_Xpitch) / atoi(m_pDeviceDlg->m_LeadWidth);
			m_pitchX = clientrect.right/2 * atoi(m_pDeviceDlg->m_Xpitch) / atoi(m_pDeviceDlg->m_LeadWidth);

			m_pitchY = clientrect.bottom* atoi(m_pDeviceDlg->m_Ypitch) / atoi(m_pDeviceDlg->m_LeadHeight);
			m_Size.cx = atoi(m_pDeviceDlg->m_Xnum);
			m_Size.cy = atoi(m_pDeviceDlg->m_Ynum);
			
			// 화면 크기 - ((모든 피치의 크기 - 디바이스 크기)*(갯수-1) + 디바이스 크기 * 갯수 )
//			m_StartPoint.x = clientrect.right -  ((m_pitchX - m_deviceX)
			m_StartPoint.x = clientrect.right/2 -  ((m_pitchX - m_deviceX) 
				* (m_Size.cx -1) + m_deviceX * m_Size.cx);
			m_StartPoint.x /= 2;
			m_StartPoint.y = clientrect.bottom - ((m_pitchY - m_deviceY)
				* (m_Size.cy -1) + m_deviceY * m_Size.cy);
			m_StartPoint.y /= 2;
		}
		//   2003.01.04
		else {
			// 화면상의 디바이스 크기를 구한다
			// 화면 전체 크기 * 디바이스 크기 / 리드크기
//			m_deviceX = clientrect.right * atoi(m_pDeviceDlg->m_ChipWidth) / atoi(m_pDeviceDlg->m_LeadWidth);
			m_deviceX = clientrect.right/2 * atoi(m_pDeviceDlg->m_ChipWidth) / atoi(m_pDeviceDlg->m_LeadWidth);

			m_deviceY = clientrect.bottom* atoi(m_pDeviceDlg->m_ChipHeight)/ atoi(m_pDeviceDlg->m_LeadHeight);
			
			// 화면상에서의 피치의 크기를 구한다
			// 화면 전체 크기 * 피치크기 / 리드크기
			// 원본
//			m_pitchX = clientrect.right * atoi(m_pDeviceDlg->m_Xpitch) / atoi(m_pDeviceDlg->m_LeadWidth);
			m_pitchX = clientrect.right/2 * atoi(m_pDeviceDlg->m_Xpitch) / atoi(m_pDeviceDlg->m_LeadWidth);
			m_pitchY = clientrect.bottom * atoi(m_pDeviceDlg->m_Ypitch) / atoi(m_pDeviceDlg->m_LeadHeight);
			
			//   2003.01.04
//			m_pitchX2 = clientrect.right * m_Xpitch_Trim / atoi(m_pDeviceDlg->m_LeadWidth);
			m_pitchX2 = clientrect.right/2 * m_Xpitch_Trim / atoi(m_pDeviceDlg->m_LeadWidth);
			m_pitchY2 = clientrect.bottom * m_Ypitch_Trim / atoi(m_pDeviceDlg->m_LeadHeight);
			//   2003.01.04
			
			m_Size.cx = atoi(m_pDeviceDlg->m_Xnum);
			m_Size.cy = atoi(m_pDeviceDlg->m_Ynum);
			
			// 화면 크기 - ((모든 피치의 크기 - 디바이스 크기)*(갯수-1) + 디바이스 크기 * 갯수 )
			// eunah 2003.01.04
			//		DevicePitch.SetNumOfPitch();
//			m_StartPoint.x = clientrect.right - ( (m_pitchX - m_deviceX) * m_pDeviceDlg->NumOfXPitch1 
			m_StartPoint.x = clientrect.right/2 - ( (m_pitchX - m_deviceX) * m_pDeviceDlg->NumOfXPitch1 
				+ (m_pitchX2 - m_deviceX) * m_pDeviceDlg->NumOfXPitch2 + m_deviceX * m_Size.cx );
			m_StartPoint.x /= 2;
			
			m_StartPoint.y = clientrect.bottom - ( (m_pitchY - m_deviceY) * m_pDeviceDlg->NumOfYPitch1 
				+ (m_pitchY2 - m_deviceY) * m_pDeviceDlg->NumOfYPitch2 + m_deviceY * m_Size.cy );
			m_StartPoint.y /= 2;
		}
	} 
	else
	{
		m_DrawFlag = FALSE;
		m_pDeviceDlg->m_ErrorCode = 2; // 스트립의 크기를 넓히세요!
	}
}

/* Part 1개 용
void CStaticPic::m_DrawWnd(CPaintDC *pDC)
{
	int i, ii;
	int x, y;
	int dirsize;

	RECT clientrect;
	GetClientRect(&clientrect);

	pDC->MoveTo(clientrect.right, clientrect.bottom);
	pDC->LineTo(clientrect.right, clientrect.top);
	y = m_StartPoint.y;
	if (m_DrawFlag == TRUE)
	{
		for (i=0; i < m_Size.cy; i++)
		{ // 행의 갯수 만큼 루프
			x = m_StartPoint.x;
			for(ii =0; ii < m_Size.cx; ii++)
			{	// 열의 갯수 만큼 루프 

				RectArray[i*m_Size.cx+ii].left = x;
				RectArray[i*m_Size.cx+ii].right = long(x + m_deviceX);
				RectArray[i*m_Size.cx+ii].bottom = y;
				RectArray[i*m_Size.cx+ii].top = long(y + m_deviceY);

				CBrush selBrush;
				selBrush.CreateSolidBrush(RGB(255,0,0));

				if (m_pDeviceDlg->SelectArray[i*(atoi(m_pDeviceDlg->m_Xnum))+ii] == 1) {
					pDC->FillRect(&RectArray[i*m_Size.cx+ii], &selBrush);
				}

				// 사가형 그리기
				pDC->MoveTo(x,y);
				pDC->LineTo(int(x + m_deviceX) ,y); // + m_deviceY);
				pDC->LineTo(int(x + m_deviceX) , int(y + m_deviceY));
				pDC->LineTo(x , int(y + m_deviceY));
				pDC->LineTo(x,y);


				// 노치 그리기
				// 가로세로중 작은 폭을 기준으로 한다
				if (m_deviceY < m_deviceX)
					dirsize = int(m_deviceY);
				else
					dirsize = int(m_deviceX);

				if (strcmp("Top Left", m_pDeviceDlg->m_IDpos) == 0)
					pDC->Ellipse(CRect(x + 1, y + 1, x + dirsize / 2 + 1 ,y + dirsize / 2 + 1));
				else if (strcmp("Top Right", m_pDeviceDlg->m_IDpos) == 0)
					pDC->Ellipse(CRect(int(x + m_deviceX-dirsize/2-1), int(y + 1), int(x + m_deviceX - 1), int(y + dirsize/2 + 1)));
				else if (strcmp("Bottom Left", m_pDeviceDlg->m_IDpos) == 0)
					pDC->Ellipse(CRect(int(x+1), int(y+m_deviceY-dirsize/2-1), int(x+dirsize/2+1), int(y+m_deviceY-1)));
				else
					pDC->Ellipse(CRect(int(x+m_deviceX-dirsize/2-1), int(y+m_deviceY-dirsize/2-1), int(x + m_deviceX -1), int(y+ m_deviceY -1)));

				//   2003.01.04
				if (m_pDeviceDlg->detailFlag == false)
					x += m_pitchX;
				else {
					if ((ii % atoi(m_pDeviceDlg->m_SmallXNum) < atoi(m_pDeviceDlg->m_SmallXNum) - 1) 
						|| atoi(m_pDeviceDlg->m_SmallXNum) == 1)
						x += m_pitchX;
					else
						x += m_pitchX2;
				}
				//   2003.01.04
			}
			//   2003.01.04
			if (m_pDeviceDlg->detailFlag == false)
				y += m_pitchY;
			else {
				if (i % atoi(m_pDeviceDlg->m_SmallYNum) < atoi(m_pDeviceDlg->m_SmallYNum) - 1
					|| atoi(m_pDeviceDlg->m_SmallYNum) == 1)
					y += m_pitchY;
				else
					y += m_pitchY2;
			}
			//   2003.01.04
		}
	}
	else // 에러시 종류별로 화면에 표시한다 
	{	
		RECT clientrect;
		GetClientRect(&clientrect);
		CString errormsg;

		switch(m_pDeviceDlg->m_ErrorCode)
		{
		case 1: //디바이스의 크기가 크거나 \n피치가 짧습니다
			errormsg = "The size of chip is too large or the pitch is too short!";
			break;
		case 2: //스트립의 크기를 넓히세요!
			errormsg = "Size of strip is too small!";
			break;
		case 3: // 배열의 크기를 넣으세요!
			errormsg = "Input the size of array!";
			break;
		case 4: //디바이스 길이가 0일때 
			errormsg = "Input the size of chip!";
		}
		pDC->TextOut((clientrect.right - errormsg.GetLength()*6)/2, clientrect.bottom/2 - 10, errormsg);

	}
}
*/

// Part 2개 용
void CStaticPic::m_DrawWnd(CPaintDC *pDC)
{
	int i, ii;
	int x, y;
	int dirsize;

	RECT clientrect;
	GetClientRect(&clientrect);

	pDC->MoveTo(clientrect.right/2, clientrect.bottom);
	pDC->LineTo(clientrect.right/2, clientrect.top);
	y = m_StartPoint.y;
	if (m_DrawFlag == TRUE)
	{
		for (i=0; i < m_Size.cy; i++)
		{ // 행의 갯수 만큼 루프
			x = m_StartPoint.x;
			for(ii =0; ii < m_Size.cx; ii++)
			{	// 열의 갯수 만큼 루프 

				RectArray[i*m_Size.cx+ii].left = x;
				RectArray[i*m_Size.cx+ii].right = x + m_deviceX;
				RectArray[i*m_Size.cx+ii].bottom = y;
				RectArray[i*m_Size.cx+ii].top = y + m_deviceY;

				CBrush selBrush;
				selBrush.CreateSolidBrush(RGB(255,0,0));

				if (m_pDeviceDlg->SelectArray[i*(atoi(m_pDeviceDlg->m_Xnum))+ii] == 1) {
					pDC->FillRect(&RectArray[i*m_Size.cx+ii], &selBrush);
				}

				// 사가형 그리기
				pDC->MoveTo(x,y);
				pDC->LineTo(x + m_deviceX ,y); // + m_deviceY);
				pDC->LineTo(x + m_deviceX , y + m_deviceY);
				pDC->LineTo(x , y + m_deviceY);
				pDC->LineTo(x,y);


				// 노치 그리기
				// 가로세로중 작은 폭을 기준으로 한다
				if (m_deviceY < m_deviceX)
					dirsize = m_deviceY;
				else
					dirsize = m_deviceX;

				if (strcmp("Top Left", m_pDeviceDlg->m_IDpos) == 0)
					pDC->Ellipse(CRect(x + 1, y + 1, x + dirsize / 2 + 1 ,y + dirsize / 2 + 1));
				else if (strcmp("Top Right", m_pDeviceDlg->m_IDpos) == 0)
					pDC->Ellipse(CRect(x + m_deviceX-dirsize/2-1, y + 1, x + m_deviceX - 1 ,y + dirsize/2 + 1));
				else if (strcmp("Bottom Left", m_pDeviceDlg->m_IDpos) == 0)
					pDC->Ellipse(CRect(x+1, y+m_deviceY-dirsize/2-1,x+dirsize/2+1,y+m_deviceY-1));
				else
					pDC->Ellipse(CRect(x+m_deviceX-dirsize/2-1, y+m_deviceY-dirsize/2-1, x + m_deviceX -1, y+ m_deviceY -1));

				//   2003.01.04
				if (m_pDeviceDlg->detailFlag == false)
					x += m_pitchX;
				else {
					if ((ii % atoi(m_pDeviceDlg->m_SmallXNum) < atoi(m_pDeviceDlg->m_SmallXNum) - 1) 
						|| atoi(m_pDeviceDlg->m_SmallXNum) == 1)
						x += m_pitchX;
					else
						x += m_pitchX2;
				}
				//   2003.01.04
			}
			//   2003.01.04
			if (m_pDeviceDlg->detailFlag == false)
				y += m_pitchY;
			else {
				if (i % atoi(m_pDeviceDlg->m_SmallYNum) < atoi(m_pDeviceDlg->m_SmallYNum) - 1
					|| atoi(m_pDeviceDlg->m_SmallYNum) == 1)
					y += m_pitchY;
				else
					y += m_pitchY2;
			}
			//   2003.01.04
		} 

		// Slave
		y = m_StartPoint.y;
		for (i=0; i < m_Size.cy; i++)
		{ // 행의 갯수 만큼 루프
			x = m_StartPoint.x + clientrect.right/2;
			for(ii =0; ii < m_Size.cx; ii++)
			{	// 열의 갯수 만큼 루프 

				RectArray2[i*m_Size.cx+ii].left = x;
				RectArray2[i*m_Size.cx+ii].right = x + m_deviceX;
				RectArray2[i*m_Size.cx+ii].bottom = y;
				RectArray2[i*m_Size.cx+ii].top = y + m_deviceY;

				CBrush selBrush;
				selBrush.CreateSolidBrush(RGB(255,0,0));


				if (m_pDeviceDlg->SelectArray2[i*(atoi(m_pDeviceDlg->m_Xnum))+ii] == 1) {
					pDC->FillRect(&RectArray2[i*m_Size.cx+ii], &selBrush); 
					// Shutter 동작 선택 했을 경우 자동 Vertical 마킹 2003.01.15
				}
				
				// 사가형 그리기
				pDC->MoveTo(x,y);
				pDC->LineTo(x + m_deviceX ,y); // + m_deviceY);
				pDC->LineTo(x + m_deviceX , y + m_deviceY);
				pDC->LineTo(x , y + m_deviceY);
				pDC->LineTo(x,y);


				// 노치 그리기
				// 가로세로중 작은 폭을 기준으로 한다
				if (m_deviceY < m_deviceX)
					dirsize = m_deviceY;
				else
					dirsize = m_deviceX;

				if (strcmp("Top Left", m_pDeviceDlg->m_IDpos) == 0)
					pDC->Ellipse(CRect(x + 1, y + 1, x + dirsize / 2 + 1 ,y + dirsize / 2 + 1));
				else if (strcmp("Top Right", m_pDeviceDlg->m_IDpos) == 0)
					pDC->Ellipse(CRect(x + m_deviceX-dirsize/2-1, y + 1, x + m_deviceX - 1 ,y + dirsize/2 + 1));
				else if (strcmp("Bottom Left", m_pDeviceDlg->m_IDpos) == 0)
					pDC->Ellipse(CRect(x+1, y+m_deviceY-dirsize/2-1,x+dirsize/2+1,y+m_deviceY-1));
				else
					pDC->Ellipse(CRect(x+m_deviceX-dirsize/2-1, y+m_deviceY-dirsize/2-1, x + m_deviceX -1, y+ m_deviceY -1));

				//   2003.01.04
				if (m_pDeviceDlg->detailFlag == false)
					x += m_pitchX;
				else {
					if ((ii % atoi(m_pDeviceDlg->m_SmallXNum) < atoi(m_pDeviceDlg->m_SmallXNum) - 1) 
						|| atoi(m_pDeviceDlg->m_SmallXNum) == 1)
						x += m_pitchX;
					else
						x += m_pitchX2;
				}
				//   2003.01.04
			}
			//   2003.01.04
			if (m_pDeviceDlg->detailFlag == false)
				y += m_pitchY;
			else {
				if (i % atoi(m_pDeviceDlg->m_SmallYNum) < atoi(m_pDeviceDlg->m_SmallYNum) - 1
					|| atoi(m_pDeviceDlg->m_SmallYNum) == 1)
					y += m_pitchY;
				else
					y += m_pitchY2;
			}
			//   2003.01.04
		} 
	}
	else // 에러시 종류별로 화면에 표시한다 
	{	
		RECT clientrect;
		GetClientRect(&clientrect);
		CString errormsg;

		switch(m_pDeviceDlg->m_ErrorCode)
		{
		case 1: //디바이스의 크기가 크거나 \n피치가 짧습니다
			errormsg = "The size of chip is too large or the pitch is too short!";
			break;
		case 2: //스트립의 크기를 넓히세요!
			errormsg = "Size of strip is too small!";
			break;
		case 3: // 배열의 크기를 넣으세요!
			errormsg = "Input the size of array!";
			break;
		case 4: //디바이스 길이가 0일때 
			errormsg = "Input the size of chip!";
		}
		pDC->TextOut((clientrect.right - errormsg.GetLength()*6)/2, clientrect.bottom/2 - 10, errormsg);

	}
}


/*UINT CStaticPic::OnNcHitTest(CPoint point) 
{
	if (prepoint == point) {
		// 포인터가 칩내부에 있다면 
		CPoint logicalPoint = point;
		CPaintDC dc(this);
		
		// 맵핑 모드를 바꾼다
		RECT clientrect;
		GetClientRect(&clientrect);
		dc.SetMapMode(MM_ISOTROPIC);
		dc.SetWindowExt( atof(m_pDeviceDlg->m_LeadWidth), -atof(m_pDeviceDlg->m_LeadHeight));
		dc.SetViewportExt(int(clientrect.right * 0.9), int(clientrect.bottom * 0.9)); // m_stripWidth, m_stripHeight);
		dc.SetViewportOrg(int(clientrect.right/2), int(clientrect.bottom/2));
		
		dc.DPtoLP(&logicalPoint);
		
		CRect rect;
		CRect rect2;

		CPoint tempPoint;
		CPoint topLeft;
		CPoint BottomRight;

		CDC *cdc = GetDC();

		CBrush selBrush;

		// Master
		for(int i=0; i < atoi(m_pDeviceDlg->m_Ynum); i++)
		{
			for(int j=0; j < atoi(m_pDeviceDlg->m_Xnum); j++)
			{
				rect = RectArray[i*(atoi(m_pDeviceDlg->m_Xnum))+j];
				m_pDeviceDlg->GetDlgItem(IDC_PREPIC)->GetWindowRect(rect2);
				tempPoint.x = point.x - rect2.left;
				tempPoint.y = point.y - rect2.top;

//				if(RectArray[i*(atoi(m_pDeviceDlg->m_Xnum))+j].PtInRect(tempPoint) == true) {
				if (rect.left <= tempPoint.x && tempPoint.x <= rect.right) {
					if (rect.bottom <= tempPoint.y && tempPoint.y <= rect.top) {
						m_pDeviceDlg->SelectArray[i*(atoi(m_pDeviceDlg->m_Xnum))+j] =
						    !(m_pDeviceDlg->SelectArray[i*(atoi(m_pDeviceDlg->m_Xnum))+j]);
					}			
				}
			}
		}

		// Slave
		for(i=0; i < atoi(m_pDeviceDlg->m_Ynum); i++)
		{
			for(int j=0; j < atoi(m_pDeviceDlg->m_Xnum); j++)
			{
				rect = RectArray2[i*(atoi(m_pDeviceDlg->m_Xnum))+j];
				m_pDeviceDlg->GetDlgItem(IDC_PREPIC)->GetWindowRect(rect2);
				tempPoint.x = point.x - rect2.left;
				tempPoint.y = point.y - rect2.top;

//				if(RectArray[i*(atoi(m_pDeviceDlg->m_Xnum))+j].PtInRect(tempPoint) == true) {
				if (rect.left <= tempPoint.x && tempPoint.x <= rect.right) {
					if (rect.bottom <= tempPoint.y && tempPoint.y <= rect.top) {
						m_pDeviceDlg->SelectArray2[i*(atoi(m_pDeviceDlg->m_Xnum))+j] =
						    !(m_pDeviceDlg->SelectArray2[i*(atoi(m_pDeviceDlg->m_Xnum))+j]);
					}			
				}
			}
		}
		Invalidate();
	}

	prepoint = point;

	return CStatic::OnNcHitTest(point);
}*/

/* Part1 용
void CStaticPic::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// 포인터가 칩내부에 있다면 
	CPoint logicalPoint = point;
	CPaintDC dc(this);
	
	// 맵핑 모드를 바꾼다
	RECT clientrect;
	GetClientRect(&clientrect);
	dc.SetMapMode(MM_ISOTROPIC);
	dc.SetWindowExt(int(atof(m_pDeviceDlg->m_LeadWidth)), int(-atof(m_pDeviceDlg->m_LeadHeight)));
	dc.SetViewportExt(int(clientrect.right * 0.9), int(clientrect.bottom * 0.9)); // m_stripWidth, m_stripHeight);
	dc.SetViewportOrg(int(clientrect.right/2), int(clientrect.bottom/2));
	
	dc.DPtoLP(&logicalPoint);
	
	CRect rect;
		
	CDC *cdc = GetDC();
	
	CBrush selBrush;
	
	// Master
	for(int i=0; i < atoi(m_pDeviceDlg->m_Ynum); i++)
	{
		for(int j=0; j < atoi(m_pDeviceDlg->m_Xnum); j++)
		{
			rect = RectArray[i*(atoi(m_pDeviceDlg->m_Xnum))+j];
			
			if (rect.left <= point.x && point.x <= rect.right) {
				if (rect.bottom <= point.y && point.y <= rect.top) {
					m_pDeviceDlg->SelectArray[i*(atoi(m_pDeviceDlg->m_Xnum))+j] =
						!(m_pDeviceDlg->SelectArray[i*(atoi(m_pDeviceDlg->m_Xnum))+j]);
				}			
			}
		}
	}
	Invalidate();
	
	CStatic::OnLButtonUp(nFlags, point);
}
*/

// Part2용
void CStaticPic::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// 포인터가 칩내부에 있다면 
	CPoint logicalPoint = point;
	CPaintDC dc(this);
	
	// 맵핑 모드를 바꾼다
	RECT clientrect;
	GetClientRect(&clientrect);
	dc.SetMapMode(MM_ISOTROPIC);
	dc.SetWindowExt( atof(m_pDeviceDlg->m_LeadWidth), -atof(m_pDeviceDlg->m_LeadHeight));
	dc.SetViewportExt(int(clientrect.right * 0.9), int(clientrect.bottom * 0.9)); // m_stripWidth, m_stripHeight);
	dc.SetViewportOrg(int(clientrect.right/2), int(clientrect.bottom/2));
	
	dc.DPtoLP(&logicalPoint);
	
	CRect rect;
		
	CDC *cdc = GetDC();
	
	CBrush selBrush;
	
	// Master
	for(int i=0; i < atoi(m_pDeviceDlg->m_Ynum); i++)
	{
		for(int j=0; j < atoi(m_pDeviceDlg->m_Xnum); j++)
		{
			rect = RectArray[i*(atoi(m_pDeviceDlg->m_Xnum))+j];
			
			if (rect.left <= point.x && point.x <= rect.right) {
				if (rect.bottom <= point.y && point.y <= rect.top) {
					m_pDeviceDlg->SelectArray[i*(atoi(m_pDeviceDlg->m_Xnum))+j] =
						!(m_pDeviceDlg->SelectArray[i*(atoi(m_pDeviceDlg->m_Xnum))+j]);
				}			
			}
		}
	}
	
	// Slave
	for(i=0; i < atoi(m_pDeviceDlg->m_Ynum); i++)
	{
		for(int j=0; j < atoi(m_pDeviceDlg->m_Xnum); j++)
		{
			rect = RectArray2[i*(atoi(m_pDeviceDlg->m_Xnum))+j];
			
			//				if(RectArray[i*(atoi(m_pDeviceDlg->m_Xnum))+j].PtInRect(tempPoint) == true) {
			if (rect.left <= point.x && point.x <= rect.right) {
				if (rect.bottom <= point.y && point.y <= rect.top) {
					m_pDeviceDlg->SelectArray2[i*(atoi(m_pDeviceDlg->m_Xnum))+j] =
						!(m_pDeviceDlg->SelectArray2[i*(atoi(m_pDeviceDlg->m_Xnum))+j]);
				}			
			}
		}
	}
	Invalidate();
	
	CStatic::OnLButtonUp(nFlags, point);
}

