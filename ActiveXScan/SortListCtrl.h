#pragma once


// CSortListCtrl
typedef enum eListColumn
{
	Column_Index_INDEX,
	Column_Index_PROGID,
	Column_Index_PATH,

	Column_Index_NUM,
} eListColumn_t;

class CSortListCtrl : public CMFCListCtrl
{
		DECLARE_DYNAMIC(CSortListCtrl)

	public:
		CSortListCtrl();
		virtual ~CSortListCtrl();

		int OnCompareItems(LPARAM lParam1, LPARAM lParam2, int iColumn);

	protected:
		DECLARE_MESSAGE_MAP()

};


