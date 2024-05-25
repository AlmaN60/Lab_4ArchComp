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
