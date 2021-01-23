#include "string.h"
#include "field.h"
#include "port.h"

#define MASK_SEGMENT 2

bool Port::set_value(String val) {
	String **range_string;
	size_t range_string_size;
	char delimeter = '-';
	val.split(&delimeter, range_string, &range_string_size);
    if(range_string_size!=MASK_SEGMENT) {
        delete[] range_string;
        return false;
    }
    String range0=range_string[0]->trim();
    String range1=range_string[1]->trim();
	this->range[0] = range0.to_integer();
	this->range[1] = range1.to_integer();
	delete[] range_string;
    return true;
}

bool Port::match_value(String val) const {
	String trimmed_val=val.trim();
    int val_int = trimmed_val.to_integer();
	return (val_int <= range[1] && val_int >= range[0]);
}