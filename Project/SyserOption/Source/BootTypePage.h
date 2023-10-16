#ifndef _BOOT_TYPE_PAGE_H_
#define _BOOT_TYPE_PAGE_H_



class CBootTypePage : public CWispForm
{
public:
	CBootTypePage();
	~CBootTypePage();
public:
	DECLARE_WISP_MSG_MAP
	DECLARE_WISP_MSG(OnFormCreate)
public:
	static WISP_FORM_RES_ITEM m_FormRes[];
};

#endif
