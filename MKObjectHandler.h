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
// Object ��ü�� �ڽ��� ���õǾ����� ��� �׸����� ���� Ŭ���� �����͸� ������ �ִ°� ���.
// ���� �̳��� CMKObjectHandler ��ü�� Singleton �� �ƴ� �� ������Ʈ�� �ڵ鸵������ �����͸�
//������ �־���Ѵ�.
// ��.. CWnd �� �������� �����ؾ��Ѵ�.			04.04.28



class CMKObjectHandler
{
public:
	
	static void Remove();
	
	CMKObjectHandler();
	virtual ~CMKObjectHandler();
	void SetObject(CMKObject *pObject);
	CMKObject *GetObject();
	void SetRegion(DWORD dwX,DWORD dwY); //���� ������� ���ȼ� �ֺ����� �ǰ� �Ҳ���!!
	void GetRegion(DWORD &dwX, DWORD &dwY);
	UINT Calculate(CDRect rtSrc,CPoint ptMouse, double dAngle);

	BOOL IsIn(long x, long y, CPoint point);
	BOOL IsIn(CPoint ptGuide, CPoint ptMouse);
	
	void Clear();


	UINT HandleMouse(CPoint point); //����. ���� ���ɿ����� ���ɸ���.!!! GetCapture�� �ϰ���?
	//�׷��ϱ� ���������� �̳༮�� ���콺 ������ ����ä�� �����ϰ� LButtonUp�� �Ǹ� ĸ�ĸ� �׸� �ϰ���.
	static CMKObjectHandler *Instance();

	
private:
	static CMKObjectHandler *m_pInstance;

	DWORD m_dwY;
	DWORD m_dwX;
	CMKObject *m_pObject;
};

#endif // !defined(AFX_MKOBJECTHANDLER_H__EDB3371A_EB83_41BA_952E_0B13136DA9B6__INCLUDED_)
