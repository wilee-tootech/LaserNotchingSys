#pragma once
#include "_Picture.h"
#include "_Font.h"

// 컴퓨터에서 Microsoft Visual C++를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// 참고: 이 파일의 내용을 수정하지 마십시오. Microsoft Visual C++에서
//  이 클래스를 다시 생성할 때 수정한 내용을 덮어씁니다.

/////////////////////////////////////////////////////////////////////////////
// CCttextctrl 래퍼 클래스입니다.

class CCttextctrl : public CWnd
{
protected:
	DECLARE_DYNCREATE(CCttextctrl)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x5628C5DE, 0xCCD5, 0x11D4, { 0xA1, 0xFF, 0x0, 0xE0, 0x98, 0x85, 0x64, 0x12 } };
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
    AlignLeft = 0,
    AlignRight = 1,
    AlignCenter = 2
}enumAlign;
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
    TextTop = 0,
    TextBottom = 1,
    TextCenter = 2
}enumTextPosn;
enum
{
    PicCenter = 0,
    PicTopLeft = 1,
    PicTopCenter = 2,
    PicTopRight = 3,
    PicMidLeft = 4,
    PicMidRight = 5,
    PicBotLeft = 6,
    PicBotCenter = 7,
    PicBotRight = 8,
    PicStretch = 9,
    PicTile = 10,
    PicHide = 11
}enumPicPosn;
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

// _DctText

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
long GetTextPosition()
{
	long result;
	GetProperty(0x4, VT_I4, (void*)&result);
	return result;
}
void SetTextPosition(long propVal)
{
	SetProperty(0x4, VT_I4, propVal);
}
long GetPicPosition()
{
	long result;
	GetProperty(0x5, VT_I4, (void*)&result);
	return result;
}
void SetPicPosition(long propVal)
{
	SetProperty(0x5, VT_I4, propVal);
}
short GetTextAngle()
{
	short result;
	GetProperty(0x6, VT_I2, (void*)&result);
	return result;
}
void SetTextAngle(short propVal)
{
	SetProperty(0x6, VT_I2, propVal);
}
CPicture GetPicture()
{
	LPDISPATCH result;
	GetProperty(0x7, VT_DISPATCH, (void*)&result);
	return CPicture(result);
}
void SetPicture(LPDISPATCH propVal)
{
	SetProperty(0x7, VT_DISPATCH, propVal);
}
unsigned long GetShadowColor()
{
	unsigned long result;
	GetProperty(0x8, VT_UI4, (void*)&result);
	return result;
}
void SetShadowColor(unsigned long propVal)
{
	SetProperty(0x8, VT_UI4, propVal);
}
BOOL GetSingleLine()
{
	BOOL result;
	GetProperty(0x9, VT_BOOL, (void*)&result);
	return result;
}
void SetSingleLine(BOOL propVal)
{
	SetProperty(0x9, VT_BOOL, propVal);
}
unsigned long GetThreeDColor()
{
	unsigned long result;
	GetProperty(0xa, VT_UI4, (void*)&result);
	return result;
}
void SetThreeDColor(unsigned long propVal)
{
	SetProperty(0xa, VT_UI4, propVal);
}
BOOL GetThreeDText()
{
	BOOL result;
	GetProperty(0xb, VT_BOOL, (void*)&result);
	return result;
}
void SetThreeDText(BOOL propVal)
{
	SetProperty(0xb, VT_BOOL, propVal);
}
unsigned long GetBorderColor()
{
	unsigned long result;
	GetProperty(0xc, VT_UI4, (void*)&result);
	return result;
}
void SetBorderColor(unsigned long propVal)
{
	SetProperty(0xc, VT_UI4, propVal);
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
short GetTextXOffset()
{
	short result;
	GetProperty(0xe, VT_I2, (void*)&result);
	return result;
}
void SetTextXOffset(short propVal)
{
	SetProperty(0xe, VT_I2, propVal);
}
short GetTextYOffset()
{
	short result;
	GetProperty(0xf, VT_I2, (void*)&result);
	return result;
}
void SetTextYOffset(short propVal)
{
	SetProperty(0xf, VT_I2, propVal);
}
BOOL GetWordWrap()
{
	BOOL result;
	GetProperty(0x10, VT_BOOL, (void*)&result);
	return result;
}
void SetWordWrap(BOOL propVal)
{
	SetProperty(0x10, VT_BOOL, propVal);
}
BOOL GetThinBorder()
{
	BOOL result;
	GetProperty(0x11, VT_BOOL, (void*)&result);
	return result;
}
void SetThinBorder(BOOL propVal)
{
	SetProperty(0x11, VT_BOOL, propVal);
}
CPicture GetBackImage()
{
	LPDISPATCH result;
	GetProperty(0x12, VT_DISPATCH, (void*)&result);
	return CPicture(result);
}
void SetBackImage(LPDISPATCH propVal)
{
	SetProperty(0x12, VT_DISPATCH, propVal);
}
short GetImageXOffset()
{
	short result;
	GetProperty(0x13, VT_I2, (void*)&result);
	return result;
}
void SetImageXOffset(short propVal)
{
	SetProperty(0x13, VT_I2, propVal);
}
short GetImageYOffset()
{
	short result;
	GetProperty(0x14, VT_I2, (void*)&result);
	return result;
}
void SetImageYOffset(short propVal)
{
	SetProperty(0x14, VT_I2, propVal);
}
BOOL GetCheckMouseOver()
{
	BOOL result;
	GetProperty(0x15, VT_BOOL, (void*)&result);
	return result;
}
void SetCheckMouseOver(BOOL propVal)
{
	SetProperty(0x15, VT_BOOL, propVal);
}
COleFont GetFontOver()
{
	LPDISPATCH result;
	GetProperty(0x16, VT_DISPATCH, (void*)&result);
	return COleFont(result);
}
void SetFontOver(LPDISPATCH propVal)
{
	SetProperty(0x16, VT_DISPATCH, propVal);
}
unsigned long GetForeColorOver()
{
	unsigned long result;
	GetProperty(0x17, VT_UI4, (void*)&result);
	return result;
}
void SetForeColorOver(unsigned long propVal)
{
	SetProperty(0x17, VT_UI4, propVal);
}
CPicture GetMouseIcon()
{
	LPDISPATCH result;
	GetProperty(0x18, VT_DISPATCH, (void*)&result);
	return CPicture(result);
}
void SetMouseIcon(LPDISPATCH propVal)
{
	SetProperty(0x18, VT_DISPATCH, propVal);
}
long GetMousePointer()
{
	long result;
	GetProperty(0x19, VT_I4, (void*)&result);
	return result;
}
void SetMousePointer(long propVal)
{
	SetProperty(0x19, VT_I4, propVal);
}
short GetMouseIndex()
{
	short result;
	GetProperty(0x1a, VT_I2, (void*)&result);
	return result;
}
void SetMouseIndex(short propVal)
{
	SetProperty(0x1a, VT_I2, propVal);
}
float GetFontSize()
{
	float result;
	GetProperty(0x1b, VT_R4, (void*)&result);
	return result;
}
void SetFontSize(float propVal)
{
	SetProperty(0x1b, VT_R4, propVal);
}
BOOL GetFontItalic()
{
	BOOL result;
	GetProperty(0x1c, VT_BOOL, (void*)&result);
	return result;
}
void SetFontItalic(BOOL propVal)
{
	SetProperty(0x1c, VT_BOOL, propVal);
}
BOOL GetFontBold()
{
	BOOL result;
	GetProperty(0x1d, VT_BOOL, (void*)&result);
	return result;
}
void SetFontBold(BOOL propVal)
{
	SetProperty(0x1d, VT_BOOL, propVal);
}
BOOL GetFontUnderline()
{
	BOOL result;
	GetProperty(0x1e, VT_BOOL, (void*)&result);
	return result;
}
void SetFontUnderline(BOOL propVal)
{
	SetProperty(0x1e, VT_BOOL, propVal);
}


};
