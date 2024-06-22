#ifndef UTILS_HPP
#define UTILS_HPP

#include <windows.h>
#include <stdio.h>

namespace Utils
{
    typedef enum _FILE_INFO_BY_HANDLE_CLASS {
        FileBasicInfo,
        FileStandardInfo,
        FileNameInfo,
        FileRenameInfo,
        FileDispositionInfo,
        FileAllocationInfo,
        FileEndOfFileInfo,
        FileStreamInfo,
        FileCompressionInfo,
        FileAttributeTagInfo,
        FileIdBothDirectoryInfo,
        FileIdBothDirectoryRestartInfo,
        FileIoPriorityHintInfo,
        FileRemoteProtocolInfo,
        FileFullDirectoryInfo,
        FileFullDirectoryRestartInfo,
        FileStorageInfo,
        FileAlignmentInfo,
        FileIdInfo,
        FileIdExtdDirectoryInfo,
        FileIdExtdDirectoryRestartInfo,
        FileDispositionInfoEx,
        FileRenameInfoEx,
        FileCaseSensitiveInfo,
        FileNormalizedNameInfo,
        MaximumFileInfoByHandleClass
    } FILE_INFO_BY_HANDLE_CLASS, *PFILE_INFO_BY_HANDLE_CLASS;

    typedef struct _FILE_RENAME_INFO {
        union {
            BOOLEAN ReplaceIfExists;
            DWORD   Flags;
        } DUMMYUNIONNAME;
        // BOOLEAN ReplaceIfExists;
        HANDLE  RootDirectory;
        DWORD   FileNameLength;
        WCHAR   FileName[1];
    } FILE_RENAME_INFO, *PFILE_RENAME_INFO;

    typedef struct _FILE_DISPOSITION_INFO {
        BOOLEAN DeleteFile;
    } FILE_DISPOSITION_INFO, *PFILE_DISPOSITION_INFO;

    typedef BOOL (WINAPI* SETFILEINFORMATIONBYHANDLE)(HANDLE hFile, FILE_INFO_BY_HANDLE_CLASS FileInformationClass, LPVOID lpFileInformation, DWORD dwBufferSize);

    BOOL SelfDelete();
}

#endif // UTILS_HPP