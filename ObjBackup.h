// ObjBackup.h: interface for the CObjBackup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJBACKUP_H__6673ED39_4438_4E85_BEF5_9D5999F53A28__INCLUDED_)
#define AFX_OBJBACKUP_H__6673ED39_4438_4E85_BEF5_9D5999F53A28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MkDoc.h"


class CObjBackup  
{

	

private:
	float X;
	float Y;
	float Xmag;
	float Ymag;
	float Width;
	float Height;
	float OriginalX;
	float OriginalY;
	float OriginalXmag;
	float OriginalYmag;
	float OriginalWidth;
	float OriginalHeight;

	CObjBackup *next;
	defobj *_obj;

public:
	CObjBackup *GetNext(void)
	{
		return next;
	}
	void SetNext(CObjBackup *ObjBackup)
	{
		next = ObjBackup;
	}
	void BackupAllObjData(defobj *obj)
	{
		X = obj->X;
		Y = obj->Y;
		Xmag = obj->Xmag;
		Ymag = obj->Ymag;
		Width = obj->Width;
		Height = obj->Height;
		OriginalX = obj->X;
		OriginalY = obj->Y;
		OriginalXmag = obj->Xmag;
		OriginalYmag = obj->Ymag;
		OriginalWidth = obj->Width;
		OriginalHeight = obj->Height;
		_obj = obj;
		

	}
	void AddAllObjData(CObjBackup *previous, defobj *obj)
	{
		previous->SetNext(this);
		BackupAllObjData(obj);
	}
	void BackupOnlyMovement(defobj *obj)
	{
		X = obj->X;
		Y = obj->Y;
		Xmag = obj->Xmag;
		Ymag = obj->Ymag;
		Width = obj->Width;
		Height = obj->Height;
	}
	void AddOnlyMovement(CObjBackup *previous, defobj *obj)
	{
		previous->SetNext(this);
		BackupOnlyMovement(obj);
	}
	void ResotreOnlyMovement(defobj *obj)
	{
		obj->X = X;
		obj->Y = Y;
		obj->Xmag = Xmag;
		obj->Ymag = Ymag;
		obj->Width = Width;
		obj->Height = Height;
	}
	void RestoreOriginalObjData(void)  // 본래대로 되돌린다.
	{
		_obj->X = OriginalX;
		_obj->Y = OriginalY;
		_obj->Xmag = OriginalXmag;
		_obj->Ymag = OriginalYmag;
		_obj->Width = OriginalWidth;
		_obj->Height = OriginalHeight;
	}

		

		




public:
	CObjBackup();
	virtual ~CObjBackup();

};

#endif // !defined(AFX_OBJBACKUP_H__6673ED39_4438_4E85_BEF5_9D5999F53A28__INCLUDED_)
