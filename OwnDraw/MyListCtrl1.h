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
	void SetSortArrow(int col, bool ascending);//���ü�ͷ
	inline bool IsAscending() const { return m_bAscending; }
	int GetColumnData(int col) const;//������Զ�������
	bool SortColumn(int columnIndex, bool ascending);//����
	void LoadData();
	
	BOOL GroupByColumn(int nCol);//���з���
	LRESULT InsertGroupHeader(int nIndex, int nGroupID, 
		const CString& strHeader, DWORD dwState = LVGS_NORMAL, DWORD dwAlign = LVGA_HEADER_LEFT);//���÷�������
	BOOL SetGroupTask(int nGroupID, const CString& task);//���÷���Task
	BOOL SetGroupSubtitle(int nGroupID, const CString& subtitle);//���÷����ӱ���
	BOOL SetGroupFooter(int nGroupID, const CString& footer, DWORD dwAlign = LVGA_FOOTER_CENTER);//���÷����ע
	BOOL SetRowGroupId(int nRow, int nGroupID);//����item�ķ���id��item���Զ���������ʾ
	int GetRowGroupId(int nRow);//��ȡ�еķ���id
	CString GetGroupHeader(int nGroupID);//��ȡ��������
	void ExpandAllGroups();//չ�����з���
	void CollapseAllGroups();//�������з���
	BOOL HasGroupState(int nGroupID, DWORD dwState);//�����Ƿ���dwState״̬
	BOOL SetGroupState(int nGroupID, DWORD dwState);//���÷���״̬


protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
	afx_msg BOOL OnHeaderClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg BOOL OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	void AdjustColumnWidth();

private:
	std::vector<bool> m_vecVisible;//���Ƿ�ɼ�
	bool m_bAscending = false; //�Ƿ�����
	int m_nSortCol = -1;//�������
	std::shared_ptr<CListCtrl_DataModel> m_pDataModel = 0;//����
};


