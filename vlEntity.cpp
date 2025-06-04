// vlEntity.cpp: implementation of the CvlEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "beameditor6.h"
#include "vlEntity.h"
#include "VeCad.h"

#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CvlEntity::CvlEntity()
{
	m_iType			= -1;		
	m_hID			= -1;			
	m_iKey			= -1;			
	m_iLayer		= -1;		
	m_iStLine		= -1;		
	m_iPage			= -1;		
	m_iLevel		= -1;
	m_iIndex		= -1;		

	m_iColor		= 0;		
	m_iFillColor	= 0;	
	m_iNoGrips		= 0;		

	m_dLineWidth	= 0.0;	
	m_dWidth		= 0.0;		
	m_dHeight		= 0.0;		
	m_dLength		= 0.0;		
	m_dArea			= 0.0;		

	m_dExtLeft		= 0.0;		
	m_dExtBottom	= 0.0;	
	m_dExtRight		= 0.0;	
	m_dExtTop		= 0.0;		

	m_bSelect		= FALSE;		
	m_bVisible		= FALSE;
	m_bInBlock		= FALSE;
	m_bDeleted		= FALSE;
	m_bFilled		= FALSE;
	m_bBorder		= FALSE;
	m_bOwnColor		= FALSE;
	m_bOwnFillColor	= FALSE;
	m_bOwnLineWidth	= FALSE;
	m_bMultiLine	= FALSE;

	m_pExtObject	= NULL;
}

CvlEntity::CvlEntity(int nIndex)
{
	m_iIndex		= nIndex;

	UpdateData(true);
}


CvlEntity::~CvlEntity()
{

}

CvlEntity* CvlEntity::GetEntity(int nIndex)
{
	int Type	= vlPropGetInt( VD_ENT_TYPE, nIndex );

	CvlEntity* pObject = NULL;

	switch(Type)
	{		
	case VL_ENT_POINT:
		pObject = new CvlPoint(nIndex);
		break;
		
	case VL_ENT_LINE:
		pObject = new CvlLine(nIndex);
		break;
		
	case VL_ENT_POLY:
		pObject = new CvlPoly(nIndex);
		break;
		
	case VL_ENT_CIRCLE:
		pObject = new CvlCircle(nIndex);
		break;
		
	case VL_ENT_ARC:
		pObject = new CvlArc(nIndex);
		break;
		
	case VL_ENT_ARC2:
//		ASSERT(false);//CvlArc2		
		break;	
	
	case VL_ENT_ELLIPSE:
		pObject = new CvlEllipse(nIndex);
		break;
		
	case VL_ENT_RECT:
		pObject = new CvlRect(nIndex);
		break;

	case VL_ENT_TEXT:
		pObject = new CvlText(nIndex);
		break;

	case VL_ENT_HATCH:
		pObject = new CvlHatch(nIndex);
		break;

	case VL_ENT_BITMAP:
//		ASSERT(false);

	case VL_ENT_INSBLOCK:
		pObject = new CvlBlock(nIndex);
		break;

	case VL_ENT_DIMLIN:
		pObject = new CvlDimLinear(nIndex);
		break;

	case VL_ENT_DIMANG:
		pObject = new CvlDimAngula(nIndex);
		break;

	case VL_ENT_DIMRAD:
		pObject = new CvlDimRadial(nIndex);
		break;

	case VL_ENT_DIMDIAM:
		pObject = new CvlDimDiameter(nIndex);
		break;

	case VL_ENT_DIMORD:
		pObject = new CvlDimOrdinate(nIndex);
		break;

	default:
		TRACE("CvlEntity::GetEntity() Call Error : Type %d\n", Type);
//		ASSERT(false);
		break;
	}
	
	return pObject;
}

void CvlEntity::UpdateData(bool bSaveAndValidate)
{
	if (bSaveAndValidate==true)
	{
		m_iType			= vlPropGetInt( VD_ENT_TYPE, m_iIndex );

		m_hID			= vlPropGetInt( VD_ENT_HANDLE     , m_iIndex );
		m_iKey			= vlPropGetInt( VD_ENT_KEY        , m_iIndex );
		m_iLayer		= vlPropGetInt( VD_ENT_LAYER      , m_iIndex );
		m_iStLine		= vlPropGetInt( VD_ENT_STLINE     , m_iIndex );
		m_iPage			= vlPropGetInt( VD_ENT_PAGE       , m_iIndex );
		m_iLevel		= vlPropGetInt( VD_ENT_LEVEL      , m_iIndex );
		m_iColor		= vlPropGetInt( VD_ENT_COLOR      , m_iIndex );
		m_iFillColor	= vlPropGetInt( VD_ENT_FILLCOLOR  , m_iIndex );

		m_dLineWidth	= vlPropGetDbl( VD_ENT_LINEWIDTH  , m_iIndex );
		m_dExtLeft		= vlPropGetDbl( VD_ENT_LEFT       , m_iIndex );
		m_dExtBottom	= vlPropGetDbl( VD_ENT_BOTTOM     , m_iIndex );
		m_dExtRight		= vlPropGetDbl( VD_ENT_RIGHT      , m_iIndex );
		m_dExtTop		= vlPropGetDbl( VD_ENT_TOP        , m_iIndex );

		m_dLength		= vlPropGetDbl( VD_ENT_LENGTH     , m_iIndex );
		m_dArea			= vlPropGetDbl( VD_ENT_AREA       , m_iIndex );
		m_dWidth		= vlPropGetDbl( VD_ENT_WIDTH      , m_iIndex );
		m_dHeight		= vlPropGetDbl( VD_ENT_HEIGHT     , m_iIndex );

		m_bSelect		= vlPropGetInt( VD_ENT_SELECT     , m_iIndex );
		m_bVisible		= vlPropGetInt( VD_ENT_ONSCREEN   , m_iIndex );
		m_bInBlock		= vlPropGetInt( VD_ENT_INBLOCK    , m_iIndex );
		m_iNoGrips		= vlPropGetInt( VD_ENT_N_GRIPS    , m_iIndex );
		m_bDeleted		= vlPropGetInt( VD_ENT_DELETED    , m_iIndex );
		m_bFilled		= vlPropGetInt( VD_ENT_FILLED     , m_iIndex );
		m_bBorder		= vlPropGetInt( VD_ENT_BORDER     , m_iIndex );
		m_bOwnColor		= vlPropGetInt( VD_ENT_OWNCOLOR   , m_iIndex );
		m_bOwnFillColor	= vlPropGetInt( VD_ENT_OWNFCOLOR  , m_iIndex );
		m_bOwnLineWidth	= vlPropGetInt( VD_ENT_OWNLINEW   , m_iIndex );

		m_bMultiLine	= vlPropGetInt( VD_ENT_MULTILINE  , m_iIndex );
		m_pExtObject	= (void*)vlPropGetInt( VD_ENT_EXTOBJECT  , m_iIndex );
	}
	else
	{
		vlPropPutInt( VD_ENT_LAYER      , m_iIndex , m_iLayer		);
		vlPropPutInt( VD_ENT_STLINE     , m_iIndex , m_iStLine		);
		vlPropPutInt( VD_ENT_PAGE       , m_iIndex , m_iPage		);
		vlPropPutInt( VD_ENT_LEVEL      , m_iIndex , m_iLevel		);
		vlPropPutInt( VD_ENT_COLOR      , m_iIndex , m_iColor		);
		vlPropPutInt( VD_ENT_FILLCOLOR  , m_iIndex , m_iFillColor	);

		vlPropPutDbl( VD_ENT_LINEWIDTH  , m_iIndex , m_dLineWidth	);
		vlPropPutDbl( VD_ENT_LEFT       , m_iIndex , m_dExtLeft		);
		vlPropPutDbl( VD_ENT_BOTTOM     , m_iIndex , m_dExtBottom	);
		vlPropPutDbl( VD_ENT_RIGHT      , m_iIndex , m_dExtRight	);
		vlPropPutDbl( VD_ENT_TOP        , m_iIndex , m_dExtTop		);

		vlPropPutDbl( VD_ENT_LENGTH     , m_iIndex , m_dLength		);
		vlPropPutDbl( VD_ENT_AREA       , m_iIndex , m_dArea		);
		vlPropPutDbl( VD_ENT_WIDTH      , m_iIndex , m_dWidth		);
		vlPropPutDbl( VD_ENT_HEIGHT     , m_iIndex , m_dHeight		);

		vlPropPutInt( VD_ENT_SELECT     , m_iIndex , m_bSelect		);
		vlPropPutInt( VD_ENT_ONSCREEN   , m_iIndex , m_bVisible		);
		vlPropPutInt( VD_ENT_INBLOCK    , m_iIndex , m_bInBlock		);
		vlPropPutInt( VD_ENT_N_GRIPS    , m_iIndex , m_iNoGrips		);
		vlPropPutInt( VD_ENT_DELETED    , m_iIndex , m_bDeleted		);
		vlPropPutInt( VD_ENT_FILLED     , m_iIndex , m_bFilled		);
		vlPropPutInt( VD_ENT_BORDER     , m_iIndex , m_bBorder		);
		vlPropPutInt( VD_ENT_OWNCOLOR   , m_iIndex , m_bOwnColor	);
		vlPropPutInt( VD_ENT_OWNFCOLOR  , m_iIndex , m_bOwnFillColor);
		vlPropPutInt( VD_ENT_OWNLINEW   , m_iIndex , m_bOwnLineWidth);

		vlPropPutInt( VD_ENT_MULTILINE  , m_iIndex , m_bMultiLine	);
	//	vlPropPut   ( VD_ENT_EXTOBJECT  , m_iIndex , m_pExtObject	);
	}
}

void CvlEntity::Move(VLPOINT dOffset)
{
	vlMove( m_iIndex, dOffset.x, dOffset.y );

	vlUpdate();
	vlRedraw();

	UpdateData(true);
}

void CvlEntity::Select(bool bSel)
{
	vlSelect( bSel, m_iIndex );
}

const CvlEntity& CvlEntity::operator = (const CvlEntity& Src)
{
	m_iLayer		= Src.m_iLayer;		
	m_iStLine		= Src.m_iStLine;		
	m_iPage			= Src.m_iPage;		
	m_iLevel		= Src.m_iLevel;
	m_iIndex		= Src.m_iIndex;		

	m_iColor		= Src.m_iColor;		
	m_iFillColor	= Src.m_iFillColor;	
	m_iNoGrips		= Src.m_iNoGrips;		

	m_dLineWidth	= Src.m_dLineWidth;	
	m_dWidth		= Src.m_dWidth;		
	m_dHeight		= Src.m_dHeight;		
	m_dLength		= Src.m_dLength;		
	m_dArea			= Src.m_dArea;		

	m_dExtLeft		= Src.m_dExtLeft;		
	m_dExtBottom	= Src.m_dExtBottom;	
	m_dExtRight		= Src.m_dExtRight;	
	m_dExtTop		= Src.m_dExtTop;		

	m_bSelect		= Src.m_bSelect;		
	m_bVisible		= Src.m_bVisible;		
	m_bInBlock		= Src.m_bInBlock;		
	m_bDeleted		= Src.m_bDeleted;		
	m_bFilled		= Src.m_bFilled;		
	m_bBorder		= Src.m_bBorder;		
	m_bOwnColor		= Src.m_bOwnColor;	
	m_bOwnFillColor	= Src.m_bOwnFillColor;
	m_bOwnLineWidth	= Src.m_bOwnLineWidth;
	m_bMultiLine	= Src.m_bMultiLine;	

	return *this;
}

void CvlEntity::Explode(int nLevel)//nLevel 은 VL_ENT_LINE 혹은 VL_ENT_POLY.
{
	// EXPLODE 되는 동안 추가되는 엔티티의 인덱스 기록.
	BOOL bRet=FALSE;

	// 블럭 내에서 해치가 있을 경우 익스플로드를 하면 사라진다. 
	// 이 문제를 해결하기 위해 블럭을 익스플로드 하기 전에 안에 해치가 있을 경우 m_ExpAddArray 에 넣는다.
	// 이 배열은 익스플로드 되어서 나온 엔티티들을 저장하기 위한 것으로 폴리곤이나 라인이 아닌 해치는 나중에 다시
	// Explode 되면서 화면에 추가되게 된다. 

	if (m_iType==VL_ENT_INSBLOCK)
	{
		CvlBlock*	pBlock	= (CvlBlock*)this;
		int			i		= 0;

		pBlock->UpdateData(true);

		while(1)
		{			
			int nEnt = vlGetBlockEntity( pBlock->m_iIndexBlockDef , i++);

			if (nEnt==-1)
				break;

			CvlEntity* pEnt = CvlEntity::GetEntity(nEnt);

			if (pEnt->m_iType==VL_ENT_HATCH)
			{
				double	dCenterX	= (pEnt->m_dExtRight + pEnt->m_dExtLeft)/2;
				double	dCenterY	= (pEnt->m_dExtTop + pEnt->m_dExtBottom)/2;

				vlRotate(pEnt->m_iIndex, dCenterX, dCenterY, pBlock->m_dAngle);
		//		vlMove(pEnt->m_iIndex, 
				
				pEnt->Explode(nLevel);
				//CVeCad::m_ExpAddArray.Add( pEnt );
			}
			else
				delete pEnt;
		}
	}
	
	if (m_iType>nLevel)
	{
		CVeCad::m_bExplode = true;
		bRet = vlExplode(m_iIndex);
		CVeCad::m_bExplode = false;
	}
	else
		CVeCad::m_ExpAddArray.Add( CvlEntity::GetEntity(m_iIndex) );

	vlUpdate();

	if ( bRet==TRUE )
	{
		// EXPLODE 가 잘 되었고, 추가된 엔티티가 있는 경우.
		int Size = CVeCad::m_ExpAddArray.GetSize();
		bool bFlag = true;

		for (int i=0; i<Size; i++)
		{
			bFlag = false;

			CvlEntity* pObj = CVeCad::m_ExpAddArray.GetAt(i);

			if (pObj->m_iType > nLevel)
			{
				CVeCad::m_ExpAddArray.RemoveAt(i);

				Size--;
				i--;
				
				pObj->Explode(nLevel);

				delete pObj;
			}
		}

		if (bFlag)// Size==0 이면, 원래부터 Line 으로 가정.
		{
			CvlEntity* pObj = CvlEntity::GetEntity(m_iIndex);
			CVeCad::m_ExpAddArray.Add(pObj);
		}	
	}
}

//////////////////////////////////////////////////////////////////////////
// Point 

CvlPoint::CvlPoint()
{	
	m_dCoord.x		= 0;
	m_dCoord.y		= 0;
	m_iStPoint		= 0;
	m_iGroup		= 0;
	m_pszTxt		= NULL;
	m_iLenTxt		= 0;
	m_dTxtOffset.x	= 0.0;
	m_dTxtOffset.y	= 0.0;
	m_dTxtAngle		= 0.0;
	m_dBlockAngle	= 0.0;
	m_bFixed		= FALSE;
}

CvlPoint::CvlPoint(int nIndex)
{
	m_iIndex		= nIndex;
	m_pszTxt		= NULL;

	UpdateData(true);
}

CvlPoint::~CvlPoint()
{
	if (m_pszTxt)
		delete[] m_pszTxt;

}

void CvlPoint::UpdateData(bool bSaveAndValidate)
{
	CvlEntity::UpdateData(bSaveAndValidate);

	if (bSaveAndValidate)
	{
		m_dCoord.x		= vlPropGetDbl( VD_POINT_X        , m_iIndex );
		m_dCoord.y		= vlPropGetDbl( VD_POINT_Y        , m_iIndex );
		m_iStPoint		= vlPropGetInt( VD_POINT_STYLE    , m_iIndex );
		m_iGroup		= vlPropGetInt( VD_POINT_GROUP    , m_iIndex );
		m_dTxtOffset.x	= vlPropGetDbl( VD_POINT_TXTDX    , m_iIndex );	
		m_dTxtOffset.y	= vlPropGetDbl( VD_POINT_TXTDY    , m_iIndex );	
		m_dTxtAngle		= vlPropGetDbl( VD_POINT_TXTANG   , m_iIndex );	
		m_dBlockAngle	= vlPropGetDbl( VD_POINT_BLKANG   , m_iIndex );		
		m_bFixed		= vlPropGetInt( VD_POINT_FIXED    , m_iIndex );		

		m_iLenTxt		= vlPropGetInt( VD_POINT_TEXTLEN  , m_iIndex );

		if (m_pszTxt)
			delete[] m_pszTxt;

		m_pszTxt		= new char[m_iLenTxt+1];

		vlPropGet( VD_POINT_TEXT     , m_iIndex , m_pszTxt);
	}
	else
	{
		vlPropPutDbl( VD_POINT_X        , m_iIndex, m_dCoord.x		 );
		vlPropPutDbl( VD_POINT_Y        , m_iIndex, m_dCoord.y		 );
		vlPropPutInt( VD_POINT_STYLE    , m_iIndex, m_iStPoint		 );
		vlPropPutInt( VD_POINT_GROUP    , m_iIndex, m_iGroup		 );
		vlPropPutDbl( VD_POINT_TXTDX    , m_iIndex, m_dTxtOffset.x	 );	
		vlPropPutDbl( VD_POINT_TXTDY    , m_iIndex, m_dTxtOffset.y	 );
		vlPropPutDbl( VD_POINT_TXTANG   , m_iIndex, m_dTxtAngle		 );
		vlPropPutDbl( VD_POINT_BLKANG   , m_iIndex, m_dBlockAngle	 );
		vlPropPutInt( VD_POINT_FIXED    , m_iIndex, m_bFixed		 );
		vlPropPutInt( VD_POINT_TEXTLEN  , m_iIndex, m_iLenTxt		 );

		vlPropPut( VD_POINT_TEXT     , m_iIndex , m_pszTxt);
	}
}

const CvlPoint& CvlPoint::operator = (const CvlPoint& Src)
{

	m_dCoord		= Src.m_dCoord;
	m_iStPoint		= Src.m_iStPoint;
	m_iGroup		= Src.m_iGroup;
	m_dTxtOffset	= Src.m_dTxtOffset;
	m_dTxtAngle		= Src.m_dTxtAngle;
	m_dBlockAngle	= Src.m_dBlockAngle;
	m_bFixed		= Src.m_bFixed;
	m_iLenTxt		= Src.m_iLenTxt;

	if (m_pszTxt)
		delete[] m_pszTxt;

	m_pszTxt	= new char[m_iLenTxt];

	memcpy(m_pszTxt	, Src.m_pszTxt, m_iLenTxt);	

	CvlEntity::operator =(Src);

	return *this;
}

//////////////////////////////////////////////////////////////////////////
// Line 

CvlLine::CvlLine()
{
	m_dLine1.x = 0.0;
	m_dLine1.y = 0.0;
	m_dLine2.x = 0.0;
	m_dLine2.y = 0.0;

	m_iArrow1 = 0;
	m_iArrow2 = 0;
}

CvlLine::CvlLine(int nIndex)
{
	m_iIndex = nIndex;

	UpdateData(true);
}

void CvlLine::UpdateData(bool bSaveAndValidate)
{	
	CvlEntity::UpdateData(bSaveAndValidate);

	if (bSaveAndValidate)
	{
		m_dLine1.x = vlPropGetDbl( VD_LINE_X1	, m_iIndex);
		m_dLine1.y = vlPropGetDbl( VD_LINE_Y1	, m_iIndex);
		m_dLine2.x = vlPropGetDbl( VD_LINE_X2	, m_iIndex);
		m_dLine2.y = vlPropGetDbl( VD_LINE_Y2	, m_iIndex);
		
		m_iArrow1 = vlPropGetInt( VD_LINE_ARROW1, m_iIndex);
		m_iArrow2 = vlPropGetInt( VD_LINE_ARROW2, m_iIndex);
	}
	else
	{
		vlPropPutDbl( VD_LINE_X1	, m_iIndex, m_dLine1.x );
		vlPropPutDbl( VD_LINE_Y1	, m_iIndex, m_dLine1.y );
		vlPropPutDbl( VD_LINE_X2	, m_iIndex, m_dLine2.x );
		vlPropPutDbl( VD_LINE_Y2	, m_iIndex, m_dLine2.y );
		
		vlPropPutInt( VD_LINE_ARROW1, m_iIndex, m_iArrow1 );
		vlPropPutInt( VD_LINE_ARROW2, m_iIndex, m_iArrow2 );
	}
}

const CvlLine& CvlLine::operator = (const CvlLine& Src)
{
	m_dLine1	= Src.m_dLine1;
	m_dLine2	= Src.m_dLine2;
	m_iArrow1	= Src.m_iArrow1;
	m_iArrow2	= Src.m_iArrow2;

	CvlEntity::operator =(Src);

	return *this;
}

// 직선의 방정식에서 두 직선의 교점좌표 구하는 함수.
bool CvlLine::CalcIntersectPt(	VLPOINT PtSrc1, VLPOINT PtSrc2, 
								VLPOINT PtDst1, VLPOINT PtDst2, 
								VLPOINT* pPtIntercept,
								bool	bLimit)
{
	if ( (PtSrc2.x - PtSrc1.x) == 0.0 && (PtDst2.x - PtDst1.x)!=0.0 )
	{
		double dDstDelta = (PtDst2.y - PtDst1.y)/(PtDst2.x - PtDst1.x);
		double dDstIntercept = PtDst1.y - dDstDelta*PtDst1.x;

		pPtIntercept->x = PtSrc1.x;
		pPtIntercept->y = dDstDelta*PtSrc1.x + dDstIntercept; 
	}
	else if ( (PtDst2.x - PtDst1.x) == 0.0 )
	{
		double dSrcDelta = (PtSrc2.y - PtSrc1.y)/(PtSrc2.x - PtSrc1.x);
		double dSrcIntercept = PtSrc1.y - dSrcDelta*PtSrc1.x;
		
		pPtIntercept->x = PtDst1.x;
		pPtIntercept->y = dSrcDelta*PtDst1.x + dSrcIntercept; 
	}
	else
	{
		// 기울기..
		double dSrcDelta = (PtSrc2.y - PtSrc1.y)/(PtSrc2.x - PtSrc1.x);
		double dDstDelta = (PtDst2.y - PtDst1.y)/(PtDst2.x - PtDst1.x);

		if (dSrcDelta == dDstDelta)
			return false;

		// y 절편.
		double dSrcIntercept = PtSrc1.y - dSrcDelta*PtSrc1.x;
		double dDstIntercept = PtDst1.y - dDstDelta*PtDst1.x;

		// 교점 좌표.
		pPtIntercept->x = (dDstIntercept - dSrcIntercept) / (dSrcDelta - dDstDelta);
		pPtIntercept->y = dSrcDelta*pPtIntercept->x + dSrcIntercept;
	}

	// 선분의 범위내에 있는지 검사. 
	if (bLimit)
	{
		if (PtSrc1.x > PtSrc2.x)
		{
			double Temp = PtSrc1.x;
			PtSrc1.x	= PtSrc2.x;
			PtSrc2.x	= Temp;
		}

		if (PtSrc1.y > PtSrc2.y)
		{
			double Temp = PtSrc1.y;
			PtSrc1.y	= PtSrc2.y;
			PtSrc2.y	= Temp;
		}
		
		bool bRes1 = ((float)PtSrc1.x <= (float)pPtIntercept->x) ? true : false;
		bool bRes2 = ((float)PtSrc2.x >= (float)pPtIntercept->x) ? true : false;
		bool bRes3 = ((float)PtSrc1.y <= (float)pPtIntercept->y) ? true : false;
		bool bRes4 = ((float)PtSrc2.y >= (float)pPtIntercept->y) ? true : false;

		if ( bRes1 && bRes2 && bRes3 && bRes4 )
			return true;
		else
			return false;
	}
	
	return true;
}

bool CvlLine::CalcIntersectPt(	VLPOINT PtSrc1, VLPOINT PtSrc2, 
								VLPOINT PtDst,
								VLPOINT* pPtIntercept,
								bool	bLimit)
{
	// 기울기..

	double dSrcDelta	= 0.0;
	double dDstDelta	= 0.0;

	if ( (PtSrc2.x - PtSrc1.x)==0.0)	// Src : x = a,
	{
		pPtIntercept->x = PtSrc1.x;
		pPtIntercept->y = PtDst.y;
	}
	else if ((PtSrc2.y - PtSrc1.y)==0.0)// Src : y = a,
	{
		pPtIntercept->x = PtDst.x;
		pPtIntercept->y = PtSrc1.y;
	}
	else
	{
		dSrcDelta = (PtSrc2.y - PtSrc1.y)/(PtSrc2.x - PtSrc1.x);
		dDstDelta = -(1/dSrcDelta);
	
		if (dSrcDelta == dDstDelta)//평행.
			return false;

		// y 절편.
		double dSrcIntercept = PtSrc1.y - dSrcDelta*PtSrc1.x;
		double dDstIntercept = PtDst.y - dDstDelta*PtDst.x;

		// 교점 좌표.
		pPtIntercept->x = (dDstIntercept - dSrcIntercept) / (dSrcDelta - dDstDelta);
		pPtIntercept->y = dSrcDelta*pPtIntercept->x + dSrcIntercept;
	}

	// 선분의 범위내에 있는지 검사. 
	if (bLimit==true)
	{
		if (PtSrc1.x > PtSrc2.x)
		{
			double Temp = PtSrc1.x;
			PtSrc1.x	= PtSrc2.x;
			PtSrc2.x	= Temp;
		}

		if (PtSrc1.y > PtSrc2.y)
		{
			double Temp = PtSrc1.y;
			PtSrc1.y	= PtSrc2.y;
			PtSrc2.y	= Temp;
		}
		
		if ((PtSrc1.x <= pPtIntercept->x && PtSrc2.x >= pPtIntercept->x) &&
			(PtSrc1.y <= pPtIntercept->y && PtSrc2.y >= pPtIntercept->y) )
			return true;
		else
			return false;
	}

	return true;
	
}

void CvlLine::MovePt1(double dX, double dY)
{
	vlPropPutDbl( VD_LINE_X1, m_iIndex, dX );
	vlPropPutDbl( VD_LINE_Y1, m_iIndex, dY );
}

void CvlLine::MovePt2(double dX, double dY)
{
	vlPropPutDbl( VD_LINE_X2, m_iIndex, dX );
	vlPropPutDbl( VD_LINE_Y2, m_iIndex, dY );
}


//////////////////////////////////////////////////////////////////////////
// PolyLine 

CvlPoly::CvlPoly()
{
	m_pdVert = NULL;
}

CvlPoly::CvlPoly(int nIndex)
{
	m_iIndex = nIndex;
	
	m_pdVert = NULL;

	UpdateData(true);
}

CvlPoly::~CvlPoly()
{
	delete[] m_pdVert;
}

void CvlPoly::UpdateData(bool bSaveAndValidate)
{
	CvlEntity::UpdateData(bSaveAndValidate);

	if (bSaveAndValidate)
	{
 		m_bClosed		= vlPropGetInt( VD_POLY_CLOSED,		m_iIndex);
		m_iStSmooth		= vlPropGetInt( VD_POLY_SMOOTH,		m_iIndex);
		m_iArrow1		= vlPropGetInt( VD_POLY_ARROW1,		m_iIndex);
		m_iArrow2		= vlPropGetInt( VD_POLY_ARROW2,		m_iIndex);
		m_dVerRadius	= vlPropGetDbl( VD_POLY_R,			m_iIndex);
		m_iNoVer		= vlPropGetInt( VD_POLY_N_VER,		m_iIndex);

		if (m_bClosed==0)
			m_bClosed=FALSE;
		else
			m_bClosed=TRUE;

		double temp = 0.0;

		if (m_pdVert)
			delete[] m_pdVert;

		m_pdVert = new VLPOINT[m_iNoVer];

		for (int i=0; i<m_iNoVer; i++)
			vlPolyVerGet(m_iIndex, i, &(m_pdVert[i].x), &(m_pdVert[i].y), &temp);
		
		m_iCurrVer			= vlPropGetInt( VD_POLY_C_VER,		m_iIndex);
		m_dCurrVerCoord.x	= vlPropGetDbl( VD_POLY_VER_X,		m_iIndex);
		m_dCurrVerCoord.y	= vlPropGetDbl( VD_POLY_VER_Y,		m_iIndex);
		m_dCurrVerRadius	= vlPropGetDbl( VD_POLY_VER_R,		m_iIndex);
		m_dCoeffBulge		= vlPropGetDbl( VD_POLY_VER_BULGE,	m_iIndex);
		m_bCurrVerOn		= vlPropGetInt( VD_POLY_VER_ON,		m_iIndex);	
	}
	else
	{
		vlPropPutInt( VD_POLY_CLOSED,		m_iIndex, m_bClosed		);
		vlPropPutInt( VD_POLY_SMOOTH,		m_iIndex, m_iStSmooth	);
		vlPropPutInt( VD_POLY_ARROW1,		m_iIndex, m_iArrow1		);
		vlPropPutInt( VD_POLY_ARROW2,		m_iIndex, m_iArrow2		);
		vlPropPutDbl( VD_POLY_R,			m_iIndex, m_dVerRadius	);
		vlPropPutInt( VD_POLY_N_VER,		m_iIndex, m_iNoVer		);

		double temp = 0.0;

		for (int i=0; i<m_iNoVer; i++)
		{
			vlPolyVerSet(m_iIndex, i, m_pdVert[i].x, m_pdVert[i].y, temp);

			TRACE("%d - %.3lf, %.3lf\n", i, m_pdVert[i].x, m_pdVert[i].y );
		}
		
		vlPropPutInt( VD_POLY_C_VER,		m_iIndex, m_iCurrVer		);
		vlPropPutDbl( VD_POLY_VER_X,		m_iIndex, m_dCurrVerCoord.x	);
		vlPropPutDbl( VD_POLY_VER_Y,		m_iIndex, m_dCurrVerCoord.y	);
		vlPropPutDbl( VD_POLY_VER_R,		m_iIndex, m_dCurrVerRadius	);
		vlPropPutDbl( VD_POLY_VER_BULGE,	m_iIndex, m_dCoeffBulge		);
		vlPropPutInt( VD_POLY_VER_ON,		m_iIndex, m_bCurrVerOn		);	
	}
}


const CvlPoly& CvlPoly::operator = (const CvlPoly& Src)
{
	m_bClosed		= Src.m_bClosed;
	m_iStSmooth		= Src.m_iStSmooth;

	m_iArrow1		= Src.m_iArrow1;
	m_iArrow2		= Src.m_iArrow2;
	m_dVerRadius	= Src.m_dVerRadius;
	m_iNoVer		= Src.m_iNoVer;
	m_iCurrVer		= Src.m_iCurrVer;
	m_dCurrVerCoord	= Src.m_dCurrVerCoord;
	m_dCurrVerRadius= Src.m_dCurrVerRadius;
	m_dCoeffBulge	= Src.m_dCoeffBulge;
	m_bCurrVerOn	= Src.m_bCurrVerOn;

	if (m_pdVert)
		delete[] m_pdVert;
	
	m_pdVert = new VLPOINT[m_iNoVer];
	memcpy(m_pdVert, Src.m_pdVert, sizeof(VLPOINT)*m_iNoVer);

	CvlEntity::operator =(Src);

	return *this;
}

//////////////////////////////////////////////////////////////////////////
// Rectangle
 
CvlRect::CvlRect()
{
	m_dCoord.x	= 0.0;
	m_dCoord.y	= 0.0;
	m_dWidth	= 0.0;
	m_dHeight	= 0.0;
	m_dAngle	= 0.0;
	m_dRadius	= 0.0;
}

CvlRect::CvlRect(int nIndex)
{
	m_iIndex = nIndex;

	UpdateData(true);
}

void CvlRect::UpdateData(bool bSaveAndValidate)
{
	CvlEntity::UpdateData(bSaveAndValidate);

	if (bSaveAndValidate)
	{
		m_dCoord.x	= vlPropGetDbl( VD_RECT_XCEN     , m_iIndex);
		m_dCoord.y	= vlPropGetDbl( VD_RECT_YCEN     , m_iIndex);
		m_dWidth	= vlPropGetDbl( VD_RECT_WIDTH    , m_iIndex);
		m_dHeight	= vlPropGetDbl( VD_RECT_HEIGHT   , m_iIndex);
		m_dAngle	= vlPropGetDbl( VD_RECT_ANGLE    , m_iIndex);
		m_dRadius	= vlPropGetDbl( VD_RECT_RADIUS   , m_iIndex);
	}
	else
	{
		vlPropPutDbl( VD_RECT_XCEN     , m_iIndex, m_dCoord.x	);
		vlPropPutDbl( VD_RECT_YCEN     , m_iIndex, m_dCoord.y	);
		vlPropPutDbl( VD_RECT_WIDTH    , m_iIndex, m_dWidth		);
		vlPropPutDbl( VD_RECT_HEIGHT   , m_iIndex, m_dHeight	);
		vlPropPutDbl( VD_RECT_ANGLE    , m_iIndex, m_dAngle		);
		vlPropPutDbl( VD_RECT_RADIUS   , m_iIndex, m_dRadius	);
	}
}

const CvlRect& CvlRect::operator = (const CvlRect& Src)
{
	m_dCoord.x	= Src.m_dCoord.x;
	m_dCoord.y	= Src.m_dCoord.y;
	m_dWidth	= Src.m_dWidth	;
	m_dHeight	= Src.m_dHeight	;
	m_dAngle	= Src.m_dAngle	;
	m_dRadius	= Src.m_dRadius	;

	CvlEntity::operator =(Src);

	return *this;
}

////////////////////////////////////////////////////////////////////////////
// Text

CvlText::CvlText()
{
	m_pszTxt			= NULL;
	m_iLength			= 0;
	m_dCoord.x			= 0.0;			
	m_dCoord.y			= 0.0;
	m_iStyle			= -1;			
	m_dHeight			= 0.0;			
	m_dWidthScale		= 0.0;		
	m_iAlign			= -1;			
	m_dAngleRotation	= 0.0;	
	m_dAngleOblique		= 0.0;	
	m_dIntervalHorz		= 0.0;	
	m_dIntervalVert		= 0.0;	
	m_bIsPath			= FALSE;			
	m_bIsStrikeOut		= FALSE;		
	m_bIsUnderLine		= FALSE;		
	m_iNoLines			= -1;
	m_iPathCurve		= -1;
	m_dCurveOrg.x		= 0.0;
	m_dCurveOrg.y		= 0.0;
	m_bIsBackwardCurve	= FALSE;	
	m_bIsAbsAngle		= FALSE;
}

CvlText::CvlText(int nIndex)
{	
	m_pszTxt = NULL;
	m_iIndex = nIndex;

	UpdateData(true);
}

CvlText::~CvlText()
{
	if (m_pszTxt)
		delete[] m_pszTxt;
}

void CvlText::UpdateData(bool bSaveAndValidate)
{
	CvlEntity::UpdateData(bSaveAndValidate);

	if (bSaveAndValidate)
	{
		m_iLength = vlPropGetInt(VD_TEXT_LENGTH, m_iIndex);

		if (m_pszTxt)
			delete[] m_pszTxt;

		m_pszTxt = new char[m_iLength];
		memset(m_pszTxt, 0, sizeof(char)*m_iLength);
		vlPropGet(VD_TEXT_TEXT      , m_iIndex, m_pszTxt);

		m_dCoord.x			= vlPropGetDbl( VD_TEXT_X,			m_iIndex);			
		m_dCoord.y			= vlPropGetDbl( VD_TEXT_Y,			m_iIndex);
		m_iStyle			= vlPropGetInt( VD_TEXT_STYLE,		m_iIndex);			
		m_dHeight			= vlPropGetDbl( VD_TEXT_HEIGHT,		m_iIndex);			
		m_dWidthScale		= vlPropGetDbl( VD_TEXT_WSCALE,		m_iIndex);		
		m_iAlign			= vlPropGetInt( VD_TEXT_ALIGN,		m_iIndex);			
		m_dAngleRotation	= vlPropGetDbl( VD_TEXT_ANGLE,		m_iIndex);	
		m_dAngleOblique		= vlPropGetDbl( VD_TEXT_OBLIQUE,	m_iIndex);	
		m_dIntervalHorz		= vlPropGetDbl( VD_TEXT_INTER_H,	m_iIndex);	
		m_dIntervalVert		= vlPropGetDbl( VD_TEXT_INTER_V,	m_iIndex);
		m_bIsPath			= vlPropGetInt( VD_TEXT_PATH,		m_iIndex);			
		m_bIsStrikeOut		= vlPropGetInt( VD_TEXT_STRIKEOUT,	m_iIndex);			
		m_bIsUnderLine		= vlPropGetInt( VD_TEXT_UNDERLINE,	m_iIndex);			
		m_iNoLines			= vlPropGetInt( VD_TEXT_N_LINES,	m_iIndex);			
		m_iPathCurve		= vlPropGetInt( VD_TEXTP_CURVE,		m_iIndex);
		m_dCurveOrg.x		= vlPropGetDbl( VD_TEXTP_DX,		m_iIndex);
		m_dCurveOrg.y		= vlPropGetDbl( VD_TEXTP_DY,		m_iIndex);
		m_bIsBackwardCurve	= vlPropGetInt( VD_TEXTP_BACKWARD,	m_iIndex);	
		m_bIsAbsAngle		= vlPropGetInt( VD_TEXTP_ABSANGLE,	m_iIndex);
	}
	else
	{
		vlPropPut(VD_TEXT_TEXT,			m_iIndex, m_pszTxt			);
		
		vlPropPutInt(VD_TEXT_LENGTH,	m_iIndex, m_iLength			);
		vlPropPutDbl( VD_TEXT_X,		m_iIndex, m_dCoord.x		);			
		vlPropPutDbl( VD_TEXT_Y,		m_iIndex, m_dCoord.y		);
		vlPropPutInt( VD_TEXT_STYLE,	m_iIndex, m_iStyle			);			
		vlPropPutDbl( VD_TEXT_HEIGHT,	m_iIndex, m_dHeight			);			
		vlPropPutDbl( VD_TEXT_WSCALE,	m_iIndex, m_dWidthScale		);		
		vlPropPutInt( VD_TEXT_ALIGN,	m_iIndex, m_iAlign			);			
		vlPropPutDbl( VD_TEXT_ANGLE,	m_iIndex, m_dAngleRotation	);	
		vlPropPutDbl( VD_TEXT_OBLIQUE,	m_iIndex, m_dAngleOblique	);	
		vlPropPutDbl( VD_TEXT_INTER_H,	m_iIndex, m_dIntervalHorz	);	
		vlPropPutDbl( VD_TEXT_INTER_V,	m_iIndex, m_dIntervalVert	);
		vlPropPutInt( VD_TEXT_PATH,		m_iIndex, m_bIsPath			);			
		vlPropPutInt( VD_TEXT_STRIKEOUT,m_iIndex, m_bIsStrikeOut	);			
		vlPropPutInt( VD_TEXT_UNDERLINE,m_iIndex, m_bIsUnderLine	);			
		vlPropPutInt( VD_TEXT_N_LINES,	m_iIndex, m_iNoLines		);			
		vlPropPutInt( VD_TEXTP_CURVE,	m_iIndex, m_iPathCurve		);
		vlPropPutDbl( VD_TEXTP_DX,		m_iIndex, m_dCurveOrg.x		);
		vlPropPutDbl( VD_TEXTP_DY,		m_iIndex, m_dCurveOrg.y		);
		vlPropPutInt( VD_TEXTP_BACKWARD,m_iIndex, m_bIsBackwardCurve);	
		vlPropPutInt( VD_TEXTP_ABSANGLE,m_iIndex, m_bIsAbsAngle		);
	}
}

const CvlText& CvlText::operator = (const CvlText& Src)
{
	m_iLength			= Src.m_iLength			; 

	if (m_pszTxt)
		delete[] m_pszTxt;

	m_pszTxt = new char[m_iLength];

	memcpy(m_pszTxt	, Src.m_pszTxt, m_iLength); 
	
	m_dCoord.x			= Src.m_dCoord.x		; 
	m_dCoord.y			= Src.m_dCoord.y		; 
	m_iStyle			= Src.m_iStyle			; 
	m_dHeight			= Src.m_dHeight			; 
	m_dWidthScale		= Src.m_dWidthScale		; 
	m_iAlign			= Src.m_iAlign			; 
	m_dAngleRotation	= Src.m_dAngleRotation	; 
	m_dAngleOblique		= Src.m_dAngleOblique	; 
	m_dIntervalHorz		= Src.m_dIntervalHorz	; 
	m_dIntervalVert		= Src.m_dIntervalVert	; 
	m_bIsPath			= Src.m_bIsPath			; 
	m_bIsStrikeOut		= Src.m_bIsStrikeOut	; 
	m_bIsUnderLine		= Src.m_bIsUnderLine	; 
	m_iNoLines			= Src.m_iNoLines		; 
	m_iPathCurve		= Src.m_iPathCurve		; 
	m_dCurveOrg.x		= Src.m_dCurveOrg.x		; 
	m_dCurveOrg.y		= Src.m_dCurveOrg.y		; 
	m_bIsBackwardCurve	= Src.m_bIsBackwardCurve; 
	m_bIsAbsAngle		= Src.m_bIsAbsAngle		; 

	CvlEntity::operator =(Src);

	return *this;
}

//////////////////////////////////////////////////////////////////////////////////
// Arc

CvlArc::CvlArc()
{
	m_dCoordCenter.x	= 0.0;
	m_dCoordCenter.y	= 0.0;
	m_dCoordStart.x		= 0.0;
	m_dCoordStart.y		= 0.0;
	m_dCoordEnd.x		= 0.0;
	m_dCoordEnd.y		= 0.0;

	m_dRadius			= 0.0;
	m_dStart			= 0.0;
	m_dEnd				= 0.0;
	m_iStArrow1			= -1;
	m_iStArrow2			= -1;
	m_dRadiusHorz		= 0.0;
	m_dRadiusVert		= 0.0;
	m_dAngleStart		= 0.0;
	m_dAngleInclude		= 0.0;
	m_dAngleRotation	= 0.0;
	m_bIsSectorMode		= FALSE;
	m_bIsChordMode		= FALSE;
}

CvlArc::CvlArc(int nIndex)
{
	m_iIndex = nIndex;

	UpdateData(true);
}

CvlArc::~CvlArc()
{

}

void CvlArc::UpdateData(bool bSaveAndValidate)
{
	CvlEntity::UpdateData(bSaveAndValidate);

	if (bSaveAndValidate)
	{
		m_dCoordCenter.x	= vlPropGetDbl(VD_ARC_X,		m_iIndex);
		m_dCoordCenter.y	= vlPropGetDbl(VD_ARC_Y,		m_iIndex);
		m_dCoordStart.x		= vlPropGetDbl(VD_ARC_XS,		m_iIndex);
		m_dCoordStart.y		= vlPropGetDbl(VD_ARC_YS,		m_iIndex);
		m_dCoordEnd.x		= vlPropGetDbl(VD_ARC_XE,		m_iIndex);
		m_dCoordEnd.y		= vlPropGetDbl(VD_ARC_YE,		m_iIndex);

		m_dRadius			= vlPropGetDbl(VD_ARC_R,		m_iIndex);
		m_dStart			= vlPropGetDbl(VD_ARC_START,	m_iIndex);
		m_dEnd				= vlPropGetDbl(VD_ARC_END,		m_iIndex);
		m_iStArrow1			= vlPropGetInt(VD_ARC_ARROW1,	m_iIndex);
		m_iStArrow2			= vlPropGetInt(VD_ARC_ARROW2,	m_iIndex);
		m_dRadiusHorz		= vlPropGetDbl(VD_ARC_RH,		m_iIndex);
		m_dRadiusVert		= vlPropGetDbl(VD_ARC_RV,		m_iIndex);
		m_dAngleStart		= vlPropGetDbl(VD_ARC_ANG0,		m_iIndex);
		m_dAngleInclude		= vlPropGetDbl(VD_ARC_ANGARC,	m_iIndex);
		m_dAngleRotation	= vlPropGetDbl(VD_ARC_ANGROT,	m_iIndex);
		m_bIsSectorMode		= vlPropGetInt(VD_ARC_SECTOR,	m_iIndex);
		m_bIsChordMode		= vlPropGetInt(VD_ARC_CHORD,	m_iIndex);
	}
	else
	{
		vlPropPutDbl(VD_ARC_X,		m_iIndex, m_dCoordCenter.x	);
		vlPropPutDbl(VD_ARC_Y,		m_iIndex, m_dCoordCenter.y	);
		vlPropPutDbl(VD_ARC_XS,		m_iIndex, m_dCoordStart.x	);
		vlPropPutDbl(VD_ARC_YS,		m_iIndex, m_dCoordStart.y	);
		vlPropPutDbl(VD_ARC_XE,		m_iIndex, m_dCoordEnd.x		);
		vlPropPutDbl(VD_ARC_YE,		m_iIndex, m_dCoordEnd.y		);

		vlPropPutDbl(VD_ARC_R,		m_iIndex, m_dRadius			);
		vlPropPutDbl(VD_ARC_START,	m_iIndex, m_dStart			);
		vlPropPutDbl(VD_ARC_END,	m_iIndex, m_dEnd			);
		vlPropPutInt(VD_ARC_ARROW1,	m_iIndex, m_iStArrow1		);
		vlPropPutInt(VD_ARC_ARROW2,	m_iIndex, m_iStArrow2		);
		vlPropPutDbl(VD_ARC_RH,		m_iIndex, m_dRadiusHorz		);
		vlPropPutDbl(VD_ARC_RV,		m_iIndex, m_dRadiusVert		);
		vlPropPutDbl(VD_ARC_ANG0,	m_iIndex, m_dAngleStart		);
		vlPropPutDbl(VD_ARC_ANGARC,	m_iIndex, m_dAngleInclude	);
		vlPropPutDbl(VD_ARC_ANGROT,	m_iIndex, m_dAngleRotation	);
		vlPropPutInt(VD_ARC_SECTOR,	m_iIndex, m_bIsSectorMode	);
		vlPropPutInt(VD_ARC_CHORD,	m_iIndex, m_bIsChordMode	);
	}
}

const CvlArc& CvlArc::operator = (const CvlArc& Src)
{
	m_dCoordCenter.x	= Src. m_dCoordCenter.x	; 
	m_dCoordCenter.y	= Src. m_dCoordCenter.y	; 
	m_dCoordStart.x		= Src. m_dCoordStart.x	; 
	m_dCoordStart.y		= Src. m_dCoordStart.y	; 
	m_dCoordEnd.x		= Src. m_dCoordEnd.x	; 
	m_dCoordEnd.y		= Src. m_dCoordEnd.y	; 

	m_dRadius			= Src. m_dRadius		; 
	m_dStart			= Src. m_dStart			; 
	m_dEnd				= Src. m_dEnd			; 
	m_iStArrow1			= Src. m_iStArrow1		; 
	m_iStArrow2			= Src. m_iStArrow2		; 
	m_dRadiusHorz		= Src. m_dRadiusHorz	; 
	m_dRadiusVert		= Src. m_dRadiusVert	; 
	m_dAngleStart		= Src. m_dAngleStart	; 
	m_dAngleInclude		= Src. m_dAngleInclude	; 
	m_dAngleRotation	= Src. m_dAngleRotation	; 
	m_bIsSectorMode		= Src. m_bIsSectorMode	; 
	m_bIsChordMode		= Src. m_bIsChordMode	; 

	CvlEntity::operator =(Src);

	return *this;
}

//////////////////////////////////////////////////////////////////////////////////
// Ellipse

CvlEllipse::CvlEllipse()
{
	m_dCoord.x			= 0.0;
	m_dCoord.y			= 0.0;
	m_dRadiusHorz		= 0.0;
	m_dRadiusVert		= 0.0;
	m_dAngle			= 0.0;
}

CvlEllipse::CvlEllipse(int nIndex)
{
	m_iIndex = nIndex;

	UpdateData(true);
}

CvlEllipse::~CvlEllipse()
{

}

void CvlEllipse::UpdateData(bool bSaveAndValidate)
{
	CvlEntity::UpdateData(bSaveAndValidate);

	if (bSaveAndValidate)
	{
		m_dCoord.x		= vlPropGetDbl( VD_ELLIPSE_X,		m_iIndex );	
		m_dCoord.y		= vlPropGetDbl( VD_ELLIPSE_Y,		m_iIndex );
		m_dRadiusHorz	= vlPropGetDbl( VD_ELLIPSE_RH,		m_iIndex );	
		m_dRadiusVert	= vlPropGetDbl( VD_ELLIPSE_RV,		m_iIndex );	
		m_dAngle		= vlPropGetDbl( VD_ELLIPSE_ANGLE,	m_iIndex );
	}
	else
	{
		vlPropPutDbl( VD_ELLIPSE_X,		m_iIndex, m_dCoord.x);	
		vlPropPutDbl( VD_ELLIPSE_Y,		m_iIndex, m_dCoord.y);
		vlPropPutDbl( VD_ELLIPSE_RH,	m_iIndex, m_dRadiusHorz	);
		vlPropPutDbl( VD_ELLIPSE_RV,	m_iIndex, m_dRadiusVert	);
		vlPropPutDbl( VD_ELLIPSE_ANGLE,	m_iIndex, m_dAngle		);
	}
}

const CvlEllipse& CvlEllipse::operator = (const CvlEllipse& Src)
{
	m_dCoord.x		= Src.m_dCoord.x ; 
	m_dCoord.x		= Src.m_dCoord.x ; 
	m_dRadiusHorz	= Src.m_dRadiusHorz	 ; 
	m_dRadiusVert	= Src.m_dRadiusVert	 ; 
	m_dAngle		= Src.m_dAngle		 ; 

	CvlEntity::operator = (Src);

	return *this;
}


//////////////////////////////////////////////////////////////////////////////////
// Circle

CvlCircle::CvlCircle()
{
	m_dCoord.x	= 0.0;
	m_dCoord.y	= 0.0;
	m_dRadius	= 0.0;
}

CvlCircle::CvlCircle(int nIndex)
{
	m_iIndex = nIndex;

	UpdateData(true);
}

CvlCircle::~CvlCircle()
{

}

void CvlCircle::UpdateData(bool bSaveAndValidate)
{
	CvlEntity::UpdateData(bSaveAndValidate);

	if (bSaveAndValidate)
	{
		m_dCoord.x	= vlPropGetDbl(VD_CIRCLE_X, m_iIndex);
		m_dCoord.y	= vlPropGetDbl(VD_CIRCLE_Y, m_iIndex);
		m_dRadius	= vlPropGetDbl(VD_CIRCLE_R, m_iIndex);
	}
	else
	{
		vlPropPutDbl(VD_CIRCLE_X, m_iIndex, m_dCoord.x	);
		vlPropPutDbl(VD_CIRCLE_Y, m_iIndex, m_dCoord.y	);
		vlPropPutDbl(VD_CIRCLE_R, m_iIndex, m_dRadius	);
	}
}

const CvlCircle& CvlCircle::operator = (const CvlCircle& Src)
{
	m_dCoord	= Src.m_dCoord;	
	m_dRadius	= Src.m_dRadius;

	CvlEntity::operator =(Src);

	return *this;
}

///////////////////////////////////////////////////////////////////////////////

void CvlArc::AddToCanvas()
{
	m_iIndex = vlAddArc(m_dCoordCenter.x,	m_dCoordCenter.y, 
		m_dRadius, m_dAngleStart, m_dAngleInclude);

	GetBasic();
	UpdateData(false);
}

void CvlEllipse::AddToCanvas()
{
	m_iIndex = vlAddEllipse(m_dCoord.x, m_dCoord.y, m_dRadiusHorz, m_dRadiusVert, m_dAngle);
	GetBasic();

	UpdateData(false);
}

void CvlCircle::AddToCanvas()
{
	m_iIndex = vlAddCircle(m_dCoord.x, m_dCoord.y, m_dRadius);
	GetBasic();

	UpdateData(false);
}

void CvlRect::AddToCanvas()
{
	m_iIndex = vlAddRect(m_dCoord.x, m_dCoord.y, m_dWidth, m_dHeight, m_dAngle, m_dRadius);
	GetBasic();

	UpdateData(true);
}

void CvlText::AddToCanvas()
{
	m_iIndex = vlAddText(m_dCoord.x, m_dCoord.y, m_pszTxt);

	GetBasic();

	UpdateData(false);
}

void CvlPoly::AddToCanvas()
{
	vlPolylineBegin();

	for (int i=0; i<m_iNoVer; i++)
		vlVertex( m_pdVert[i].x, m_pdVert[i].y );

	m_iIndex = vlAddPolyline(m_iStSmooth, m_bClosed);

	GetBasic();
	
	UpdateData(false);
}

void CvlLine::AddToCanvas()
{
	m_iIndex = vlAddLine(m_dLine1.x, m_dLine1.y, m_dLine2.x, m_dLine2.y);
	GetBasic();

	UpdateData(false);
}

void CvlPoint::AddToCanvas()
{
	m_iIndex = vlAddPoint(m_dCoord.x, m_dCoord.y);
	GetBasic();

	UpdateData(false);
}

void CvlEntity::GetBasic()
{
	m_hID			= vlPropGetInt( VD_ENT_HANDLE     , m_iIndex );
	m_iKey			= vlPropGetInt( VD_ENT_KEY        , m_iIndex );
	m_iLayer		= vlPropGetInt( VD_ENT_LAYER      , m_iIndex );
}


/////////////////////////////////////////////////////////////////////////////////////////

bool CvlCircle::Offset(double dSize)
{
	if (m_dRadius + dSize > 0)
	{
		m_dRadius += dSize;
		UpdateData(false);

		return true;
	}

	return false;
}

bool CvlLine::Offset(double dSize)
{
	double dSrcDist = sqrt( pow( m_dLine2.x - m_dLine1.x, 2 ) + pow(m_dLine2.y - m_dLine1.y, 2) );

	double dSin = (m_dLine2.y - m_dLine1.y) / dSrcDist;
	double dCos = -(m_dLine2.x - m_dLine1.x) / dSrcDist;

	double dX = dSize * dSin;
	double dY = dSize * dCos;

	/////////////////////////////////////

	m_dLine1.x += dX;
	m_dLine1.y += dY;
	m_dLine2.x += dX;
	m_dLine2.y += dY;

	UpdateData(false);
	
	return true;
}

bool CvlPoly::Offset(double dSize)
{
	VLPOINT*	pdVertNew	= new VLPOINT[m_iNoVer];
	VLPOINT		PtEdge[3];

	memset(pdVertNew, 0, m_iNoVer*sizeof(VLPOINT));

	// Center 점이 Polygon 내부에 있는지 검사. 

	LPPOINT pPtWin = new POINT[m_iNoVer];

	for (int i=0; i<m_iNoVer; i++)
		vlCoordDwgToWin(m_pdVert[i].x, m_pdVert[i].y, (int*)&(pPtWin[i].x), (int*)&pPtWin[i].y);

	CRgn Rgn;
	Rgn.CreatePolygonRgn(pPtWin, m_iNoVer, ALTERNATE);

	// 시작점에 대한 처리.
	PtEdge[0] = (m_pdVert[m_iNoVer-1].x !=m_pdVert[0].x || m_pdVert[m_iNoVer-1].y !=m_pdVert[0].y) ? m_pdVert[m_iNoVer-1] : m_pdVert[m_iNoVer-2];
	PtEdge[1] = m_pdVert[0];
	PtEdge[2] = m_pdVert[1];

	CvlPoly::FindCoordAngle(PtEdge[0], PtEdge[1], PtEdge[2], &Rgn, dSize, &pdVertNew[0] );

	// 끝점에 대한 처리.
	PtEdge[0] = m_pdVert[m_iNoVer-2];
	PtEdge[1] = m_pdVert[m_iNoVer-1];
	PtEdge[2] = (PtEdge[1].x !=m_pdVert[0].x || PtEdge[1].y !=m_pdVert[0].y) ? m_pdVert[0] : PtEdge[2] = m_pdVert[1];	

	CvlPoly::FindCoordAngle(PtEdge[0], PtEdge[1], PtEdge[2], &Rgn, dSize, &pdVertNew[m_iNoVer-1] );
	
	// 사이 점들에 대한 처리.
	for (i=0; i<m_iNoVer-2; i++)
		CvlPoly::FindCoordAngle(m_pdVert[i], m_pdVert[i+1], m_pdVert[i+2], &Rgn, dSize, &pdVertNew[i+1] );

	// 아까 만든 Rgn 제거.
	Rgn.DeleteObject();
	delete[] pPtWin;

	// 현재 선택된 점에 대한 처리.
	m_dCurrVerCoord = pdVertNew[m_iCurrVer];

	// Vertex 배열 바꾸기.
	delete[] m_pdVert;
	m_pdVert		= pdVertNew;

	UpdateData(false);

	return true;
}

bool CvlRect::Offset(double dSize)
{
	dSize *= 2;

	if (m_dHeight + dSize > 0 &&
		m_dWidth + dSize > 0)
	{
		m_dHeight	+= dSize;
		m_dWidth	+= dSize;
		
		UpdateData(false);
		return true;
	}

	return false;
}

bool CvlText::Offset(double /*dSize*/)
{
	return true;
}

bool CvlArc::Offset(double dSize)
{
	if (m_dRadius + dSize > 0 &&
		m_dRadiusVert + dSize > 0 &&
		m_dRadiusHorz + dSize > 0)
	{
		m_dRadius		+= dSize;
		m_dRadiusHorz	+= dSize;
		m_dRadiusVert	+= dSize;
	
		UpdateData(false);

		return true;
	}

	return false;	
}

bool CvlEllipse::Offset(double dSize)
{
	if (m_dRadiusHorz + dSize > 0 &&
		m_dRadiusVert + dSize > 0 )
	{
		m_dRadiusHorz += dSize;
		m_dRadiusVert += dSize;

		UpdateData(false);

		return true;
	}
	return false;
}


bool CvlArc::Resize(VLPOINT dOrigin, double dRatioX, double dRatioY)
{
	m_dCoordCenter.x= dOrigin.x - (dOrigin.x - m_dCoordCenter.x)*dRatioX/100;
	m_dCoordCenter.y= dOrigin.y - (dOrigin.y - m_dCoordCenter.y)*dRatioY/100;

	m_dCoordStart.x = dOrigin.x - (dOrigin.x - m_dCoordStart.x)*dRatioX/100;
	m_dCoordStart.y = dOrigin.y - (dOrigin.y - m_dCoordStart.y)*dRatioY/100;
	
	m_dCoordEnd.x	= dOrigin.x - (dOrigin.x - m_dCoordEnd.x)*dRatioX/100;
	m_dCoordEnd.y	= dOrigin.y - (dOrigin.y - m_dCoordEnd.y)*dRatioY/100;

	m_dRadius		= sqrt( pow(m_dCoordCenter.x - m_dCoordStart.x, 2) + pow(m_dCoordCenter.y - m_dCoordStart.y, 2) );

	m_dRadiusHorz	= m_dRadiusVert = m_dRadius;

	UpdateData(false);

	return true;
}

bool CvlRect::Resize(VLPOINT dOrigin, double dRatioX, double dRatioY)
{
	double dNewLeft		= dOrigin.x - ( dOrigin.x - ( m_dCoord.x - m_dWidth/2 ) ) * dRatioX / 100;
	double dNewRight	= dOrigin.x + ( ( m_dCoord.x + m_dWidth/2) - dOrigin.x ) * dRatioX / 100;

	double dNewTop		= dOrigin.y + ( ( m_dCoord.y + m_dHeight/2) - dOrigin.y ) * dRatioY / 100;
	double dNewBottom	= dOrigin.y - ( dOrigin.y - ( m_dCoord.y - m_dHeight/2 ) ) * dRatioY / 100;

	m_dHeight	= (dNewTop - dNewBottom);
	m_dWidth	= (dNewRight - dNewLeft);

	m_dCoord.x	= (dNewRight + dNewLeft)/ 2;
	m_dCoord.y	= (dNewBottom+ dNewTop) / 2;

	UpdateData( false );

	return true;
}


bool CvlCircle::Resize(VLPOINT dOrigin, double dRatioX, double dRatioY)
{
	double dLeft, dTop, dRight, dBottom;
	GetRect(&dLeft, &dTop, &dRight, &dBottom);

	double dTopNew	= (dTop - dOrigin.y)*dRatioY/100 + dOrigin.y;
	double dBtmNew	= dOrigin.y - (dOrigin.y - dBottom)*dRatioY/100;
	double dRightNew= (dRight - dOrigin.x)*dRatioX/100 + dOrigin.x;
	double dLeftNew	= dOrigin.x - (dOrigin.x - dLeft)*dRatioX/100;

	if ( dRatioX - dRatioY !=0.0)//원을 지우고 Ellipse 를 넣는다.
	{
		CvlEllipse* pEllipse = new CvlEllipse;

		(*(CvlEntity*)pEllipse) = (*(CvlEntity*)this);
		
		pEllipse->m_dCoord.x	= (dRightNew + dLeftNew)/2;
		pEllipse->m_dCoord.y	= (dTopNew + dBtmNew)/2;

		pEllipse->m_dRadiusHorz	= (dRightNew - dLeftNew)/2;
		pEllipse->m_dRadiusVert	= (dTopNew - dBtmNew)/2;
		
		pEllipse->AddToCanvas();
		
		Erase();// 원을 지운다.
		
		delete pEllipse;
	}
	else// 원의 형태를 유지한다.
	{
		m_dCoord.x		= (dRightNew + dLeftNew)/2;
		m_dCoord.y		= (dTopNew + dBtmNew)/2;

		m_dRadius		= (dRightNew - dLeftNew)/2;

		UpdateData(false);
	}

	return true;
}

bool CvlEllipse::Resize(VLPOINT dOrigin, double dRatioX, double dRatioY)
{	
	double dNewLeft		= dOrigin.x - ( dOrigin.x - ( m_dCoord.x - m_dRadiusHorz ) ) * dRatioX / 100;
	double dNewRight	= dOrigin.x + ( ( m_dCoord.x + m_dRadiusHorz) - dOrigin.x ) * dRatioX / 100;

	double dNewTop		= dOrigin.y + ( ( m_dCoord.y + m_dRadiusVert ) - dOrigin.y ) * dRatioY / 100;
	double dNewBottom	= dOrigin.y - ( dOrigin.y - ( m_dCoord.y - m_dRadiusVert ) ) * dRatioY / 100;

	m_dRadiusVert	= (dNewTop - dNewBottom)/2;
	m_dRadiusHorz	= (dNewRight - dNewLeft)/2;

	m_dCoord.x		= (dNewRight + dNewLeft)/ 2;
	m_dCoord.y		= (dNewBottom+ dNewTop) / 2;

	UpdateData( false );

	return true;
}

bool CvlLine::Resize(VLPOINT dOrigin, double dRatioX, double dRatioY)
{
	m_dLine1.x = dOrigin.x - (dOrigin.x - m_dLine1.x) * dRatioX / 100;
	m_dLine1.y = dOrigin.y - (dOrigin.y - m_dLine1.y) * dRatioY / 100;

	m_dLine2.x = dOrigin.x - (dOrigin.x - m_dLine2.x) * dRatioX / 100;
	m_dLine2.y = dOrigin.y - (dOrigin.y - m_dLine2.y) * dRatioY / 100;

	UpdateData(false);

	return true;
}

bool CvlPoint::Resize(VLPOINT /*dOrigin*/, double /*dRatioX*/, double /*dRatioY*/)
{
	return true;
}

bool CvlPoly::Resize(VLPOINT dOrigin, double dRatioX, double dRatioY)
{
	for (int i=0; i<m_iNoVer; i++)
	{
		m_pdVert[i].x = dOrigin.x + (m_pdVert[i].x  - dOrigin.x)*dRatioX/100;
		m_pdVert[i].y = dOrigin.y + (m_pdVert[i].y  - dOrigin.y)*dRatioY/100;

		if (i==m_iCurrVer)
			m_dCurrVerCoord = m_pdVert[i];
	}

	UpdateData(false);

	return true;
}

bool CvlText::Resize(VLPOINT /*dOrigin*/, double /*dRatioX*/, double /*dRatioY*/)
{
	return true;
}

void CvlEntity::Erase()
{
	vlErase(m_iIndex);
}

bool CvlPoly::FindCoordDist(VLPOINT PtSrc1, VLPOINT PtSrc2, double Dist, VLPOINT *pPtDst)
{
	// 기울기.
	double SrcDist = sqrt( pow( PtSrc2.x - PtSrc1.x , 2 ) + pow( PtSrc2.y - PtSrc1.y, 2 ) );

	double dCos = ( PtSrc2.x - PtSrc1.x ) / SrcDist ;
	double dSin	= ( PtSrc2.y - PtSrc1.y ) / SrcDist ;
	
	double dX = Dist * dCos;
	double dY = Dist * dSin;

	pPtDst->x = PtSrc2.x + dX;
	pPtDst->y = PtSrc2.y + dY;

	return true;
}

// Poly 의 제대로된 Offset 을 위해서.

bool CvlPoly::FindLineEq(VLPOINT Pt1, VLPOINT Pt2, VLPOINT PtCenter, double dSize, double* pDstDelta, double* pDstSlice)
{
	if ( (Pt2.x - Pt1.x) == 0.0)
		return false;

	double DeltaA	= (Pt2.y - Pt1.y) / (Pt2.x - Pt1.x);

	VLPOINT PtA		= {	(Pt2.x + Pt1.x) / 2,
						(Pt2.y + Pt1.y) / 2 };

	double Theta	= atan(-1 / DeltaA);

	VLPOINT PtB1	= { (PtA.x + cos(Theta) * dSize), 
						(PtA.y + sin(Theta) * dSize) };

	VLPOINT PtB2	= { (PtA.x - cos(Theta) * dSize), 
						(PtA.y - sin(Theta) * dSize) };

	*pDstDelta	= DeltaA;

	double Dist2 = sqrt( pow( PtB2.x-PtCenter.x , 2 ) + pow( PtB2.y-PtCenter.y , 2 ) );
	double Dist1 = sqrt( pow( PtB1.x-PtCenter.x , 2 ) + pow( PtB1.y-PtCenter.y , 2 ) );

	if ( ( dSize > 0 && Dist2 > Dist1 ) ||
		 ( dSize < 0 && Dist2 < Dist1 ) )
		*pDstSlice	= PtB2.y - DeltaA * PtB2.x;
	else
		*pDstSlice	= PtB1.y - DeltaA * PtB1.x;

	return true;
}


bool CvlPoly::FindCoordAngle(VLPOINT PtSrc1, VLPOINT PtSrc2, VLPOINT PtSrc3, /*VLPOINT PtCenter,*/ CRgn* pRgn, double Dist, VLPOINT *pPtDst)
{
	double Delta1, Delta2;
	double SliceY1, SliceY2;

	// 어거지...ㅡ.ㅡ
	VLPOINT dCenter = { (PtSrc1.x + PtSrc2.x + PtSrc3.x)/3, (PtSrc1.y + PtSrc2.y + PtSrc3.y)/3 };
	VLPOINT dCenter2 = { (dCenter.x+PtSrc2.x)/2 , (dCenter.y+PtSrc2.y)/2 };

	POINT PtCenter, PtCenter2;
	
	vlCoordDwgToWin( dCenter.x, dCenter.y, (int*)&PtCenter.x, (int*)&PtCenter.y);
	vlCoordDwgToWin( dCenter2.x, dCenter2.y, (int*)&PtCenter2.x, (int*)&PtCenter2.y);

	if (pRgn->PtInRegion(PtCenter)==FALSE && pRgn->PtInRegion(PtCenter2)==FALSE)
		Dist = -Dist;
		
	CvlPoly::FindLineEq(PtSrc1, PtSrc2, dCenter, Dist, &Delta1, &SliceY1);
	CvlPoly::FindLineEq(PtSrc2, PtSrc3, dCenter, Dist, &Delta2, &SliceY2);

	// 직각에서 기울기가 계산이 안되는 경우에 대한 처리.
	if (PtSrc1.x != PtSrc2.x && PtSrc2.x != PtSrc3.x)
	{
		pPtDst->x = (SliceY2 - SliceY1)/(Delta1 - Delta2);
		pPtDst->y = Delta1*pPtDst->x + SliceY1;
	}
	else if (PtSrc1.x == PtSrc2.x && PtSrc2.x != PtSrc3.x)
	{
		pPtDst->x = (PtCenter.x > PtSrc1.x) ? PtSrc1.x - Dist : PtSrc1.x + Dist;
		pPtDst->y = Delta2*pPtDst->x + SliceY2;
	}		
	else if (PtSrc1.x != PtSrc2.x && PtSrc2.x == PtSrc3.x)
	{
		pPtDst->x = (PtCenter.x > PtSrc2.x) ? PtSrc2.x - Dist : PtSrc2.x + Dist;
		pPtDst->y = Delta1*pPtDst->x + SliceY1;
	}
	// 직각이 아니어서 기울기가 계산된 경우.
	else if (PtSrc1.x == PtSrc2.x && PtSrc2.x == PtSrc3.x)
	{
		pPtDst->x = PtSrc1.x;
		pPtDst->y = PtSrc2.y;
	}
	else
	{
		TRACE("\nFindCoordAngle() - 계산되지 않은 경우\n");
//		ASSERT(false);
		return false;
	}

	return true;
}


//nIndex 위치에 Pt 넣기.
void CvlPoly::InsertVertex(int nIndex, VLPOINT Pt)
{
//	ASSERT( nIndex>=0 && nIndex <= m_iNoVer );

	VLPOINT* pdVertNew = new VLPOINT[m_iNoVer+1];
	
	if (nIndex>0)
		memcpy( pdVertNew, m_pdVert, sizeof(VLPOINT)* nIndex );

	pdVertNew[nIndex] = Pt;

	if (nIndex<m_iNoVer)
		memcpy( pdVertNew + (nIndex+1), m_pdVert + nIndex, m_iNoVer-nIndex );

	m_iNoVer++;

	delete[] m_pdVert;
	
	m_pdVert = pdVertNew;

	UpdateData(false);
}


bool CvlArc::GetCenter(VLPOINT* pdCenter)
{
//	ASSERT(pdCenter!=NULL);

	*pdCenter = m_dCoordCenter;
	return true;
}

bool CvlEllipse::GetCenter(VLPOINT* pdCenter)
{
//	ASSERT(pdCenter!=NULL);

	*pdCenter = m_dCoord;
	return true;
}
bool CvlLine::GetCenter(VLPOINT* pdCenter)
{
	pdCenter->x = (m_dLine2.x + m_dLine1.x)/2;
	pdCenter->y = (m_dLine2.y + m_dLine1.y)/2;

	return true;
}
bool CvlPoint::GetCenter(VLPOINT* pdCenter)
{
//	ASSERT(pdCenter!=NULL);

	*pdCenter = m_dCoord;
	return true;
}
bool CvlRect::GetCenter(VLPOINT* pdCenter)
{
//	ASSERT(pdCenter!=NULL);

	*pdCenter = m_dCoord;
	return true;
}

bool CvlText::GetCenter(VLPOINT* pdCenter)
{
//	ASSERT(pdCenter!=NULL);

	*pdCenter = m_dCoord;
	return true;
}

bool CvlCircle::GetCenter(VLPOINT* pdCenter)
{
//	ASSERT(pdCenter!=NULL);

	*pdCenter = m_dCoord;
	return true;
}

bool CvlPoly::GetCenter(VLPOINT *pdCenter)
{
//	ASSERT(pdCenter!=NULL);

	UpdateData(true);

	pdCenter->x = (m_dExtLeft+m_dExtRight)/2;
	pdCenter->y = (m_dExtBottom+m_dExtTop)/2;

	return true;
}

bool CvlPoly::GetCOG(VLPOINT* pdCenter)
{
//	ASSERT( pdCenter!=NULL );

	pdCenter->x = 0.0;
	pdCenter->y = 0.0;

	for (int i=0; i<m_iNoVer; i++)
	{
		pdCenter->x += m_pdVert[i].x;
		pdCenter->y += m_pdVert[i].y;
	}

	pdCenter->x /= m_iNoVer;
	pdCenter->y /= m_iNoVer;

	return true;
}


void CvlCircle::GetRect(double* pdLeft, double* pdTop, double* pdRight, double* pdBottom)
{
//	ASSERT(pdLeft!=NULL && pdTop!=NULL && pdRight!=NULL && pdBottom!=NULL);

	*pdLeft		= m_dCoord.x - m_dRadius;
	*pdTop		= m_dCoord.y + m_dRadius;
	*pdBottom	= m_dCoord.y - m_dRadius;
	*pdRight	= m_dCoord.x + m_dRadius;
}

void CvlEntity::GetOuterRect(double* pdLeft, double* pdTop, double* pdRight, double* pdBottom)
{
//	ASSERT(pdLeft!=NULL && pdTop!=NULL && pdRight!=NULL && pdBottom!=NULL);

	*pdLeft		= m_dExtLeft;
	*pdRight	= m_dExtRight;
	*pdTop		= m_dExtTop;
	*pdBottom	= m_dExtBottom;
}



CvlHatch::CvlHatch()
{
	m_iStyle = 0;
	m_dAngle = 0.0;
	m_dScale = 0.0;
}

CvlHatch::CvlHatch(int nIndex)
{
	m_iIndex = nIndex;

	UpdateData(true);
}

CvlHatch::~CvlHatch()
{

}

void CvlHatch::UpdateData(bool bSaveAndValidate)
{
	CvlEntity::UpdateData(bSaveAndValidate);

	if (bSaveAndValidate)
	{
		m_iStyle	= vlPropGetInt( VD_HATCH_STYLE	, m_iIndex );
		m_dScale	= vlPropGetDbl( VD_HATCH_SCALE	, m_iIndex );
		m_dAngle	= vlPropGetDbl( VD_HATCH_ANGLE	, m_iIndex );
	}
	else
	{
		vlPropPutInt( VD_HATCH_STYLE	, m_iIndex , m_iStyle );
		vlPropPutDbl( VD_HATCH_SCALE	, m_iIndex , m_dScale );
		vlPropPutDbl( VD_HATCH_ANGLE	, m_iIndex , m_dAngle );
	}
}

const CvlHatch& CvlHatch::operator = (const CvlHatch& Src)
{
	CvlEntity::operator =(Src);

	m_iStyle = Src.m_iStyle;
	m_dScale = Src.m_dScale;
	m_dAngle = Src.m_dAngle;

	return *this;
}

void CvlHatch::AddToCanvas()
{
	vlAddHatch(m_iStyle, m_dScale, m_dAngle);
}

bool CvlHatch::Offset(double /*dSize*/)
{
	return true;
}

bool CvlHatch::Resize(VLPOINT /*dOrigin*/, double /*dRatioX*/, double /*dRatioY*/)
{
	return true;
}

bool CvlHatch::GetCenter(VLPOINT* /*pdCenter*/)
{
	return true;
}


CvlBlock::CvlBlock()
{
	m_dPtInsertion.x	= 0.0;
	m_dPtInsertion.y	= 0.0;
	m_iIndexBlockDef	= 0;
	m_dAngle			= 0.0;
	m_dScaleX			= 0.0;
	m_dScaleY			= 0.0;
	m_dScale			= 0.0;
	
	memset(m_pszName, 0, sizeof(char)*32);
}

CvlBlock::CvlBlock(int nIndex)
{
	m_iIndex = nIndex;

	UpdateData(true);
}

CvlBlock::~CvlBlock()
{

}

void CvlBlock::UpdateData(bool bSaveAndValidate)
{
	CvlEntity::UpdateData( bSaveAndValidate );

	if (bSaveAndValidate)
	{
		m_dPtInsertion.x	= vlPropGetDbl ( VD_INSBLK_X		, m_iIndex );
		m_dPtInsertion.y	= vlPropGetDbl ( VD_INSBLK_Y		, m_iIndex );
		m_iIndexBlockDef	= vlPropGetInt ( VD_INSBLK_BLOCK	, m_iIndex );
		m_dAngle			= vlPropGetDbl ( VD_INSBLK_ANGLE	, m_iIndex );
		m_dScaleX			= vlPropGetDbl ( VD_INSBLK_SCALEX	, m_iIndex );
		m_dScaleY			= vlPropGetDbl ( VD_INSBLK_SCALEY	, m_iIndex );
		m_dScale			= vlPropGetDbl ( VD_INSBLK_SCALE	, m_iIndex );

		m_dBlockWidth		= vlPropGetDbl ( VD_BLOCK_WIDTH     , m_iIndexBlockDef );
		m_dBlockHeight		= vlPropGetDbl ( VD_BLOCK_HEIGHT    , m_iIndexBlockDef );

	//	int m_nNumObject	= vlPropGetInt ( VD_BLOCK_N_REF     , m_iIndexBlockDef ); // number of objects that use this block definition
//		int m_iBlockID		= vlPropGetInt ( VD_BLOCK_ID        , m_iIndexBlockDef );
//		int m_iIndexBlock	= vlPropGetInt ( VD_BLOCK_INDEX     , m_iIndexBlockDef );

		m_dBlockBase.x		= vlPropGetDbl ( VD_BLOCK_XBASE, m_iIndexBlockDef );
		m_dBlockBase.y		= vlPropGetDbl ( VD_BLOCK_YBASE, m_iIndexBlockDef );

		vlPropGet(VD_BLOCK_NAME, m_iIndexBlockDef, m_pszName);
	}
	else
	{
		vlPropPutDbl ( VD_INSBLK_X		, m_iIndex , m_dPtInsertion.x	); 
		vlPropPutDbl ( VD_INSBLK_Y		, m_iIndex , m_dPtInsertion.y	); 
		vlPropPutInt ( VD_INSBLK_BLOCK	, m_iIndex , m_iIndexBlockDef	); 
		vlPropPutDbl ( VD_INSBLK_ANGLE	, m_iIndex , m_dAngle			); 			
		vlPropPutDbl ( VD_INSBLK_SCALEX	, m_iIndex , m_dScaleX			); 		
		vlPropPutDbl ( VD_INSBLK_SCALEY	, m_iIndex , m_dScaleY			); 	
		vlPropPutDbl ( VD_INSBLK_SCALE	, m_iIndex , m_dScale			); 

		vlPropPutDbl ( VD_BLOCK_WIDTH	, m_iIndexBlockDef , m_dBlockWidth	);
		vlPropPutDbl ( VD_BLOCK_HEIGHT, m_iIndexBlockDef , m_dBlockHeight	);

		vlPropPutDbl ( VD_BLOCK_XBASE	, m_iIndexBlockDef , m_dBlockBase.x	);
		vlPropPutDbl ( VD_BLOCK_YBASE	, m_iIndexBlockDef , m_dBlockBase.y	);

		vlPropPut(VD_BLOCK_NAME, m_iIndexBlockDef, m_pszName);
	}
}

const CvlBlock& CvlBlock::operator = (const CvlBlock& Src)
{
	CvlEntity::operator = (Src);

	m_dPtInsertion.x	= Src.m_dPtInsertion.x;
	m_dPtInsertion.y	= Src.m_dPtInsertion.y; 
	m_iIndexBlockDef	= Src.m_iIndexBlockDef; 
	m_dAngle			= Src.m_dAngle; 
	m_dScaleX			= Src.m_dScaleX; 
	m_dScaleY			= Src.m_dScaleY; 
	m_dScale			= Src.m_dScale; 

	return *this;
}

void CvlBlock::AddToCanvas()
{

}

bool CvlBlock::Offset(double /*dSize*/)
{

	return true;
}

bool CvlBlock::Resize(VLPOINT /*dOrigin*/, double /*dRatioX*/, double /*dRatioY*/)
{

	return true;
}

bool CvlBlock::GetCenter(VLPOINT* /*pdCenter*/)
{

	return true;
}

//////////////////////////////////////////////////////////////////////////

CvlDim::CvlDim()
{
	m_iStyle	= 0;
	m_iDimType	= 0;
	m_bStatic	= FALSE;
	m_dText.x	= 0.0;
	m_dText.y	= 0.0;

	memset(m_szStaticValue, 0, sizeof(char)*MAX_PATH);
}

CvlDim::CvlDim(int iIndex)
{
	m_iIndex = iIndex;

	UpdateData(true);
}

CvlDim::~CvlDim()
{

}

void CvlDim::UpdateData(bool bSaveAndValidate)
{
	CvlEntity::UpdateData(bSaveAndValidate);

	if (bSaveAndValidate)
	{
		m_iStyle	= vlPropGetInt( VD_DIM_STYLE,	m_iIndex );
		m_iDimType	= vlPropGetInt( VD_DIM_TYPE,	m_iIndex );
		m_bStatic	= vlPropGetInt( VD_DIM_STATIC,	m_iIndex );
		m_dText.x	= vlPropGetDbl( VD_DIM_VALUE,	m_iIndex );
		m_dText.y	= vlPropGetDbl( VD_DIM_XTEXT,	m_iIndex );
		
		vlPropGet(VD_DIM_VALUE, m_iIndex, m_szStaticValue);
	}
	else
	{
		vlPropPutInt( VD_DIM_STYLE,	m_iIndex, m_iStyle );
		vlPropPutInt( VD_DIM_TYPE,	m_iIndex, m_iDimType );
		vlPropPutInt( VD_DIM_STATIC,m_iIndex, m_bStatic );
		vlPropPutDbl( VD_DIM_VALUE,	m_iIndex, m_dText.x );
		vlPropPutDbl( VD_DIM_XTEXT,	m_iIndex, m_dText.y );

		vlPropPut(VD_DIM_VALUE, m_iIndex, m_szStaticValue);
	}
}

const CvlDim& CvlDim::operator = (const CvlDim& Src)
{
	CvlEntity::operator =(Src);

	strcpy(m_szStaticValue, Src.m_szStaticValue);

	m_iStyle	= Src.m_iStyle;
	m_iDimType	= Src.m_iDimType;
	m_bStatic	= Src.m_bStatic;
	m_dText.x	= Src.m_dText.x;
	m_dText.y	= Src.m_dText.y;

	return *this;
}


void CvlDim::AddToCanvas()
{

}


CvlDimLinear::CvlDimLinear()
{
	m_dPt1.x = 0.0;
	m_dPt1.y = 0.0;
	m_dPt2.x = 0.0;
	m_dPt2.y = 0.0;
	m_dOffset= 0.0;
	m_dPos.x = 0.0;
	m_dPos.y = 0.0;
}

CvlDimLinear::CvlDimLinear(int iIndex)
{
	m_iIndex = iIndex;

	UpdateData(true);
}

CvlDimLinear::~CvlDimLinear()
{

}

void CvlDimLinear::UpdateData(bool bSaveAndValidate)
{
	CvlDim::UpdateData(bSaveAndValidate);

	if (bSaveAndValidate)
	{
		m_dPt1.x = vlPropGetDbl( VD_DIM_L_X1	, m_iIndex );
		m_dPt1.y = vlPropGetDbl( VD_DIM_L_Y1	, m_iIndex );
		m_dPt2.x = vlPropGetDbl( VD_DIM_L_X2	, m_iIndex );
		m_dPt2.y = vlPropGetDbl( VD_DIM_L_Y2	, m_iIndex );
		m_dOffset= vlPropGetDbl( VD_DIM_L_OFFSET, m_iIndex );
		m_dPos.x = vlPropGetDbl( VD_DIM_L_XLINE	, m_iIndex );
		m_dPos.y = vlPropGetDbl( VD_DIM_L_YLINE	, m_iIndex );
	}
	else
	{
		vlPropPutDbl( VD_DIM_L_X1	 , m_iIndex , m_dPt1.x );
		vlPropPutDbl( VD_DIM_L_Y1	 , m_iIndex , m_dPt1.y );
		vlPropPutDbl( VD_DIM_L_X2	 , m_iIndex , m_dPt2.x );
		vlPropPutDbl( VD_DIM_L_Y2	 , m_iIndex , m_dPt2.y );
		vlPropPutDbl( VD_DIM_L_OFFSET, m_iIndex , m_dOffset);
		vlPropPutDbl( VD_DIM_L_XLINE , m_iIndex , m_dPos.x );
		vlPropPutDbl( VD_DIM_L_YLINE , m_iIndex , m_dPos.y );
	}
}

const CvlDimLinear& CvlDimLinear::operator = (const CvlDimLinear& Src)
{
	CvlDim::operator =(Src);

	m_dPt1.x = Src.m_dPt1.x ;
	m_dPt1.y = Src.m_dPt1.y ;
	m_dPt2.x = Src.m_dPt2.x ;
	m_dPt2.y = Src.m_dPt2.y ;
	m_dOffset= Src.m_dOffset;
	m_dPos.x = Src.m_dPos.x ;
	m_dPos.y = Src.m_dPos.y ;

	return *this;
}

void CvlDimLinear::AddToCanvas()
{
	/*
	switch(m_iDimType)
	{
	case VL_DIM_HOR:break;
	case VL_DIM_VER:break;
	case VL_DIM_PAR:break;
	}
	*/
}


////////////////////////////////////////////////////////////

CvlDimAngula::CvlDimAngula()
{
	m_dPtCenter.x	= 0.0;
	m_dPtCenter.y	= 0.0;
	m_dPt1.x		= 0.0;		
	m_dPt1.y		= 0.0;		
	m_dPt2.x		= 0.0;
	m_dPt2.y		= 0.0;
	m_dRadius		= 0.0;	
}

CvlDimAngula::CvlDimAngula(int iIndex)
{
	m_iIndex = iIndex;

	UpdateData(true);
}

CvlDimAngula::~CvlDimAngula()
{

}

void	CvlDimAngula::UpdateData(bool bSaveAndValidate)
{
	CvlDim::UpdateData(bSaveAndValidate);

	if (bSaveAndValidate)
	{
		m_dPtCenter.x	= vlPropGetDbl( VD_DIM_A_XCEN	, m_iIndex );
		m_dPtCenter.y	= vlPropGetDbl( VD_DIM_A_YCEN	, m_iIndex );
		m_dPt1.x		= vlPropGetDbl( VD_DIM_A_X1		, m_iIndex );
		m_dPt1.y		= vlPropGetDbl( VD_DIM_A_Y1		, m_iIndex );
		m_dPt2.x		= vlPropGetDbl( VD_DIM_A_X2		, m_iIndex );
		m_dPt2.y		= vlPropGetDbl( VD_DIM_A_Y2		, m_iIndex );
		m_dRadius		= vlPropGetDbl( VD_DIM_A_RADIUS	, m_iIndex );
	}
	else
	{
		vlPropPutDbl( VD_DIM_A_XCEN		, m_iIndex , m_dPtCenter.x	);
		vlPropPutDbl( VD_DIM_A_YCEN		, m_iIndex , m_dPtCenter.y	);
		vlPropPutDbl( VD_DIM_A_X1		, m_iIndex , m_dPt1.x		);
		vlPropPutDbl( VD_DIM_A_Y1		, m_iIndex , m_dPt1.y		);
		vlPropPutDbl( VD_DIM_A_X2		, m_iIndex , m_dPt2.x		);
		vlPropPutDbl( VD_DIM_A_Y2		, m_iIndex , m_dPt2.y		);
		vlPropPutDbl( VD_DIM_A_RADIUS	, m_iIndex , m_dRadius		);
	}
}

const	CvlDimAngula& CvlDimAngula::operator = (const CvlDimAngula& Src)
{
	CvlDim::operator =(Src);

	m_dPtCenter.x	= Src. m_dPtCenter.x;
	m_dPtCenter.y	= Src. m_dPtCenter.y;
	m_dPt1.x		= Src. m_dPt1.x		;
	m_dPt1.y		= Src. m_dPt1.y		;
	m_dPt2.x		= Src. m_dPt2.x		;
	m_dPt2.y		= Src. m_dPt2.y		;
	m_dRadius		= Src. m_dRadius	;

	return *this;
}

void	CvlDimAngula::AddToCanvas()
{
	vlAddDimAng     (m_dPtCenter.x, m_dPtCenter.y, m_dPt1.x, m_dPt1.y, m_dPt2.x, m_dPt2.y, m_dRadius);
}

////////////////////////////////////////////////////////////

CvlDimRadial::CvlDimRadial()
{
	m_dPtCenter.x	= 0.0;
	m_dPtCenter.y	= 0.0;
	m_dPtRadial.x	= 0.0;
	m_dPtRadial.y	= 0.0;
	m_dOffset		= 0.0;
}

CvlDimRadial::CvlDimRadial(int iIndex)
{
	m_iIndex = iIndex;

	UpdateData(true);
}

CvlDimRadial::~CvlDimRadial()
{

}

void	CvlDimRadial::UpdateData(bool bSaveAndValidate)
{
	CvlDim::UpdateData(bSaveAndValidate);

	if (bSaveAndValidate)
	{
		m_dPtCenter.x	= vlPropGetDbl( VD_DIM_R_XCEN	, m_iIndex );
		m_dPtCenter.y	= vlPropGetDbl( VD_DIM_R_YCEN	, m_iIndex );
		m_dPtRadial.x	= vlPropGetDbl( VD_DIM_R_XRAD	, m_iIndex );
		m_dPtRadial.y	= vlPropGetDbl( VD_DIM_R_YRAD	, m_iIndex );
		m_dOffset		= vlPropGetDbl( VD_DIM_R_OFFSET	, m_iIndex );
	}
	else
	{
		vlPropPutDbl( VD_DIM_R_XCEN		, m_iIndex , m_dPtCenter.x );
		vlPropPutDbl( VD_DIM_R_YCEN		, m_iIndex , m_dPtCenter.y );
		vlPropPutDbl( VD_DIM_R_XRAD		, m_iIndex , m_dPtRadial.x );
		vlPropPutDbl( VD_DIM_R_YRAD		, m_iIndex , m_dPtRadial.y );
		vlPropPutDbl( VD_DIM_R_OFFSET	, m_iIndex , m_dOffset	 );
	}
}

const	CvlDimRadial& CvlDimRadial::operator = (const CvlDimRadial& Src)
{
	CvlDim::operator =(Src);

	m_dPtCenter.x	= Src.m_dPtCenter.x	; 
	m_dPtCenter.y	= Src.m_dPtCenter.y	; 
	m_dPtRadial.x	= Src.m_dPtRadial.x	; 
	m_dPtRadial.y	= Src.m_dPtRadial.y	; 
	m_dOffset		= Src.m_dOffset		; 

	return *this;
}

void	CvlDimRadial::AddToCanvas()
{
	vlAddDimRad     (m_dPtCenter.x, m_dPtCenter.y, m_dPtRadial.x, m_dPtRadial.y, m_dOffset);
}

////////////////////////////////////////////////////////////

CvlDimDiameter::CvlDimDiameter()
{
	m_dPtCenter.x	= 0.0;
	m_dPtCenter.y	= 0.0;
	m_dPtRadial.x	= 0.0;
	m_dPtRadial.y	= 0.0;
}

CvlDimDiameter::CvlDimDiameter(int iIndex)
{
	m_iIndex = iIndex;

	UpdateData(true);
}

CvlDimDiameter::~CvlDimDiameter()
{

}

void	CvlDimDiameter::UpdateData(bool bSaveAndValidate)
{
	CvlDim::UpdateData(bSaveAndValidate);

	if (bSaveAndValidate)
	{
		m_dPtCenter.x	= vlPropGetDbl( VD_DIM_D_XCEN , m_iIndex );
		m_dPtCenter.y	= vlPropGetDbl( VD_DIM_D_YCEN , m_iIndex );
		m_dPtRadial.x	= vlPropGetDbl( VD_DIM_D_XRAD , m_iIndex );
		m_dPtRadial.y	= vlPropGetDbl( VD_DIM_D_YRAD , m_iIndex );
	}
	else
	{
		vlPropPutDbl( VD_DIM_D_XCEN , m_iIndex, m_dPtCenter.x );
		vlPropPutDbl( VD_DIM_D_YCEN , m_iIndex, m_dPtCenter.y );
		vlPropPutDbl( VD_DIM_D_XRAD , m_iIndex, m_dPtRadial.x );
		vlPropPutDbl( VD_DIM_D_YRAD , m_iIndex, m_dPtRadial.y );
	}
}

const	CvlDimDiameter& CvlDimDiameter::operator = (const CvlDimDiameter& Src)
{
	CvlDim::operator =(Src);

	m_dPtCenter.x	= Src.m_dPtCenter.x;
	m_dPtCenter.y	= Src.m_dPtCenter.y;
	m_dPtRadial.x	= Src.m_dPtRadial.x;
	m_dPtRadial.y	= Src.m_dPtRadial.y;

	return *this;
}

void	CvlDimDiameter::AddToCanvas()
{
	vlAddDimDiam    ( m_dPtCenter.x, m_dPtCenter.y, m_dPtRadial.x, m_dPtRadial.y );
}

////////////////////////////////////////////////////////////

CvlDimOrdinate::CvlDimOrdinate()
{
	m_dPtOrdinate.x		= 0.0;
	m_dPtOrdinate.y		= 0.0;	
	m_bShowOrdinateY	= FALSE;
}

CvlDimOrdinate::CvlDimOrdinate(int iIndex)
{
	m_iIndex = iIndex;

	UpdateData(true);
}

CvlDimOrdinate::~CvlDimOrdinate()
{
}

void	CvlDimOrdinate::UpdateData(bool bSaveAndValidate)
{
	CvlDim::UpdateData(bSaveAndValidate);

	if (bSaveAndValidate)
	{
		m_dPtOrdinate.x		= vlPropGetDbl( VD_DIM_O_X, m_iIndex);
		m_dPtOrdinate.y		= vlPropGetDbl( VD_DIM_O_Y, m_iIndex);
		m_bShowOrdinateY	= vlPropGetInt( VD_DIM_O_ORDY, m_iIndex);
	}
	else
	{
		vlPropPutDbl( VD_DIM_O_X	, m_iIndex , m_dPtOrdinate.x );
		vlPropPutDbl( VD_DIM_O_Y	, m_iIndex , m_dPtOrdinate.y );
		vlPropPutInt( VD_DIM_O_ORDY	, m_iIndex , m_bShowOrdinateY);
	}
}

const	CvlDimOrdinate& CvlDimOrdinate::operator = (const CvlDimOrdinate& Src)
{
	CvlDim::operator =(Src);

	m_dPtOrdinate.x		= Src.m_dPtOrdinate.x ;
	m_dPtOrdinate.y		= Src.m_dPtOrdinate.y ;
	m_bShowOrdinateY	= Src.m_bShowOrdinateY;

	return *this;
}

void	CvlDimOrdinate::AddToCanvas()
{
	vlAddDimOrd     ( m_dPtOrdinate.x, m_dPtOrdinate.y, m_dText.x, m_dText.y, m_bShowOrdinateY );
}
