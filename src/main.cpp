#include <iostream>
#include "Wrapper.hpp"
using namespace std;

void l_cppfunction(lua_State *L) {
	double arg = luaL_checknumber(L,1);
	lua_pushnumber(L, arg * 0.5);
}

int main() {
	cout << "Test Lua embedding" << endl;
	bool var1;
	int var2;
	double var3;
	float var4;
	string var5;
	string ret;

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
	lw->setGlobal("cppvar", 5);

	cout << "Run file" << endl;
	if(!lw->runFile()) {
		cerr << "Error: " << lw->getLastError() << endl;
		goto cleanup;
	}

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

	cout << "Calling a Lua function from C++" << endl;
	lw->callFunction("myluafunction", &ret, 5);
	cout << "Result: " << ret << endl;

	cout << "Calling a C++ function from Lua" << endl;
	lw->registerFunction("cppfunction", l_cppfunction);
	lw->callFunction("myfunction", &ret, 5);
	cout << "Result: " << ret << endl;

cleanup:
	cout << "Clean-up" << endl;
	delete lw;
	return 0;
}
