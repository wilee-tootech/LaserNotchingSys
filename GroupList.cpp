// GroupList.cpp: implementation of the CGroupList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MK.h"
#include "GroupList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGroupList::CGroupList()
{
	m_Grouped = FALSE;
	dx = 0;
	dy = 0;
}
 
CGroupList::~CGroupList()
{

}
