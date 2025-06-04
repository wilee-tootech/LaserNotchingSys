/***************************************************************************
*                                                                          *
*   wuerror.mc --  error code definitions for Windows Update.              *
*                                                                          *
*   Copyright (c) 2004, Microsoft Corp. All rights reserved.               *
*                                                                          *
***************************************************************************/
#ifndef _WUERROR_
#define _WUERROR_

#if defined (_MSC_VER) && (_MSC_VER >= 1020) && !defined(__midl)
#pragma once
#endif
///////////////////////////////////////////////////////////////////////////////
// Windows Update Success Codes
///////////////////////////////////////////////////////////////////////////////
//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: WU_S_SERVICE_STOP
//
// MessageText:
//
//  Service stopped.
//
#define WU_S_SERVICE_STOP                0x00240001L

//
// MessageId: WU_S_SELFUPDATE
//
// MessageText:
//
//  Agent selfupdates.
//
#define WU_S_SELFUPDATE                  0x00240002L

//
// MessageId: WU_S_UPDATE_ERROR
//
// MessageText:
//
//  Overall operation completed but error occurred while processing one or more specified updates.
//
#define WU_S_UPDATE_ERROR                0x00240003L

//
// MessageId: WU_S_MARKED_FOR_DISCONNECT
//
// MessageText:
//
//  The caller attempted to disconnect an operation but the operation is busy calling back so the callback is marked for disconnect later.
//
#define WU_S_MARKED_FOR_DISCONNECT       0x00240004L

//
// MessageId: WU_S_REBOOT_REQUIRED
//
// MessageText:
//
//  The system needs to be rebooted to complete installtation.
//
#define WU_S_REBOOT_REQUIRED             0x00240005L

//
// MessageId: WU_S_ALREADY_INSTALLED
//
// MessageText:
//
//  The update to be installed is already installed.
//
#define WU_S_ALREADY_INSTALLED           0x00240006L

//
// MessageId: WU_S_ALREADY_UNINSTALLED
//
// MessageText:
//
//  The update to be uninstalled is already not installed.
//
#define WU_S_ALREADY_UNINSTALLED         0x00240007L

//
// MessageId: WU_S_ALREADY_DOWNLOADED
//
// MessageText:
//
//  The update to be downloaded is already downloaded.
//
#define WU_S_ALREADY_DOWNLOADED          0x00240008L

///////////////////////////////////////////////////////////////////////////////
// Windows Update Error Codes
///////////////////////////////////////////////////////////////////////////////
//
// MessageId: WU_E_NO_SERVICE
//
// MessageText:
//
//  Service stopped.
//  For whatever reason, SUS agent can not provide the service.
//
#define WU_E_NO_SERVICE                  0x80240001L

//
// MessageId: WU_E_MAX_CAPACITY_REACHED
//
// MessageText:
//
//  maximum capacity of the service is reached
//
#define WU_E_MAX_CAPACITY_REACHED        0x80240002L

//
// MessageId: WU_E_UNKNOWN_ID
//
// MessageText:
//
//  Id not found
//
#define WU_E_UNKNOWN_ID                  0x80240003L

//
// MessageId: WU_E_NOT_INITIALIZED
//
// MessageText:
//
//  object is not correctly initialized
//
#define WU_E_NOT_INITIALIZED             0x80240004L

//
// MessageId: WU_E_RANGEOVERLAP
//
// MessageText:
//
//  Update handler attempted to request a byte range that overlapped a 
//  previously requested byte range
//
#define WU_E_RANGEOVERLAP                0x80240005L

//
// MessageId: WU_E_TOOMANYRANGES
//
// MessageText:
//
//  Update handler attempted to request too many ranges (more than 2^31 - 1)
//
#define WU_E_TOOMANYRANGES               0x80240006L

//
// MessageId: WU_E_INVALIDINDEX
//
// MessageText:
//
//  An attempt was made to use an invalid index
//
#define WU_E_INVALIDINDEX                0x80240007L

//
// MessageId: WU_E_ITEMNOTFOUND
//
// MessageText:
//
//  A query was made for an item with a particular key and that key was not found
//
#define WU_E_ITEMNOTFOUND                0x80240008L

//
// MessageId: WU_E_OPERATIONINPROGRESS
//
// MessageText:
//
//  The caller attempted to perform an operation on an interface while another operation was in progress.
//
#define WU_E_OPERATIONINPROGRESS         0x80240009L

//
// MessageId: WU_E_COULDNOTCANCEL
//
// MessageText:
//
//  The caller attempted to cancel an operation that is not cancelable
//
#define WU_E_COULDNOTCANCEL              0x8024000AL

//
// MessageId: WU_E_CALL_CANCELLED
//
// MessageText:
//
//  call has been cancelled
//
#define WU_E_CALL_CANCELLED              0x8024000BL

//
// MessageId: WU_E_NOOP
//
// MessageText:
//
//  no operation is needed
//
#define WU_E_NOOP                        0x8024000CL

//
// MessageId: WU_E_XML_MISSINGDATA
//
// MessageText:
//
//  the SUS agent is attempting to parse an update's XML blob and has
//  not found expected data
//
#define WU_E_XML_MISSINGDATA             0x8024000DL

//
// MessageId: WU_E_XML_INVALID
//
// MessageText:
//
//  the SUS agent is attempting to parse an update's XML blob and has
//  encountered data that is invalid
//
#define WU_E_XML_INVALID                 0x8024000EL

//
// MessageId: WU_E_CYCLE_DETECTED
//
// MessageText:
//
//  cycle detected in meta data
//
#define WU_E_CYCLE_DETECTED              0x8024000FL

//
// MessageId: WU_E_TOO_DEEP_RELATION
//
// MessageText:
//
//  too deep relation ship found
//
#define WU_E_TOO_DEEP_RELATION           0x80240010L

//
// MessageId: WU_E_INVALID_RELATIONSHIP
//
// MessageText:
//
//  relationship data wrong for an update
//
#define WU_E_INVALID_RELATIONSHIP        0x80240011L

//
// MessageId: WU_E_REG_VALUE_INVALID
//
// MessageText:
//
//  registry value was read but is invalid
//
#define WU_E_REG_VALUE_INVALID           0x80240012L

//
// MessageId: WU_E_DUPLICATE_ITEM
//
// MessageText:
//
//  try to add a duplicated item to a list
//
#define WU_E_DUPLICATE_ITEM              0x80240013L

//
// MessageId: WU_E_INSTALL_NOT_ALLOWED
//
// MessageText:
//
//  try to install while another install is going on 
//  or reboot is pending
//
#define WU_E_INSTALL_NOT_ALLOWED         0x80240016L

//
// MessageId: WU_E_NOT_APPLICABLE
//
// MessageText:
//
//  install is not needed because no updates are applicable
//
#define WU_E_NOT_APPLICABLE              0x80240017L

//
// MessageId: WU_E_NO_USERTOKEN
//
// MessageText:
//
//  operation failed due to missing user token
//
#define WU_E_NO_USERTOKEN                0x80240018L

//
// MessageId: WU_E_EXCLUSIVE_INSTALL_CONFILCT
//
// MessageText:
//
//  try to install an exclusive update with other updates at the same time
//
#define WU_E_EXCLUSIVE_INSTALL_CONFILCT  0x80240019L

//
// MessageId: WU_E_POLICY_NOT_SET
//
// MessageText:
//
//  policy value is not set
//
#define WU_E_POLICY_NOT_SET              0x8024001AL

//
// MessageId: WU_E_SELFUPDATE_IN_PROGRESS
//
// MessageText:
//
//  self-update in progress
//
#define WU_E_SELFUPDATE_IN_PROGRESS      0x8024001BL

//
// MessageId: WU_E_INVALID_UPDATE
//
// MessageText:
//
//  an update had bogus metadata
//
#define WU_E_INVALID_UPDATE              0x8024001DL

//
// MessageId: WU_E_SERVICE_STOP
//
// MessageText:
//
//  call was aborted due to service stop or system shut down
//
#define WU_E_SERVICE_STOP                0x8024001EL

//
// MessageId: WU_E_NO_CONNECTION
//
// MessageText:
//
//  no network connection is available to finish the operation
//
#define WU_E_NO_CONNECTION               0x8024001FL

//
// MessageId: WU_E_NO_INTERACTIVE_USER
//
// MessageText:
//
//  interactive user is missing to finish the operation
//
#define WU_E_NO_INTERACTIVE_USER         0x80240020L

//
// MessageId: WU_E_TIME_OUT
//
// MessageText:
//
//  operation timed out
//
#define WU_E_TIME_OUT                    0x80240021L

//
// MessageId: WU_E_ALL_UPDATES_FAILED
//
// MessageText:
//
//  operation failed on all specified updates
//
#define WU_E_ALL_UPDATES_FAILED          0x80240022L

//
// MessageId: WU_E_EULAS_DECLINED
//
// MessageText:
//
//  EULA's for all the updates are declined
//
#define WU_E_EULAS_DECLINED              0x80240023L

//
// MessageId: WU_E_NO_UPDATE
//
// MessageText:
//
//  there are no updates
//
#define WU_E_NO_UPDATE                   0x80240024L

//
// MessageId: WU_E_USER_ACCESS_DISABLED
//
// MessageText:
//
//  User access to Windows Update is prevented by Group Policy setting
//
#define WU_E_USER_ACCESS_DISABLED        0x80240025L

//
// MessageId: WU_E_INVALID_UPDATE_TYPE
//
// MessageText:
//
//  invalid type of update
//
#define WU_E_INVALID_UPDATE_TYPE         0x80240026L

//
// MessageId: WU_E_URL_TOO_LONG
//
// MessageText:
//
//  URL is too long
//
#define WU_E_URL_TOO_LONG                0x80240027L

//
// MessageId: WU_E_UNINSTALL_NOT_ALLOWED
//
// MessageText:
//
//  uninstall is not allowed due to non managed environment
//
#define WU_E_UNINSTALL_NOT_ALLOWED       0x80240028L

//
// MessageId: WU_E_INVALID_PRODUCT_LICENSE
//
// MessageText:
//
//  A product with an invalid license was found on the system.
//
#define WU_E_INVALID_PRODUCT_LICENSE     0x80240029L

//
// MessageId: WU_E_MISSING_HANDLER
//
// MessageText:
//
//  A component required for detecting applicable updates was missing.
//
#define WU_E_MISSING_HANDLER             0x8024002AL

//
// MessageId: WU_E_LEGACYSERVER
//
// MessageText:
//
//  The Sus server we are talking to is a Legacy Sus Server (Sus Server 1.0)
//
#define WU_E_LEGACYSERVER                0x8024002BL

//
// MessageId: WU_E_BIN_SOURCE_ABSENT
//
// MessageText:
//
//  A binary-delta patch failed because the source was required
//
#define WU_E_BIN_SOURCE_ABSENT           0x8024002CL

//
// MessageId: WU_E_SOURCE_ABSENT
//
// MessageText:
//
//  a patch failed because the source was required
//
#define WU_E_SOURCE_ABSENT               0x8024002DL

//
// MessageId: WU_E_WU_DISABLED
//
// MessageText:
//
//  non managed server access is disallowed
//
#define WU_E_WU_DISABLED                 0x8024002EL

//
// MessageId: WU_E_CALL_CANCELLED_BY_POLICY
//
// MessageText:
//
//  call cancelled because of DisableWindowsUpdateAccess 
//  policy takes effect
//
#define WU_E_CALL_CANCELLED_BY_POLICY    0x8024002FL

//
// MessageId: WU_E_INVALID_PROXY_SERVER
//
// MessageText:
//
//  invalid format for proxy list
//
#define WU_E_INVALID_PROXY_SERVER        0x80240030L

//
// MessageId: WU_E_INVALID_FILE
//
// MessageText:
//
//  file is not of the right format
//
#define WU_E_INVALID_FILE                0x80240031L

//
// MessageId: WU_E_INVALID_CRITERIA
//
// MessageText:
//
//  invalid criteria string
//
#define WU_E_INVALID_CRITERIA            0x80240032L

//
// MessageId: WU_E_EULA_UNAVAILABLE
//
// MessageText:
//
//  EULA download failure
//
#define WU_E_EULA_UNAVAILABLE            0x80240033L

//
// MessageId: WU_E_DOWNLOAD_FAILED
//
// MessageText:
//
//  Failed to download
//
#define WU_E_DOWNLOAD_FAILED             0x80240034L

//
// MessageId: WU_E_UPDATE_NOT_PROCESSED
//
// MessageText:
//
//  INTERNAL ONLY: The update was not processed.
//
#define WU_E_UPDATE_NOT_PROCESSED        0x80240035L

//
// MessageId: WU_E_INVALID_OPERATION
//
// MessageText:
//
//  The operation is invalid for the object's current state.
//
#define WU_E_INVALID_OPERATION           0x80240036L

//
// MessageId: WU_E_NOT_SUPPORTED
//
// MessageText:
//
//  The invoked functionality is not supported.
//
#define WU_E_NOT_SUPPORTED               0x80240037L

//
// MessageId: WU_E_WINHTTP_INVALID_FILE
//
// MessageText:
//
//  WinHttp download file format is invalid.
//  
//
#define WU_E_WINHTTP_INVALID_FILE        0x80240038L

//
// MessageId: WU_E_UNEXPECTED
//
// MessageText:
//
//  generic unexpected failure
//
#define WU_E_UNEXPECTED                  0x80240FFFL

///////////////////////////////////////////////////////////////////////////////
// Windows Installer minor errors
//
// The following errors are used to indicate that part of a search failed for
// MSI problems. Another part of the search may successfully return updates.
// All MSI minor codes should share the same error code range so that the caller
// tell that they are related to Windows Installer.
///////////////////////////////////////////////////////////////////////////////
//
// MessageId: WU_E_MSI_WRONG_VERSION
//
// MessageText:
//
//  The MSI version on the machine is less than what we expect (SUS 2.0 requires MSI 3.0)
//
#define WU_E_MSI_WRONG_VERSION           0x80241001L

//
// MessageId: WU_E_MSI_NOT_CONFIGURED
//
// MessageText:
//
//  MSI is not configured
//
#define WU_E_MSI_NOT_CONFIGURED          0x80241002L

//
// MessageId: WU_E_MSP_DISABLED
//
// MessageText:
//
//  MSI patching is disabled by policy
//
#define WU_E_MSP_DISABLED                0x80241003L

//
// MessageId: WU_E_MSP_UNEXPECTED
//
// MessageText:
//
//  generic unexpected MSP failure
//
#define WU_E_MSP_UNEXPECTED              0x80241FFFL

///////////////////////////////////////////////////////////////////////////////
// Protocol Talker errors
//
// The following map to SOAPCLIENT_ERRORs from atlsoap.h. These errors
// are obtained from calling GetClientError() on the CClientWebService
// object.
///////////////////////////////////////////////////////////////////////////////
//
// MessageId: WU_E_PT_SOAPCLIENT_BASE
//
// MessageText:
//
//  Used as a base to map SOAPCLIENT_ERROR errors.
//
#define WU_E_PT_SOAPCLIENT_BASE          0x80244000L

//
// MessageId: WU_E_PT_SOAPCLIENT_INITIALIZE
//
// MessageText:
//
//  SOAPCLIENT_INITIALIZE_ERROR initialization failed -- most likely an MSXML installation problem
//
#define WU_E_PT_SOAPCLIENT_INITIALIZE    0x80244001L

//
// MessageId: WU_E_PT_SOAPCLIENT_OUTOFMEMORY
//
// MessageText:
//
//  SOAPCLIENT_OUTOFMEMORY out of memory
//
#define WU_E_PT_SOAPCLIENT_OUTOFMEMORY   0x80244002L

//
// MessageId: WU_E_PT_SOAPCLIENT_GENERATE
//
// MessageText:
//
//  SOAPCLIENT_GENERATE_ERROR failed in generating the response
//
#define WU_E_PT_SOAPCLIENT_GENERATE      0x80244003L

//
// MessageId: WU_E_PT_SOAPCLIENT_CONNECT
//
// MessageText:
//
//  SOAPCLIENT_CONNECT_ERROR failed connecting to server
//
#define WU_E_PT_SOAPCLIENT_CONNECT       0x80244004L

//
// MessageId: WU_E_PT_SOAPCLIENT_SEND
//
// MessageText:
//
//  SOAPCLIENT_SEND_ERROR failed in sending message
//  This generic error has been deprecated in favor of the more
//  specific underlying WinHTTP errors, which will be returned
//  when the client encounters an error communicating with the server.
//
#define WU_E_PT_SOAPCLIENT_SEND          0x80244005L

//
// MessageId: WU_E_PT_SOAPCLIENT_SERVER
//
// MessageText:
//
//  SOAPCLIENT_SERVER_ERROR server error
//
#define WU_E_PT_SOAPCLIENT_SERVER        0x80244006L

//
// MessageId: WU_E_PT_SOAPCLIENT_SOAPFAULT
//
// MessageText:
//
//  SOAPCLIENT_SOAPFAULT a SOAP Fault was returned by the server
//  See the more specific WU_E_PT_SOAP_xxxx mappings 
//  when a SOAP fault was returned by the server.
//
#define WU_E_PT_SOAPCLIENT_SOAPFAULT     0x80244007L

//
// MessageId: WU_E_PT_SOAPCLIENT_PARSEFAULT
//
// MessageText:
//
//  SOAPCLIENT_PARSEFAULT_ERROR failed in parsing SOAP fault
//
#define WU_E_PT_SOAPCLIENT_PARSEFAULT    0x80244008L

//
// MessageId: WU_E_PT_SOAPCLIENT_READ
//
// MessageText:
//
//  SOAPCLIENT_READ_ERROR failed in reading response
//
#define WU_E_PT_SOAPCLIENT_READ          0x80244009L

//
// MessageId: WU_E_PT_SOAPCLIENT_PARSE
//
// MessageText:
//
//  SOAPCLIENT_PARSE_ERROR failed in parsing response
//
#define WU_E_PT_SOAPCLIENT_PARSE         0x8024400AL

// The following map to SOAP_ERROR_CODEs from atlsoap.h. These errors
// are obtained from the m_fault.m_soapErrCode member on the
// CClientWebService object when GetClientError() returned
// SOAPCLIENT_SOAPFAULT.
//
// MessageId: WU_E_PT_SOAP_VERSION
//
// MessageText:
//
//  SOAP_E_VERSION_MISMATCH Invalid namespace for the SOAP envelope
//
#define WU_E_PT_SOAP_VERSION             0x8024400BL

//
// MessageId: WU_E_PT_SOAP_MUST_UNDERSTAND
//
// MessageText:
//
//  SOAP_E_MUST_UNDERSTAND Child of header with mustUnderstand
//  attribute = 1 wasn't understood or obeyed
//
#define WU_E_PT_SOAP_MUST_UNDERSTAND     0x8024400CL

//
// MessageId: WU_E_PT_SOAP_CLIENT
//
// MessageText:
//
//  SOAP_E_CLIENT The message was malformed or incomplete.
//  No reason to retry unless problem fixed.
//
#define WU_E_PT_SOAP_CLIENT              0x8024400DL

//
// MessageId: WU_E_PT_SOAP_SERVER
//
// MessageText:
//
//  SOAP_E_SERVER The message was OK but server couldn't
//  process at the moment. Same message
//  may succeed at a later time.
//
#define WU_E_PT_SOAP_SERVER              0x8024400EL

//
// MessageId: WU_E_PT_WMI_ERROR
//
// MessageText:
//
//  An unspecified error occurred using WMI
//
#define WU_E_PT_WMI_ERROR                0x8024400FL

//
// MessageId: WU_E_PT_EXCEEDED_MAX_SERVER_TRIPS
//
// MessageText:
//
//  The maximum allowed number of round trips to the server was exceeded
//
#define WU_E_PT_EXCEEDED_MAX_SERVER_TRIPS 0x80244010L

//
// MessageId: WU_E_PT_SUS_SERVER_NOT_SET
//
// MessageText:
//
//  WUServer policy value is missing in the registry
//
#define WU_E_PT_SUS_SERVER_NOT_SET       0x80244011L

//
// MessageId: WU_E_PT_DOUBLE_INITIALIZATION
//
// MessageText:
//
//  object is initialized second time
//
#define WU_E_PT_DOUBLE_INITIALIZATION    0x80244012L

//
// MessageId: WU_E_PT_INVALID_COMPUTER_NAME
//
// MessageText:
//
//  Cannot determine computer name
//
#define WU_E_PT_INVALID_COMPUTER_NAME    0x80244013L

//
// MessageId: WU_E_PT_INVALID_COMPUTER_LSID
//
// MessageText:
//
//  Cannot determine computer LSID
//
#define WU_E_PT_INVALID_COMPUTER_LSID    0x80244014L

//
// MessageId: WU_E_PT_REFRESH_CACHE_REQUIRED
//
// MessageText:
//
//  Server replied with InvalidCookie or ServerChanged 
//  Caller should refresh its internal state then repeat the call to Protocol Talker
//
#define WU_E_PT_REFRESH_CACHE_REQUIRED   0x80244015L

//
// MessageId: WU_E_PT_HTTP_STATUS_BAD_REQUEST
//
// MessageText:
//
//  Http status 400 - invalid syntax
//
#define WU_E_PT_HTTP_STATUS_BAD_REQUEST  0x80244016L

//
// MessageId: WU_E_PT_HTTP_STATUS_DENIED
//
// MessageText:
//
//  Http status 401 - access denied
//
#define WU_E_PT_HTTP_STATUS_DENIED       0x80244017L

//
// MessageId: WU_E_PT_HTTP_STATUS_FORBIDDEN
//
// MessageText:
//
//  Http status 403 - request forbidden
//
#define WU_E_PT_HTTP_STATUS_FORBIDDEN    0x80244018L

//
// MessageId: WU_E_PT_HTTP_STATUS_NOT_FOUND
//
// MessageText:
//
//  Http status 404 - object not found
//
#define WU_E_PT_HTTP_STATUS_NOT_FOUND    0x80244019L

//
// MessageId: WU_E_PT_HTTP_STATUS_BAD_METHOD
//
// MessageText:
//
//  Http status 405 - method is not allowed
//
#define WU_E_PT_HTTP_STATUS_BAD_METHOD   0x8024401AL

//
// MessageId: WU_E_PT_HTTP_STATUS_PROXY_AUTH_REQ
//
// MessageText:
//
//  Http status 407 - proxy authentication required
//
#define WU_E_PT_HTTP_STATUS_PROXY_AUTH_REQ 0x8024401BL

//
// MessageId: WU_E_PT_HTTP_STATUS_REQUEST_TIMEOUT
//
// MessageText:
//
//  Http status 408 - server timed out waiting for request
//
#define WU_E_PT_HTTP_STATUS_REQUEST_TIMEOUT 0x8024401CL

//
// MessageId: WU_E_PT_HTTP_STATUS_CONFLICT
//
// MessageText:
//
//  Http status 409 - user should resubmit with more info
//
#define WU_E_PT_HTTP_STATUS_CONFLICT     0x8024401DL

//
// MessageId: WU_E_PT_HTTP_STATUS_GONE
//
// MessageText:
//
//  Http status 410 - the resource is no longer available
//
#define WU_E_PT_HTTP_STATUS_GONE         0x8024401EL

//
// MessageId: WU_E_PT_HTTP_STATUS_SERVER_ERROR
//
// MessageText:
//
//  Http status 500 - internal server error
//
#define WU_E_PT_HTTP_STATUS_SERVER_ERROR 0x8024401FL

//
// MessageId: WU_E_PT_HTTP_STATUS_NOT_SUPPORTED
//
// MessageText:
//
//  Http status 501 - required not supported
//
#define WU_E_PT_HTTP_STATUS_NOT_SUPPORTED 0x80244020L

//
// MessageId: WU_E_PT_HTTP_STATUS_BAD_GATEWAY
//
// MessageText:
//
//  Http status 502 - error response received from gateway
//
#define WU_E_PT_HTTP_STATUS_BAD_GATEWAY  0x80244021L

//
// MessageId: WU_E_PT_HTTP_STATUS_SERVICE_UNAVAIL
//
// MessageText:
//
//  Http status 503 - temporarily overloaded
//
#define WU_E_PT_HTTP_STATUS_SERVICE_UNAVAIL 0x80244022L

//
// MessageId: WU_E_PT_HTTP_STATUS_GATEWAY_TIMEOUT
//
// MessageText:
//
//  Http status 504 - timed out waiting for gateway
//
#define WU_E_PT_HTTP_STATUS_GATEWAY_TIMEOUT 0x80244023L

//
// MessageId: WU_E_PT_HTTP_STATUS_VERSION_NOT_SUP
//
// MessageText:
//
//  Http status 505 - HTTP version not supported
//
#define WU_E_PT_HTTP_STATUS_VERSION_NOT_SUP 0x80244024L

//
// MessageId: WU_E_PT_FILE_LOCATIONS_CHANGED
//
// MessageText:
//
//  Server replied with FileLocationsChange
//  Caller should refresh its internal state then repeat the call to Protocol Talker
//
#define WU_E_PT_FILE_LOCATIONS_CHANGED   0x80244025L

//
// MessageId: WU_E_PT_REGISTRATION_NOT_SUPPORTED
//
// MessageText:
//
//  Client doesn't support registration with non-SUS server
//
#define WU_E_PT_REGISTRATION_NOT_SUPPORTED 0x80244026L

//
// MessageId: WU_E_PT_NO_AUTH_PLUGINS_REQUESTED
//
// MessageText:
//
//  Server returned an empty AuthInfo list
//
#define WU_E_PT_NO_AUTH_PLUGINS_REQUESTED 0x80244027L

//
// MessageId: WU_E_PT_NO_AUTH_COOKIES_CREATED
//
// MessageText:
//
//  The client was unable to create any valid auth cookies
//
#define WU_E_PT_NO_AUTH_COOKIES_CREATED  0x80244028L

//
// MessageId: WU_E_PT_INVALID_CONFIG_PROP
//
// MessageText:
//
//  One of the Config ConfigurationProperty values was wrong
//
#define WU_E_PT_INVALID_CONFIG_PROP      0x80244029L

//
// MessageId: WU_E_PT_CONFIG_PROP_MISSING
//
// MessageText:
//
//  One of the Config ConfigurationProperty values was wrong
//
#define WU_E_PT_CONFIG_PROP_MISSING      0x8024402AL

//
// MessageId: WU_E_PT_HTTP_STATUS_NOT_MAPPED
//
// MessageText:
//
//  Http status other than 200, but not mapped above
//
#define WU_E_PT_HTTP_STATUS_NOT_MAPPED   0x8024402BL

//
// MessageId: WU_E_PT_WINHTTP_NAME_NOT_RESOLVED
//
// MessageText:
//
//  Winhttp SendRequest/ReceiveResponse failed with 0x2ee7 error.
//  Either the proxy server or target server name can not be resolved.
//  Corresponding to ERROR_WINHTTP_NAME_NOT_RESOLVED. 
//  Stop/Restart service or reboot the machine if you see this error frequently. 
//
#define WU_E_PT_WINHTTP_NAME_NOT_RESOLVED 0x8024402CL

//
// MessageId: WU_E_PT_SAME_REDIR_ID
//
// MessageText:
//
//  During recovery Protocol Talker failed to download a wuredir.cab with
//  a newer redirectorId from the server
//
#define WU_E_PT_SAME_REDIR_ID            0x8024502DL

//
// MessageId: WU_E_PT_NO_MANAGED_RECOVER
//
// MessageText:
//
//  A redirector recovery action was specified, but the server is managed.
//
#define WU_E_PT_NO_MANAGED_RECOVER       0x8024502EL

//
// MessageId: WU_E_PT_ECP_SUCCEEDED_WITH_ERRORS
//
// MessageText:
//
//  External cabs processing succeeded with some errors.
//
#define WU_E_PT_ECP_SUCCEEDED_WITH_ERRORS 0x8024402FL

//
// MessageId: WU_E_PT_ECP_INIT_FAILED
//
// MessageText:
//
//  A Failure happened while intializing external cab processor.
//
#define WU_E_PT_ECP_INIT_FAILED          0x80244030L

//
// MessageId: WU_E_PT_ECP_INVALID_FILE_FORMAT
//
// MessageText:
//
//  The file format for the metadata file was invalid.
//
#define WU_E_PT_ECP_INVALID_FILE_FORMAT  0x80244031L

//
// MessageId: WU_E_PT_ECP_INVALID_METADATA
//
// MessageText:
//
//  The metadata expected by external cab processor was invalid.
//
#define WU_E_PT_ECP_INVALID_METADATA     0x80244032L

//
// MessageId: WU_E_PT_ECP_FAILURE_TO_EXTRACT_DIGEST
//
// MessageText:
//
//  There was a failure to extract the file digest.
//
#define WU_E_PT_ECP_FAILURE_TO_EXTRACT_DIGEST 0x80244033L

//
// MessageId: WU_E_PT_ECP_FAILURE_TO_DECOMPRESS_CAB_FILE
//
// MessageText:
//
//  There was a failure to decompress the cab file.
//
#define WU_E_PT_ECP_FAILURE_TO_DECOMPRESS_CAB_FILE 0x80244034L

//
// MessageId: WU_E_PT_ECP_FILE_LOCATION_ERROR
//
// MessageText:
//
//  There was a failure to in getting the file locations.
//
#define WU_E_PT_ECP_FILE_LOCATION_ERROR  0x80244035L

//
// MessageId: WU_E_PT_UNEXPECTED
//
// MessageText:
//
//  generic unexpected protocol talker failure
//
#define WU_E_PT_UNEXPECTED               0x80244FFFL

///////////////////////////////////////////////////////////////////////////////
// Redirector errors
//
// The following errors are generated by the components that download and
// parse the wuredir.cab
///////////////////////////////////////////////////////////////////////////////
//
// MessageId: WU_E_REDIRECTOR_LOAD_XML
//
// MessageText:
//
//  The XML extracted from the wuredir.cab failed to load into the DOM
//
#define WU_E_REDIRECTOR_LOAD_XML         0x80245001L

//
// MessageId: WU_E_REDIRECTOR_S_FALSE
//
// MessageText:
//
//  An expected XML element node, map, attribute, value, etc. could not be found.
//
#define WU_E_REDIRECTOR_S_FALSE          0x80245002L

//
// MessageId: WU_E_REDIRECTOR_ID_SMALLER
//
// MessageText:
//
//  The redirectorId in the downloaded wuredir.cab is smaller than the cached cab.
//
#define WU_E_REDIRECTOR_ID_SMALLER       0x80245003L

//
// MessageId: WU_E_REDIRECTOR_UNEXPECTED
//
// MessageText:
//
//  generic unexpected redirector failure
//
#define WU_E_REDIRECTOR_UNEXPECTED       0x80245FFFL

///////////////////////////////////////////////////////////////////////////////
// driver util errors
//
// The device PnP enumerated device was pruned from the SystemSpec because
// one of the hardware or compatible IDs matched an installed printer driver.
// This is not considered a fatal error and the device is simply skipped.
///////////////////////////////////////////////////////////////////////////////
//
// MessageId: WU_E_DRV_PRUNED
//
// MessageText:
//
//  Driver was pruned.
//
#define WU_E_DRV_PRUNED                  0x8024C001L

//
// MessageId: WU_E_DRV_NOPROP_OR_LEGACY
//
// MessageText:
//
//  A property wasn't found. Depending on the context this may not be an error.
//  For example, it is expected that legacy drivers will be missing properties
//  we require (there is no support for legacy drivers).
//
#define WU_E_DRV_NOPROP_OR_LEGACY        0x8024C002L

//
// MessageId: WU_E_DRV_REG_MISMATCH
//
// MessageText:
//
//  The registry type we read didn't match what was expected
//
#define WU_E_DRV_REG_MISMATCH            0x8024C003L

//
// MessageId: WU_E_DRV_NO_METADATA
//
// MessageText:
//
//  The driver Update didn't have a metadata blob
//
#define WU_E_DRV_NO_METADATA             0x8024C004L

//
// MessageId: WU_E_DRV_MISSING_ATTRIBUTE
//
// MessageText:
//
//  The driver Update metadata was missing a required attribute
//
#define WU_E_DRV_MISSING_ATTRIBUTE       0x8024C005L

//
// MessageId: WU_E_DRV_SYNC_FAILED
//
// MessageText:
//
//  A driver sync operation failed
//
#define WU_E_DRV_SYNC_FAILED             0x8024C006L

//
// MessageId: WU_E_DRV_NO_PRINTER_CONTENT
//
// MessageText:
//
//  No printer driver content following SyncApplicablePrinters
//
#define WU_E_DRV_NO_PRINTER_CONTENT      0x8024C007L

//
// MessageId: WU_E_DRV_UNEXPECTED
//
// MessageText:
//
//  generic unexpected driver utility failure
//
#define WU_E_DRV_UNEXPECTED              0x8024CFFFL

//////////////////////////////////////////////////////////////////////////////
// data store errors
///////////////////////////////////////////////////////////////////////////////
//
// MessageId: WU_E_DS_SHUTDOWN
//
// MessageText:
//
//  The call failed because the SUS agent is shutting down
//
#define WU_E_DS_SHUTDOWN                 0x80248000L

//
// MessageId: WU_E_DS_INUSE
//
// MessageText:
//
//  The call failed because the data store is in use and the operation can 
//  only be executed on an idle data store.
//
#define WU_E_DS_INUSE                    0x80248001L

//
// MessageId: WU_E_DS_INVALID
//
// MessageText:
//
//  The data store is in an invalid state. This can occur if we attempt to 
//  validate the database schema and find a mismatch between the current
//  state and the state we expect.
//
#define WU_E_DS_INVALID                  0x80248002L

//
// MessageId: WU_E_DS_TABLEMISSING
//
// MessageText:
//
//  The data store has a missing table
//
#define WU_E_DS_TABLEMISSING             0x80248003L

//
// MessageId: WU_E_DS_TABLEINCORRECT
//
// MessageText:
//
//  The data store has a table whose columns are not what SUS expects
//
#define WU_E_DS_TABLEINCORRECT           0x80248004L

//
// MessageId: WU_E_DS_INVALIDTABLENAME
//
// MessageText:
//
//  The caller tried to open a table that is not in the datastore
//
#define WU_E_DS_INVALIDTABLENAME         0x80248005L

//
// MessageId: WU_E_DS_BADVERSION
//
// MessageText:
//
//  The data store's version does not match what the client expects
//
#define WU_E_DS_BADVERSION               0x80248006L

//
// MessageId: WU_E_DS_NODATA
//
// MessageText:
//
//  The caller asked for data that is not in the data store
//
#define WU_E_DS_NODATA                   0x80248007L

//
// MessageId: WU_E_DS_MISSINGDATA
//
// MessageText:
//
//  The data store is in an invalid state because data that should be present
//  is missing. This error can occur if we encounter a column in a table that
//  is NULL when it is not allowed to be NULL.
//
#define WU_E_DS_MISSINGDATA              0x80248008L

//
// MessageId: WU_E_DS_MISSINGREF
//
// MessageText:
//
//  The data store is in an invalid state because data that should be present
//  is missing. This will occur if we try to fetch a linked row
//  from another table and the linked row does not exist.  This can
//  happen with EULAs, files, and/or localized properties referenced
//  by an update.
//
#define WU_E_DS_MISSINGREF               0x80248009L

//
// MessageId: WU_E_DS_UNKNOWNHANDLER
//
// MessageText:
//
//  The caller attempted to add an update that used an unknown update handler
//
#define WU_E_DS_UNKNOWNHANDLER           0x8024800AL

//
// MessageId: WU_E_DS_CANTDELETE
//
// MessageText:
//
//  The caller attempted to delete an update that is referenced by one or more services
//
#define WU_E_DS_CANTDELETE               0x8024800BL

//
// MessageId: WU_E_DS_LOCKTIMEOUTEXPIRED
//
// MessageText:
//
//  The caller attempted to delete an update that is referenced by one or more services
//
#define WU_E_DS_LOCKTIMEOUTEXPIRED       0x8024800CL

//
// MessageId: WU_E_DS_NOCATEGORIES
//
// MessageText:
//
//  The caller attempted to add a non-toplevel category update that contained
//  no parent categories
//
#define WU_E_DS_NOCATEGORIES             0x8024800DL

//
// MessageId: WU_E_DS_ROWEXISTS
//
// MessageText:
//
//  The caller attempted to add a row whose primary key matched an existing row
//
#define WU_E_DS_ROWEXISTS                0x8024800EL

//
// MessageId: WU_E_DS_STOREFILELOCKED
//
// MessageText:
//
//  We attempted to initialize the datastore, but it was locked by another process
//
#define WU_E_DS_STOREFILELOCKED          0x8024800FL

//
// MessageId: WU_E_DS_CANNOTREGISTER
//
// MessageText:
//
//  The caller is attepting to register the datastore with COM, but the store
//  cannot be loaded into the current process
//
#define WU_E_DS_CANNOTREGISTER           0x80248010L

//
// MessageId: WU_E_DS_UNABLETOSTART
//
// MessageText:
//
//  Could not create an out of proc datastore object
//
#define WU_E_DS_UNABLETOSTART            0x80248011L

//
// MessageId: WU_E_DS_MISSINGFILEFORURL
//
// MessageText:
//
//  a file URL was passed in for a file that does not exist in the datastore
//
#define WU_E_DS_MISSINGFILEFORURL        0x80248012L

//
// MessageId: WU_E_DS_DUPLICATEUPDATEID
//
// MessageText:
//
//  the server has passed the same update to the client with two different 
//  revision ids.
//
#define WU_E_DS_DUPLICATEUPDATEID        0x80248013L

//
// MessageId: WU_E_DS_UNKNOWNSERVICE
//
// MessageText:
//
//  the caller has requested some action on a service that is not known to 
//  the datastore
//
#define WU_E_DS_UNKNOWNSERVICE           0x80248014L

//
// MessageId: WU_E_DS_SERVICEEXPIRED
//
// MessageText:
//
//  the caller has requested a service whose registration has expired
//
#define WU_E_DS_SERVICEEXPIRED           0x80248015L

//
// MessageId: WU_E_DS_DECLINENOTALLOWED
//
// MessageText:
//
//  an update cannot be declined while it is deployed with a deadline by 1 
//  or more services or if it is a mandatory update
//
#define WU_E_DS_DECLINENOTALLOWED        0x80248016L

//
// MessageId: WU_E_DS_TABLESESSIONMISMATCH
//
// MessageText:
//
//  the caller atteped to close a table with a session it was not associated with
//
#define WU_E_DS_TABLESESSIONMISMATCH     0x80248017L

//
// MessageId: WU_E_DS_SESSIONLOCKMISMATCH
//
// MessageText:
//
//  the caller atteped to close a table with a session it was not associated
//  with
//
#define WU_E_DS_SESSIONLOCKMISMATCH      0x80248018L

//
// MessageId: WU_E_DS_NEEDWINDOWSSERVICE
//
// MessageText:
//
//  the caller attempted to remove the windows update service without having
//  another service configured that delivers updates to windows
//
#define WU_E_DS_NEEDWINDOWSSERVICE       0x80248019L

//
// MessageId: WU_E_DS_INVALIDOPERATION
//
// MessageText:
//
//  The attempted operation was not allowed
//
#define WU_E_DS_INVALIDOPERATION         0x8024801AL

//
// MessageId: WU_E_DS_SCHEMAMISMATCH
//
// MessageText:
//
//  The schema of a table in a backup XML file cannot be reconciled with the current store schema
//
#define WU_E_DS_SCHEMAMISMATCH           0x8024801BL

//
// MessageId: WU_E_DS_RESETREQUIRED
//
// MessageText:
//
//  The datastore required a reset and either the state of the current session
//  was too complex to retry (it is in a caller initiated transaction or a 
//  caller acquired a section lock) or the reset failed.  In either case, the
//  only option is to release the session and try again with a newly acquired
//  session.  Once a session returns this error, it will always return this
//  error.
//
#define WU_E_DS_RESETREQUIRED            0x8024801CL

//
// MessageId: WU_E_DS_IMPERSONATED
//
// MessageText:
//
//  The datastore cannot be called while impersonating
//
#define WU_E_DS_IMPERSONATED             0x8024801DL

//
// MessageId: WU_E_DS_UNEXPECTED
//
// MessageText:
//
//  generic unexpected data store failure
//
#define WU_E_DS_UNEXPECTED               0x80248FFFL

/////////////////////////////////////////////////////////////////////////////
//AU Errors
/////////////////////////////////////////////////////////////////////////////
//
// MessageId: WU_E_AU_NOSERVICE
//
// MessageText:
//
//  AU was unable to service incoming AU calls
//
#define WU_E_AU_NOSERVICE                0x8024A000L

//
// MessageId: WU_E_AU_NONLEGACYSERVER
//
// MessageText:
//
//  The legacy AU client stopped because the sus server has been upgraded
//
#define WU_E_AU_NONLEGACYSERVER          0x8024A002L

//
// MessageId: WU_E_AU_LEGACYCLIENTDISABLED
//
// MessageText:
//
//  The legacy AU client stopped because it was disabled
//
#define WU_E_AU_LEGACYCLIENTDISABLED     0x8024A003L

//
// MessageId: WU_E_AU_PAUSED
//
// MessageText:
//
//  AU was unable to service incoming AU calls because it was paused
//
#define WU_E_AU_PAUSED                   0x8024A004L

//
// MessageId: WU_E_AU_UNEXPECTED
//
// MessageText:
//
//  generic unexpected Automatic Updates
//
#define WU_E_AU_UNEXPECTED               0x8024AFFFL

//////////////////////////////////////////////////////////////////////////////
// update handler errors
///////////////////////////////////////////////////////////////////////////////
//
// MessageId: WU_E_UH_REMOTEUNAVAILABLE
//
// MessageText:
//
//  The caller requested a remote object, but no remote process is available
//
#define WU_E_UH_REMOTEUNAVAILABLE        0x80242000L

//
// MessageId: WU_E_UH_LOCALONLY
//
// MessageText:
//
//  The caller requested a remote object, but the specified handler is local only
//
#define WU_E_UH_LOCALONLY                0x80242001L

//
// MessageId: WU_E_UH_UNKNOWNHANDLER
//
// MessageText:
//
//  The caller requested an unknown handler object
//
#define WU_E_UH_UNKNOWNHANDLER           0x80242002L

//
// MessageId: WU_E_UH_REMOTEALREADYACTIVE
//
// MessageText:
//
//  The caller requested an unknown handler object
//
#define WU_E_UH_REMOTEALREADYACTIVE      0x80242003L

//
// MessageId: WU_E_UH_DOESNOTSUPPORTACTION
//
// MessageText:
//
//  The update does not support the current action (install or uninstall)
//
#define WU_E_UH_DOESNOTSUPPORTACTION     0x80242004L

//
// MessageId: WU_E_UH_WRONGHANDLER
//
// MessageText:
//
//  The caller tried to use the wrong handler for an action
//
#define WU_E_UH_WRONGHANDLER             0x80242005L

//
// MessageId: WU_E_UH_INVALIDMETADATA
//
// MessageText:
//
//  The caller passed an update with invalid metadata to the handler
//
#define WU_E_UH_INVALIDMETADATA          0x80242006L

//
// MessageId: WU_E_UH_INSTALLERHUNG
//
// MessageText:
//
//  The installer took too long and was terminated
//
#define WU_E_UH_INSTALLERHUNG            0x80242007L

//
// MessageId: WU_E_UH_OPERATIONCANCELLED
//
// MessageText:
//
//  The install was canceled via a handler method (as opposed to, for example,
//  an installer running with UI that was cancelled externally to SUS)
//
#define WU_E_UH_OPERATIONCANCELLED       0x80242008L

//
// MessageId: WU_E_UH_BADHANDLERXML
//
// MessageText:
//
//  The XML contained in the handler specific data for the update is invalid.
//
#define WU_E_UH_BADHANDLERXML            0x80242009L

//
// MessageId: WU_E_UH_CANREQUIREINPUT
//
// MessageText:
//
//  The update may require user input so can not be installed in this context.
//
#define WU_E_UH_CANREQUIREINPUT          0x8024200AL

//
// MessageId: WU_E_UH_INSTALLERFAILURE
//
// MessageText:
//
//  At least one update passed to the handler failed to install.
//
#define WU_E_UH_INSTALLERFAILURE         0x8024200BL

//
// MessageId: WU_E_UH_FALLBACKTOSELFCONTAINED
//
// MessageText:
//
//  Handler should fall back to self-contained from delta.
//
#define WU_E_UH_FALLBACKTOSELFCONTAINED  0x8024200CL

//
// MessageId: WU_E_UH_NEEDANOTHERDOWNLOAD
//
// MessageText:
//
//  The installer requires more data to be downloaded
//
#define WU_E_UH_NEEDANOTHERDOWNLOAD      0x8024200DL

//
// MessageId: WU_E_UH_NOTIFYFAILURE
//
// MessageText:
//
//  The attempted operation was not allowed
//
#define WU_E_UH_NOTIFYFAILURE            0x8024200EL

//
// MessageId: WU_E_UH_UNEXPECTED
//
// MessageText:
//
//  generic unexpected update handler failure
//
#define WU_E_UH_UNEXPECTED               0x80242FFFL

//////////////////////////////////////////////////////////////////////////////
// download manager errors
///////////////////////////////////////////////////////////////////////////////
//
// MessageId: WU_E_DM_URLNOTAVAILABLE
//
// MessageText:
//
//  The requested file does not have an URL
//
#define WU_E_DM_URLNOTAVAILABLE          0x80246001L

//
// MessageId: WU_E_DM_INCORRECTFILEHASH
//
// MessageText:
//
//  The file digest did not match the expected value
//
#define WU_E_DM_INCORRECTFILEHASH        0x80246002L

//
// MessageId: WU_E_DM_UNKNOWNALGORITHM
//
// MessageText:
//
//  The file metadata requested an unknown hash algorithm
//
#define WU_E_DM_UNKNOWNALGORITHM         0x80246003L

//
// MessageId: WU_E_DM_NEEDDOWNLOADREQUEST
//
// MessageText:
//
//  A download request from a download handler is required.
//
#define WU_E_DM_NEEDDOWNLOADREQUEST      0x80246004L

//
// MessageId: WU_E_DM_NONETWORK
//
// MessageText:
//
//  Network connection was not available
//
#define WU_E_DM_NONETWORK                0x80246005L

//
// MessageId: WU_E_DM_WRONGBITSVERSION
//
// MessageText:
//
//  The version of BITS installed on the machine is not compatible.
//
#define WU_E_DM_WRONGBITSVERSION         0x80246006L

//
// MessageId: WU_E_DM_NOTDOWNLOADED
//
// MessageText:
//
//  The update has not been downloaded.
//
#define WU_E_DM_NOTDOWNLOADED            0x80246007L

//
// MessageId: WU_E_DM_FAILTOCONNECTTOBITS
//
// MessageText:
//
//  Failed to create the IBackgroundCopyManager interface to BITS. The BITS
//  service may have been disabled.
//
#define WU_E_DM_FAILTOCONNECTTOBITS      0x80246008L

//
// MessageId: WU_E_DM_BITSTRANSFERERROR
//
// MessageText:
//
//  A BITS transfer error occurred, but the exact error could not be retrieved.
//
#define WU_E_DM_BITSTRANSFERERROR        0x80246009L

//
// MessageId: WU_E_DM_UNEXPECTED
//
// MessageText:
//
//  generic unexpected download manager failure
//
#define WU_E_DM_UNEXPECTED               0x80246FFFL

//////////////////////////////////////////////////////////////////////////////
// Setup/SelfUpdate errors
///////////////////////////////////////////////////////////////////////////////
//
// MessageId: WU_E_SETUP_INVALID_INFDATA
//
// MessageText:
//
//  Setup failed due to invalid data in the INF file.
//
#define WU_E_SETUP_INVALID_INFDATA       0x8024D001L

//
// MessageId: WU_E_SETUP_INVALID_IDENTDATA
//
// MessageText:
//
//  Setup failed due to invalid data in the wuident file.
//
#define WU_E_SETUP_INVALID_IDENTDATA     0x8024D002L

//
// MessageId: WU_E_SETUP_ALREADY_INITIALIZED
//
// MessageText:
//
//  Setup failed due to multiple initialization.
//
#define WU_E_SETUP_ALREADY_INITIALIZED   0x8024D003L

//
// MessageId: WU_E_SETUP_NOT_INITIALIZED
//
// MessageText:
//
//  Setup has not been initialized correctly.
//
#define WU_E_SETUP_NOT_INITIALIZED       0x8024D004L

//
// MessageId: WU_E_SETUP_SOURCE_VERSION_MISMATCH
//
// MessageText:
//
//  Setup failed as the version specified in the INF file doesn't match the source binary version.
//
#define WU_E_SETUP_SOURCE_VERSION_MISMATCH 0x8024D005L

//
// MessageId: WU_E_SETUP_TARGET_VERSION_GREATER
//
// MessageText:
//
//  Setup failed as the target version on the system is higher than source binary version.
//
#define WU_E_SETUP_TARGET_VERSION_GREATER 0x8024D006L

//
// MessageId: WU_E_SETUP_REGISTRATION_FAILED
//
// MessageText:
//
//  Regsvr32 for client dll during setup failed.
//
#define WU_E_SETUP_REGISTRATION_FAILED   0x8024D007L

//
// MessageId: WU_E_SETUP_UNEXPECTED
//
// MessageText:
//
//  Generic unexpected Setup failure.
//
#define WU_E_SETUP_UNEXPECTED            0x8024DFFFL

//////////////////////////////////////////////////////////////////////////////
// expression evaluator errors
///////////////////////////////////////////////////////////////////////////////
//
// MessageId: WU_E_EE_UNKNOWN_EXPRESSION
//
// MessageText:
//
//  an expression handler was passed an expression that it doesn't know about
//
#define WU_E_EE_UNKNOWN_EXPRESSION       0x8024E001L

//
// MessageId: WU_E_EE_INVALID_EXPRESSION
//
// MessageText:
//
//  an expression handler was passed an expression that is bad.
//
#define WU_E_EE_INVALID_EXPRESSION       0x8024E002L

//
// MessageId: WU_E_EE_MISSING_METADATA
//
// MessageText:
//
//  an expression handler was passed an expression that requires an applicability
//  metadata blob, but did not receive one or received too many.
//
#define WU_E_EE_MISSING_METADATA         0x8024E003L

//
// MessageId: WU_E_EE_INVALID_VERSION
//
// MessageText:
//
//  Invalid version of the serialized expression data.
//
#define WU_E_EE_INVALID_VERSION          0x8024E004L

//
// MessageId: WU_E_EE_NOT_INITIALIZED
//
// MessageText:
//
//  The Expression Evaluator has not been initialized correctly.
//
#define WU_E_EE_NOT_INITIALIZED          0x8024E005L

//
// MessageId: WU_E_EE_INVALID_ATTRIBUTEDATA
//
// MessageText:
//
//  An invalid attribute data was passed to an expression evaluator.
//
#define WU_E_EE_INVALID_ATTRIBUTEDATA    0x8024E006L

//
// MessageId: WU_E_EE_UNEXPECTED
//
// MessageText:
//
//  generic unexpected expression evaluator failures
//
#define WU_E_EE_UNEXPECTED               0x8024EFFFL

//////////////////////////////////////////////////////////////////////////////
// UI errors
///////////////////////////////////////////////////////////////////////////////
//
// MessageId: WU_E_AUCLIENT_UNEXPECTED
//
// MessageText:
//
//  generic unexpected UI [AU Client] failures
//
#define WU_E_AUCLIENT_UNEXPECTED         0x80243FFFL

//////////////////////////////////////////////////////////////////////////////
// reporter errors
///////////////////////////////////////////////////////////////////////////////
//
// MessageId: WU_E_REPORTER_EVENTCACHECORRUPT
//
// MessageText:
//
//  event cache file was corrupt/malformed
//
#define WU_E_REPORTER_EVENTCACHECORRUPT  0x8024F001L

//
// MessageId: WU_E_REPORTER_EVENTNAMESPACEPARSEFAILED
//
// MessageText:
//
//  event namespace descriptor XML could not be parsed
//
#define WU_E_REPORTER_EVENTNAMESPACEPARSEFAILED 0x8024F002L

//
// MessageId: WU_E_INVALID_EVENT
//
// MessageText:
//
//  event was reported with invalid/malformed data
//
#define WU_E_INVALID_EVENT               0x8024F003L

//
// MessageId: WU_E_SERVER_BUSY
//
// MessageText:
//
//  event was rejected by server because server was too busy
//
#define WU_E_SERVER_BUSY                 0x8024F004L

//
// MessageId: WU_E_REPORTER_UNEXPECTED
//
// MessageText:
//
//  generic unexpected reporter failures
//
#define WU_E_REPORTER_UNEXPECTED         0x8024FFFFL

//
// MessageId: WU_E_OL_INVALID_SCANFILE
//
// MessageText:
//
//  Scan file specified is invalid
//
#define WU_E_OL_INVALID_SCANFILE         0x80247001L

//
// MessageId: WU_E_OL_NEWCLIENT_REQUIRED
//
// MessageText:
//
//  Scan file specified requires a newer version of WUS client agent
//
#define WU_E_OL_NEWCLIENT_REQUIRED       0x80247002L

//
// MessageId: WU_E_OL_UNEXPECTED
//
// MessageText:
//
//  generic unexpected offline sync failures
//
#define WU_E_OL_UNEXPECTED               0x80247FFFL

#endif //_WUERROR_
