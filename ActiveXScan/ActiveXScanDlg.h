
// ActiveXScanDlg.h : 头文件
//

#pragma once

#include "SortListCtrl.h"

#define LOAD_STRING_FROM_RESOURCE(s, r) \
	if(s.LoadString(r) == FALSE) { AfxThrowResourceException(); }

// CActiveXScanDlg 对话框
class CActiveXScanDlg : public CDialogEx
{
		// 构造
	public:
		CActiveXScanDlg(CWnd* pParent = NULL);  // 标准构造函数

		// 对话框数据
		enum { IDD = IDD_ACTIVEXSCAN_DIALOG };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

		// 实现
	protected:
		HICON m_hIcon;

		// 生成的消息映射函数
		virtual BOOL OnInitDialog();
		afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
		afx_msg void OnPaint();
		afx_msg HCURSOR OnQueryDragIcon();
		DECLARE_MESSAGE_MAP()
	public:
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	private:
		void LayoutWnd(void);
		void InitListCtrl(void);
		void RefreshActiveX(void);
		// 判断是否为ActiveX控件
		BOOL IsActiveX(HKEY hkClass);
	public:
		CSortListCtrl m_listActiveX;
};
