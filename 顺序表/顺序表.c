#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
//顺序表的增、删、改、查
typedef struct SList
{
	int *arr;		//记录动态数组的大小
	int size;		//记录顺序表有效元素的个数
	int capacity;
}SList;

//扩容
void SListExpand(SList* list)
{
	//扩容的条件：size=capacity
	if (list->size == list->capacity)
	{
		//先分配一个比原来大两倍的内存空间来存放新的顺序表
		int Newcapacity = list->capacity * 2;
		int *Newarr = (int *)malloc(sizeof(int)*Newcapacity);
		//开始转移数据
		for (int i = 0; i < list->size; i++)
		{
			Newarr[i] = list->arr[i];
		}
		free(list->arr);
		list->arr = Newarr;
		list->capacity = Newcapacity;
	}
	return;
}







//初始化顺序表:将有效元素的个数置空
void SListInit(SList *list,int capacity)
{
	//将容量为capacity的顺序表进行初始化操作：
	//先分配内存
	//即将有效元素的个数置0
	list->arr = (int *)malloc(sizeof(int)*capacity);
	assert(list->arr != NULL);
	list->size = 0;
	list->capacity = capacity;
	return;
}
//插入：头插
void SListInsertFront(SList *list,int value)
{
	//先将元素进行后移，再进行插入操作
	for (int i = list->size; i > 0; i--)
	{
		list->arr[i] = list->arr[i - 1];
	}
	list->arr[0] = value;
	list->size++;
	return;
}
//尾插
void SListInsertTail(SList *list, int value)
{
	//不用搬运元素，直接进行赋值即可
	list->arr[list->size] = value;
	list->size++;
	return;
}
//在指定位置pos处插入
void SListInsert(SList *list, int pos, int value)
{
	//将pos后的元素全部向后移动一格
	for (int i = list->size; i > pos; i--)
	{
		list->arr[i] = list->arr[i - 1];
	}
	list->arr[pos] = value;
	list->size++;
	return;
}

//删除:头删
void SListDeleteFront(SList *list)
{
	//将所有的元素前移一个位置即可
	for (int i = 0; i < list->size; i++)
	{
		list->arr[i] = list->arr[i + 1];
	}
	list->size--;
	return;
}

//尾删
void SListDeleteTail(SList *list)
{
	list->size--;
	return;
}

//在指定位置pos处删除
void SListDelete(SList *list, int pos)
{
	//将pos位置后的元素都向前移动一个位置即可
	for (int i = pos; i < list->size; i++)
	{
		list->arr[i] = list->arr[i + 1];
	}
	list->size--;
	return;
}


//查找某一个值：遍历顺序表
typedef struct Find			//用来记录要查找的数字的信息，该数字的个数以及位置
{
	int count;
	int *find_pos;
}Find;
Find* SListFindvalue(SList *list, int value)
{
	int i = 0;
	Find find;
	find.count = 0;
	Find *find_add=&find;
	find_add->find_pos = (int*)malloc(sizeof(int)*list->size);//为存储位置信息的变量分配内存
	assert(find_add->find_pos != NULL);
	for (i = 0; i < list->size; i++)
	{
		//遍历整个顺序表，找寻value
		if (list->arr[i] == value)
		{
			//将value的下标存放在find_pos数组中
			find.find_pos[find.count] = i;
			find.count++;			
		}
	}
	if (find.count == 0)
	{
		return NULL;
	}
	return find_add;
}

//删除顺序表中的某一个值:只删除第一次遇到该数的时候
void SListDeletevalue(SList *list, int value)
{
	//先查询此数
	Find * findvalue = SListFindvalue(&list, value);
	if (findvalue->count == 0)
	{
		printf("查无此数，无法删除！！！\n");
	}
	else if (findvalue->count > 0)
	{
		//开始进行删除操作：只删除第一个
		SListDelete(&list, findvalue->find_pos[0]);
	}
	return;
}


//销毁
void SListDestory(SList *list)
{
	free(list->arr);
	list->arr == NULL;
	list->size = 0;
	list->capacity = 0;
	
	printf("销毁顺序表！\n");
	return;
}


//输出顺序表
void SListPrint(SList *list)
{
	if (list->arr == NULL)
	{
		printf("顺序表为空！！！\n");
		return;
	}

	for (int i = 0; i < list->size; i++)
	{
		printf("%-3d", list->arr[i]);
	}
	printf("\n");
	return;
}





int main()
{
	SList list;
	SListInit(&list,10);			//初始化
	SListInsertFront(&list,10);		//头插
	SListInsertFront(&list, 10);		//头插

	SListInsertTail(&list, 20);		//尾插
	SListInsert(&list, 1, 30);		//指定位置插入
	SListPrint(&list);				//打印顺序表

	Find *find_value = SListFindvalue(&list, 10);		//查找某个值
	if (find_value->count == 0)
	{
		printf("查无此数！！！\n");
	}
	else if (find_value->count > 0)
	{
		printf("顺序表中一共有%d个该数字！！！\n下标分别是：\n",find_value->count);
		for (int i = 0; i < find_value->count; i++)
		{		
			printf("%-3d", find_value->find_pos[i]);
		}
	}

	//SListDeleteFront(&list);		//头删
	//SListDeleteTail(&list);			//尾删
	//SListDelete(&list, 1);			//指定位置删除

	//SListDestory(&list);			//销毁
	//SListPrint(&list);				//打印顺序表
	system("pause");
	return 0;
}