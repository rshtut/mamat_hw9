#include "field.h"
#include "string.h"

#define MASK_SEGMENT 2
#define SEGMENTS 4

class Ip : public Field {
private:
    unsigned int low;
    unsigned int high;
    
    unsigned int get_ip_int(String val_str) const {
    	String **str_array;
    	size_t *size;
    	char del = '.';
    	val_str.split(&del, str_array, size);
    	if (*size != SEGMENTS)
    		return 0;
    	int *values = new int[SEGMENTS];
    	for (int i = 0; i < SEGMENTS; i++) {
    		str_array[i]->trim();
            values[i] = str_array[i]->to_integer();
    	}
    	return (values[0] << 24) | (values[1] << 16) | (values[2] << 8) | (values[3]);
    }

public:

    Ip(String pattern);

    bool set_value(String val) {
    	String **rule_fields;
    	size_t *rule_fields_size;
    	char del = '/';
    	val.split(&del, rule_fields, rule_fields_size);
    	rule_fields[1]->trim();
        rule_fields[0]->trim();
        int dc_num = 32 - rule_fields[1]->to_integer();
    	unsigned int val_int = get_ip_int(*rule_fields[0]);
    	low = (val_int >> dc_num) << dc_num;
    	high = (val_int >> dc_num);
    	for (int i = 0; i < dc_num; i++) {
    		high = high << 1;
    		high ++;
    	}
        return true;
    }

    bool match_value(String val) const {
    	val.trim();
        unsigned int ip_int = get_ip_int(val);
    	return (ip_int <= high && ip_int >= low);
    }
};

