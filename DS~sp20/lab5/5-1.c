#include <stdio.h>
#include <stdlib.h>
struct twonum///由两个数组成的结构体，存储所有该题中要求输出的绝对值差最小的数对
{
    int little;//数对中较小的数
    int big;//数对中较大的数
}dou[2001];//最多可能有2002-1个这样的数对，即排序后形成等差数列

int arr[2002];//存储输入数据

//请实现排序算法,可自定义参数
void resort(int *arr, int low, int high)
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
        resort(arr, low, i - 1);     //对k的左边进行递归排序
        resort(arr, i + 1, high);    //对k的右边进行递归排序
    }
}

//找到最邻近数字对,可自定义参数
void findClosestPair(int *arr, int num)
{
    int min = arr[1]-arr[0],k=0;
    for(int i=1;i<num-1;i++)
    {
        if(arr[i+1]-arr[i]<min)
        {
            min = arr[i+1]-arr[i];//找到绝对值差的最小值
        }
    }
    for(int i=0;i<num-1;i++)
    {
        if(arr[i+1]-arr[i]==min)//有一数对绝对值差等于最小值，符合要求，记录在dou数组中
        {
            dou[k].little=arr[i];
            dou[k].big=arr[i+1];
            k++;
        }
    }
    for(int i=0;i<k-1;i++)
    {
        printf("%d %d,",dou[i].little,dou[i].big);
    }
    printf("%d %d\n",dou[k-1].little,dou[k-1].big);//打印出所有满足题意的数对
}


int main(){
    int num;
    int caseNum = 0;

    // 文件输入方式
    freopen("5_1_input.in", "r", stdin);
    while(scanf("%d",&num)!=EOF){
        caseNum++;
        printf("==== Case %d ====\n",caseNum);
        for(int i = 0; i < num; i++){
            scanf("%d",&arr[i]);
        }
        resort(arr,0,num-1);
        findClosestPair(arr, num);
    }
    fclose(stdin);



    /*while(scanf("%d",&num)!=EOF){
        caseNum++;
        printf("==== Case %d ====\n",caseNum);
        for(int i = 0; i < num; i++){
            scanf("%d",&arr[i]);
        }
        resort(arr,0,num-1);
        findClosestPair(arr, num);

    }*/


    return 0;
}
