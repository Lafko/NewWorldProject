#pragma once
#include "xor.h"
#include <TlHelp32.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "xor.h"
#include <cassert>
#include <intrin.h>

using namespace std;

typedef struct _UNICODE_STRING2 {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING2;
typedef UNICODE_STRING2* PUNICODE_STRING2;
typedef const UNICODE_STRING2* PCUNICODE_STRING2;

typedef struct _OBJECT_ATTRIBUTES2 {
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING2 ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor;
    PVOID SecurityQualityOfService;
} OBJECT_ATTRIBUTES2;
typedef OBJECT_ATTRIBUTES2* POBJECT_ATTRIBUTES2;

typedef NTSTATUS(NTAPI* lpNtCreateThreadEx)(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES2, HANDLE, LPTHREAD_START_ROUTINE, LPVOID, ULONG, ULONG_PTR, SIZE_T, SIZE_T, LPVOID);
typedef NTSTATUS(NTAPI* lpNtQueryInformationThread)(HANDLE, LONG, PVOID, ULONG, PULONG);

DWORD CreateThreadProtected(HANDLE* hThread2, LPTHREAD_START_ROUTINE ThreadMethud)
{
    //deleted
}

string random_string()
{
    srand((unsigned int)time((time_t*)0));
    string str = ("QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890");
    string newstr;
    int pos;
    while (newstr.size() != 5)
    {
        pos = ((rand() % (str.size() + 1)));
        newstr += str.substr(pos, 1);
    }
    return newstr;
}

string get_files_directory_s()
{
    //deleted
}

string get_random_file_name_directory(string type_file)
{
    string sz_file = get_files_directory_s() + random_string() + type_file;
    return sz_file;
}

bool drop_file(string path, int resId, string lpType)
{
    HRSRC RES_HRSRC = FindResourceA(NULL, MAKEINTRESOURCEA(resId), lpType.c_str());
    if (RES_HRSRC)
    {
        HGLOBAL hRes = LoadResource(NULL, RES_HRSRC);
        PVOID pDriverData = LockResource(hRes);
        HANDLE hFile = CreateFileA(path.c_str(), FILE_GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);

        if (hFile != INVALID_HANDLE_VALUE)
        {
            DWORD bytes = 0;
            WriteFile(hFile, pDriverData, SizeofResource(NULL, RES_HRSRC), &bytes, NULL);
            CloseHandle(hFile);
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

void run_us_admin_and_params(string sz_exe, string sz_params, bool show)
{
    ShellExecuteA(NULL, "runas", sz_exe.c_str(), sz_params.c_str(), NULL, show);
}

bool LoadDriverKmemNew()
{
    string sz_mapper = get_random_file_name_directory(".exe");
    string sz_driver = get_random_file_name_directory(".sys");
    string sz_params = " --mdl " + sz_driver;

    if (drop_file(sz_driver, 170, "SYS"))
    {
        if (drop_file(sz_mapper, 171, "EXE"))
        {
            run_us_admin_and_params(sz_mapper, sz_params, false);
        loop:
            Sleep(5);
            try {
               
               filesystem::remove(sz_mapper);
               filesystem::remove(sz_driver);
            }
            catch (const filesystem::filesystem_error& err)
            {
                goto loop;
            }
            return true;
        }
    }
    return false;
}

LONG guard_handler(_EXCEPTION_POINTERS* ExceptionInfo)
{
    std::ofstream myfile("error_log.txt");
    if (myfile.is_open())
    {
        myfile << "ExceptionAddress " << ExceptionInfo->ExceptionRecord->ExceptionAddress << "\n";
        myfile << "ExceptionFlags " << ExceptionInfo->ExceptionRecord->ExceptionFlags << "\n";
        myfile << "EFlags " << ExceptionInfo->ContextRecord->EFlags << "\n";

        for (auto ExceptionInformation : ExceptionInfo->ExceptionRecord->ExceptionInformation)
        {
            myfile << "ExceptionInformation " << ExceptionInformation << "\n";
        }

        myfile.close();
    }
    return EXCEPTION_CONTINUE_SEARCH;
}

LPCSTR ProcessIdToName(DWORD processId)
{
    LPCSTR ret = "NULL";
    HANDLE handle = OpenProcess(
        PROCESS_QUERY_LIMITED_INFORMATION,
        FALSE,
        processId /* This is the PID, you can find one from windows task manager */
    );
    if (handle)
    {
        DWORD buffSize = 1024;
        CHAR buffer[1024];
        if (QueryFullProcessImageNameA(handle, 0, buffer, &buffSize))
        {
            ret = buffer;
        }
        else
        {
            //printf("Error GetModuleBaseNameA : %lu", GetLastError());
        }
        CloseHandle(handle);
    }
    else
    {
        //printf("Error OpenProcess : %lu", GetLastError());
    }
    return ret;
}

string convertToString(char* a, int size)
{
	int i;
	string s = "";
	for (i = 0; i < size; i++) {
		s = s + a[i];
	}
	return s;
}