
/*
 *status.h
 */
#define OK      	0     	//exit with no problem
#define ERR     	1	//exit with unknown err
#define OF      	2	//over float
#define UST     	3	//unset
#define BDAG    	4	//bad args type
#define POPEND  	5	//error of char stack popend
#define MATCHERR        6	//error of brac match
#define NUMERR  	7	//error of str to int
#define NAMEERR 	8	//error of func/elem name 
#define NOSUCHFILE	9
#define ARGNUMERR      	10
#define ARGTYPEERR	11
#define FUNCNAMEERR	12
#define ELEMREDEF	13
#define ELEMNOTFOUND	14
#define ELEMTYPEERR	15

#define EXIT		100

char *statToStr(int stat)
{
	switch(stat)
		{
		case OK:
			return "OK";
		case ERR:
			return "ERR";
		case OF:
			return "OF";
		case UST:
			return "UST";
		case BDAG:
			return "BDAG";
		case POPEND:
			return "POPEND";
		case MATCHERR:
			return "MATCHERR";
		case NUMERR:
			return "NUMERR";
		case NAMEERR:
			return "NAMEERR";
		case NOSUCHFILE:
			return "NOSUCHFILE";
		case ARGNUMERR:
			return "ARGNUMERR";
		case ARGTYPEERR:
			return "ARGTYPEERR";
		case FUNCNAMEERR:
			return "FUNCNAMEERR";
		case ELEMREDEF:
			return "ELEMREDEF";
		case ELEMNOTFOUND:
			return "ELEMNOTFOUND";
		case ELEMTYPEERR:
			return "ELEMTYPEERR";
		case EXIT:
			return "EXIT";
		default:
			return "UNKNOWN";
		}
}

