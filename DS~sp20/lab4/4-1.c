#include <stdio.h>
#include <stdlib.h>
/**图的邻接矩阵存储方式*/
#define    MaxInt 32767 //极大值，即无穷大
#define    MVNum  100  //最大顶点数
typedef   struct
{
    int vexs[MVNum];   //顶点表
    int arcs[MVNum][MVNum];    //邻接矩阵
    int vexnum,arcnum;    //图的当前

}  AMGraph ;

int start;//谣言起点

/**采用邻接矩阵表示法创建有向网*/
AMGraph* CreateUDN(int nvex,int narc,int ns)
{
    AMGraph *G=(AMGraph*)malloc(sizeof(AMGraph));
    if(!G) exit(-2);
    int v1,v2,w;
    G->vexnum=nvex;
    G->arcnum=narc;
    start=ns;
    //scanf("%d%d%d",&G->vexnum,&G->arcnum,&start);//第一行输入总顶点数，边数，谣言起点
    for(int i=0;i<G->vexnum;i++)
    {
        G->vexs[i]=i+1;//依次输入点的信息
    }
    for(int i=0;i<G->vexnum;i++)
    {
        for(int j=0;j<G->vexnum;j++)
        {
            G->arcs[i][j]=MaxInt;//初始化邻接矩阵，边的权值均置为无穷大
        }
    }
   for(int i=0;i<G->arcnum;i++)
   {
      scanf("%d%d%d",&v1,&v2,&w);//输入一条边依附的顶点和权值
        G->arcs[v1-1][v2-1]=w;//边<v1,v2>权值置为w
   }
    return G;//返回指向该图的指针
}


/**用迪杰斯特拉算法求出谣言起点到其余各点的最短路径，则到所有点最短路径的最大值即为传遍整个图所需最短时间*/
int ShortestPath_DIJ_Answer(AMGraph *G)
{
    int S[MVNum];//记录从起点到终点是否已经被确定最短路径长度
    int D[MVNum];//记录从起点到终点的当前最短路径长度
    int min;
    for(int v=0;v<G->vexnum;v++)
    {
        S[v]=0;//S初始为空集
        D[v]=G->arcs[start-1][v];//将起点到各个终点的最短路径长度初始化为弧上的权值
    }
    int v=0;
    S[start-1]=1;//将起点加入S
    D[start-1]=0;//起点到起点距离为0
    /**开始主循环，每次求得起点到某个顶点v的最短路径，将v加入进S*/
    for(int i=1;i<G->vexnum;i++)
    {
        min=MaxInt;
        for(int w=0;w<G->vexnum;w++)
        {
            if(!S[w]&&D[w]<min)
            {
                v=w;
                min=D[w];
            }//选择一条当前最短路径，终点为v
        }
        S[v]=1;//将v加入S
        for(int a=0;a<G->vexnum;a++)//更新从起点出发到集合V-S上所有顶点的最短路径长度
        {
            if(!S[a]&&(min+G->arcs[v][a]<D[a]))
            {
                D[a]=min+G->arcs[v][a];//更新最短路径长度
            }
        }
    }
    /**若主循环结束后仍有到某点的最短距离为无穷大，则说明图不连通，消息无法传遍整个网络*/
    for(int i=0;i<G->vexnum;i++)
    {
        if(D[i]==MaxInt)
        {
            return -1;
        }
    }
    int answer=0;
    for(int b=0;b<G->vexnum;b++)/**求到所有点最短距离的最大值*/
    {
        if(D[b]>answer)
        {
            answer=D[b];
        }
    }
    return answer;
}

int main()
{
    int vexn,arcn,s;
    freopen("4_1_input.in", "r", stdin);
    while(scanf("%d%d%d",&vexn,&arcn,&s)!=EOF)
    {

        AMGraph *g=CreateUDN(vexn,arcn,s);
        printf("%d\n",ShortestPath_DIJ_Answer(g));

    }
    fclose(stdin);

    return 0;


}





