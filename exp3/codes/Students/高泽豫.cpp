#include <stdlib.h>
#include <stdio.h>
#define STR_MAX_LEN 100010
#define NODE_MAX 20010
#define DEPTH_MAX 10010
char str[STR_MAX_LEN]; //, *pos = str;
struct BitTree
{
    int data;
    BitTree *lchild, *rchild;
};
BitTree tree_nodes[NODE_MAX];
BitTree *queue[NODE_MAX];
BitTree *p_tree = tree_nodes;
unsigned short tree_alloc;
unsigned short queue_head, queue_tail, number_of_node, num_has_outputed, depth, maxdepth;
int output[NODE_MAX];
void bfs(BitTree *root)
{
    queue[queue_head++] = root;
    while (queue_head != queue_tail)
    {
        BitTree *c = queue[queue_tail++];
        output[num_has_outputed++] = c->data;
        if (c->lchild)
            queue[queue_head++] = c->lchild;
        if (c->rchild)
            queue[queue_head++] = c->rchild;
    }
}
#define ISDIGITAL(c) ((c) >= '0' && (c) <= '9')
int pos, data;
BitTree *create()
{
    if (str[++pos] == '}')
    {
        if (depth > maxdepth)
            maxdepth = depth;
        return nullptr;
    }
    BitTree *new_tree = &(tree_nodes[tree_alloc++]);
    output[++depth]++;
    new_tree->lchild = create();
    pos += 2, data = 0;
    while (ISDIGITAL(str[pos]))
        data = (data << 3) + (data << 1) + str[pos++] - '0'; //num[cnt++] = *(pos++);
    number_of_node++;
    new_tree->data = data;
    pos++;
    new_tree->rchild = create();
    pos++, depth--;
    return new_tree;
}
void pre_order(BitTree *root)
{
    if (!root)
        return;
    output[num_has_outputed++] = root->data;
    pre_order(root->lchild);
    pre_order(root->rchild);
}
int main()
{
    fgets(str, STR_MAX_LEN, stdin);
    BitTree *tree = create();
    unsigned short max_num_of_depth = 0;
    unsigned short depth_has_max_num = 0;
    for (register unsigned short i = 1; i <= maxdepth; i++)
        if (output[i] >= max_num_of_depth)
            max_num_of_depth = output[i], depth_has_max_num = i;
    num_has_outputed = 0;
    pre_order(tree);
    for (register unsigned short i = 0; i < num_has_outputed - 1; i++)
    {
        printf("%d,", output[i]);
    }
    printf("%d\n", output[num_has_outputed - 1]);
    num_has_outputed = 0;
    bfs(tree);
    for (register unsigned short i = 0; i < num_has_outputed - 1; i++)
    {
        printf("%d,", output[i]);
    }
    printf("%d\n", output[num_has_outputed - 1]);
    printf("%d\n", depth_has_max_num);
    printf("%d\n", max_num_of_depth);
    printf("%d", maxdepth);
    return 0;
}