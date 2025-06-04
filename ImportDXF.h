#pragma once

#ifndef __IMPORTDXF_H__
#define __IMPORTDXF_H__

#ifndef __AFXTEMPL_H__
	#include <Afxtempl.h>
#endif

#include "ImportStruct.h"
#include "Vector.h"
#include "TransUnit.h"
#include "Define.h"
#include "PointerManager.h"
#include "DlgProgressBar.h"
#include "MathUtil.h"

#define MAX_TEMPDATA		4000

#define ID_DRAW_POINT		10
#define ID_DRAW_LINE		ID_DRAW_POINT + 1
#define ID_DRAW_CIRCLE		ID_DRAW_POINT + 2
#define ID_DRAW_ARC			ID_DRAW_POINT + 3
#define ID_DRAW_ELLIPSE		ID_DRAW_POINT + 4
#define ID_DRAW_CURVE		ID_DRAW_POINT + 5
#define ID_DRAW_POLYLINE	ID_DRAW_POINT + 6

class CImportDXF
{
public:
	void CountEntities();
	double m_nEntitiesCnt;
	DWORD GetVectorLength();
	double GetHeight();
	double GetWidth();
	Vector * GetVector();
	CImportDXF(void);
	virtual ~CImportDXF(void);

	// DXF 파일 열기
	BOOL	Open(CString strPathName);

	// Pen 칼라 저장하기
	void	SetColor(void);

	// 저장된 데이터 갯수읽기
	DWORD	GetCount();
	// 저장된 데이터 읽기
	BOOL	GetData(DWORD dwPos, IMPORTDATA& dataGet, BOOL bCenter = TRUE);

	// 중심위치로 설정
	void	SetCenter(double dMinX, double dMinY, double dMaxX, double dMaxY);

protected:
	// 데이터 초기화
	void	InitObject(IMPORTDATA& dList, UINT nCode);

	// Pen 칼라 읽기
	DWORD	GetColor(int nColorNum);

	// 그림의 영역 설정
	void	SetRect(double dX, double dY);

	// 데이터 삭제
	void	DeleteData();

	// 코드 읽기
	BOOL	DxfGetGroupCode();
	// 엔트리 읽기
	BOOL	FindEntry(CString strEntry);

	// 정수값 구하기
	int		GetInteger();
	// 실수값 구하기
	double	GetDouble();
	// 칼라번호 구하기
	int		GetColorNum();

	// 길이와 각도로 위치 구하기 
	void	GetAnglePos(double dCenX, double dCenY, double dLength, double dAngle, double& dX, double& dY);

	// 점 데이터 저장
	void	AddPoint();
	// 선 데이터 저장
	void	AddLine();
	// M선 데이터 저장
	void	AddMLine();
	// X선 데이터 저장
	void	AddXLine();
	// SP선 데이터 저장
	void	AddSPLine();
	// POLY선 데이터 저장
	void	AddPolyLine();
	// LWPoly선 데이터 저장
	void	AddLWPolyLine();
	// 원 데이터 저장
	void	AddCircle();
	// 호 데이터 저장
	void	AddArc();
	// 타원 데이터 저장
	void	AddEllipse();
	// 해치 데이터 저장
	void	AddHatch();
	// 그림 데이터 저장
	void	AddImage();
	// 문자 데이터 저장
	void	AddText();
	// M문자 데이터 저장
	void	AddMText();
	// LAYER 데이터 저장
	void	AddLayer();
	// 데이터 저장
	void	AddObject();


protected:
	double m_dHeight;
	double m_dWidth;
	DWORD m_dwVectorLength;
	typedef struct tagTEMPLINE
	{
		DWORD	dwColor;					// 선의 색상
		double	dX1;						// 선의 X축시작 위치
		double	dY1;						// 선의 Y축시작 위치
		double	dX2;						// 선의 X축끝 위치
		double	dY2;						// 선의 Y축끝 위치
	}TEMPLINE, *LPTEMPLINE;

	typedef struct tagLAYER
	{
		CString	strLayer;					// 레이어 명
		int		nColorNum;					// 레이어 색상번호
	}LAYER, *LPLAYER;	

	typedef struct tagLWPOLYLINEDATA
	{
		double	d10;
		double	d20;
		double	d42;
	}LWPOLYLINEDATA, *LPLWPOLYLINEDATA;

	CList<IMPORTDATA, IMPORTDATA&> m_cList;		// 도형의 정보데이터

	CStdioFile	m_fileFP;					// DXF의 파일

	CString		m_strCurrent;				// 읽은 현재 데이터
	CString		m_strFormer;				// 읽은 이전 데이터

	int			m_nGroupCode;				// 그룹코드 종류
	int			m_nColorNum;				// 작업 색상번호

	int			m_nLayerPos;				// 레이어 카운트
	int			m_nLayerMax;				// 레이어 전체 갯수
	LPLAYER		m_lpLayer;					// 레이어명과 색상번호

	double		m_dMoveX;					// 중심으로 X축 이동량
	double		m_dMoveY;					// 중심으로 Y축 이동량
	double		m_dMinX;					// X축의 최소값
	double		m_dMinY;					// Y축의 최소값
	double		m_dMaxX;					// X축의 최대값
	double		m_dMaxY;					// Y축의 최대값

	int			m_nTotalCount;				// 전체 선의개수
	int			m_nRowCount;				// 세로 데이터의 개수
	int			m_nColCount;				// 가로 데이터의 개수

	int			m_nColorMax;				// Pen color 개수
	DWORD		m_dwTable[255];				// pen color 저장 장소

	// 임시 도형의 정보데이터
//	CArray<TEMPLINE, TEMPLINE>m_dTemp[MAX_TEMPDATA];

	//Vector *m_pVector;
};

#endif // _IMPORTDXF_H_