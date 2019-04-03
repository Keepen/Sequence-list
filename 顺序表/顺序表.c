#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
//˳��������ɾ���ġ���
typedef struct SList
{
	int *arr;		//��¼��̬����Ĵ�С
	int size;		//��¼˳�����ЧԪ�صĸ���
	int capacity;
}SList;

//����
void SListExpand(SList* list)
{
	//���ݵ�������size=capacity
	if (list->size >= list->capacity)
	{
		//�ȷ���һ����ԭ�����������ڴ�ռ�������µ�˳���
		int Newcapacity = list->capacity * 2;
		int *Newarr = (int *)malloc(sizeof(int)*Newcapacity);
		//��ʼת������
		for (int i = 0; i < list->size; i++)
		{
			Newarr[i] = list->arr[i];
		}
		free(list->arr);
		list->arr = Newarr;
		list->capacity = Newcapacity;
	}
	printf("%d\n", list->capacity);
	return;
}


//��ʼ��˳���:����ЧԪ�صĸ����ÿ�
void SListInit(SList *list,int capacity)
{
	//������Ϊcapacity��˳�����г�ʼ��������
	//�ȷ����ڴ�
	//������ЧԪ�صĸ�����0
	list->arr = (int *)malloc(sizeof(int)*capacity);
	assert(list->arr != NULL);
	list->size = 0;
	list->capacity = capacity;
	return;
}
//���룺ͷ��
void SListInsertFront(SList *list,int value)
{
	//�Ƚ�Ԫ�ؽ��к��ƣ��ٽ��в������
	for (int i = list->size; i > 0; i--)
	{
		list->arr[i] = list->arr[i - 1];
	}
	list->arr[0] = value;
	list->size++;
	return;
}
//β��
void SListInsertTail(SList *list, int value)
{
	//���ð���Ԫ�أ�ֱ�ӽ��и�ֵ����
	list->arr[list->size] = value;
	list->size++;
	return;
}
//��ָ��λ��pos������
void SListInsert(SList *list, int pos, int value)
{
	//��pos���Ԫ��ȫ������ƶ�һ��
	for (int i = list->size; i > pos; i--)
	{
		list->arr[i] = list->arr[i - 1];
	}
	list->arr[pos] = value;
	list->size++;
	return;
}

//ɾ��:ͷɾ
void SListDeleteFront(SList *list)
{
	//�����е�Ԫ��ǰ��һ��λ�ü���
	for (int i = 0; i < list->size; i++)
	{
		list->arr[i] = list->arr[i + 1];
	}
	list->size--;
	return;
}

//βɾ
void SListDeleteTail(SList *list)
{
	list->size--;
	return;
}

//��ָ��λ��pos��ɾ��
void SListDelete(SList *list, int pos)
{
	//��posλ�ú��Ԫ�ض���ǰ�ƶ�һ��λ�ü���
	for (int i = pos; i < list->size; i++)
	{
		list->arr[i] = list->arr[i + 1];
	}
	list->size--;
	return;
}


//����ĳһ��ֵ������˳���
int* SListFindvalue(SList *list, int value)
{
	//
	int i,j;
	int *count = (int *)malloc(sizeof(int)*list->size);		//������¼�Ѳ鵽Ŀ�����ֵ��±�
	for (i = 0,j = 0; i < list->size; ++i) {
		if (list->arr[i] == value) {
			count[j] = i;
			printf("�ҵ��������±��ǣ�%d  \n", count[j]);			
			++j;
		}
		else if (i >= list->size) {
			free(count);		//������޴��������ͷ�������¼�±������Ŀռ�
			count = NULL;		//��������ָ���
			printf("δ�ҵ�����������\n");
			return NULL;
		}
	}
}

//ɾ��˳����е�ĳһ��ֵ:ֻɾ����һ������������ʱ��
void SListDeletevalue(SList *list, int value)
{
	//�Ȳ�ѯ����
	int* findvalue = SListFindvalue(&list, value);
	if (findvalue == NULL)
	{
		printf("���޴������޷�ɾ��������\n");
	}
	else if (findvalue != NULL)
	{
		//��ʼ����ɾ��������ֻɾ����һ��
		SListDelete(&list, findvalue[0]);
	}
	return;
}


//����
void SListDestory(SList *list)
{
	free(list->arr);
	list->arr == NULL;
	list->size = 0;
	list->capacity = 0;
	
	printf("����˳���\n");
	return;
}


//���˳���
void SListPrint(SList *list)
{
	if (list->arr == NULL)
	{
		printf("˳���Ϊ�գ�����\n");
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
	SListInit(&list,10);			//��ʼ��
	SListInsertFront(&list,10);		//ͷ��
	SListInsertFront(&list, 10);		//ͷ��

	SListInsertTail(&list, 20);		//β��
	SListInsert(&list, 1, 30);		//ָ��λ�ò���
	SListPrint(&list);				//��ӡ˳���
	SListExpand(&list);
	SListFindvalue(&list, 10);

	//SListDeleteFront(&list);		//ͷɾ
	//SListDeleteTail(&list);			//βɾ
	SListDelete(&list, 1);			//ָ��λ��ɾ��

	//SListDestory(&list);			//����
	SListPrint(&list);				//��ӡ˳���
	system("pause");
	return 0;
}