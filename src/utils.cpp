#include "utils.hpp"

namespace Utils
{
    BOOL SelfDelete()
    {
        // Load required function.
        HMODULE hKernel32 = LoadLibraryA("kernel32.dll");
        if (!hKernel32)
        {
            printf("kernel32.dll not found.\n");
            return FALSE;
        }
        SETFILEINFORMATIONBYHANDLE pSetFileInformationByHandle = reinterpret_cast<SETFILEINFORMATIONBYHANDLE>(GetProcAddress(hKernel32, "SetFileInformationByHandle"));
        if (!pSetFileInformationByHandle) {
            printf("SetFileInformationByHandle is not found.\n");
            return FALSE;
        }

        // Change this executable information
        LPCWSTR lpNewStream = L":null";
        SIZE_T dwStreamLength = wcslen(lpNewStream) * sizeof(wchar_t);
        SIZE_T dwRenameLength = sizeof(FILE_RENAME_INFO) + dwStreamLength;

        PFILE_RENAME_INFO pRenameInfo = (PFILE_RENAME_INFO)HeapAlloc(
            GetProcessHeap(),
            HEAP_ZERO_MEMORY,
            dwRenameLength
        );
        if (!pRenameInfo)
        {
            return FALSE;
        }

        WCHAR wPath[MAX_PATH * 2] = {0};
        FILE_DISPOSITION_INFO fdi = {0};

        RtlZeroMemory(wPath, sizeof(wPath));
        RtlZeroMemory(&fdi, sizeof(FILE_DISPOSITION_INFO));

        fdi.DeleteFile = TRUE;

        pRenameInfo->FileNameLength = dwStreamLength;
        RtlCopyMemory(pRenameInfo->FileName, lpNewStream, dwStreamLength);

        // Get the path for the current executable itself.
        if (GetModuleFileNameW(NULL, wPath, MAX_PATH * 2) == 0)
        {
            return FALSE;
        }

        // Rename
        HANDLE hFile;
        hFile = CreateFileW(
            wPath,
            DELETE | SYNCHRONIZE,
            FILE_SHARE_READ,
            nullptr,
            OPEN_EXISTING,
            0,
            nullptr
        );
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return FALSE;
        }

        // Rename the data stream
        if (!pSetFileInformationByHandle(hFile, FileRenameInfo, pRenameInfo, dwRenameLength))
        {
            return FALSE;
        }

        CloseHandle(hFile);

        // Delete
        hFile = CreateFileW(
            wPath,
            DELETE | SYNCHRONIZE,
            FILE_SHARE_READ,
            nullptr,
            OPEN_EXISTING,
            0,
            nullptr
        );
        if (hFile == INVALID_HANDLE_VALUE)
        {
            return FALSE;
        }

        if (!pSetFileInformationByHandle(hFile, FileDispositionInfo, &fdi, sizeof(fdi)))
        {
            return FALSE;
        }

        CloseHandle(hFile);
        HeapFree(GetProcessHeap(), 0, pRenameInfo);

        return TRUE;
    }
}
