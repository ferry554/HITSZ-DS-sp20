
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OVERFLOW -2


typedef struct Node
{
    char data;
    struct Node *lchild, *rchild;
} TreeNode, *BiTree; //定义树节点的结构体

BiTree bt2=NULL;//采用全局变量，便于操作

BiTree createBiTree()//先序建立二叉树
{
    BiTree T;
    char ch;
    scanf("%c",&ch);
    if(ch=='#')  T=NULL;//空树返回空指针
    else
    {
        T=(TreeNode*)malloc(sizeof(TreeNode));
        if(!T)
            exit(OVERFLOW);
        T->data=ch;//读入第一个字符作为根节点
        /**递归建立左右子树*/
        T->lchild=createBiTree();
        T->rchild=createBiTree();
    }
    return T;


}
void preOrderTraverse(BiTree p)//函数功能：前序遍历
{
    if(p)
    {
        printf("%c",p->data);
        preOrderTraverse(p->lchild);
        preOrderTraverse(p->rchild);
    }
    return;
}

void inOrderTraverse(BiTree p)//函数功能：中序遍历
{
    if(p)
    {
        inOrderTraverse(p->lchild);
        printf("%c",p->data);
        inOrderTraverse(p->rchild);
    }
    return;
}

void postOrderTraverse(BiTree p)//函数功能：后序遍历
{
    if(p)
    {
        postOrderTraverse(p->lchild);
        postOrderTraverse(p->rchild);
        printf("%c",p->data);
    }
    return;
}

BiTree PostInCreate(char in[],char post[],int n)
{
    //根据中序和后序序列建立一棵二叉树*/
    BiTree T;
    int count;
    T=(BiTree)malloc(sizeof(TreeNode));
    if(T==NULL)
        exit(OVERFLOW);
    if(n==0)
        return NULL;//输入空树返回空指针
    T->data=post[n-1];/**后序序列的最后一个字符即为根节点数据*/
    for(int i=0;i<n;i++)/**在中序序列中查找根节点位置*/
    {
        if(in[i]==T->data)
        {
            count = i;//得到根节点在中序序列的位置
            break;
        }
        if(i==n-1)/**没有找到，说明不能构造*/
        {
            printf("Unable to build a binary tree");
            exit(0);
        }
    }
    /**中序序列中根节点的前后分别为左子树和右子树*/
    T->lchild = PostInCreate(in,post,count);
    T->rchild = PostInCreate(in+count+1,post+count,n-count-1);/**递归建立左子树和右子树*/
    return T;
}
int countLeafSum(BiTree root)
{
//函数功能：计算叶子节点数
    int numl,numr;
    if(root==NULL)//空树
        return 0;
    else if((root->lchild==NULL)&&(root->rchild==NULL))//只有一个根节点
        return 1;
    else
    {
        numl = countLeafSum(root->lchild);
        numr = countLeafSum(root->rchild);
        return numl+numr;/**一棵树的叶子节点数等于左子树和右子树的叶子数之和*/
    }
}

int maxwidth(BiTree T)/**借鉴二叉树层序遍历的思想，找到结点最多的那一层*/
 {     //求二叉树的宽度
    int i,front=0,rear=0,max=0,maxlev[10]={0};
    struct
    {
        BiTree Node;
        int Nodelev;
    }Q[50];/**用数组实现一个队列，数据元素为指向树的节点的指针以及结点所在层次构成的结构体*/
    Q[front].Node=T;
    Q[front].Nodelev=1;//根节点
    while(front<=rear)//队列不空时
    {
        if(Q[front].Node->lchild)//队头节点的左或者右子树不空，则将其入队
            {
                Q[++rear].Node=Q[front].Node->lchild;
                Q[rear].Nodelev=Q[front].Nodelev+1;
            }
        if(Q[front].Node->rchild)
            {
                Q[++rear].Node=Q[front].Node->rchild;
                Q[rear].Nodelev=Q[front].Nodelev+1;
            }
        front++;//队头节点出队
    }
    for(i=0;i<=rear;i++)
        maxlev[Q[i].Nodelev]++;
    for(i=0;i<10;i++)//寻找最大值
        if(max<maxlev[i])
            max=maxlev[i];
    return max;
}

int isEquivalent(BiTree bt1,BiTree bt2)
{
   //函数功能：判断两树是否等价
    //参数说明：bt1:第一个二叉树，bt2:第二个二叉树
    int x=0;
    if((bt1==NULL)&&(bt2==NULL))//若两棵树均为空，则等价
        x=1;
    else if ( (bt1!=NULL) && (bt2!=NULL) )
        if (  bt1->data== bt2->data  )//若根节点数据相同，依次比较左子树和右子树
            if ( isEquivalent(bt1->lchild,bt2->lchild) )
                  x= isEquivalent(bt1->rchild,bt2->rchild);//若左子树等价，则整棵树等价性取决于右子树等价性
    return( x ) ;
}




void task1(BiTree bt){
    //任务1：实现二叉树先序、中序、后序遍历
    printf("start task (1) Create Tree in PreOrder\n");
    printf("preOrderTraverse\n");
    preOrderTraverse(bt);
    printf("\n");
    printf("inOrderTraverse\n");
    inOrderTraverse(bt);
    printf("\n");
    printf("postOrderTraverse\n");
    postOrderTraverse(bt);
    printf("\n");
}

/**合并了任务2和3*/
void task2and3(){

    printf("start task (2) Input the postOrder and inOrder Sequence ,Then build the tree\n");
    char post[20];  //后序序列
    char in[20];    //中序序列

    printf("please input the postorder sequence\n");
    scanf("%s",post);
    printf("please input the inorder sequence\n");
    scanf("%s",in);
    //请完善函数
    if(strlen(post)!=strlen(in))/**序列长度不一致*/
    {
        printf("Unable to build a binary tree");
        return;
    }
    int len=strlen(in);

    int i,j;/**序列所含字符不一致*/
    for(i=0;i<len;i++)
    {
        /**对post中每个字符查找in中是否存在*/
        for(j=0;j<len;j++)
        {
            if(post[i]==in[j])
                break;
            if(j==len-1)
            {
                /**对当前字符的查找遍历了整个in，说明在in中不存在，不一致*/
                printf("Unable to build a binary tree");
                return;
            }
        }

    }

    bt2=PostInCreate(in,post,len);
    printf("preOrderTraverse:\n");
    preOrderTraverse(bt2);
    printf("\n");
    printf("start task (3) ------------------------------\n");


    printf("The number of leaf nodes of the tree is:\n");
    printf("%d\n",countLeafSum(bt2));
    printf("The widht of the tree is:\n");
    printf("%d\n",maxwidth(bt2));

}




void task4(BiTree bt1,BiTree bt2){
    //任务4：判断两个二叉树是否等价
    //使用函数：isEquivalent
    printf("start task (4) Are two Bitrees equivalent?\n");
    printf("%d\n",isEquivalent(bt1,bt2));

}
int main()
{
    BiTree bt1=NULL;
    printf("Create Tree1 in PreOrder\n");
    bt1=createBiTree();

    task1(bt1);


    task2and3();/**合并了任务2和3*/

    task4(bt1,bt2);

    return 0;
}

