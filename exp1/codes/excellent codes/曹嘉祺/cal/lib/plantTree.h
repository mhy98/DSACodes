int plantTree(tree *root,char *str,elem *head)
{
	//ptr point to string's head subptr go follow chars
	char *ptr=str;
	char *subPtr=str;

	//ptr point to (
	for(ptr=str;!ifLeft(*ptr);ptr++);

	//ptr point to first letter after (
	for(;ifBlank(*ptr)||ifLeft(*ptr);ptr++);
	subPtr=ptr;

	//root->left is func node there must be a func and rights are elems
	int functag=0;
	int err;
	while(TRUE)
		{
			//name
			if(ifLetter(*ptr))
				{

					for(subPtr=ptr;*subPtr!=' '&&!ifRight(*subPtr);subPtr++)
						{
							//only letters are allowed in func/elem name
							if(!ifLetter(*subPtr))
								return NAMEERR;
						}
					//save the name
					char *name=readLen(ptr,subPtr-ptr);
					IF_NULL_DO_RET_OF(name,freeTree(root));

					//creat func node
					if(functag==0)
						{
							err=treeAddL(root,FUNC,FUNC,name);
							IF_NOT_OK_DO_RET(err,freeTree(root));
							functag=1;
						}
					else
						{
							//elem *elem=findElem(head,name);
							int type;
							
							//if the elem was quote
							//if(elem==NULL)
							type=UNSET;
							//else
							//type=elem->type;
							
							err=treeAddR(root,type,ELEM,name);
							IF_NOT_OK_DO_RET(err,freeTree(root));
						}
					//move ptr and sub ptr to next noblank char 
					for(;*subPtr==' ';subPtr++);
					ptr=subPtr;
					
				}
			//number
			else if(ifNum(*ptr)||*ptr=='-')
				{
					//point tag num without point is int ,else float
					int point=0;
					
					//check if num in law
					for(subPtr=ptr+1;*subPtr!=' '&&!ifRight(*subPtr);subPtr++)
						{
							if(*subPtr=='.'&&point==0)
								point=1;
							else if(*subPtr=='.'&&point==1)
								return NUMERR;
							if(!ifNum(*subPtr)&&*subPtr!='.')
								return NUMERR;
						}
					char *num=readLen(ptr,subPtr-ptr);
					IF_NULL_DO_RET_OF(num,freeTree(root));

					//this is a func!?
					if(functag!=1)
						return FUNCNAMEERR;
					
					int type;
					if(point==0)
						type=INT;
					else if(point==1)
						type=FLOAT;
					
					err=treeAddR(root,type,ELEM,num);
					IF_NOT_OK_DO_RET(err,freeTree(root));

					//same to above
					for(;*subPtr==' ';subPtr++);
					ptr=subPtr;
				}
			//state
			else if(ifLeft(*ptr))
				{

					if(functag!=1)
						{
							return FUNCNAMEERR;
						}
					tree *newRoot;
					err=treeAddR(root,UNSET,EVAL,NULL);
					IF_NOT_OK_DO_RET(err,freeTree(root));

					//move to the node added
					for(newRoot=root;newRoot->right!=NULL;newRoot=newRoot->right);
					newRoot=newRoot->left;
					
					err=plantTree(newRoot,ptr,head);
					IF_NOT_OK_DO_RET(err,freeTree(root));
					//go to the brac end
					int brac=1;
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
			//string
			else if(*ptr=='"')
				{
					//func name cant be string
					if(functag!=1)
						{
							return FUNCNAMEERR;
						}
					//subptr mark the position of next "
					for(subPtr=ptr+1;*subPtr!='"';subPtr++);
						
					char *str=readLen(ptr+1,subPtr-ptr-1);
					IF_NULL_DO_RET_OF(str,freeTree(root));

					err=treeAddR(root,STR,ELEM,str);
					IF_NOT_OK_DO_RET(err,freeTree(root));

					subPtr++;
					for(;*subPtr==' ';subPtr++);
					ptr=subPtr;
				}
			//)
			else if(ifRight(*ptr))
				{
					return OK;
				}
		}
	
	return OK;
}
