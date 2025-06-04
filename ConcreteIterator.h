// ConcreteIterator.h: interface for the CConcreteIterator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMITERATOR_H__4E0358C6_CF25_4B7B_A51D_448FD5C52792__INCLUDED_)
#define AFX_COMMITERATOR_H__4E0358C6_CF25_4B7B_A51D_448FD5C52792__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "ItemList.h"

template <class Item>
class CConcreteIterator : public Iterator<Item> 
{
public:
	CConcreteIterator(const CItemList<Item>* pItemList);
	virtual ~CConcreteIterator();

	virtual void SetFirst();
	virtual void SetNext();
	virtual Item GetCurrentItem() const;
	virtual bool HasNext() const;
	virtual void SkipTo(int index);

private:
	long m_lCurrent;
	const CItemList<Item>* m_pItemList;
};

#endif // !defined(AFX_COMMITERATOR_H__4E0358C6_CF25_4B7B_A51D_448FD5C52792__INCLUDED_)

template <class Item>
CConcreteIterator<Item>::~CConcreteIterator()
{

}

template <class Item>
CConcreteIterator<Item>::CConcreteIterator( const CItemList<Item>* pItemList)
{
	m_pItemList = pItemList;
	m_lCurrent = 0;
}

template <class Item>
void CConcreteIterator<Item>::SetFirst()
{
	m_lCurrent = 0;
}

template <class Item>
void CConcreteIterator<Item>::SetNext()
{
	m_lCurrent++;
}

template <class Item>
bool CConcreteIterator<Item>::HasNext() const 
{
	if (m_lCurrent < m_pItemList->GetCount()) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

template <class Item>
Item CConcreteIterator<Item>::GetCurrentItem() const 
{
	if (!HasNext()) {
		AfxMessageBox(IDS_NO_ITEM);
	}
	return m_pItemList->Get(m_lCurrent);
}

template <class Item>
void CConcreteIterator<Item>::SkipTo(int index)
{
	m_lCurrent = index;
}
