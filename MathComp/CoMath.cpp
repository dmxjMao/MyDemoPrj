// CoMath.cpp : implementation file
//

#include "stdafx.h"
#include "MathComp.h"
#include "CoMath.h"


// CoMath
// {131EE8B3-E2A5-4624-A8DC-4A91A5C9F4C0}
extern "C" const IID IID_IMath = { 0x131ee8b3, 0xe2a5, 0x4624,{ 0xa8, 0xdc, 0x4a, 0x91, 0xa5, 0xc9, 0xf4, 0xc0 } };

IMPLEMENT_DYNAMIC(CoMath, CCmdTarget)


CoMath::CoMath()
{
}

CoMath::~CoMath()
{
}


BEGIN_MESSAGE_MAP(CoMath, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_INTERFACE_MAP(CoMath, CCmdTarget)
	INTERFACE_PART(CoMath, IID_IMath, MathObj)
END_INTERFACE_MAP()


// CoMath message handlers




//IMath接口实现
STDMETHODIMP_(ULONG)
CoMath::XMathObj::AddRef() {
	METHOD_PROLOGUE(CoMath, MathObj);
	return pThis->ExternalAddRef();
}


STDMETHODIMP_(ULONG)
CoMath::XMathObj::Release() {
	METHOD_PROLOGUE(CoMath, MathObj);
	return pThis->ExternalRelease();
}

STDMETHODIMP
CoMath::XMathObj::QueryInterface(REFIID riid,LPVOID* ppv) {
	METHOD_PROLOGUE(CoMath, MathObj);
	return pThis->ExternalQueryInterface(&riid, ppv);
}


STDMETHODIMP
CoMath::XMathObj::Add(int a, int b, long& r) {
	r = a + b;
	return S_OK;
}

STDMETHODIMP
CoMath::XMathObj::Subtract(int a, int b, int& r) {
	r = a - b;
	return S_OK;
}