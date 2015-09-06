#include <iostream>
#include "Wrapper.hpp"
using namespace std;

int main() {
	cout << "Test Lua embedding" << endl;
	bool var1;
	int var2;
	double var3;
	float var4;
	string var5;

	cout << "Init Lua" << endl;
	LuaWrapper *lw = new LuaWrapper();

	cout << "Load script file" << endl;
	if(!lw->loadFile("luascript.lua")) {
		cerr << "Error: " << lw->getLastError() << endl;
		goto cleanup; // haeters gonna haet
	}

	cout << "Set global vars" << endl;
	var1 = true;
	var2 = 1;
	var3 = 2.3f;
	var4 = 2.3f;
	var5 = "yolo";

	lw->setGlobal("var1", var1);
	lw->setGlobal("var2", var2);
	lw->setGlobal("var3", var3);
	lw->setGlobal("var4", var4);
	lw->setGlobal("var5", var5);

	cout << "Read global vars" << endl;
	lw->getGlobal("var1", &var1);
	cout << "var1 = " << var1 << endl;
        lw->getGlobal("var2", &var2);
	cout << "var2 = " << var2 << endl;
        lw->getGlobal("var3", &var3);
	cout << "var3 = " << var3 << endl;
        lw->getGlobal("var4", &var4);
	cout << "var4 = " << var4 << endl;
        lw->getGlobal("var5", &var5);
	cout << "var5 = " << var5 << endl;

cleanup:
	cout << "Clean-up" << endl;
	delete lw;
	return 0;
}
