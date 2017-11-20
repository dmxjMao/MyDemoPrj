#pragma once

//enum emMenuItemType {
//	Separater,//分割条
//	MenuItem,//菜单项
//};

struct stMenuItem {
	CString strItem;//文本
	int nIdx;//菜单项索引
	int nID;//菜单项id，0代表分割条
};



class CMyMenu1 : public CMenu {
	DECLARE_DYNCREATE(CMyMenu1)

public:
	CMyMenu1();

protected:
	std::vector<stMenuItem> m_vecMenuItems;
	int m_ImageIndex = 0;

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);
	BOOL ChangeMenuItem(CMenu* pMenu);

protected:
	//画分割条
	void DrawSeparater(CDC* pDC, CRect rcItem);
	//画文本
	void DrawItemText(CDC* pDC, const CString& str, CRect rcItem);
	//画边框
	void DrawComMenu(CDC* pDC, CRect rcItem, bool bSel);
	//画左侧标题
	void DrawMenuTitle(CDC* pDC, CRect rcItem, const CString& str);
};