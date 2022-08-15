#pragma warning (disable:6031)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct tel //구조체 선언
{
	char* name;
	char *tel_no;
	char *birth;
}tel;

void insert(tel** p, int* count, int MAX_NUM); //정보 입력 받는 함수
void print_all(tel** p, int* count); //show all 함수
void delete_tel(tel** p, int* count); //정보 삭제 함수
void find_by_birth(tel** p, int* count); //생일 찾는 함수  모든 함수는 구조체 배열의 시작 주소와 count의 주소를 인자로 받는다. 주소로 받는 이유는 count가 함수 내에서 변하기 때문
void RegFromFile(tel **p, int* count,int MAX_NUM); //파일에서 연락처 정보를 가져오는 함수
void SortFile(int count); //모든 작업이 끝난 후 파일에 정렬되지 않은 정보들을 정렬해서 메모장에 쓰기 위한 함수
int main(void)
{
	int MAX_NUM;
	struct tel **tel_list= NULL; //구조체 배열 100만큼 선언
	int count = 0, N,count1=0;
	printf("Max_num:");
	scanf("%d", &MAX_NUM); //MAX_NUM 입력받음

	tel_list = (tel**)malloc(sizeof(tel*) * MAX_NUM); //MAX_NUM 만큼 구조체 포인터 배열 할당
	if (tel_list == NULL) //체크
	{
		printf("Not Enough Memory");
		return -1;
	}
	while (1) //5 입력 받을 때 까지 반복
	{
		if (count1 == 1)
		{
			break;
		}
		printf("*****Menu*****\n");
		printf("<1.Registration><2.ShowAll><3.Delete><4.FindByBirth><5.RegFromFile><6.Exit>\n");
		printf("Enter_the_menu_number:"); //메뉴 출력

		scanf("%d", &N); //N입력 받음

		switch (N) //N에 따라
		{
		case 1: insert(tel_list, &count,MAX_NUM); break; //1이면 insert
		case 2: print_all(tel_list, &count); break; //2면 print
		case 3: delete_tel(tel_list, &count); break; //3이면 삭제
		case 4: find_by_birth(tel_list, &count); break; //4면 생일 찾기
		case 5: RegFromFile(tel_list, &count,MAX_NUM); break; //5면 파일로부터 읽어서 프로그램에 저장
		case 6: count1++; //6이면 프로그램 종료
		}

	}
	SortFile(count); //정렬해서 메모장에 적음
	for (int i = 0; i < count; i++)
	{
		free(tel_list[i][0].name);
		free(tel_list[i][0].tel_no);
		free(tel_list[i][0].birth); //구조체 멤버들 먼저 해제
		free(tel_list[i]); //구조체 배열 해제
	}
	free(tel_list); //구조체 포인터 배열 해제
	return 0;
}
void insert(tel** p, int* count,int MAX_NUM)
{
	if (*count >= MAX_NUM) //정보가 100개가 넘을경우
	{
		printf("OVERFLOW\n"); //예외상황 출력
		return;
	}
	FILE* fp;
	if (*count == 0) { //처음 메모장이 실행되었을 경우 쓰기 모드로 불러옴
		fp = fopen("PHONE_BOOK.txt", "w");
	}
	else // 두번째 부터는 갖다 붙여야 하기 때문에 append 모드로 불러옴
	{
		fp = fopen("PHONE_BOOK.txt", "a");
		fputc('\n', fp); //개행문자를 메모장에 넣으며 시작
	}
	if (fp == NULL) //체크
	{
		printf("Couldn't open file");
		return;
	}

	char tmp[1000]; //대신 받을 tmp 선언
	p[*count] = (tel*)malloc(sizeof(tel) * 1); //정보가 들어갈 구조체 배열 동적할당
	if (p[*count] == NULL) //체크
	{
		printf("Not Enough Memory");
		return;
	}

	printf("Name:");
	scanf("%s", tmp); 
	int len1 = strlen(tmp); 
	p[*count][0].name = (char*)malloc(sizeof(char) * (len1 + 1)); //tmp를 입력받은 후 문자열의 길이+1만큼 메모리 할당
	strcpy(p[*count][0].name, tmp); //할당 받은 메모리에 문자열 복사
	fputs(tmp, fp); fputc(' ', fp); // 파일에 첫번째 문자열 저장, 띄어쓰기 따로 저장

	printf("Phone_number:");
	scanf("%s", tmp);
	int len2 = strlen(tmp);
	p[*count][0].tel_no = (char*)malloc(sizeof(char) * (len2 + 1)); //tmp를 입력받은 후 문자열의 길이+1만큼 메모리 할당
	strcpy(p[*count][0].tel_no, tmp); //할당 받은 메모리에 문자열 복사
	fputs(tmp, fp); fputc(' ', fp); // 파일에 두번째 문자열 저장, 띄어쓰기 따로 저장

	printf("Birth:");
	scanf("%s", tmp); 
	int len3 = strlen(tmp);
	p[*count][0].birth = (char*)malloc(sizeof(char) * (len3 + 1)); //tmp를 입력받은 후 문자열의 길이+1만큼 메모리 할당
	strcpy(p[*count][0].birth, tmp); //정보 입력받음
	fputs(tmp, fp); // 파일에 마지막 문자열 저장

	for (int i = *count; i > 0; i--) //뒤에서 부터 만약 이름이 사전적으로 앞에 있는 정보보다 빠를경우 교환,정렬
	{
		if (strcmp(p[i][0].name, p[i - 1][0].name) < 0) //사전적으로 빠를경우
		{
			tel *tmp1 = p[i];
			p[i] = p[i - 1];
			p[i - 1] = tmp1; //교환
		}
	}
	(*count)++; //성공적으로 들어갔으니 개수 ++
	printf("<<%d>>\n", *count); // 개수 출력

	fclose(fp); //파일 썼으니 닫기
	return;
}
void print_all(tel** p, int* count)
{
	for (tel** q = p; q < p + *count; q++) //모든 정보 프린트
	{
		printf("%s %s %s\n", q[0]->name, q[0]->tel_no, q[0]->birth);
	}
	return;
}
void delete_tel(tel** p, int* count)
{
	char tmp[21]; int index = 0;
	if (*count == 0) //만약 아무 정보도 없을 경우
	{
		printf("NO MEMBER\n"); //예외 출력
		return;
	}

	printf("Name:");
	scanf("%s", tmp); //tmp에 저장

	for (int i = 0; i < *count; i++) //정보 수만큼 반복
	{
		if (strcmp(p[i][0].name, tmp) == 0) //입력된 문자열이 같다면
		{
			index = i; //그 문자열의 주소 저장
			break;
		}
		index = -1; //없다면 -1
	}
	if (index == -1) //같은 문자열이 없다면 그냥 넘김
	{
		return;
	}

	for (int i = index + 1; i < *count; i++) //제거할 구조체를 제일 뒤로 미룸
	{
		tel* tmp = p[i - 1];
		p[i - 1] = p[i];
		p[i] = tmp;
	}

	free(p[*count - 1][0].name);
	free(p[*count - 1][0].tel_no);
	free(p[*count - 1][0].birth);
	free(p[*count - 1]); //제일 뒤의 구조체의 모든 메모리 해제(삭제)

	(*count)--; //정보수 -1
	return;
}
void find_by_birth(tel** p, int* count)
{
	char tmp[3];

	printf("Birth:");

	scanf("%s", tmp); //birth를 문자열로 받음
	if (strlen(tmp) == 1) //만약 한자리 수일 경우
	{
		tmp[1] = tmp[0];
		tmp[0] = '0';
		tmp[2] = '\0'; //한칸 뒤로 숫자를 땡긴 후 앞에 0추가한 다음 널문자 넣어줌
	}

	for (int i = 0; i < *count; i++)
	{
		if (strncmp(&p[i][0].birth[4], tmp, 2) == 0) //index 4부터(달만 비교) 2자리 수를 비교해서 같다면
		{
			printf("%s %s %s\n", p[i][0].name, p[i][0].tel_no, p[i][0].birth); //출력
		}
	}
}
void RegFromFile(tel** p, int* count,int MAX_NUM)//파일에서 연락처 정보를 가져오는 함수
{
	int len = 0, cnt = 0;int cnt3 = 0; int index = *count;
	FILE* fp = fopen("PHONE_BOOK.txt", "r"); //읽기 모드로 파일 연결
	if (fp == NULL) //체크
	{
		printf("Couldn't open file\n");
		return;
	}
	if (*count >= MAX_NUM) //추가하려는데 최대 개수보다 정보가 이미 많이 들어있을 경우
	{
		printf("OVERFLOW\n");
		return;
	}
	char st[1000];
	char tmp[3][1000];
	while (!feof(fp)) //파일이 끝날때 까지
	{
		if (*count >= MAX_NUM) //만약에 추가하면서 정보가 최대 개수를 넘어갈 경우 종료
		{
			printf("OVERFLOW\n");
			break;
		}

		fgets(st, sizeof(st), fp); //한 줄을 읽어옴
		for (char* q = st; q < st + 1000; q++)
		{
			for (char* r = q; r < st + 1000; r++) //단어 분리
			{
				if (*r == '\0')
				{
					strcpy(tmp[cnt], q);
					if (!feof(fp)) { //파일의 마지막 문장이 아닐 경우 개행문자가 있기 때문에 
						tmp[cnt][len - 1] = '\0'; //len-1에 널문자를 삽입
					}
					else
					{
						tmp[cnt][len] = '\0'; //파일의 마지막 문장의 경우 개행문자가 없기 때문에 len에 널문자 삽입
					}
					cnt++;
					q = r;
					break;
				}
				if (*r == ' ') //나머지 문자열 단어 분리와 동일
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
		p[*count] = (tel*)malloc(sizeof(tel) * 1); //먼저 구조체 배열에 동적할당 해줌
		int len1 = strlen(tmp[0]);
		p[*count][0].name = (char*)malloc(sizeof(char) * (len1 + 1)); //분리된 단어 첫번째는 name
		if (p[*count][0].name == NULL) //할당 체크
		{
				printf("Not Enough Memory");
				return;
		}
		strcpy(p[*count][0].name, tmp[0]); //단어 복사, 구조체 배열에 저장

		len1 = strlen(tmp[1]); //분리된 단어 두번째는 전화번호
		p[*count][0].tel_no = (char*)malloc(sizeof(char) * (len1 + 1));
		if (p[*count][0].tel_no == NULL) //할당 체크
		{
			printf("Not Enough Memory");
			return;
		}
		strcpy(p[*count][0].tel_no , tmp[1]); //단어 복사, 구조체 배열에 저장

		len1 = strlen(tmp[2]); //세번째 단어는 birth
		p[*count][0].birth = (char*)malloc(sizeof(char) * (len1 + 1)); //단어 길이 만큼 할당
		if (p[*count][0].birth == NULL)
		{
			printf("Not Enough Memory");
			return;
		}
		strcpy(p[*count][0].birth, tmp[2]); //단어 복사, 저장

		cnt3++; //메모장을 통해 얻은 정보 개수++
		(*count)++; //정보 늘었으니 count++
		cnt = 0; //cnt 초기화
	}
	for (int i = *count-1; i > 0; i--) //뒤에서 부터 만약 이름이 사전적으로 앞에 있는 정보보다 빠를경우 교환,정렬
	{
		if (strcmp(p[i][0].name, p[i - 1][0].name) < 0) //사전적으로 빠를경우
		{
			tel* tmp1 = p[i];
			p[i] = p[i - 1];
			p[i - 1] = tmp1; //교환
		}
	}

	fclose(fp); //파일 닫기
}
void SortFile(int count)//모든 작업이 끝난 후 파일에 정렬해서 저장하기 위한 함수
{
	int cnt = 0, len = 0, cnt3 = 0;
	FILE* fp = fopen("PHONE_BOOK.txt", "r"); //먼저 읽기 모드로 파일을 불러옴
	if (fp == NULL) //체크
	{
		printf("Couldn't open file\n");
		return;
	}
	char st[1000]; //메모장의 문자열을 모두 저장할 st
	char tmp[100][3][1000]; //메모장의 문자열을 분리해서 저장할 tmp
	while (!feof(fp)) //파일이 끝날때 까지
	{
		fgets(st, sizeof(st), fp); //한 줄을 읽어옴
		for (char* q = st; q < st + 1000; q++)
		{
			for (char* r = q; r < st + 1000; r++) //단어 분리
			{
				if (*r == '\0')
				{
					strcpy(tmp[cnt3][cnt], q);
					if (!feof(fp)) { //파일의 마지막 문장이 아닐 경우 개행문자가 있기 때문에 
						tmp[cnt3][cnt][len - 1] = '\0'; //len-1에 널문자를 삽입
					}
					else
					{
						tmp[cnt3][cnt][len] = '\0'; //파일의 마지막 문장의 경우 개행문자가 없기 때문에 len에 널문자 삽입
					}
					cnt++;
					q = r;
					break;
				}
				if (*r == ' ') //나머지 문자열 단어 분리와 동일
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
		cnt3++; //메모장 정보 개수
		cnt = 0; //cnt 초기화
	}

	fclose(fp); //읽기모드 종료

	fp = fopen("PHONE_BOOK.txt", "w"); //파일 쓰기 모드 실행
	if (fp == NULL) //체크
	{
		printf("Couldn't open file\n");
		return;
	}

	for (int i = 0; i < cnt3; i++) //cnt3 = 메모장 정보 개수 만큼 반복
	{
		for (int k = i+1; k < cnt3; k++) //선택 정렬
		{
			if (strcmp(tmp[i][0], tmp[k][0]) > 0) //이름 순으로 정렬
			{
				char tmp1[100]; char tmp2[100]; char tmp3[100]; //교환에 필요한 tmp들 먼저 선언

				strcpy(tmp1, tmp[i][0]);
				strcpy(tmp2, tmp[i][1]);
				strcpy(tmp3, tmp[i][2]); 

				strcpy(tmp[i][0], tmp[k][0]);
				strcpy(tmp[i][1], tmp[k][1]);
				strcpy(tmp[i][2], tmp[k][2]);

				strcpy(tmp[k][0], tmp1);
				strcpy(tmp[k][1], tmp2);
				strcpy(tmp[k][2], tmp3); //바꾸자 하는 두 줄의 모든 단어를 바꿈
			}
		}
	}
	
	for (int i = 0; i < cnt3; i++) //파일에 쓰기위해 반복문 실행
	{
		for (int k = 0; k < 3; k++) { //정보가 3개
			fputs(tmp[i][k], fp); //fputs를 이용해 메모장에 씀
			if (k != 2) {
				fputc(' ', fp); //공백 문자를 3개의 단어 사이에 2번 넣어줌
			}
		}
		if (i != cnt3 - 1) //한 정보가 모두 끝났을 때는 개행문자 삽입, 모든 정보가 끝난 마지막에는 개행문자 삽입하지 않음
		{
			fputc('\n', fp); //개행문자 삽입
		}
	}
	fclose(fp); //파일 쓰기 모드 종료
}
