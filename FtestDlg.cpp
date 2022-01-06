
// FtestDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Ftest.h"
#include "FtestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CFtestDlg 대화 상자



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


// CFtestDlg 메시지 처리기

BOOL CFtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	m_progress_time.SetRange(0, 180); //180초,, progress control에 범위를 설정
	m_progress_time.SetPos(180); // 180 -> 0으로 시간이 흘러감

	SetTimer(2, 1000, NULL);

	CString str;

	for (int i = 0; i < MAX_CARD_COUNT; i++) {	
		str.Format(L"res\\pp\\%03d.png", i); //printf와 비슷하지만 출력값을 화면이 아닌 클래스로 보낸다.
		
		m_card_image[i].Load(str);
		
	}

	for (int i = 0; i < REAL_CARD_COUNT; i++) {
		m_card_table[i] = i; //0~17배열에 0~17의 숫자 차례로 부여
		m_card_table[18 + i] = i; //18~35배열에 0~17의 숫자 차례로 부여 ==> index숫자 부여작업
	}
	srand((unsigned int)time(NULL)); //난수를 초단위로 변경

	char first_index, second_index, temp; //2개 카드의 값을 바꾸기 위해 선언

	for (int i = 0; i < 50; i++) { // 자리바꿈을 50번 실행
		first_index = rand() % 36; // 0~35사이의 숫자 중 임의로 선택
		second_index = rand() % 36;

		temp = m_card_table[first_index];
		m_card_table[first_index] = m_card_table[second_index];
		m_card_table[second_index] = temp;
	}
	SetTimer(1, 3000, NULL);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CFtestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialogEx::OnPaint();
		CPaintDC dc(this);
		if (m_hint_flag == 1) {//앞면출력
			int index;
			for (int i = 0; i < REAL_CARD_COUNT * 2; i++) {
				index = m_card_table[i] + 1;
				if (index) {
					m_card_image[index].Draw(dc, (i % 6) * 36+8, (i / 6) * 56+8);
					//x축은 0~5까지 이동하기위해, y축은 y좌표 0을 주기 위해
					//i%6은 한줄에 6개를 그려주는것, i/6은 그리면 다음줄로 넘겨주는 것
				}
			}
		}
		else {//뒷면 출력
			for (int i = 0; i < REAL_CARD_COUNT * 2; i++) {
				if (m_card_table[i] != -1) {
					m_card_image[0].Draw(dc, (i % 6) * 36+8, (i / 6) * 56+8);
				}
			}
		}
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CFtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFtestDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == 1) {
		KillTimer(1);
		m_hint_flag = 0;
		Invalidate();
	}
	else if (nIDEvent == 2) {
		int pos = m_progress_time.GetPos(); // progress의 위치를 pos에 저장
		if(pos > 0) {
			pos--; //pos감소
			m_progress_time.SetPos(pos); //감소된 pos값을 progress로 다시 넣음
		}
		else {
			KillTimer(2);
			MessageBox(L"패배하였습니다.", L"ㅎ;;", MB_ICONSTOP);
		}
		
	}


	CDialogEx::OnTimer(nIDEvent);
}


void CFtestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다
	if (m_hint_flag == 2) return; // 1초안에 여러번 클릭되는 것을 막는다.

	if (point.x >= 0 && point.x <= 6 * 36 && point.y >= 0 && point.y <= 6 * 56) {
		int x = point.x / 36;
		int y = point.y / 56; //36, 56으로 나누는 것은 이미지의 선택범위를 나타내기 위해서
		CClientDC dc(this);

		int select_index = y * 6 + x; //2차원을 1차원배열의 index값으로 변환
		
		int index = m_card_table[select_index];
		if (index == -1) { //뒤집힌 자리를 클릭했을때 다시 뒷면이 나오지 않게 설정
			return;
		}

		if (m_first_selected_index == -1) { // 최초 -1로 초기화되있어서 if문에서 시작함
			m_first_selected_index = select_index; //처음 클릭한 좌표값

			m_card_image[m_card_table[select_index] + 1].Draw(dc, x * 36+8, y * 56+8);  //뒷면의 인덱스가 0이므로 +1을 해서 그림표시되게 함
		}
		else {
			if (select_index != m_first_selected_index) { // 처음클릭한 값과 비교하여 다르면 실행, 같으면 함수종료
			
				m_second_selected_index = select_index;

				m_card_image[m_card_table[select_index] + 1].Draw(dc, x * 36+8, y * 56+8); // 두번째 클릭한 값에 이미지를 그림

				int pos = m_progress_time.GetPos();
				if (m_card_table[m_first_selected_index] == m_card_table[m_second_selected_index]) {
					m_card_table[m_first_selected_index] = -1;
					m_card_table[m_second_selected_index] = -1;
					m_progress_time.SetPos(pos + 10); //정답을 맞추면 시간증가
				}
				else {
					m_progress_time.SetPos(pos - 10); //정답을 틀리면 시간감소
				}
				m_first_selected_index = -1; // -1로 초기화해서 다음 클릭엔 if문부터 시작하게 해줌
				m_second_selected_index = -1;

				m_hint_flag = 2;
				SetTimer(1, 1000, NULL); // 1초뒤에 타이머발생
			}
		}
		CDialogEx::OnLButtonDown(nFlags, point);
	}	
}

void CFtestDlg::OnBnClickedExitbtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SendMessage(WM_CLOSE, 0, 0);
}


void CFtestDlg::OnBnClickedRstart()
{

	KillTimer(1);
	KillTimer(2);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

									// TODO: 여기에 추가 초기화 작업을 추가합니다.

	m_hint_flag = 1;

	m_progress_time.SetRange(0, 180); //180초,, progress control에 범위를 설정
	m_progress_time.SetPos(180); // 180 -> 0으로 시간이 흘러감

	SetTimer(2, 1000, NULL);


	for (int i = 0; i < REAL_CARD_COUNT; i++) {
		m_card_table[i] = i; //0~17배열에 0~17의 숫자 차례로 부여
		m_card_table[18 + i] = i; //18~35배열에 0~17의 숫자 차례로 부여 ==> index숫자 부여작업
	}
	srand((unsigned int)time(NULL)); //난수를 초단위로 변경

	char first_index, second_index, temp; //2개 카드의 값을 바꾸기 위해 선언

	for (int i = 0; i < 50; i++) { // 자리바꿈을 50번 실행
		first_index = rand() % 36; // 0~35사이의 숫자 중 임의로 선택
		second_index = rand() % 36;

		temp = m_card_table[first_index];
		m_card_table[first_index] = m_card_table[second_index];
		m_card_table[second_index] = temp;
	}
	SetTimer(1, 3000, NULL);
	
	Invalidate();
	
	SetDlgItemInt(IDC_REVIEW, 2);
	
	if (IDCANCEL == MessageBox(L"게임이 다시 시작됩니다.", L"체크!!", MB_ICONQUESTION)) {
		return;
	}
}


void CFtestDlg::OnBnClickedReviewBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int num = GetDlgItemInt(IDC_REVIEW); // 버튼의 caption값을 정수형으로 받아옴
	if (num > 0) {
		num--;
		SetDlgItemInt(IDC_REVIEW, num); // 감소된 값을 caption에 넣어줌
		m_hint_flag = 1;
		Invalidate(); // WM_PAINT메시지가 발생하고 화면을 강제로 갱신
		SetTimer(1, 3000, NULL);
	}
}