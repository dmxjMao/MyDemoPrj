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
		if (0 == lpDS->itemData) //lpDS->itemData����˵������������
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
			//DrawMenuTitle(pDC, rc, _T("��Ծ�Ƽ����޹�˾"));
			break;
		}
	}
}



//���ָ���
void CMyMenu1::DrawSeparater(CDC* pDC, CRect rcItem)
{
	//CDC����const��Graphic�����鷳��rcItem��������
	rcItem.DeflateRect(29, 0, 0, 0);
	pDC->Draw3dRect(rcItem, RGB(0, 0, 255), RGB(0, 255, 0));
}


//���ı�
void CMyMenu1::DrawItemText(CDC* pDC, const CString& str, CRect rcItem)
{
	rcItem.DeflateRect(40, 0, 0, 0);
	pDC->DrawText(str, rcItem, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
}

//���߿�
void CMyMenu1::DrawComMenu(CDC* pDC, CRect rcItem, bool bSel)
{
	//Graphics gh(pDC->m_hDC);

	CBrush *brush = new CBrush;
	CPen *pen = new CPen;
	CString strText;
	//CDC *pDC = CDC::FromHandle(lpdis->hDC); //��ȡ�˵�����豸���   
	//�˵����Ƿ�Ϊѡ��״̬   
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
	//�ڵ�ǰ�˵����ϻ�һ�����ο�   
	pDC->Rectangle(rcItem.left,
		rcItem.top,
		rcItem.right,
		rcItem.bottom);
	/*--------------------------------------*/
	//��ȡ��ǰ��Ϣ���ڲ˵�����ı�   
	//CMenu menu;
	//menu.Attach((HMENU)lpdis->hwndItem);
	//menu.GetMenuString(lpdis->itemID, strText, MF_BYCOMMAND);

	/*--------------------------------------*/
	//���Ϊ�˵�������DrawItem��Ϣ   
	//if (nIDCtl == 0)
	//{
	//	//�ڲ˵���������˵��ı�   
	//	pDC->TextOutW(lpdis->rcItem.left + 20, lpdis->rcItem.top + 4, strText.GetBuffer(0), strText.GetLength());
	//}
	//menu.Detach();
	delete brush;
	delete pen;
}

//��������
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
			//ÿ�εݹ�idx��0��ʼ������m_vecMenuItems����ʱ�õ�
			//������OnInitDialog�У���m_vecMenuItems�ڹ�����
			stMenuItem& st = m_vecMenuItems[idx];

			//��ȡ�˵����ı����˵�id
			pMenu->GetMenuString(i, st.strItem, MF_BYPOSITION);
			st.nID = pMenu->GetMenuItemID(i);

			//����Ƕ���˵����˵�id = -1���ָ���id = 0
			if (st.nID > 0) {
				st.nIdx = m_ImageIndex++;
			}
			//UIDNewltem�˵�id��MF_POPUPʱָ���Ӳ˵����
			//MF_OWNERDRAW st�����ػ�ʱ��itemData
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