#pragma once
#include "UICfg.h"

// CMyButton1

class CMyButton1 : public CButton, public CUICfg
{
	DECLARE_DYNAMIC(CMyButton1)

public:
	CMyButton1();
	virtual ~CMyButton1();

protected:
	DECLARE_MESSAGE_MAP()
};


