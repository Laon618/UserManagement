#include <stdio.h>
#include "UserManagement.h"
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#pragma warning(disable:4996)
#define USER_COUNT 50

int main(void)
{
	UserInfo userInfo[USER_COUNT];
	FILE *readFile;
	FILE *writeFile;
	int user_count;
	char userChoice='0';
	int result=0;
	readFile = fopen("data.txt", "rt");
	if (readFile == NULL)
	{
		puts("data.txt file error\n");
		return -1;
	}

	writeFile = fopen("out.txt", "wt");
	if (writeFile == NULL)
	{
		puts("data.txt file error\n");
		return -1;
	}
	user_count= initData(userInfo, readFile);
	
	userManagement(userChoice, userInfo, user_count, result, readFile, writeFile);

	return 0;
}
void userManagement(char userChoice, UserInfo userInfo[], int user_count, int result, FILE *readFile, FILE *writeFile)
{
	while (1)
	{
		if (userChoice == '0')
		{
			system("cls");
			printf("회원정보관리 시스템\n");
			printf("1. 회원 목록 보기\n");
			printf("2. 회원 추가하기\n");
			printf("3. 회원 검색하기\n");
			printf("4. 회원 수정하기\n");
			printf("5. 회원 삭제하기\n");
			printf("6. 저장하기\n");
			printf("7. 종료하기\n");
			scanf_s("%c", &userChoice, 1);
			fflush(stdin);
		}

		if (userChoice == '1')
		{
			system("cls");
			printf("1. 회원 목록 보기\n");
			showData(userInfo, user_count);
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '2')
		{
			system("cls");
			printf("2. 회원 추가하기\n\n");
			insertMember(userInfo, user_count);
			user_count++;
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '3')
		{
			system("cls");
			printf("3. 회원 검색하기\n\n");
			result = searchData(userInfo, user_count);
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '4')
		{
			system("cls");
			printf("4. 회원 수정하기\n\n");
			result = searchData(userInfo, user_count);
			if (result != -1) updateData(userInfo, result, user_count);
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '5')
		{
			system("cls");
			printf("5. 회원 삭제하기\n\n");
			result = searchData(userInfo, user_count);
			if (result != -1) deleteData(userInfo, result);
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '6')
		{
			system("cls");
			printfData(userInfo, writeFile, user_count);
			printf("저장이 완료되엇습니다\n");
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '7')
		{
			endProgram(userChoice, userInfo, user_count, readFile, writeFile);
			break;
		}
		else
		{
			userChoice = incorrectInput();
		}
		if (user_count % 50 == 49)
		{
			
		}
	}
}

char backToMenu(char userChoice)
{
	while (1)
	{
		printf("\n메뉴로 돌아가려면 0을 눌러주세요\n");
		scanf("%c", &userChoice);
		fflush(stdin);
		if (userChoice == '0')
			return userChoice;
	}
}

void deleteData(UserInfo userInfo [], int i)
{
	char choice;
	printf("이 회원을 정말 삭제하시겠습니까?\n");
	printf("1. 예 \n2. 아니요\n");
	scanf("%c", &choice);
	fflush(stdin);
	while (1)
	{
		if (choice == '1')
		{
			userInfo[i].userId = -1;
			printf("삭제가 완료되었습니다!\n");
			break;
		}
		else if (choice == '2')
		{
			printf("회원삭제가 취소되었습니다.\n");
			break;
		}
		else
		{
			choice = incorrectInput();
		}
	}
}

void updateData(UserInfo userInfo [], int i, int count)
{
	char methodChoice;
	char searchInfo[256] = { 0 };

	printf("1. 이름 수정\n2. 주소 수정\n3. 연락처 수정\n");
	scanf("%c", &methodChoice);
	fflush(stdin);
	while (1)
	{
		if (methodChoice != '1' && methodChoice != '2' &&methodChoice != '3')
		{
			methodChoice = incorrectInput();
		}
		else break;
	}
	system("cls");
	printf("4. 회원 수정하기\n\n");
	if (methodChoice == '1')
	{
		printf("수정하실 이름를 입력해주세요\n");
		scanf("%s", userInfo[i].userName);
		fflush(stdin);
	}
	else if (methodChoice == '2')
	{
		printf("수정하실 주소를 입력해주세요\n");
		scanf(" %[^\n]", userInfo[i].userAddress);
		fflush(stdin);
	}
	else if (methodChoice == '3')
		printf("수정하실 연락처를 입력해주세요(숫자만 입력해주세요)\n");
		cellphoneFormCheck(userInfo, count, i);
	printf("수정이 완료되었습니다!\n");
}

void insertMember(UserInfo userInfo [], int count)
{

	userInfo[count].userId = (141100 + count);
	printf("추가할 회원의 이름은?\n");
	scanf("%s", userInfo[count].userName);
	fflush(stdin);
	printf("추가할 회원의 주소는?\n");
	scanf(" %[^\n]", userInfo[count].userAddress);
	fflush(stdin);
	printf("추가할 회원의 연락처는? (숫자만 입력해주세요)\n");
	cellphoneFormCheck(userInfo, count, count);
	printf("회원 추가가 완료되었습니다!\n");
}

void cellphoneFormCheck(UserInfo userInfo[], int count,int input)
{
	int i;
	int result= -1;
	char tempCellphone[30];
	while (result == -1)
	{
		int j = 0;
		while (1)
		{
			scanf("%s", tempCellphone);
			fflush(stdin);
			for (i = 0; i < 11; i++)
			{
				if (tempCellphone[i]<48 || tempCellphone[i]>57 || strlen(tempCellphone)>11)
				{
					printf("형식이 올바르지 않습니다! 다시 입력해주세요!\n");
					break;
				}
			}
			if (i == 11) break;
		}	
		for (i = 0; i < 11; i++)
		{
			userInfo[input].userCellphone[j] = tempCellphone[i];
			j++;
			if (i == 2 || i == 6)
			{
				userInfo[input].userCellphone[j] = '-';
				j++;
			}
		}
		userInfo[input].userCellphone[j] = '\0';
		result = duplicationCheck(userInfo, count, input);
		if (result == -1)
			printf("중복되는 연락처입니다. \n다시 입력해주세요.\n");
		else break;
	}
}

void cellphoneInput(UserInfo userInfo [], int input, char tempCellphone[])
{
	int i;
	int j = 0;
	for (i = 0; i < 11; i++)
	{
		userInfo[input].userCellphone[j] = tempCellphone[i];
		j++;
		if (i == 2 || i == 6)
		{
			userInfo[input].userCellphone[j] = '-';
			j++;
		}
	}
	userInfo[input].userCellphone[j] = '\0';
}

int duplicationCheck(UserInfo userInfo[], int count, int input)
{
	int result, i;
	for (i = 0; i < count; i++)
	{
		result = strcmp(userInfo[input].userCellphone, userInfo[i].userCellphone);
		if (result == 0)
		{
			if (userInfo[i].userId < 0 || i==input) continue;
			return -1;
		}
	}
	return 0;
}

char incorrectInput(void)
{
	char choice;
	printf("올바른 입력이 아닙니다.\n 다시 입력해주세요\n");
	scanf("%c", &choice);
	fflush(stdin);
	return choice;
}

void showData(UserInfo userInfo [], int count)
{
	int i;
	printf("	Id\t 이름\t\t 주소\t\t 연락처\n");
	for (i = 0; i < count; i++)
	{
		if (userInfo[i].userId < 0) continue;
		printf("	%d\t%s\t%2s\t%s\n", userInfo[i].userId, userInfo[i].userName, userInfo[i].userAddress, userInfo[i].userCellphone);
	}
}


int initData(UserInfo userInfo[], FILE* fp)
{
	int count = 1;
	char buffer[256] = { 0 };
	int i = 0;
	while ((fgets(buffer, sizeof(buffer), fp)) != NULL)
	{
		fscanf(fp, "%d\t%s\t%[^\t]\t%s", &userInfo[i].userId, &userInfo[i].userName, &userInfo[i].userAddress, &userInfo[i].userCellphone);
		i++;
		count++;
	}
	return count;
}

void printfData(UserInfo userInfo [], FILE *writeFile, int count)
{
	int i;

	fprintf(writeFile, "%s""회원아이디\t 회원이름\t 회원주소\t 연락처\n");
	for (i = 1; i < count; i++)
	{
		if (userInfo[i].userId < 0)continue;
		fprintf(writeFile, "%d\t%s\t%s\t%s\n", userInfo[i].userId, userInfo[i].userName, userInfo[i].userAddress, userInfo[i].userCellphone);
	}
}

int searchData(UserInfo userInfo[], int count)
{
	char methodChoice;
	int searchId;
	int i, result;
	char searchInfo[256] = { 0 };
	printf("1. Id로 찾기\n2. 이름으로 찾기\n3. 연락처로 찾기\n");
	scanf("%c", &methodChoice);
	fflush(stdin);
	while (1)
	{
		if (methodChoice != '1' && methodChoice != '2' &&methodChoice != '3')
			methodChoice = incorrectInput();
		else break;
	}
	system("cls");
	if (methodChoice == '1')
	{
		printf("찾으실 ID를 입력해주세요\n");
		scanf("%d", &searchId);
		fflush(stdin);
		while (1)
		{
			if (searchId < 0)
			{
				printf("ID가 올바르지 않습니다.\n다시 입력해주세요.\n");
				scanf("%d", &searchId);
				fflush(stdin);
			}
			else break;
		}
		for (i = 0; i < count; i++)
		{
			if (userInfo[i].userId == searchId) break;
		}
		if (i == count) i = -1;
	}
	else if (methodChoice == '2')
	{
		printf("찾으실 이름를 입력해주세요\n");
		scanf("%s", searchInfo);
		fflush(stdin);
		for (i = 0; i < count; i++)
		{
			if (userInfo[i].userId < 0) continue;
			result = strcmp(searchInfo, userInfo[i].userName);
			if (result == 0) break;
		}
		if (i == count) i = -1;
	}
	else if (methodChoice == '3')
	{
		printf("찾으실 연락처를 입력해주세요\n");
		scanf("%s", searchInfo);
		fflush(stdin);
		for (i = 0; i < count; i++)
		{
			result = strcmp(searchInfo, userInfo[i].userCellphone);
			if (result == 0)
			{
				if (userInfo[i].userId < 0) continue;
				break;
			}
		}
		if (i == count) i = -1;
	}
	if (i == -1)
	{
		printf("찾으시는 회원이 존재하지 않습니다.\n");
		return -1;
	}
	else
	{
		printf("	Id\t 이름\t\t 주소\t\t 연락처\n");
		printf("	%d\t%s\t%2s\t%s\n", userInfo[i].userId, userInfo[i].userName, userInfo[i].userAddress, userInfo[i].userCellphone);
		return i;
	}
}


void endProgram(char userChoice, UserInfo userInfo[], int user_count, FILE *readFile, FILE *writeFile)
{
	char methodChoice;
	system("cls");
	printf("7. 종료하기\n\n");
	printf("종료하기전에 저장하시겠습니까?\n");
	printf("1. 예\n2. 아니요\n");
	scanf("%c", &methodChoice);
	fflush(stdin);
	while (1)
	{
		if (methodChoice != '1' && methodChoice != '2')
			methodChoice = incorrectInput();
		else break;
	}
	if (methodChoice == '1')
	{
		printfData(userInfo, writeFile, user_count);
		printf("저장하고 종료합니다.\n");
	}
	else if (methodChoice == '2')
		printf("저장하지 않고 종료합니다.\n");
	fclose(readFile);
}