// PointTranslator.h: interface for the CPointTranslator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINTTRANSLATOR_H__0B266248_6A54_418D_B07C_A885EB85A3CD__INCLUDED_)
#define AFX_POINTTRANSLATOR_H__0B266248_6A54_418D_B07C_A885EB85A3CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//   : �ʵ������ ����Ʈ������ �����ϰ� �ٲ��ִ� Ŭ����.
// ScreenOffset �� ScreenZoom �ΰ��� ������ �����ϰ� �̿��ؼ� ����ؼ� ��� ���� ��ȯ �Ѵ�.
// �ᱹ�� Field�� Point�� ������ ScreenZoom �� �� ���̰� ScreenOffset�� �ʵ� ������ �ɰ��̴�.
// �׷��� �����ϸ� �ϳ��� ����̽��� ���ؼ� �󸶳� ����Ʈ�� �����ϰ� �ɰ������� ����Ҽ� �������̴�.

class CPointTranslator  
{
public:
	CPointTranslator(double ScreenZoom, CDPoint ScreenOffset);
	virtual ~CPointTranslator();
	void FieldtoPoint(double dX,double dY, double &iX, double &iY); //�ʵ带 ȭ����� ��ǥ (Offset, Zoom���µ��� ����Ͽ�)
	void FieldtoPoint(const CRect &srcRect, CRect &desRect);   // Field������ Rect�� �Ѱܼ� Point������ Rect�� �����޴´�.
	void FieldtoPoint(const CDRect &srcRect, CDRect &desRect);

	CPointTranslator(double dScreenZoomX, double dScreenZoomY, CPoint ScreenOffset);


	void FieldtoRealView(const CRect &srcRect, CRect &desRect); //�ʵ� ���� ���ڰ� ������ ȭ����� ��ġ�� ��ǥ.
	void FieldtoRealView(const CDRect &srcRect, CDRect &desRect); //double ������ 
	void FieldtoRealView(const CRect srcRect, CDRect &desRect);

	void PointtoField(double iX, double iY, double &dX, double &dY); //����Ʈ�� �ʵ��.

private:
	double m_ScreenZoom;
	double m_ScreenZoomOther;
	CDPoint m_ScreenOffset;

};

#endif // !defined(AFX_POINTTRANSLATOR_H__0B266248_6A54_418D_B07C_A885EB85A3CD__INCLUDED_)
