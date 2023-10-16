#ifndef _ALT_CONFIG_HPP_
#define _ALT_CONFIG_HPP_

//ALT config header file
#define ALT_FILE_STREAM			//support file stream
#define ALT_NAME_SPACE			ALT

///////////////////////////////////////////
//∫Í“¿¿µπÿœµ–ﬁ’˝ don't modify
///////////////////////////////////////////
#ifdef	CODE_ASSERT
#define ALT_ASSERT				CODE_ASSERT
#else//	CODE_ASSERT
#ifdef	assert
#define ALT_ASSERT				assert
#endif//assert
#endif//CODE_ASSERT

#ifndef ALT_ASSERT
#define ALT_ASSERT
#endif

#ifdef	ALT_NAME_SPACE
#define ALT_NAME_SPACE_BEGIN	namespace ALT_NAME_SPACE{
#define ALT_NAME_SPACE_END		}
#else
#define ALT_NAME_SPACE_BEGIN
#define ALT_NAME_SPACE_END
#endif


#endif
