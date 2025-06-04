///////////////////////////////////////////////////////////////////////////////
// FILE : SocketComm.h
// Header file for CSocketComm class
// CSocketComm
//     Generic class for Socket Communication
///////////////////////////////////////////////////////////////////////////////

#ifndef _SOCKETCOMM_H_
#define _SOCKETCOMM_H_
#include <list>

#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32")

// Event value
#define EVT_CONSUCCESS      0x0000  // Connection established
#define EVT_CONFAILURE      0x0001  // General failure - Wait Connection failed
#define EVT_CONDROP         0x0002  // Connection dropped
#define EVT_ZEROLENGTH      0x0003  // Zero length message

#ifndef BUFFER_SIZE
#define BUFFER_SIZE     MAX_PATH
#endif
#define HOSTNAME_SIZE   MAX_PATH
#define STRING_LENGTH   40

//sun 2016.03.21
//{{
#define FC_DTRSR		0x01
#define FC_RTSCTS		0x02
#define FC_XONXOF		0x04

#define ASCII_BEL		0x07
#define ASCII_BS		0x08
#define ASCII_LF		0x0A
#define ASCII_CR		0x0D
#define ASCII_XON		0x11
#define ASCII_XOFF		0x13

#define ASCII_STX   	0x02
#define ASCII_ACK		0x06
#define ASCII_NAK		0x15
#define ASCII_CHAR_A	0x41
#define ASCII_CHAR_E	0x45

#define ASCII_SOH		0x01
#define ASCII_ENQ		0x05
#define ASCII_ETX		0x03
#define ASCII_SP		0x20
//}}

#define BASIC_SPI_PACKET_SIZE 6     //startByte , ArgumentCount, CommandStartByte, LaserCommand, StopByte, CheckSum
#define SPI_PACKET_START_BYTE 0x1B
#define SPI_PACKET_RESPONSE_NORMALLY 0x09
#define SPI_COMMAND_START_BYTE 0x09
#define SPI_PACKET_STOP_BYTE 0x0D
#define SPI_RECEIVE_PACKET_LASER_COMMAND_POS 4
#define SPI_RECEIVE_PACKET_RESPONSE_VALUE_POS 2


enum SPILaserCommandByte {SetRS232BaudRate = 0x10,  GetRS232BaudRate = 0x11,
					  SetLaserInterfaceControlMode = 0x14, GetLaserInterfaceControlMode = 0x15, 
					  SetLaserControlSignals = 0x1A, GetLaserControlSignals = 0x1B,
					  SetAnalogueCurrentSetPoint = 0x1C, 
					  GetAnalogueSignals = 0x1D,
					  SetPulseWaveform = 0x20, GetPulseWaveform = 0x21,
					  SetPulseRate = 0x22, GetPulseRate = 0x23,
					  SetPulseBurstLength = 0x24, GetPulseBrustLength = 0x25,
					  SetPumpDutyFactor = 0x26, GetPumpDutyFactor = 0x27,
					  SetAllPulseGeneratorParameters = 0x2C, GetAllPulseGeneratorParameters = 0x2D,
					  RestartPulseGenerator = 0x2F,
					  QueryStatusLinesAndAlarms = 0x50,
					  QueryLaserTemperatures = 0x51,
					  QueryLaserCurrents = 0x52,
					  QueryPowerSupplyVoltages = 0x53,
					  QueryHardwareInterface = 0x54,
					  QueryOperatingHours = 0x55,
					  QueryExternalPulseTriggerRepetitionRate = 0x56, //메뉴얼 확인 필요
					  QueryExtendedLaserCurrents = 0x57,
					  SetLaserIntoDiagnosisState = 0x60,
					  GetLaserSerialNumber = 0x62,
					  GetLaserPartNumber = 0x63,
					  GetLaserFirmwareDetails = 0x64,
					  GetLaserDescription = 0x65,
};






struct SockAddrIn : public SOCKADDR_IN {
public:
    SockAddrIn() { Clear(); }
    SockAddrIn(const SockAddrIn& sin) { Copy( sin ); }
    ~SockAddrIn() { }
    SockAddrIn& Copy(const SockAddrIn& sin);
    void    Clear() { memset(this, 0, sizeof(SOCKADDR_IN)); }
    bool    IsEqual(const SockAddrIn& sin) const;
    bool    IsGreater(const SockAddrIn& sin) const;
    bool    IsLower(const SockAddrIn& pm) const;
    bool    IsNull() const { return ((sin_addr.s_addr==0L)&&(sin_port==0)); }
    ULONG   GetIPAddr() const { return sin_addr.s_addr; }
    short   GetPort() const { return sin_port; }
    bool    CreateFrom(LPCTSTR sAddr, LPCTSTR sService, int nFamily = AF_INET);
    SockAddrIn& operator=(const SockAddrIn& sin) { return Copy( sin ); }
    bool    operator==(const SockAddrIn& sin) { return IsEqual( sin ); }
    bool    operator!=(const SockAddrIn& sin) { return !IsEqual( sin ); }
    bool    operator<(const SockAddrIn& sin)  { return IsLower( sin ); }
    bool    operator>(const SockAddrIn& sin)  { return IsGreater( sin ); }
    bool    operator<=(const SockAddrIn& sin) { return !IsGreater( sin ); }
    bool    operator>=(const SockAddrIn& sin) { return !IsLower( sin ); }
    operator LPSOCKADDR() { return (LPSOCKADDR)(this); }
    size_t  Size() const { return sizeof(SOCKADDR_IN); }
    void    SetAddr(SOCKADDR_IN* psin) { memcpy(this, psin, Size()); }
};

typedef std::list<SockAddrIn> CSockAddrList;

struct stMessageProxy
{
  SockAddrIn address;
  BYTE byData[BUFFER_SIZE];
};

class CSocketComm
{
public:
    CSocketComm();
    virtual ~CSocketComm();

    bool IsOpen() const;    // Is Socket valid?
    bool IsStart() const;   // Is Thread started?
    bool IsServer() const;  // Is running in server mode
    bool IsBroadcast() const; // Is UDP Broadcast active
    bool IsSmartAddressing() const; // Is Smart Addressing mode support
    SOCKET GetSocket() const;   // return socket handle
    void SetServerState(bool bServer);  // Run as server mode if true
    void SetSmartAddressing(bool bSmartAddressing); // Set Smart addressing mode
    bool GetSockName(SockAddrIn& saddr_in); // Get Socket name - address
    bool GetPeerName(SockAddrIn& saddr_in); // Get Peer Socket name - address
    bool AddMembership(LPCTSTR strAddress);
    bool DropMembership(LPCTSTR strAddress);
    void AddToList(const SockAddrIn& saddr_in); // Add an address to the list
    void RemoveFromList(const SockAddrIn& saddr_in);    // Remove an address from the list
    void CloseComm();       // Close Socket
    bool __declspec(dllexport) WatchComm();       // Start Socket thread
    void StopComm();        // Stop Socket thread

    // Create a socket - Server side (support for multiple adapters)
    bool CreateSocketEx(LPCTSTR strHost, LPCTSTR strServiceName, int nFamily, int nType, UINT uOptions /* = 0 */);
    // Create a Socket - Server side
    bool __declspec(dllexport) CreateSocket(LPCTSTR strServiceName, int nProtocol, int nType, UINT uOptions = 0);
    // Create a socket, connect to (Client side)
    bool __declspec(dllexport) ConnectTo(LPCTSTR strDestination, LPCTSTR strServiceName, int nProtocol, int nType);

// Event function - override to get data
    virtual void OnDataReceived(const LPBYTE lpBuffer, DWORD dwCount);
	virtual void OnEvent(UINT uEvent, LPVOID lpvData);
// Run function - override to implement a new behaviour
    virtual void Run();

// Data function
    DWORD ReadComm(LPBYTE lpBuffer, DWORD dwSize, DWORD dwTimeout);
    DWORD WriteComm(const LPBYTE lpBuffer, DWORD dwCount, DWORD dwTimeout);

    // Utility functions
    static SOCKET WaitForConnection(SOCKET sock); // Wait For a new connection (Server side)
    static bool ShutdownConnection(SOCKET sock);  // Shutdown a connection
    static USHORT GetPortNumber( LPCTSTR strServiceName );  // Get service port number
    static ULONG GetIPAddress( LPCTSTR strHostName );   // Get IP address of a host
    static bool GetLocalName(LPTSTR strName, UINT nSize);   // GetLocalName
    static bool __declspec(dllexport) GetLocalAddress(LPTSTR strAddress, UINT nSize); // GetLocalAddress
// SocketComm - data
protected:
    HANDLE      m_hComm;        // Serial Comm handle
    HANDLE      m_hThread;      // Thread Comm handle
    bool        m_bServer;      // Server mode (true)
    bool        m_bSmartAddressing; // Smart Addressing mode (true) - many listeners
    bool        m_bBroadcast;   // Broadcast mode
    CSockAddrList m_AddrList;   // Connection address list for broadcast
    HANDLE      m_hMutex;       // Mutex object
// SocketComm - function
protected:
    // Synchronization function
    void LockList();            // Lock the object
    void UnlockList();          // Unlock the object

    static UINT WINAPI SocketThreadProc(LPVOID pParam);

private:





/////////////////////////////////////////SPI PACKET//////////////////////////////////
public:
	
};

#endif // _SOCKETCOMM_H_
