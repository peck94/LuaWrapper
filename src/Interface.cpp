#include "Wrapper.hpp"
#include "Interface.hpp"
using namespace std;

LuaInterface::LuaInterface(LuaWrapper *wrapper) {
	this->wrapper = wrapper;
}

LuaWrapper* LuaInterface::getWrapper() {
	return wrapper;
}

void LuaInterface::get(int index, bool *value) {
	*value = lua_toboolean(wrapper->getState(), index);
}

void LuaInterface::get(int index, int *value) {
	*value = lua_tointeger(wrapper->getState(), index);
}

void LuaInterface::get(int index, double *value) {
	*value = lua_tonumber(wrapper->getState(), index);
}

void LuaInterface::get(int index, float *value) {
	double result;
	get(index, &result);

	*value = static_cast<float>(result);
}

void LuaInterface::get(int index, string *value) {
	*value = string{lua_tostring(wrapper->getState(), index)};
}

void LuaInterface::put(bool value) {
	lua_pushboolean(wrapper->getState(), value);
}

void LuaInterface::put(int value) {
	lua_pushinteger(wrapper->getState(), value);
}

void LuaInterface::put(double value) {
	lua_pushnumber(wrapper->getState(), value);
}

void LuaInterface::put(float value) {
	put(static_cast<double>(value));
}

void LuaInterface::put(string value) {
	lua_pushstring(wrapper->getState(), value.c_str());
}
