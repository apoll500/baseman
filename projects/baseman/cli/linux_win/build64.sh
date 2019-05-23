#!/bin/sh
#-------------------------------------------------------------------------------
echo 'compiling...'
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/csv/csv.cpp -o ../../../../source/csv/csv.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/csv/CsvData.cpp -o ../../../../source/csv/CsvData.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/csv/CsvRecord.cpp -o ../../../../source/csv/CsvRecord.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/csv/CsvField.cpp -o ../../../../source/csv/CsvField.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/settings/settings.cpp -o ../../../../source/settings/settings.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/reader/reader.cpp -o ../../../../source/reader/reader.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/reader/ReaderImpl.cpp -o ../../../../source/reader/ReaderImpl.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/reader/FileReader.cpp -o ../../../../source/reader/FileReader.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/reader/StringReader.cpp -o ../../../../source/reader/StringReader.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/reader/StrReader.cpp -o ../../../../source/reader/StrReader.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/reader/WcsReader.cpp -o ../../../../source/reader/WcsReader.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/file/file.cpp -o ../../../../source/file/file.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/dir/dir.cpp -o ../../../../source/dir/dir.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/path/path.cpp -o ../../../../source/path/path.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/strman/strman.cpp -o ../../../../source/strman/strman.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/strconv/strconv.cpp -o ../../../../source/strconv/strconv.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/label/label.cpp -o ../../../../source/label/label.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/baseman/cli/main.cpp -o ../../../../source/baseman/cli/main.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/baseman/baseman.cpp -o ../../../../source/baseman/baseman.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/baseman/bm/base.cpp -o ../../../../source/baseman/bm/base.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/baseman/bm/bm.cpp -o ../../../../source/baseman/bm/bm.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/baseman/bm/project.cpp -o ../../../../source/baseman/bm/project.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/baseman/bm/version.cpp -o ../../../../source/baseman/bm/version.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/baseman/cli/runclp.cpp -o ../../../../source/baseman/cli/runclp.o
x86_64-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/baseman/controllers/BmCopyControl.cpp -o ../../../../source/baseman/controllers/BmCopyControl.o
#-------------------------------------------------------------------------------
echo 'make lib...'


#-------------------------------------------------------------------------------
echo 'linking...'
x86_64-w64-mingw32-g++ -o baseman\.exe ../../../../source/csv/csv.o ../../../../source/csv/CsvData.o ../../../../source/csv/CsvRecord.o ../../../../source/csv/CsvField.o ../../../../source/settings/settings.o ../../../../source/reader/reader.o ../../../../source/reader/ReaderImpl.o ../../../../source/reader/FileReader.o ../../../../source/reader/StringReader.o ../../../../source/reader/StrReader.o ../../../../source/reader/WcsReader.o ../../../../source/file/file.o ../../../../source/dir/dir.o ../../../../source/path/path.o ../../../../source/strman/strman.o ../../../../source/strconv/strconv.o ../../../../source/label/label.o ../../../../source/baseman/cli/main.o ../../../../source/baseman/baseman.o ../../../../source/baseman/bm/base.o ../../../../source/baseman/bm/bm.o ../../../../source/baseman/bm/project.o ../../../../source/baseman/bm/version.o ../../../../source/baseman/cli/runclp.o ../../../../source/baseman/controllers/BmCopyControl.o -s -static -static-libgcc -static-libstdc++  
#-------------------------------------------------------------------------------
