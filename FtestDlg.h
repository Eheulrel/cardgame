
// FtestDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"

#define MAX_CARD_COUNT 19 //전체 읽어올 카드 종류
#define REAL_CARD_COUNT 18 //실제 사용할 카드 종류(뒷면 1장)

// CFtestDlg 대화 상자
class CFtestDlg : public CDialogEx
{
// 생성입니다.
private:
	CImage m_card_image[MAX_CARD_COUNT]; //카드이미지 불러오기
	char m_card_table[REAL_CARD_COUNT * 2]; //2장씩 짝지어주기 위해 *2
	char m_hint_flag = 1; // flag = 1 앞면 ,, 나머지는 뒷면
	char m_first_selected_index = -1;
	char m_second_selected_index = -1;
public:
	CFtestDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
