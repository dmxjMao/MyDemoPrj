#pragma once

#include <Unknwn.h>

__interface IMath : IUnknown
{
	STDMETHOD(Add)(int, int, long&) = 0;
	//virtual HRESULT Add(int, int, long&) = 0;
	//virtual HRESULT Subtract(int, int, int&) = 0;
	STDMETHOD(Subtract)(int, int, int&) = 0;
};

