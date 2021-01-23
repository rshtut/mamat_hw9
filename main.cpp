#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"
#include "input.h"

extern int check_args(int,char**);
extern void parse_input(Field&);

#define FAIL -1

int main(int argc, char** argv) {
	//char *rule;
	//cin >> ru
	if (check_args(argc,argv)!=0) {
		return FAIL;
	}
	String rule(argv[1]);
	String **rule_fields;
	char delim='=';
	size_t rule_size=0;
	rule.split(&delim,rule_fields,&rule_size);
	if (rule_fields==NULL) {
		return FAIL;
	}
	Field *cur_rule = new Field(*rule_fields[0]);
	cur_rule->set_value(*rule_fields[1]);
	parse_input(*cur_rule);
	delete cur_rule;
	delete[] rule_fields;
	return 0;
}