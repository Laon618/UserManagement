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
	char userChoice;
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

	printf("ȸ���������� �ý���\n");
	printf("1. ȸ�� ��� ����\n");
	printf("2. ȸ�� �߰��ϱ�\n");
	printf("3. ȸ�� �˻��ϱ�\n");
	printf("4. ȸ�� �����ϱ�\n");
	printf("5. ȸ�� �����ϱ�\n");
	printf("6. �����ϰ� ����\n");
	scanf_s("%c", &userChoice, 1);
	fflush(stdin);
	
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
			printf("ȸ���������� �ý���\n");
			printf("1. ȸ�� ��� ����\n");
			printf("2. ȸ�� �߰��ϱ�\n");
			printf("3. ȸ�� �˻��ϱ�\n");
			printf("4. ȸ�� �����ϱ�\n");
			printf("5. ȸ�� �����ϱ�\n");
			printf("6. �����ϰ� ����\n");
			scanf_s("%c", &userChoice, 1);
			fflush(stdin);
		}
		//CONSOLE_SCREEN_BUFFER_INFO origInfo;
		//GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &origInfo);

		if (userChoice == '1')
		{
			printf("1. ȸ�� ��� ����\n");
			system("cls");
			showData(userInfo, user_count);
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '2')
		{
			system("cls");
			insertMember(userInfo, user_count);
			user_count++;
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '3')
		{
			system("cls");
			result = searchData(userInfo, user_count);
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '4')
		{
			system("cls");
			result = searchData(userInfo, user_count);
			if (result != -1) updateData(userInfo, result);
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '5')
		{
			system("cls");
			result = searchData(userInfo, user_count);
			if (result != -1) deleteData(userInfo, result);
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '6')
		{
			printfData(userInfo, writeFile, user_count);
			fclose(readFile);
			break;
		}
		else
		{
			//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), origInfo.dwCursorPosition);
			printf("�ùٸ� �Է��� �ƴմϴ�.\n �ٽ� �Է����ּ���\n");
			scanf_s("%c", &userChoice, 1);
			fflush(stdin);
			//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), origInfo.dwCursorPosition);
		}
	}
}

char backToMenu(char userChoice)
{
	while (1)
	{
		printf("\n�޴��� ���ư����� 0�� �����ּ���\n");
		scanf("%c", &userChoice);
		fflush(stdin);
		if (userChoice == '0')
			return userChoice;
	}
}

void deleteData(UserInfo userInfo [], int i)
{
	char choice;
	printf("�� ȸ���� ���� �����Ͻðڽ��ϱ�?\n");
	printf("1. �� \n2. �ƴϿ�\n");
	scanf_s("%c", &choice, 1);
	if (choice == 1)
		userInfo[i].userId = -1;
	printf("������ �Ϸ�Ǿ����ϴ�!\n");
}

void updateData(UserInfo userInfo [], int i)
{
	char methodChoice;
	char searchInfo[256] = { 0 };

	printf("4. ȸ�� �����ϱ�\n\n");
	printf("1. �̸� ����\n2. �ּ� ����\n3. ����ó ����\n");
	scanf("%c", &methodChoice);
	fflush(stdin);
	while (1)
	{
		if (methodChoice != '1' && methodChoice != '2' &&methodChoice != '3')
		{
			printf("�ùٸ� �Է��� �ƴմϴ�.\n �ٽ� �Է����ּ���\n");
			scanf("%c", &methodChoice);
			fflush(stdin);
		}
		else break;
	}
	system("cls");
	printf("4. ȸ�� �����ϱ�\n\n");
	if (methodChoice == '1')
	{
		printf("�����Ͻ� �̸��� �Է����ּ���\n");
		scanf("%s", userInfo[i].userName);
		fflush(stdin);
	}
	else if (methodChoice == '2')
	{
		printf("�����Ͻ� �ּҸ� �Է����ּ���\n");
		scanf(" %[^\n]", userInfo[i].userAddress);
		fflush(stdin);
	}
	else if (methodChoice == '3')
	{
		printf("�����Ͻ� ����ó�� �Է����ּ���\n");
		scanf("%s", userInfo[i].userCellphone);
		fflush(stdin);
	}
	printf("������ �Ϸ�Ǿ����ϴ�!\n");
}


void insertMember(UserInfo userInfo [], int count)
{
	userInfo[count].userId = (141100 + count);
	printf("2. ȸ�� �߰��ϱ�\n\n");
	printf("�߰��� ȸ���� �̸���?\n");
	scanf("%s", userInfo[count].userName);
	fflush(stdin);
	printf("�߰��� ȸ���� �ּҴ�?\n");
	scanf(" %[^\n]", userInfo[count].userAddress);
	fflush(stdin);
	cellphoneFormCheck(userInfo, count);
	printf("ȸ�� �߰��� �Ϸ�Ǿ����ϴ�!\n");
}



void cellphoneFormCheck(UserInfo userInfo [], int count)
{
	int i;
	int result= -1;
	char tempCellphone[30];
	while (result == -1)
	{
		int j = 0;
		while (1)
		{
			printf("�߰��� ȸ���� ����ó��? (���ڸ� �Է����ּ���)\n");
			scanf("%s", tempCellphone);
			fflush(stdin);
			for (i = 0; i < 11; i++)
			{
				if (tempCellphone[i]<48 || tempCellphone[i]>57 || strlen(tempCellphone)>11)
				{
					printf("������ �ùٸ��� �ʽ��ϴ�! �ٽ� �Է����ּ���!\n");
					break;
				}
			}
			if (i == 11) break;
		}
		for (i = 0; i < 11; i++)
		{
			userInfo[count].userCellphone[j] = tempCellphone[i];
			j++;
			if (i == 2 || i == 6)
			{
				userInfo[count].userCellphone[j] = '-';
				j++;
			}
		}
		userInfo[count].userCellphone[j] = '\0';
		result = duplicationCheck(userInfo, count);
		if (result == -1)
			printf("�ߺ��Ǵ� ����ó�Դϴ�. \n�ٽ� �Է����ּ���.\n");
		else break;
	}
}

int duplicationCheck(UserInfo userInfo[], int count)
{
	int result, i;
	for (i = 0; i < count; i++)
	{
		result = strcmp(userInfo[count].userCellphone, userInfo[i].userCellphone);
		if (result == 0)
		{
			if (userInfo[i].userId < 0) continue;
			return -1;
		}
	}
	return 0;
}

void showData(UserInfo userInfo [], int count)
{
	int i;
	printf("	Id\t �̸�\t\t �ּ�\t\t ����ó\n");
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

	fprintf(writeFile, "%s""ȸ�����̵�\t ȸ���̸�\t ȸ���ּ�\t ����ó\n");
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

	printf("3. ȸ�� �˻��ϱ�\n\n");
	printf("1. Id�� ã��\n2. �̸����� ã��\n3. ����ó�� ã��\n");
	scanf("%c", &methodChoice);
	fflush(stdin);
	while (1)
	{
		if (methodChoice != '1' && methodChoice != '2' &&methodChoice != '3')
		{
			printf("�ùٸ� �Է��� �ƴմϴ�.\n �ٽ� �Է����ּ���\n");
			scanf("%c", &methodChoice);
			fflush(stdin);
		}
		else break;
	}
	system("cls");
	printf("3. ȸ�� �˻��ϱ�\n\n");
	if (methodChoice == '1')
	{
		printf("ã���� ID�� �Է����ּ���\n");
		scanf("%d", &searchId);
		fflush(stdin);
		while (1)
		{
			if (searchId < 0)
			{
				printf("ID�� �ùٸ��� �ʽ��ϴ�.\n�ٽ� �Է����ּ���.\n");
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
		printf("ã���� �̸��� �Է����ּ���\n");
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
		printf("ã���� ����ó�� �Է����ּ���\n");
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
		printf("ã���ô� ȸ���� �������� �ʽ��ϴ�.\n");
		return -1;
	}
	else
	{
		printf("	Id\t �̸�\t\t �ּ�\t\t ����ó\n");
		printf("	%d\t%s\t%2s\t%s\n", userInfo[i].userId, userInfo[i].userName, userInfo[i].userAddress, userInfo[i].userCellphone);
		return i;
	}
}