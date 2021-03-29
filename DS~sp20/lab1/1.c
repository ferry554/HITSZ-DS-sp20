#include <stdlib.h>
#include <stdio.h>

typedef struct node{
    int ClassID;
    int StuID;
    int Grade;
    struct node *next;
}StudentLinkedListNode;


/* 打印单个节点 */
void printLinkedListNode(StudentLinkedListNode * node){
    printf("{Class:%d, ID:%d, Grade:%d}",node->ClassID, node->StuID, node->Grade);
    if(node->next!=NULL){
        printf("->");
    }else
    {
        printf("\n");
    }

}

/* 输出该表的成绩情况 */
void outputStudentLinkedList(StudentLinkedListNode* head){
    // 用于单个节点输出的函数printLinkedListNode已提供
    //请你实现遍历链表的逻辑
    //TODO
    StudentLinkedListNode* p = head;
    while(p)   //当指针p非空时，即p指向链表中某一结点时，执行循环
    {
        printLinkedListNode(p);//输出该节点
        p = p->next;//p指针向后移动一个节点，当其指向空指针时说明链表已完成遍历，结束循环
    }
}


/** 新建一个链表node并返回 */
StudentLinkedListNode* studentLinkedListCreate(int class_id,int student_id,int grade) {
    //tips:malloc的时候记得为转化为结构体指针
    //TODO
    StudentLinkedListNode* p = (StudentLinkedListNode*)malloc(sizeof(StudentLinkedListNode));
    //为结构体中相应数据赋值
    p->ClassID = class_id;
    p->StuID = student_id;
    p->Grade = grade;
    p->next = NULL;
    return p;
}

/** copy一个已有的node */
StudentLinkedListNode* studentLinkedListCopy(StudentLinkedListNode* src){

    StudentLinkedListNode* p = studentLinkedListCreate(src->ClassID,src->StuID,src->Grade);
    return p;
}



/** 按照降序插入学生的成绩情况,并返回链表头指针 */
StudentLinkedListNode* studentLinkedListAdd(StudentLinkedListNode* head, StudentLinkedListNode* node) {
//TODO
    StudentLinkedListNode* p = head;
    /**头指针为空，即链表不存在*/
    if(!p)
    {
        p = node;
        return p;
    }
    /**头节点的数据单独处理*/
    if(p->Grade < node->Grade)//当前节点成绩大于头节点
    {
        node->next = p;
        p = node;//将当前节点插入头节点之前
        return p;
    }
    //不考虑上述两种情况会在某些情况下引起程序异常结束
    /**在后续链表节点中查找插入位置*/
    while ((p->next)&&(p->Grade > node->Grade)) //当前节点成绩小于p节点
    {
        p = p->next;  //向后移动指针p
                      //直到p为最后一个节点或当前节点成绩大于p节点
    }
    node->next = p->next;
    p->next = node;  //将当前节点插入p节点之前
    return head;
}

/** 根据学号查找某个学生的成绩情况 如果没有,请printf("the linklist has no such node as id=%d",id);*/
void searchByID(StudentLinkedListNode*head ,int id){
//TODO
    StudentLinkedListNode* p = head;
    while((p->next)&&(p->StuID!=id))
    {
        p = p->next;  //当p节点ID不等于id且p不是最后节点，则后移p节点进行查找
    }
    if(p->StuID == id)
    {
        printLinkedListNode(p);  //输出其ID等于id的p节点
    }
    else
    {
        printf("the linklist has no such node as id=%d",id);//打印错误信息
    }
}

/** 根据学号删除某个学生的成绩情况 如果没有,请printf("the linklist has no such node as id=%d",id);*/
StudentLinkedListNode* deleteByID(StudentLinkedListNode* head,int id){
//TODO
    StudentLinkedListNode* p = head;
    /**对头结点进行单独处理*/
    if(p->StuID == id)
    {
        printLinkedListNode(p);
        p = p->next;
        printf("\nthe student %d is deleted\n",id);  //打印删除成功的提示
        return p;
    }
    while((p->next)&&(p->next->next)&&(p->next->StuID!=id))
    {
        //若不判断p->next->next是否为空指针则删除最后一个节点时程序会崩溃
        p = p->next;  //当p节点ID不等于id且p不是最后节点，则后移p节点进行查找
    }
    if(p->next->StuID == id)
    {
        printLinkedListNode(p->next);  //输出其ID等于id的p节点
        p->next=p->next->next;   //删除p节点
        printf("\nthe student %d is deleted\n",id);  //打印删除成功的提示
    }
    else
    {
        printf("the linklist has no such node as id=%d",id);  //打印错误信息
    }
    return head;
}


/** 合并两个班级的成绩情况 */
StudentLinkedListNode* mergeLinkedList(StudentLinkedListNode* heads[]){
    //tips:因为传入的都是指针,为了防止拆分过程中影响了原来总链表的存储,
    //在链表node赋值的时候可以用上面提供的studentLinkedListCopy函数
    //如 node->next = temp_node 改为 node->next = studentLinkedListCopy(temp_node)
    //StudentLinkedListNode**Class=(StudentLinkedListNode**)malloc(2*sizeof(StudentLinkedListNode*));
    //TODO
    /**创建一新的空学生节点并置为list3的头节点*/
    StudentLinkedListNode* Head = studentLinkedListCreate(0,0,0);
    /**list3用于归并过程*/
    StudentLinkedListNode* list3 = Head;
    /**主函数中定义的heads*/
    StudentLinkedListNode* list1 = heads[0];
    StudentLinkedListNode* list2 = heads[1];
    /**若其中一表为空表，则直接返回另一个表*/
    if(list1== NULL)
    {
        return list2;
    }
    if(list2 == NULL)
    {
        return list1;
    }
    /**两个表都不为空表*/
    while(list1!=NULL && list2!=NULL)
    {
        /**依次比较表1和表2的成绩进行归并,将成绩较大的插入list3中*/
        if(list1->Grade >= list2->Grade)
        {
            //将list1中的该节点插入到list3中，并将list1和list3中的计数指针均后移一位
            list3->next=studentLinkedListCopy(list1);
            list1 = list1->next;
            list3 = list3->next;
        }
        else
        {
            //将list2中的该节点插入到list3中，并将list2和list3中的计数指针均后移一位
            list3->next=studentLinkedListCopy(list2);
            list2 = list2->next;
            list3 = list3->next;
        }
    }
    /**处理一剩余的非空表*/
    if(list1!=NULL)
    {
        list3->next = studentLinkedListCopy(list1);
    }
    if(list2!=NULL)
    {
        list3->next = studentLinkedListCopy(list2);
    }
    return Head->next;
}

/**将总表中信息在新表中翻转打印出*/
StudentLinkedListNode* reverseLinkedList(StudentLinkedListNode*head){
//TODO
    if (head==NULL) //总表为空直接返回空指针
    {
        return NULL;
    }
    StudentLinkedListNode *p = head,*q;
    while(p->next&&p)  //实现反转链表的功能
    {
      q=p->next;
      p->next=p->next->next;
      q->next=head;
      head=q;
    }
    return head;
}


int main(){
        StudentLinkedListNode* Class[2]={NULL};
        StudentLinkedListNode* All=NULL;
        StudentLinkedListNode* reAll=NULL;
        printf("1.insert 2.search by StuID 3.delete by StuID  4.merge 5.output  \n");

        int op;
        int i;

        int tempClass;
        int tempStuId;
        int tempGrade;

        StudentLinkedListNode *p;
        while (scanf("%d", &op) != EOF) {
            switch (op) {
                case 1:
                    printf("How many rows of data do you need to input?\n");
                    scanf("%d",&i);
                    printf("input the i row data format as:class_id,student_id,grade\n");
                    while (i!=0){
                        scanf("%d,%d,%d", &tempClass, &tempStuId, &tempGrade);
                        p = studentLinkedListCreate(tempClass, tempStuId, tempGrade);
                        Class[tempClass]=studentLinkedListAdd(Class[tempClass], p);
                        i--;
                    }
                    break;
                case 2:
                    printf("input thedata format as: ClassID, StuID\n");
                    scanf("%d,%d",&tempClass,&tempStuId);
                    searchByID(Class[tempClass], tempStuId);
                    break;
                case 3:
                    printf("input the data format as: ClassID, StuID\n");
                    scanf("%d,%d",&tempClass,&tempStuId);
                    Class[tempClass]=deleteByID(Class[tempClass], tempStuId);

                    break;
                case 4:
                    All=mergeLinkedList(Class);
                    outputStudentLinkedList(All);
                    break;
                case 5:
                    reAll=reverseLinkedList(All);
                    outputStudentLinkedList(reAll);
                    break;
                case 6:
                    printf("Class 0:\n");
                    outputStudentLinkedList(Class[0]);
                    printf("\nClass 1:\n");
                    outputStudentLinkedList(Class[1]);
                    break;

            }
            printf("\n###################################\n");
            printf("1.insert 2.search by studentID 3.delete by studentID 4.merge 5. reverse 6.output  \n");
    }
}
