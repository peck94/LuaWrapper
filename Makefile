LUAHOME=lua-5.3.1/src
all: sample
sample: sample.cpp
	g++ -g sample.cpp -llua -L$(LUAHOME) -I$(LUAHOME) -o sample -Wl,--no-as-needed -ldl
