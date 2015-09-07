#ifndef LUA_EXCEPTIONS
#define LUA_EXCEPTIONS

#include <string>

class lw_error {
public:
	virtual std::string what() = 0;
};

class lw_type_error: public lw_error {
private:
	std::string name;

public:
	lw_type_error(std::string name) {
		this->name = name;
	}

	virtual std::string what() {
		return std::string{"Type error: data was not of type " + name};
	}
};

class lw_name_error: public lw_error {
private:
	std::string name;

public:
	lw_name_error(std::string name) {
                this->name = name;
        }

        virtual std::string what() {
                return std::string{"Name error: undefined symbol " + name};
        }
};

#endif
