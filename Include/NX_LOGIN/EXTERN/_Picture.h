#pragma once

// �����翡�� Microsoft Visual C++�� ����Ͽ� IDispatch ���� Ŭ������ �����߽��ϴ�.
//
// CPicture ���� Ŭ�����Դϴ�.

class _CPicture : public COleDispatchDriver
{
public:
	_CPicture() {}		// COleDispatchDriver �⺻ �����ڸ� ȣ���մϴ�.
	_CPicture(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_CPicture(const _CPicture& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	long GetHandle()
	{
		long result;
		GetProperty(0x0, VT_I4, (void*)&result);
		return result;
	}

	long GetHPal()
	{
		long result;
		GetProperty(0x2, VT_I4, (void*)&result);
		return result;
	}

	void SetHPal(long propVal)
	{
		SetProperty(0x2, VT_I4, propVal);
	}

	short GetType()
	{
		short result;
		GetProperty(0x3, VT_I2, (void*)&result);
		return result;
	}

	long GetWidth()
	{
		long result;
		GetProperty(0x4, VT_I4, (void*)&result);
		return result;
	}

	long GetHeight()
	{
		long result;
		GetProperty(0x5, VT_I4, (void*)&result);
		return result;
	}
};
