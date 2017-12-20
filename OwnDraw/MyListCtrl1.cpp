// MyListCtrl1.cpp : 实现文件
//

#include "stdafx.h"
#include "OwnDraw.h"
#include "MyListCtrl1.h"
#include "MyCommonDefine.h"
#include "ListCtrl_DataModel.h"

namespace {

	using std::vector;
	using std::string;
	using std::shared_ptr;
	using std::make_shared;


	struct PARAMSORT //排序元素
	{
		PARAMSORT(const shared_ptr<CListCtrl_DataModel>& datamodel, int columnData, bool ascending)
			:m_DataModel(datamodel)
			, m_ColumnData(columnData)
			, m_Ascending(ascending)
		{}

		const shared_ptr<CListCtrl_DataModel>& m_DataModel;
		int  m_ColumnData;
		bool m_Ascending;
		CSimpleMap<int, CString> m_GroupNames;

		const CString& LookupGroupName(int nGroupId)
		{
			int groupIdx = m_GroupNames.FindKey(nGroupId);
			if (groupIdx == -1)
			{
				static const CString emptyStr;
				return emptyStr;
			}
			return m_GroupNames.GetValueAt(groupIdx);
		}
	};

	// Comparison extracts values from the DataModel
	int CALLBACK SortFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
	{
		PARAMSORT& ps = *(PARAMSORT*)lParamSort;

		const CString& left = ps.m_DataModel->GetCellText((size_t)lParam1, ps.m_ColumnData);
		const CString& right = ps.m_DataModel->GetCellText((size_t)lParam2, ps.m_ColumnData);

		if (ps.m_Ascending)
			return left < right;
		else
			return right < left;
	}

	int CALLBACK SortFuncGroup(int nLeftId, int nRightId, void* lParamSort)
	{
		PARAMSORT& ps = *(PARAMSORT*)lParamSort;

		const CString& left = ps.LookupGroupName(nLeftId);
		const CString& right = ps.LookupGroupName(nRightId);

		if (ps.m_Ascending)
			return _tcscmp(left, right);
		else
			return _tcscmp(right, left);
	}

	//std algorithm
	struct SortFunc2
	{
		int m_ColumnData;
		bool m_Ascending;

		SortFunc2(int columnData, bool ascending)
			:m_ColumnData(columnData)
			, m_Ascending(ascending)
		{}

		bool operator()(const CListCtrl_DataRecord& left, const CListCtrl_DataRecord& right)
		{
			if (m_Ascending)
				return left.GetCellText(m_ColumnData, false) < right.GetCellText(m_ColumnData, false);
			else
				return right.GetCellText(m_ColumnData, false) < left.GetCellText(m_ColumnData, false);
		}
	};
}


// CMyListCtrl1

IMPLEMENT_DYNAMIC(CMyListCtrl1, CListCtrl)

CMyListCtrl1::CMyListCtrl1()
{
	//try {
	//	m_regex.assign(
	//		"(?|"
	//		")"
	//		, boost::regex_constants::icase);
	//}
	//catch (boost::regex_error e) {
	//	//theApp.WriteLog
	//}
	//m_cfg["head"] = "";

	m_pDataModel = make_shared<CListCtrl_DataModel>();
}

CMyListCtrl1::~CMyListCtrl1()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl1, CListCtrl)
	ON_NOTIFY_REFLECT_EX(LVN_COLUMNCLICK, OnHeaderClick)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY_REFLECT_EX(LVN_GETDISPINFO, OnGetDispInfo)	// Text Callback
	ON_MESSAGE(LVM_INSERTCOLUMN, OnInsertColumn)
	ON_MESSAGE(LVM_DELETECOLUMN, OnDeleteColumn)
END_MESSAGE_MAP()



// CMyListCtrl1 消息处理程序




void CMyListCtrl1::PreSubclassWindow()
{
	//ModifyStyle(0, LVS_REPORT | LVS_OWNERDRAWFIXED | LVS_SHOWSELALWAYS);
	__super::PreSubclassWindow();

	//一定要拖动控件在DDX，否则这些样式都不起作用，LVS_OWNDATA更是要在属性单中指定
	ModifyStyle(0, LVS_REPORT);
	SetExtendedStyle(GetExtendedStyle() | LVS_EX_DOUBLEBUFFER 
		| LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP 
		| LVS_EX_COLUMNSNAPPOINTS/*最小列宽*/
	);


	EnableWindowTheme(GetSafeHwnd(), L"ListView", L"Explorer", 0);
}


BOOL CMyListCtrl1::OnHeaderClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLISTVIEW* pLV = reinterpret_cast<NMLISTVIEW*>(pNMHDR);

	SetFocus();	// Ensure other controls gets kill-focus

	int colIndex = pLV->iSubItem;

	if (m_nSortCol == colIndex)
	{
		m_bAscending = !m_bAscending;
	}
	else
	{
		m_nSortCol = colIndex;
		m_bAscending = true;
	}

	if (SortColumn(m_nSortCol, m_bAscending))
		SetSortArrow(m_nSortCol, m_bAscending);

	return FALSE;	// Let parent-dialog get chance
}



void CMyListCtrl1::OnContextMenu(CWnd* pWnd, CPoint point)
{
	if (pWnd == GetHeaderCtrl())
	{
		CPoint pt = point;
		ScreenToClient(&pt);

		HDHITTESTINFO hdhti = { 0 };
		hdhti.pt = pt;
		hdhti.pt.x += GetScrollPos(SB_HORZ);   //加上滚动条的距离
		::SendMessage(GetHeaderCtrl()->GetSafeHwnd(), HDM_HITTEST, 0, (LPARAM)&hdhti);
		if (hdhti.iItem != -1) //点击了表头
		{
			// 获取表头标题
			CString strTitle = m_pDataModel->GetColTitle(hdhti.iItem);

			//动态创建菜单
			CMenu menu;
			UINT uFlags = MF_BYPOSITION | MF_STRING;
			VERIFY(menu.CreatePopupMenu());
			menu.InsertMenu(0, uFlags, 1, CString(_T("Group by: ")) + strTitle);
			if (IsGroupViewEnabled())
				menu.InsertMenu(0, uFlags, 2, _T("Disable Grouping"));
			for (int i = m_vecVisible.size() - 1; i >= 0; --i) {
				uFlags = MF_BYPOSITION | MF_STRING;
				if (m_vecVisible[i])
					uFlags |= MF_CHECKED;		
				else
					uFlags |= MF_UNCHECKED;

				CString strTitle = m_pDataModel->GetColTitle(i);

				menu.InsertMenu(0, uFlags, i + 3, strTitle);
			}

			//TPM_RETURNCMD nResult是点击的菜单 不会走OnCommand
			/*int nResult = */menu.TrackPopupMenu(TPM_LEFTALIGN/* | TPM_RETURNCMD*/, point.x, point.y, this, 0);
			//switch (nResult) //如果放开就不走OnCommand
			//{
			//case 1:	GroupByColumn(hdhti.iItem); break;
			//case 2: RemoveAllGroups(); EnableGroupView(FALSE); break;
			//}
		}
		return;
	}

	//点击的区域不是表头
	if (IsGroupViewEnabled())
	{
		if (point.x != -1 && point.y != -1) //在客户区内
		{
			CMenu menu;
			UINT uFlags = MF_BYPOSITION | MF_STRING;
			VERIFY(menu.CreatePopupMenu());

			CPoint pt = point;
			ScreenToClient(&pt);
			//int nGroupId = GroupHitTest(pt);  //如果点击了“分组区域”
			//if (nGroupId >= 0)
			//{
			//	const CString& groupHeader = GetGroupHeader(nGroupId);
			//	CString menuText = CString(_T("Check group: ")) + groupHeader;
			//	menu.InsertMenu(1, uFlags, 3, menuText);
			//	menuText = CString(_T("Uncheck group: ")) + groupHeader;
			//	menu.InsertMenu(2, uFlags, 4, menuText);
			//	menuText = CString(_T("Delete group: ")) + groupHeader;
			//	menu.InsertMenu(3, uFlags, 5, menuText);

			//	menu.InsertMenu(4, uFlags | MF_SEPARATOR, 6, _T(""));
			//}

			int nRow = HitTest(pt);
			if (nRow == -1) //点击区域不在行上
			{
				menu.InsertMenu(5, uFlags, 7, _T("Expand all groups"));
				menu.InsertMenu(6, uFlags, 8, _T("Collapse all groups"));
				menu.InsertMenu(7, uFlags, 9, _T("Disable grouping"));
			}

			int nResult = menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RETURNCMD, point.x, point.y, this, 0);
			switch (nResult)
			{
			//case 1: SetGroupState(nGroupId, LVGS_NORMAL); break;
			//case 2: SetGroupState(nGroupId, LVGS_COLLAPSED); break;
			//case 3: CheckEntireGroup(nGroupId, true); break;
			//case 4: CheckEntireGroup(nGroupId, false); break;
			//case 5: DeleteEntireGroup(nGroupId); break;
			case 7: ExpandAllGroups(); break;
			case 8: CollapseAllGroups(); break;
			case 9: RemoveAllGroups(); EnableGroupView(FALSE); break;
			}
		}
	}
}


void CMyListCtrl1::SetSortArrow(int colIndex, bool ascending)
{

	for (int i = 0; i < GetHeaderCtrl()->GetItemCount(); ++i)
	{
		HDITEM hditem = { 0 };
		hditem.mask = HDI_FORMAT;
		VERIFY(GetHeaderCtrl()->GetItem(i, &hditem));
		hditem.fmt &= ~(HDF_SORTDOWN | HDF_SORTUP);
		if (i == colIndex)
		{
			hditem.fmt |= ascending ? HDF_SORTDOWN : HDF_SORTUP;
		}
		VERIFY(CListCtrl::GetHeaderCtrl()->SetItem(i, &hditem));
	}

}


// The column version of GetItemData(), one can specify an unique
// identifier when using InsertColumn()
int CMyListCtrl1::GetColumnData(int col) const
{
	LVCOLUMN lvc = { 0 };
	lvc.mask = LVCF_SUBITEM;
	VERIFY(GetColumn(col, &lvc));
	return lvc.iSubItem;
}



bool CMyListCtrl1::SortColumn(int nCol, bool ascending)
{
	//普通排序
	if (GetItemCount() != m_pDataModel->GetRowIds())
		return false;

	//columnData可以是附加参数
	int columnData = GetColumnData(nCol);
	PARAMSORT paramsort(m_pDataModel, columnData, ascending);
	if (IsGroupViewEnabled())
	{
		SetRedraw(FALSE);

		//先分组，行自动归类分组
		GroupByColumn(nCol);

		// Cannot use GetGroupInfo during sort
		for (int nRow = 0; nRow < GetItemCount(); ++nRow)
		{
			int nGroupId = GetRowGroupId(nRow);
			if (nGroupId != -1 && paramsort.m_GroupNames.FindKey(nGroupId) == -1)
				paramsort.m_GroupNames.Add(nGroupId, GetGroupHeader(nGroupId));
		}

		SetRedraw(TRUE);
		Invalidate(FALSE);

		//分组也要排序
		// Avoid bug in CListCtrl::SortGroups() which differs from ListView_SortGroups
		if (!ListView_SortGroups(m_hWnd, SortFuncGroup, &paramsort))
			return false;
	}
	SortItems(SortFunc, (DWORD_PTR)&paramsort);


	/*
	//使用LVS_OWNDATA，针对大数据，m_pDataModel是缓存
	int columnData = GetColumnData(columnIndex);
	std::stable_sort(m_pDataModel->GetRecords().begin(),
		m_pDataModel->GetRecords().end(), SortFunc2(columnData, ascending));
	SetItemCount((int)m_pDataModel->GetRowIds());	// Refresh List-Control
	*/
	return true;

}


BOOL CMyListCtrl1::ShowColumn(int nCol, bool bShow)
{
	SetRedraw(FALSE);

	if (bShow)
	{
		SetExtendedStyle(GetExtendedStyle() | LVS_EX_COLUMNSNAPPOINTS);

		SetColumnWidth(nCol, 1);
		m_vecVisible[nCol] = true;
		AdjustColumnWidth();
	}
	else //隐藏列
	{
		SetExtendedStyle(GetExtendedStyle()&~LVS_EX_COLUMNSNAPPOINTS);

		m_vecVisible[nCol] = false;
		SetColumnWidth(nCol, 0);

		SetExtendedStyle(GetExtendedStyle() | LVS_EX_COLUMNSNAPPOINTS);
	}

	SetRedraw(TRUE);
	Invalidate(FALSE);
	return TRUE;
}


void CMyListCtrl1::LoadData()
{
	//普通的加载数据
	if (GetHeaderCtrl()->GetItemCount() == 0)
	{
		// Create Columns
		LVCOLUMN lvCol;
		lvCol.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_MINWIDTH;
		for (int col = 0; col < m_pDataModel->GetColCount(); ++col)
		{
			CString& title = const_cast<CString&>(m_pDataModel->GetColTitle(col));
			lvCol.pszText = title.GetBuffer();
			lvCol.cchTextMax = title.GetLength();
			lvCol.iSubItem = col;
			lvCol.cxMin = 2 * GetStringWidth(title);
			//VERIFY(InsertColumn(col, title, LVCFMT_LEFT, 100) != -1);
			InsertColumn(col, &lvCol);
		}
	}
	//else
	//{
	//	// Empty list-control and force refresh
	//	DeleteAllItems();
	//	//ResetSortOrder();
	//	Invalidate();
	//	UpdateWindow();
	//}

	// Insert data with callback
	SetRedraw(FALSE);	// Disable redraw as InsertItem becomes so much faster
	int nItem = 0;
	for (size_t rowId = 0; rowId < m_pDataModel->GetRowIds(); ++rowId)
	{
		nItem = InsertItem(++nItem, _T(""));	// Fastest to insert at the end
		VERIFY(nItem != -1);
		VERIFY(SetItemData(nItem, rowId));
		for (int col = 0; col < m_pDataModel->GetColCount(); ++col)
		{
			//发送消息填充内容
			//VERIFY(SetItemText(nItem, col, LPSTR_TEXTCALLBACK));
			
			//直接填充
			CString value(m_pDataModel->GetCellText(rowId, col));
			SetItemText(nItem, col, value);
		}
	}
	SetRedraw(TRUE);
	Invalidate();
	UpdateWindow();

	AdjustColumnWidth();
	GroupByColumn(m_pDataModel->GetColCount() - 1);

	/*
	//LSV_OWNDATA加载数据，不创建行，缓存
	if (GetHeaderCtrl()->GetItemCount() == 0)
	{
		// Create Columns
		LVCOLUMN lvCol;
		lvCol.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_MINWIDTH;
		for (int col = 0; col < m_pDataModel->GetColCount(); ++col)
		{
			CString& title = const_cast<CString&>(m_pDataModel->GetColTitle(col));
			lvCol.pszText = title.GetBuffer();
			lvCol.cchTextMax = title.GetLength();
			lvCol.iSubItem = col;
			lvCol.cxMin = 2 * GetStringWidth(title);
			//VERIFY(InsertColumn(col, title, LVCFMT_LEFT, 100) != -1);
			InsertColumn(col, &lvCol);
		}
	}

	//ResetSortOrder();

	//m_DataModel 是缓存结构，数据已经在里面了，LVN_GETDISPINFO填数据;

	// Tell list-control how much data we have, LVS_OWNDATA需要
	SetItemCount((int)m_pDataModel->GetRowIds());

	AdjustColumnWidth();
	*/
}



BOOL CMyListCtrl1::OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO* pNMW = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	int nItem = pNMW->item.iItem;
	int nSubItem = pNMW->item.iSubItem;

	if (nItem< 0 || nItem >= GetItemCount())
		return FALSE;	// requesting invalid item

	if (nSubItem < 0 || nSubItem >= GetHeaderCtrl()->GetItemCount())
		return FALSE;	// requesting invalid column

	//int col = GetColumnData(nSubItem);
	//size_t rowId = (size_t)GetItemData(nItem);

	if (pNMW->item.mask & LVIF_TEXT)
	{
		// Request text
		CString& result = const_cast<CString&>(m_pDataModel->GetCellText(nItem, nSubItem));
		_tcsncpy_s(pNMW->item.pszText, pNMW->item.cchTextMax,
			result.GetBuffer(), pNMW->item.cchTextMax);
	}

	return FALSE;	// Let parent-dialog get chance
}



void CMyListCtrl1::AdjustColumnWidth()
{
	SetRedraw(FALSE);
	int nColumnCount = GetHeaderCtrl()->GetItemCount();

	for (int i = 0; i < nColumnCount; i++)
	{
		SetColumnWidth(i, LVSCW_AUTOSIZE);
		int nColumnWidth = GetColumnWidth(i);
		SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
		int nHeaderWidth = GetColumnWidth(i);

		SetColumnWidth(i, max(nColumnWidth, nHeaderWidth));
	}
	SetRedraw(TRUE);
}



BOOL CMyListCtrl1::GroupByColumn(int nCol)
{

	CWaitCursor waitCursor;

	SetSortArrow(-1, false);

	SetRedraw(FALSE);

	RemoveAllGroups();

	EnableGroupView(GetItemCount() > 0);

	if (IsGroupViewEnabled())
	{
		//<item文本，哪几行有这个文本>
		CSimpleMap<CString, CSimpleArray<int> > groups;

		//分组是要遍历全部记录，“重新组装”的
		// Loop through all rows and find possible groups
		for (int nRow = 0; nRow<GetItemCount(); ++nRow)
		{
			CString cellText = GetItemText(nRow, nCol);

			int nGroupId = groups.FindKey(cellText);
			if (nGroupId == -1)
			{
				CSimpleArray<int> rows;
				groups.Add(cellText, rows);
				nGroupId = groups.FindKey(cellText);
			}
			groups.GetValueAt(nGroupId).Add(nRow);
		}

		// Look through all groups and assign rows to group
		for (int nGroupId = 0; nGroupId < groups.GetSize(); ++nGroupId)
		{
			const CSimpleArray<int>& groupRows = groups.GetValueAt(nGroupId);
			DWORD dwState = /*LVGS_NORMAL*/LVGS_COLLAPSIBLE;

			VERIFY(InsertGroupHeader(nGroupId, nGroupId, groups.GetKeyAt(nGroupId), dwState) != -1);
			//SetGroupTask(nGroupId, _T("Task: Check Group"));
			//CString subtitle;
			//subtitle.Format(_T("Subtitle: %i rows"), groupRows.GetSize());
			//SetGroupSubtitle(nGroupId, subtitle);
			//SetGroupFooter(nGroupId, _T("Group Footer"));

			for (int groupRow = 0; groupRow < groupRows.GetSize(); ++groupRow)
			{
				VERIFY(SetRowGroupId(groupRows[groupRow], nGroupId));
			}
		}
		SetRedraw(TRUE);
		Invalidate(FALSE);
		return TRUE;
	}

	SetRedraw(TRUE);
	Invalidate(FALSE);
	return FALSE;
}



LRESULT CMyListCtrl1::InsertGroupHeader(int nIndex, int nGroupId, 
	const CString& strHeader, DWORD dwState /* = LVGS_NORMAL */, DWORD dwAlign /*= LVGA_HEADER_LEFT*/)
{
	LVGROUP lg = { 0 };
	lg.cbSize = sizeof(lg);
	lg.iGroupId = nGroupId;
	lg.state = dwState;
	lg.mask = LVGF_GROUPID | LVGF_HEADER | LVGF_STATE | LVGF_ALIGN;
	lg.uAlign = dwAlign;

	// Header-title must be unicode (Convert if necessary)
	lg.pszHeader = (LPWSTR)(LPCTSTR)strHeader;
	lg.cchHeader = strHeader.GetLength();

	return InsertGroup(nIndex, (PLVGROUP)&lg);
}



BOOL CMyListCtrl1::SetGroupTask(int nGroupID, const CString& task)
{
	LVGROUP lg = { 0 };
	lg.cbSize = sizeof(lg);
	lg.mask = LVGF_TASK;
	lg.pszTask = (LPWSTR)(LPCTSTR)task;
	lg.cchTask = task.GetLength();

	if (SetGroupInfo(nGroupID, (PLVGROUP)&lg) == -1)
		return FALSE;

	return TRUE;
}


BOOL CMyListCtrl1::SetGroupSubtitle(int nGroupID, const CString& subtitle)
{

	LVGROUP lg = { 0 };
	lg.cbSize = sizeof(lg);
	lg.mask = LVGF_SUBTITLE;
	lg.pszSubtitle = (LPWSTR)(LPCTSTR)subtitle;
	lg.cchSubtitle = subtitle.GetLength();

	if (SetGroupInfo(nGroupID, (PLVGROUP)&lg) == -1)
		return FALSE;

	return TRUE;

}


BOOL CMyListCtrl1::SetGroupFooter(int nGroupID, const CString& footer, DWORD dwAlign /*= LVGA_FOOTER_CENTER*/)
{
	LVGROUP lg = { 0 };
	lg.cbSize = sizeof(lg);
	lg.mask = LVGF_FOOTER | LVGF_ALIGN;
	lg.uAlign = dwAlign;
	lg.pszFooter = (LPWSTR)(LPCTSTR)footer;
	lg.cchFooter = footer.GetLength();

	if (SetGroupInfo(nGroupID, (PLVGROUP)&lg) == -1)
		return FALSE;

	return TRUE;
}



BOOL CMyListCtrl1::SetRowGroupId(int nRow, int nGroupId)
{
	//OBS! Rows not assigned to a group will not show in group-view
	LVITEM lvItem = { 0 };
	lvItem.mask = LVIF_GROUPID;
	lvItem.iItem = nRow;
	lvItem.iSubItem = 0;
	lvItem.iGroupId = nGroupId;
	return SetItem(&lvItem);
}


int CMyListCtrl1::GetRowGroupId(int nRow)
{
	LVITEM lvi = { 0 };
	lvi.mask = LVIF_GROUPID;
	lvi.iItem = nRow;
	VERIFY(GetItem(&lvi));
	return lvi.iGroupId;
}


CString CMyListCtrl1::GetGroupHeader(int nGroupId)
{
	LVGROUP lg = { 0 };
	lg.cbSize = sizeof(lg);
	lg.iGroupId = nGroupId;
	lg.mask = LVGF_HEADER | LVGF_GROUPID;
	VERIFY(GetGroupInfo(nGroupId, (PLVGROUP)&lg) != -1);

	return lg.pszHeader;

}


void CMyListCtrl1::ExpandAllGroups()
{
	// Loop through all rows and find possible groups
	for (int nRow = 0; nRow<GetItemCount(); ++nRow)
	{
		int nGroupId = GetRowGroupId(nRow);
		if (nGroupId != -1)
		{
			if (HasGroupState(nGroupId, LVGS_COLLAPSED))
			{
				SetGroupState(nGroupId, LVGS_NORMAL);
			}
		}
	}
}


void CMyListCtrl1::CollapseAllGroups()
{
	// Loop through all rows and find possible groups
	for (int nRow = 0; nRow<GetItemCount(); ++nRow)
	{
		int nGroupId = GetRowGroupId(nRow);
		if (nGroupId != -1)
		{
			if (!HasGroupState(nGroupId, LVGS_COLLAPSED))
			{
				SetGroupState(nGroupId, LVGS_COLLAPSED);
			}
		}
	}
}

BOOL CMyListCtrl1::HasGroupState(int nGroupId, DWORD dwState)
{
	LVGROUP lg = { 0 };
	lg.cbSize = sizeof(lg);
	lg.mask = LVGF_STATE;
	lg.stateMask = dwState;
	if (GetGroupInfo(nGroupId, (PLVGROUP)&lg) == -1)
		return FALSE;

	return lg.state == dwState;
}

BOOL CMyListCtrl1::SetGroupState(int nGroupId, DWORD dwState)
{
	LVGROUP lg = { 0 };
	lg.cbSize = sizeof(lg);
	lg.mask = LVGF_STATE;
	lg.state = dwState;
	lg.stateMask = dwState;

	// Maintain LVGS_COLLAPSIBLE state
	if (HasGroupState(nGroupId, LVGS_COLLAPSIBLE))
		lg.state |= LVGS_COLLAPSIBLE;

	if (SetGroupInfo(nGroupId, (PLVGROUP)&lg) == -1)
		return FALSE;

	return TRUE;
}


LRESULT CMyListCtrl1::OnInsertColumn(WPARAM wParam, LPARAM lParam)
{
	// Let the CListCtrl handle the event
	LRESULT lRet = DefWindowProc(LVM_INSERTCOLUMN, wParam, lParam);
	if (lRet == -1)
		return -1;

	int nCol = (int)lRet;

	// Book keeping of columns
	if ((int)m_vecVisible.size() < GetHeaderCtrl()->GetItemCount())
		m_vecVisible.push_back(true);	// Insert as visible

	return lRet;
}

LRESULT CMyListCtrl1::OnDeleteColumn(WPARAM wParam, LPARAM lParam)
{
	// Let the CListCtrl handle the event
	LRESULT lRet = DefWindowProc(LVM_DELETECOLUMN, wParam, lParam);
	if (lRet == FALSE)
		return FALSE;

	// Book keeping of columns
	int nCol = (int)wParam;
	if(nCol < (int)m_vecVisible.size())
		m_vecVisible[nCol] = false;

	return lRet;
}

BOOL CMyListCtrl1::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(wParam) == 0) //菜单
	{
		int id = LOWORD(wParam); //菜单id：OnContextMenu
		switch (id)
		{
		case 1:	GroupByColumn(id); break;
		case 2: RemoveAllGroups(); EnableGroupView(FALSE); break;
		default: {//显示列
			int nCol = id - 3;
			ShowColumn(nCol, !m_vecVisible[nCol]);
			break;
		}
		}
		
	}
	return TRUE;
}
