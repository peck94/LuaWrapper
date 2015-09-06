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
	void pushValue(bool value);
	void pushValue(int value);
	void pushValue(double value);
	void pushValue(float value);
	void pushValue(std::string value);

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
	* Destroy the LuaWrapper.
	* Cleans up the Lua state.
	*/
	~LuaWrapper();
};
