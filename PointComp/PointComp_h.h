

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sat Oct 28 16:59:52 2017
 */
/* Compiler settings for PointComp.idl:
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


#ifndef __PointComp_h_h__
#define __PointComp_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPointObj_FWD_DEFINED__
#define __IPointObj_FWD_DEFINED__
typedef interface IPointObj IPointObj;

#endif 	/* __IPointObj_FWD_DEFINED__ */


#ifndef __PointObj_FWD_DEFINED__
#define __PointObj_FWD_DEFINED__

#ifdef __cplusplus
typedef class PointObj PointObj;
#else
typedef struct PointObj PointObj;
#endif /* __cplusplus */

#endif 	/* __PointObj_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __PointComp_LIBRARY_DEFINED__
#define __PointComp_LIBRARY_DEFINED__

/* library PointComp */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_PointComp;

#ifndef __IPointObj_DISPINTERFACE_DEFINED__
#define __IPointObj_DISPINTERFACE_DEFINED__

/* dispinterface IPointObj */
/* [uuid] */ 


EXTERN_C const IID DIID_IPointObj;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("1716B8DF-6E8B-4567-A0C5-50FA64C6E8D2")
    IPointObj : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IPointObjVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPointObj * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPointObj * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPointObj * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPointObj * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPointObj * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPointObj * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPointObj * This,
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
    } IPointObjVtbl;

    interface IPointObj
    {
        CONST_VTBL struct IPointObjVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPointObj_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPointObj_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPointObj_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPointObj_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPointObj_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPointObj_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPointObj_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IPointObj_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PointObj;

#ifdef __cplusplus

class DECLSPEC_UUID("B9143056-208E-4DD9-8E76-7A7F0B9A5B1D")
PointObj;
#endif
#endif /* __PointComp_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


