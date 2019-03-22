/*
VMWalker.h: ¡°ÏêÏ¸ÐÅÏ¢¡±ÐéÄâÄÚ´æÒ³Í·ÎÄ¼þ
×÷Õß£º1120151764 ³ÂÄÁÇÇ
*/
//¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª<³ÂÄÁÇÇ>
#pragma once


// VMWalker ¶Ô»°¿ò

class VMWalker : public CDialogEx
{
	DECLARE_DYNAMIC(VMWalker)

public:
	VMWalker(CWnd* pParent = nullptr);   // ±ê×¼¹¹Ôìº¯Êý
	virtual ~VMWalker();

	// ¶Ô»°¿òÊý¾Ý
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VMWALKER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV Ö§³Ö

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString pid;
	CString pname;
	CString psize;
	CEdit m_pid;
	CEdit m_pname;
	CEdit m_psize;
	CListCtrl m_list_vmwalker;
	void AddItem(TCHAR* startAddtrss, TCHAR* endAddress, TCHAR* size,
		TCHAR* state, TCHAR* protection, TCHAR* type, TCHAR* name);
	void WalkVM(HANDLE hProcess);
	DWORD GetProcessidFromName(LPCTSTR name);
};
//¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª</³ÂÄÁÇÇ>