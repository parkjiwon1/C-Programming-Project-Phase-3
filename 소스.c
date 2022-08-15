#pragma warning (disable:6031)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct tel //����ü ����
{
	char* name;
	char *tel_no;
	char *birth;
}tel;

void insert(tel** p, int* count, int MAX_NUM); //���� �Է� �޴� �Լ�
void print_all(tel** p, int* count); //show all �Լ�
void delete_tel(tel** p, int* count); //���� ���� �Լ�
void find_by_birth(tel** p, int* count); //���� ã�� �Լ�  ��� �Լ��� ����ü �迭�� ���� �ּҿ� count�� �ּҸ� ���ڷ� �޴´�. �ּҷ� �޴� ������ count�� �Լ� ������ ���ϱ� ����
void RegFromFile(tel **p, int* count,int MAX_NUM); //���Ͽ��� ����ó ������ �������� �Լ�
void SortFile(int count); //��� �۾��� ���� �� ���Ͽ� ���ĵ��� ���� �������� �����ؼ� �޸��忡 ���� ���� �Լ�
int main(void)
{
	int MAX_NUM;
	struct tel **tel_list= NULL; //����ü �迭 100��ŭ ����
	int count = 0, N,count1=0;
	printf("Max_num:");
	scanf("%d", &MAX_NUM); //MAX_NUM �Է¹���

	tel_list = (tel**)malloc(sizeof(tel*) * MAX_NUM); //MAX_NUM ��ŭ ����ü ������ �迭 �Ҵ�
	if (tel_list == NULL) //üũ
	{
		printf("Not Enough Memory");
		return -1;
	}
	while (1) //5 �Է� ���� �� ���� �ݺ�
	{
		if (count1 == 1)
		{
			break;
		}
		printf("*****Menu*****\n");
		printf("<1.Registration><2.ShowAll><3.Delete><4.FindByBirth><5.RegFromFile><6.Exit>\n");
		printf("Enter_the_menu_number:"); //�޴� ���

		scanf("%d", &N); //N�Է� ����

		switch (N) //N�� ����
		{
		case 1: insert(tel_list, &count,MAX_NUM); break; //1�̸� insert
		case 2: print_all(tel_list, &count); break; //2�� print
		case 3: delete_tel(tel_list, &count); break; //3�̸� ����
		case 4: find_by_birth(tel_list, &count); break; //4�� ���� ã��
		case 5: RegFromFile(tel_list, &count,MAX_NUM); break; //5�� ���Ϸκ��� �о ���α׷��� ����
		case 6: count1++; //6�̸� ���α׷� ����
		}

	}
	SortFile(count); //�����ؼ� �޸��忡 ����
	for (int i = 0; i < count; i++)
	{
		free(tel_list[i][0].name);
		free(tel_list[i][0].tel_no);
		free(tel_list[i][0].birth); //����ü ����� ���� ����
		free(tel_list[i]); //����ü �迭 ����
	}
	free(tel_list); //����ü ������ �迭 ����
	return 0;
}
void insert(tel** p, int* count,int MAX_NUM)
{
	if (*count >= MAX_NUM) //������ 100���� �������
	{
		printf("OVERFLOW\n"); //���ܻ�Ȳ ���
		return;
	}
	FILE* fp;
	if (*count == 0) { //ó�� �޸����� ����Ǿ��� ��� ���� ���� �ҷ���
		fp = fopen("PHONE_BOOK.txt", "w");
	}
	else // �ι�° ���ʹ� ���� �ٿ��� �ϱ� ������ append ���� �ҷ���
	{
		fp = fopen("PHONE_BOOK.txt", "a");
		fputc('\n', fp); //���๮�ڸ� �޸��忡 ������ ����
	}
	if (fp == NULL) //üũ
	{
		printf("Couldn't open file");
		return;
	}

	char tmp[1000]; //��� ���� tmp ����
	p[*count] = (tel*)malloc(sizeof(tel) * 1); //������ �� ����ü �迭 �����Ҵ�
	if (p[*count] == NULL) //üũ
	{
		printf("Not Enough Memory");
		return;
	}

	printf("Name:");
	scanf("%s", tmp); 
	int len1 = strlen(tmp); 
	p[*count][0].name = (char*)malloc(sizeof(char) * (len1 + 1)); //tmp�� �Է¹��� �� ���ڿ��� ����+1��ŭ �޸� �Ҵ�
	strcpy(p[*count][0].name, tmp); //�Ҵ� ���� �޸𸮿� ���ڿ� ����
	fputs(tmp, fp); fputc(' ', fp); // ���Ͽ� ù��° ���ڿ� ����, ���� ���� ����

	printf("Phone_number:");
	scanf("%s", tmp);
	int len2 = strlen(tmp);
	p[*count][0].tel_no = (char*)malloc(sizeof(char) * (len2 + 1)); //tmp�� �Է¹��� �� ���ڿ��� ����+1��ŭ �޸� �Ҵ�
	strcpy(p[*count][0].tel_no, tmp); //�Ҵ� ���� �޸𸮿� ���ڿ� ����
	fputs(tmp, fp); fputc(' ', fp); // ���Ͽ� �ι�° ���ڿ� ����, ���� ���� ����

	printf("Birth:");
	scanf("%s", tmp); 
	int len3 = strlen(tmp);
	p[*count][0].birth = (char*)malloc(sizeof(char) * (len3 + 1)); //tmp�� �Է¹��� �� ���ڿ��� ����+1��ŭ �޸� �Ҵ�
	strcpy(p[*count][0].birth, tmp); //���� �Է¹���
	fputs(tmp, fp); // ���Ͽ� ������ ���ڿ� ����

	for (int i = *count; i > 0; i--) //�ڿ��� ���� ���� �̸��� ���������� �տ� �ִ� �������� ������� ��ȯ,����
	{
		if (strcmp(p[i][0].name, p[i - 1][0].name) < 0) //���������� �������
		{
			tel *tmp1 = p[i];
			p[i] = p[i - 1];
			p[i - 1] = tmp1; //��ȯ
		}
	}
	(*count)++; //���������� ������ ���� ++
	printf("<<%d>>\n", *count); // ���� ���

	fclose(fp); //���� ������ �ݱ�
	return;
}
void print_all(tel** p, int* count)
{
	for (tel** q = p; q < p + *count; q++) //��� ���� ����Ʈ
	{
		printf("%s %s %s\n", q[0]->name, q[0]->tel_no, q[0]->birth);
	}
	return;
}
void delete_tel(tel** p, int* count)
{
	char tmp[21]; int index = 0;
	if (*count == 0) //���� �ƹ� ������ ���� ���
	{
		printf("NO MEMBER\n"); //���� ���
		return;
	}

	printf("Name:");
	scanf("%s", tmp); //tmp�� ����

	for (int i = 0; i < *count; i++) //���� ����ŭ �ݺ�
	{
		if (strcmp(p[i][0].name, tmp) == 0) //�Էµ� ���ڿ��� ���ٸ�
		{
			index = i; //�� ���ڿ��� �ּ� ����
			break;
		}
		index = -1; //���ٸ� -1
	}
	if (index == -1) //���� ���ڿ��� ���ٸ� �׳� �ѱ�
	{
		return;
	}

	for (int i = index + 1; i < *count; i++) //������ ����ü�� ���� �ڷ� �̷�
	{
		tel* tmp = p[i - 1];
		p[i - 1] = p[i];
		p[i] = tmp;
	}

	free(p[*count - 1][0].name);
	free(p[*count - 1][0].tel_no);
	free(p[*count - 1][0].birth);
	free(p[*count - 1]); //���� ���� ����ü�� ��� �޸� ����(����)

	(*count)--; //������ -1
	return;
}
void find_by_birth(tel** p, int* count)
{
	char tmp[3];

	printf("Birth:");

	scanf("%s", tmp); //birth�� ���ڿ��� ����
	if (strlen(tmp) == 1) //���� ���ڸ� ���� ���
	{
		tmp[1] = tmp[0];
		tmp[0] = '0';
		tmp[2] = '\0'; //��ĭ �ڷ� ���ڸ� ���� �� �տ� 0�߰��� ���� �ι��� �־���
	}

	for (int i = 0; i < *count; i++)
	{
		if (strncmp(&p[i][0].birth[4], tmp, 2) == 0) //index 4����(�޸� ��) 2�ڸ� ���� ���ؼ� ���ٸ�
		{
			printf("%s %s %s\n", p[i][0].name, p[i][0].tel_no, p[i][0].birth); //���
		}
	}
}
void RegFromFile(tel** p, int* count,int MAX_NUM)//���Ͽ��� ����ó ������ �������� �Լ�
{
	int len = 0, cnt = 0;int cnt3 = 0; int index = *count;
	FILE* fp = fopen("PHONE_BOOK.txt", "r"); //�б� ���� ���� ����
	if (fp == NULL) //üũ
	{
		printf("Couldn't open file\n");
		return;
	}
	if (*count >= MAX_NUM) //�߰��Ϸ��µ� �ִ� �������� ������ �̹� ���� ������� ���
	{
		printf("OVERFLOW\n");
		return;
	}
	char st[1000];
	char tmp[3][1000];
	while (!feof(fp)) //������ ������ ����
	{
		if (*count >= MAX_NUM) //���࿡ �߰��ϸ鼭 ������ �ִ� ������ �Ѿ ��� ����
		{
			printf("OVERFLOW\n");
			break;
		}

		fgets(st, sizeof(st), fp); //�� ���� �о��
		for (char* q = st; q < st + 1000; q++)
		{
			for (char* r = q; r < st + 1000; r++) //�ܾ� �и�
			{
				if (*r == '\0')
				{
					strcpy(tmp[cnt], q);
					if (!feof(fp)) { //������ ������ ������ �ƴ� ��� ���๮�ڰ� �ֱ� ������ 
						tmp[cnt][len - 1] = '\0'; //len-1�� �ι��ڸ� ����
					}
					else
					{
						tmp[cnt][len] = '\0'; //������ ������ ������ ��� ���๮�ڰ� ���� ������ len�� �ι��� ����
					}
					cnt++;
					q = r;
					break;
				}
				if (*r == ' ') //������ ���ڿ� �ܾ� �и��� ����
				{
					strcpy(tmp[cnt], q);
					tmp[cnt][len] = '\0';
					cnt++;
					q = r;
					break;
				}
				len++;
			}
			len = 0;
			if (*q == '\0')
			{
				break;
			}
		}
		p[*count] = (tel*)malloc(sizeof(tel) * 1); //���� ����ü �迭�� �����Ҵ� ����
		int len1 = strlen(tmp[0]);
		p[*count][0].name = (char*)malloc(sizeof(char) * (len1 + 1)); //�и��� �ܾ� ù��°�� name
		if (p[*count][0].name == NULL) //�Ҵ� üũ
		{
				printf("Not Enough Memory");
				return;
		}
		strcpy(p[*count][0].name, tmp[0]); //�ܾ� ����, ����ü �迭�� ����

		len1 = strlen(tmp[1]); //�и��� �ܾ� �ι�°�� ��ȭ��ȣ
		p[*count][0].tel_no = (char*)malloc(sizeof(char) * (len1 + 1));
		if (p[*count][0].tel_no == NULL) //�Ҵ� üũ
		{
			printf("Not Enough Memory");
			return;
		}
		strcpy(p[*count][0].tel_no , tmp[1]); //�ܾ� ����, ����ü �迭�� ����

		len1 = strlen(tmp[2]); //����° �ܾ�� birth
		p[*count][0].birth = (char*)malloc(sizeof(char) * (len1 + 1)); //�ܾ� ���� ��ŭ �Ҵ�
		if (p[*count][0].birth == NULL)
		{
			printf("Not Enough Memory");
			return;
		}
		strcpy(p[*count][0].birth, tmp[2]); //�ܾ� ����, ����

		cnt3++; //�޸����� ���� ���� ���� ����++
		(*count)++; //���� �þ����� count++
		cnt = 0; //cnt �ʱ�ȭ
	}
	for (int i = *count-1; i > 0; i--) //�ڿ��� ���� ���� �̸��� ���������� �տ� �ִ� �������� ������� ��ȯ,����
	{
		if (strcmp(p[i][0].name, p[i - 1][0].name) < 0) //���������� �������
		{
			tel* tmp1 = p[i];
			p[i] = p[i - 1];
			p[i - 1] = tmp1; //��ȯ
		}
	}

	fclose(fp); //���� �ݱ�
}
void SortFile(int count)//��� �۾��� ���� �� ���Ͽ� �����ؼ� �����ϱ� ���� �Լ�
{
	int cnt = 0, len = 0, cnt3 = 0;
	FILE* fp = fopen("PHONE_BOOK.txt", "r"); //���� �б� ���� ������ �ҷ���
	if (fp == NULL) //üũ
	{
		printf("Couldn't open file\n");
		return;
	}
	char st[1000]; //�޸����� ���ڿ��� ��� ������ st
	char tmp[100][3][1000]; //�޸����� ���ڿ��� �и��ؼ� ������ tmp
	while (!feof(fp)) //������ ������ ����
	{
		fgets(st, sizeof(st), fp); //�� ���� �о��
		for (char* q = st; q < st + 1000; q++)
		{
			for (char* r = q; r < st + 1000; r++) //�ܾ� �и�
			{
				if (*r == '\0')
				{
					strcpy(tmp[cnt3][cnt], q);
					if (!feof(fp)) { //������ ������ ������ �ƴ� ��� ���๮�ڰ� �ֱ� ������ 
						tmp[cnt3][cnt][len - 1] = '\0'; //len-1�� �ι��ڸ� ����
					}
					else
					{
						tmp[cnt3][cnt][len] = '\0'; //������ ������ ������ ��� ���๮�ڰ� ���� ������ len�� �ι��� ����
					}
					cnt++;
					q = r;
					break;
				}
				if (*r == ' ') //������ ���ڿ� �ܾ� �и��� ����
				{
					strcpy(tmp[cnt3][cnt], q);
					tmp[cnt3][cnt][len] = '\0';
					cnt++;
					q = r;
					break;
				}
				len++;
			}
			len = 0;
			if (*q == '\0')
			{
				break;
			}
		}
		cnt3++; //�޸��� ���� ����
		cnt = 0; //cnt �ʱ�ȭ
	}

	fclose(fp); //�б��� ����

	fp = fopen("PHONE_BOOK.txt", "w"); //���� ���� ��� ����
	if (fp == NULL) //üũ
	{
		printf("Couldn't open file\n");
		return;
	}

	for (int i = 0; i < cnt3; i++) //cnt3 = �޸��� ���� ���� ��ŭ �ݺ�
	{
		for (int k = i+1; k < cnt3; k++) //���� ����
		{
			if (strcmp(tmp[i][0], tmp[k][0]) > 0) //�̸� ������ ����
			{
				char tmp1[100]; char tmp2[100]; char tmp3[100]; //��ȯ�� �ʿ��� tmp�� ���� ����

				strcpy(tmp1, tmp[i][0]);
				strcpy(tmp2, tmp[i][1]);
				strcpy(tmp3, tmp[i][2]); 

				strcpy(tmp[i][0], tmp[k][0]);
				strcpy(tmp[i][1], tmp[k][1]);
				strcpy(tmp[i][2], tmp[k][2]);

				strcpy(tmp[k][0], tmp1);
				strcpy(tmp[k][1], tmp2);
				strcpy(tmp[k][2], tmp3); //�ٲ��� �ϴ� �� ���� ��� �ܾ �ٲ�
			}
		}
	}
	
	for (int i = 0; i < cnt3; i++) //���Ͽ� �������� �ݺ��� ����
	{
		for (int k = 0; k < 3; k++) { //������ 3��
			fputs(tmp[i][k], fp); //fputs�� �̿��� �޸��忡 ��
			if (k != 2) {
				fputc(' ', fp); //���� ���ڸ� 3���� �ܾ� ���̿� 2�� �־���
			}
		}
		if (i != cnt3 - 1) //�� ������ ��� ������ ���� ���๮�� ����, ��� ������ ���� ���������� ���๮�� �������� ����
		{
			fputc('\n', fp); //���๮�� ����
		}
	}
	fclose(fp); //���� ���� ��� ����
}