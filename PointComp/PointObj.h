
#pragma once


// CPointObj command target

class CPointObj : public CCmdTarget
{
	DECLARE_DYNAMIC(CPointObj)

public:
	CPointObj();
	virtual ~CPointObj();

	virtual void OnFinalRelease();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

public:
	long x;
	void MoveTo(long xDest, long yDest);
};


