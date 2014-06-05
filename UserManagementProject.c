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
			printf("ȸ���������� �ý���\n");
			printf("1. ȸ�� ��� ����\n");
			printf("2. ȸ�� �߰��ϱ�\n");
			printf("3. ȸ�� �˻��ϱ�\n");
			printf("4. ȸ�� �����ϱ�\n");
			printf("5. ȸ�� �����ϱ�\n");
			printf("6. �����ϱ�\n");
			printf("7. �����ϱ�\n");
			scanf_s("%c", &userChoice, 1);
			fflush(stdin);
		}

		if (userChoice == '1')
		{
			system("cls");
			printf("1. ȸ�� ��� ����\n");
			showData(userInfo, user_count);
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '2')
		{
			system("cls");
			printf("2. ȸ�� �߰��ϱ�\n\n");
			insertMember(userInfo, user_count);
			user_count++;
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '3')
		{
			system("cls");
			printf("3. ȸ�� �˻��ϱ�\n\n");
			result = searchData(userInfo, user_count);
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '4')
		{
			system("cls");
			printf("4. ȸ�� �����ϱ�\n\n");
			result = searchData(userInfo, user_count);
			if (result != -1) updateData(userInfo, result, user_count);
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '5')
		{
			system("cls");
			printf("5. ȸ�� �����ϱ�\n\n");
			result = searchData(userInfo, user_count);
			if (result != -1) deleteData(userInfo, result);
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '6')
		{
			system("cls");
			printfData(userInfo, writeFile, user_count);
			printf("������ �Ϸ�Ǿ����ϴ�\n");
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
	scanf("%c", &choice);
	fflush(stdin);
	while (1)
	{
		if (choice == '1')
		{
			userInfo[i].userId = -1;
			printf("������ �Ϸ�Ǿ����ϴ�!\n");
			break;
		}
		else if (choice == '2')
		{
			printf("ȸ�������� ��ҵǾ����ϴ�.\n");
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

	printf("1. �̸� ����\n2. �ּ� ����\n3. ����ó ����\n");
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
		printf("�����Ͻ� ����ó�� �Է����ּ���(���ڸ� �Է����ּ���)\n");
		cellphoneFormCheck(userInfo, count, i);
	printf("������ �Ϸ�Ǿ����ϴ�!\n");
}

void insertMember(UserInfo userInfo [], int count)
{

	userInfo[count].userId = (141100 + count);
	printf("�߰��� ȸ���� �̸���?\n");
	scanf("%s", userInfo[count].userName);
	fflush(stdin);
	printf("�߰��� ȸ���� �ּҴ�?\n");
	scanf(" %[^\n]", userInfo[count].userAddress);
	fflush(stdin);
	printf("�߰��� ȸ���� ����ó��? (���ڸ� �Է����ּ���)\n");
	cellphoneFormCheck(userInfo, count, count);
	printf("ȸ�� �߰��� �Ϸ�Ǿ����ϴ�!\n");
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
					printf("������ �ùٸ��� �ʽ��ϴ�! �ٽ� �Է����ּ���!\n");
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
			printf("�ߺ��Ǵ� ����ó�Դϴ�. \n�ٽ� �Է����ּ���.\n");
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
	printf("�ùٸ� �Է��� �ƴմϴ�.\n �ٽ� �Է����ּ���\n");
	scanf("%c", &choice);
	fflush(stdin);
	return choice;
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
	printf("1. Id�� ã��\n2. �̸����� ã��\n3. ����ó�� ã��\n");
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


void endProgram(char userChoice, UserInfo userInfo[], int user_count, FILE *readFile, FILE *writeFile)
{
	char methodChoice;
	system("cls");
	printf("7. �����ϱ�\n\n");
	printf("�����ϱ����� �����Ͻðڽ��ϱ�?\n");
	printf("1. ��\n2. �ƴϿ�\n");
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
		printf("�����ϰ� �����մϴ�.\n");
	}
	else if (methodChoice == '2')
		printf("�������� �ʰ� �����մϴ�.\n");
	fclose(readFile);
}