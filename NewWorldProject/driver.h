#pragma once

//deleted

DWORD GamePid;
DWORD64 BaseAddr;
#define STATUS_SUCCESS                   ((NTSTATUS)0x00000000L)    // ntsubauth

typedef struct _SYSCALL_DATA
{
	int Id;
	int Pid;
	PVOID Arg1;
	PVOID Arg2;
	int Status;
} SYSCALL_DATA, * PSYSCALL_DATA;

NTSTATUS(*TEST)(PVOID, PVOID, PVOID, PVOID, PVOID, PVOID, PVOID);

int DoSyscall(DWORD syscall, PVOID* Argument1, PVOID* Argument2, DWORD Pid)
{
	SYSCALL_DATA data = { 0 };

	data.Id = syscall;
	data.Arg1 = Argument1;
	data.Arg2 = Argument2;
	data.Pid = Pid;

	TEST(&data, (PVOID)1, (PVOID)2, (PVOID)3, (PVOID)4, (PVOID)5, (PVOID)6);
	if (data.Arg1)
	{
		*Argument1 = data.Arg1;
	}
	if (data.Arg2)
	{
		*Argument2 = data.Arg2;
	}
	return data.Status;

}

bool SetupSyscalls()
{
	auto win32u = skCrypt("win32u.dll");
	HMODULE module = LoadLibraryA(win32u);
	win32u.clear();
	if (!module)
	{
		auto gdi32full = skCrypt("gdi32full.dll");
		module = LoadLibraryA(gdi32full);
		gdi32full.clear();
		if (!module)
		{
			return false;
		}
		return false;
	}
	auto sTEST = skCrypt("TEST");
	*(PVOID*)&TEST = GetProcAddress(module, sTEST);
	sTEST.clear();
	if (DoSyscall(99996, 0, 0, 0) == 1)
	{
		return true;
	}
	return false;
}

bool protect_process_by_hook(int pid)
{
	if (DoSyscall(99999, 0, 0, pid) == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Init()
{
	if (SetupSyscalls())
	{
		if (DoSyscall(99996, 0, 0, 0) == 1)
		{
			return true;
		}
	}
	return false;
}

DWORD64 get_baseaddr(int pid)
{
	DWORD64 Base = 0;
	DoSyscall(99997, (PVOID*)&Base, 0, pid);
	return Base;
}

void get_thread(HWND window_handle, DWORD64* thread_context)
{
	SYSCALL_DATA data = { 0 };

	data.Id = 99994;
	data.Arg1 = (PVOID)window_handle;
	data.Arg2 = (PVOID)thread_context;
	data.Pid = 0;
	TEST(&data, (PVOID)1, (PVOID)2, (PVOID)3, (PVOID)4, (PVOID)5, (PVOID)6);
	*thread_context = (DWORD64)data.Arg2;
}

void set_thread(HWND window_handle, DWORD64 thread_context)
{
	SYSCALL_DATA data = { 0 };

	data.Id = 99993;
	data.Arg1 = (PVOID)window_handle;
	data.Arg2 = (PVOID)thread_context;
	data.Pid = 0;

	TEST(&data, (PVOID)1, (PVOID)2, (PVOID)3, (PVOID)4, (PVOID)5, (PVOID)6);
}

template<typename T> T read(SIZE_T address)
{
	T buff;
	SYSCALL_DATA data = { 0 };

	data.Id = 99990;
	data.Arg1 = reinterpret_cast<PVOID>(address);
	data.Arg2 = reinterpret_cast<PVOID>(&buff);
	data.Pid = GamePid;
	data.Status = sizeof(T);

	TEST(&data, (PVOID)1, (PVOID)2, (PVOID)3, (PVOID)4, (PVOID)5, (PVOID)6);
	return buff;
}

template<typename T> T write(SIZE_T address, const T& buff)
{
	SYSCALL_DATA data = { 0 };

	data.Id = 99998;
	data.Arg1 = reinterpret_cast<PVOID>(address);
	data.Arg2 = (PVOID)(&buff);
	data.Pid = GamePid;
	data.Status = sizeof(T);
	TEST(&data, (PVOID)1, (PVOID)2, (PVOID)3, (PVOID)4, (PVOID)5, (PVOID)6);
	return buff;
}

#define WriteFloat(addr, buff)write<float>(addr, buff)
#define WriteVector(addr, buff)write<FVector>(addr, buff)
#define WriteByte(addr, buff)write<BYTE>(addr, buff)

#define ReadInteger(addr)read<int>(addr)
#define ReadFloat(addr)read<float>(addr)
#define READV(addr)read<FVector>(addr)
#define RPMFT(addr)read<FTransform>(addr)
#define READR(addr)read<FRotator>(addr)
#define READB(addr)read<BYTE>(addr)
#define READ32(addr)read<DWORD>(addr)
#define READ64(addr)read<DWORD64>(addr)
#define RPMDPTR(addr)read<DWORD_PTR>(addr)

#define READS(src,dest,size)																				\
		SYSCALL_DATA data = { 0 };																			\
		data.Id = 99990;																					\
		data.Arg1 = (PVOID)(src);																			\
		data.Arg2 = (PVOID)(&dest);																			\
		data.Pid = GamePid;																					\
		data.Status = sizeof(size);																			\
		TEST(&data, (PVOID)1, (PVOID)2, (PVOID)3, (PVOID)4, (PVOID)5, (PVOID)6);			