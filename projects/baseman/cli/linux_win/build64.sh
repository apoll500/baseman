#!/bin/sh
#-------------------------------------------------------------------------------
echo 'compiling...'
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/csv/csv.cpp -o ../../../../source/csv/csv.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/csv/CsvData.cpp -o ../../../../source/csv/CsvData.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/csv/CsvRecord.cpp -o ../../../../source/csv/CsvRecord.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/csv/CsvField.cpp -o ../../../../source/csv/CsvField.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/settings/settings.cpp -o ../../../../source/settings/settings.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/reader/ReaderImpl.cpp -o ../../../../source/reader/ReaderImpl.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/reader/FileReader.cpp -o ../../../../source/reader/FileReader.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/file/file.cpp -o ../../../../source/file/file.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/strconv/strconv.cpp -o ../../../../source/strconv/strconv.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/baseman/cli/main.cpp -o ../../../../source/baseman/cli/main.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/baseman/baseman.cpp -o ../../../../source/baseman/baseman.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/baseman/bm/base.cpp -o ../../../../source/baseman/bm/base.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/baseman/bm/bm.cpp -o ../../../../source/baseman/bm/bm.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/baseman/bm/project.cpp -o ../../../../source/baseman/bm/project.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/baseman/bm/version.cpp -o ../../../../source/baseman/bm/version.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/baseman/cli/runclp.cpp -o ../../../../source/baseman/cli/runclp.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/baseman/controllers/BmCopyControl.cpp -o ../../../../source/baseman/controllers/BmCopyControl.o
#-------------------------------------------------------------------------------
echo 'make lib...'


#-------------------------------------------------------------------------------
echo 'linking...'
x86_64-w64-mingw32-g++ -o baseman\.exe ../../../../source/csv/csv.o ../../../../source/csv/CsvData.o ../../../../source/csv/CsvRecord.o ../../../../source/csv/CsvField.o ../../../../source/settings/settings.o ../../../../source/reader/ReaderImpl.o ../../../../source/reader/FileReader.o ../../../../source/file/file.o ../../../../source/strconv/strconv.o ../../../../source/baseman/cli/main.o ../../../../source/baseman/baseman.o ../../../../source/baseman/bm/base.o ../../../../source/baseman/bm/bm.o ../../../../source/baseman/bm/project.o ../../../../source/baseman/bm/version.o ../../../../source/baseman/cli/runclp.o ../../../../source/baseman/controllers/BmCopyControl.o -static -static-libgcc -static-libstdc++ -s   
#-------------------------------------------------------------------------------
