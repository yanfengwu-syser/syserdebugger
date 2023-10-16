#ifndef _CODE_CONFIG_H_
#define _CODE_CONFIG_H_

//操作系统选择
//CODE_OS_WIN		Window应用程序
//CODE_OS_NT_DRV	Window NT驱动程序
//CODE_OS_UNIX		UNIX家族

#define _CRT_SECURE_NO_WARNINGS //VC8安全库警告

#ifdef	WIN32
#ifndef CODE_OS_NT_DRV
#define CODE_OS_WIN
#endif
#else	//WIN32
#ifndef CODE_OS_CATOS
#define CODE_OS_UNIX
#endif
#endif

#define CODE_INT_BYTES		4

#ifndef CODE_OS_WIN
#ifndef CODE_OS_NT_DRV
///////////////////////////////////////////
//大字节序
#define CODE_BIG_ENDIAN
///////////////////////////////////////////

///////////////////////////////////////////
//存在Bus对齐问题
#define CODE_BUS_ALIGN

///////////////////////////////////////////
//存在对齐问题的结构自动按指定字节对齐
//#define CODE_ST_PACK
///////////////////////////////////////////
#endif //not define CODE_OS_NT_DRV
#endif //not define CODE_OS_WIN

///////////////////////////////////////////
//可变参数定义
//#define CODE_VA_DEFINE

///////////////////////////////////////////
//UNIX下是否使用线程相关函数
//#define CODE_UNIX_THREAD
///////////////////////////////////////////

///////////////////////////////////////////
//调试内存泄漏
//#define CODE_DEBUG_ALLOC
///////////////////////////////////////////

///////////////////////////////////////////
//重载内存分配
//#define CODE_ALLOC_OVERLOAD
///////////////////////////////////////////

///////////////////////////////////////////
//使用CFixedHeap对象管理内存分配
//#define CODE_ALLOC_USER_HEAP					30*0x100000
//#define CODE_ALLOC_USER_HEAP_FREE_CHECK			//释放内存时检查内存边界标志是否完整，来检测内存溢出
//#define CODE_ALLOC_USER_HEAP_OVERFLOW_OUTPUT
//#define CODE_ALLOC_USER_HEAP_DEBUG_BREAK
///////////////////////////////////////////

////////////////////////////////////////////
//#define CODE_USE_NAME_SPACE
//使用code名字空间
////////////////////////////////////////////

///////////////////////////////////////////
//宏依赖关系修正 don't modify
///////////////////////////////////////////
#ifdef	CODE_USE_NAME_SPACE
#define NAME_SPACE				code
#define NAME_SPACE_BEGIN			namespace	NAME_SPACE{
#define NAME_SPACE_END				}
#else
#define NAME_SPACE
#define NAME_SPACE_BEGIN
#define NAME_SPACE_END
#endif

#ifdef	CODE_ALLOC_USER_HEAP
#define CODE_ALLOC_OVERLOAD
#endif

#ifndef CODE_VA_DEFINE
#ifdef  CODE_OS_NT_DRV
#define CODE_VA_DEFINE
#endif
#endif

///////////////////////////////////////////
//宏依赖关系修正
///////////////////////////////////////////


#endif
