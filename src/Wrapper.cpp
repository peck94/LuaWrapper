#include "Wrapper.hpp"
using namespace std;

/*
* Private functions
*/
void LuaWrapper::setState(lua_State *newState) {
	luaState = newState;
}

lua_State* LuaWrapper::getState() {
	return luaState;
}

void LuaWrapper::setLastError(int newLastError) {
	lastError = newLastError;
}

inline void LuaWrapper::pushValue(bool value) {
	lua_pushboolean(getState(), value);
}

inline void LuaWrapper::pushValue(int value) {
	lua_pushinteger(getState(), value);
}

inline void LuaWrapper::pushValue(double value) {
	lua_pushnumber(getState(), value);
}

inline void LuaWrapper::pushValue(float value) {
	lua_pushnumber(getState(), static_cast<float>(value));
}

inline void LuaWrapper::pushValue(string value) {
	lua_pushstring(getState(), value.c_str());
}

inline void LuaWrapper::popValue(bool* value) {
	*value = lua_toboolean(getState(), -1);
	lua_pop(getState(), 1);
}

inline void LuaWrapper::popValue(int* value) {
	*value = lua_tointeger(getState(), -1);
	lua_pop(getState(), 1);
}

inline void LuaWrapper::popValue(double* value) {
	*value = lua_tonumber(getState(), -1);
	lua_pop(getState(), 1);
}

inline void LuaWrapper::popValue(float* value) {
	*value = static_cast<float>(lua_tonumber(getState(), -1));
	lua_pop(getState(), 1);
}

inline void LuaWrapper::popValue(string* value) {
	*value = string{lua_tostring(getState(), -1)};
	lua_pop(getState(), 1);
}

/*
* Public functions
*/
LuaWrapper::LuaWrapper() {
	// create new Lua state
	setState(luaL_newstate());

	// load standard libraries
	luaL_openlibs(getState());
}

int LuaWrapper::getLastError() {
	return lastError;
}

bool LuaWrapper::loadFile(string filename) {
	setLastError(luaL_loadfile(getState(), filename.c_str()));
	return getLastError() == 0;
}

template<typename T>
void LuaWrapper::setGlobal(string name, T value) {
	pushValue(value);
	lua_setglobal(getState(), name.c_str());
}

template<typename T>
void LuaWrapper::getGlobal(string name, T* value) {
        lua_getglobal(getState(), name.c_str());
	popValue(value);
}

LuaWrapper::~LuaWrapper() {
	lua_close(getState());
}

/*
* Template instantiations
*/
template void LuaWrapper::setGlobal(string, bool);
template void LuaWrapper::setGlobal(string, int);
template void LuaWrapper::setGlobal(string, double);
template void LuaWrapper::setGlobal(string, float);
template void LuaWrapper::setGlobal(string, string);

template void LuaWrapper::getGlobal(string, bool*);
template void LuaWrapper::getGlobal(string, int*);
template void LuaWrapper::getGlobal(string, double*);
template void LuaWrapper::getGlobal(string, float*);
template void LuaWrapper::getGlobal(string, string*);
