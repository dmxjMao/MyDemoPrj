
#pragma once


// CAccountExe ÃüÁîÄ¿±ê

class CAccountExe : public CCmdTarget
{
	DECLARE_DYNCREATE(CAccountExe)

public:
	CAccountExe();
	virtual ~CAccountExe();

	virtual void OnFinalRelease();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CAccountExe)
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};


