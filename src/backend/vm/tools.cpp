#include "../../base.cpp"
#if defined(__linux__) || defined(__APPLE__)
#include <sys/mman.h>
#endif
namespace vm {
    void execute(std::vector<uint8_t>&& code) {
        using func_type = void(*)();
        #if defined(__linux__) || defined(__APPLE__)
        auto code_buf = mmap(NULL, code.size(), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
        memcpy(code_buf, code.data(), code.size());
        mprotect(code_buf, code.size(), PROT_READ|PROT_EXEC);
        ((func_type)code_buf)();
        munmap(code_buf, code.size());
        #elif defined(_WIN32)
        auto code_buf = VirtualAlloc(NULL, code.size(), MEM_RESERVE|MEM_TOP_DOWN, PAGE_READWRITE);
        memcpy(code_buf, code.data(), code.size());
        DWORD a;
        VirtualProtect(code_buf, code.size(), PAGE_EXECUTE_READ, &a);
        ((func_type)code_buf)();
        VirtualFree(code_buf, code.size(), MEM_DECOMMIT);
        #else
        #error "wtf system you use"
        #endif
    }
};