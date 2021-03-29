#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>
int start[1002];
int end[1002];

int arr[2004];

void QuickSort(int *arr, int low, int high)
{
    //运用平均情况下较快的快速排序的思想
    if (low < high)
    {
        int i = low;
        int j = high;
        int k = arr[i];//简单起见，选第一个元素作为哨兵
        while (i < j)//i和j向中间查找
        {
            while(arr[j] >= k)     // 从右向左找第一个小于k的数
                j--;
            if(i < j)//由于在循环内部改变了j的值，故从此往后需要再重新判断i和j的大小关系，若相遇则停止操作
                arr[i++] = arr[j];
            while(i < j && arr[i] < k)      // 从左向右找第一个大于等于k的数
                i++;
            if(i < j)
                arr[j--] = arr[i];
            //消除左右两边的逆序对
        }
        arr[i] = k;//哨兵元素插入位
        QuickSort(arr, low, i - 1);     //对k的左边进行递归排序
        QuickSort(arr, i + 1, high);    //对k的右边进行递归排序
    }
}


int DeleteRepetition(int *a,int anum)
{
    //去除数组中重复元素并返回去重后元素个数
    for (int i=0;i<anum-1;i++)
    {
        for (int j=i+1;j<anum;)//此时第三个表达式空出，因为当找到重复的数据，后面的数往前覆盖之后，应该再进行一次对比
        {
            if (a[i]==a[j])//判断如果出现相同数据，则将后面的数据往前移一位
            {
                for (int k=j;k<anum-1;k++)
                {
                a[k]=a[k+1];
                }
                anum--;//记录数组长度的变量相应减1
            }
            else
            {
                j++;//当没有重复的时候才++
            }
        }
    }
    int length=anum;
    return length;
}



void process(int *a,int *b,int M)
{
    //按题目三要求打印出所有不同空闲时段的开始时间和结束时间
    int i,j,number;
    for(i=0;i<M;i++)
    {
        arr[i]=a[i];
    }
    for(i=M;i<M*2;i++)
    {
        arr[i]=b[i-M];
    }
    //先将start存储到arr中，紧接其后再将end存储到arr中。
    QuickSort(arr,0,M*2-1);
    number=DeleteRepetition(arr,M*2);//number即为输入的2M个时间段中所真正包含的时间段总数
    int Condition[M][number];
    for(j=0;j<number;j++)
    {
        for(i=0;i<M;i++)
        {
            Condition[i][j]=0;//初始化全为0
        }
    }
    for(j=0;j<number;j++)
    {
        for(i=0;i<M;i++)
        {
            if(arr[j]>=a[i]&&arr[j]<=b[i])
            {
                Condition[i][j]=1;
                //如果一个时间段属于一个学生的空闲时间，二维数组中的对应位置就被置为1
            }
        }
    }
    int personnum[number];//对所有时间段统计空闲人数
    for(i=0;i<number;i++)
    {
        personnum[i]=0;
    }
    for(j=0;j<number;j++)
    {
        for(i=0;i<M;i++)
        {
            if(Condition[i][j]==1)
            {
                personnum[j]++;
            }
        }
    }//遍历condition的每列，统计1的个数即可，第i列的1的个数存储进personnum的第i分量
    int max=personnum[0];
    for(i=1;i<number;i++)
    {
        if(personnum[i]>max)
            max=personnum[i];
    }//在personnum中迭代求空闲人数的最大值
    int key[M],count=0;
    //Key保存personnum中拥有最多空闲人数时间段的地址
    //count统计拥有最多空闲人数时间段的数目
    for(i=0;i<number;i++)
    {
        if(personnum[i]==max)
        {
            key[count]=i;
            count++;
        }
    }
    //设立与key等长数组mark对key中元素，即所有拥有最多空闲人数的时间段进行分类标记
    int mark[M],marknum=1;
    //具体标记数用marknum存储。属于同一大空闲时间段的空闲时间的标记都相等
    for(i=0;i<count;i++)
    {
        mark[i]=0;
    }//先将mark中count个元素都置为0
    mark[0]=1;//第一个置为1
    for(i=1;i<count;i++)
    {//检查key中剩余数据
        if(key[i]-key[i-1]!=1)
        {//与前一个数据相差超过1，说明为不挨着的空闲时间段，不可能属于同一大时间段
            marknum++;
            mark[i]=marknum;
        }//marknum增一并标记，表明与前一个不同
        else
        {
            for(j=0;j<M;j++)
            {//根据key中存储的地址到condition中验证这两个时间段的具体情况
                if(Condition[j][key[i]]!=Condition[j][key[i-1]])
                {//若出现有一个学生在这两个时间段空闲状况不一样，则说明属于不一样的大空闲时间段
                    marknum++;
                    mark[i]=marknum;
                    break;//marknum增一并标记，表明与前一个不同
                }
                //若没有找到，说明与前一个属于相同大空闲时间段，marknum不变，标记，表明与前一个相同
            }
            mark[i]=marknum;
        }
    }
    struct{
        int s;
        int e;

    } address[count];//指示一个大空闲时间段的起始时间和终止时间
    int AddressAmount=0;//统计实际大空闲时间段的个数
    address[0].s=key[0];//第一个分量的s被置为key的第一个元素
    for(i=1;i<count;i++)
    {
        if(mark[i]==mark[i-1])
            continue;//若这一个元素的标记等于上一个，说明属于同一个大空闲时间段
        else
        {
            AddressAmount++;
            address[AddressAmount-1].e=key[i-1];
            address[AddressAmount].s=key[i];
            //若不等于，则将key中该位置前一个元素赋给address中前一个元素的e，key中该位置元素赋给address中该位置元素的s
        }
    }
    address[AddressAmount].e=key[count-1];//将最后一个分量的e置为key的最后一个元素
    for(i=0;i<=AddressAmount-1;i++)
    {
        printf("%d %d,",arr[address[i].s],arr[address[i].e]);
    }
    printf("%d %d\n",arr[address[AddressAmount].s],arr[address[AddressAmount].e]);
    //根据address中存储的地址找到arr中相应元素，格式化输出即可
}



int main()
{
   int N, M; //分别存储时间的段数和学生的个数
   int caseNum = 0;


   freopen("5_3_input.in", "r", stdin);
   while(scanf("%d %d",&N,&M)!=EOF){
       caseNum++;
       printf("==== Case %d ====\n",caseNum);
       for(int i = 0; i < M;i++){
           scanf("%d %d",&start[i],&end[i]);
       }
       process(start,end,M);
   }
   fclose(stdin);


   /*while(scanf("%d %d",&N,&M)!=EOF){
       caseNum++;
       printf("==== Case %d ====\n",caseNum);
       for(int i = 0; i < M;i++){
           scanf("%d %d",&start[i],&end[i]);
       }
       process(start,end,M);
   }*/

}
