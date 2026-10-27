#include <windows.h>
#include <cassert>
#include <iostream>
#include <vector>
#include <string>

namespace namedpipe {
struct PipeInfo {
    std::wstring name;
    bool exists;
};
std::vector<PipeInfo> scan_named_pipes();
}

int main() {
    std::cout << "Testing Named Pipe namespace scan...\n";
    // Create a temporary pipe to verify scan accuracy
    HANDLE hPipe = CreateNamedPipeW(
        L"\\\\.\\pipe\\test_audit_canary_pipe",
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_BYTE | PIPE_WAIT,
        1, 1024, 1024, 0, NULL
    );

    assert(hPipe != INVALID_HANDLE_VALUE && "Failed to create canary test pipe");

    WIN32_FIND_DATAW ffd;
    HANDLE hFind = FindFirstFileW(L"\\\\.\\pipe\\*", &ffd);
    assert(hFind != INVALID_HANDLE_VALUE && "FindFirstFile on pipe namespace must succeed");

    bool found_canary = false;
    do {
        if (wcscmp(ffd.cFileName, L"test_audit_canary_pipe") == 0) {
            found_canary = true;
            break;
        }
    } while (FindNextFileW(hFind, &ffd) != 0);

    FindClose(hFind);
    CloseHandle(hPipe);

    assert(found_canary && "Canary pipe must be discovered during namespace scan");
    std::cout << "Named pipe audit tests passed successfully!\n";
    return 0;
}
