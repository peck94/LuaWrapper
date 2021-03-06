#ifndef LUA_INTERFACE
#define LUA_INTERFACE

#include "Wrapper.hpp"
#include <lua.hpp>
#include <string>

class LuaWrapper;

class LuaInterface {
private:
	// store wrapper instance
	LuaWrapper *wrapper;
	// store number of return arguments
	int returnValues = 0;

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
	template<typename... Types>
	void put(Types... values);

	/*
	* Retrieve the number of return values.
	*/
	int getReturnSize();
};

#endif
