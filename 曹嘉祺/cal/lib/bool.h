#define TRUE	1
#define FALSE	0

char *boolToStr(int a)
{
	if(a==TRUE)
		{
			return "TRUE";
		}
	return "FALSE";
}
int strToBool(char *str)
{
	if(strcmp(str,"TRUE")==0)
		return TRUE;
	return FALSE;
}
