#!/bin/sh
#-------------------------------------------------------------------------------
i686-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/csv/csv.cpp -o ../../../../source/csv/csv.o
i686-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/csv/CsvData.cpp -o ../../../../source/csv/CsvData.o
i686-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/csv/CsvRecord.cpp -o ../../../../source/csv/CsvRecord.o
i686-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/csv/CsvField.cpp -o ../../../../source/csv/CsvField.o
i686-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/settings/settings.cpp -o ../../../../source/settings/settings.o
i686-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/file/file.cpp -o ../../../../source/file/file.o
i686-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/dir/dir.cpp -o ../../../../source/dir/dir.o
i686-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/path/path.cpp -o ../../../../source/path/path.o
i686-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/base64/base64.cpp -o ../../../../source/base64/base64.o
i686-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/strman/strman.cpp -o ../../../../source/strman/strman.o
i686-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/strconv/strconv.cpp -o ../../../../source/strconv/strconv.o
i686-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/prompt/prompt.cpp -o ../../../../source/prompt/prompt.o
i686-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/reader/reader.cpp -o ../../../../source/reader/reader.o
i686-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/reader/ReaderImpl.cpp -o ../../../../source/reader/ReaderImpl.o
i686-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/reader/FileReader.cpp -o ../../../../source/reader/FileReader.o
i686-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/reader/StringReader.cpp -o ../../../../source/reader/StringReader.o
i686-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/reader/StrReader.cpp -o ../../../../source/reader/StrReader.o
i686-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/reader/WcsReader.cpp -o ../../../../source/reader/WcsReader.o
i686-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/label/label.cpp -o ../../../../source/label/label.o
i686-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/bmsetup/cli/main.cpp -o ../../../../source/bmsetup/cli/main.o
i686-w64-mingw32-g++ -D OS_WIN  -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3  -c ../../../../source/bmsetup/bmsetup.cpp -o ../../../../source/bmsetup/bmsetup.o
#-------------------------------------------------------------------------------


#-------------------------------------------------------------------------------
i686-w64-mingw32-g++ -o bmsetup\.exe ../../../../source/csv/csv.o ../../../../source/csv/CsvData.o ../../../../source/csv/CsvRecord.o ../../../../source/csv/CsvField.o ../../../../source/settings/settings.o ../../../../source/file/file.o ../../../../source/dir/dir.o ../../../../source/path/path.o ../../../../source/base64/base64.o ../../../../source/strman/strman.o ../../../../source/strconv/strconv.o ../../../../source/prompt/prompt.o ../../../../source/reader/reader.o ../../../../source/reader/ReaderImpl.o ../../../../source/reader/FileReader.o ../../../../source/reader/StringReader.o ../../../../source/reader/StrReader.o ../../../../source/reader/WcsReader.o ../../../../source/label/label.o ../../../../source/bmsetup/cli/main.o ../../../../source/bmsetup/bmsetup.o -s -static -static-libgcc -static-libstdc++  
#-------------------------------------------------------------------------------
