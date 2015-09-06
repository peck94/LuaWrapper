LUAHOME=lua-5.3.1/src
all: main
main: src/main.cpp src/Wrapper.cpp
	g++ -g src/Wrapper.cpp src/main.cpp -llua -L$(LUAHOME) -I$(LUAHOME) -o test/sample -Wl,--no-as-needed -ldl -std=c++11
