#include <iostream>
#include "Wrapper.hpp"
using namespace std;

int main() {
	cout << "Test Lua embedding" << endl;

	cout << "Init Lua" << endl;
	LuaWrapper *lw = new LuaWrapper();

	cout << "Load script file" << endl;
	if(!lw->loadFile("luascript.lua")) {
		cerr << "Error: " << lw->getLastError() << endl;
		goto cleanup; // haeters gonna haet
	}

	cout << "Set global vars" << endl;
	lw->setGlobal("var1", true); // bool
	lw->setGlobal("var2", 1); // int
	lw->setGlobal("var3", 2.3f); // double
	lw->setGlobal("var4", string{"yolo"}); // string

cleanup:
	cout << "Clean-up" << endl;
	delete lw;
	return 0;
}
