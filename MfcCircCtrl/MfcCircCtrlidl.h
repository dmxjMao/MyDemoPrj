

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Dec 21 22:55:20 2017
 */
/* Compiler settings for MfcCircCtrl.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

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


#ifndef __MfcCircCtrlidl_h__
#define __MfcCircCtrlidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DMfcCircCtrl_FWD_DEFINED__
#define ___DMfcCircCtrl_FWD_DEFINED__
typedef interface _DMfcCircCtrl _DMfcCircCtrl;

#endif 	/* ___DMfcCircCtrl_FWD_DEFINED__ */


#ifndef ___DMfcCircCtrlEvents_FWD_DEFINED__
#define ___DMfcCircCtrlEvents_FWD_DEFINED__
typedef interface _DMfcCircCtrlEvents _DMfcCircCtrlEvents;

#endif 	/* ___DMfcCircCtrlEvents_FWD_DEFINED__ */


#ifndef __MfcCircCtrl_FWD_DEFINED__
#define __MfcCircCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class MfcCircCtrl MfcCircCtrl;
#else
typedef struct MfcCircCtrl MfcCircCtrl;
#endif /* __cplusplus */

#endif 	/* __MfcCircCtrl_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_MfcCircCtrl_0000_0000 */
/* [local] */ 

#pragma once
#pragma region Desktop Family
#pragma endregion


extern RPC_IF_HANDLE __MIDL_itf_MfcCircCtrl_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_MfcCircCtrl_0000_0000_v0_0_s_ifspec;


#ifndef __MfcCircCtrlLib_LIBRARY_DEFINED__
#define __MfcCircCtrlLib_LIBRARY_DEFINED__

/* library MfcCircCtrlLib */
/* [control][version][uuid] */ 


EXTERN_C const IID LIBID_MfcCircCtrlLib;

#ifndef ___DMfcCircCtrl_DISPINTERFACE_DEFINED__
#define ___DMfcCircCtrl_DISPINTERFACE_DEFINED__

/* dispinterface _DMfcCircCtrl */
/* [uuid] */ 


EXTERN_C const IID DIID__DMfcCircCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("AAC8F54A-B68F-49D9-ADD7-0B85911C6DD5")
    _DMfcCircCtrl : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMfcCircCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMfcCircCtrl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMfcCircCtrl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMfcCircCtrl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMfcCircCtrl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMfcCircCtrl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMfcCircCtrl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMfcCircCtrl * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMfcCircCtrlVtbl;

    interface _DMfcCircCtrl
    {
        CONST_VTBL struct _DMfcCircCtrlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMfcCircCtrl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMfcCircCtrl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMfcCircCtrl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMfcCircCtrl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMfcCircCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMfcCircCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMfcCircCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMfcCircCtrl_DISPINTERFACE_DEFINED__ */


#ifndef ___DMfcCircCtrlEvents_DISPINTERFACE_DEFINED__
#define ___DMfcCircCtrlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DMfcCircCtrlEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__DMfcCircCtrlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("965D2AA7-4EE0-4D3F-B70A-D83BAA354B00")
    _DMfcCircCtrlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMfcCircCtrlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMfcCircCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMfcCircCtrlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMfcCircCtrlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMfcCircCtrlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMfcCircCtrlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMfcCircCtrlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMfcCircCtrlEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DMfcCircCtrlEventsVtbl;

    interface _DMfcCircCtrlEvents
    {
        CONST_VTBL struct _DMfcCircCtrlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMfcCircCtrlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DMfcCircCtrlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DMfcCircCtrlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DMfcCircCtrlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DMfcCircCtrlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DMfcCircCtrlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DMfcCircCtrlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMfcCircCtrlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MfcCircCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("26A29B83-9263-47B4-B6EE-1261BB10FA40")
MfcCircCtrl;
#endif
#endif /* __MfcCircCtrlLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


