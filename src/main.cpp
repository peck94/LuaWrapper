#include <iostream>
#include "Wrapper.hpp"
#include "Interface.hpp"
#include "Exceptions.hpp"
using namespace std;

void cppfunction1(LuaInterface *li) {
	double arg;
	li->get(1, &arg);

	li->put(arg * 0.5);
}

void cppfunction2(LuaInterface *li) {
	int arg1, arg2;
	li->get(1, &arg1);
	li->get(2, &arg2);

	li->put(arg1 + arg2);
}

void cppfunction3(LuaInterface *li) {
	string arg;
	li->get(1, &arg);

	cout << "Input: " << arg << endl;
}

void cppfunction4(LuaInterface *li) {
	cout << "Void function without arguments" << endl;
}

void cppfunction5(LuaInterface *li) {
	cout << "Non-void function without arguments" << endl;
	li->put(1337);
}

void cppfunction6(LuaInterface *li) {
	while(true) {
		li->put(1);
	}
}

int main() {
	cout << "Test Lua embedding" << endl;
	bool var1;
	int var2;
	double var3;
	float var4;
	string var5;
	string ret;
	double luavar;

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
	lw->getGlobal("luavar", &luavar);
	cout << "luavar = " << luavar << endl;

	cout << "Calling a Lua function from C++" << endl;
	lw->callFunction("myluafunction", &ret, 5);
	cout << "Result: " << ret << endl;

	cout << "Calling a C++ function from Lua" << endl;
	lw->registerFunction("cppfunction", cppfunction1);
	lw->registerFunction("cppfunction2", cppfunction2);
	lw->registerFunction("cppfunction3", cppfunction3);
	lw->registerFunction("cppfunction4", cppfunction4);
	lw->registerFunction("cppfunction5", cppfunction5);
	lw->registerFunction("cppfunction6", cppfunction6);

	lw->callFunction("myfunction", &ret, 5);
	cout << "Result: " << ret << endl;
	lw->callFunction("cppfunction2", &ret, 3, 9);
	cout << "Result: " << ret << endl;
	lw->callVoidFunction("cppfunction3", string{"swag"});
	lw->callVoidFunction("cppfunction4");
	lw->callFunction("cppfunction5", &ret);
	cout << "Result: " << ret << endl;

	cout << "Smashing the stack for fun and profit" << endl;
	try{
		lw->callVoidFunction("cppfunction6");
	}catch(lw_stack_overflow e) {
		cout << e.what() << endl;
	}

	cout << "Getting wrong types should fail" << endl;
	try{
		lw->getGlobal("var5", &var3);
	}catch(lw_type_error e) {
		cout << "And it did: " << e.what() << endl;
	}

	cout << "Calling undefined functions should fail" << endl;
	try{
		lw->callVoidFunction("undefined_function");
	}catch(lw_name_error e) {
		cout << "And it did: " << e.what() << endl;
	}

cleanup:
	cout << "Clean-up" << endl;
	delete lw;
	return 0;
}
