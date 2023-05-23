#pragma once

#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>

namespace hlib {

	void emptyHandle();
	bool setHandle(HANDLE* pHandle);
	bool isAttached();
	bool isAttachedex(HANDLE* pHandle);
	bool mread(DWORD addr, void* buf);
	bool mwrite(DWORD addr, void* buf);
	bool mreadex(HANDLE* pHandle, DWORD addr, void* buf);
	bool mwriteex(HANDLE* pHandle, DWORD addr, void* buf);
	bool mreadext(unsigned int pid, DWORD addr, void* buf);
	bool mwriteext(unsigned int pid, DWORD addr, void* buf);
	unsigned int getpid(const char* proc);
	bool key(char k1, char k2, const char* id, bool* var);
	bool keyex(char k1, char k2, const char* enmsg, const char* dismsg,
		bool* var, bool isChange);
}

static class vars {
public:
	HANDLE m_pHandle = INVALID_HANDLE_VALUE;
	bool hSet();
}var;