#include <iostream>
#include <memory>
#include <cstdio>

// 1. 定義一個刪除器結構（可以是仿函式 Functor、函式指標或 Lambda）
struct FileDeleter {
    void operator()(FILE* fp) const {
        if (fp) {
            std::cout << "[Deleter] Closing file automatically...\n";
            fclose(fp);
        }
    }
};

int main() {
    // unique_ptr<FILE, FileDeleter> stores a FILE*; FileDeleter is the
    // deleter type, called later with that FILE* when filePtr is destroyed.
    // fopen returns FILE*, so it can initialize the pointer being managed.
    std::unique_ptr<FILE, FileDeleter> filePtr(fopen("test.txt", "w"));

    if (filePtr) {
        std::fputs("Hello, RAII C++!", filePtr.get());
        std::cout << "Wrote to file successfully.\n";
    }

    // 3. 離開作用域時，FileDeleter 會自動被呼叫，確保檔案一定會關閉！
    return 0;
}
