// MarkImage.cpp : implementation file
//

#include "stdafx.h"
#include "MK.h"
#include "MarkImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
 
/////////////////////////////////////////////////////////////////////////////
// CMarkImage

CMarkImage::CMarkImage()
{
	// 2003.06.03 �ùķ��̼� ���
	isSimulation = FALSE;
	SimulationSpeed = 1;
	PenSize = 1;

}

CMarkImage::~CMarkImage()
{
}


BEGIN_MESSAGE_MAP(CMarkImage, CStatic)
	//{{AFX_MSG_MAP(CMarkImage)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMarkImage message handlers

void CMarkImage::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect temprect;
	GetClientRect(&temprect);

	CRgn rgn;
	rgn.CreateRectRgn(temprect.left, temprect.top, temprect.right, temprect.bottom);
	dc.SelectClipRgn(&rgn);

	CBrush tempbrush;
	tempbrush.CreateSolidBrush(RGB(255,255,255));
	RECT clientrect;
	GetClientRect(&clientrect);
	dc.FillRect(&clientrect,&tempbrush);
	
//	CPoint center;
//  center.x = (::GetSystemMetrics(SM_CXFULLSCREEN) - 325); 
//  center.y = (::GetSystemMetrics(SM_CYFULLSCREEN) - 142 - 16); 

	// ���� ��带 �ٲ۴�
	dc.SetMapMode(MM_ANISOTROPIC);
	dc.SetWindowExt(m_pDoc->GetScreenSize().cx , m_pDoc->GetScreenSize().cy);  // �̷������� ���� ũ��
	dc.SetViewportExt(clientrect.right, clientrect.bottom); // ȭ���� �ִ� ����̽� ��ǥ
	dc.SetViewportOrg(clientrect.right/2, clientrect.bottom/2);	// ������ ��ǥ�� �̵��Ѵ�

/*	int i;
	for(i=0;i<MAXOBJ;i++)
	{
		if (m_pDoc->MKOBJ[i].type == EMPTY || m_pDoc->MKOBJ[i].mark == FALSE )
			continue;
		DrawObj(&(m_pDoc->MKOBJ[i]), &dc);
	}*/
	// �߽� ���� �ߴ´�
	dc.MoveTo(-m_pDoc->GetScreenSize().cy/2,0);
	dc.LineTo( m_pDoc->GetScreenSize().cy/2,0);
	dc.MoveTo(0,-m_pDoc->GetScreenSize().cx/2);
	dc.LineTo(0, m_pDoc->GetScreenSize().cx/2);

	// 2003.06.03 �ùķ��̼� ��� start
	// ���� �״�� �������� �ε�
	if (isSimulation == false) {
		
		int i;
		for(i=0;i<MAXOBJ;i++)
		{
			if (m_pDoc->MKOBJ[i].type == EMPTY || m_pDoc->MKOBJ[i].mark == FALSE )
				continue;
			
			//   2003.01.28 simulation�� ���� �߰�
			DrawObj(&(m_pDoc->MKOBJ[i]), &dc);
			
		}
	}

	// 2003.06.03   �߰� Simulation ���ý��� �ൿ
	else {
		POSITION pos;
		defobj *obj;
		
		pos = m_pDoc->m_MarkOrder.m_markOrder.GetHeadPosition();
		while(pos)
		{
			obj = m_pDoc->m_MarkOrder.m_markOrder.GetNext(pos);
			
			if (obj->type == EMPTY || obj->mark == FALSE )
				continue;
			
			SimulationDraw(obj, &dc);
		}
		isSimulation = false;
	}
	// 2003.06.03 �ùķ��̼� ��� end

	// ���� �̿��� ������ �����
//	dc.SetViewportOrg(0,0);	// ������ ��ǥ�� �̵��Ѵ�
//	RECT rect;
//	CBrush brush(GetSysColor(COLOR_BTNFACE));
//	rect.top = -50; rect.left = -34; rect.bottom = 620; rect.right =-16; // ����
//	dc.FillRect(&rect, &brush);
//	rect.top = -50; rect.left = -16; rect.bottom = -17; rect.right =950; // ����
//	dc.FillRect(&rect, &brush);
//	rect.top = -50; rect.left = m_pDoc->GetScreenSize().cy+16; rect.bottom = 620; rect.right = 950; // ������
//	dc.FillRect(&rect, &brush);

//	rect.top = m_pDoc->GetScreenSize().cy+17; rect.left = -16; rect.bottom = 620; rect.right = 950; // �Ʒ��� 
//	dc.FillRect(&rect, &brush);
	
//	MarkDlg *ttt;
//	ttt = (MarkDlg*)GetParent();
//	ttt->SetBkGround(ttt);
	// Do not call CStatic::OnPaint() for painting messages
}

void CMarkImage::SetViewPoint(CMKView *pView, CMKDoc *pDoc)
{
	m_pView = pView;
	m_pDoc  = pDoc ;
}
#include <math.h>
void CMarkImage::DrawObj(defobj *obj, CDC *pDC)
{ 
	CString str;
	unsigned long i;
	CPoint pos,prepos;
	float xratio, yratio;
	float px, py;
//	float x, y;

//	float ppx, ppy;
	double PI = 3.1415926535;


	// �� �����
	CPen* pPenOld = NULL;
	CPen penNew1, penNew2, penNew3, penNew4, penNew5;
	penNew1.CreatePen(PS_SOLID, 1, RGB(0,0,255));
	penNew2.CreatePen(PS_SOLID, 1, RGB(255,0,0));
	penNew3.CreatePen(PS_SOLID, 1, RGB(0,255,0));
	penNew4.CreatePen(PS_SOLID, 1, RGB(0,0,0));
	penNew5.CreatePen(PS_SOLID, 1, RGB(100,100,100));
	pPenOld = pDC->SelectObject(&penNew1);

	COLORREF col=RGB(0,0,200);

	xratio =  float(0.1); //ScreenZoom;
	yratio = float(-0.1); //-ScreenZoom;

	px =0; py =0;
	int maxx = 0 , maxy = 0 , minx = 9999, miny= 9999;

	RECT temprect;
	GetClientRect(&temprect);

	pDC->SetBkMode(TRANSPARENT);

	pDC->DPtoLP(&temprect);
	CPoint ScreenOffset = CPoint(temprect.right/2, temprect.bottom/2);

	int statex = 0;//, xx; // 0: ���� ���� 1: ��� ���ʿ� �ִ� ���� 2: ����� �۱��ʿ� �ִ� ����
	int statey = 0;//, yy;
//	int limitx, limity;

//	double dtheta, tmptheta, r, deltax, deltay;

	switch(obj->type)
	{
	case STEXT:
	// 2003.10.22 TTF ���� �߰�
	case TTF:
	case HPGL :
	case BARCODE:
		px = obj->X;	// �߾� + ��ü�� ��ġ + ȭ����� �� ��ġ
		py = obj->Y;	//+obj->Height*obj->Ymag*yratio); 

		pos = CPoint(int(px),int(py));
		pDC->MoveTo(pos);

////// For Rotation /////////////////////////
//		if(obj->RadialFlag)
//		{	//� ����� ���
//			tmptheta = (90.) ;
//			r =  obj->Radius; // ������
//			dtheta = obj->chrWidth / r;
//		
//			deltax = obj->Radius*cos(tmptheta / 180 * PI);
//			deltay = obj->Radius*sin(tmptheta / 180 * PI);
//		} else 
//		{
//		
//		}
//		ppx = px ; ppy = py ;
/////////////////////////////////////////////
		pDC->LineTo(pos);
		for(i=0; i < obj->nhpd; i++) 
		{
			pDC->SetBkMode(TRANSPARENT);

			// ȭ�� ���� ��ǥ�� �׸���
			// 2003.07.08 Detail Rotation ���� ���� start
			if (obj->Angle == 0 ||obj->Angle == 180|| obj->type == BARCODE) {
				px += obj->hpgl_data[i].d.x * xratio * obj->Xmag ;
				py += obj->hpgl_data[i].d.y * yratio * obj->Ymag ;
			}
			else {
				px += obj->hpgl_data[i].d.x * xratio * obj->Xmag ;
				py += obj->hpgl_data[i].d.y * yratio  * obj->Ymag ;
			}
			// 2003.07.08 Detail Rotation ���� ���� end

			pos = CPoint(int(px),int(py));

			if (obj->mark == TRUE)
			{	// ���׸������� ���� �����Ѵ�
				switch(obj->hpgl_data[i].t) 
				{
				case 03 : // ���
					pDC->SelectObject(&penNew1);
					break;
				case 04 : // ���������� �׸��� ������
					pDC->SelectObject(&penNew2);
					break;
				case 10 : // �׸� 
					pDC->SelectObject(&penNew3);
					break;
				case 18 : // ����
					pDC->SelectObject(&penNew4);
					break;
				default : // 
					pDC->SelectObject(&penNew2);
				}
			} else
			{
				pDC->SelectObject(&penNew5);
			}
			switch(obj->hpgl_data[i].t) 
			{
			case 03 : // 03 : character
				if(obj->RadialFlag) 
				{
				}
			case 18 :
			case 10 :
			case 02 : // 02 : MoveTo
				pDC->MoveTo(pos);
				break;
			default :  // 04 : LineTo
				pDC->LineTo(pos);
				break;
			}
		}

		////////////////////////////////////////////////////////////
		// ���ܸ� ����ؼ� �׸���
/*		px = float(obj->X);//m_pView->ScreenOffset.x + obj->X);	// �߾� + ��ü�� ��ġ 
		py = float(obj->Y);//m_pView->ScreenOffset.y + obj->Y);	//+obj->Height*obj->Ymag*yratio); 

		pos = CPoint(px, py);
		prepos = pos;
		pDC->MoveTo(pos);
		ppx = px ; ppy = py ;			// ������ġ�� �����Ѵ�
		pDC->LineTo(pos);

		for(i = 0; i < obj->nhpd; i++)
		{
			limitx = temprect.right , limity = temprect.right;

			px += obj->hpgl_data[i].d.x * xratio* obj->Xmag;
			py += obj->hpgl_data[i].d.y * yratio* obj->Ymag;

			if ( prepos.x <= temprect.left)
				limitx = temprect.left;
			else if ( prepos.x >= temprect.right)
				limitx = temprect.right;
			else if ( px <= temprect.left)
				limitx = temprect.left;
			else if ( px >= temprect.right)
				limitx = temprect.right;

			switch(statex)
			{
			case 0: // ó�� ���� �����̴�
				if (prepos.x < temprect.right &&  prepos.x > temprect.left)
				{	//  ���� ���� �������� �ִٸ�					
					if (px < temprect.right && px > temprect.left)
					{	// ����� ���ʿ� �ִ� ���� // �״�� �׸���
						x = px; y = py;
						statex = 1;
					} else
					{	// ����� �ٱ��ʿ� �ִ� ���� // ������ ��� ���� �׸���
						x = limitx;
						y = prepos.y + ((limitx - prepos.x) * obj->hpgl_data[i].d.y * yratio * obj->Ymag)
								/ (obj->hpgl_data[i].d.x * xratio * obj->Xmag);

						statex = 2;
					}
				} else
				{	// �������� ������ �ٱ��� �ִٸ�
					if (px < temprect.right && px > temprect.left)
					{	// ����� �������� ���ϴ� ���� // ������� �������� �׸���
						x = limitx;
						y = prepos.y + ((limitx - prepos.x) * obj->hpgl_data[i].d.y * yratio * obj->Ymag)
								/ (obj->hpgl_data[i].d.x * xratio * obj->Xmag);

						prepos.x = x;
						prepos.y = y;

						pDC->MoveTo(x, y);
						x = px; y = py;
						statex = 1;
					} else
					{	// ����� �ٱ������� ���ϴ� ���� // �׸��� �ʴ´�
						x = prepos.x;
						y = prepos.y;
						statex = 2;
					}					
				}
				break;
			case 1: // ���� ����� �ȿ� �ִ� ����
				if (px < temprect.right && px > temprect.left)
				{	// ����� ���ʿ� �ִ� ���� // �״�� �׸���
					x = px; y = py;
					statex = 1;
				} else
				{	// ����� �ٱ��ʿ� �ִ� ���� // ������ ��� ���� �׸���
					x = limitx;
					y = prepos.y + ((limitx - prepos.x) * obj->hpgl_data[i].d.y * yratio * obj->Ymag)
							/ (obj->hpgl_data[i].d.x * xratio * obj->Xmag);
					statex = 2;
				}
				break;
			case 2: // ���� ��踦 ���� �� ����
				if (px < temprect.right && px > temprect.left)
				{	// ����� ���ʿ� ���� ���� ���� // ������� �������� �׸���
					x = limitx;
					y = prepos.y + ((limitx - prepos.x) * obj->hpgl_data[i].d.y * yratio * obj->Ymag)
							/ (obj->hpgl_data[i].d.x * xratio * obj->Xmag);

					prepos.x = x;
					prepos.y = y;

					pDC->MoveTo(x, y);
					x = px; y = py;
					statex = 1;
				} else
				{	// ����� �ٱ������� ���� ���� // �ƹ��͵� �ȱ׸���
					x = prepos.x;
					y = prepos.y;
					statex = 2;
				}
				break;
			}

			if ( prepos.y <= temprect.left)
				limity = temprect.left;
			else if ( prepos.y >= temprect.right)
				limity = temprect.right;
			else if ( y <= temprect.left)
				limity = temprect.left;
			else if ( y >= temprect.right)
				limity = temprect.right;

			if (prepos.y < temprect.right &&  prepos.y > temprect.left)
				statey = 1;
			else 
				statey = 2;
			switch(statey)
			{
			case 1: // ���� ����� �ȿ� �ִ� ����
				if (y < temprect.right && y > temprect.left)
				{	// ����� ���ʿ� �ִ� ���� // �״�� �׸���
					statey = 1;
				} else
				{	// ����� �ٱ��ʿ� �ִ� ���� // ������ ��� ���� �׸���
					y = limity;
					x = prepos.x + ((limity - prepos.y) * obj->hpgl_data[i].d.x * xratio * obj->Xmag)
							/ (obj->hpgl_data[i].d.y * yratio * obj->Ymag);
					statey = 2;
				}
				break;
			case 2: // ���� ��踦 ���� �� ����
				if (y < temprect.right && y > temprect.left)
				{	// ����� ���ʿ� ���� ���� ���� // ������� �������� �׸���
					xx = x;
					yy = y;

					y = limity;
					x = prepos.x + ((limity - prepos.y) * obj->hpgl_data[i].d.x * xratio * obj->Xmag)
							/ (obj->hpgl_data[i].d.y * yratio * obj->Ymag);
					pDC->MoveTo(x, y);
					x = xx; 
					y = yy;

					statey = 1;
				} else
				{	// ����� �ٱ������� ���� ���� // �ƹ��͵� �ȱ׸���
					x = prepos.x;
					y = prepos.y;
					statey = 2;
				}
				break;
			}

			pos = CPoint(int(x),int(y));

			switch(obj->hpgl_data[i].t) 
			{ // ���� ���� ���� �����Ͽ� �׸���
			case 03 : 
				pDC->SelectObject(&penNew1);
				break;
			case 04 :
				pDC->SelectObject(&penNew2);
				break;
			case 10 :
				pDC->SelectObject(&penNew3);
				break;
			case 18 :
				pDC->SelectObject(&penNew4);
				break;
			default :
				pDC->SelectObject(&penNew2);
			}

			switch(obj->hpgl_data[i].t) 
			{
			case 03 : // 03 : character
			case 18 :
			case 10 :
			case 02 : // 02 : MoveTo
				pDC->LineTo(pos);
				pDC->MoveTo(px, py);
				break;
			default :  // 04 : LineTo
				pDC->LineTo(pos);
			}
			pDC->MoveTo(px, py);
			prepos = CPoint(int(px), int(py));;
		}
*/
		break;
	case BMP :
		i=0;
		break;
	case BARCODE2D:
	case BITIMG:
		if ( !obj->m_Img.IsDataNull() )
		{
			px = obj->X;
			py = obj->Y;

			pos = CPoint(int(px),int(py));

			if ( !obj->m_Img.IsDataNull() )
			{
				CRect rcDIB;
				rcDIB.left   = 0;
				rcDIB.top    = 0;
				rcDIB.right  = obj->m_Img.GetWidth();
				rcDIB.bottom = obj->m_Img.GetHeight();
				CRect rcDest;

				rcDest = rcDIB;
				rcDest.left  = long(px + rcDest.left  * xratio * obj->Xmag);
				rcDest.top   = long(py + rcDIB.bottom * yratio * obj->Ymag);
				rcDest.right = long(px + rcDest.right * xratio * obj->Xmag);
				rcDest.bottom= long(py - rcDIB.top    * yratio * obj->Ymag);

				obj->m_Img.Draw(pDC->m_hDC,&rcDIB,&rcDest, SRCCOPY);
			}

		}
	default :
		i=0;
		break;
	}

	if (pPenOld != NULL)
		pDC->SelectObject(pPenOld);	
}

// 2003.06.03 Simulation Draw start
void CMarkImage::SimulationDraw(defobj *obj, CDC *pDC)
{ 
	CString str;
	unsigned long i;
	CPoint pos,prepos;
	float xratio, yratio;
	float px, py;
//	float x, y;

//	float ppx, ppy;
	double PI = 3.1415926535;


	// �� �����
	CPen* pPenOld = NULL;
	CPen penNew1, penNew2, penNew3, penNew4, penNew5, penNew_up;
	penNew1.CreatePen(PS_SOLID, PenSize, RGB(0,0,255));
	penNew2.CreatePen(PS_SOLID, PenSize, RGB(255,0,0));
	penNew3.CreatePen(PS_SOLID, PenSize, RGB(0,255,0));
	penNew4.CreatePen(PS_SOLID, PenSize, RGB(0,0,0));
	penNew5.CreatePen(PS_SOLID, PenSize, RGB(100,100,100));
	penNew_up.CreatePen(PS_DOT, PenSize, RGB(255,0,0));
	pPenOld = pDC->SelectObject(&penNew1);

	COLORREF col=RGB(0,0,200);

	xratio =  float(0.1); //ScreenZoom;
	yratio = float(-0.1); //-ScreenZoom;

	px =0; py =0;
	int maxx = 0 , maxy = 0 , minx = 9999, miny= 9999;

	RECT temprect;
	GetClientRect(&temprect);

	pDC->SetBkMode(TRANSPARENT);

	pDC->DPtoLP(&temprect);
	CPoint ScreenOffset = CPoint(temprect.right/2, temprect.bottom/2);

	int statex = 0;//, xx; // 0: ���� ���� 1: ��� ���ʿ� �ִ� ���� 2: ����� �۱��ʿ� �ִ� ����
	int statey = 0;//, yy;
//	int limitx, limity;

//	double dtheta, tmptheta, r, deltax, deltay;

	switch(obj->type)
	{
	case STEXT:
	// 2003.10.22 TTF ���� �߰�
	case TTF:
	case HPGL :
	case BARCODE:
		px = obj->X;	// �߾� + ��ü�� ��ġ + ȭ����� �� ��ġ
		py = obj->Y;	//+obj->Height*obj->Ymag*yratio); 

		pos = CPoint(int(px),int(py));
		// 2003.07.09 Pen Up Line�� �׸��� start
//		pDC->SelectObject(&penNew_up);
//		pDC->LineTo(pos);
//		pDC->MoveTo(pos); ����
		// 2003.07.09 Pen Up Line�� �׸��� end

		for(i=0; i < obj->nhpd; i++) 
		{
			pDC->SetBkMode(TRANSPARENT);

			// ȭ�� ���� ��ǥ�� �׸���
			// 2003.07.08 Detail Rotation ���� ���� start
			if (obj->Angle == 0 || obj->type == BARCODE) {
				px += obj->hpgl_data[i].d.x * xratio * obj->Xmag ;
				py += obj->hpgl_data[i].d.y * yratio * obj->Ymag ;
			}
			else {
				px += obj->hpgl_data[i].d.x * xratio* obj->Xmag ;
				py += obj->hpgl_data[i].d.y * yratio* obj->Ymag;
			}
			// 2003.07.08 Detail Rotation ���� ���� end

			pos = CPoint(int(px),int(py));

			if (obj->mark == TRUE)
			{	// ���׸������� ���� �����Ѵ�
				switch(obj->hpgl_data[i].t) 
				{
				case 03 : // ���
					pDC->SelectObject(&penNew1);
					break;
				case 04 : // ���������� �׸��� ������
					pDC->SelectObject(&penNew2);
					break;
				case 10 : // �׸� 
					pDC->SelectObject(&penNew3);
					break;
				case 18 : // ����
					pDC->SelectObject(&penNew4);
					break;
				default : // 
					pDC->SelectObject(&penNew2);
				}
			} else
			{
				pDC->SelectObject(&penNew5);
			}
			switch(obj->hpgl_data[i].t) 
			{
			case 03 : // 03 : character
				if(obj->RadialFlag) 
				{
				}
			case 18 :
			case 10 :
			case 02 : // 02 : MoveTo
				// 2003.07.08 Detail Rotation ���� ���� start
//				pDC->MoveTo(pos); ����
				pDC->SelectObject(&penNew_up);
				if (i < (obj->nhpd))
					pDC->LineTo(pos);
				// 2003.07.08 Detail Rotation ���� ���� end
				break;
			default :  // 04 : LineTo
				//   2003.01.28 Timer
				DWORD dwTick = GetTickCount();
				MSG msg;
//				while(GetTickCount() - dwTick < 1)
				while(GetTickCount() - dwTick < SimulationSpeed)	
				{
					if (isSimulation == false)
						break;

					if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
					 {
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				}
				pDC->LineTo(pos);
				break;
			}
		}
		break;
	case BMP :
		i=0;
		break;
	case BITIMG:
		if ( !obj->m_Img.IsDataNull() )
		{
			px = obj->X;
			py = obj->Y;

			pos = CPoint(int(px),int(py));

			// 2003.07.09 Pen Up Line�� �׸��� start
			pDC->SelectObject(&penNew_up);
			pDC->LineTo(pos);
			// 2003.07.09 Pen Up Line�� �׸��� end

			if ( !obj->m_Img.IsDataNull() )
			{
				CRect rcDIB;
				rcDIB.left   = 0;
				rcDIB.top    = 0;
				rcDIB.right  = obj->m_Img.GetWidth();
				rcDIB.bottom = obj->m_Img.GetHeight();
				CRect rcDest;

				rcDest = rcDIB;
				rcDest.left  = long(px + rcDest.left  * xratio * obj->Xmag);
				rcDest.top   = long(py + rcDIB.bottom * yratio * obj->Ymag);
				rcDest.right = long(px + rcDest.right * xratio * obj->Xmag);
				rcDest.bottom= long(py - rcDIB.top    * yratio * obj->Ymag);

				obj->m_Img.Draw(pDC->m_hDC,&rcDIB,&rcDest, SRCCOPY);
			}

		}
	default :
		i=0;
		break;
	}

	if (pPenOld != NULL)
		pDC->SelectObject(pPenOld);	

}
// 2003.06.03 Simulation Draw  end


