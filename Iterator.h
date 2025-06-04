// Iterator.h: interface for the Iterator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITERATOR_H__79EAC125_C593_42DA_BC4C_858F201E91CC__INCLUDED_)
#define AFX_ITERATOR_H__79EAC125_C593_42DA_BC4C_858F201E91CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"

template <class Item>
class Iterator  
{
public:
	virtual ~Iterator();
	virtual void SetFirst() = 0;
	virtual void SetNext() = 0;
	virtual Item GetCurrentItem() const = 0;
	virtual bool HasNext() const = 0;
	virtual void SkipTo(int index) = 0;
	
protected:
	Iterator();
};

#endif // !defined(AFX_ITERATOR_H__79EAC125_C593_42DA_BC4C_858F201E91CC__INCLUDED_)

template <class Item>
Iterator<Item>::Iterator()
{
}

template <class Item>
Iterator<Item>::~Iterator()
{
}