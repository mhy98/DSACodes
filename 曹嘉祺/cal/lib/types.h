#define UNMATCH	-2
#define UNSET	-1
#define FUNC	0
#define INT	1
#define BOOL	2
#define STR	3
#define POLY	4
#define FLOAT	5
char *typeToStr(int type)
{
	switch(type)
		{
		case UNMATCH:
			return "UNMATCH";
		case UNSET:
			return "UNSET";
		case FUNC:
			return "FUNC";
		case INT:
			return "INT";
		case BOOL:
			return "BOOL";
		case STR:
			return "STR";
		case POLY:
			return "POLY";
		case FLOAT:
			return "FLOAT";
		default:
			return "UNKNOWN";
		}
}
#define IF_EQ(name) if(strcmp(str,#name)==0)
int strToType(char *str)
{
	IF_EQ(UNSET)
		return UNSET;
	IF_EQ(FUNC)
		return FUNC;
	IF_EQ(INT)
		return INT;
	IF_EQ(BOOL)
		return BOOL;
	IF_EQ(POLY)
		return POLY;
	IF_EQ(STR)
		return STR;
	IF_EQ(FLOAT)
		return FLOAT;
	return UNMATCH;
}
