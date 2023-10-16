/**
 * @file pcreplus.h
 * @brief Wrapper classes for PCRE using C++
 * @author Simon Steele
 * @note Copyright (c) 2002-2003 Simon Steele <s.steele@pnotepad.org>
 *
 * Programmers Notepad 2 : The license file (license.[txt|html]) describes 
 * the conditions under which this source may be modified / distributed.
 *
 * This code uses PCRE to provide regular expressions support - see pcre_license.txt.
 */

#ifndef pcreplus_h__included
#define pcreplus_h__included

#define PCRE_STATIC

//extern "C" {
	#include "..\..\..\Pcre\Source\Pcre.h"
//}

#ifndef PCRE_DEFAULT_FLAGS
	#ifndef PCRE_NO_UTF8
		#define PCRE_DEFAULT_FLAGS	PCRE::RegExp::UTF8
	#else
		#define PCRE_DEFAULT_FLAGS 0
	#endif
#endif

namespace PCRE
{

class RegExp
{
	public:
		RegExp();
		RegExp(const char* expression, int flags = -1);
		~RegExp();

		void Compile(const char* expression, int flags = -1);

		void Study();
		
		bool Match(const char* str, int offset = 0);
		bool Match(const char* str, int length, int offset);

		bool GetNamedMatch(const char* name, char** str);

		enum {
			Anchored		= PCRE_ANCHORED,
			CaseInsensitive = PCRE_CASELESS,
			DollarEndOnly	= PCRE_DOLLAR_ENDONLY,	// Dollar matches do not include newlines.
			DotMatchesAll	= PCRE_DOTALL,			// Include newlines in . matches
			Extended		= PCRE_EXTENDED,		// Ignore unescaped whitespace in pattern.
			MultiLine		= PCRE_MULTILINE,
			NoAutoCapture	= PCRE_NO_AUTO_CAPTURE,	// Disable numbered capturing parentheses.
			UnGreedy		= PCRE_UNGREEDY,		// Invert operator greediness.
			UTF8			= PCRE_UTF8,			// Enable UTF-8 Support.
		};

	protected:
		void clear();
		void compile(const char* expression, int flags);
		bool match(const char* str, int length, int offset, int flags);

	protected:
		pcre*		m_pRE;
		pcre_extra*	m_pStudyData;
		const char*	m_strmatch;
		int			m_strmatchlen;
		int			m_lastResult;
		int*		m_pSubStringVector;
		int			m_nCaptureGroups;
};

/**
 * @brief Exception class used by RegExp
 */
class REException
{
	public:
		REException(const char* message, int offset = -1);
		REException(int errCode);
		REException(const REException& copy);
		~REException();
		void set(const char* message, int offset = -1);
		const char* GetMessage();
		int GetOffset();
	protected:
		char*	m_pMsg;
		int		m_offset;
};

} // namespace PCRE

#endif