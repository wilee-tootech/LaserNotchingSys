// PointTranslator.h: interface for the CPointTranslator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINTTRANSLATOR_H__0B266248_6A54_418D_B07C_A885EB85A3CD__INCLUDED_)
#define AFX_POINTTRANSLATOR_H__0B266248_6A54_418D_B07C_A885EB85A3CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//   : 필드단위를 포인트단위로 적절하게 바꿔주는 클래스.
// ScreenOffset 과 ScreenZoom 두가지 변수를 적절하게 이용해서 계산해서 결과 값을 반환 한다.
// 결국은 Field와 Point의 비율이 ScreenZoom 이 될 것이고 ScreenOffset은 필드 단위가 될것이다.
// 그렇게 생각하면 하나의 디바이스에 대해서 얼마난 포인트가 차지하게 될것인지도 계산할수 있을것이다.

class CPointTranslator  
{
public:
	CPointTranslator(double ScreenZoom, CDPoint ScreenOffset);
	virtual ~CPointTranslator();
	void FieldtoPoint(double dX,double dY, double &iX, double &iY); //필드를 화면상의 좌표 (Offset, Zoom상태등을 고려하여)
	void FieldtoPoint(const CRect &srcRect, CRect &desRect);   // Field단위의 Rect를 넘겨서 Point단위의 Rect를 돌려받는다.
	void FieldtoPoint(const CDRect &srcRect, CDRect &desRect);

	CPointTranslator(double dScreenZoomX, double dScreenZoomY, CPoint ScreenOffset);


	void FieldtoRealView(const CRect &srcRect, CRect &desRect); //필드 단위 상자가 실제로 화면상의 위치할 좌표.
	void FieldtoRealView(const CDRect &srcRect, CDRect &desRect); //double 단위로 
	void FieldtoRealView(const CRect srcRect, CDRect &desRect);

	void PointtoField(double iX, double iY, double &dX, double &dY); //포인트를 필드로.

private:
	double m_ScreenZoom;
	double m_ScreenZoomOther;
	CDPoint m_ScreenOffset;

};

#endif // !defined(AFX_POINTTRANSLATOR_H__0B266248_6A54_418D_B07C_A885EB85A3CD__INCLUDED_)
