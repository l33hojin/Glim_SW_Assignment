
// MFCGlimHomeworkDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MFCGlimHomework.h"
#include "MFCGlimHomeworkDlg.h"
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


// CMFCGlimHomeworkDlg 대화 상자



CMFCGlimHomeworkDlg::CMFCGlimHomeworkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCGLIMHOMEWORK_DIALOG, pParent)
	, m_nBackgroundWidth(640)
	, m_nBackgroundHeight(500)
	, m_nBackgroundBpp(8)
	, m_nRadius(10)
	, m_bMouseClicked(false)
	, m_szCirclePoints(_T(""))
	, m_nCircleThickness(4)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCGlimHomeworkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_LBString(pDX, IDC_LIST_CIRCLE_POSITION, m_szCirclePoints);
	DDX_Control(pDX, IDC_LIST_CIRCLE_POSITION, m_lstCirclePoints);
	DDX_Text(pDX, IDC_EDIT_THICKNESS, m_nCircleThickness);
	DDX_Text(pDX, IDC_EDIT_RADIUS, m_nRadius);
}

BEGIN_MESSAGE_MAP(CMFCGlimHomeworkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CMFCGlimHomeworkDlg::OnBnClickedBtnClear)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_RANDOM, &CMFCGlimHomeworkDlg::OnBnClickedBtnRandom)
	ON_MESSAGE(WM_THREAD_UPDATE, &CMFCGlimHomeworkDlg::OnThreadUpdate)

END_MESSAGE_MAP()


// CMFCGlimHomeworkDlg 메시지 처리기

BOOL CMFCGlimHomeworkDlg::OnInitDialog()
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

	m_imgBackground.Create(m_nBackgroundWidth, -m_nBackgroundHeight, m_nBackgroundBpp);

	if (m_nBackgroundBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_imgBackground.SetColorTable(0, 256, rgb);
	}

	unsigned char* fm = (unsigned char*)m_imgBackground.GetBits();
	memset(fm, 0xff, m_nBackgroundWidth * m_nBackgroundHeight);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCGlimHomeworkDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCGlimHomeworkDlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	if (IsIconic())
	{
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
		m_imgBackground.Draw(dc, 0, 0);
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCGlimHomeworkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCGlimHomeworkDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	UpdateData(true);
	m_bMouseClicked = true;
	
	if (m_vecCirclePoints.size() < 3) {

		DrawCircle(m_nRadius, point, GRAY);
		AddCirclePointToList(point);
		m_vecCirclePoints.push_back(point);
		
		if (m_vecCirclePoints.size() == 3) {
			CalculateCircleFrom3Points(m_vecCirclePoints);
			for (int i = 0; i < m_vecCirclePoints.size(); i++) {
				DrawCircle(m_nRadius, m_vecCirclePoints[i], GRAY);
			}
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CMFCGlimHomeworkDlg::OnBnClickedBtnClear()
{
	m_lstCirclePoints.ResetContent();
	m_vecCirclePoints.clear();
	ClearDisplay();
}


void CMFCGlimHomeworkDlg::ClearDisplay() 
{
	unsigned char* fm = (unsigned char*)m_imgBackground.GetBits();
	memset(fm, 0xff, m_nBackgroundWidth * m_nBackgroundHeight);
		
	Invalidate(FALSE);
}

void CMFCGlimHomeworkDlg::CalculateCircleFrom3Points(std::vector<CPoint> points) {
	
	UpdateData(true);

	if (points.size() < 3)
		return;

	CPoint pt1 = points[0];
	CPoint pt2 = points[1];
	CPoint pt3 = points[2];

	double A = pt2.x - pt1.x;
	double B = pt2.y - pt1.y;
	double C = pt3.x - pt1.x;
	double D = pt3.y - pt1.y;

	double E = A * (pt1.x + pt2.x) + B * (pt1.y + pt2.y);
	double F = C * (pt1.x + pt3.x) + D * (pt1.y + pt3.y);
	double G = 2.0 * (A * (pt3.y - pt2.y) - B * (pt3.x - pt2.x));

	if (G == 0)
		return;		

	double cx = (D * E - B * F) / G;
	double cy = (A * F - C * E) / G;

	CPoint ptCenter = CPoint((int)cx, (int)cy);
	int nRadius = sqrt((pt1.x - cx)*(pt1.x - cx) + (pt1.y - cy)*(pt1.y - cy));

	DrawHollowCircle(nRadius + m_nCircleThickness/2, nRadius - m_nCircleThickness/2, ptCenter, BLACK);
}


void CMFCGlimHomeworkDlg::DrawCircle(int radius, CPoint center, int color) {

	int nPitch = m_imgBackground.GetPitch();

	unsigned char* fm = (unsigned char*)m_imgBackground.GetBits();

	int nWidth  = m_imgBackground.GetWidth();
	int nHeight = m_imgBackground.GetHeight();

	int nStartX = max(center.x - radius, 0);
	int nEndX   = min(center.x + radius, nWidth - 1);
	int nStartY = max(center.y - radius, 0);
	int nEndY   = min(center.y + radius, nHeight - 1);


	for (int j = nStartY; j < nEndY; j++) {
		for (int i = nStartX; i < nEndX; i++) {
			int nDx = i - center.x;
			int nDy = j - center.y;

			if (nDx * nDx + nDy * nDy <= radius * radius)
					fm[j * nPitch + i] = color;
		}
	}

	Invalidate(FALSE);
}


bool CMFCGlimHomeworkDlg::isInCircle(CPoint point) {
	int nDx = 0;
	int nDy = 0;

	for (int i = 0; i < m_vecCirclePoints.size(); i++) {
		nDx = m_vecCirclePoints[i].x - point.x;
		nDy = m_vecCirclePoints[i].y - point.y;

		if (m_nRadius * m_nRadius >= nDx*nDx + nDy*nDy)
			return true;
	}
	return false;
}

void CMFCGlimHomeworkDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bMouseClicked && isInCircle(point) && !m_vecCirclePoints.empty()) {
		int nIndex = GetClickedCircleIndex(point);

		if (nIndex > -1) {
			ClearDisplay();
			m_vecCirclePoints[nIndex].x = point.x;
			m_vecCirclePoints[nIndex].y = point.y;

			CalculateCircleFrom3Points(m_vecCirclePoints);

			for (int i = 0; i < m_vecCirclePoints.size(); i++) 
				DrawCircle(m_nRadius, m_vecCirclePoints[i], GRAY);
			UpdateCirclePointsList();
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CMFCGlimHomeworkDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bMouseClicked)
		m_bMouseClicked = false;

	CDialogEx::OnLButtonUp(nFlags, point);
}

int CMFCGlimHomeworkDlg::GetClickedCircleIndex(CPoint point) {
	
	int nDx = 0;
	int nDy = 0;

	for (int i = 0; i < m_vecCirclePoints.size(); i++) {
		nDx = m_vecCirclePoints[i].x - point.x;
		nDy = m_vecCirclePoints[i].y - point.y;

		if (m_nRadius * m_nRadius >= nDx*nDx + nDy*nDy)
			return i;
		
	}
	return -1;
}


void CMFCGlimHomeworkDlg::DrawHollowCircle(int radiusOuter, int radiusInner, CPoint center, int color)
{
	if (m_imgBackground.IsNull()) 
		return;

	int nPitch = m_imgBackground.GetPitch();
	unsigned char* fm = (unsigned char*)m_imgBackground.GetBits();

	int nWidth  = m_imgBackground.GetWidth();
	int nHeight = m_imgBackground.GetHeight();

	int nStartX = max(center.x - radiusOuter, 0);
	int nEndX   = min(center.x + radiusOuter, nWidth - 1);
	int nStartY = max(center.y - radiusOuter, 0);
	int nEndY   = min(center.y + radiusOuter, nHeight - 1);

	for (int j = nStartY; j < nEndY; j++) {
		for (int i = nStartX; i < nEndX; i++) {
			int dx = i - center.x;
			int dy = j - center.y;
			if (dx * dx + dy * dy <= radiusOuter * radiusOuter && dx * dx + dy * dy >= radiusInner * radiusInner) {
				fm[j * nPitch + i] = color;
			}
		}
	}
}


void CMFCGlimHomeworkDlg::AddCirclePointToList(CPoint point) {

	m_szCirclePoints.Format(L"X = %d, Y = %d", point.x, point.y);
	m_lstCirclePoints.AddString(m_szCirclePoints);

}


void CMFCGlimHomeworkDlg::UpdateCirclePointsList() {
	
	if (m_vecCirclePoints.empty())
		return;

	m_lstCirclePoints.ResetContent();
	for (int i = 0; i < m_vecCirclePoints.size(); i++) {
		m_szCirclePoints.Format(L"X = %d, Y = %d", m_vecCirclePoints[i].x, m_vecCirclePoints[i].y);
		m_lstCirclePoints.AddString(m_szCirclePoints);
	}

	return;
}

void CMFCGlimHomeworkDlg::OnBnClickedBtnRandom()
{
	if (m_vecCirclePoints.size() < 3) {
		MessageBox(L"세 점을 클릭해주세요.", L"경고", MB_ICONWARNING | MB_OK);
		return;
	}

	UpdateData(TRUE);

	if (m_vecCirclePoints.size() != 3)
		return;

	AfxBeginThread(ThreadDrawRandomCircle, this);
}


UINT CMFCGlimHomeworkDlg::ThreadDrawRandomCircle(LPVOID pParam)
{
	CMFCGlimHomeworkDlg* pDlg = (CMFCGlimHomeworkDlg*)pParam;

	for (int i = 0; i < 10; i++) {
		if (!pDlg) break;

		for (int j = 0; j < pDlg->m_vecCirclePoints.size(); j++) {
			CPoint pt(rand() % pDlg->m_nBackgroundWidth, rand() % pDlg->m_nBackgroundHeight);
			pDlg->m_vecCirclePoints[j] = pt;
		}

		pDlg->PostMessage(WM_THREAD_UPDATE, 0, 0);
		Sleep(500); 
	}
	return 0;
}

LRESULT CMFCGlimHomeworkDlg::OnThreadUpdate(WPARAM wParam, LPARAM lParam)
{
	ClearDisplay();

	if (m_vecCirclePoints.size() == 3) {
		CalculateCircleFrom3Points(m_vecCirclePoints);

		for (int i = 0; i < m_vecCirclePoints.size(); i++)
			DrawCircle(m_nRadius, m_vecCirclePoints[i], GRAY);
		UpdateCirclePointsList();
	}
	return 0;
}
