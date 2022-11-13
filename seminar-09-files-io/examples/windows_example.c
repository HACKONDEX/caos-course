#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
// #include </usr/share/mingw-w64/include/winbase.h> // For CLion indexing

int main() {
    HANDLE fileHandle = CreateFileA(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    DWORD bytes_read;
    BOOL success;

    char buffer[256];

    success = ReadFile(fileHandle, buffer, 5,
                           &bytes_read, NULL);

    LARGE_INTEGER offset;
    offset.QuadPart = 11;
    success = SetFilePointerEx(fileHandle, offset, NULL, FILE_BEGIN);

    CloseHandle(fileHandle);
    return 0;
}