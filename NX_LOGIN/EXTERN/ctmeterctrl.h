#pragma once
#include "_Picture.h"
#include "_Font.h"

// 컴퓨터에서 Microsoft Visual C++를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// 참고: 이 파일의 내용을 수정하지 마십시오. Microsoft Visual C++에서
//  이 클래스를 다시 생성할 때 수정한 내용을 덮어씁니다.

/////////////////////////////////////////////////////////////////////////////
// CCtmeterctrl 래퍼 클래스입니다.

class CCtmeterctrl : public CWnd
{
protected:
	DECLARE_DYNCREATE(CCtmeterctrl)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x5A1B36C6, 0xCB42, 0x11D4, { 0xA1, 0xFF, 0x0, 0xE0, 0x98, 0x85, 0x64, 0x12 } };
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
    BorderRegular = 0,
    BorderNone = 1,
    BorderRaised = 2,
    BorderLowered = 3,
    BorderDrop = 4,
    BorderInset = 5
}enumBorder;
enum
{
    MeterHorz = 0,
    MeterVert = 1
}enumMeterStyle;
enum
{
    AlignLeft = 0,
    AlignRight = 1,
    AlignCenter = 2
}enumAlign;
enum
{
    DisplayRegular = 0,
    DisplayBlocked = 1
}enumDisplay;


// 작업입니다.
public:

// _DctMeter

// Functions
//

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
COleFont GetFont()
{
	LPDISPATCH result;
	GetProperty(DISPID_FONT, VT_DISPATCH, (void*)&result);
	return COleFont(result);
}
void SetFont(LPDISPATCH propVal)
{
	SetProperty(DISPID_FONT, VT_DISPATCH, propVal);
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
CString GetCaption()
{
	CString result;
	GetProperty(DISPID_CAPTION, VT_BSTR, (void*)&result);
	return result;
}
void SetCaption(CString propVal)
{
	SetProperty(DISPID_CAPTION, VT_BSTR, propVal);
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
unsigned long GetForeColor()
{
	unsigned long result;
	GetProperty(0x2, VT_UI4, (void*)&result);
	return result;
}
void SetForeColor(unsigned long propVal)
{
	SetProperty(0x2, VT_UI4, propVal);
}
long GetBorderType()
{
	long result;
	GetProperty(0x3, VT_I4, (void*)&result);
	return result;
}
void SetBorderType(long propVal)
{
	SetProperty(0x3, VT_I4, propVal);
}
long GetMeterStyle()
{
	long result;
	GetProperty(0x4, VT_I4, (void*)&result);
	return result;
}
void SetMeterStyle(long propVal)
{
	SetProperty(0x4, VT_I4, propVal);
}
unsigned long GetShadowColor()
{
	unsigned long result;
	GetProperty(0x5, VT_UI4, (void*)&result);
	return result;
}
void SetShadowColor(unsigned long propVal)
{
	SetProperty(0x5, VT_UI4, propVal);
}
unsigned long GetBorderColor()
{
	unsigned long result;
	GetProperty(0x6, VT_UI4, (void*)&result);
	return result;
}
void SetBorderColor(unsigned long propVal)
{
	SetProperty(0x6, VT_UI4, propVal);
}
long GetValue()
{
	long result;
	GetProperty(0x7, VT_I4, (void*)&result);
	return result;
}
void SetValue(long propVal)
{
	SetProperty(0x7, VT_I4, propVal);
}
long GetMinValue()
{
	long result;
	GetProperty(0x8, VT_I4, (void*)&result);
	return result;
}
void SetMinValue(long propVal)
{
	SetProperty(0x8, VT_I4, propVal);
}
long GetMaxValue()
{
	long result;
	GetProperty(0x9, VT_I4, (void*)&result);
	return result;
}
void SetMaxValue(long propVal)
{
	SetProperty(0x9, VT_I4, propVal);
}
BOOL GetDisplayText()
{
	BOOL result;
	GetProperty(0xa, VT_BOOL, (void*)&result);
	return result;
}
void SetDisplayText(BOOL propVal)
{
	SetProperty(0xa, VT_BOOL, propVal);
}
long GetMeterValue()
{
	long result;
	GetProperty(0xb, VT_I4, (void*)&result);
	return result;
}
void SetMeterValue(long propVal)
{
	SetProperty(0xb, VT_I4, propVal);
}
BOOL GetUseCaption()
{
	BOOL result;
	GetProperty(0xc, VT_BOOL, (void*)&result);
	return result;
}
void SetUseCaption(BOOL propVal)
{
	SetProperty(0xc, VT_BOOL, propVal);
}
long GetAlignment()
{
	long result;
	GetProperty(0xd, VT_I4, (void*)&result);
	return result;
}
void SetAlignment(long propVal)
{
	SetProperty(0xd, VT_I4, propVal);
}
BOOL GetThinBorder()
{
	BOOL result;
	GetProperty(0xe, VT_BOOL, (void*)&result);
	return result;
}
void SetThinBorder(BOOL propVal)
{
	SetProperty(0xe, VT_BOOL, propVal);
}
long GetDisplayStyle()
{
	long result;
	GetProperty(0xf, VT_I4, (void*)&result);
	return result;
}
void SetDisplayStyle(long propVal)
{
	SetProperty(0xf, VT_I4, propVal);
}
_CPicture GetBackImage()
{
	LPDISPATCH result;
	GetProperty(0x10, VT_DISPATCH, (void*)&result);
	return _CPicture(result);
}
void SetBackImage(LPDISPATCH propVal)
{
	SetProperty(0x10, VT_DISPATCH, propVal);
}
short GetImageXOffset()
{
	short result;
	GetProperty(0x11, VT_I2, (void*)&result);
	return result;
}
void SetImageXOffset(short propVal)
{
	SetProperty(0x11, VT_I2, propVal);
}
short GetImageYOffset()
{
	short result;
	GetProperty(0x12, VT_I2, (void*)&result);
	return result;
}
void SetImageYOffset(short propVal)
{
	SetProperty(0x12, VT_I2, propVal);
}
short GetBlockSize()
{
	short result;
	GetProperty(0x13, VT_I2, (void*)&result);
	return result;
}
void SetBlockSize(short propVal)
{
	SetProperty(0x13, VT_I2, propVal);
}
short GetBlockMargin()
{
	short result;
	GetProperty(0x14, VT_I2, (void*)&result);
	return result;
}
void SetBlockMargin(short propVal)
{
	SetProperty(0x14, VT_I2, propVal);
}
BOOL GetSquareBlocks()
{
	BOOL result;
	GetProperty(0x15, VT_BOOL, (void*)&result);
	return result;
}
void SetSquareBlocks(BOOL propVal)
{
	SetProperty(0x15, VT_BOOL, propVal);
}
unsigned long GetChangeColor()
{
	unsigned long result;
	GetProperty(0x16, VT_UI4, (void*)&result);
	return result;
}
void SetChangeColor(unsigned long propVal)
{
	SetProperty(0x16, VT_UI4, propVal);
}
short GetChangeValue()
{
	short result;
	GetProperty(0x17, VT_I2, (void*)&result);
	return result;
}
void SetChangeValue(short propVal)
{
	SetProperty(0x17, VT_I2, propVal);
}
unsigned long GetTextColor()
{
	unsigned long result;
	GetProperty(0x18, VT_UI4, (void*)&result);
	return result;
}
void SetTextColor(unsigned long propVal)
{
	SetProperty(0x18, VT_UI4, propVal);
}


};
