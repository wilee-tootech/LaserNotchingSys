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
	void Append(const Item& item, int iIndex); // ��...2003.11.13 �߰�
	void Prepend(const Item&);
	void Remove(const Item&);
	void DeleteAll();
	
	UINT Save(CString strFileName) const;
	UINT Open(CString strFileName) const;

	void UnSerialize(char *pstrSerial);
	char * Serialize(DWORD &dwLength);

	Iterator<Item>* iterator() const; // Iterator Creator
	
	// ������ instance ��ȯ
//	static CItemList *GetInstance();

private:
	int last;// �ϳ��� �߰��ϸ鼭 ���� index �����ϰ� �ִ� ��
	long m_iCount;
	Item items[DEFAULT_SIZE] ;// ComSetting ���� // ����� �迭 ����
	// 2003.11.05
//	static CItemList *m_pItemList; // ������ instance
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
	// ����Ʈ�� �ڱ��ڽ��� �Ҹ��Ҷ� �����͵���� ������ �ǹ��� ����.  //Memory Leak�������� ����.
	// ������ �ڽŰ� ��ü�� �ƴϴ� �׵��� �׵� ������� ���� ��ư��� ���� ����Ʈ ������.
/*	for (int i = 0; i < last; i++) {
		if (this->items[i] != NULL) {
			delete this->items[i];
			this->items[i] = NULL;
		}
	}*/
}

// �߰��� item�� ������ ��ҷ� �����
template <class Item>
void CItemList<Item>::Append(const Item& item)
{
	// ���� ��Ұ� ������ ����� �ٽ� �����ϱ� �߰�����
	// 2003.11.05 ���� ��� ã��
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
	// ���� ��Ұ� ������ ����� �ٽ� �����ϱ� �߰�����
	// 2003.11.05 ���� ��� ã��
	for (int i =0; i < last; i++) {
		if (this->items[i]->GetIndex() == item->GetIndex()) {
			delete this->items[i]; // �߰�. ���� �������ϰ�� ������ ���� 

			this->items[i] = item;
			return;
		}
	}
	this->items[last] = item;
	last++;
}

// �߰��� item�� ù��° ��ҷ� �����
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

	MKFR.SeekInit(); // Ž�� ��ġ�� �Ǿ����� �ű��. ��ü�� �����ɶ� �⺻���� �Ǿ��̱� �ϴ�.
	while(1)
	{
		pData = MKFR.GetNext(pchSerial,dwGetID,dwGetSize); // �ѵ���Ÿ�� ������Ʈ �ϳ��� ��ġ�� �޾ƿ´�.
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
		if(pData == NULL) // ��å���� ������ ����
		{
			OutputDebugString("CItemList<Item>::Serialize - Error Occured when doing serialize");
			return NULL;
		}
		MKFW.Add(dwID,dwSize,pData);//������Ʈ�� ������� 0������ 1�� �����ϴ� ID�� ������ ������� ����ȴ�.
		delete pData;
		dwID++;
	}

	return MKFW.GetTotalData(dwLength);
}
