
#pragma once
#include "..\interface\IDictionary.h"
#include "..\interface\ISpellCheck.h"

// CDictionaryObj command target

class CDictionaryObj : public CCmdTarget
{
	DECLARE_DYNAMIC(CDictionaryObj)

	DECLARE_INTERFACE_MAP()
	DECLARE_OLECREATE(CDictionaryObj)
	//BEGIN_INTERFACE_PART(CDictionary, IDictionary)

public:
	CDictionaryObj();
	virtual ~CDictionaryObj();

	//字典接口
	BEGIN_INTERFACE_PART(Dictionary, IDictionary)
		INIT_INTERFACE_PART(CDictionaryObj, Dictionary)
		STDMETHOD_(BOOL, Initialize);
	END_INTERFACE_PART_STATIC(Dictionary)

	//拼写检查接口
	//BEGIN_INTERFACE_PART(SpellCheck, ISpellCheck)
	//	INIT_INTERFACE_PART(CDictionaryObj, SpellCheck)
	//	STDMETHOD_(BOOL, CheckWord)(LPOLESTR, LPOLESTR*);
	//END_INTERFACE_PART_STATIC(SpellCheck)

protected:
	DECLARE_MESSAGE_MAP()
};


