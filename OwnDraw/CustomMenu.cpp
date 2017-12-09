#include "stdafx.h"
#include "CustomMenu.h"

using std::shared_ptr;
using std::string;

IMPLEMENT_DYNCREATE(CMyMenu1,CMenu)

CMyMenu1::CMyMenu1()
{
	//int nCnt = 10;
	//m_vecMenuItems.resize(nCnt);
	//for (auto& sp : m_vecMenuItems) {
	//	sp = std::make_shared<stMenuItem>();
	//}
}

void CMyMenu1::MeasureItem(LPMEASUREITEMSTRUCT lpMS)
{
	if (ODT_MENU == lpMS->CtlType) {
		lpMS->itemHeight = 22;
		lpMS->itemWidth = 100;
		
		auto& spItem = *(shared_ptr<stMenuItem>*)(lpMS->itemData);
		if (0 == spItem->nID) {
			lpMS->itemHeight = 1;
		}
	}
}

void CMyMenu1::DrawItem(LPDRAWITEMSTRUCT lpDS)
{
	if (ODT_MENU == lpDS->CtlType) {
		if (0 == lpDS->itemData) //lpDS->itemData是与菜单项关联的数据
			return;

		auto& spItem = *(shared_ptr<stMenuItem>*)(lpDS->itemData);
		UINT state = lpDS->itemState;
		CRect rc = lpDS->rcItem;

		//Graphics gh(lpDS->hDC);
		CDC* pDC = CDC::FromHandle(lpDS->hDC);
		switch (spItem->nID)
		{
		case 0:
			DrawSeparater(pDC, lpDS->rcItem);
			break;
		default:
			DrawComMenu(pDC, lpDS->rcItem, state & ODS_SELECTED);
			DrawItemText(pDC, spItem->strItem, rc);
			//DrawMenuTitle(pDC, rc, _T("天跃科技有限公司"));
			break;
		}
	}
}



//画分割条
void CMyMenu1::DrawSeparater(CDC* pDC, CRect rcItem)
{
	//CDC不能const，Graphic反而麻烦，rcItem不能引用
	rcItem.DeflateRect(29, 0, 0, 0);
	pDC->Draw3dRect(rcItem, RGB(0, 0, 255), RGB(0, 255, 0));
}


//画文本
void CMyMenu1::DrawItemText(CDC* pDC, const CString& str, CRect rcItem)
{
	rcItem.DeflateRect(40, 0, 0, 0);
	pDC->DrawText(str, rcItem, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
}

//画边框
void CMyMenu1::DrawComMenu(CDC* pDC, CRect rcItem, bool bSel)
{
	//Graphics gh(pDC->m_hDC);

	CBrush *brush = new CBrush;
	CPen *pen = new CPen;
	CString strText;
	//CDC *pDC = CDC::FromHandle(lpdis->hDC); //获取菜单项的设备句柄   
	//菜单项是否为选中状态   
	if (bSel) {
		brush->CreateSolidBrush(RGB(182, 189, 210));
		pen->CreatePen(PS_SOLID, 1, RGB(10, 36, 106)); 
		pDC->SetBkColor(RGB(182, 189, 210));
	}
	else {
		brush->CreateSolidBrush(GetSysColor(COLOR_MENU));
		pen->CreatePen(PS_SOLID, 0, GetSysColor(COLOR_MENU));
		pDC->SetBkColor(GetSysColor(COLOR_MENU));
	}
	pDC->SelectObject(pen);
	pDC->SelectObject(brush);
	//在当前菜单项上画一个矩形框   
	pDC->Rectangle(rcItem.left,
		rcItem.top,
		rcItem.right,
		rcItem.bottom);
	/*--------------------------------------*/
	//获取当前消息所在菜单项的文本   
	//CMenu menu;
	//menu.Attach((HMENU)lpdis->hwndItem);
	//menu.GetMenuString(lpdis->itemID, strText, MF_BYCOMMAND);

	/*--------------------------------------*/
	//如果为菜单发出的DrawItem消息   
	//if (nIDCtl == 0)
	//{
	//	//在菜单项上输出菜单文本   
	//	pDC->TextOutW(lpdis->rcItem.left + 20, lpdis->rcItem.top + 4, strText.GetBuffer(0), strText.GetLength());
	//}
	//menu.Detach();
	delete brush;
	delete pen;
}

//画左侧标题
void CMyMenu1::DrawMenuTitle(CDC* pDC, CRect rcItem, const CString& str)
{

}


BOOL CMyMenu1::ChangeMenuItem(CMenu* pMenu)
{
	int idx = 0;
	if (pMenu) {
		int nCnt = pMenu->GetMenuItemCount();
		m_vecMenuItems.resize(10);

		for (int i = 0; i < nCnt; ++i) {
			//每次递归idx从0开始，所以m_vecMenuItems是临时用的
			//函数在OnInitDialog中，而m_vecMenuItems在构造中
			stMenuItem& st = m_vecMenuItems[idx];

			//获取菜单项文本、菜单id
			pMenu->GetMenuString(i, st.strItem, MF_BYPOSITION);
			st.nID = pMenu->GetMenuItemID(i);

			//如果是顶层菜单，菜单id = -1，分割条id = 0
			if (st.nID > 0) {
				st.nIdx = m_ImageIndex++;
			}
			//UIDNewltem菜单id或MF_POPUP时指定子菜单句柄
			//MF_OWNERDRAW st就是重绘时的itemData
			pMenu->ModifyMenu(i, MF_OWNERDRAW | MF_BYPOSITION | MF_STRING,
				st.nID, (LPTSTR)&m_vecMenuItems[idx]);
			++idx;

			CMenu* sub = pMenu->GetSubMenu(i);
			if (sub) {
				ChangeMenuItem(sub);
			}
		}
	}
	return TRUE;
}