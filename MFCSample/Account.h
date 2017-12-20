
#pragma once


// CAccount ÃüÁîÄ¿±ê

class CAccount : public CCmdTarget
{
	DECLARE_DYNCREATE(CAccount)

public:
	CAccount();
	virtual ~CAccount();

	virtual void OnFinalRelease();

	inline afx_msg long GetBalance() { return m_nBalance; }
	inline afx_msg void SetBalance(long l) { m_nBalance = l; }

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CAccount)
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

private:
	long m_nBalance;
public:
	void Post(long lAmount, LPBSTR pResult);
};


