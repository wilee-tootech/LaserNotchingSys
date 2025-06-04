// DlgDevicePitch.cpp : implementation file
//

#include "stdafx.h"
#include "mk.h"
#include "DlgDevicePitch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDevicePitch dialog
#include "MKDoc.h"
#include "Mainfrm.h"
#include "TransUnit.h"
#include "DeviceDlg.h"

CDlgDevicePitch::CDlgDevicePitch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDevicePitch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDevicePitch)
	m_fixPos = FALSE;
	m_unit = -1;
	m_offsetX = 0.0f;
	m_offsetY = 0.0f;
	//   2003.01.04
	NumOfXPitch1 = 1;  // X Pitch1의 갯수
	NumOfXPitch2 = 1;  // X Pitch2의 갯수
	NumOfYPitch1 = 1;  // Y Pitch1의 갯수
	NumOfYPitch2 = 1;  // Y Pitch2의 갯수

	//}}AFX_DATA_INIT
	m_pChip = NULL;
}


void CDlgDevicePitch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDevicePitch)
	DDX_Control(pDX, IDC_DEVICE_PITCH, m_deviceView);
	DDX_Check(pDX, IDC_CHECK_FIXED, m_fixPos);
	DDX_Radio(pDX, IDC_UNIT_POINT, m_unit);
	DDX_Text(pDX, IDC_OFFSET_X, m_offsetX);
	DDX_Text(pDX, IDC_OFFSET_Y, m_offsetY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDevicePitch, CDialog)
	//{{AFX_MSG_MAP(CDlgDevicePitch)
	ON_BN_CLICKED(IDC_CHIP_OFFSET, OnChipOffset)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	ON_BN_CLICKED(IDC_UNIT_POINT, OnUnitPoint)
	ON_BN_CLICKED(IDC_UNIT_MM, OnUnitMm)
	ON_BN_CLICKED(IDC_UNIT_MIL, OnUnitMil)
	ON_BN_CLICKED(IDC_UNIT_FIELD, OnUnitField)
	ON_BN_CLICKED(IDC_PITCH_OFFSET_FLG, OnPitchOffsetFlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDevicePitch message handlers

BOOL CDlgDevicePitch::OnInitDialog() 
{	
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	m_fixPos = 1;
	m_unit = 1;
//	m_OffsetFlag = false;

	UpdateData(FALSE);

	//   2002.12.26
	CMKDoc *pDoc = (CMKDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveDocument();

	if (pDoc->m_resetFalg == TRUE)
		OnReset();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDevicePitch::init()
{
	m_deviceView.m_stripHeight = int(m_stripHeight);
	m_deviceView.m_stripWidth  = int(m_stripWidth);
	m_deviceView.m_chipHeight = int(m_chipHeight);
	m_deviceView.m_chipWidth  = int(m_chipWidth);
	m_deviceView.m_pitchHeight = int(m_pitchHeight);
	m_deviceView.m_pitchWidth  = int(m_pitchWidth);
	m_deviceView.m_numX = m_numX;
	m_deviceView.m_numY = m_numY;
}

void CDlgDevicePitch::MkChip(CChip *pChip,int idfDir, int idfOffset)
{
	int i, j;
	BOOL odd=FALSE;
	
	CPoint pos;
	// CChip 배열 만들기
	//   2002.12.26 임시 주석
/*	if(m_pChip != NULL)
		delete m_pChip;*/
	m_pChip = new CChip[m_numY*m_numX];
	
	//   2003.01.03
	/*	pos.x = -(m_numX-1) * m_pitchWidth/2 ;
	pos.y =  (m_numY-1) * m_pitchHeight/2;*/
	
	//   2003.01.04

	//   2003.01.06
	float m_pitchWidth2_Trim;
	float m_pitchHeight2_Trim;
	//   2003.01.06

	//   2003.01.06
	m_pitchWidth2_Trim = m_pitchWidth2 - (m_pitchWidth * (m_SmallnumX - 1));
	m_pitchHeight2_Trim = m_pitchHeight2 - (m_pitchHeight * (m_SmallnumY - 1));
	//   2003.01.06
	
	if (m_SmallnumX == 1) {
		NumOfXPitch1 = m_numX - 1;
		NumOfXPitch2 = 0;
	}
	else if (m_numX % m_SmallnumX == 0) {
		NumOfXPitch1 = (m_numX / m_SmallnumX) * (m_SmallnumX -1);
		NumOfXPitch2 = m_numX / m_SmallnumX - 1;
	}
	else {
		NumOfXPitch1 = (m_numX / m_SmallnumX) * (m_SmallnumX -1) + (m_numX % m_SmallnumX -1);
		NumOfXPitch2 = m_numX / m_SmallnumX;
	}
	
	if (m_SmallnumY == 1) {
		NumOfYPitch1 = m_numY - 1;
		NumOfYPitch2 = 0;
	}
	else if (m_numY % m_SmallnumY == 0) {
		NumOfYPitch1 = (m_numY / m_SmallnumY) * (m_SmallnumY -1);
		NumOfYPitch2 = m_numY / m_SmallnumY - 1;
	}
	else {
		NumOfYPitch1 = (m_numY / m_SmallnumY) * (m_SmallnumY -1) + (m_numY % m_SmallnumY -1);
		NumOfYPitch2 = m_numY / m_SmallnumY;
	}
				//   2003.01.04

	if(detailFlag == TRUE)
	{
		//   2003.01.04
		pos.x = long(-NumOfXPitch1 * m_pitchWidth/2 + -NumOfXPitch2 * m_pitchWidth2_Trim/2);  // center 기준
		pos.y = long(NumOfYPitch1 * m_pitchHeight/2 + NumOfYPitch2 * m_pitchHeight2_Trim/2);  // center 기준
		
		//   2003.01.08
//		pos.x = -m_stripWidth/2; // Strip 시작점 기준
//		pos.y = m_stripHeight/2; // Strip 시작점 기준
		//   2003.01.08

		// 2007.03.14 hcpark - 이러면 안되는데... 시간관계상... 고정한다.
		idfDir = 0;

		if (idfDir == 0)
		{	// vertical
			for(i=0; i < m_numY; i++)
			{
				for(j=0; j < m_numX; j++)
				{
					m_pChip[i*m_numX+j].m_offsetX = 0;
					m_pChip[i*m_numX+j].m_offsetY = 0;
					m_pChip[i*m_numX+j].m_width  = int(m_chipWidth);
					m_pChip[i*m_numX+j].m_height = int(m_chipHeight);
					
					m_pChip[i*m_numX+j].m_position.x = pos.x;
					if (odd == TRUE)
					{
						m_pChip[i*m_numX+j].m_position.y = pos.y + idfOffset;
					} else
					{
						m_pChip[i*m_numX+j].m_position.y = pos.y;					
					}
					
					odd = ((odd == TRUE)? FALSE: TRUE);
					
					//   2003.01.03
					if (j % m_SmallnumX < m_SmallnumX - 1 || m_SmallnumX == 1)
						pos.x += long(m_pitchWidth);
					else // even
						pos.x += long(m_pitchWidth2_Trim);
					//   2003.01.03
				}
				odd=FALSE;  // line 바뀌면 새로 setting
				
				//	pos.x = -m_stripWidth/2 + m_chipWidth/2 ;  // 첫번째 칩 밀려나오는 문제 해결
				
				//   2003.01.04
				pos.x = long(-NumOfXPitch1 * m_pitchWidth/2 + -NumOfXPitch2 * m_pitchWidth2_Trim/2); // Center 기준
				//   2003.01.08
//				pos.x = -m_stripWidth/2; // Strip 시작점 기준
				//   2003.01.08
				
				if (i % m_SmallnumY < m_SmallnumY - 1 || m_SmallnumY == 1) // odd
					pos.y -= long(m_pitchHeight);
				else // even
					pos.y -= long(m_pitchHeight2_Trim);
				//   2003.01.04
			}
		} 
		else
		{	// horizontal
			for(j=0; j < m_numX; j++)
			{
				for(i=0; i < m_numY; i++)
				{
					m_pChip[i*m_numX+j].m_offsetX = 0;
					m_pChip[i*m_numX+j].m_offsetY = 0;
					m_pChip[i*m_numX+j].m_width  = int(m_chipWidth);
					m_pChip[i*m_numX+j].m_height = int(m_chipHeight);
					
					m_pChip[i*m_numX+j].m_position.y = pos.y;
					if (odd == TRUE)
					{
						m_pChip[i*m_numX+j].m_position.x = pos.x + idfOffset;
					} else
					{
						m_pChip[i*m_numX+j].m_position.x = pos.x;
					}
					odd = ((odd == TRUE)? FALSE: TRUE);
					//   2003.01.08
					if (i % m_SmallnumY < m_SmallnumY - 1 || m_SmallnumY == 1) // odd
						pos.y -= long(m_pitchHeight);
					else // even
						pos.y -= long(m_pitchHeight2_Trim);

//					pos.y -= m_pitchHeight;
				}
				odd=FALSE;  // line 바뀌면 새로 setting

				//   2003.01.03
				if (j % m_SmallnumX < m_SmallnumX - 1 || m_SmallnumX == 1)
					pos.x += long(m_pitchWidth);
				else // even
					pos.x += long(m_pitchWidth2_Trim);
				//   2003.01.03

//				pos.x += m_pitchWidth;
//				pos.y = -m_stripHeight/2 + m_chipHeight/2 ; 
					pos.y =  long((m_numY-1) * m_pitchHeight/2);  // center기준
//				pos.y = m_stripHeight/2; // Strip 시작점 기준 //   2003.01.08
			}
		}
		//   2003.01.03
	} else  // 
	{
		pos.x = long(-(m_numX-1) * m_pitchWidth/2);  // center기준
		pos.y = long((m_numY-1) * m_pitchHeight/2);  // center기준

		//   2003.01.08
//		pos.x = -m_stripWidth/2; // Strip 시작점 기준
//		pos.y = m_stripHeight/2; // Strip 시작점 기준
		//   2003.01.08

		// 2007.03.14 hcpark - 이러면 안되는데... 시간관계상... 고정한다.
		idfDir = 0;

		if (idfDir == 0)
		{	// vertical
			for(i=0; i < m_numY; i++)
			{
				for(j=0; j < m_numX; j++)
				{
					m_pChip[i*m_numX+j].m_offsetX = 0;
					m_pChip[i*m_numX+j].m_offsetY = 0;
					m_pChip[i*m_numX+j].m_width  = int(m_chipWidth);
					m_pChip[i*m_numX+j].m_height = int(m_chipHeight);
					
					m_pChip[i*m_numX+j].m_position.x = pos.x;
					if (odd == TRUE)
					{
						m_pChip[i*m_numX+j].m_position.y = pos.y + idfOffset;
					} else
					{
						m_pChip[i*m_numX+j].m_position.y = pos.y;					
					}
					
					odd = ((odd == TRUE)? FALSE: TRUE);
					pos.x += long(m_pitchWidth);
				}
				odd=FALSE;  // line 바뀌면 새로 setting
				
				//	pos.x = -m_stripWidth/2 + m_chipWidth/2 ; 
				// 첫번째 칩 밀려나오는 문제 해결
				pos.x = long(-(m_numX-1) * m_pitchWidth/2);  // center기준
				//   2003.01.08
//				pos.x = -m_stripWidth/2;  // 기준점 변경
				//   2003.01.08
				pos.y -= long(m_pitchHeight);
			}
		} 
		else
		{	// horizontal
			for(j=0; j < m_numX; j++)
			{
				for(i=0; i < m_numY; i++)
				{
					m_pChip[i*m_numX+j].m_offsetX = 0;
					m_pChip[i*m_numX+j].m_offsetY = 0;
					m_pChip[i*m_numX+j].m_width  = int(m_chipWidth);
					m_pChip[i*m_numX+j].m_height = int(m_chipHeight);
					
					m_pChip[i*m_numX+j].m_position.y = pos.y;
					if (odd == TRUE)
					{
						m_pChip[i*m_numX+j].m_position.x = pos.x + idfOffset;
					} else
					{
						m_pChip[i*m_numX+j].m_position.x = pos.x;
					}
					odd = ((odd == TRUE)? FALSE: TRUE);
					pos.y -= long(m_pitchHeight);
				}
				odd=FALSE;  // line 바뀌면 새로 setting

				pos.x += long(m_pitchWidth);
//				pos.y = -m_stripHeight/2 + m_chipHeight/2 ;  
				pos.y = long((m_numY-1) * m_pitchHeight/2);  // center기준
				//   2003.01.08
//				pos.y = m_stripHeight/2; // Strip 시작점 기준
				//   2003.01.08
			}
		}
	}
	
	m_deviceView.m_pChip = m_pChip;
}

///////////////////////////////////
// OFFSET 을 결정한다
void CDlgDevicePitch::OnChipOffset() 
{
	// TODO: Add your control notification handler code here
	// chip 데이터 조작
	UpdateData(TRUE);
	CMKDoc *pDoc = (CMKDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveDocument();
	CTransUnit value(float(pDoc->MaxField), float(pDoc->Maxmm));

	// 현재의 값을 field 값으로 변화 시킨다
	int unit;
	switch(m_unit)
	{
	case 0: //point
		unit = 2; break;
	case 1: // mm
		unit = 0; break;
	case 2: // Mil
		unit = 3; break;
	case 3: // Field
		unit = 1; break;
	default: // Field
		unit = 1; break;
	}

	float offsetx, offsety;
	value.SetValue(m_offsetX, unit);
	offsetx = float(value.GetField());
	
	value.SetValue(m_offsetY, unit);
	offsety = float(value.GetField());

	int i, j;

	//   2002.12.31
	BOOL OffsetFlag = true;
	int OffsetCount = 0;
	int CompareCount = 0;

	for(i=0; i < m_numY; i++)
	{
		for(j=0; j < m_numX; j++)
		{
			if (m_pChip[i*m_numX+j].m_selected == TRUE)
			{
				m_pChip[i*m_numX+j].m_offsetX = int(offsetx);
				m_pChip[i*m_numX+j].m_offsetY = int(offsety);
			}
				//   2002.12.31
/*				if (offsetx == 0 && offsety == 0)
					OffsetFlag = false;*/
		}
	}

	m_deviceView.Invalidate();

	//   2002.12.26
/*	if (OffsetFlag == true)
		pDoc->m_resetFalg = false;
	else 
		pDoc->m_resetFalg = true;*/
	pDoc->m_resetFalg = false;

}

void CDlgDevicePitch::OnReset() 
{
	// TODO: Add your control notification handler code here
	int i, j;

	CPoint pos;
	pos.x = long(-(m_numX-1) * m_pitchWidth/2);
	pos.y = long((m_numY-1) * m_pitchHeight/2);

	for(i=0; i < m_numY; i++)
	{
		for(j=0; j < m_numX; j++)
		{
			m_pChip[i*m_numX+j].m_offsetX = 0;
			m_pChip[i*m_numX+j].m_offsetY = 0;
			m_pChip[i*m_numX+j].m_width  = int(m_chipWidth);
			m_pChip[i*m_numX+j].m_height = int(m_chipHeight);
			m_pChip[i*m_numX+j].m_position = pos;

			pos.x += long(m_pitchWidth);
		}
		pos.x = long(-(m_numX-1) * m_pitchWidth/2);
		pos.y -= long(m_pitchHeight);
	}
	m_deviceView.Invalidate();

	//   2002.12.26
	CMKDoc *pDoc = (CMKDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveDocument();
	pDoc->m_resetFalg = true;
}

void CDlgDevicePitch::ShowOffsetDate(int offsetX, int offsetY)
{
	UpdateData(TRUE);
	CMKDoc *pDoc = (CMKDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveDocument();
	CTransUnit value(float(pDoc->MaxField), float(pDoc->Maxmm));
	int unit;

	switch(m_unit)
	{
	case 0: //point
		unit = 2; break;
	case 1: // mm
		unit = 0; break;
	case 2: // Mil
		unit = 3; break;
	case 3: // Field
		unit = 1; break;
	default: // Field
		unit = 1; break;
	}

	value.SetValue(offsetX, 1); // field
	ShowOffsetX(value.GetValue(unit));

	value.SetValue(offsetY, 1);
	ShowOffsetY(value.GetValue(unit));
}

void CDlgDevicePitch::ShowOffsetX(CString value)
{
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_STATIC_OFFSETX);
	pWnd->SetWindowText(value);
}

void CDlgDevicePitch::ShowOffsetX(int value)
{
	CWnd *pWnd;
	CString offset;

	pWnd = GetDlgItem(IDC_STATIC_OFFSETX);
	offset.Format("%d", value);			
	pWnd->SetWindowText(offset);
}

void CDlgDevicePitch::ShowOffsetX(double value)
{
	CWnd *pWnd;
	CString offset;

	pWnd = GetDlgItem(IDC_STATIC_OFFSETX);
	offset.Format("%.2f", value);			
	pWnd->SetWindowText(offset);
}

void CDlgDevicePitch::ShowOffsetY(CString value)
{
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_STATIC_OFFSETY);
	pWnd->SetWindowText(value);
}

void CDlgDevicePitch::ShowOffsetY(int value)
{
	CWnd *pWnd;
	CString offset;

	pWnd = GetDlgItem(IDC_STATIC_OFFSETY);
	offset.Format("%d", value);			
	pWnd->SetWindowText(offset);
}

void CDlgDevicePitch::ShowOffsetY(double value)
{
	CWnd *pWnd;
	CString offset;

	pWnd = GetDlgItem(IDC_STATIC_OFFSETY);
	offset.Format("%.2f", value);			
	pWnd->SetWindowText(offset);
}

void CDlgDevicePitch::ShowPosX(CString value)
{
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_STATIC_POSX);
	pWnd->SetWindowText(value);
}

void CDlgDevicePitch::ShowPosX(int value)
{
	CWnd *pWnd;
	CString offset;

	pWnd = GetDlgItem(IDC_STATIC_POSX);
	offset.Format("%d", value);			
	pWnd->SetWindowText(offset);
}

void CDlgDevicePitch::ShowPosX(double value)
{
	CWnd *pWnd;
	CString offset;

	pWnd = GetDlgItem(IDC_STATIC_POSX);
	offset.Format("%.2f", value);			
	pWnd->SetWindowText(offset);
}

void CDlgDevicePitch::ShowPosY(CString value)
{
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_STATIC_POSY);
	pWnd->SetWindowText(value);
}

void CDlgDevicePitch::ShowPosY(int value)
{
	CWnd *pWnd;
	CString offset;

	pWnd = GetDlgItem(IDC_STATIC_POSY);
	offset.Format("%d", value);			
	pWnd->SetWindowText(offset);
}

void CDlgDevicePitch::ShowPosY(double value)
{
	CWnd *pWnd;
	CString offset;

	pWnd = GetDlgItem(IDC_STATIC_POSY);
	offset.Format("%.2f", value);			
	pWnd->SetWindowText(offset);
}

void CDlgDevicePitch::ShowPosDate(int posX, int posY)
{
	UpdateData(TRUE);
	CMKDoc *pDoc = (CMKDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveDocument();
	CTransUnit value(float(pDoc->MaxField), float(pDoc->Maxmm));
	int unit;

	switch(m_unit)
	{
	case 0: //point
		unit = 2; break;
	case 1: // mm
		unit = 0; break;
	case 2: // Mil
		unit = 3; break;
	case 3: // Field
		unit = 1; break;
	default: // Field
		unit = 1; break;
	}

	value.SetValue(posX, 1); // field
	ShowPosX(value.GetValue(unit));

	value.SetValue(posY, 1);
	ShowPosY(value.GetValue(unit));
}

void CDlgDevicePitch::OnUnitPoint() 
{
	// TODO: Add your control notification handler code here
	CMKDoc *pDoc = (CMKDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveDocument();
	CTransUnit value(float(pDoc->MaxField), float(pDoc->Maxmm));
	int unit;
	switch(m_unit)
	{
	case 0: //point
		unit = 2; break;
	case 1: // mm
		unit = 0; break;
	case 2: // Mil
		unit = 3; break;
	case 3: // Field
		unit = 1; break;
	default: // Field
		unit = 1; break;
	}

	UpdateData(TRUE);
	
	value.SetValue(m_offsetX, unit);
	m_offsetX = float(value.GetValue(2));

	value.SetValue(m_offsetY, unit);
	m_offsetY = float(value.GetValue(2));
	UpdateData(FALSE);
}

void CDlgDevicePitch::OnUnitMm() 
{
	// TODO: Add your control notification handler code here
	CMKDoc *pDoc = (CMKDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveDocument();
	CTransUnit value(float(pDoc->MaxField), float(pDoc->Maxmm));
	int unit;
	switch(m_unit)
	{
	case 0: //point
		unit = 2; break;
	case 1: // mm
		unit = 0; break;
	case 2: // Mil
		unit = 3; break;
	case 3: // Field
		unit = 1; break;
	default: // Field
		unit = 1; break;
	}

	UpdateData(TRUE);
	
	value.SetValue(m_offsetX, unit);
	m_offsetX = float(value.GetValue(0));

	value.SetValue(m_offsetY, unit);
	m_offsetY = float(value.GetValue(0));
	UpdateData(FALSE);
	
}

void CDlgDevicePitch::OnUnitMil() 
{
	// TODO: Add your control notification handler code here
	CMKDoc *pDoc = (CMKDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveDocument();
	CTransUnit value(float(pDoc->MaxField), float(pDoc->Maxmm));
	int unit;
	switch(m_unit)
	{
	case 0: //point
		unit = 2; break;
	case 1: // mm
		unit = 0; break;
	case 2: // Mil
		unit = 3; break;
	case 3: // Field
		unit = 1; break;
	default: // Field
		unit = 1; break;
	}

	UpdateData(TRUE);
	
	value.SetValue(m_offsetX, unit);
	m_offsetX = float(value.GetValue(3));

	value.SetValue(m_offsetY, unit);
	m_offsetY = float(value.GetValue(3));
	UpdateData(FALSE);	
}

void CDlgDevicePitch::OnUnitField()
{
	// TODO: Add your control notification handler code here
	CMKDoc *pDoc = (CMKDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveDocument();
	CTransUnit value(float(pDoc->MaxField), float(pDoc->Maxmm));

	int unit;
	switch(m_unit)
	{
	case 0: //point
		unit = 2; break;
	case 1: // mm
		unit = 0; break;
	case 2: // Mil
		unit = 3; break;
	case 3: // Field
		unit = 1; break;
	default: // Field
		unit = 1; break;
	}

	UpdateData(TRUE);
	
	value.SetValue(m_offsetX, unit);
	m_offsetX = float(value.GetValue(1));

	value.SetValue(m_offsetY, unit);
	m_offsetY = float(value.GetValue(1));
	UpdateData(FALSE);		
}

void CDlgDevicePitch::OnPitchOffsetFlg() 
{
// m_OffsetFlag =! m_OffsetFlag; 	
}

//   2003.01.04
void CDlgDevicePitch::SetNumOfPitch()
{
	if (m_numX % m_SmallnumX == 0) {
		NumOfXPitch1 = (m_numX / m_SmallnumX) * (m_SmallnumX -1);
		NumOfXPitch2 = m_numX / m_SmallnumX - 1;
	}
	else {
		NumOfXPitch1 = (m_numX / m_SmallnumX) * (m_SmallnumX -1) + (m_numX % m_SmallnumX -1);
		NumOfXPitch2 = m_numX / m_SmallnumX;
	}
	
	if (m_numY % m_SmallnumY == 0) {
		NumOfYPitch1 = (m_numY / m_SmallnumY) * (m_SmallnumY -1);
		NumOfYPitch2 = m_numY / m_SmallnumY - 1;
	}
	else {
		NumOfYPitch1 = (m_numY / m_SmallnumY) * (m_SmallnumY -1) + (m_numY % m_SmallnumY -1);
		NumOfYPitch2 = m_numY / m_SmallnumY;
	}
}
//   2003.01.04
