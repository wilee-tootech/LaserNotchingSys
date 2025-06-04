#ifndef _IMPORTSTRUCT_H_
#define _IMPORTSTRUCT_H_

#define MAX_IMPORT_COLOR		255			// 수입시 작업색상
#define MAX_IMPORT_COLOR_HPGL	7			// HPGL의 최대 작업 색상

#define IMPORT_POINT			0x00		// 점
#define IMPORT_LINE				0x01		// 선
#define IMPORT_CIRCLE			0x02		// 원
#define IMPORT_ARC				0x03		// 호
#define IMPORT_ELLIPSE			0x05		// 타원
#define IMPORT_BEZIER			0x06		// 베지어
#define IMPORT_POLYLINE			0x07		// Poly선


typedef struct tagIMPORTDATA
{
	struct
	{
		UINT	nCode;					// 도형의 종류
		DWORD	dwColor;				// 도형의 색상
	}Attrib;
	union
	{
		struct
		{
			double	dX;					// 점의 X축위치
			double	dY;					// 점의 Y축위치
		}Point;
		struct
		{
			double	dX1;				// 선의 X1축위치
			double	dY1;				// 선의 Y1축위치
			double	dX2;				// 선의 X2축위치
			double	dY2;				// 선의 Y2축위치
		}Line;
		struct
		{
			double	dXC;				// 원의 X축 중심위치
			double	dYC;				// 원의 Y축 중심위치
			double	dRad;				// 원의 반지름
		}Circle;
		struct
		{
			double	dXC;				// 호의 X축 중심위치
			double	dYC;				// 호의 Y축 중심위치
			double	dRad;				// 호의 반지름
			double	dSAng;				// 호의 시작 각도
			double	dEAng;				// 호의 끝 각도
		}Arc;
		struct
		{
			double	dXC;				// 타원의 X축 중심위치
			double	dYC;				// 타원의 Y축 중심위치
			double	dReltoXC;			// 타원중심에서 상대적인 장축의 x위치
			double	dReltoYC;			// 타원중심에서 상대적인 장축의 y위치
			double	dRatioAxi;			// 장축과 단축의 비율
//			double	dXRad;				// 타원의 X축반지름
//			double	dYRad;				// 타원의 Y축반지름
//			double	dSAng;				// 타원의 시작 각도
//			double	dEAng;				// 타원의 끝 각도
		}Ellipse;
		struct
		{
			double	dX1;				// 곡선의 X1축위치
			double	dY1;				// 곡선의 Y1축위치
			double	dX2;				// 곡선의 X2축위치
			double	dY2;				// 곡선의 Y2축위치
			double	dX3;				// 곡선의 X3축위치
			double	dY3;				// 곡선의 Y3축위치
			double	dX4;				// 곡선의 X4축위치
			double	dY4;				// 곡선의 Y4축위치
		}Bezier;
		struct
		{
			int		totalPoint;			// 정점 개수
			int		currPoint;
			int		polyFlag;
			double	*dX;				// 점의 X축위치
			double	*dY;				// 점의 Y축위치
		}PolyLine;
	}Data;
}IMPORTDATA, *LPIMPORTDATA;

#endif // _IMPORTSTRUCT_H_