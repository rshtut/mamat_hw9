#ifndef PORT_H
#define PORT_H

#include "string.h"
#include "field.h"

class Port : public Field {
private:
    int range[2];

public:

    Port(String pattern);

    bool set_value(String val) {
    	String **range_string;
    	size_t *range_string_size;
    	char delimeter = '-';
    	val.split(&delimeter, range_string, range_string_size);
        range_string[0]->trim();
        range_string[1]->trim();
    	this->range[0] = range_string[0]->to_integer();
    	this->range[1] = range_string[1]->to_integer();
    	for (size_t i = 0; i < *range_string_size; i++) {
    		delete range_string[i];
    	}
    	delete range_string_size;
    	delete range_string;
        return true;
    }

    bool match_value(String val) const {
    	val.trim();
        int val_int = val.to_integer();
    	return (val_int <= range[1] && val_int >= range[0]);
    }
};

#endif
