#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"

extern int check_args(int,char**);
extern void parse_input(Field&);

#define FAIL -1

int main(int argc, char** argv) {
	//char *rule;
	//cin >> ru
	if (check_args(argc,argv)!=0) {
		return FAIL;
	}
	String *rule = new String(argv[1]);
	String **rule_fields;
	char delim='=';
	size_t *rule_size;
	rule->split(&delim,rule_fields,rule_size);
	Field *cur_rule = new Field(*rule_fields[0]);
	cur_rule->set_value(*rule_fields[1]);
	parse_input(*cur_rule);
	delete rule;
	delete cur_rule;
	for(size_t i=0;i<*rule_size; i++) {
		delete rule_fields[i];
	}
	delete rule_fields;
	return 0;
}