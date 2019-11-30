//state
#define FUNC	0
#define EVAL	1
#define ELEM	2
#define LINK	3
char *stateToStr(int state)
{
	switch(state)
		{
		case FUNC:
			return "FUNC";
		case EVAL:
			return "EVAL";
		case ELEM:
			return "ELEM";
		case LINK:
			return "LINK";
		default :
			return "UNKNOWN";
		}
}
struct treeNode
{
	int type;
	int state;
	char *elem;
	struct treeNode *left;
	struct treeNode *right;
};
typedef struct treeNode tree;

tree *treeInit()
{
	tree *root=MALLOC(tree);
	IF_NULL_RET_NULL(root);
	root->type=UNSET;
	root->state=EVAL;
	root->elem=NULL;
	root->left=NULL;
	root->right=NULL;
	
	return root;
}
int treeAddL(tree *root,int type,int state,char *elem)
{
	tree *left=MALLOC(tree);
	IF_NULL_RET_OF(left);
	left->type=type;
	left->state=state;
	left->elem=elem;
	root->left=left;
	left->left=NULL;
	left->right=NULL;
	return OK;
}
int treeAddR(tree *root,int type,int state,char *elem)
{
	tree *tmp;
	for(tmp=root;tmp->right!=NULL;tmp=tmp->right);
	tmp->right=MALLOC(tree);
	IF_NULL_RET_OF(tmp->right);
	tmp=tmp->right;
	tmp->left=NULL;
	tmp->right=NULL;
	tmp->type=UNSET;
	tmp->state=LINK;
	tmp->elem=NULL;
	int err=treeAddL(tmp,type,state,elem);
	if(err==OF)
		{
			free(tmp);
			return OF;
		}
	return OK;
}
		
		
int freeTree(tree *root)
{
	if(root==NULL)
		return OK;
	else
		{
			freeTree(root->left);
			freeTree(root->right);
			free(root->elem);
			free(root);
			return OK;
		}
}
int setTree(tree *node,char *elem,int type,int state)
{
	if(elem!=NULL)
		{
			node->elem=copyStr(elem);
			IF_NULL_RET_OF(node->elem);
		}
	else
		node->elem=NULL;
	node->type=type;
	node->state=state;
	return OK;
}

int copyTree(tree *root,tree **copyPtr)
{
	tree *copy;
	tree *left;
	tree *right;
	if(root==NULL)
		{
			*copyPtr=NULL;
			return OK;
		}
	int err=copyTree(root->left,&left);
	IF_NOT_OK_RET(err);
	err=copyTree(root->right,&right);	
	IF_NOT_OK_RET(err);
	copy=treeInit();
	IF_NULL_DO_RET_OF(copy,do{freeTree(left);freeTree(right);}while(0));
	err=setTree(copy,root->elem,root->type,root->state);
	IF_NOT_OK_RET(err);
	copy->right=right;
	copy->left=left;
	*copyPtr=copy;
	return OK;
}
int argNum(tree *root)
{
	if(root==NULL)
		return -1;
	int i=0;
	for(tree *tmp=root;tmp->right!=NULL&&tmp->right->left!=NULL;tmp=tmp->right)
		i++;

	return i;
}
			
int argCheck(tree *root,int num)
{
	int i=argNum(root);
	if(i==num)
		return OK;
	else
		return ARGNUMERR;
}
int argTypeCheck(tree *root,int index,int type,int state)
{
	int num=argNum(root);
	if(num<index)
		return ARGNUMERR;

	tree *node=root;
	for(int i=0;i<index;i++)
		{
			node=node->right;
		}
	node=node->left;
	if(node->type!=type||node->state!=state)
		return ARGTYPEERR;
	return OK;
}
			
int printTree(tree *root)
{
	for(tree *tmp=root;tmp!=NULL;tmp=tmp->right)
		printf("node:%i,%i,%s\n",tmp->left->type,tmp->left->state,tmp->left->elem);
	return OK;
}
