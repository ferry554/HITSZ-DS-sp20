#include <stdio.h>
#include <string.h>

// 以字符串的形式表示数字
typedef struct nString{
   char strNum[1002];
   int length;
}nString;
// 也可自行决定存储结构

nString arr[1002];

// 比较两个字符串，可自定义参数或自定义函数
int cmpStr(nString fir,nString sec)
{
   //若位数不一样可直接判断大小
   if(fir.length>sec.length)
    return 1;
   if(fir.length<sec.length)
    return -1;
    //若位数相同，则从最高位开始依次比较每位数字
   if(fir.length==sec.length)
   {
       for(int i=0;i<fir.length;i++)
       {
            if(fir.strNum[i]==sec.strNum[i])
                continue;
            if(fir.strNum[i]>sec.strNum[i])
                return 1;
            if(fir.strNum[i]<sec.strNum[i])
                return -1;
       }
    }
    return 0;///fir 大于 sec 为1，小于为-1，等于为0
}

//请实现排序算法,可自定义参数
void resort(nString *arr, int low, int high)
{
    if (low < high)
    {
        int i = low;
        int j = high;
        nString k = arr[low];//简单起见，选第一个元素作为哨兵
        while (i < j)//i和j向中间查找
        {
            while(cmpStr(arr[j],k)>=0)// 从右向左找第一个小于k的数
                j--;
            if(i < j)//由于在循环内部改变了j的值，故从此往后需要再重新判断i和j的大小关系，若相遇则停止操作
                arr[i++] = arr[j];
            while(i < j && cmpStr(arr[i],k)<0)// 从左向右找第一个大于等于k的数
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

int main(void){
   int num;
   int caseNum = 0;

   // 文件输入方式
   freopen("5_2_input.in", "r", stdin);
   while(scanf("%d",&num)!=EOF){
       caseNum++;
       printf("==== Case %d ====\n",caseNum);
       for(int i = 0; i < num; i++){
           scanf("%s",arr[i].strNum);
           arr[i].length = strlen(arr[i].strNum);
       }
       resort(arr,0,num-1);
       for(int i = 0; i < num; i++){
           printf("%s\n",arr[i].strNum);
       }
   }
   fclose(stdin);


   /*while(scanf("%d",&num)!=EOF){
       caseNum++;
       printf("==== Case %d ====\n",caseNum);
       for(int i = 0; i < num; i++){
           scanf("%s",arr[i].strNum);
           arr[i].length = strlen(arr[i].strNum);
       }
       resort(arr,0, num-1);
       for(int i = 0; i < num; i++){
           printf("%s\n",arr[i].strNum);
       }
   }*/

}


