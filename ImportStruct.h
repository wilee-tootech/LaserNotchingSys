#ifndef _IMPORTSTRUCT_H_
#define _IMPORTSTRUCT_H_

#define MAX_IMPORT_COLOR		255			// ���Խ� �۾�����
#define MAX_IMPORT_COLOR_HPGL	7			// HPGL�� �ִ� �۾� ����

#define IMPORT_POINT			0x00		// ��
#define IMPORT_LINE				0x01		// ��
#define IMPORT_CIRCLE			0x02		// ��
#define IMPORT_ARC				0x03		// ȣ
#define IMPORT_ELLIPSE			0x05		// Ÿ��
#define IMPORT_BEZIER			0x06		// ������
#define IMPORT_POLYLINE			0x07		// Poly��


typedef struct tagIMPORTDATA
{
	struct
	{
		UINT	nCode;					// ������ ����
		DWORD	dwColor;				// ������ ����
	}Attrib;
	union
	{
		struct
		{
			double	dX;					// ���� X����ġ
			double	dY;					// ���� Y����ġ
		}Point;
		struct
		{
			double	dX1;				// ���� X1����ġ
			double	dY1;				// ���� Y1����ġ
			double	dX2;				// ���� X2����ġ
			double	dY2;				// ���� Y2����ġ
		}Line;
		struct
		{
			double	dXC;				// ���� X�� �߽���ġ
			double	dYC;				// ���� Y�� �߽���ġ
			double	dRad;				// ���� ������
		}Circle;
		struct
		{
			double	dXC;				// ȣ�� X�� �߽���ġ
			double	dYC;				// ȣ�� Y�� �߽���ġ
			double	dRad;				// ȣ�� ������
			double	dSAng;				// ȣ�� ���� ����
			double	dEAng;				// ȣ�� �� ����
		}Arc;
		struct
		{
			double	dXC;				// Ÿ���� X�� �߽���ġ
			double	dYC;				// Ÿ���� Y�� �߽���ġ
			double	dReltoXC;			// Ÿ���߽ɿ��� ������� ������ x��ġ
			double	dReltoYC;			// Ÿ���߽ɿ��� ������� ������ y��ġ
			double	dRatioAxi;			// ����� ������ ����
//			double	dXRad;				// Ÿ���� X�������
//			double	dYRad;				// Ÿ���� Y�������
//			double	dSAng;				// Ÿ���� ���� ����
//			double	dEAng;				// Ÿ���� �� ����
		}Ellipse;
		struct
		{
			double	dX1;				// ��� X1����ġ
			double	dY1;				// ��� Y1����ġ
			double	dX2;				// ��� X2����ġ
			double	dY2;				// ��� Y2����ġ
			double	dX3;				// ��� X3����ġ
			double	dY3;				// ��� Y3����ġ
			double	dX4;				// ��� X4����ġ
			double	dY4;				// ��� Y4����ġ
		}Bezier;
		struct
		{
			int		totalPoint;			// ���� ����
			int		currPoint;
			int		polyFlag;
			double	*dX;				// ���� X����ġ
			double	*dY;				// ���� Y����ġ
		}PolyLine;
	}Data;
}IMPORTDATA, *LPIMPORTDATA;

#endif // _IMPORTSTRUCT_H_