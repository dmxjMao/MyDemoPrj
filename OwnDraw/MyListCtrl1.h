#pragma once
#include "UICfg.h"

// CMyListCtrl1
//struct stDeviceInfo;
class CListCtrl_DataModel;

class CMyListCtrl1 : public CListCtrl, public CUICfg
{
	DECLARE_DYNAMIC(CMyListCtrl1)

public:
	CMyListCtrl1();
	virtual ~CMyListCtrl1();
	
	//void FillItem(const std::vector<std::shared_ptr<stDeviceInfo>>& );
	void SetSortArrow(int col, bool ascending);//设置箭头
	inline bool IsAscending() const { return m_bAscending; }
	int GetColumnData(int col) const;//排序的自定义数据
	bool SortColumn(int columnIndex, bool ascending);//排序
	void LoadData();
	
	BOOL GroupByColumn(int nCol);//按列分组
	LRESULT InsertGroupHeader(int nIndex, int nGroupID, 
		const CString& strHeader, DWORD dwState = LVGS_NORMAL, DWORD dwAlign = LVGA_HEADER_LEFT);//设置分组名称
	BOOL SetGroupTask(int nGroupID, const CString& task);//设置分组Task
	BOOL SetGroupSubtitle(int nGroupID, const CString& subtitle);//设置分组子标题
	BOOL SetGroupFooter(int nGroupID, const CString& footer, DWORD dwAlign = LVGA_FOOTER_CENTER);//设置分组脚注
	BOOL SetRowGroupId(int nRow, int nGroupID);//设置item的分组id，item会自动在组内显示
	int GetRowGroupId(int nRow);//获取行的分组id
	CString GetGroupHeader(int nGroupID);//获取分组名称
	void ExpandAllGroups();//展开所有分组
	void CollapseAllGroups();//收缩所有分组
	BOOL HasGroupState(int nGroupID, DWORD dwState);//分组是否有dwState状态
	BOOL SetGroupState(int nGroupID, DWORD dwState);//设置分组状态


protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
	afx_msg BOOL OnHeaderClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg BOOL OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	void AdjustColumnWidth();

private:
	std::vector<bool> m_vecVisible;//列是否可见
	bool m_bAscending = false; //是否升序
	int m_nSortCol = -1;//排序的列
	std::shared_ptr<CListCtrl_DataModel> m_pDataModel = 0;//数据
};


