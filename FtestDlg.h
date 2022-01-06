
// FtestDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"

#define MAX_CARD_COUNT 19 //��ü �о�� ī�� ����
#define REAL_CARD_COUNT 18 //���� ����� ī�� ����(�޸� 1��)

// CFtestDlg ��ȭ ����
class CFtestDlg : public CDialogEx
{
// �����Դϴ�.
private:
	CImage m_card_image[MAX_CARD_COUNT]; //ī���̹��� �ҷ�����
	char m_card_table[REAL_CARD_COUNT * 2]; //2�徿 ¦�����ֱ� ���� *2
	char m_hint_flag = 1; // flag = 1 �ո� ,, �������� �޸�
	char m_first_selected_index = -1;
	char m_second_selected_index = -1;
public:
	CFtestDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedExitbtn();
	afx_msg void OnBnClickedRstart();
	afx_msg void OnBnClickedReviewBtn();

private:
	CProgressCtrl m_progress_time;
};
