
struct polyNode
{
	int exp;
	double val;
	struct polyNode *next;
};
typedef struct polyNode poly;

poly *polyInit()
{
	poly *head;
	head=MALLOC(poly);
	IF_NULL_RET_NULL(head);
	head->exp=0;
	head->val=0;
	head->next=NULL;
	return head;
}
poly *polyCreat(int exp,double val)
{
	poly *tmp;
	tmp=MALLOC(poly);
	IF_NULL_RET_NULL(tmp);
	tmp->exp=exp;
	tmp->val=val;
	tmp->next=NULL;
	return tmp;
}
int delPolyNode(poly *head,int exp)
{
	poly *pos;
	for(pos=head;pos->next!=NULL&&pos->next->exp!=exp;pos=pos->next);
	if(pos->next==NULL)
		return OK;
	poly *tmp=pos->next;
	pos->next=pos->next->next;
	free(tmp);
	return OK;
}
int addPolyNode(poly *head,int exp,double val)
{
	if(equDouble(val,0.00)==TRUE||exp<0)
		return OK;
	//printf("exp:%i,val:%lf\n",exp,val);
	poly *pos;
	for(pos=head;pos->next!=NULL&&pos->next->exp>=exp;pos=pos->next);
	if(pos!=head&&pos->exp==exp)
		{
			pos->val=val+pos->val;
			if(equDouble(pos->val,0.00)==TRUE)
				{
					delPolyNode(head,pos->exp);
				}
			return OK;
		}
	else if(pos->next==NULL)
		{
			poly *tmp=polyCreat(exp,val);
			IF_NULL_RET_OF(tmp);
			pos->next=tmp;
			return OK;
		}
	else
		{
			poly *tmp=polyCreat(exp,val);
			IF_NULL_RET_OF(tmp);
			tmp->next=pos->next;
			pos->next=tmp;
			return OK;
		}
}

int *freePoly(poly *head)
{
	if(head==NULL)
		{
			return OK;
		}
    	freePoly(head->next);
	free(head);
	return OK;
}
poly *clonePoly(poly *head)
{
	poly *clone=polyInit();
	IF_NULL_RET_NULL(clone);
	poly *tmp;
	int err;
	for(tmp=head;tmp->next!=NULL;tmp=tmp->next)
	{
		err=addPolyNode(clone,tmp->next->exp,tmp->next->val);
		if(err!=OK)
		{
			freePoly(clone);
			return NULL;
		}
	}
	return clone;
}
double findVal(poly *head,int exp)
{
	for(poly *tmp=head;tmp->next!=NULL;tmp=tmp->next)
		{
			if(tmp->next->exp==exp)
				return tmp->next->val;
		}
	return 0;
}
int printPoly(poly *thisPoly)
{
	printf("(%.4f,%i)",thisPoly->val,thisPoly->exp);
	return OK;
}
int foreachPoly(poly *head,int (* method)(poly *thisPoly))
{
	for(poly *tmp=head;tmp->next!=NULL;tmp=tmp->next)
	{
		method(tmp->next);
	}
	return OK;
}
poly *addPoly(poly *p1,poly *p2)
{
	int err;
	poly *sum=clonePoly(p1);
	IF_NULL_RET_NULL(sum);
	for(poly *tmp=p2;tmp->next!=NULL;tmp=tmp->next)
		{
			err=addPolyNode(sum,tmp->next->exp,tmp->next->val);
			if(err!=OK)
				{
					freePoly(sum);
					return NULL;
				}
		}
	return sum;
}
poly *subPoly(poly *p1,poly *p2)
{
	int err;
	poly *sub=clonePoly(p1);
	IF_NULL_RET_NULL(sub);
	for(poly *tmp=p2;tmp->next!=NULL;tmp=tmp->next)
		{
			err=addPolyNode(sub,tmp->next->exp,0.0-(tmp->next->val));
			if(err!=OK)
				{
					freePoly(sub);
					return NULL;
				}
		}
	return sub;
}
int crossPolyNode(poly *head,double val,int exp)
{
	for(poly *tmp=head;tmp->next!=NULL;tmp=tmp->next)
		{
			tmp->next->exp+=exp;
			tmp->next->val*=val;
		}
	return OK;
}
poly *crossPoly(poly *p1,poly *p2)
{
	int err;
	poly *cross=polyInit();
	IF_NULL_RET_NULL(cross);
	for(poly *tmp=p2;tmp->next!=NULL;tmp=tmp->next)
		{
			poly *crossNode=clonePoly(p1);
			if(crossNode==NULL)
				{
					freePoly(cross);
					return NULL;
				}
			crossPolyNode(crossNode,tmp->next->val,tmp->next->exp);
			poly *sum=addPoly(cross,crossNode);
			if(sum==NULL)
				{
					freePoly(cross);
					freePoly(crossNode);
					return NULL;
				}
			freePoly(cross);
			cross=sum;
		}
	return cross;
}
poly *divPoly(poly *p1,poly *p2)
{
	int err;
	poly *div=polyInit();
	if(p2->next==NULL||p1->next==NULL)
		return div;
	if(div==NULL)
		return NULL;
	poly *divTmp1=clonePoly(p1);
	if(divTmp1==NULL)
		{
			freePoly(div);
			return NULL;
		}
	poly *divTmp2=clonePoly(p2);
	if(divTmp2==NULL)
		{
			freePoly(div);
			freePoly(divTmp1);
			return NULL;
		}	
	int exp1=p1->next->exp;
	int exp2=p2->next->exp;	
	int loop=p1->next->exp-p2->next->exp;
	double val2=findVal(divTmp2,exp2);
	for(int i=loop;i>=0;i--)
		{
			double val1=findVal(divTmp1,i+exp2);
			
			crossPolyNode(divTmp2,val1/val2,i);
			err=addPolyNode(div,i,val1/val2);
			if(err!=OK)
				{
					freePoly(div);
					freePoly(divTmp1);
					freePoly(divTmp2);
					return NULL;
				}
			poly *sub=subPoly(divTmp1,divTmp2);
			if(sub==NULL)
				{
					freePoly(div);
					freePoly(divTmp1);
					freePoly(divTmp2);
					return NULL;
				}
			freePoly(divTmp1);
			divTmp1=sub;
			freePoly(divTmp2);
			divTmp2=clonePoly(p2);
			if(divTmp2==NULL)
				{
					freePoly(div);
					freePoly(divTmp1);
					return NULL;
				}
		}
	freePoly(divTmp1);
	freePoly(divTmp2);
	return div;
}
poly *modPoly(poly *p1,poly *p2)
{
	int err;
	poly *div=polyInit();
	if(p2->next==NULL||p1->next==NULL)
		return div;
	if(div==NULL)
		return NULL;
	poly *divTmp1=clonePoly(p1);
	if(divTmp1==NULL)
		{
			freePoly(div);
			return NULL;
		}
	poly *divTmp2=clonePoly(p2);
	if(divTmp2==NULL)
		{
			freePoly(div);
			freePoly(divTmp1);
			return NULL;
		}	
	int exp1=p1->next->exp;
	int exp2=p2->next->exp;	
	int loop=p1->next->exp-p2->next->exp;
	double val2=findVal(divTmp2,exp2);
	for(int i=loop;i>=0;i--)
		{
			double val1=findVal(divTmp1,i+exp2);
			
			crossPolyNode(divTmp2,val1/val2,i);
			err=addPolyNode(div,i,val1/val2);
			if(err!=OK)
				{
					freePoly(div);
					freePoly(divTmp1);
					freePoly(divTmp2);
					return NULL;
				}
			poly *sub=subPoly(divTmp1,divTmp2);
			if(sub==NULL)
				{
					freePoly(div);
					freePoly(divTmp1);
					freePoly(divTmp2);
					return NULL;
				}
			freePoly(divTmp1);
			divTmp1=sub;
			freePoly(divTmp2);
			divTmp2=clonePoly(p2);
			if(divTmp2==NULL)
				{
					freePoly(div);
					freePoly(divTmp1);
					return NULL;
				}
		}
	freePoly(div);
	freePoly(divTmp2);
	return divTmp1;
}
double calPoly(poly *head,double x)
{
	double result=0;
	for(poly *tmp=head;tmp->next!=NULL;tmp=tmp->next)
		{
			result+=tmp->next->val*pow(x,tmp->next->exp);
		}
	return result;
}
int dPoly(poly *head)
{
	for(poly *tmp=head;tmp->next!=NULL;tmp=tmp->next)
		{
			tmp->next->val*=tmp->next->exp;
			if(tmp->next->exp!=0)
				tmp->next->exp--;
			else
				{
					free(tmp->next);
					tmp->next=NULL;
				}
		}
	return OK;
}
int s1Poly(poly *head)
{
	for(poly *tmp=head;tmp->next!=NULL;tmp=tmp->next)
		{
			tmp->next->val/=tmp->next->exp+1;
			tmp->next->exp++;
		}
	return OK;
}
double s2Poly(poly *head,double x1,double x2)
{
	poly *tmpPoly=clonePoly(head);
	if(tmpPoly==NULL)
		return 0;
	s1Poly(tmpPoly);
	double result=calPoly(tmpPoly,x2)-calPoly(tmpPoly,x1);
	freePoly(tmpPoly);
	return result;
}
poly *expPoly(poly *head,int x)
{
	poly *exp=clonePoly(head);
	if(exp==NULL)
		return NULL;
	for(int i=1;i<x;i++)
		{
			poly *tmp=crossPoly(exp,head);
			if(tmp==NULL)
				{
					freePoly(exp);
					return NULL;
				}
			freePoly(exp);
			exp=tmp;
		}
	return exp;
}
char *polyToStr(poly *head)
{
	char *str=MALLOC_NUM(char,STR_SIZE);
	IF_NULL_RET_NULL(str);
	sprintf(str,"\0");
	char *ptr=str;
	for(poly *tmp=head;tmp->next!=NULL;tmp=tmp->next)
		{
			ptr+=sprintf(ptr,"(%.4f,%i)",tmp->next->val,tmp->next->exp);
		}
	return str;
}
			
poly *strToPoly(char *str)
{
	if(str==NULL)
		return NULL;
	poly *new=polyInit();
	IF_NULL_RET_NULL(new);
	char *ptr=str;
	int err;
	while(*ptr!='\0')
		{
			if(*ptr=='(')
				{
					double val;
					int exp;
					sscanf(ptr,"(%lf,%i)",&val,&exp);
					err=addPolyNode(new,exp,val);
					if(err!=OK)
						{
							freePoly(new);
							return NULL;
						}
				}
			ptr++;
		}
	return new;
}
