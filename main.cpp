/*
                      Лабораторна робота №4
            Журавський Дмитро Олексійович - Варіант 14
                            ПЗ-23-3
Використовуючи мову програмування високого рівня (Я обрав C++) створити програму, яка виконує наступне:
Варіант 14. Скопіювати файли з каталогу в каталог.
1)Робота з вказаним каталогом (передається як параметр утиліти)
2)Робота з вказаними файлами за шаблоном (наприклад, *.exe) 
3)Розбір та інтерпретація параметрів командного рядка: - змінне число параметрів;
4)Режим підказки:- підтримується;
5)Програма формує коди завершення
6)Програмою враховуються атрибути файлів (прихований, тільки читання, архівний)

*/  
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <cstdlib>

#if __has_include(<filesystem>)
    #include <filesystem>
    namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#else
    #error "Neither <filesystem> nor <experimental/filesystem> is available."
#endif

void print_help() {
    std::cout << "Usage: filecopy [options] <source_dir> <dest_dir> <pattern>\n";
    std::cout << "Options:\n";
    std::cout << "  -h, --help      Show this help message\n";
}

bool match_pattern(const std::string& filename, const std::string& pattern) {
    std::regex regex_pattern(pattern);
    return std::regex_match(filename, regex_pattern);
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        print_help();
        return 1; //  error code 1: Not enough arguments
    }

    std::vector<std::string> args(argv, argv + argc);
    std::string source_dir;
    std::string dest_dir;
    std::string pattern;

    for (const auto& arg : args) {
        if (arg == "-h" || arg == "--help") {
            print_help();
            return 0; // help shown, normal exit
        }
    }

    source_dir = args[argc - 3];
    dest_dir = args[argc - 2];
    pattern = args[argc - 1];

    try {
        fs::create_directories(dest_dir);

        std::cout << "Source Directory: " << source_dir << "\n";
        std::cout << "Destination Directory: " << dest_dir << "\n";
        std::cout << "Pattern: " << pattern << "\n";

        for (const auto& entry : fs::directory_iterator(source_dir)) {
            const auto& path = entry.path();
            if (fs::is_regular_file(path)) {
                std::string filename = path.filename().string();
                if (match_pattern(filename, pattern)) {
                    fs::path dest_path = fs::path(dest_dir) / filename;

                    //checking file attributes
                    auto file_status = fs::status(path);
                    bool is_hidden = (path.filename().string()[0] == '.');
                    bool is_readonly = (file_status.permissions() & fs::perms::owner_write) == fs::perms::none;
                    bool is_archive = (file_status.permissions() & fs::perms::owner_exec) != fs::perms::none;

                    std::cout << "Copying: " << filename << "\n";
                    std::cout << "Attributes - Hidden: " << is_hidden 
                              << ", Read-only: " << is_readonly 
                              << ", Archive: " << is_archive << "\n";

                    // Copy the file
                    fs::copy(path, dest_path, fs::copy_options::overwrite_existing);

                    // Set attributes
                    if (is_readonly) {
                        fs::permissions(dest_path, fs::perms::owner_write, fs::perm_options::remove);
                    }
                    if (is_archive) {
                        fs::permissions(dest_path, fs::perms::owner_exec, fs::perm_options::add);
                    }
                    std::cout << "Copied: " << filename << "\n";
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 2; // Error code 2: Exception caught
    }

    return 0; // Success
}


/*
Зробив у онлайн компіляторі replit.com (С++)

/.................Крок 1.................\

1.1 Написав код у main.cpp

\.................Крок 1................./

///////////////////////////////////////////

/.................Крок 2.................\

2.1 у файлі Makefile написав

{ pkgs }: 
{
  deps = [
    pkgs.gcc
    pkgs.boost
  ];
  shellHook = ''
    export CXXFLAGS="-std=c++17"
  '';
}

\.................Крок 2................./

///////////////////////////////////////////

/.................Крок 3..................                                   1
4.1 Скомпілював програму через термінал (Shell):

g++ -std=c++17 -o filecopy main.cpp

\.................Крок 3................./

///////////////////////////////////////////

/.................Крок 4.................\                                   2

3.1 Використовуючи вбудований термінал Replit, cтворив тестові данні через консоль (Shell):

mkdir source_directory
echo "Test executable content" > source_directory/test1.exe
echo "Another test executable" > source_directory/test2.exe
echo "Not matching file" > source_directory/test.txt 

\.................Крок 4................./

///////////////////////////////////////////

/.................Крок 5.................\
5.1 Запустив через термінал (Shell):

./filecopy source_directory destination_directory ".*\.exe"

\.................Крок 5................./

Результат:
~/Lab4arxhitect$ g++ -std=c++17 -o filecopy main.cpp
~/Lab4arxhitect$ mkdir source_directory
~/Lab4arxhitect$ echo "Test executable content" > source_directory/test1.exe
~/Lab4arxhitect$ echo "Another test executable" > source_directory/test2.exe
~/Lab4arxhitect$ echo "Not matching file" > source_directory/test.txt
~/Lab4arxhitect$ ./filecopy source_directory destination_directory ".*\.exe"
Source Directory: source_directory
Destination Directory: destination_directory
Pattern: .*\.exe
Copying: test1.exe
Attributes - Hidden: 0, Read-only: 0, Archive: 0
Copied: test1.exe
Copying: test2.exe
Attributes - Hidden: 0, Read-only: 0, Archive: 0
Copied: test2.exe

*/