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
	if(!lua_isboolean(wrapper->getState(), index)) {
		throw lw_type_error("bool");
	}

	*value = lua_toboolean(wrapper->getState(), index);
}

void LuaInterface::get(int index, int *value) {
	if(!lua_isinteger(wrapper->getState(), index)) {
		throw lw_type_error("int");
	}

	*value = lua_tointeger(wrapper->getState(), index);
}

void LuaInterface::get(int index, double *value) {
	if(!lua_isnumber(wrapper->getState(), index)) {
		throw lw_type_error("double");
	}

	*value = lua_tonumber(wrapper->getState(), index);
}

void LuaInterface::get(int index, float *value) {
	if(!lua_isnumber(wrapper->getState(), index)) {
		throw lw_type_error("float");
	}

	double result;
	get(index, &result);

	*value = static_cast<float>(result);
}

void LuaInterface::get(int index, string *value) {
	if(!lua_isstring(wrapper->getState(), index)) {
		throw lw_type_error("string");
	}

	*value = string{lua_tostring(wrapper->getState(), index)};
}

template<typename... Types>
void LuaInterface::put(Types... values) {
	wrapper->pushValues(values...);
	returnValues+= sizeof...(Types);
}

int LuaInterface::getReturnSize() {
	return returnValues;
}

/*
* Template instantiations
*/
template void LuaInterface::put(bool);
template void LuaInterface::put(int);
template void LuaInterface::put(double);
template void LuaInterface::put(float);
template void LuaInterface::put(string);
