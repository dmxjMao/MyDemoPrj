// MyListCtrl1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OwnDraw.h"
#include "MyListCtrl1.h"
#include "MyCommonDefine.h"

using std::vector;
using std::string;
using std::shared_ptr;
using std::make_shared;

// CMyListCtrl1

IMPLEMENT_DYNAMIC(CMyListCtrl1, CListCtrl)

CMyListCtrl1::CMyListCtrl1()
{
	try {
		m_regex.assign(
			"(?|"
			"(head):(.*)"//��ͷ��Ӣ�Ķ��ŷָ����磺����,����...
			")"
			, boost::regex_constants::icase);
	}
	catch (boost::regex_error e) {
		//theApp.WriteLog
	}
	m_cfg["head"] = "";
}

CMyListCtrl1::~CMyListCtrl1()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl1, CListCtrl)
END_MESSAGE_MAP()



// CMyListCtrl1 ��Ϣ�������




void CMyListCtrl1::PreSubclassWindow()
{
	ModifyStyle(0, LVS_REPORT | LVS_OWNERDRAWFIXED | LVS_SHOWSELALWAYS);
	ModifyStyleEx(0, LVS_EX_FULLROWSELECT
		| LVS_EX_DOUBLEBUFFER | LVS_EX_HEADERDRAGDROP
		| LVS_EX_COLUMNSNAPPOINTS //resizeֻ�ܵ���С���
		| LVS_EX_ONECLICKACTIVATE);

	__super::PreSubclassWindow();
}



void CMyListCtrl1::FillItem(const vector<shared_ptr<stDeviceInfo>>& vecItem)
{
	
	//��ȡ��ͷ����
	vector<CString> vecCStr;
	auto& str = m_cfg["head"];
	vector<string> vecStr;
	SplitString(str, ',', vecStr);

	for (int i = 0; i < (int)vecStr.size(); ++i) {
		CA2T sz(vecStr[i].c_str());
		vecCStr.emplace_back(sz);
	}

	SetRedraw(FALSE);

	CRect rcClient;
	GetClientRect(&rcClient);
	int nItemCnt = vecCStr.size();

	//�п�
	vector<int> vecWidth(nItemCnt, rcClient.Width() / nItemCnt);
	
	//��
	//CHeaderCtrl* pHeader = GetHeaderCtrl();
	LVCOLUMN lvCol;
	lvCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM | LVCF_MINWIDTH;
	for (int i = 0; i < nItemCnt; ++i) {
		CString& str = vecCStr[i];

		lvCol.pszText = str.GetBuffer();
		lvCol.cchTextMax = str.GetLength();
		lvCol.iSubItem = i;
		lvCol.cxMin = 2 * GetStringWidth(str);
		lvCol.cx = vecWidth[i];

		InsertColumn(i, &lvCol);
	}


}