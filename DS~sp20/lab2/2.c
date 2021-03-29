//头文件
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

//宏定义
#define  TRUE  1
#define  FALSE 0
#define  OK    1
#define  ERROR 0
#define  MAXLEN  100
#define  OVERFLOW   -2
#define  STACK_INIT_SIZE  100
#define  STACKINCREMENT    10
/**本程序中栈可能需要的所有头文件和宏*/


/**栈的顺序结构表示*/
typedef struct
{
    int *base;
    int *top;
    int  stacksize;
}SqStack;

//构建一个空栈
int InitStack(SqStack *S)
{
    S->base = (int*)malloc(STACK_INIT_SIZE*sizeof(int));//分配预定义的存储空间
    if (!S->base)
        exit(OVERFLOW);//存储分配失败
    S->top = S->base; //初始化空栈
    S->stacksize = STACK_INIT_SIZE;
    return OK;
}


//判断栈是否为空
int StackEmpty(SqStack S)
{
    if (S.top == S.base)
        return OK;
    else
        return ERROR;
}

//求栈顶元素
int GetTop(SqStack S)
{
    int e;
    if (S.top == S.base)
        return FALSE;
    else
        e = *(S.top - 1);/**非空栈中栈顶指针始终在栈顶元素下一个位置*/
    return e;
}


//栈顶插入元素
int Push(SqStack *S, int e)
{
    if (S->top - S->base >= STACK_INIT_SIZE)
    {//栈满，追加存储空间
        S->base = (int *)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(int));
        if (!S->base)
        {
            return ERROR;//追加存储分配失败
        }
        S->top = S->base + STACK_INIT_SIZE;//栈底地址可能改变，重新定位栈顶元素
        S->stacksize = S->stacksize + STACKINCREMENT;
    }
    *S->top = e; //插入元素
    S->top++; //栈顶指针上移
    return OK;
}

//删除栈顶元素
int Pop(SqStack *S)
{
    if (S->top == S->base)//空栈，没有可以删的元素
        return ERROR;
    else
    {
        S->top--;/**栈顶指针减一即可，原来元素物理上存在但对后续栈的各种操作无影响*/
        return OK;
    }
}

int SeqLegal(int in[],int out[],int num)
{
    /** 实验内容1:判断输入的出站序列是否可由输入的进站序列通过进出栈得到
     可行返回1，不可行返回0
     */
     int i=0,j=0;
     SqStack S;
     InitStack(&S);/**新建栈，模拟火车站LIFO的特性*/
     for(;i<num;i++)
     {
         Push(&S,in[i]);/**进站序列依次入站*/
         while(!StackEmpty(S)&&GetTop(S)==out[j])
         {/**j从0开始，当前栈不空且栈顶元素与出站序列中首个还未出站元素相符合时则出站*/
             Pop(&S);
             j++;/**考虑出站序列中下一个元素*/
         }
     }
     if(StackEmpty(S))/**最后栈为空，即所有元素按照入站顺序入栈一次后都能按出站顺序出栈一次*/
       {
            return 1;
       }

     else/**栈不空，即不是每个元素都能顺利出栈，说明出站顺序有问题*/
       {
            return 0;
       }

}

typedef struct QueueNode
{
    /** 队列节点 */
    int id;
    struct QueueNode* next;
}QNode;

typedef struct Queue
{
    /** 队列 */
    QNode *front;
    QNode *rear;
    int size;
}LinkQueue;

/**队列的操作中一些程序与栈的思路基本相同，不再额外添加注释*/
LinkQueue* InitQueue()
{
    /** 初始化队列 */
    LinkQueue* Q = (LinkQueue*) malloc(sizeof(LinkQueue));
    Q->front = Q->rear = (QNode *)malloc(sizeof(QNode));//队列头节点
    Q->front->next = NULL;
    Q -> size = 0;
    return Q;
}

int EnQueue(LinkQueue *Q,int ele)
{
    /** 入队 */
    QNode *p=(QNode *)malloc(sizeof(QNode));
    if(!p)
        exit(OVERFLOW);
    p->id =ele;
    p->next=NULL;
    Q->rear->next=p;
    Q->rear=p;
    return 1;//可删除
}

int DeQueue(LinkQueue *Q,int* ele)
{
    /** 出队 */
    if(Q->front==Q->rear)
        return ERROR;
    QNode *p=Q->front->next;
    *ele=p->id;
    Q->front->next=p->next;
    if(Q->rear==p)
        Q->rear =Q->front;
    return 1;//可删除
}

int GetRear(LinkQueue Q)
{
    /**返回队尾元素*/
    return Q.rear->id;
}


int findClosestQueue(LinkQueue *railQueue[],int usedQueue,int curTrain)
{
    /**  找到最合适的火车轨道 */
    int closestIdx;
    if(usedQueue==0)/**还没有用到轨道，即第一个火车进入缓冲轨道*/
    {
        EnQueue(railQueue[0],curTrain);
        return 0;
    }
    else
    {
        for(int i=0;i<usedQueue;i++)/**遍历已存在的所有缓冲轨道*/
        {
            if(curTrain>GetRear(*railQueue[i]))
/**只要最后所有的缓冲轨道上都是数据元素从对头到队尾依次递增，所有火车就能按升序依次开出
   因此使用贪心算法的思想，只要发现队尾元素小于现有元素的队列，即将现有元素插入该队列
   因为从第二个元素开始，所有元素都是按照此规则插入的，
   故最终得到的最后所有的缓冲轨道上都是数据元素从对头到队尾依次递增*/
            {
                EnQueue(railQueue[i],curTrain);
                closestIdx=i;
                return closestIdx;
            }
        }
        /**如果所有队列的队尾元素都大于该元素，那么就将其插入一个新的队列*/
        EnQueue(railQueue[usedQueue],curTrain);
        closestIdx=usedQueue;
        return closestIdx;
    }
}

int minBufferQueue(int out[],int num){
    /** 实验内容2:求解所需缓冲轨道的最小值*/
    LinkQueue *railQueue[num]; //指针数组，记录各缓存轨道的火车，有与火车数相等的轨道数时一定可行
    int i;
    for(i = 0;i < num;i++)/**初始化所有可能用到的队列*/
    {
        railQueue[i] = InitQueue();
    }
    int usedQueue = 0;      //已使用的队列数
    for(i=0;i<num;i++)
    {/**对于所有火车，依次找到最合适轨道并插入*/
        if(findClosestQueue(railQueue,usedQueue,out[i])==usedQueue)
            usedQueue++;/**当其要插入一个新的轨道时，已经使用的轨道数自然要增加1*/
    }
    return usedQueue;
}


int main()
{

    int trainNum;
    int count = 0;
    freopen("TestTrain.in", "r", stdin);

    while(scanf("%d",&trainNum)!=EOF){
        count++;
        int trainIn[trainNum];
        int trainOut[trainNum];
        for(int i = 0;i < trainNum;i++){
            scanf("%d",&trainIn[i]);
        }
        for(int i = 0;i < trainNum;i++){
            scanf("%d",&trainOut[i]);
        }
        printf("====Case %d====\n",count);
        // 实验内容1
        if(SeqLegal(trainIn,trainOut,trainNum)){
            printf("The output train sequence is Possible\n");
        }else{
            printf("The output train sequence is impossible\n");
        }
        // 实验内容2
        printf("To recover the order, %d buffer queue is needed:\n",minBufferQueue(trainOut, trainNum));
    }
    fclose(stdin);
    return 0;
}
