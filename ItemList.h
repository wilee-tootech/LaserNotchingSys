// ItemList.h: interface for the CItemList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMLIST_H__A6A7820B_E7D4_4CEE_B6C0_6314FB5DF723__INCLUDED_)
#define AFX_COMMLIST_H__A6A7820B_E7D4_4CEE_B6C0_6314FB5DF723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "Iterator.h"
#include "return.h"
#include "MKFileWriter.h"
#include "MKFileReader.h"
#include "define.h"



template <class Item>
class CItemList {
public:
	CItemList(long size = DEFAULT_SIZE);
	CItemList(CItemList *);
	virtual ~CItemList();

	long GetCount() const;
 	Item Get(long index) const;
	void Append(const Item&);
	void Append(const Item& item, int iIndex); // 음...2003.11.13 추가
	void Prepend(const Item&);
	void Remove(const Item&);
	void DeleteAll();
	
	UINT Save(CString strFileName) const;
	UINT Open(CString strFileName) const;

	void UnSerialize(char *pstrSerial);
	char * Serialize(DWORD &dwLength);

	Iterator<Item>* iterator() const; // Iterator Creator
	
	// 유일한 instance 반환
//	static CItemList *GetInstance();

private:
	int last;// 하나씩 추가하면서 최종 index 저장하고 있는 놈
	long m_iCount;
	Item items[DEFAULT_SIZE] ;// ComSetting 저장 // 현재는 배열 형식
	// 2003.11.05
//	static CItemList *m_pItemList; // 유일한 instance
};

#endif // !defined(AFX_COMMLIST_H__A6A7820B_E7D4_4CEE_B6C0_6314FB5DF723__INCLUDED_)

template <class Item>
CItemList<Item>::CItemList(long size)
{
	last = 0;
	m_iCount = size;
}

template <class Item>
CItemList<Item>::CItemList(CItemList *itemList)
{
	this->last = itemList->last;
	for (int i =0; i < last; i++) {
		this->items[i] = itemList->items[i];
	}
	this->m_iCount = itemList->m_iCount;
}

template <class Item>
CItemList<Item>::~CItemList()
{
	// 리스트는 자기자신이 소멸할때 포인터들까지 지워줄 의무는 없다.  //Memory Leak문제땜시 수정.
	// 실제로 자신과 일체가 아니다 그들은 그들 나름대로 삶을 살아가고 나는 리스트 관리만.
/*	for (int i = 0; i < last; i++) {
		if (this->items[i] != NULL) {
			delete this->items[i];
			this->items[i] = NULL;
		}
	}*/
}

// 추가된 item을 마지막 요소로 만들기
template <class Item>
void CItemList<Item>::Append(const Item& item)
{
	// 같은 요소가 있으면 지우고 다시 생성하기 추가하자
	// 2003.11.05 같은 요소 찾기
	for (int i =0; i < last; i++) {
		if (this->items[i]->GetOwner() == item->GetOwner()) {
			this->items[i] = item;
			return;
		}
	}
	this->items[last] = item;
	last++;
}

template <class Item>
void CItemList<Item>::Append(const Item& item, int iIndex)
{
	// 같은 요소가 있으면 지우고 다시 생성하기 추가하자
	// 2003.11.05 같은 요소 찾기
	for (int i =0; i < last; i++) {
		if (this->items[i]->GetIndex() == item->GetIndex()) {
			delete this->items[i]; // 추가. 같은 아이템일경우 기존것 삭제 

			this->items[i] = item;
			return;
		}
	}
	this->items[last] = item;
	last++;
}

// 추가된 item을 첫번째 요소로 만들기
template <class Item>
void CItemList<Item>::Prepend(const Item& item)
{
	for (int i = 0; i < last; i++) {
		this->items[i+1] = this->items[i]; 
	}
	this->items[i] = item;
	last++
}

template <class Item>
void CItemList<Item>::DeleteAll()
{
	for (int i = 0; i < last; i++) {
		if (this->items[i] != NULL) {
			delete this->items[i];
			this->items[i] = NULL;
		}
	}
}

template <class Item>
void CItemList<Item>::Remove(const Item&)
{
}

template <class Item>
Iterator<Item>* CItemList<Item>::iterator() const
{
	return new CConcreteIterator<Item>(this);
}

template <class Item>
long CItemList<Item>::GetCount() const
{
	return last;
}

template <class Item>
Item CItemList<Item>::Get(long index) const
{
	return (this->items[index]);
}

template <class Item>
void CItemList<Item>::UnSerialize(char *pchSerial)
{
	CMKFileReader MKFR;
	char *pData;
	DWORD dwGetID, dwGetSize;

	MKFR.SeekInit(); // 탐색 위치를 맨앞으로 옮긴다. 객체가 생성될때 기본값을 맨앞이긴 하다.
	while(1)
	{
		pData = MKFR.GetNext(pchSerial,dwGetID,dwGetSize); // 총데이타중 오브젝트 하나의 뭉치를 받아온다.
		if( pData == NULL) return;
		this->items[dwGetID]->UnSerialize(pData);
		delete pData;
	}
}

template <class Item>
char *CItemList<Item>::Serialize(DWORD &dwLength)
{
	CMKFileWriter MKFW;

	DWORD dwID = 0;
	char *pData;
	DWORD dwSize;

	for (int i = 0; i < last; i++) {

		pData = this->items[i]->Serialize(dwSize);
		if(pData == NULL) // 대책없이 나가기 ㅋㅋ
		{
			OutputDebugString("CItemList<Item>::Serialize - Error Occured when doing serialize");
			return NULL;
		}
		MKFW.Add(dwID,dwSize,pData);//오브젝트는 순서대로 0번부터 1씩 증가하는 ID를 가지고 순서대로 저장된다.
		delete pData;
		dwID++;
	}

	return MKFW.GetTotalData(dwLength);
}
