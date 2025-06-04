// Vector.cpp: implementation of the CVector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
// #include "FontEditor.h"
#include "Vector.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVector::CVector()
{

}

CVector::~CVector()
{

}

void CVector::LoadVector(BYTE *vector_data)
{
	char PenSwitch;
	short Dx=0, Dy=0;

	memcpy(&PenSwitch,	&vector_data[0] , 1);
	memcpy(&Dx,			&vector_data[1] , 2);
	memcpy(&Dy,			&vector_data[3] , 2);

	SetPenType(PenSwitch);
	SetDxData(Dx);
	SetDyData(Dy);
}

void CVector::SetDxData(short dx)
{
	m_Dx = dx;
}

void CVector::SetDyData(short dy)
{
	m_Dy = dy;
}

void CVector::SetPenType(char type)
{
	m_PenSwitch = type;
}

void CVector::DeleteData()
{
	delete this;
}

/////////////////////////////////////////////////
// 해당 포인터의 데이터를 가져온다
void CVector::LoadVectorToVector(CVector *pVector)
{
	m_Dx = pVector->GetDx();
	m_Dy = pVector->GetDy();
	m_PenSwitch = pVector->GetPenType();
}

short CVector::GetDx()
{
	return m_Dx;
}

short CVector::GetDy()
{
	return m_Dy;
}

char CVector::GetPenType()
{
	return m_PenSwitch;
}

////////////////////////////
// 벡터의 길이를 구한다
DWORD CVector::GetVectorLength()
{
	DWORD length =0 ;

	length = sizeof(m_PenSwitch);
	length += sizeof(m_Dx);
	length += sizeof(m_Dy);

	return length;
}

//////////////////////////////////////////
// 해당 메모리에 벡터를 저장한다
void CVector::SaveVector(BYTE *destination)
{
	memcpy(destination, &m_PenSwitch, 1);
	memcpy(destination+1, &m_Dx, 2);
	memcpy(destination+3, &m_Dy, 2);
}


