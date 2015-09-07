#include <exception>

class lw_type_error: public runtime_error {
private:
	std::string name;

public:
	lw_type_error(std::string name) {
		this->name = name;
	}

	virtual const char* what() const throw() {
		return "Type error: data was not of type " + name;
	}
};
