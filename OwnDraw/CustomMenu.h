#pragma once

//enum emMenuItemType {
//	Separater,//�ָ���
//	MenuItem,//�˵���
//};

struct stMenuItem {
	CString strItem;//�ı�
	int nIdx;//�˵�������
	int nID;//�˵���id��0����ָ���
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
	//���ָ���
	void DrawSeparater(CDC* pDC, CRect rcItem);
	//���ı�
	void DrawItemText(CDC* pDC, const CString& str, CRect rcItem);
	//���߿�
	void DrawComMenu(CDC* pDC, CRect rcItem, bool bSel);
	//��������
	void DrawMenuTitle(CDC* pDC, CRect rcItem, const CString& str);
};