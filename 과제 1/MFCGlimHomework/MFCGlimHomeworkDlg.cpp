
// MFCGlimHomeworkDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MFCGlimHomework.h"
#include "MFCGlimHomeworkDlg.h"
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


// CMFCGlimHomeworkDlg ��ȭ ����



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


// CMFCGlimHomeworkDlg �޽��� ó����

BOOL CMFCGlimHomeworkDlg::OnInitDialog()
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

	m_imgBackground.Create(m_nBackgroundWidth, -m_nBackgroundHeight, m_nBackgroundBpp);

	if (m_nBackgroundBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_imgBackground.SetColorTable(0, 256, rgb);
	}

	unsigned char* fm = (unsigned char*)m_imgBackground.GetBits();
	memset(fm, 0xff, m_nBackgroundWidth * m_nBackgroundHeight);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMFCGlimHomeworkDlg::OnPaint()
{
	CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

	if (IsIconic())
	{
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
		m_imgBackground.Draw(dc, 0, 0);
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
		MessageBox(L"�� ���� Ŭ�����ּ���.", L"���", MB_ICONWARNING | MB_OK);
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
