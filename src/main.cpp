#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

namespace namedpipe {

struct PipeInfo {
    std::wstring name;
    bool exists;
};

std::vector<PipeInfo> scan_named_pipes() {
    std::vector<PipeInfo> pipes;
    WIN32_FIND_DATAW ffd;
    HANDLE hFind = FindFirstFileW(L"\\\\.\\pipe\\*", &ffd);

    if (hFind == INVALID_HANDLE_VALUE) {
        return pipes;
    }

    do {
        if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            pipes.push_back({ffd.cFileName, true});
        }
    } while (FindNextFileW(hFind, &ffd) != 0);

    FindClose(hFind);
    return pipes;
}

}

int main() {
    std::wcout << L"[NamedPipe-Audit] Windows Named Pipe IPC Security Auditor\n";
    std::wcout << L"Querying \\\\.\\pipe\\* namespace for exposed IPC endpoints...\n\n";

    auto pipes = namedpipe::scan_named_pipes();
    std::wcout << L"Discovered " << pipes.size() << L" active Named Pipes on the system:\n\n";
    std::wcout << L"PIPE NAME\n";
    std::wcout << L"----------------------------------------------------\n";

    for (size_t i = 0; i < (pipes.size() < 15 ? pipes.size() : 15); ++i) {
        std::wcout << L"\\\\.\\pipe\\" << pipes[i].name << L" [ACTIVE]\n";
    }

    return pipes.empty() ? 1 : 0;
}
