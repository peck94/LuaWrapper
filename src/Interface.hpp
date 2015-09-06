#ifndef LUA_INTERFACE
#define LUA_INTERFACE

#include <lua.hpp>
#include <string>

class LuaWrapper;

class LuaInterface {
private:
	LuaWrapper *wrapper;

public:
	/*
	* Initialize the interface with a wrapper instance.
	*/
	LuaInterface(LuaWrapper *wrapper);

	/*
	* Return the wrapper.
	*/
	LuaWrapper* getWrapper();

	/*
	* Get an argument from the stack.
	*/
	void get(int index, bool *value);
	void get(int index, int *value);
	void get(int index, double *value);
	void get(int index, float *value);
	void get(int index, std::string *value);

	/*
	* Push a value to the stack.
	*/
	void put(bool value);
	void put(int value);
	void put(double value);
	void put(float value);
	void put(std::string value);
};

#endif
