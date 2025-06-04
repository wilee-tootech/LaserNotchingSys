#pragma once
#include "./Include/EXTERN/Picture.h"
#include "./Include/EXTERN/Font.h"

// 컴퓨터에서 Microsoft Visual C++를 사용하여 생성한 IDispatch 래퍼 클래스입니다.

// 참고: 이 파일의 내용을 수정하지 마십시오. Microsoft Visual C++에서
//  이 클래스를 다시 생성할 때 수정한 내용을 덮어씁니다.

/////////////////////////////////////////////////////////////////////////////
// CCtlistctrl_log 래퍼 클래스입니다.

class CCtlistctrl_log : public CWnd
{
protected:
	DECLARE_DYNCREATE(CCtlistctrl_log)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x97CCB606, 0x956, 0x11D4, { 0x94, 0x66, 0xE4, 0xE1, 0xE, 0xC1, 0x0, 0x0 } };
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
    btRegular = 0,
    btNone = 1,
    btRaised = 2,
    btLowered = 3,
    btRaisedThin = 4,
    btLoweredThin = 5
}enumBorderType;
enum
{
    AlignLeft = 0,
    AlignRight = 1,
    AlignCenter = 2
}enumAlign;
enum
{
    ColumnNone = 0,
    ColumnArrow = 1,
    ColumnNum0 = 2,
    ColumnNum1 = 3,
    ColumnPicture = 4
}enumPreColumn;
enum
{
    TitleRegular = 0,
    TitleRaised = 1,
    TitleLowered = 2
}enumTitles;
enum
{
    FocusSolid = 0,
    FocusRectangle = 1
}enumFocus;
enum
{
    TipsLeft = 0,
    TipsRight = 1
}enumTipsPosn;
enum
{
    ArrowLeft = 0,
    ArrowRight = 1
}enumArrowAlign;
enum
{
    SortDescend = 0,
    SortAscend = 1
}enumSortDir;
enum
{
    SelectAll = 0,
    SelectText = 1
}enumSelectStyle;
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
    mpCustom = 99
}enumMousePointer;
enum
{
    MapText = 0,
    MapLoEnglish = 1,
    MapHiEnglish = 2,
    MapLoMetric = 3,
    MapHiMetric = 4,
    MapTwips = 5
}enumMapMode;
enum
{
    TipsNone = 0,
    TipsScroll = 1,
    TipsCell = 2,
    TipsBoth = 3
}enumTipsType;
enum
{
    Format_MDY = 0,
    Format_DMY = 1,
    Format_YDM = 2
}enumDateFormat;


// 작업입니다.
public:

// _DctList

// Functions
//

	short ColumnCount()
	{
		short result;
		InvokeHelper(0x80, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	short AddColumn(LPCTSTR strCaption, short nWidth)
	{
		short result;
		static BYTE parms[] = VTS_BSTR VTS_I2 ;
		InvokeHelper(0x81, DISPATCH_METHOD, VT_I2, (void*)&result, parms, strCaption, nWidth);
		return result;
	}
	BOOL ClearColumns()
	{
		BOOL result;
		InvokeHelper(0x82, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	long AddItem(LPCTSTR strText)
	{
		long result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x83, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strText);
		return result;
	}
	long ListCount()
	{
		long result;
		InvokeHelper(0x84, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	short InsertColumn(LPCTSTR strCaption, short nWidth, short nIndex)
	{
		short result;
		static BYTE parms[] = VTS_BSTR VTS_I2 VTS_I2 ;
		InvokeHelper(0x85, DISPATCH_METHOD, VT_I2, (void*)&result, parms, strCaption, nWidth, nIndex);
		return result;
	}
	long InsertItem(LPCTSTR strCaption, long nIndex)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 ;
		InvokeHelper(0x86, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strCaption, nIndex);
		return result;
	}
	BOOL ClearList()
	{
		BOOL result;
		InvokeHelper(0x87, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL RemoveColumn(short nIndex)
	{
		BOOL result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x88, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nIndex);
		return result;
	}
	BOOL RemoveItem(long nIndex)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x89, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nIndex);
		return result;
	}
	void ClearFont(long nIndex)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x8a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nIndex);
	}
	void ListFont(LPDISPATCH fntFont, long nIndex)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 ;
		InvokeHelper(0x8b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, fntFont, nIndex);
	}
	short ItemHeight()
	{
		short result;
		InvokeHelper(0x8c, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	long DragDrop(short nxPosn, short nyPosn)
	{
		long result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x8d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nxPosn, nyPosn);
		return result;
	}
	long DragOver(short nxPosn, short nyPosn, short nState)
	{
		long result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x8e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nxPosn, nyPosn, nState);
		return result;
	}
	void ReDraw(BOOL nType)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x8f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nType);
	}
	BOOL SortList()
	{
		BOOL result;
		InvokeHelper(0x90, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void CancelSort()
	{
		InvokeHelper(0x91, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL SortNewColumn(short nColumn)
	{
		BOOL result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x92, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nColumn);
		return result;
	}
	short SubTextHeight()
	{
		short result;
		InvokeHelper(0x93, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	short CalcSubTextHeight(long nIndex)
	{
		short result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x94, DISPATCH_METHOD, VT_I2, (void*)&result, parms, nIndex);
		return result;
	}
	long ctDragDrop(short nxPosn, short nyPosn)
	{
		long result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x95, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nxPosn, nyPosn);
		return result;
	}
	long ctDragOver(short nxPosn, short nyPosn, short nState)
	{
		long result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x96, DISPATCH_METHOD, VT_I4, (void*)&result, parms, nxPosn, nyPosn, nState);
		return result;
	}
	short AddImage(LPDISPATCH picImage)
	{
		short result;
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x97, DISPATCH_METHOD, VT_I2, (void*)&result, parms, picImage);
		return result;
	}
	BOOL RemoveImage(short nIndex)
	{
		BOOL result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x98, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nIndex);
		return result;
	}
	long RemoveSelected()
	{
		long result;
		InvokeHelper(0x99, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	void CancelEdit()
	{
		InvokeHelper(0x9a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL StartLabelEdit()
	{
		BOOL result;
		InvokeHelper(0x9b, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL PrintList()
	{
		BOOL result;
		InvokeHelper(0x9c, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void AbortPrint()
	{
		InvokeHelper(0x9d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL PrintInWindow(long nHDC, short nLeft, short nTop, short nRight, short nBottom)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 VTS_I2 VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0x9e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, nHDC, nLeft, nTop, nRight, nBottom);
		return result;
	}
	long FindText(LPCTSTR strText, long nIndex, short nColumn, BOOL bSoftSeek, BOOL bMatchCase)
	{
		long result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I2 VTS_BOOL VTS_BOOL ;
		InvokeHelper(0x9f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, strText, nIndex, nColumn, bSoftSeek, bMatchCase);
		return result;
	}
	void SortMultiColumns(short nColumn1, short nColumn2, short nColumn3)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 ;
		InvokeHelper(0xa0, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nColumn1, nColumn2, nColumn3);
	}
	short get_ColumnWidth(short nIndex)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xa1, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ColumnWidth(short nIndex, short newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0xa1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	short get_ColumnTextAlign(short nIndex)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xa2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ColumnTextAlign(short nIndex, short newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0xa2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	short get_ColumnPicture(short nIndex)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xa3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ColumnPicture(short nIndex, short newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0xa3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	CString get_ColumnText(short nIndex)
	{
		CString result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xa4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ColumnText(short nIndex, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_BSTR ;
		InvokeHelper(0xa4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	BOOL get_ColumnLock(short nIndex)
	{
		BOOL result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xa5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ColumnLock(short nIndex, BOOL newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_BOOL ;
		InvokeHelper(0xa5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	short get_ColumnCheckBox(short nIndex)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xa6, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ColumnCheckBox(short nIndex, short newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0xa6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	CString get_ListText(long nIndex)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xa7, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ListText(long nIndex, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0xa7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	unsigned long get_ListBackColor(long nIndex)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xa8, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ListBackColor(long nIndex, unsigned long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0xa8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	unsigned long get_ListForeColor(long nIndex)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xa9, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ListForeColor(long nIndex, unsigned long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_UI4 ;
		InvokeHelper(0xa9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	unsigned long get_ColumnBackColor(short nIndex)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xaa, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ColumnBackColor(short nIndex, unsigned long newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_UI4 ;
		InvokeHelper(0xaa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	BOOL get_ColumnSortable(short nIndex)
	{
		BOOL result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xab, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ColumnSortable(short nIndex, BOOL newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_BOOL ;
		InvokeHelper(0xab, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	unsigned long get_ColumnForeColor(short nIndex)
	{
		unsigned long result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xac, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ColumnForeColor(short nIndex, unsigned long newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_UI4 ;
		InvokeHelper(0xac, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	CString get_ListSubText(long nIndex)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xad, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ListSubText(long nIndex, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0xad, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	CString get_ListCargo(long nIndex)
	{
		CString result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xae, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ListCargo(long nIndex, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BSTR ;
		InvokeHelper(0xae, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	short get_ListSubHeight(long nIndex)
	{
		short result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xaf, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ListSubHeight(long nIndex, short newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I2 ;
		InvokeHelper(0xaf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	CString get_CellText(long nIndex, short nColumn)
	{
		CString result;
		static BYTE parms[] = VTS_I4 VTS_I2 ;
		InvokeHelper(0xb0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, nIndex, nColumn);
		return result;
	}
	void put_CellText(long nIndex, short nColumn, LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I2 VTS_BSTR ;
		InvokeHelper(0xb0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, nColumn, newValue);
	}
	short get_CellPicture(long nIndex, short nColumn)
	{
		short result;
		static BYTE parms[] = VTS_I4 VTS_I2 ;
		InvokeHelper(0xb1, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, nIndex, nColumn);
		return result;
	}
	void put_CellPicture(long nIndex, short nColumn, short newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I2 VTS_I2 ;
		InvokeHelper(0xb1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, nColumn, newValue);
	}
	short get_ColumnPictureAlign(short nIndex)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xb2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ColumnPictureAlign(short nIndex, short newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0xb2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	short get_ColumnCheckAlign(short nIndex)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xb3, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ColumnCheckAlign(short nIndex, short newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0xb3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	short get_CellCheck(long nIndex, short nColumn)
	{
		short result;
		static BYTE parms[] = VTS_I4 VTS_I2 ;
		InvokeHelper(0xb4, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, nIndex, nColumn);
		return result;
	}
	void put_CellCheck(long nIndex, short nColumn, short newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I2 VTS_I2 ;
		InvokeHelper(0xb4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, nColumn, newValue);
	}
	short get_CellPicSelect(long nIndex, short nColumn)
	{
		short result;
		static BYTE parms[] = VTS_I4 VTS_I2 ;
		InvokeHelper(0xb5, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, nIndex, nColumn);
		return result;
	}
	void put_CellPicSelect(long nIndex, short nColumn, short newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I2 VTS_I2 ;
		InvokeHelper(0xb5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, nColumn, newValue);
	}
	long get_ListData(long nIndex)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xb6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ListData(long nIndex, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0xb6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	BOOL get_ListSelect(long nIndex)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xb7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ListSelect(long nIndex, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0xb7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	short get_ListIndent(long nIndex)
	{
		short result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xb8, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ListIndent(long nIndex, short newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I2 ;
		InvokeHelper(0xb8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	short get_ListFontBold(long nIndex)
	{
		short result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xb9, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ListFontBold(long nIndex, short newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I2 ;
		InvokeHelper(0xb9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	LPDISPATCH get_ListImage(short nIndex)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xba, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ListImage(short nIndex, LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_DISPATCH ;
		InvokeHelper(0xba, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	BOOL get_ListHeader(long nIndex)
	{
		BOOL result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xbb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms, nIndex);
		return result;
	}
	void put_ListHeader(long nIndex, BOOL newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL ;
		InvokeHelper(0xbb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nIndex, newValue);
	}
	short get_ColumnDataType(short nColumn)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0xbc, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, parms, nColumn);
		return result;
	}
	void put_ColumnDataType(short nColumn, short newValue)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0xbc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, nColumn, newValue);
	}
	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

// Properties
//

unsigned long GetBackColor()
{
	unsigned long result;
	GetProperty(DISPID_BACKCOLOR, VT_UI4, (void*)&result);
	return result;
}
void SetBackColor(unsigned long propVal)
{
	SetProperty(DISPID_BACKCOLOR, VT_UI4, propVal);
}
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
unsigned long GetForeColor()
{
	unsigned long result;
	GetProperty(DISPID_FORECOLOR, VT_UI4, (void*)&result);
	return result;
}
void SetForeColor(unsigned long propVal)
{
	SetProperty(DISPID_FORECOLOR, VT_UI4, propVal);
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
unsigned long GetBorderColor()
{
	unsigned long result;
	GetProperty(0x1, VT_UI4, (void*)&result);
	return result;
}
void SetBorderColor(unsigned long propVal)
{
	SetProperty(0x1, VT_UI4, propVal);
}
long GetBorderType()
{
	long result;
	GetProperty(0x2, VT_I4, (void*)&result);
	return result;
}
void SetBorderType(long propVal)
{
	SetProperty(0x2, VT_I4, propVal);
}
BOOL GetShowTitle()
{
	BOOL result;
	GetProperty(0x3, VT_BOOL, (void*)&result);
	return result;
}
void SetShowTitle(BOOL propVal)
{
	SetProperty(0x3, VT_BOOL, propVal);
}
unsigned long GetTitleBackColor()
{
	unsigned long result;
	GetProperty(0x4, VT_UI4, (void*)&result);
	return result;
}
void SetTitleBackColor(unsigned long propVal)
{
	SetProperty(0x4, VT_UI4, propVal);
}
unsigned long GetTitleForeColor()
{
	unsigned long result;
	GetProperty(0x5, VT_UI4, (void*)&result);
	return result;
}
void SetTitleForeColor(unsigned long propVal)
{
	SetProperty(0x5, VT_UI4, propVal);
}
COleFont GetTitleFont()
{
	LPDISPATCH result;
	GetProperty(0x6, VT_DISPATCH, (void*)&result);
	return COleFont(result);
}
void SetTitleFont(LPDISPATCH propVal)
{
	SetProperty(0x6, VT_DISPATCH, propVal);
}
CString GetTitleText()
{
	CString result;
	GetProperty(0x7, VT_BSTR, (void*)&result);
	return result;
}
void SetTitleText(CString propVal)
{
	SetProperty(0x7, VT_BSTR, propVal);
}
CPicture GetTitleBackImage()
{
	LPDISPATCH result;
	GetProperty(0x8, VT_DISPATCH, (void*)&result);
	return CPicture(result);
}
void SetTitleBackImage(LPDISPATCH propVal)
{
	SetProperty(0x8, VT_DISPATCH, propVal);
}
BOOL GetShowHeader()
{
	BOOL result;
	GetProperty(0x9, VT_BOOL, (void*)&result);
	return result;
}
void SetShowHeader(BOOL propVal)
{
	SetProperty(0x9, VT_BOOL, propVal);
}
COleFont GetHeaderFont()
{
	LPDISPATCH result;
	GetProperty(0xa, VT_DISPATCH, (void*)&result);
	return COleFont(result);
}
void SetHeaderFont(LPDISPATCH propVal)
{
	SetProperty(0xa, VT_DISPATCH, propVal);
}
unsigned long GetShadowColor()
{
	unsigned long result;
	GetProperty(0xb, VT_UI4, (void*)&result);
	return result;
}
void SetShadowColor(unsigned long propVal)
{
	SetProperty(0xb, VT_UI4, propVal);
}
long GetHeaderAlign()
{
	long result;
	GetProperty(0xc, VT_I4, (void*)&result);
	return result;
}
void SetHeaderAlign(long propVal)
{
	SetProperty(0xc, VT_I4, propVal);
}
unsigned long GetHeaderBackColor()
{
	unsigned long result;
	GetProperty(0xd, VT_UI4, (void*)&result);
	return result;
}
void SetHeaderBackColor(unsigned long propVal)
{
	SetProperty(0xd, VT_UI4, propVal);
}
unsigned long GetHeaderForeColor()
{
	unsigned long result;
	GetProperty(0xe, VT_UI4, (void*)&result);
	return result;
}
void SetHeaderForeColor(unsigned long propVal)
{
	SetProperty(0xe, VT_UI4, propVal);
}
long GetHeaderBorder()
{
	long result;
	GetProperty(0xf, VT_I4, (void*)&result);
	return result;
}
void SetHeaderBorder(long propVal)
{
	SetProperty(0xf, VT_I4, propVal);
}
short GetHeaderOffset()
{
	short result;
	GetProperty(0x10, VT_I2, (void*)&result);
	return result;
}
void SetHeaderOffset(short propVal)
{
	SetProperty(0x10, VT_I2, propVal);
}
short GetTitleOffset()
{
	short result;
	GetProperty(0x11, VT_I2, (void*)&result);
	return result;
}
void SetTitleOffset(short propVal)
{
	SetProperty(0x11, VT_I2, propVal);
}
short GetHeaderXOffset()
{
	short result;
	GetProperty(0x12, VT_I2, (void*)&result);
	return result;
}
void SetHeaderXOffset(short propVal)
{
	SetProperty(0x12, VT_I2, propVal);
}
short GetHeaderYOffset()
{
	short result;
	GetProperty(0x13, VT_I2, (void*)&result);
	return result;
}
void SetHeaderYOffset(short propVal)
{
	SetProperty(0x13, VT_I2, propVal);
}
long GetTitleAlign()
{
	long result;
	GetProperty(0x14, VT_I4, (void*)&result);
	return result;
}
void SetTitleAlign(long propVal)
{
	SetProperty(0x14, VT_I4, propVal);
}
long GetTitleBorder()
{
	long result;
	GetProperty(0x15, VT_I4, (void*)&result);
	return result;
}
void SetTitleBorder(long propVal)
{
	SetProperty(0x15, VT_I4, propVal);
}
short GetTitleXOffset()
{
	short result;
	GetProperty(0x16, VT_I2, (void*)&result);
	return result;
}
void SetTitleXOffset(short propVal)
{
	SetProperty(0x16, VT_I2, propVal);
}
short GetTitleYOffset()
{
	short result;
	GetProperty(0x17, VT_I2, (void*)&result);
	return result;
}
void SetTitleYOffset(short propVal)
{
	SetProperty(0x17, VT_I2, propVal);
}
unsigned long GetAltColorOdd()
{
	unsigned long result;
	GetProperty(0x18, VT_UI4, (void*)&result);
	return result;
}
void SetAltColorOdd(unsigned long propVal)
{
	SetProperty(0x18, VT_UI4, propVal);
}
unsigned long GetAltColorEven()
{
	unsigned long result;
	GetProperty(0x19, VT_UI4, (void*)&result);
	return result;
}
void SetAltColorEven(unsigned long propVal)
{
	SetProperty(0x19, VT_UI4, propVal);
}
BOOL GetAlternateColor()
{
	BOOL result;
	GetProperty(0x1a, VT_BOOL, (void*)&result);
	return result;
}
void SetAlternateColor(BOOL propVal)
{
	SetProperty(0x1a, VT_BOOL, propVal);
}
BOOL GetMaskBitmap()
{
	BOOL result;
	GetProperty(0x1b, VT_BOOL, (void*)&result);
	return result;
}
void SetMaskBitmap(BOOL propVal)
{
	SetProperty(0x1b, VT_BOOL, propVal);
}
unsigned long GetMaskColor()
{
	unsigned long result;
	GetProperty(0x1c, VT_UI4, (void*)&result);
	return result;
}
void SetMaskColor(unsigned long propVal)
{
	SetProperty(0x1c, VT_UI4, propVal);
}
short GetHeightOffset()
{
	short result;
	GetProperty(0x1d, VT_I2, (void*)&result);
	return result;
}
void SetHeightOffset(short propVal)
{
	SetProperty(0x1d, VT_I2, propVal);
}
BOOL GetHorzScroll()
{
	BOOL result;
	GetProperty(0x1e, VT_BOOL, (void*)&result);
	return result;
}
void SetHorzScroll(BOOL propVal)
{
	SetProperty(0x1e, VT_BOOL, propVal);
}
unsigned long GetSelectedBackColor()
{
	unsigned long result;
	GetProperty(0x1f, VT_UI4, (void*)&result);
	return result;
}
void SetSelectedBackColor(unsigned long propVal)
{
	SetProperty(0x1f, VT_UI4, propVal);
}
unsigned long GetSelectedForeColor()
{
	unsigned long result;
	GetProperty(0x20, VT_UI4, (void*)&result);
	return result;
}
void SetSelectedForeColor(unsigned long propVal)
{
	SetProperty(0x20, VT_UI4, propVal);
}
short GetHorzRange()
{
	short result;
	GetProperty(0x21, VT_I2, (void*)&result);
	return result;
}
void SetHorzRange(short propVal)
{
	SetProperty(0x21, VT_I2, propVal);
}
BOOL GetHorzAutoSize()
{
	BOOL result;
	GetProperty(0x22, VT_BOOL, (void*)&result);
	return result;
}
void SetHorzAutoSize(BOOL propVal)
{
	SetProperty(0x22, VT_BOOL, propVal);
}
long GetPreColumnType()
{
	long result;
	GetProperty(0x23, VT_I4, (void*)&result);
	return result;
}
void SetPreColumnType(long propVal)
{
	SetProperty(0x23, VT_I4, propVal);
}
short GetPreColumnWidth()
{
	short result;
	GetProperty(0x24, VT_I2, (void*)&result);
	return result;
}
void SetPreColumnWidth(short propVal)
{
	SetProperty(0x24, VT_I2, propVal);
}
BOOL GetMultiSelect()
{
	BOOL result;
	GetProperty(0x25, VT_BOOL, (void*)&result);
	return result;
}
void SetMultiSelect(BOOL propVal)
{
	SetProperty(0x25, VT_BOOL, propVal);
}
long GetListAlign()
{
	long result;
	GetProperty(0x26, VT_I4, (void*)&result);
	return result;
}
void SetListAlign(long propVal)
{
	SetProperty(0x26, VT_I4, propVal);
}
long GetSelected()
{
	long result;
	GetProperty(0x27, VT_I4, (void*)&result);
	return result;
}
void SetSelected(long propVal)
{
	SetProperty(0x27, VT_I4, propVal);
}
long GetListIndex()
{
	long result;
	GetProperty(0x28, VT_I4, (void*)&result);
	return result;
}
void SetListIndex(long propVal)
{
	SetProperty(0x28, VT_I4, propVal);
}
BOOL GetHorzGridLines()
{
	BOOL result;
	GetProperty(0x29, VT_BOOL, (void*)&result);
	return result;
}
void SetHorzGridLines(BOOL propVal)
{
	SetProperty(0x29, VT_BOOL, propVal);
}
unsigned long GetHorzGridColor()
{
	unsigned long result;
	GetProperty(0x2a, VT_UI4, (void*)&result);
	return result;
}
void SetHorzGridColor(unsigned long propVal)
{
	SetProperty(0x2a, VT_UI4, propVal);
}
BOOL GetVertGridLines()
{
	BOOL result;
	GetProperty(0x2b, VT_BOOL, (void*)&result);
	return result;
}
void SetVertGridLines(BOOL propVal)
{
	SetProperty(0x2b, VT_BOOL, propVal);
}
unsigned long GetVertGridColor()
{
	unsigned long result;
	GetProperty(0x2c, VT_UI4, (void*)&result);
	return result;
}
void SetVertGridColor(unsigned long propVal)
{
	SetProperty(0x2c, VT_UI4, propVal);
}
long GetTitleTextStyle()
{
	long result;
	GetProperty(0x2d, VT_I4, (void*)&result);
	return result;
}
void SetTitleTextStyle(long propVal)
{
	SetProperty(0x2d, VT_I4, propVal);
}
long GetFocusType()
{
	long result;
	GetProperty(0x2e, VT_I4, (void*)&result);
	return result;
}
void SetFocusType(long propVal)
{
	SetProperty(0x2e, VT_I4, propVal);
}
unsigned long GetSubTextColor()
{
	unsigned long result;
	GetProperty(0x2f, VT_UI4, (void*)&result);
	return result;
}
void SetSubTextColor(unsigned long propVal)
{
	SetProperty(0x2f, VT_UI4, propVal);
}
COleFont GetSubTextFont()
{
	LPDISPATCH result;
	GetProperty(0x30, VT_DISPATCH, (void*)&result);
	return COleFont(result);
}
void SetSubTextFont(LPDISPATCH propVal)
{
	SetProperty(0x30, VT_DISPATCH, propVal);
}
short GetSubTextIndent()
{
	short result;
	GetProperty(0x31, VT_I2, (void*)&result);
	return result;
}
void SetSubTextIndent(short propVal)
{
	SetProperty(0x31, VT_I2, propVal);
}
BOOL GetScrollOnVThumb()
{
	BOOL result;
	GetProperty(0x32, VT_BOOL, (void*)&result);
	return result;
}
void SetScrollOnVThumb(BOOL propVal)
{
	SetProperty(0x32, VT_BOOL, propVal);
}
BOOL GetScrollOnHThumb()
{
	BOOL result;
	GetProperty(0x33, VT_BOOL, (void*)&result);
	return result;
}
void SetScrollOnHThumb(BOOL propVal)
{
	SetProperty(0x33, VT_BOOL, propVal);
}
unsigned long GetTipsBackColor()
{
	unsigned long result;
	GetProperty(0x34, VT_UI4, (void*)&result);
	return result;
}
void SetTipsBackColor(unsigned long propVal)
{
	SetProperty(0x34, VT_UI4, propVal);
}
unsigned long GetTipsForeColor()
{
	unsigned long result;
	GetProperty(0x35, VT_UI4, (void*)&result);
	return result;
}
void SetTipsForeColor(unsigned long propVal)
{
	SetProperty(0x35, VT_UI4, propVal);
}
short GetTipsDistance()
{
	short result;
	GetProperty(0x36, VT_I2, (void*)&result);
	return result;
}
void SetTipsDistance(short propVal)
{
	SetProperty(0x36, VT_I2, propVal);
}
long GetTipsPosition()
{
	long result;
	GetProperty(0x37, VT_I4, (void*)&result);
	return result;
}
void SetTipsPosition(long propVal)
{
	SetProperty(0x37, VT_I4, propVal);
}
CString GetTipsText()
{
	CString result;
	GetProperty(0x38, VT_BSTR, (void*)&result);
	return result;
}
void SetTipsText(CString propVal)
{
	SetProperty(0x38, VT_BSTR, propVal);
}
COleFont GetTipsFont()
{
	LPDISPATCH result;
	GetProperty(0x39, VT_DISPATCH, (void*)&result);
	return COleFont(result);
}
void SetTipsFont(LPDISPATCH propVal)
{
	SetProperty(0x39, VT_DISPATCH, propVal);
}
long GetPicAlign()
{
	long result;
	GetProperty(0x3a, VT_I4, (void*)&result);
	return result;
}
void SetPicAlign(long propVal)
{
	SetProperty(0x3a, VT_I4, propVal);
}
short GetPicXOffset()
{
	short result;
	GetProperty(0x3b, VT_I2, (void*)&result);
	return result;
}
void SetPicXOffset(short propVal)
{
	SetProperty(0x3b, VT_I2, propVal);
}
short GetPicYOffset()
{
	short result;
	GetProperty(0x3c, VT_I2, (void*)&result);
	return result;
}
void SetPicYOffset(short propVal)
{
	SetProperty(0x3c, VT_I2, propVal);
}
long GetCheckAlign()
{
	long result;
	GetProperty(0x3d, VT_I4, (void*)&result);
	return result;
}
void SetCheckAlign(long propVal)
{
	SetProperty(0x3d, VT_I4, propVal);
}
short GetCheckXOffset()
{
	short result;
	GetProperty(0x3e, VT_I2, (void*)&result);
	return result;
}
void SetCheckXOffset(short propVal)
{
	SetProperty(0x3e, VT_I2, propVal);
}
short GetCheckYOffset()
{
	short result;
	GetProperty(0x3f, VT_I2, (void*)&result);
	return result;
}
void SetCheckYOffset(short propVal)
{
	SetProperty(0x3f, VT_I2, propVal);
}
BOOL GetMultiLine()
{
	BOOL result;
	GetProperty(0x40, VT_BOOL, (void*)&result);
	return result;
}
void SetMultiLine(BOOL propVal)
{
	SetProperty(0x40, VT_BOOL, propVal);
}
BOOL GetSelectOnScroll()
{
	BOOL result;
	GetProperty(0x41, VT_BOOL, (void*)&result);
	return result;
}
void SetSelectOnScroll(BOOL propVal)
{
	SetProperty(0x41, VT_BOOL, propVal);
}
short GetSortColumn()
{
	short result;
	GetProperty(0x42, VT_I2, (void*)&result);
	return result;
}
void SetSortColumn(short propVal)
{
	SetProperty(0x42, VT_I2, propVal);
}
long GetSortDirection()
{
	long result;
	GetProperty(0x43, VT_I4, (void*)&result);
	return result;
}
void SetSortDirection(long propVal)
{
	SetProperty(0x43, VT_I4, propVal);
}
BOOL GetSortOnCase()
{
	BOOL result;
	GetProperty(0x44, VT_BOOL, (void*)&result);
	return result;
}
void SetSortOnCase(BOOL propVal)
{
	SetProperty(0x44, VT_BOOL, propVal);
}
BOOL GetSortArrows()
{
	BOOL result;
	GetProperty(0x45, VT_BOOL, (void*)&result);
	return result;
}
void SetSortArrows(BOOL propVal)
{
	SetProperty(0x45, VT_BOOL, propVal);
}
CPicture GetCheckPicDown()
{
	LPDISPATCH result;
	GetProperty(0x46, VT_DISPATCH, (void*)&result);
	return CPicture(result);
}
void SetCheckPicDown(LPDISPATCH propVal)
{
	SetProperty(0x46, VT_DISPATCH, propVal);
}
CPicture GetCheckPicUp()
{
	LPDISPATCH result;
	GetProperty(0x47, VT_DISPATCH, (void*)&result);
	return CPicture(result);
}
void SetCheckPicUp(LPDISPATCH propVal)
{
	SetProperty(0x47, VT_DISPATCH, propVal);
}
CString GetBreakChar()
{
	CString result;
	GetProperty(0x48, VT_BSTR, (void*)&result);
	return result;
}
void SetBreakChar(CString propVal)
{
	SetProperty(0x48, VT_BSTR, propVal);
}
short GetSubColumnStart()
{
	short result;
	GetProperty(0x49, VT_I2, (void*)&result);
	return result;
}
void SetSubColumnStart(short propVal)
{
	SetProperty(0x49, VT_I2, propVal);
}
short GetSubColumnEnd()
{
	short result;
	GetProperty(0x4a, VT_I2, (void*)&result);
	return result;
}
void SetSubColumnEnd(short propVal)
{
	SetProperty(0x4a, VT_I2, propVal);
}
BOOL GetSmoothScroll()
{
	BOOL result;
	GetProperty(0x4b, VT_BOOL, (void*)&result);
	return result;
}
void SetSmoothScroll(BOOL propVal)
{
	SetProperty(0x4b, VT_BOOL, propVal);
}
short GetScrollSpeed()
{
	short result;
	GetProperty(0x4c, VT_I2, (void*)&result);
	return result;
}
void SetScrollSpeed(short propVal)
{
	SetProperty(0x4c, VT_I2, propVal);
}
short GetImageListCount()
{
	short result;
	GetProperty(0x4d, VT_I2, (void*)&result);
	return result;
}
void SetImageListCount(short propVal)
{
	SetProperty(0x4d, VT_I2, propVal);
}
BOOL GetSmallIcons()
{
	BOOL result;
	GetProperty(0x4e, VT_BOOL, (void*)&result);
	return result;
}
void SetSmallIcons(BOOL propVal)
{
	SetProperty(0x4e, VT_BOOL, propVal);
}
CPicture GetBackImage()
{
	LPDISPATCH result;
	GetProperty(0x4f, VT_DISPATCH, (void*)&result);
	return CPicture(result);
}
void SetBackImage(LPDISPATCH propVal)
{
	SetProperty(0x4f, VT_DISPATCH, propVal);
}
unsigned long GetNoFocusBackColor()
{
	unsigned long result;
	GetProperty(0x50, VT_UI4, (void*)&result);
	return result;
}
void SetNoFocusBackColor(unsigned long propVal)
{
	SetProperty(0x50, VT_UI4, propVal);
}
unsigned long GetNoFocusForeColor()
{
	unsigned long result;
	GetProperty(0x51, VT_UI4, (void*)&result);
	return result;
}
void SetNoFocusForeColor(unsigned long propVal)
{
	SetProperty(0x51, VT_UI4, propVal);
}
BOOL GetLabelEdit()
{
	BOOL result;
	GetProperty(0x52, VT_BOOL, (void*)&result);
	return result;
}
void SetLabelEdit(BOOL propVal)
{
	SetProperty(0x52, VT_BOOL, propVal);
}
long GetSelectedStyle()
{
	long result;
	GetProperty(0x53, VT_I4, (void*)&result);
	return result;
}
void SetSelectedStyle(long propVal)
{
	SetProperty(0x53, VT_I4, propVal);
}
long GetArrowAlign()
{
	long result;
	GetProperty(0x54, VT_I4, (void*)&result);
	return result;
}
void SetArrowAlign(long propVal)
{
	SetProperty(0x54, VT_I4, propVal);
}
short GetArrowXOffset()
{
	short result;
	GetProperty(0x55, VT_I2, (void*)&result);
	return result;
}
void SetArrowXOffset(short propVal)
{
	SetProperty(0x55, VT_I2, propVal);
}
short GetArrowYOffset()
{
	short result;
	GetProperty(0x56, VT_I2, (void*)&result);
	return result;
}
void SetArrowYOffset(short propVal)
{
	SetProperty(0x56, VT_I2, propVal);
}
CPicture GetCheckPicDisabled()
{
	LPDISPATCH result;
	GetProperty(0x57, VT_DISPATCH, (void*)&result);
	return CPicture(result);
}
void SetCheckPicDisabled(LPDISPATCH propVal)
{
	SetProperty(0x57, VT_DISPATCH, propVal);
}
COleFont GetPrintTitleFont()
{
	LPDISPATCH result;
	GetProperty(0x58, VT_DISPATCH, (void*)&result);
	return COleFont(result);
}
void SetPrintTitleFont(LPDISPATCH propVal)
{
	SetProperty(0x58, VT_DISPATCH, propVal);
}
CString GetPrintTitle()
{
	CString result;
	GetProperty(0x59, VT_BSTR, (void*)&result);
	return result;
}
void SetPrintTitle(CString propVal)
{
	SetProperty(0x59, VT_BSTR, propVal);
}
CString GetPrintSubTitle()
{
	CString result;
	GetProperty(0x5a, VT_BSTR, (void*)&result);
	return result;
}
void SetPrintSubTitle(CString propVal)
{
	SetProperty(0x5a, VT_BSTR, propVal);
}
short GetPageXOffset()
{
	short result;
	GetProperty(0x5b, VT_I2, (void*)&result);
	return result;
}
void SetPageXOffset(short propVal)
{
	SetProperty(0x5b, VT_I2, propVal);
}
short GetPageYOffset()
{
	short result;
	GetProperty(0x5c, VT_I2, (void*)&result);
	return result;
}
void SetPageYOffset(short propVal)
{
	SetProperty(0x5c, VT_I2, propVal);
}
short GetPrintOffset()
{
	short result;
	GetProperty(0x5d, VT_I2, (void*)&result);
	return result;
}
void SetPrintOffset(short propVal)
{
	SetProperty(0x5d, VT_I2, propVal);
}
long GetPrintTitleAlign()
{
	long result;
	GetProperty(0x5e, VT_I4, (void*)&result);
	return result;
}
void SetPrintTitleAlign(long propVal)
{
	SetProperty(0x5e, VT_I4, propVal);
}
unsigned long GetPrintBackColor()
{
	unsigned long result;
	GetProperty(0x5f, VT_UI4, (void*)&result);
	return result;
}
void SetPrintBackColor(unsigned long propVal)
{
	SetProperty(0x5f, VT_UI4, propVal);
}
long GetControlPointer()
{
	long result;
	GetProperty(0x60, VT_I4, (void*)&result);
	return result;
}
void SetControlPointer(long propVal)
{
	SetProperty(0x60, VT_I4, propVal);
}
short GetAlternateItems()
{
	short result;
	GetProperty(0x61, VT_I2, (void*)&result);
	return result;
}
void SetAlternateItems(short propVal)
{
	SetProperty(0x61, VT_I2, propVal);
}
CPicture GetMouseIcon()
{
	LPDISPATCH result;
	GetProperty(0x62, VT_DISPATCH, (void*)&result);
	return CPicture(result);
}
void SetMouseIcon(LPDISPATCH propVal)
{
	SetProperty(0x62, VT_DISPATCH, propVal);
}
long GetMousePointer()
{
	long result;
	GetProperty(0x63, VT_I4, (void*)&result);
	return result;
}
void SetMousePointer(long propVal)
{
	SetProperty(0x63, VT_I4, propVal);
}
short GetMouseIndex()
{
	short result;
	GetProperty(0x64, VT_I2, (void*)&result);
	return result;
}
void SetMouseIndex(short propVal)
{
	SetProperty(0x64, VT_I2, propVal);
}
long GetPreColumnBorder()
{
	long result;
	GetProperty(0x65, VT_I4, (void*)&result);
	return result;
}
void SetPreColumnBorder(long propVal)
{
	SetProperty(0x65, VT_I4, propVal);
}
unsigned long GetPreColumnBackColor()
{
	unsigned long result;
	GetProperty(0x66, VT_UI4, (void*)&result);
	return result;
}
void SetPreColumnBackColor(unsigned long propVal)
{
	SetProperty(0x66, VT_UI4, propVal);
}
unsigned long GetPreColumnForeColor()
{
	unsigned long result;
	GetProperty(0x67, VT_UI4, (void*)&result);
	return result;
}
void SetPreColumnForeColor(unsigned long propVal)
{
	SetProperty(0x67, VT_UI4, propVal);
}
CPicture GetPreColumnPicture()
{
	LPDISPATCH result;
	GetProperty(0x68, VT_DISPATCH, (void*)&result);
	return CPicture(result);
}
void SetPreColumnPicture(LPDISPATCH propVal)
{
	SetProperty(0x68, VT_DISPATCH, propVal);
}
long GetPreSelectBorder()
{
	long result;
	GetProperty(0x69, VT_I4, (void*)&result);
	return result;
}
void SetPreSelectBorder(long propVal)
{
	SetProperty(0x69, VT_I4, propVal);
}
unsigned long GetPreSelectBackColor()
{
	unsigned long result;
	GetProperty(0x6a, VT_UI4, (void*)&result);
	return result;
}
void SetPreSelectBackColor(unsigned long propVal)
{
	SetProperty(0x6a, VT_UI4, propVal);
}
unsigned long GetPreSelectForeColor()
{
	unsigned long result;
	GetProperty(0x6b, VT_UI4, (void*)&result);
	return result;
}
void SetPreSelectForeColor(unsigned long propVal)
{
	SetProperty(0x6b, VT_UI4, propVal);
}
BOOL GetHeaderMultiLine()
{
	BOOL result;
	GetProperty(0x6c, VT_BOOL, (void*)&result);
	return result;
}
void SetHeaderMultiLine(BOOL propVal)
{
	SetProperty(0x6c, VT_BOOL, propVal);
}
long GetPrintMapMode()
{
	long result;
	GetProperty(0x6d, VT_I4, (void*)&result);
	return result;
}
void SetPrintMapMode(long propVal)
{
	SetProperty(0x6d, VT_I4, propVal);
}
long GetTipsType()
{
	long result;
	GetProperty(0x6e, VT_I4, (void*)&result);
	return result;
}
void SetTipsType(long propVal)
{
	SetProperty(0x6e, VT_I4, propVal);
}
BOOL GetColumnPriority()
{
	BOOL result;
	GetProperty(0x6f, VT_BOOL, (void*)&result);
	return result;
}
void SetColumnPriority(BOOL propVal)
{
	SetProperty(0x6f, VT_BOOL, propVal);
}
BOOL GetDisplayTitle()
{
	BOOL result;
	GetProperty(0x70, VT_BOOL, (void*)&result);
	return result;
}
void SetDisplayTitle(BOOL propVal)
{
	SetProperty(0x70, VT_BOOL, propVal);
}
BOOL GetDisplayHeader()
{
	BOOL result;
	GetProperty(0x71, VT_BOOL, (void*)&result);
	return result;
}
void SetDisplayHeader(BOOL propVal)
{
	SetProperty(0x71, VT_BOOL, propVal);
}
short GetTipsDelay()
{
	short result;
	GetProperty(0x72, VT_I2, (void*)&result);
	return result;
}
void SetTipsDelay(short propVal)
{
	SetProperty(0x72, VT_I2, propVal);
}
long GetTipsTextAlign()
{
	long result;
	GetProperty(0x73, VT_I4, (void*)&result);
	return result;
}
void SetTipsTextAlign(long propVal)
{
	SetProperty(0x73, VT_I4, propVal);
}
short GetDateOffset()
{
	short result;
	GetProperty(0x74, VT_I2, (void*)&result);
	return result;
}
void SetDateOffset(short propVal)
{
	SetProperty(0x74, VT_I2, propVal);
}
long GetDateFormat()
{
	long result;
	GetProperty(0x75, VT_I4, (void*)&result);
	return result;
}
void SetDateFormat(long propVal)
{
	SetProperty(0x75, VT_I4, propVal);
}
BOOL GetIncludeSeconds()
{
	BOOL result;
	GetProperty(0x76, VT_BOOL, (void*)&result);
	return result;
}
void SetIncludeSeconds(BOOL propVal)
{
	SetProperty(0x76, VT_BOOL, propVal);
}
BOOL GetIncludeAmPm()
{
	BOOL result;
	GetProperty(0x77, VT_BOOL, (void*)&result);
	return result;
}
void SetIncludeAmPm(BOOL propVal)
{
	SetProperty(0x77, VT_BOOL, propVal);
}
BOOL GetIncludeTime()
{
	BOOL result;
	GetProperty(0x78, VT_BOOL, (void*)&result);
	return result;
}
void SetIncludeTime(BOOL propVal)
{
	SetProperty(0x78, VT_BOOL, propVal);
}
CString GetDateSepChar()
{
	CString result;
	GetProperty(0x79, VT_BSTR, (void*)&result);
	return result;
}
void SetDateSepChar(CString propVal)
{
	SetProperty(0x79, VT_BSTR, propVal);
}
CString GetTimeSepChar()
{
	CString result;
	GetProperty(0x7a, VT_BSTR, (void*)&result);
	return result;
}
void SetTimeSepChar(CString propVal)
{
	SetProperty(0x7a, VT_BSTR, propVal);
}
BOOL GetLongYear()
{
	BOOL result;
	GetProperty(0x7b, VT_BOOL, (void*)&result);
	return result;
}
void SetLongYear(BOOL propVal)
{
	SetProperty(0x7b, VT_BOOL, propVal);
}
long GetHeaderPicAlign()
{
	long result;
	GetProperty(0x7c, VT_I4, (void*)&result);
	return result;
}
void SetHeaderPicAlign(long propVal)
{
	SetProperty(0x7c, VT_I4, propVal);
}
CString GetDecimalChar()
{
	CString result;
	GetProperty(0x7d, VT_BSTR, (void*)&result);
	return result;
}
void SetDecimalChar(CString propVal)
{
	SetProperty(0x7d, VT_BSTR, propVal);
}
BOOL GetSorted()
{
	BOOL result;
	GetProperty(0x7e, VT_BOOL, (void*)&result);
	return result;
}
void SetSorted(BOOL propVal)
{
	SetProperty(0x7e, VT_BOOL, propVal);
}
long GetTopRow()
{
	long result;
	GetProperty(0x7f, VT_I4, (void*)&result);
	return result;
}
void SetTopRow(long propVal)
{
	SetProperty(0x7f, VT_I4, propVal);
}


};
