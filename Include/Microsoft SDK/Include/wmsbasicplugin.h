

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* Compiler settings for wmsbasicplugin.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __wmsbasicplugin_h__
#define __wmsbasicplugin_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWMSBasicPlugin_FWD_DEFINED__
#define __IWMSBasicPlugin_FWD_DEFINED__
typedef interface IWMSBasicPlugin IWMSBasicPlugin;
#endif 	/* __IWMSBasicPlugin_FWD_DEFINED__ */


/* header files for imported files */
#include "WMSNamedValues.h"
#include "nsscore.h"
#include "WMSEventLog.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_wmsbasicplugin_0000 */
/* [local] */ 

//*****************************************************************************
//
// Microsoft Windows Media
// Copyright (C) Microsoft Corporation. All rights reserved.
//
// Automatically generated by Midl from WMSBasicPlugin.idl
//
// DO NOT EDIT THIS FILE.
//
//*****************************************************************************
EXTERN_GUID( IID_IWMSBasicPlugin, 0x66E6CE48,0xF8BB,0x4bcc,0x8F,0xD6,0x42,0xA9,0xD5,0xD3,0x28,0x71 );


extern RPC_IF_HANDLE __MIDL_itf_wmsbasicplugin_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_wmsbasicplugin_0000_v0_0_s_ifspec;

#ifndef __IWMSBasicPlugin_INTERFACE_DEFINED__
#define __IWMSBasicPlugin_INTERFACE_DEFINED__

/* interface IWMSBasicPlugin */
/* [unique][version][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IWMSBasicPlugin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("66E6CE48-F8BB-4bcc-8FD6-42A9D5D32871")
    IWMSBasicPlugin : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InitializePlugin( 
            /* [in] */ IWMSContext *pServerContext,
            /* [in] */ IWMSNamedValues *pNamedValues,
            /* [in] */ IWMSClassObject *pClassFactory) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnHeartbeat( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCustomAdminInterface( 
            /* [retval][out] */ IDispatch **ppValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ShutdownPlugin( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnablePlugin( 
            /* [out][in] */ long *plFlags,
            /* [out][in] */ long *plHeartbeatPeriod) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DisablePlugin( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMSBasicPluginVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMSBasicPlugin * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMSBasicPlugin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMSBasicPlugin * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InitializePlugin )( 
            IWMSBasicPlugin * This,
            /* [in] */ IWMSContext *pServerContext,
            /* [in] */ IWMSNamedValues *pNamedValues,
            /* [in] */ IWMSClassObject *pClassFactory);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnHeartbeat )( 
            IWMSBasicPlugin * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCustomAdminInterface )( 
            IWMSBasicPlugin * This,
            /* [retval][out] */ IDispatch **ppValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ShutdownPlugin )( 
            IWMSBasicPlugin * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnablePlugin )( 
            IWMSBasicPlugin * This,
            /* [out][in] */ long *plFlags,
            /* [out][in] */ long *plHeartbeatPeriod);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DisablePlugin )( 
            IWMSBasicPlugin * This);
        
        END_INTERFACE
    } IWMSBasicPluginVtbl;

    interface IWMSBasicPlugin
    {
        CONST_VTBL struct IWMSBasicPluginVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMSBasicPlugin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMSBasicPlugin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMSBasicPlugin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMSBasicPlugin_InitializePlugin(This,pServerContext,pNamedValues,pClassFactory)	\
    (This)->lpVtbl -> InitializePlugin(This,pServerContext,pNamedValues,pClassFactory)

#define IWMSBasicPlugin_OnHeartbeat(This)	\
    (This)->lpVtbl -> OnHeartbeat(This)

#define IWMSBasicPlugin_GetCustomAdminInterface(This,ppValue)	\
    (This)->lpVtbl -> GetCustomAdminInterface(This,ppValue)

#define IWMSBasicPlugin_ShutdownPlugin(This)	\
    (This)->lpVtbl -> ShutdownPlugin(This)

#define IWMSBasicPlugin_EnablePlugin(This,plFlags,plHeartbeatPeriod)	\
    (This)->lpVtbl -> EnablePlugin(This,plFlags,plHeartbeatPeriod)

#define IWMSBasicPlugin_DisablePlugin(This)	\
    (This)->lpVtbl -> DisablePlugin(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWMSBasicPlugin_InitializePlugin_Proxy( 
    IWMSBasicPlugin * This,
    /* [in] */ IWMSContext *pServerContext,
    /* [in] */ IWMSNamedValues *pNamedValues,
    /* [in] */ IWMSClassObject *pClassFactory);


void __RPC_STUB IWMSBasicPlugin_InitializePlugin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWMSBasicPlugin_OnHeartbeat_Proxy( 
    IWMSBasicPlugin * This);


void __RPC_STUB IWMSBasicPlugin_OnHeartbeat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWMSBasicPlugin_GetCustomAdminInterface_Proxy( 
    IWMSBasicPlugin * This,
    /* [retval][out] */ IDispatch **ppValue);


void __RPC_STUB IWMSBasicPlugin_GetCustomAdminInterface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWMSBasicPlugin_ShutdownPlugin_Proxy( 
    IWMSBasicPlugin * This);


void __RPC_STUB IWMSBasicPlugin_ShutdownPlugin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWMSBasicPlugin_EnablePlugin_Proxy( 
    IWMSBasicPlugin * This,
    /* [out][in] */ long *plFlags,
    /* [out][in] */ long *plHeartbeatPeriod);


void __RPC_STUB IWMSBasicPlugin_EnablePlugin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IWMSBasicPlugin_DisablePlugin_Proxy( 
    IWMSBasicPlugin * This);


void __RPC_STUB IWMSBasicPlugin_DisablePlugin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMSBasicPlugin_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


