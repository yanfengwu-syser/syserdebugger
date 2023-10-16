#ifndef _WISP_FILE_WND_H_
#define _WISP_FILE_WND_H_

#include "WispSplitWnd.h"
#include "WispListTree.h"

enum FILE_WND_ID
{
	ID_FOLDER_TREE, ID_FOLDER_LIST
};
class CWispFileWnd :
	public CWispSplitWnd
{
public:
	CWispFileWnd(void);
	virtual ~CWispFileWnd(void);

	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnCreate);
	DECLARE_WISP_MSG(OnCommand);

	int FillFolderTree(CListStringItem* pItem);
	int FillFolderList(CListStringItem* pItem);

protected:
	CWispListTree		m_FolderTree, m_FolderList;
	CWispEdit	m_StatusWnd;
};

#endif//_WISP_FILE_WND_H_
