

linux:
	x86_64-linux-gnu-g++ -std=c++14 src/Test.cpp src/main.cpp -o bin/lab4

win32:
	x86_64-w64-mingw32-g++ -std=c++14 src/Test.cpp src/main.cpp -o bin/lab4.exe

clear:
	rm bin/*
