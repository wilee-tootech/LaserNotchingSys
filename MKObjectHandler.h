// MKObjectHandler.h: interface for the CMKObjectHandler class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MKOBJECTHANDLER_H__EDB3371A_EB83_41BA_952E_0B13136DA9B6__INCLUDED_)
#define AFX_MKOBJECTHANDLER_H__EDB3371A_EB83_41BA_952E_0B13136DA9B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMKObject;


#define C_LB 1
#define C_CB 2
#define C_RB 3
#define C_LC 4
#define C_CC 5
#define C_RC 6
#define C_LT 7
#define C_CT 8
#define C_RT 9

// w
// Object 자체가 자신이 선택되었을때 어떻게 그릴지에 대한 클래스 포인터를 가지고 있는게 어떤지.
// 또한 이놈의 CMKObjectHandler 자체도 Singleton 이 아닌 각 오브젝트가 핸들링에대한 포인터를
//가지고 있어야한다.
// 즉.. CWnd 의 개념으로 접근해야한다.			04.04.28



class CMKObjectHandler
{
public:
	
	static void Remove();
	
	CMKObjectHandler();
	virtual ~CMKObjectHandler();
	void SetObject(CMKObject *pObject);
	CMKObject *GetObject();
	void SetRegion(DWORD dwX,DWORD dwY); //근접 허용정도 몇픽셀 주변까지 되게 할꺼냐!!
	void GetRegion(DWORD &dwX, DWORD &dwY);
	UINT Calculate(CDRect rtSrc,CPoint ptMouse, double dAngle);

	BOOL IsIn(long x, long y, CPoint point);
	BOOL IsIn(CPoint ptGuide, CPoint ptMouse);
	
	void Clear();


	UINT HandleMouse(CPoint point); //만약. 선택 가능영역에 딱걸리면.!!! GetCapture을 하겠지?
	//그러니깐 순간적으로 이녀석이 마우스 정보를 가로채기 시작하고 LButtonUp이 되면 캡쳐를 그만 하겠지.
	static CMKObjectHandler *Instance();

	
private:
	static CMKObjectHandler *m_pInstance;

	DWORD m_dwY;
	DWORD m_dwX;
	CMKObject *m_pObject;
};

#endif // !defined(AFX_MKOBJECTHANDLER_H__EDB3371A_EB83_41BA_952E_0B13136DA9B6__INCLUDED_)
