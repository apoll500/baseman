#!/bin/sh
#-------------------------------------------------------------------------------
echo 'compiling...'
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -m32 -c ../../../../source/csv/csv.cpp -o ../../../../source/csv/csv.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -m32 -c ../../../../source/csv/CsvData.cpp -o ../../../../source/csv/CsvData.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -m32 -c ../../../../source/csv/CsvRecord.cpp -o ../../../../source/csv/CsvRecord.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -m32 -c ../../../../source/csv/CsvField.cpp -o ../../../../source/csv/CsvField.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -m32 -c ../../../../source/settings/settings.cpp -o ../../../../source/settings/settings.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -m32 -c ../../../../source/reader/ReaderImpl.cpp -o ../../../../source/reader/ReaderImpl.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -m32 -c ../../../../source/reader/FileReader.cpp -o ../../../../source/reader/FileReader.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -m32 -c ../../../../source/file/file.cpp -o ../../../../source/file/file.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -m32 -c ../../../../source/strconv/strconv.cpp -o ../../../../source/strconv/strconv.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -m32 -c ../../../../source/baseman/cli/main.cpp -o ../../../../source/baseman/cli/main.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -m32 -c ../../../../source/baseman/baseman.cpp -o ../../../../source/baseman/baseman.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -m32 -c ../../../../source/baseman/bm/base.cpp -o ../../../../source/baseman/bm/base.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -m32 -c ../../../../source/baseman/bm/bm.cpp -o ../../../../source/baseman/bm/bm.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -m32 -c ../../../../source/baseman/bm/project.cpp -o ../../../../source/baseman/bm/project.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -m32 -c ../../../../source/baseman/bm/version.cpp -o ../../../../source/baseman/bm/version.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -m32 -c ../../../../source/baseman/cli/runclp.cpp -o ../../../../source/baseman/cli/runclp.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -m32 -c ../../../../source/baseman/controllers/BmCopyControl.cpp -o ../../../../source/baseman/controllers/BmCopyControl.o
#-------------------------------------------------------------------------------
echo 'make lib...'


#-------------------------------------------------------------------------------
echo 'linking...'
g++ -o baseman ../../../../source/csv/csv.o ../../../../source/csv/CsvData.o ../../../../source/csv/CsvRecord.o ../../../../source/csv/CsvField.o ../../../../source/settings/settings.o ../../../../source/reader/ReaderImpl.o ../../../../source/reader/FileReader.o ../../../../source/file/file.o ../../../../source/strconv/strconv.o ../../../../source/baseman/cli/main.o ../../../../source/baseman/baseman.o ../../../../source/baseman/bm/base.o ../../../../source/baseman/bm/bm.o ../../../../source/baseman/bm/project.o ../../../../source/baseman/bm/version.o ../../../../source/baseman/cli/runclp.o ../../../../source/baseman/controllers/BmCopyControl.o -no-pie -s -m32 -static -static-libgcc -static-libstdc++ 
#-------------------------------------------------------------------------------
