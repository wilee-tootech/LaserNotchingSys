
#ifndef _UserInterface
#define _UserInterface

// 유저와 교류하는 부분. 이를 통해서 되도록 
// 메인 뷰에서 이루어지는 행동들만을 정의한다.. State패턴적용
// 예를들어 보통상태에서 마우스클릭한경우는
// 오브젝트가 선택되어져야한다. 그런 코드들.

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
	friend class CUserState;   // 모든 함수를 state에 떠넘긴다.
	friend class CBeamEditor6View;
	friend class CMainFrame;
	friend class Command;
	friend class CMDCreateArc;
	friend class CMDCreateLine;
	friend class CMDChangeOrder;
	void ChangeState(CUserState*);

private:
	CUserState *_state;  //CUserState를 상속받은 많은 상태 클래스들이
						 // 현재 동작에 맞는 행동을 구현한다. 
};


#endif
	
