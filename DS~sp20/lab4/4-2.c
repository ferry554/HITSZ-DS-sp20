#include <stdio.h>
#include <stdlib.h>
/**图的邻接矩阵存储方式*/
#define    MaxInt 32767 //极大值，即无穷大
#define    MVNum  100  //最大顶点数
typedef   struct
{
    int vexs[MVNum];   //顶点表
    int arcs[MVNum][MVNum];    //邻接矩阵
    int vexnum,arcnum;    //图的当前点数和边数
    int nums,nume;  //图的当前输入层神经元个数和输出层神经元个数
}  AMGraph ;

/**采用邻接矩阵表示法创建带权值的有向无环图表示神经网络，顶点表示神经元*/
AMGraph* CreateUDN(int nvex,int narc,int ns,int ne)
{
    AMGraph *G=(AMGraph*)malloc(sizeof(AMGraph));
    if(!G) exit(-2);
    int v1,v2,w;
    G->vexnum=nvex;
    G->arcnum=narc;
    G->nums=ns;
    G->nume=ne;//初始化网络的基本信息
    for(int i=0;i<G->vexnum;i++)
    {
        G->vexs[i]=0;//各顶点的信息均初始化为0，方便计算权值
    }
    for(int i=0;i<G->vexnum;i++)
    {
        for(int j=0;j<G->vexnum;j++)
        {
            G->arcs[i][j]=MaxInt;//初始化邻接矩阵，边的系数均置为无穷大
        }
    }
   for(int i=0;i<G->arcnum;i++)
   {
      scanf("%d%d%d",&v1,&v2,&w);//输入一条边依附的顶点和它的系数
        G->arcs[v1-1][v2-1]=w;//边<v1,v2>系数置为w，创建有向边
   }
   for(int i=0;i<G->nums;i++)
   {
       scanf("%d",&G->vexs[i]);//读入输入层各神经元权值
   }
    return G;//返回指向该图的指针
}

int ans[MVNum];//存储每个输出层神经元的权值

/**在G指向的神经网络中实现正向传播算法*/
void forward_propagation(AMGraph *G)
{
    for(int i=G->nums;i<G->vexnum;i++)//计算隐藏层和输出层各神经元的权值
    {
        for(int j=0;j<i;j++)//对于一个神经元，遍历在其之前的神经元
        {
            if(G->arcs[j][i]!=MaxInt)//发现两个神经元之间有边相连
            {
                G->vexs[i] += G->vexs[j]*G->arcs[j][i];//将前面神经元的权值乘两神经元之间的边的系数，加到后面神经元上
            }
        }///对于一神经元，其权值被置为所有有边指向它的神经元权值乘指向它的边的系数之和，实现了正向传遍
    }
    int n=G->vexnum-G->nume;
    for(int i=0;i<G->nume;i++)//将输出层神经元的权值存储进结果数组中
    {
        ans[i] = G->vexs[i+n];
    }
}

int main()
{
    int vexn,arcn,s,e;
    freopen("4_2_input.in", "r", stdin);
    while(scanf("%d%d%d%d",&vexn,&arcn,&s,&e)!=EOF)
    {

        AMGraph *g=CreateUDN(vexn,arcn,s,e);
        forward_propagation(g);
        for (int i = 0;i<e;i++)
        {
            printf(i < e-1 ? "%d " : "%d\n", ans[i]);
            //为格式需要，每个网络中最后一神经元权值打印出后要换行打印下一网络的信息
        }

    }
    fclose(stdin);

    return 0;


}

