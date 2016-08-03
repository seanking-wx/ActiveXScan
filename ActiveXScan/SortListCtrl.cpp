// SortListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "ActiveXScan.h"
#include "SortListCtrl.h"


// CSortListCtrl

IMPLEMENT_DYNAMIC(CSortListCtrl, CMFCListCtrl)

CSortListCtrl::CSortListCtrl()
{
}

CSortListCtrl::~CSortListCtrl()
{
}


BEGIN_MESSAGE_MAP(CSortListCtrl, CMFCListCtrl)
	//  ON_WM_COMPAREITEM()
END_MESSAGE_MAP()

// CSortListCtrl 消息处理程序
int CSortListCtrl::OnCompareItems(LPARAM lParam1, LPARAM lParam2, int iColumn)
{
	if((iColumn >= Column_Index_PROGID) && (iColumn <= Column_Index_PATH))
	{
		LVFINDINFO lvfi;
		lvfi.flags=LVFI_PARAM;
		lvfi.lParam=lParam1;
		CString strItem1 = GetItemText(FindItem(&lvfi),iColumn);
		lvfi.lParam=lParam2;
		CString strItem2 = GetItemText(FindItem(&lvfi),iColumn);
		return strItem1.Compare(strItem2);
	}
	return lParam1-lParam2;
}