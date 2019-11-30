int printFile(char *path)
{
	FILE *fp=fopen(path,"r");
	if(fp==NULL)
		{
			return NOSUCHFILE;
		}
	char c;
	while((c=fgetc(fp))!=EOF)
		{
			putchar(c);
		}
	putchar('\n');
	fclose(fp);
	return OK;
}
		
