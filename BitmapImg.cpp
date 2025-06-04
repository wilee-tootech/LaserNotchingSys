// BitmapImg.cpp : implementation file
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "BitmapImg.h"

#include "Util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitmapImg

CBitmapImg::CBitmapImg()
{
	
}

CBitmapImg::~CBitmapImg()
{
	
}


BEGIN_MESSAGE_MAP(CBitmapImg, CStatic)
	//{{AFX_MSG_MAP(CBitmapImg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitmapImg message handlers

void CBitmapImg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CStatic::OnPaint() for painting messages
	
		
}
void CBitmapImg::SetFileName(CString strFileName)
{
	
}

int CBitmapImg::GetGrayLevel()
{
	return 0;
}

void CBitmapImg::SetClone(CMKObject *pSrcObj)
{
	
}