#include "stdafx.h"
#include "ADJModule.h"


CDoubleBuffer::CDoubleBuffer():m_pfAOIDataBuffer(NULL),m_pfAOITimeDataBuffer(NULL),m_fDataBufferSize(0)
{

}
CDoubleBuffer::CDoubleBuffer(size_t nSize):m_pfAOIDataBuffer(NULL),m_pfAOITimeDataBuffer(NULL),m_fDataBufferSize(0)
{
	AllocDataBuffer(nSize);
}
CDoubleBuffer::~CDoubleBuffer()
{
	FreefDataBuffer();
}
bool CDoubleBuffer::AllocDataBuffer(size_t nSize)
{
	if(m_pfAOIDataBuffer==NULL)
	{
		m_pfAOIDataBuffer=new double [nSize];
		m_pfAOITimeDataBuffer=new double [nSize];
		m_fDataBufferSize=nSize;
		memset(m_pfAOIDataBuffer,0,sizeof(double)*m_fDataBufferSize);
		memset(m_pfAOITimeDataBuffer,0,sizeof(double)*m_fDataBufferSize);
		return true;
	}
	else
	{
		if(nSize!=m_fDataBufferSize)
		{
			FreefDataBuffer();
			m_pfAOIDataBuffer=new double [nSize];
			m_pfAOITimeDataBuffer=new double [nSize];
			m_fDataBufferSize=nSize;
			memset(m_pfAOIDataBuffer,0,sizeof(double)*m_fDataBufferSize);
			memset(m_pfAOITimeDataBuffer,0,sizeof(double)*m_fDataBufferSize);
			return true;
		}
	}
	return false;
}
void CDoubleBuffer::FreefDataBuffer()
{
	if(m_pfAOIDataBuffer!=NULL)
	{
		delete [] m_pfAOIDataBuffer;
		m_pfAOIDataBuffer=NULL;
	}
	if(m_pfAOITimeDataBuffer!=NULL)
	{
		delete [] m_pfAOITimeDataBuffer;
		m_pfAOITimeDataBuffer=NULL;
	}
	m_fDataBufferSize=0;
}
size_t CDoubleBuffer::GetDataBufferSize()
{
	return m_fDataBufferSize;
}

bool CDoubleBuffer::SetData(size_t nIndex,double fData,double fTime)
{
	if(m_pfAOIDataBuffer!=NULL &&  m_pfAOITimeDataBuffer!=NULL    && nIndex < m_fDataBufferSize)
	{
		m_pfAOIDataBuffer[nIndex]=fData;
		m_pfAOITimeDataBuffer[nIndex]=fTime;
		return true;
	}
	return false;
}
double * CDoubleBuffer::GetDataBufferPointor()
{
	if(m_pfAOIDataBuffer!=NULL )
	{
		return m_pfAOIDataBuffer;
	}
	return NULL;
}
double * CDoubleBuffer::GetTimeBufferPointor()
{
	return m_pfAOITimeDataBuffer;
}
CADJModule::~CADJModule(void)
{
	StopOutput();
	delete m_pTimerThread;
	m_pTimerThread=NULL;

	delete m_pAOValueSetFunc;
	m_pAOValueSetFunc=NULL;
	delete m_pAOVoltRangeFunc;
	m_pAOVoltRangeFunc=NULL;
}
void CADJModule::StartOutput()
{
	m_pAOValueSetFunc->Run(0.0);
	m_pTimerThread->Start();
	m_fTmpTime=0.0;
	m_iStartIndex=0;
	m_bLaserSeqRunning = TRUE;
}
void CADJModule::StopOutput()
{
	m_pAOValueSetFunc->Run(0.0);
	m_pTimerThread->Stop();
	m_bLaserSeqRunning = FALSE;
	
}
void CADJModule::Execute()
{
	if(m_fADJBuffer.GetDataBufferSize()>0)
	{
		if(m_iStartIndex>(int)m_fADJBuffer.GetDataBufferSize())
		{
		   StopOutput();
		}
		else
		{
		   if(m_fTmpTime<=0.0)	
		   {
    		    m_pAOValueSetFunc->Run(m_fADJBuffer.GetDataBufferPointor()[m_iStartIndex]);
	    		m_fTmpTime=TIME_GetQueryTime();
		   }
		   else
		   {
			   if(TIME_GetQueryTime()>m_fTmpTime+m_fADJBuffer.GetTimeBufferPointor()[m_iStartIndex])
			   {
				   m_iStartIndex++;
				   m_fTmpTime=0.0;
			   }
		   }
		}
	}
	else
	{
		StopOutput();
	}
}
bool CADJModule::IsRunning()
{
	return m_pTimerThread->IsRunning();
}

bool CADJModule::AllocADJDataBuffer(size_t nSize)
{
	if(IsRunning()==false)
	{
		return m_fADJBuffer.AllocDataBuffer(nSize);
	}
	return false;
}
bool CADJModule::SetADJData(size_t nIndex,double fVoltage,double fOnTime)
{
	if(IsRunning()==false)
	{
	  return m_fADJBuffer.SetData(nIndex,fVoltage,fOnTime);
	}
	return false;
}

size_t  CADJModule::GetADJDataBufferSize()
{
	return m_fADJBuffer.GetDataBufferSize();
}


double * CADJModule::GetDataBufferPointor()
{
	return m_fADJBuffer.GetDataBufferPointor();
}

double * CADJModule::GetTimeBufferPointor()
{
	return m_fADJBuffer.GetTimeBufferPointor();
}

BOOL   CADJModule::GetLaserSeqRunning()
{
	return m_bLaserSeqRunning;
}
