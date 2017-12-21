
#pragma once


// CAccount ÃüÁîÄ¿±ê

class CAccount : public CCmdTarget
{
	DECLARE_DYNCREATE(CAccount)

public:
	CAccount();
	virtual ~CAccount();

	virtual void OnFinalRelease();

	//inline afx_msg long GetBalance() { return m_nBalance; }
	//inline afx_msg void SetBalance(long l) { m_nBalance = l; }

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CAccount)
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

private:
	long m_balance;
public:
	//HRESULT Post2(long lAmount/*, LPBSTR pResult*/);
protected:
	LONG GetBalance();
	void SetBalance(LONG newVal);

	enum
	{
		dispidPost = 2L,
		dispidBalance = 1
	};
	BSTR Post(LONG lAmount);
};


