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

	// DXF ���� ����
	BOOL	Open(CString strPathName);

	// Pen Į�� �����ϱ�
	void	SetColor(void);

	// ����� ������ �����б�
	DWORD	GetCount();
	// ����� ������ �б�
	BOOL	GetData(DWORD dwPos, IMPORTDATA& dataGet, BOOL bCenter = TRUE);

	// �߽���ġ�� ����
	void	SetCenter(double dMinX, double dMinY, double dMaxX, double dMaxY);

protected:
	// ������ �ʱ�ȭ
	void	InitObject(IMPORTDATA& dList, UINT nCode);

	// Pen Į�� �б�
	DWORD	GetColor(int nColorNum);

	// �׸��� ���� ����
	void	SetRect(double dX, double dY);

	// ������ ����
	void	DeleteData();

	// �ڵ� �б�
	BOOL	DxfGetGroupCode();
	// ��Ʈ�� �б�
	BOOL	FindEntry(CString strEntry);

	// ������ ���ϱ�
	int		GetInteger();
	// �Ǽ��� ���ϱ�
	double	GetDouble();
	// Į���ȣ ���ϱ�
	int		GetColorNum();

	// ���̿� ������ ��ġ ���ϱ� 
	void	GetAnglePos(double dCenX, double dCenY, double dLength, double dAngle, double& dX, double& dY);

	// �� ������ ����
	void	AddPoint();
	// �� ������ ����
	void	AddLine();
	// M�� ������ ����
	void	AddMLine();
	// X�� ������ ����
	void	AddXLine();
	// SP�� ������ ����
	void	AddSPLine();
	// POLY�� ������ ����
	void	AddPolyLine();
	// LWPoly�� ������ ����
	void	AddLWPolyLine();
	// �� ������ ����
	void	AddCircle();
	// ȣ ������ ����
	void	AddArc();
	// Ÿ�� ������ ����
	void	AddEllipse();
	// ��ġ ������ ����
	void	AddHatch();
	// �׸� ������ ����
	void	AddImage();
	// ���� ������ ����
	void	AddText();
	// M���� ������ ����
	void	AddMText();
	// LAYER ������ ����
	void	AddLayer();
	// ������ ����
	void	AddObject();


protected:
	double m_dHeight;
	double m_dWidth;
	DWORD m_dwVectorLength;
	typedef struct tagTEMPLINE
	{
		DWORD	dwColor;					// ���� ����
		double	dX1;						// ���� X����� ��ġ
		double	dY1;						// ���� Y����� ��ġ
		double	dX2;						// ���� X�ೡ ��ġ
		double	dY2;						// ���� Y�ೡ ��ġ
	}TEMPLINE, *LPTEMPLINE;

	typedef struct tagLAYER
	{
		CString	strLayer;					// ���̾� ��
		int		nColorNum;					// ���̾� �����ȣ
	}LAYER, *LPLAYER;	

	typedef struct tagLWPOLYLINEDATA
	{
		double	d10;
		double	d20;
		double	d42;
	}LWPOLYLINEDATA, *LPLWPOLYLINEDATA;

	CList<IMPORTDATA, IMPORTDATA&> m_cList;		// ������ ����������

	CStdioFile	m_fileFP;					// DXF�� ����

	CString		m_strCurrent;				// ���� ���� ������
	CString		m_strFormer;				// ���� ���� ������

	int			m_nGroupCode;				// �׷��ڵ� ����
	int			m_nColorNum;				// �۾� �����ȣ

	int			m_nLayerPos;				// ���̾� ī��Ʈ
	int			m_nLayerMax;				// ���̾� ��ü ����
	LPLAYER		m_lpLayer;					// ���̾��� �����ȣ

	double		m_dMoveX;					// �߽����� X�� �̵���
	double		m_dMoveY;					// �߽����� Y�� �̵���
	double		m_dMinX;					// X���� �ּҰ�
	double		m_dMinY;					// Y���� �ּҰ�
	double		m_dMaxX;					// X���� �ִ밪
	double		m_dMaxY;					// Y���� �ִ밪

	int			m_nTotalCount;				// ��ü ���ǰ���
	int			m_nRowCount;				// ���� �������� ����
	int			m_nColCount;				// ���� �������� ����

	int			m_nColorMax;				// Pen color ����
	DWORD		m_dwTable[255];				// pen color ���� ���

	// �ӽ� ������ ����������
//	CArray<TEMPLINE, TEMPLINE>m_dTemp[MAX_TEMPDATA];

	//Vector *m_pVector;
};

#endif // _IMPORTDXF_H_