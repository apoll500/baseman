#!/bin/sh
#-------------------------------------------------------------------------------
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/csv/csv.cpp -o ../../../../source/csv/csv.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/csv/CsvData.cpp -o ../../../../source/csv/CsvData.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/csv/CsvRecord.cpp -o ../../../../source/csv/CsvRecord.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/csv/CsvField.cpp -o ../../../../source/csv/CsvField.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/settings/settings.cpp -o ../../../../source/settings/settings.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/file/file.cpp -o ../../../../source/file/file.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/dir/dir.cpp -o ../../../../source/dir/dir.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/path/path.cpp -o ../../../../source/path/path.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/base64/base64.cpp -o ../../../../source/base64/base64.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/strman/strman.cpp -o ../../../../source/strman/strman.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/str/str.cpp -o ../../../../source/str/str.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/strconv/strconv.cpp -o ../../../../source/strconv/strconv.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/prompt/prompt.cpp -o ../../../../source/prompt/prompt.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/reader/reader.cpp -o ../../../../source/reader/reader.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/reader/ReaderImpl.cpp -o ../../../../source/reader/ReaderImpl.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/reader/FileReader.cpp -o ../../../../source/reader/FileReader.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/reader/StringReader.cpp -o ../../../../source/reader/StringReader.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/reader/StrReader.cpp -o ../../../../source/reader/StrReader.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/reader/WcsReader.cpp -o ../../../../source/reader/WcsReader.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/label/label.cpp -o ../../../../source/label/label.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/osdir/osdir.cpp -o ../../../../source/osdir/osdir.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/bmsetup/cli/main.cpp -o ../../../../source/bmsetup/cli/main.o
g++ -D OS_LIN  -fno-pie -Wextra -fexceptions -Wall -I/opt/prokee/system/inc/ -I../../../../source/ -fexpensive-optimizations -O3 -c ../../../../source/bmsetup/bmsetup.cpp -o ../../../../source/bmsetup/bmsetup.o
#-------------------------------------------------------------------------------


#-------------------------------------------------------------------------------
g++ -o bmsetup ../../../../source/csv/csv.o ../../../../source/csv/CsvData.o ../../../../source/csv/CsvRecord.o ../../../../source/csv/CsvField.o ../../../../source/settings/settings.o ../../../../source/file/file.o ../../../../source/dir/dir.o ../../../../source/path/path.o ../../../../source/base64/base64.o ../../../../source/strman/strman.o ../../../../source/str/str.o ../../../../source/strconv/strconv.o ../../../../source/prompt/prompt.o ../../../../source/reader/reader.o ../../../../source/reader/ReaderImpl.o ../../../../source/reader/FileReader.o ../../../../source/reader/StringReader.o ../../../../source/reader/StrReader.o ../../../../source/reader/WcsReader.o ../../../../source/label/label.o ../../../../source/osdir/osdir.o ../../../../source/bmsetup/cli/main.o ../../../../source/bmsetup/bmsetup.o -no-pie -s 
#-------------------------------------------------------------------------------
