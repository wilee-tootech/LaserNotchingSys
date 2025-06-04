
#ifndef _UserInterface
#define _UserInterface

// ������ �����ϴ� �κ�. �̸� ���ؼ� �ǵ��� 
// ���� �信�� �̷������ �ൿ�鸸�� �����Ѵ�.. State��������
// ������� ������¿��� ���콺Ŭ���Ѱ���
// ������Ʈ�� ���õǾ������Ѵ�. �׷� �ڵ��.

#include "UserState.h"


class CUserInterface
{

public:
	CUserInterface();
	virtual ~CUserInterface();


	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnLButtonDblClk( UINT nFlags, CPoint point);
	void OnRButtonDown(UINT nFlags, CPoint point);
	void OnRButtonUp(UINT nFlags, CPoint point);
	void OnRButtonDblClk( UINT nFlags, CPoint point);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags );
	
	void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

private:
	friend class CUserState;   // ��� �Լ��� state�� ���ѱ��.
	friend class CBeamEditor6View;
	friend class CMainFrame;
	friend class Command;
	friend class CMDCreateArc;
	friend class CMDCreateLine;
	friend class CMDChangeOrder;
	void ChangeState(CUserState*);

private:
	CUserState *_state;  //CUserState�� ��ӹ��� ���� ���� Ŭ��������
						 // ���� ���ۿ� �´� �ൿ�� �����Ѵ�. 
};


#endif
	
