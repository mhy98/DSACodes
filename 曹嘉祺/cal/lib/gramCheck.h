struct charStack
{
	char c;
	struct charStack *next;
};

typedef struct charStack cs;

cs *csInit()
{
	cs *head;
	head=MALLOC(cs);
	IF_NULL_RET_NULL(head);
	head->c='\0';
	head->next=NULL;
	return head;
}
int csPush(cs *head,char c)
{
	cs *tail;
	TOTAIL(head,tail);
	
	tail->next=MALLOC(cs);
	tail=tail->next;
	IF_NULL_RET_OF(tail);
	tail->next=NULL;
	tail->c=c;
	return OK;
}
int csPop(cs *head,char *c)
{
	cs *tail;
	TOTAIL(head,tail);
	if(head==tail)
		return POPEND;
	cs *tailFront;
	for(tailFront=head;tailFront->next->next!=NULL;tailFront=tailFront->next);
	tailFront->next=NULL;
	*c=tail->c;
	free(tail);
	return OK;
}
int csFree(cs *head)
{
	
	if(head==NULL)
		return OK;
	csFree(head->next);
	free(head);
	return OK;
}
int ifEmptyCs(cs *head)
{
	cs *tail;
	TOTAIL(head,tail);
	if(head==tail)
		return TRUE;
	return FALSE;
}
int ifNum(char c)
{
	if(c<='9'&&c>='0')
		return TRUE;
	return FALSE;
}
int ifLetter(char c)
{
	if((c<='z'&&c>='a')||(c<='Z'&&c>='A'))
		return TRUE;
	return FALSE;
}
int ifBlank(char c)
{
	if(c=='\n'||c==' ')
		return TRUE;
	return FALSE;
}
int ifLeft(char c)
{
	if(c=='('||c=='{'||c=='[')
		return TRUE;
	return FALSE;
}
int ifRight(char c)
{
	if(c==')'||c=='}'||c==']')
		return TRUE;
	return FALSE;
}
int ifMatch(char c1,char c2)
{
	if(!(ifLeft(c1)&&ifRight(c2)))
		return FALSE;
	if(c1=='('&&c2!=')')
		return FALSE;
	if(c1=='['&&c2!=']')
		return FALSE;
	if(c1=='{'&&c2!='}')
		return FALSE;
	return TRUE;
}

int bracCheck(char *str)
{
	cs *stack=csInit();
	IF_NULL_RET_OF(stack);
	int err;
	int ifStr=0;
	for(char *c=str;*c!='\0';c++)
		{
			if(*c=='"')
				{
					ifStr=!ifStr;
					//printf("here is a \"\n");
					char tmp;
					err=csPop(stack,&tmp);
					//printf("pop:%c \n",tmp);
					
					if(err==POPEND)
						return NAMEERR;
					if(tmp!=*c)
						{
										
							
							err=csPush(stack,tmp);
							//printf("push:%c\n",tmp);
							IF_STACK_OF(stack);
							err=csPush(stack,*c);
							//printf("push:%c\n",*c);
							IF_STACK_OF(stack);
						}
				
				
				}
							
			if(ifLeft(*c)&&!ifStr)
				{
					//printf("left brac '%c'\n",*c);
					err=csPush(stack,*c);
					//printf("push:%c\n",*c);
					if(err==OF)
						{
							//printf("stack OF\n");
							csFree(stack);
							return OF;
						}
				}
			if(ifRight(*c)&&!ifStr)
				{
					//printf("right brac '%c'\n",*c);
					char poped;
					err=csPop(stack,&poped);
					//printf("pop:%c \n",poped);
					if(!ifMatch(poped,*c))
						{
							csFree(stack);
							return MATCHERR;
						}
				}
		}
	if(ifEmptyCs(stack))
		{
			csFree(stack);
			return OK;
		}
	return MATCHERR;
}
int ifCharInLaw(char c)
{
	if(c=='{'||c=='}'||c=='('||c==')'||c=='['||c==']')
		return TRUE;
	if(c<='z'&&c>='a')
		return TRUE;
	if(c<='Z'&&c>='A')
		return TRUE;
	if(c<='9'&&c>='0')
		return TRUE;
	if(c==' '||c=='.'||c=='-')
		return TRUE;
	if(c=='"')
		return TRUE;
	return FALSE;
}
int bracCharCheck(char *str)
{
	if(!ifLeft(*str))
		return MATCHERR;
	int strTag=0;
	for(char *c=str;*c!='\0'&&*c!='\n';c++)
		{
			if(*c=='"'&&strTag==0)
				strTag=1;
			else if(*c=='"'&&strTag==1)
				strTag=0;
			if(strTag!=1&&ifCharInLaw(*c)==FALSE)
				return NAMEERR;
		}

	int err;
	if((err=bracCheck(str))!=OK)
		{
			return err;
		}
	return OK;
}
int gCheck(char *str)
{
	//printf("----enterPlantTree----\n");
	char *ptr=str;
	char *subPtr=str;
	for(ptr=str;!ifLeft(*ptr);ptr++);
	//printf("left:%c\n",*ptr);
	for(;ifBlank(*ptr)||ifLeft(*ptr);ptr++);
	subPtr=ptr;
	int functag=0;
	int err;
	while(TRUE)
		{
			//printf(">loop\n");
			if(ifLetter(*ptr))
				{

					for(subPtr=ptr;*subPtr!=' '&&!ifRight(*subPtr);subPtr++)
						{
							if(!ifLetter(*subPtr))
								return NAMEERR;
						}

					if(functag==0)
						{

							functag=1;
						}

					for(;*subPtr==' ';subPtr++);
					ptr=subPtr;
					
				}
			else if(ifNum(*ptr)||*ptr=='-')
				{

					int point=0;
					for(subPtr=ptr+1;*subPtr!=' '&&!ifRight(*subPtr);subPtr++)
						{
							if(*subPtr=='.'&&point==0)
								point=1;
							else if(*subPtr=='.'&&point==1)
								return NUMERR;
							if(!ifNum(*subPtr)&&*subPtr!='.')
								return NUMERR;
						}


					if(functag!=1)
						return NAMEERR;

					for(;*subPtr==' ';subPtr++);
					ptr=subPtr;
				}
			else if(ifLeft(*ptr))
				{

					if(functag!=1)
						{
							return ERR;
						}

					
					if((err=gCheck(ptr))!=OK)
						return err;
					int brac=TRUE;
					for(subPtr=ptr+1;!(ifRight(*subPtr)&&brac==1);subPtr++)
						{
							
							if(ifRight(*subPtr))
								brac--;
							else if(ifLeft(*subPtr))
								brac++;
						}

					subPtr++;
					for(;*subPtr==' ';subPtr++);
					ptr=subPtr;
				}
			else if(*ptr=='"')
				{
					if(functag!=1)
						{
							return ERR;
						}
					for(subPtr=ptr+1;*subPtr!='"';subPtr++);
						
					
					
					subPtr++;
					for(;*subPtr==' ';subPtr++);
					ptr=subPtr;
				}
			else if(ifRight(*ptr))
				{
					return OK;
				}
		}
	
	return OK;
}
int gramCheck(char *str)
{
	int err;
	err=bracCharCheck(str);
	if(err!=OK)
		return err;
	err=gCheck(str);
	if(err!=OK)
		return err;
	return OK;
}
