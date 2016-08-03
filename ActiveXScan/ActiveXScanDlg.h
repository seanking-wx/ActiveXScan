
// ActiveXScanDlg.h : ͷ�ļ�
//

#pragma once

#include "SortListCtrl.h"

#define LOAD_STRING_FROM_RESOURCE(s, r) \
	if(s.LoadString(r) == FALSE) { AfxThrowResourceException(); }

// CActiveXScanDlg �Ի���
class CActiveXScanDlg : public CDialogEx
{
		// ����
	public:
		CActiveXScanDlg(CWnd* pParent = NULL);  // ��׼���캯��

		// �Ի�������
		enum { IDD = IDD_ACTIVEXSCAN_DIALOG };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

		// ʵ��
	protected:
		HICON m_hIcon;

		// ���ɵ���Ϣӳ�亯��
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
		// �ж��Ƿ�ΪActiveX�ؼ�
		BOOL IsActiveX(HKEY hkClass);
	public:
		CSortListCtrl m_listActiveX;
};
