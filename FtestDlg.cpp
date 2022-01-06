
// FtestDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Ftest.h"
#include "FtestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFtestDlg ��ȭ ����



CFtestDlg::CFtestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS_TIME, m_progress_time);
}

BEGIN_MESSAGE_MAP(CFtestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(ID_EXITBTN, &CFtestDlg::OnBnClickedExitbtn)
	ON_BN_CLICKED(IDC_RSTART, &CFtestDlg::OnBnClickedRstart)
	ON_BN_CLICKED(IDC_REVIEW, &CFtestDlg::OnBnClickedReviewBtn)
END_MESSAGE_MAP()


// CFtestDlg �޽��� ó����

BOOL CFtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_progress_time.SetRange(0, 180); //180��,, progress control�� ������ ����
	m_progress_time.SetPos(180); // 180 -> 0���� �ð��� �귯��

	SetTimer(2, 1000, NULL);

	CString str;

	for (int i = 0; i < MAX_CARD_COUNT; i++) {	
		str.Format(L"res\\pp\\%03d.png", i); //printf�� ��������� ��°��� ȭ���� �ƴ� Ŭ������ ������.
		
		m_card_image[i].Load(str);
		
	}

	for (int i = 0; i < REAL_CARD_COUNT; i++) {
		m_card_table[i] = i; //0~17�迭�� 0~17�� ���� ���ʷ� �ο�
		m_card_table[18 + i] = i; //18~35�迭�� 0~17�� ���� ���ʷ� �ο� ==> index���� �ο��۾�
	}
	srand((unsigned int)time(NULL)); //������ �ʴ����� ����

	char first_index, second_index, temp; //2�� ī���� ���� �ٲٱ� ���� ����

	for (int i = 0; i < 50; i++) { // �ڸ��ٲ��� 50�� ����
		first_index = rand() % 36; // 0~35������ ���� �� ���Ƿ� ����
		second_index = rand() % 36;

		temp = m_card_table[first_index];
		m_card_table[first_index] = m_card_table[second_index];
		m_card_table[second_index] = temp;
	}
	SetTimer(1, 3000, NULL);
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CFtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CFtestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialogEx::OnPaint();
		CPaintDC dc(this);
		if (m_hint_flag == 1) {//�ո����
			int index;
			for (int i = 0; i < REAL_CARD_COUNT * 2; i++) {
				index = m_card_table[i] + 1;
				if (index) {
					m_card_image[index].Draw(dc, (i % 6) * 36+8, (i / 6) * 56+8);
					//x���� 0~5���� �̵��ϱ�����, y���� y��ǥ 0�� �ֱ� ����
					//i%6�� ���ٿ� 6���� �׷��ִ°�, i/6�� �׸��� �����ٷ� �Ѱ��ִ� ��
				}
			}
		}
		else {//�޸� ���
			for (int i = 0; i < REAL_CARD_COUNT * 2; i++) {
				if (m_card_table[i] != -1) {
					m_card_image[0].Draw(dc, (i % 6) * 36+8, (i / 6) * 56+8);
				}
			}
		}
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CFtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFtestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (nIDEvent == 1) {
		KillTimer(1);
		m_hint_flag = 0;
		Invalidate();
	}
	else if (nIDEvent == 2) {
		int pos = m_progress_time.GetPos(); // progress�� ��ġ�� pos�� ����
		if(pos > 0) {
			pos--; //pos����
			m_progress_time.SetPos(pos); //���ҵ� pos���� progress�� �ٽ� ����
		}
		else {
			KillTimer(2);
			MessageBox(L"�й��Ͽ����ϴ�.", L"��;;", MB_ICONSTOP);
		}
		
	}


	CDialogEx::OnTimer(nIDEvent);
}


void CFtestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�
	if (m_hint_flag == 2) return; // 1�ʾȿ� ������ Ŭ���Ǵ� ���� ���´�.

	if (point.x >= 0 && point.x <= 6 * 36 && point.y >= 0 && point.y <= 6 * 56) {
		int x = point.x / 36;
		int y = point.y / 56; //36, 56���� ������ ���� �̹����� ���ù����� ��Ÿ���� ���ؼ�
		CClientDC dc(this);

		int select_index = y * 6 + x; //2������ 1�����迭�� index������ ��ȯ
		
		int index = m_card_table[select_index];
		if (index == -1) { //������ �ڸ��� Ŭ�������� �ٽ� �޸��� ������ �ʰ� ����
			return;
		}

		if (m_first_selected_index == -1) { // ���� -1�� �ʱ�ȭ���־ if������ ������
			m_first_selected_index = select_index; //ó�� Ŭ���� ��ǥ��

			m_card_image[m_card_table[select_index] + 1].Draw(dc, x * 36+8, y * 56+8);  //�޸��� �ε����� 0�̹Ƿ� +1�� �ؼ� �׸�ǥ�õǰ� ��
		}
		else {
			if (select_index != m_first_selected_index) { // ó��Ŭ���� ���� ���Ͽ� �ٸ��� ����, ������ �Լ�����
			
				m_second_selected_index = select_index;

				m_card_image[m_card_table[select_index] + 1].Draw(dc, x * 36+8, y * 56+8); // �ι�° Ŭ���� ���� �̹����� �׸�

				int pos = m_progress_time.GetPos();
				if (m_card_table[m_first_selected_index] == m_card_table[m_second_selected_index]) {
					m_card_table[m_first_selected_index] = -1;
					m_card_table[m_second_selected_index] = -1;
					m_progress_time.SetPos(pos + 10); //������ ���߸� �ð�����
				}
				else {
					m_progress_time.SetPos(pos - 10); //������ Ʋ���� �ð�����
				}
				m_first_selected_index = -1; // -1�� �ʱ�ȭ�ؼ� ���� Ŭ���� if������ �����ϰ� ����
				m_second_selected_index = -1;

				m_hint_flag = 2;
				SetTimer(1, 1000, NULL); // 1�ʵڿ� Ÿ�̸ӹ߻�
			}
		}
		CDialogEx::OnLButtonDown(nFlags, point);
	}	
}

void CFtestDlg::OnBnClickedExitbtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SendMessage(WM_CLOSE, 0, 0);
}


void CFtestDlg::OnBnClickedRstart()
{

	KillTimer(1);
	KillTimer(2);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

									// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_hint_flag = 1;

	m_progress_time.SetRange(0, 180); //180��,, progress control�� ������ ����
	m_progress_time.SetPos(180); // 180 -> 0���� �ð��� �귯��

	SetTimer(2, 1000, NULL);


	for (int i = 0; i < REAL_CARD_COUNT; i++) {
		m_card_table[i] = i; //0~17�迭�� 0~17�� ���� ���ʷ� �ο�
		m_card_table[18 + i] = i; //18~35�迭�� 0~17�� ���� ���ʷ� �ο� ==> index���� �ο��۾�
	}
	srand((unsigned int)time(NULL)); //������ �ʴ����� ����

	char first_index, second_index, temp; //2�� ī���� ���� �ٲٱ� ���� ����

	for (int i = 0; i < 50; i++) { // �ڸ��ٲ��� 50�� ����
		first_index = rand() % 36; // 0~35������ ���� �� ���Ƿ� ����
		second_index = rand() % 36;

		temp = m_card_table[first_index];
		m_card_table[first_index] = m_card_table[second_index];
		m_card_table[second_index] = temp;
	}
	SetTimer(1, 3000, NULL);
	
	Invalidate();
	
	SetDlgItemInt(IDC_REVIEW, 2);
	
	if (IDCANCEL == MessageBox(L"������ �ٽ� ���۵˴ϴ�.", L"üũ!!", MB_ICONQUESTION)) {
		return;
	}
}


void CFtestDlg::OnBnClickedReviewBtn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int num = GetDlgItemInt(IDC_REVIEW); // ��ư�� caption���� ���������� �޾ƿ�
	if (num > 0) {
		num--;
		SetDlgItemInt(IDC_REVIEW, num); // ���ҵ� ���� caption�� �־���
		m_hint_flag = 1;
		Invalidate(); // WM_PAINT�޽����� �߻��ϰ� ȭ���� ������ ����
		SetTimer(1, 3000, NULL);
	}
}