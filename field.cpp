#include "string.h"

enum field_type { IP=0, PORT, GENERIC };

class Field {
private:
    String pattern;
    field_type type;

protected:

    Field(String pattern, field_type type) {
    	this->pattern=pattern;
    	this->type=type;
    }

public:

    Field(String pattern) {
    	pattern.trim();
        if(pattern.equals("src-ip") || pattern.equals("dst-ip") ) {
    		this->type=IP;
    	}
    	else {
    		this->type=PORT;
    	}
    	this->pattern=pattern;
    }

    ~Field() {
    	delete &pattern;
    }

    field_type get_type() const {
    	return this->type;
    }

    bool set_value(String val) {
        return false;
    }

    bool match_value(String val) const {
        return false;
    }

    bool match(String packet) {
    	String **packet_fields;
    	char delimeter = ',';
    	size_t *size;
    	packet.split(&delimeter,packet_fields,size);
    	for(size_t i=0;i<*size;i++) {
    		delimeter='=';
    		size_t *size_field;
    		String **field_values;
    		packet_fields[i]->split(&delimeter,field_values,size_field);
            field_values[0]->trim();
    		if (field_values[0]->equals(this->pattern)) {
    			field_values[1]->trim();
                bool result = this->match_value(*field_values[1]);
                for(size_t j=0;j<*size_field;j++) {
                    delete field_values[j];
                }
                delete size_field;
                delete field_values;
                for(size_t i=0;i<*size;i++) {
                    delete packet_fields[i];
                }
                delete size;
                delete packet_fields;
                return result;
    		}
    		for(size_t j=0;j<*size_field;j++) {
    			delete field_values[j];
    		}
    		delete size_field;
    		delete field_values;
    	}
    	for(size_t i=0;i<*size;i++) {
    		delete packet_fields[i];
    	}
    	delete size;
    	delete packet_fields;
        return false;
    }

};