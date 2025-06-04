#include "StdAfx.h"
//#include "LaserWriter.h"
//#include "registerKey.h"
#include "Define.h"
#include "Resource.h"
#include "ImportDxf.h"
#include <Math.h>

//	Common Group Codes for Graphical Objects 
//	3DFACE 
//	3DSOLID 
//	ACAD_PROXY_ENTITY 
//		ARC 
//	ATTDEF 
//	ATTRIB 
//	BODY 
//		CIRCLE 
//	DIMENSION 
//		ELLIPSE 
//		HATCH 
//		IMAGE 
//	INSERT 
//	LEADER 
//		LINE 
//		LWPOLYLINE 
//		MLINE 
//		MTEXT 
//	OLEFRAME 
//	OLE2FRAME 
//		POINT 
//		POLYLINE 
//	RAY 
//	REGION 
//	SEQEND 
//	SHAPE 
//	SOLID 
//		SPLINE 
//		TEXT 
//	TOLERANCE 
//	TRACE 
//	VERTEX 
//	VIEWPORT 
//		XLINE 


CImportDXF::CImportDXF(void)
{
	m_lpLayer	= NULL;

	m_dMoveX	= 0.0;
	m_dMoveY	= 0.0;

	m_dMinX		= 99999999.0;
	m_dMinY		= 99999999.0;
	m_dMaxX		= -99999999.0;
	m_dMaxY		= -99999999.0;

	m_nColorMax	= 0xff;

	CString strPen;

	for(int nNo = 0; nNo < m_nColorMax; nNo ++)
	{
		strPen.LoadString((UINT)("펜값" + (nNo * 2)));

		m_dwTable[nNo] = (DWORD)atol(strPen);

	}

	m_nEntitiesCnt = 0;
}

CImportDXF::~CImportDXF(void)
{
	DeleteData();
}

void CImportDXF::SetColor()
{
	CString	strPathName /*= CRegisterKey::GetPenFile()*/;

	// 동일한 파일명이 존재를 하는지	
	CFileFind fileFind;
	if(!fileFind.FindFile(strPathName))
		return;

	// 파일이 정상적으로 열리는지
	CStdioFile fileFP;
	if(!fileFP.Open(strPathName, CFile::modeRead))
		return;

	int nPenColor, nPenNum;
	CString strData, strName;

	// 최대 펜 개수를 초기화 하고 
	nPenNum = 0;

	while(TRUE)
	{
		// 데이터 읽기
		if(FALSE == fileFP.ReadString(strData))
			break;

		sscanf(strData, "%d", &nPenColor);

		if(FALSE == fileFP.ReadString(strName))
			break;
		
		if(nPenNum < 0xff)
			m_dwTable[nPenNum++] = nPenColor;

		TRACE("%X %d %s\n", nPenColor, nPenColor, strName);
	};

	fileFP.Close();			// file 닫기

	m_nColorMax = nPenNum;

	return;	
}

// AUTOCAD칼라 읽기
DWORD CImportDXF::GetColor(int nColorNum)
{
	if(nColorNum >= m_nColorMax || nColorNum < 0)
		return 0;

	return m_dwTable[nColorNum];
}

// 그림의 영역 설정
void CImportDXF::SetRect(double dX, double dY)
{
	if(m_dMinX > dX)		m_dMinX = dX;
	if(m_dMinY > dY)		m_dMinY = dY;
	if(m_dMaxX < dX)		m_dMaxX = dX;
	if(m_dMaxY < dY)		m_dMaxY = dY;
}

// 데이터 삭제
void CImportDXF::DeleteData()
{
	int size = m_cList.GetCount(), i;
	IMPORTDATA dList;

	for (i = 0; i < size; i++)
	{
		POSITION pos = m_cList.FindIndex(i);
		dList = m_cList.GetAt(pos);
		if (dList.Attrib.nCode == ID_DRAW_POLYLINE)
		{
			if (dList.Data.PolyLine.dX)
			{
				delete [] dList.Data.PolyLine.dX;
				dList.Data.PolyLine.dX = NULL;
			}
			if (dList.Data.PolyLine.dY)
			{
				delete [] dList.Data.PolyLine.dY;
				dList.Data.PolyLine.dY = NULL;
			}
		}
	}
}

// 코드 읽기
BOOL CImportDXF::DxfGetGroupCode()
{
	// 코드 데이터 읽기
	if(FALSE == m_fileFP.ReadString(m_strCurrent))
		return FALSE;

	sscanf(m_strCurrent, "%d", &m_nGroupCode);

	// 아래 코드를 읽지 않게하기 위하여
	if(0 == m_nGroupCode)
		return TRUE;

	// 데이터 읽기
	if(FALSE == m_fileFP.ReadString(m_strCurrent))
		return FALSE;

	m_strCurrent.TrimLeft();
	m_strCurrent.TrimRight();
	
	return TRUE;
}

// 엔트리 읽기
BOOL CImportDXF::FindEntry(CString strEntry)
{
	do
	{
		if(FALSE == DxfGetGroupCode())
			return FALSE;

		if(m_strCurrent == strEntry)
			return TRUE;
	}while(TRUE);

	return FALSE;
}

// 길이와 각도로 위치 구하기 
void CImportDXF::GetAnglePos(double dCenX, double dCenY, double dLength, double dAngle, double& dX, double& dY)
{
	// 각도를 라디안으로 변환
	dAngle = dAngle * 0.0174532925199432957692369076849;
	
	dX = (dLength * cos(dAngle)) + dCenX;
	dY = (dLength * sin(dAngle)) + dCenY;
}

// 정수값 구하기
int CImportDXF::GetInteger()
{
	int nInteger;

	sscanf(m_strCurrent, "%d", &nInteger);

	return nInteger;
}

// 실수값 구하기
double CImportDXF::GetDouble()
{
#define MAX_CUR
	float fValue;

	sscanf(m_strCurrent, "%f", &fValue);

//	int nValue = fValue * 10000.0;
	return (double)fValue;
}

// 데이터 초기화
void CImportDXF::InitObject(IMPORTDATA& dList, UINT nCode)
{
	memset(&dList, 0, sizeof(IMPORTDATA));
	dList.Attrib.nCode = nCode;
}


// 칼라번호 구하기
int CImportDXF::GetColorNum()
{
	for(int nNum = 0; nNum < m_nLayerMax; nNum ++)
	{
		if(m_lpLayer[nNum].strLayer == m_strCurrent)
			return m_lpLayer[nNum].nColorNum;
	}

	return 0;
}

// 점 데이터 저장
void CImportDXF::AddPoint()
{
	IMPORTDATA dList;
	InitObject(dList, ID_DRAW_POINT);
	do
	{
		if(FALSE == DxfGetGroupCode())
			return;

		switch(m_nGroupCode)
		{
			case    62  :	// Data color
				m_nColorNum	= GetInteger();								break;
			case    8  :	// Data Layer name
				m_nColorNum = GetColorNum();							break;
			case  100	:	// Subclass marker (AcDbPoint) 
																		break;
			case   10	:	// DXF: X values of point location (in WCS)
				dList.Data.Point.dX		= GetDouble();					break;
			case   20	:	// DXF: Y values of point location (in WCS)
				dList.Data.Point.dY		= GetDouble();					break;
			case   30	:	// DXF: Z values of point location (in WCS)
																		break;
			case   39	:	// Thickness (optional; default = 0)
																		break;
			case  210	:	// Extrusion direction(default = 0) X value;
																		break;
			case  220	:	// Extrusion direction(default = 0) Y value;
																		break;
			case  230	:	// Extrusion direction(default = 1) Z value;
																		break;
			case   50	:	// Angle of the X axis for the UCS in effect when the point was drawn (optional, default = 0); used when PDMODE is nonzero
																		break;
			case    0	:
				if(0 < m_nColorNum)
				{
					SetRect(dList.Data.Point.dX, dList.Data.Point.dY);
					dList.Attrib.dwColor = GetColor(m_nColorNum);

					m_cList.AddTail(dList);									return;
				}
				return;
		}
	}while(TRUE);
}

// 선 데이터 저장
void CImportDXF::AddLine()
{
	IMPORTDATA dList;
	InitObject(dList, ID_DRAW_LINE);
	do
	{
 		if(FALSE == DxfGetGroupCode())
			return;

		switch(m_nGroupCode)
		{
			case    62  :	// Data color
				m_nColorNum	= GetInteger();								break;
			case    8  :	// Data Layer name
				m_nColorNum = GetColorNum();							break;
			case  100	:	// Subclass marker (AcDbPoint) 
																		break;
			case   39	:	// Thickness (optional; default = 0) 
																		break;
			case   10	:	// Start point (in WCS). DXF: X value
				dList.Data.Line.dX1		= GetDouble();					break;
			case   20	:	// Start point (in WCS). DXF: Y value
				dList.Data.Line.dY1		= GetDouble();					break;
			case   30	:	// Start point (in WCS). DXF: Z value
																		break;
			case   11	:	// End point (in WCS). DXF: X value
				dList.Data.Line.dX2		= GetDouble();					break;
			case   21	:	// End point (in WCS). DXF: Y value
				dList.Data.Line.dY2		= GetDouble();					break;
			case   31	:	// End point (in WCS). DXF: Z value
																		break;
			case  210	:	// Extrusion direction(default = 0) X value;
																		break;
			case  220	:	// Extrusion direction(default = 0) Y value;
																		break;
			case  230	:	// Extrusion direction(default = 1) Z value;
																		break;
			case    0	:

				if(dList.Data.Line.dX1 == dList.Data.Line.dX2)			// 세로 데이터
					m_nColCount ++;
				else if(dList.Data.Line.dY1 == dList.Data.Line.dY2)		// 가로 데이터
					m_nRowCount ++;
				else
					m_nTotalCount ++;

//				if(0 < m_nColorNum)
				{
					SetRect(dList.Data.Line.dX1, dList.Data.Line.dY1);
					SetRect(dList.Data.Line.dX2, dList.Data.Line.dY2);
					//dList.Attrib.dwColor = GetColor(m_nColorNum);
					//dList.Attrib.dwColor = theApp.m_dwPenColor[m_nColorNum];
					dList.Attrib.dwColor = m_dwTable[m_nColorNum];

					m_cList.AddTail(dList);									return;
				}
				return;
		}
		
	}while(TRUE);
}

// M선 데이터 저장
void CImportDXF::AddMLine()
{
	int		nOpenOrCosed = 0;
	int		nJustification;
	double	dScale = 0.0;
	double	dFirstX = 0, dFirstY = 0;
	BOOL	bIsSave = FALSE;

	IMPORTDATA dList;
	InitObject(dList, ID_DRAW_LINE);
	do
	{
		if(FALSE == DxfGetGroupCode())
			return;

		switch(m_nGroupCode)
		{
			case    62  :	// Data color
				m_nColorNum	= GetInteger();								break;
			case    8  :	// Data Layer name
				m_nColorNum = GetColorNum();							break;
			case  100	:	// Subclass marker (AcDbPoint) 
																		break;
			case	 2  :	// String of up to 32 characters. The name of the style used for this mline. An entry for this style must exist in the MLINESTYLE dictionary. 
																		break;
			case  340	:	//  Pointer-handle/ID of MLINESTYLE dictionary
																		break;
			case   40	:	//  Scale factor
				dScale			= GetDouble();							break;
			case   70	:	//  Justification: 0=top, 1=zero, 2=bottom
				nJustification	= GetInteger();							break;
			case   71	:	//  Open/closed flag: 1=open, 3=closed
				nOpenOrCosed	= GetInteger();							break;
			case   72	:	//  Number of vertices
																		break;
			case   73	:	//  Number of elements in MLINESTYLE definition
																		break;
			case   10	:	// Start point (in WCS). DXF: X value
				dList.Data.Line.dX1		= dFirstX = GetDouble();		break;
			case   20	:	// Start point (in WCS). DXF: Y value
				dList.Data.Line.dY1		= dFirstY = GetDouble();		break;
			case   30	:	// Start point (in WCS). DXF: Z value
																		break;
			case  210	:	// X values of extrusion direction (optional; default = 0)
																		break;
			case  220	:	// Y values of extrusion direction (optional; default = 0)
																		break;
			case  230	:	// Z values of extrusion direction (optional; default = 1)
																		break;
			case   11	:	// End point (in WCS). DXF: X value
				dList.Data.Line.dX2		= GetDouble();					break;
			case   21	:	// End point (in WCS). DXF: Y value
				dList.Data.Line.dY2		= GetDouble();
				bIsSave					= TRUE;						break;
			case   31	:	// End point (in WCS). DXF: Z value
																		break;
			case   12	:	// DXF: X values of direction vector of segment starting at this vertex
																		break;
			case   22	:	// DXF: Y values of direction vector of segment starting at this vertex
																		break;
			case   32	:	// DXF: Z values of direction vector of segment starting at this vertex
																		break;
			case   13	:	// DXF: X values of direction vector of miter
																		break;
			case   23	:	// DXF: Y values of direction vector of miter
																		break;
			case   33	:	// DXF: Z values of direction vector of miter
																		break;
			case   74	:	// Number of parameters for this element (repeats for each element in segment)
																		break;
			case   41	:	// Element parameters (repeats based on previous code 74)
																		break;
			case   75	:	// Number of area fill parameters for this element (repeats for each element in segment)
																		break;
			case   42	:	// Area fill parameters (repeats based on previous code 75)
																		break;
			case    0	:
					if(3 == nOpenOrCosed)	// Close일경우에만
					{
						if(0 < m_nColorNum)
						{
							dList.Data.Line.dX1 = dList.Data.Line.dX2;
							dList.Data.Line.dY1 = dList.Data.Line.dY2;
							dList.Data.Line.dX2 = dFirstX;
							dList.Data.Line.dY2 = dFirstY;

							SetRect(dList.Data.Line.dX1, dList.Data.Line.dY1);
							SetRect(dList.Data.Line.dX2, dList.Data.Line.dY2);
							dList.Attrib.dwColor = GetColor(m_nColorNum);

							m_cList.AddTail(dList);
						}
					}													return;
		}
		// 데이터 저장
		if(TRUE == bIsSave)
		{
			if(0 < m_nColorNum)
			{
				SetRect(dList.Data.Line.dX1, dList.Data.Line.dY1);
				SetRect(dList.Data.Line.dX2, dList.Data.Line.dY2);

				dList.Attrib.dwColor = GetColor(m_nColorNum);

				m_cList.AddTail(dList);
			}

			dList.Data.Line.dX1 = dList.Data.Line.dX2;
			dList.Data.Line.dY1 = dList.Data.Line.dY2;
			bIsSave	= FALSE;
		}
	}while(TRUE);
}

// X선 데이터 저장
void CImportDXF::AddXLine()
{

}

// SP선 데이터 저장
void CImportDXF::AddSPLine()
{

}

// POLY선 데이터 저장
void CImportDXF::AddPolyLine()
{

}

// LWPoly선 데이터 저장
void CImportDXF::AddLWPolyLine()
{
	IMPORTDATA dList;
	InitObject(dList, ID_DRAW_POLYLINE);

	dList.Data.PolyLine.dX = NULL;
	dList.Data.PolyLine.dY = NULL;
	do
	{
		if (FALSE == DxfGetGroupCode())
			return;

		switch (m_nGroupCode)
		{
		case	62	:	// Data color
			m_nColorNum = GetInteger();												break;
		case    8  :	// Data Layer name
			m_nColorNum = GetColorNum();											break;
		case	90	:	// point count
			dList.Data.PolyLine.totalPoint = GetInteger();			
			dList.Data.PolyLine.currPoint = 0;
			dList.Data.PolyLine.dX  = new double[dList.Data.PolyLine.totalPoint];
			dList.Data.PolyLine.dY  = new double[dList.Data.PolyLine.totalPoint];	break;
		case	70	:
			dList.Data.PolyLine.polyFlag = GetInteger();							break;
		case	10	:	// X value; APP: 2D point 
			dList.Data.PolyLine.dX[dList.Data.PolyLine.currPoint] = GetDouble();	break;
		case   20	:	// Y value of vertex coordinates 
			dList.Data.PolyLine.dY[dList.Data.PolyLine.currPoint] = GetDouble();
			SetRect(dList.Data.PolyLine.dX[dList.Data.PolyLine.currPoint],
						dList.Data.PolyLine.dY[dList.Data.PolyLine.currPoint]);
			dList.Data.PolyLine.currPoint++;										break;
		case	42	:	// ???????????????????????


																					break;
		case	0	:
			if (0 <= m_nColorNum)
			{
				dList.Attrib.dwColor = m_dwTable[m_nColorNum];
				m_cList.AddTail(dList);													return;
			}
			break;
		}
	} while (TRUE);
}

// 원 데이터 저장
void CImportDXF::AddCircle()
{
	IMPORTDATA dList;
	InitObject(dList, ID_DRAW_CIRCLE);

	do
	{
		if(FALSE == DxfGetGroupCode())
			return;

		switch(m_nGroupCode)
		{
			case    62  :	// Data color
				dList.Attrib.dwColor	= (COLORREF)GetInteger();		break;
			case    8  :	// Data Layer name
				m_nColorNum = GetColorNum();
			case  100	:	// Subclass marker (AcDbPoint) 
																		break;
			case   39	:	// Thickness (optional; default = 0) 
																		break;
			case   10	:	// Center point (in OCS). DXF: X value; APP: 3D point
				dList.Data.Circle.dXC		= GetDouble();				break;
			case   20	:	// Center point (in OCS). DXF: Y value; APP: 3D point
				dList.Data.Circle.dYC		= GetDouble();				break;
			case   30	:	// Center point (in OCS). DXF: Z value; APP: 3D point
																		break;
			case   40	:	// Radius
				dList.Data.Circle.dRad		= GetDouble();				break;
			case  210	:	// Extrusion direction DXF: X value; APP: 3D vector
																		break;
			case  220	:	// Extrusion direction DXF: Y value; APP: 3D vector
																		break;
			case  230	:	// Extrusion direction DXF: Z value; APP: 3D vector
																		break;
			case    0	:
				{
					double dRadius = dList.Data.Circle.dRad;
					SetRect(dList.Data.Circle.dXC - dRadius, dList.Data.Circle.dYC - dRadius);
					SetRect(dList.Data.Circle.dXC + dRadius, dList.Data.Circle.dYC + dRadius);

					dList.Attrib.dwColor = GetColor(m_nColorNum);

//					if(0 < m_nColorNum)
						m_cList.AddTail(dList);								return;
				}
		}
	}while(TRUE);
}

// 호 데이터 저장
void CImportDXF::AddArc()
{
	IMPORTDATA dList;
	InitObject(dList, ID_DRAW_ARC);

	do
	{
		if(FALSE == DxfGetGroupCode())
			return;

		switch(m_nGroupCode)
		{
			case    62  :	// Data color
				dList.Attrib.dwColor	= (COLORREF)GetInteger();		break;
			case  100	:	// Subclass marker (AcDbPoint) 
																		break;
			case   39	:	// Thickness (optional; default = 0) 
																		break;
			case   10	:	// Center point (in OCS). DXF: X value; APP: 3D point
				dList.Data.Arc.dXC		= GetDouble();					break;
			case   20	:	// Center point (in OCS). DXF: Y value; APP: 3D point
				dList.Data.Arc.dYC		= GetDouble();					break;
			case   30	:	// Center point (in OCS). DXF: Z value; APP: 3D point
																		break;
			case   40	:	// Radius
				dList.Data.Arc.dRad		= GetDouble();					break;
			case   50	:	// Start angle
				dList.Data.Arc.dSAng	= GetDouble();					break;
			case   51	:	// End angle
				dList.Data.Arc.dEAng	= GetDouble();					break;
			case  210	:	// Extrusion direction DXF: X value; APP: 3D vector
																		break;
			case  220	:	// Extrusion direction DXF: Y value; APP: 3D vector
																		break;
			case  230	:	// Extrusion direction DXF: Z value; APP: 3D vector
																		break;
			case    0	:
				{
					double dRadius = dList.Data.Arc.dRad;
					SetRect(dList.Data.Arc.dXC - dRadius, dList.Data.Arc.dYC - dRadius);
					SetRect(dList.Data.Arc.dXC + dRadius, dList.Data.Arc.dYC + dRadius);

					dList.Attrib.dwColor = GetColor(m_nColorNum);

					if(0 < m_nColorNum)
						m_cList.AddTail(dList);								return;
						
				}
		}
	}while(TRUE);
}

// 타원 데이터 저장
void CImportDXF::AddEllipse()
{
	IMPORTDATA dList;
	InitObject(dList, ID_DRAW_ELLIPSE);

	do
	{
		if(FALSE == DxfGetGroupCode())
			return;

		switch(m_nGroupCode)
		{
			case    62  :	// Data color
				m_nColorNum	= GetInteger();								break;
			case    8  :	// Data Layer name
				m_nColorNum = GetColorNum();							break;
			case  100	:	// Subclass marker (AcDbPoint) 
																		break;
			case   39	:	// Thickness (optional; default = 0) 
																		break;
			case   10	:	// Center point (in OCS). DXF: X value; APP: 3D point
				dList.Data.Ellipse.dXC		= GetDouble();				break;
			case   20	:	// Center point (in OCS). DXF: Y value; APP: 3D point
				dList.Data.Ellipse.dYC		= GetDouble();				break;
			case   30	:	// Center point (in OCS). DXF: Z value; APP: 3D point
																		break;
			case   11	:	// Endpoint of major axis, relative to the center (in WCS). X value
				dList.Data.Ellipse.dReltoXC	= GetDouble();				break;
			case   21	:	// Endpoint of major axis, relative to the center (in WCS). Y value
				dList.Data.Ellipse.dReltoYC	= GetDouble();				break;
			case   31	:	// Endpoint of major axis, relative to the center (in WCS). Z value
																		break;
			case   40	:	// Ratio of minor axis to major axis
				dList.Data.Ellipse.dRatioAxi	= GetDouble();				break;
			case   41	:	// Start parameter (this value is 0.0 for a full ellipse)
//				dList.Data.Ellipse.dSAng	= GetDouble();				break;
			case   42	:	// End parameter (this value is 2pi for a full ellipse)
//				dList.Data.Ellipse.dEAng	= GetDouble();				break;
			case  210	:	// Extrusion direction DXF: X value; APP: 3D vector
																		break;
			case  220	:	// Extrusion direction DXF: Y value; APP: 3D vector
																		break;
			case  230	:	// Extrusion direction DXF: Z value; APP: 3D vector
																		break;
			case    0	:
				return;
		}
	}while(TRUE);
}

// 해치 데이터 저장
void CImportDXF::AddHatch()
{

}

// 그림 데이터 저장
void CImportDXF::AddImage()
{

}

// 문자 데이터 저장
void CImportDXF::AddText()
{

}

// M문자 데이터 저장
void CImportDXF::AddMText()
{

}

// LAYER 데이터 저장
void CImportDXF::AddLayer()
{
	do
	{
		if(FALSE == DxfGetGroupCode())
			return;

		switch(m_nGroupCode)
		{
			case   62  :	// Color number (if negative, layer is off)
				if(NULL != m_lpLayer && m_nLayerPos < m_nLayerMax)
				{
					m_lpLayer[m_nLayerPos].nColorNum= GetInteger();
				}														break;
			case    2	:	// Linetype name
				if(NULL != m_lpLayer && m_nLayerPos < m_nLayerMax)
				{
					m_lpLayer[m_nLayerPos].strLayer	= m_strCurrent;
				}														break;
			case  100	:	// Subclass marker (AcDbPoint) 
																		break;
			case   70	:	// Standard flags (bit-coded values)
							//   1 = Layer is frozen; otherwise layer is thawed
							//   2 = Layer is frozen by default in new viewports
							//   4 = Layer is locked
							//  16 = If set, table entry is externally dependent on an xref
							//  32 = If this bit and bit 16 are both set, the externally dependent xref has
							//		 been successfully resolved
							//  64 = If set, the table entry was referenced by at least one entity in the
							//		 drawing the last time the drawing was edited. (This flag is for the
							//		 benefit of AutoCAD commands. It can be ignored by most programs
							//		 that read DXF files and need not be set by programs that write DXF files)
				if(0 == m_nLayerMax)
				{
					m_nLayerMax = GetInteger();
					m_lpLayer	= new LAYER[m_nLayerMax];

					return;
				}														break;
			case  290	:	// Plotting flag. If set to 0, do not plot this layer
																		break;
			case  370	:	// Lineweight enum value
																		break;
			case  390	:	// Hard pointer ID/handle of PlotStyleName object
																		break;
			case    0	:
				m_nLayerPos ++;											return;
		}
	}while(TRUE);
}

// 데이터 저장
void CImportDXF::AddObject()
{
	CPointerManager *m_pPointerManager = m_pPointerManager->GetInstance();
	CDlgProgressBar *pDlg = m_pPointerManager->GetDlgProgressbar();
	double progressPos = 0;
	pDlg->m_ctrProgress.SetRange(0, 100);
	pDlg->m_ctrProgressSta.SetWindowText("Read DXF...");
	int pos;

	while(TRUE)
	{
		m_nColorNum = 0;	// 칼라 색상을 설정

		if(FALSE == DxfGetGroupCode())
			return;

		if(m_strCurrent == _T("POINT")) {
			AddPoint();
			progressPos++;
		}
		else if(m_strCurrent == _T("LINE")) {
			AddLine();
			progressPos++;
		}
		else if(m_strCurrent == _T("MLINE")) {
			AddMLine();
			progressPos++;
		}
		else if(m_strCurrent == _T("XLINE")) {
			AddXLine();
			progressPos++;
		}
		else if(m_strCurrent == _T("SPLINE")) {
			AddSPLine();
			progressPos++;
		}
		else if(m_strCurrent == _T("POLYLINE")) {
			AddPolyLine();
			progressPos++;
		}
		else if(m_strCurrent == _T("LWPOLYLINE")) {
			AddLWPolyLine();
			progressPos++;
		}
		else if(m_strCurrent == _T("CIRCLE")) {
			AddCircle();
			progressPos++;
		}
		else if(m_strCurrent == _T("ARC")) {
			AddArc();
			progressPos++;
		}
		else if(m_strCurrent == _T("ELLIPSE")) {
			AddEllipse();
			progressPos++;
		}
		else if(m_strCurrent == _T("HATCH")) {
			AddHatch();
			progressPos++;
		}
		else if(m_strCurrent == _T("IMAGE")) {
			AddImage();
			progressPos++;
		}
		else if(m_strCurrent == _T("TEXT")) {
			AddText();
			progressPos++;
		}
		else if(m_strCurrent == _T("MTEXT")) {
			AddMText();
			progressPos++;
		}
		else if(m_strCurrent == _T("LAYER")) {
			AddLayer();
			progressPos++;
		}
		
		m_strCurrent = _T("");
		pos = (progressPos / m_nEntitiesCnt) * 100.;
		pDlg->m_ctrProgress.SetPos(pos);
	};
	pDlg->m_ctrProgress.SetPos(0);
}

// DXF 파일 열기
BOOL CImportDXF::Open(CString strPathName)
{
	CFileFind fileFind;
	if(!fileFind.FindFile(strPathName))	
		return FALSE;

	CFileException ex;
	if(!m_fileFP.Open(strPathName, CFile::modeRead, &ex))
	{
		TCHAR chError[MAX_PATH];
		ex.GetErrorMessage(chError, MAX_PATH);
		AfxMessageBox(chError, MB_OK | MB_ICONEXCLAMATION);

		return FALSE;
	}

	m_nTotalCount = 0;	// 전체 선의개수
	m_nRowCount	= 0;	// 세로 데이터의 개수
	m_nColCount = 0;	// 가로 데이터의 개수

	m_nLayerPos = 0;	// 레이어 카운트
	m_nLayerMax = 0;	// 레이어 전체 갯수

	CountEntities();
	m_fileFP.Close();

	if(!m_fileFP.Open(strPathName, CFile::shareDenyRead, &ex))
	{
		TCHAR chError[MAX_PATH];
		ex.GetErrorMessage(chError, MAX_PATH);
		AfxMessageBox(chError, MB_OK | MB_ICONEXCLAMATION);

		return FALSE;
	}

	if(TRUE == FindEntry(_T("ENTITIES")))
		AddObject();

	m_fileFP.Close();

	if(NULL != m_lpLayer)
		delete[] m_lpLayer;

	return TRUE;
}

// 중심위치로 설정
void CImportDXF::SetCenter(double dMinX, double dMinY, double dMaxX, double dMaxY)
{
	m_dMoveX = ((dMinX + dMaxX) / 2.0) - ((m_dMinX + m_dMaxX) / 2.0);
	m_dMoveY = ((dMinY + dMaxY) / 2.0) - ((m_dMinY + m_dMaxY) / 2.0);
}

// 저장된 데이터 갯수읽기
DWORD CImportDXF::GetCount()
{
	return (DWORD)m_cList.GetCount();
}

/*
// 임시버퍼를 위치변형 또는 데이터회전을 한후 할당된 버퍼에 적용
int CImportDXF::ConvertData()
{

}
*/
// 저장된 데이터 읽기
BOOL CImportDXF::GetData(DWORD dwPos, IMPORTDATA& dataGet, BOOL bCenter)
{
	if(dwPos > (DWORD)m_cList.GetCount())
		return FALSE;

	POSITION pos = m_cList.FindIndex(dwPos);
	dataGet = m_cList.GetAt(pos);
	dataGet.Attrib.dwColor = dataGet.Attrib.dwColor;
	switch(dataGet.Attrib.nCode)
	{
		case ID_DRAW_POINT	:
			{
				dataGet.Data.Point.dX	+= (!bCenter) ? 0.0 : m_dMoveX;
				dataGet.Data.Point.dY	+= (!bCenter) ? 0.0 : m_dMoveY;
			}	return TRUE;
		case ID_DRAW_LINE	:
			{
				dataGet.Data.Line.dX1	+= (!bCenter) ? 0.0 : m_dMoveX;
				dataGet.Data.Line.dY1	+= (!bCenter) ? 0.0 : m_dMoveY;
				dataGet.Data.Line.dX2	+= (!bCenter) ? 0.0 : m_dMoveX;
				dataGet.Data.Line.dY2	+= (!bCenter) ? 0.0 : m_dMoveY;
			}	return TRUE;
		case ID_DRAW_CIRCLE	:
			{
				dataGet.Data.Circle.dXC += (!bCenter) ? 0.0 : m_dMoveX;
				dataGet.Data.Circle.dYC += (!bCenter) ? 0.0 : m_dMoveY;
			}	return TRUE;
		case ID_DRAW_ARC	:
			{
				dataGet.Data.Arc.dXC	+= (!bCenter) ? 0.0 : m_dMoveX;
				dataGet.Data.Arc.dYC	+= (!bCenter) ? 0.0 : m_dMoveY;
			}	return TRUE;
		case ID_DRAW_ELLIPSE	:
			{
				dataGet.Data.Ellipse.dXC+= (!bCenter) ? 0.0 : m_dMoveX;
				dataGet.Data.Ellipse.dYC+= (!bCenter) ? 0.0 : m_dMoveY;
			}	return TRUE;
		case ID_DRAW_CURVE	:
			{
				dataGet.Data.Bezier.dX1 += (!bCenter) ? 0.0 : m_dMoveX;
				dataGet.Data.Bezier.dY1 += (!bCenter) ? 0.0 : m_dMoveY;
				dataGet.Data.Bezier.dX2 += (!bCenter) ? 0.0 : m_dMoveX;
				dataGet.Data.Bezier.dY2 += (!bCenter) ? 0.0 : m_dMoveY;
				dataGet.Data.Bezier.dX3 += (!bCenter) ? 0.0 : m_dMoveX;
				dataGet.Data.Bezier.dY3 += (!bCenter) ? 0.0 : m_dMoveY;
				dataGet.Data.Bezier.dX4 += (!bCenter) ? 0.0 : m_dMoveX;
				dataGet.Data.Bezier.dY4 += (!bCenter) ? 0.0 : m_dMoveY;
			}	return TRUE;
	}
	return FALSE;
}


Vector * CImportDXF::GetVector()
{
	CPointerManager *m_pPointerManager = m_pPointerManager->GetInstance();
	CDlgProgressBar *pDlg = m_pPointerManager->GetDlgProgressbar();
	CTransUnit	*pTransUnit = pTransUnit->GetInstance();

	DWORD dwVectorLength = 0;
	double xmin = 999999, xmax = -999999, ymin = 999999, ymax = -999999;
	double x, y, px=0, py=0, bufx, bufy, stx, sty;
	int cnt = 0, cnt1 = 0;
	CPoint p;

	IMPORTDATA data;	
	
	pDlg->m_ctrProgressSta.SetWindowText("Make vector...");
	double totalSize = m_cList.GetCount() * 2;

	POSITION pos = m_cList.GetHeadPosition();
	while(pos)
	{
		data = m_cList.GetNext(pos);

		switch(data.Attrib.nCode)
		{
		case ID_DRAW_POINT	:
			{
				
			}	break;
		case ID_DRAW_LINE	:
			{
				dwVectorLength += 2;
			}	break;
		case ID_DRAW_CIRCLE	:
			{
				dwVectorLength += 61;
			}	break;
		case ID_DRAW_ARC	:
			{

			}	break;
		case ID_DRAW_ELLIPSE	:
			{

			}	break;
		case ID_DRAW_CURVE	:
			{

			}	break;
		case ID_DRAW_POLYLINE	:
			{
				dwVectorLength += data.Data.PolyLine.totalPoint;
				if (data.Data.PolyLine.polyFlag == 1)
					dwVectorLength++;
			}	break;
		}

		pDlg->m_ctrProgress.SetPos(cnt1 / totalSize * 100);
		cnt1++;
	}


	Vector *pVector = new Vector[dwVectorLength];
	m_dwVectorLength = dwVectorLength;


	pos = m_cList.GetHeadPosition();
	while(pos)
	{
		data = m_cList.GetNext(pos);
		
		switch(data.Attrib.nCode)
		{
		case ID_DRAW_POINT	:
			{
				
			}	break;
		case ID_DRAW_LINE	:
			{
				/////////////////////// dX1 //////////////////////////
//				x = data.Data.Line.dX1 / 1000.0f;
//				y = data.Data.Line.dY1 / 1000.0f;
//				x = CMathUtil::Round(pTransUnit->GetField(x, MM), 0);
//				y = CMathUtil::Round(pTransUnit->GetField(y, MM), 0);

				x = data.Data.Line.dX1;
				y = data.Data.Line.dY1;
				
				if (!(px == x) || !(py == y))
				{
					if (cnt == 0)
					{
						stx = px = x;
						sty = py = y;
						
						bufx = x - px;
						bufy = y - py;
						
						x = bufx;
						y = bufy;
					}
					else
					{
						bufx = x - px;
						bufy = y - py;
						
						px = x;
						py = y;
						
						x = bufx;
						y = bufy;
					}
					
					pVector[cnt].t = 2;
					pVector[cnt].d.x = x;
					pVector[cnt].d.y = y;
					
					cnt++;
				}
				
				/////////////////////// dX2 //////////////////////////
//				x = data.Data.Line.dX2 / 1000.0f;
//				y = data.Data.Line.dY2 / 1000.0f;
//				x = CMathUtil::Round(pTransUnit->GetField(x, MM), 1);
//				y = CMathUtil::Round(pTransUnit->GetField(y, MM), 1);

			
				x = data.Data.Line.dX2;
				y = data.Data.Line.dY2;

				if (!(px == x) || !(py == y))
				{
					bufx = x - px;
					bufy = y - py;
					
					px = x;
					py = y;
					
					x = bufx;
					y = bufy;
										
					pVector[cnt].t = 4;
					pVector[cnt].d.x = x;
					pVector[cnt].d.y = y;

					cnt++;
				}
				
			}	break;
		case ID_DRAW_CIRCLE	:
			{
				int i = 0;
				double rad = 3.1415926535897932384626433832795 * (6*i) / 180;
				for (i = 0; i < 61; i++)
				{
					x = data.Data.Circle.dXC + data.Data.Circle.dRad * cos(rad);
					y = data.Data.Circle.dYC + data.Data.Circle.dRad * sin(rad);
//					x /= 1000;
//					y /= 1000;
//					x = CMathUtil::Round(pTransUnit->GetField(x, MM), 1);
//					y = CMathUtil::Round(pTransUnit->GetField(y, MM), 1);

					if (cnt == 0)
					{
						stx = px = x;
						sty = py = y;
						
						bufx = x - px;
						bufy = y - py;
						
						x = bufx;
						y = bufy;
					}
					else
					{
						bufx = x - px;
						bufy = y - py;
						
						px = x;
						py = y;
						
						x = bufx;
						y = bufy;
					}
										
					if (i == 0)
						pVector[cnt].t = 2;
					else
						pVector[cnt].t = 4;

					pVector[cnt].d.x = x;
					pVector[cnt].d.y = y;

					cnt++;
				}
			}	break;
		case ID_DRAW_ARC	:
			{

			}	break;
		case ID_DRAW_ELLIPSE	:
			{

			}	break;
		case ID_DRAW_CURVE	:
			{

			}	break;
		case ID_DRAW_POLYLINE	:
			{
				int size = data.Data.PolyLine.totalPoint, i = 0,  etx=0, ety=0;
				
				for (i = 0; i < size; i++)
				{
//					x = data.Data.PolyLine.dX[i] / 1000;
//					y = data.Data.PolyLine.dY[i] / 1000;
//					x = CMathUtil::Round(pTransUnit->GetField(x, MM), 1);
//					y = CMathUtil::Round(pTransUnit->GetField(y, MM), 1);

					x = data.Data.PolyLine.dX[i];
					y = data.Data.PolyLine.dY[i];

					if (cnt == 0)
					{
						stx = px = x;
						sty = py = y;
						
						bufx = x - px;
						bufy = y - py;
						
						x = bufx;
						y = bufy;
					}
					else
					{
						if (i == 0 && data.Data.PolyLine.polyFlag == 1)
						{
							etx = x;
							ety = y;
						}

						bufx = x - px;
						bufy = y - py;
						
						px = x;
						py = y;
						
						x = bufx;
						y = bufy;
					}
														
					if (i == 0)
						pVector[cnt].t = 2;
					else
						pVector[cnt].t = 4;

					pVector[cnt].d.x = x;
					pVector[cnt].d.y = y;

					cnt++;
				}

				if (data.Data.PolyLine.polyFlag == 1)
				{
					x = etx;
					y = ety;
					
					bufx = x - px;
					bufy = y - py;
					
					px = x;
					py = y;
					
					x = bufx;
					y = bufy;

					pVector[cnt].t = 4;
					pVector[cnt].d.x = x;
					pVector[cnt].d.y = y;

					cnt ++;
				}
			}	break;
		}

		pDlg->m_ctrProgress.SetPos(cnt1 / totalSize * 100);
		cnt1++;
	}




//	double minX = m_dMinX/1000, minY = m_dMinY/1000;
//	minX = pTransUnit->GetField(minX, MM);
//	minY = pTransUnit->GetField(minY, MM);
//
//	if (minX < stx)
//		pVector[0].d.x += stx - minX;
//	if (minY < sty)
//		pVector[0].d.y += sty - minY;

	if (m_dMinX < stx)
		pVector[0].d.x += stx - m_dMinX;
	if (m_dMinY < sty)
		pVector[0].d.y += sty - m_dMinY;


	return pVector;	
}

double CImportDXF::GetWidth()
{
//	CTransUnit	*pTransUnit = pTransUnit->GetInstance();
//	double maxX = m_dMaxX/1000, minX = m_dMinX/1000;
//
//	maxX = pTransUnit->GetField(maxX, MM);
//	minX = pTransUnit->GetField(minX, MM);
//
//	return maxX - minX;

	return m_dMaxX - m_dMinX;
}

double CImportDXF::GetHeight()
{
//	CTransUnit	*pTransUnit = pTransUnit->GetInstance();
//	double maxY = m_dMaxY/1000, minY = m_dMinY/1000;
//
//	maxY = pTransUnit->GetField(maxY, MM);
//	minY = pTransUnit->GetField(minY, MM);
//
//	return maxY - minY;

	return m_dMaxY - m_dMinY;
}

DWORD CImportDXF::GetVectorLength()
{
	return m_dwVectorLength;
}

void CImportDXF::CountEntities()
{
	do
	{
		if(FALSE == DxfGetGroupCode())
			return;

		if(m_strCurrent == _T("POINT")
			|| m_strCurrent == _T("LINE")
			|| m_strCurrent == _T("MLINE")
			|| m_strCurrent == _T("XLINE")
			|| m_strCurrent == _T("SPLINE")
			|| m_strCurrent == _T("POLYLINE")
			|| m_strCurrent == _T("LWPOLYLINE")
			|| m_strCurrent == _T("CIRCLE")
			|| m_strCurrent == _T("ARC")
			|| m_strCurrent == _T("ELLIPSE")
			|| m_strCurrent == _T("HATCH")
			|| m_strCurrent == _T("IMAGE")
			|| m_strCurrent == _T("TEXT")
			|| m_strCurrent == _T("MTEXT")
			|| m_strCurrent == _T("LAYER"))
		{
			m_nEntitiesCnt++;
		}
		
	}while(1);

	return;	
}
