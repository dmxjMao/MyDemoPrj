// MyListCtrl1.cpp : 实现文件
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
			"(head):(.*)"//表头，英文逗号分隔，如：姓名,年龄...
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



// CMyListCtrl1 消息处理程序




void CMyListCtrl1::PreSubclassWindow()
{
	ModifyStyle(0, LVS_REPORT | LVS_OWNERDRAWFIXED | LVS_SHOWSELALWAYS);
	ModifyStyleEx(0, LVS_EX_FULLROWSELECT
		| LVS_EX_DOUBLEBUFFER | LVS_EX_HEADERDRAGDROP
		| LVS_EX_COLUMNSNAPPOINTS //resize只能到最小宽度
		| LVS_EX_ONECLICKACTIVATE);

	__super::PreSubclassWindow();
}



void CMyListCtrl1::FillItem(const vector<shared_ptr<stDeviceInfo>>& vecItem)
{
	
	//获取表头文字
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

	//列宽
	vector<int> vecWidth(nItemCnt, rcClient.Width() / nItemCnt);
	
	//列
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