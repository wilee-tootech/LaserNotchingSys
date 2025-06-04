#pragma once
#include "Picture.h"

// 컴퓨터에서 Microsoft Visual C++를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// 참고: 이 파일의 내용을 수정하지 마십시오. Microsoft Visual C++에서
//  이 클래스를 다시 생성할 때 수정한 내용을 덮어씁니다.

/////////////////////////////////////////////////////////////////////////////
// CctSpein 래퍼 클래스입니다.

class CctSpein : public CWnd
{
protected:
	DECLARE_DYNCREATE(CctSpein)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x96AA3C1E, 0xCE88, 0x11D4, { 0xA1, 0xFF, 0x0, 0xE0, 0x98, 0x85, 0x64, 0x12 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// 특성입니다.
public:
enum
{
    ArrowSmall = 0,
    ArrowLarge = 1
}enumArrowSize;
enum
{
    SpinVert = 0,
    SpinHorz = 1
}enumSpinStyle;
enum
{
    BorderNone = 0,
    BorderFixed = 1
}enumBorderStyle;
enum
{
    mpDefault = 0,
    mpArrow = 1,
    mpCross = 2,
    mpIBeam = 3,
    mpIcon = 4,
    mpSize = 5,
    mpSizeNESW = 6,
    mpSize_NS = 7,
    mpSize_NW_SE = 8,
    mpSize_WE = 9,
    mpUp_Arrow = 10,
    mpHourglass = 11,
    mpNo_Drop = 12,
    mpApp_Starting = 13,
    mpQuestion = 14,
    mpSize_All = 15,
    mpFinger = 16,
    mpCustom = 99
}enumMousePointer;


// 작업입니다.
public:

// _DctSpin

// Functions
//

	void StopTimer()
	{
		InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

// Properties
//

BOOL GetEnabled()
{
	BOOL result;
	GetProperty(DISPID_ENABLED, VT_BOOL, (void*)&result);
	return result;
}
void SetEnabled(BOOL propVal)
{
	SetProperty(DISPID_ENABLED, VT_BOOL, propVal);
}
OLE_HANDLE GethWnd()
{
	OLE_HANDLE result;
	GetProperty(DISPID_HWND, VT_I4, (void*)&result);
	return result;
}
void SethWnd(OLE_HANDLE propVal)
{
	SetProperty(DISPID_HWND, VT_I4, propVal);
}
unsigned long GetBackColor()
{
	unsigned long result;
	GetProperty(0x1, VT_UI4, (void*)&result);
	return result;
}
void SetBackColor(unsigned long propVal)
{
	SetProperty(0x1, VT_UI4, propVal);
}
unsigned long GetArrowColor()
{
	unsigned long result;
	GetProperty(0x2, VT_UI4, (void*)&result);
	return result;
}
void SetArrowColor(unsigned long propVal)
{
	SetProperty(0x2, VT_UI4, propVal);
}
short GetBevelSize()
{
	short result;
	GetProperty(0x3, VT_I2, (void*)&result);
	return result;
}
void SetBevelSize(short propVal)
{
	SetProperty(0x3, VT_I2, propVal);
}
unsigned long GetBorderColor()
{
	unsigned long result;
	GetProperty(0x4, VT_UI4, (void*)&result);
	return result;
}
void SetBorderColor(unsigned long propVal)
{
	SetProperty(0x4, VT_UI4, propVal);
}
unsigned long GetDisableColor()
{
	unsigned long result;
	GetProperty(0x5, VT_UI4, (void*)&result);
	return result;
}
void SetDisableColor(unsigned long propVal)
{
	SetProperty(0x5, VT_UI4, propVal);
}
short GetRepeatRate()
{
	short result;
	GetProperty(0x6, VT_I2, (void*)&result);
	return result;
}
void SetRepeatRate(short propVal)
{
	SetProperty(0x6, VT_I2, propVal);
}
short GetInitialDelay()
{
	short result;
	GetProperty(0x7, VT_I2, (void*)&result);
	return result;
}
void SetInitialDelay(short propVal)
{
	SetProperty(0x7, VT_I2, propVal);
}
long GetSpinStyle()
{
	long result;
	GetProperty(0x8, VT_I4, (void*)&result);
	return result;
}
void SetSpinStyle(long propVal)
{
	SetProperty(0x8, VT_I4, propVal);
}
long GetArrowSize()
{
	long result;
	GetProperty(0x9, VT_I4, (void*)&result);
	return result;
}
void SetArrowSize(long propVal)
{
	SetProperty(0x9, VT_I4, propVal);
}
long GetBorderStyle()
{
	long result;
	GetProperty(0xa, VT_I4, (void*)&result);
	return result;
}
void SetBorderStyle(long propVal)
{
	SetProperty(0xa, VT_I4, propVal);
}
long GetMousePointer1()
{
	long result;
	GetProperty(0xb, VT_I4, (void*)&result);
	return result;
}
void SetMousePointer1(long propVal)
{
	SetProperty(0xb, VT_I4, propVal);
}
long GetMousePointer2()
{
	long result;
	GetProperty(0xc, VT_I4, (void*)&result);
	return result;
}
void SetMousePointer2(long propVal)
{
	SetProperty(0xc, VT_I4, propVal);
}
CPicture GetMouseIcon1()
{
	LPDISPATCH result;
	GetProperty(0xd, VT_DISPATCH, (void*)&result);
	return CPicture(result);
}
void SetMouseIcon1(LPDISPATCH propVal)
{
	SetProperty(0xd, VT_DISPATCH, propVal);
}
CPicture GetMouseIcon2()
{
	LPDISPATCH result;
	GetProperty(0xe, VT_DISPATCH, (void*)&result);
	return CPicture(result);
}
void SetMouseIcon2(LPDISPATCH propVal)
{
	SetProperty(0xe, VT_DISPATCH, propVal);
}
short GetMouseIndex1()
{
	short result;
	GetProperty(0xf, VT_I2, (void*)&result);
	return result;
}
void SetMouseIndex1(short propVal)
{
	SetProperty(0xf, VT_I2, propVal);
}
short GetMouseIndex2()
{
	short result;
	GetProperty(0x10, VT_I2, (void*)&result);
	return result;
}
void SetMouseIndex2(short propVal)
{
	SetProperty(0x10, VT_I2, propVal);
}


};
