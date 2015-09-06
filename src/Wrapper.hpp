#include <lua.hpp>
#include <string>

class LuaWrapper {
private:
	/* Members */

	// store Lua state
	lua_State *luaState;

	// store code of last error
	int lastError;

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
	*/
	bool loadFile(std::string filename);

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
	bool callFunction(std::string name, T* result, Types... args);

	/*
	* Destroy the LuaWrapper.
	* Cleans up the Lua state.
	*/
	~LuaWrapper();
};
