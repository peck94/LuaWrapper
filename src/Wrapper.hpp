#ifndef LUA_WRAPPER
#define LUA_WRAPPER

#include <lua.hpp>
#include <string>
#include <functional>
#include <vector>
#include "Interface.hpp"

// forward declaration will be needed
class LuaWrapper;

/*
* LuaFunction is the type that functions you pass from C++ into Lua
* will have. They return nothing and accept a single argument, namely
* a LuaInterface*, which is a decorator around the LuaWrapper instance
* they were registered from. LuaInterface provides two helper functions,
* get and put, which your functions will need to use in order to get their
* arguments from the stack and return values.
*/
typedef std::function<void(LuaInterface*)> LuaFunction;

/*
* A FunctionRecord keeps track of which registered functions have which
* LuaWrapper instance associated with them. This is an important piece
* of bookkeeping when handling multiple LuaWrapper instances, since due
* to technical reasons the functions will be stored in a static member
* variable.
*/
struct FunctionRecord {
	LuaWrapper *wrapper;
	LuaFunction function;
};

class LuaWrapper {
private:
	// this friend may access our private members
	friend class LuaInterface;

	/* Members */

	// store Lua state
	lua_State *luaState;

	// store code of last error
	int lastError;

	// store registered functions
	static std::vector<FunctionRecord*> functions;

	/* Private functions */

	// set the Lua state
	void setState(lua_State *newState);

	// retrieve the Lua state
	lua_State *getState();

	// set the last error
	void setLastError(int newLastError);

	// helper functions for pushing and popping values to/from the Lua stack
	void pushValues();
	template<typename... T>	void pushValues(bool value, T... rest);
	template<typename... T> void pushValues(int value, T... rest);
	template<typename... T> void pushValues(double value, T... rest);
	template<typename... T> void pushValues(float value, T... rest);
	template<typename... T> void pushValues(std::string value, T... rest);

	void popValue(bool *value);
	void popValue(int *value);
	void popValue(double *value);
	void popValue(float *value);
	void popValue(std::string* value);

	// helper function for calls from Lua into C++
	static int callFromLua(lua_State *state);

public:
	/*
	* Construct a new LuaWrapper instance.
	* This will create and initialize a new Lua state.
	*/
	LuaWrapper();

	/*
	* Retrieve the code of the last error.
	*/
	int getLastError();

	/*
	* Load a Lua script file into the Lua state.
	* Note: this does NOT run the file, so any symbols such as functions
	* defined in the given script will NOT be loaded into the runtime.
	* Use runFile for that.
	*/
	bool loadFile(std::string filename);

	/*
	* Run a previously loaded file.
	*/
	bool runFile();

	/*
	* Load and run a file.
	*/
	bool runFile(std::string filename);

	/*
	* Set a global variable in the Lua state.
	*/
	template<typename T>
	void setGlobal(std::string name, T value);

	/*
	* Get a global variable from the Lua state.
	*/
	template<typename T>
	void getGlobal(std::string name, T* value);

	/*
	* Call into a Lua function.
	*/
	template<typename T, typename... Types>
	bool callFunction(std::string name, T* result, Types... args) {
        	int num = (result) ? 1 : 0;

        	lua_getglobal(getState(), name.c_str());
        	pushValues(args...);
        	setLastError(lua_pcall(getState(), sizeof...(Types), num, 0));
        	if(result) {
        	        popValue(result);
	       	}

	        return getLastError() == 0;
	}

	/*
	* Register a function in the Lua runtime.
	*/
	void registerFunction(std::string name, LuaFunction function);

	/*
	* Destroy the LuaWrapper.
	* Cleans up the Lua state.
	*/
	~LuaWrapper();
};

#endif
