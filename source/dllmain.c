#include <xanadu-cctl/xanadu.h>


// 动态库入口
#if defined(XANADU_SYSTEM_WINDOWS)
#if defined(__cplusplus)
extern "C"
#else
extern
#endif
BOOL WINAPI DllMain(HANDLE _HDllHandle, DWORD _Reason, LPVOID _Reserved)
{
	XANADU_UNUSED(_HDllHandle);
	XANADU_UNUSED(_Reserved);

	switch(_Reason)
	{
		case DLL_PROCESS_ATTACH:
			break;
		case DLL_PROCESS_DETACH:
			break;
		default:
			break;
	}
	return TRUE;
}
#else
__attribute((constructor)) void xanadu_cctl_dynamic_library_init(void)
{
};

__attribute((destructor)) void xanadu_cctl_dynamic_library_fini(void)
{
};
#endif
