// ObjectSender.h: interface for the CObjectSender class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECTSENDER_H__B055AE6D_F13B_4E61_8AEB_16921FFA6C4D__INCLUDED_)
#define AFX_OBJECTSENDER_H__B055AE6D_F13B_4E61_8AEB_16921FFA6C4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Marking.h"

class CObjectSender  
{
public:
	CObjectSender();
	virtual ~CObjectSender();

//	UINT DataSend(CMarking *pMarking, int iObjNumber, int *pVectorData, int iNumberOfVector, int iParameterIndex, int iBinIndex);
	virtual UINT SendObjectData(CMarking *pMarking, int iObjNumber, double *pVectorData, int iNumberOfVector, int iParameterIndex, int iBinIndex)=0;
	virtual UINT SendObjectData2(CMarking *pMarking, int iObjNumber, double *pVectorData, int iNumberOfVector, int iParameterIndex, int iBinIndex)=0;
};

#endif // !defined(AFX_OBJECTSENDER_H__B055AE6D_F13B_4E61_8AEB_16921FFA6C4D__INCLUDED_)
