#pragma once
#include "UICfg.h"

// CMyListCtrl1
struct stDeviceInfo;

class CMyListCtrl1 : public CListCtrl, public CUICfg
{
	DECLARE_DYNAMIC(CMyListCtrl1)

public:
	CMyListCtrl1();
	virtual ~CMyListCtrl1();
	
	void FillItem(const std::vector<std::shared_ptr<stDeviceInfo>>& );



protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
};


