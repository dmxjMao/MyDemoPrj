// MyCombo1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OwnDraw.h"
#include "MyCombo1.h"


// CMyCombo1

IMPLEMENT_DYNAMIC(CMyCombo1, CComboBoxEx)

CMyCombo1::CMyCombo1()
{

}

CMyCombo1::~CMyCombo1()
{
}


BEGIN_MESSAGE_MAP(CMyCombo1, CComboBoxEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()





void CMyCombo1::FillItem(const std::vector<CString>& vecItem)
{
	const int nCnt = vecItem.size() > 10 ? 10 : (int)vecItem.size();

	for (int i = 0; i < nCnt; ++i) {
		AddString(vecItem[i]);
	}

	SetCurSel(0);
}

void CMyCombo1::OnPaint()
{
	//BOOL b = SetCueBanner(_T("abc"));
	__super::OnPaint();
}


void CMyCombo1::PreSubclassWindow()
{
	BOOL b = SetCueBanner(_T("�û�����"));
	ModifyStyle(CBS_SORT, CBS_AUTOHSCROLL);//������ˮƽ����
	SetMinVisibleItems(10);//������ʾ10��

	__super::PreSubclassWindow();
}
