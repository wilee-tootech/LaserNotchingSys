// DeviceArea.h: interface for the CDeviceArea class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVICEAREA_H__3EAF0638_7F42_49F0_9708_F4D34F759890__INCLUDED_)
#define AFX_DEVICEAREA_H__3EAF0638_7F42_49F0_9708_F4D34F759890__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDeviceArea  
{
public:
	CDeviceArea();
	virtual ~CDeviceArea();
	static CRect GetDeviceArea();
};

#endif // !defined(AFX_DEVICEAREA_H__3EAF0638_7F42_49F0_9708_F4D34F759890__INCLUDED_)
