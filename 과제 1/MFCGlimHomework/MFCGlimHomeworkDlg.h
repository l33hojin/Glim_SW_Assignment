
// MFCGlimHomeworkDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include <iostream>
#include <vector>

#define WHITE 0xff
#define BLACK 0x00
#define GRAY 0x60

#define WM_THREAD_UPDATE (WM_USER + 1)

// CMFCGlimHomeworkDlg ��ȭ ����
class CMFCGlimHomeworkDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMFCGlimHomeworkDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCGLIMHOMEWORK_DIALOG };
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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnRandom();

	afx_msg LRESULT OnThreadUpdate(WPARAM wParam, LPARAM lParam);

	void ClearDisplay();

	void CalculateCircleFrom3Points(std::vector<CPoint> points);
	void DrawCircle(int radius, CPoint center, int color);
	void DrawHollowCircle(int radiusOuter, int radiusInner, CPoint center, int color);
	void AddCirclePointToList(CPoint point);
	void UpdateCirclePointsList();

	int GetClickedCircleIndex(CPoint point);

	bool isInCircle(CPoint point);

	static UINT ThreadDrawRandomCircle(LPVOID pParam);

	CImage m_imgBackground;
	CString m_szCirclePoints;
	CListBox m_lstCirclePoints;

	int m_nCircleThickness;
	int m_nRadius;
	int m_nBackgroundWidth;
	int m_nBackgroundHeight;
	int m_nBackgroundBpp;

	bool m_bMouseClicked;

	std::vector<CPoint> m_vecCirclePoints;
};
