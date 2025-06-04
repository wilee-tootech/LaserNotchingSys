#ifndef _TIMECOUNTER_H_
#define _TIMECOUNTER_H_

#include <WinBase.h>

enum ENUM_TIME_COUNTER_MODE { ENUM_TIME_COUNTER_MODE_GETTICK, ENUM_TIME_COUNTER_MODE_QUERY};
enum ENUM_TIME_COUNTER_UNIT { ENUM_TIME_COUNTER_UNIT_usec, ENUM_TIME_COUNTER_UNIT_msec, ENUM_TIME_COUNTER_UNIT_sec};
class CTimeCounter
{
public:
	CTimeCounter(void);
	~CTimeCounter(void);
private:
	double m_fStartTime;
	double m_fEndTime;

	BOOL m_bStartTime;
protected:
public:
	CString m_strTime;
public:
	void Init(void);
	void SetTime(ENUM_TIME_COUNTER_MODE a_eMode = ENUM_TIME_COUNTER_MODE_GETTICK);
	double GetDelayTime(ENUM_TIME_COUNTER_MODE a_eMode = ENUM_TIME_COUNTER_MODE_GETTICK, ENUM_TIME_COUNTER_UNIT a_eUnit = ENUM_TIME_COUNTER_UNIT_msec , int a_nDigit = 0);
	CString GetDelayTime(int a_nDigit);
};
#endif

