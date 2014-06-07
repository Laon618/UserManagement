#include <stdio.h>
#include "UserManagement.h"
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#pragma warning(disable:4996)
#define USER_COUNT 50



int main(void)
{
	UserInfo userInfo[USER_COUNT];
	FILE *readFile;
	FILE *writeFile;
	int user_count;
	char userChoice = '0';
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

	int maxID;
	maxID = findMaxId(userInfo, user_count);
	
	userManagement(userChoice, userInfo, user_count, result, readFile, writeFile, maxID);

	return 0;
}

int findMaxId(UserInfo userInfo [], int user_count)
{
	int i;
	int maxID = 0;
	for (i = 0; i < user_count; i++)
	{
		if (userInfo[i].userId >= maxID)
			maxID = userInfo[i].userId;
	}
	return maxID;
}
void userManagement(char userChoice, UserInfo userInfo[], int user_count, int result, FILE *readFile, FILE *writeFile, int maxID)
{
	while (1)
	{
		if (userChoice == '0')
		{
			system("cls");
			gotoxy(30, 2);
			printf("ȸ���������� �ý���\n");
			gotoxy(31, 7);
			printf("1. ȸ�� ��� ����\n");
			gotoxy(31, 9);
			printf("2. ȸ�� �߰��ϱ�\n");
			gotoxy(31, 11);
			printf("3. ȸ�� �˻��ϱ�\n");
			gotoxy(31, 13);
			printf("4. ȸ�� �����ϱ�\n");
			gotoxy(31, 15);
			printf("5. ȸ�� �����ϱ�\n");
			gotoxy(31, 17);
			printf("6. �����ϱ�\n");
			gotoxy(31, 19);
			printf("7. �����ϱ�\n");
			userChoice = UserChoice();
		}

		if (userChoice == '1')
		{
			system("cls");
			gotoxy(30, 2);
			printf("1. ȸ�� ��� ����\n");
			showData(userInfo, user_count);
			userChoice = '0';
		}
		else if (userChoice == '2')
		{
			system("cls");
			gotoxy(30, 2);
			printf("2. ȸ�� �߰��ϱ�\n\n");
			maxID = insertMember(userInfo, user_count, maxID);
			user_count++;
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '3')
		{
			system("cls");
			gotoxy(30, 2);
			printf("3. ȸ�� �˻��ϱ�\n\n");
			char more= '1';
			while (more == '1')
			{
				clearExceptHeadline();
				result = searchData(userInfo, user_count);
				if (result == -1)
				{
					gotoxy(26, 17);
					printf("�ٽ� �˻��Ͻðڽ��ϱ�?\n");
					gotoxy(28, 18);
					printf("1. ��   2. �ƴϿ�\n");
					more = UserChoice();
					if (more != '1'&& more != '2')
					{
						IncorrectInput();
						more = UserChoice();
					}
					else if (more == '2') break;
				}
				else break;
			}
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '4')
		{
			system("cls");
			gotoxy(30, 2);
			printf("4. ȸ�� �����ϱ�\n\n");
			result = searchData(userInfo, user_count);
			if (result != -1) updateData(userInfo, result, user_count);
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '5')
		{
			system("cls");
			gotoxy(30, 2);
			printf("5. ȸ�� �����ϱ�\n\n");
			result = searchData(userInfo, user_count);
			if (result != -1) deleteData(userInfo, result);
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '6')
		{
			system("cls");
			gotoxy(30, 2);
			printf("6. �����ϱ�\n");
			printfData(userInfo, writeFile, user_count);
			gotoxy(27, 12);
			printf("������ �Ϸ�Ǿ����ϴ�!\n");
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '7')
		{
			system("cls");
			gotoxy(30, 2);
			printf("7. �����ϱ�\n\n");
			endProgram(userChoice, userInfo, user_count, readFile, writeFile);
			break;
		}
		else
		{
			IncorrectInput();
			userChoice = UserChoice();
		}
		if (user_count % 50 == 49)
		{
			
		}
	}
}

char backToMenu(char userChoice)
{
	gotoxy(25, 24);
	printf("\t\t\t\t");
	gotoxy(23, 23);
	printf("�޴��� ���ư����� 0�� �����ּ��� ");
	while (1)
	{
		userChoice = getch();
		if (userChoice == '0')
			return userChoice;
		else
		{
			IncorrectInput();
			gotoxy(56, 23);
		}
	}
}

void deleteData(UserInfo userInfo [], int i)
{
	char choice;
	gotoxy(23, 9);
	printf("�� ȸ���� ���� �����Ͻðڽ��ϱ�?");
	gotoxy(30, 11);
	printf("1. ��   2. �ƴϿ�");
	choice = UserChoice();
	while (1)
	{
		gotoxy(27, 19);
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
			IncorrectInput();
			choice = UserChoice();
		}
	}
}

void updateData(UserInfo userInfo [], int i, int count)
{
	char methodChoice;
	char searchInfo[256] = { 0 };

	gotoxy(31, 13);
	printf("1. �̸� ����");
	gotoxy(31, 15);
	printf("2. �ּ� ����");
	gotoxy(31, 17);
	printf("3. ����ó ����");
	methodChoice = UserChoice();
	while (1)
	{
		if (methodChoice != '1' && methodChoice != '2' &&methodChoice != '3')
		{
			IncorrectInput();
			methodChoice = UserChoice();
		}
		else break;
	}
	clearExceptHeadline();
	gotoxy(1, 6);
	printf("	Id\t �̸�\t\t �ּ�\t\t ����ó\n");
	printf("	%d\t%s\t%2s\t%s\n", userInfo[i].userId, userInfo[i].userName, userInfo[i].userAddress, userInfo[i].userCellphone);
	if (methodChoice == '1')
	{
		while (1)
		{
			gotoxy(30, 11);
			printf("\t\t\t\t\t\t\t");
			gotoxy(30, 11);
			printf("�� �� : ");
			scanf("%s", userInfo[i].userName);
			fflush(stdin);
			if (strlen(userInfo[i].userName) >= 30)
				IncorrectInput();
			else break;
		}
	}
	else if (methodChoice == '2')
	{
		while (1)
		{
			gotoxy(30, 11);
			printf("\t\t\t\t\t\t\t");
			gotoxy(30, 11);
			printf("�� �� : ");
			scanf("%[^\n]", userInfo[i].userAddress);
			fflush(stdin);
			if (strlen(userInfo[i].userAddress) >= 128)
				IncorrectInput();
			else break;
		}
	}
	else if (methodChoice == '3')
	{
		int result = 0;
		char tempCellphone[30];
		while (1)
		{
			gotoxy(10, 9);
			printf("\t\t\t\t\t\t\t");
			gotoxy(10, 9);
			printf("����ó ('-'�� ������ ���ڸ� �־��ּ���.) : ");
			scanf("%s", tempCellphone);
			fflush(stdin);
			result = cellphoneFormCheck(userInfo, count, i, tempCellphone);
			if (result == -1)
			{
				IncorrectInput();
				continue;
			}
			else if (result == 0)
				duplicationCheck(userInfo, count, i);
			if (result == -1)
			{
				IncorrectInput();
				continue;
			}
			else if (result == 0) break;
		}
	}
	gotoxy(27, 19);
	printf("������ �Ϸ�Ǿ����ϴ�!\n");
}

int insertMember(UserInfo userInfo [], int count, int maxID)
{

	userInfo[count].userId = maxID+1;
	maxID += 1;

	while (1)
	{
		gotoxy(10, 5);
		printf("\t\t\t\t\t\t\t");
		gotoxy(10, 5);
		printf("�� �� : ");
		scanf("%s", userInfo[count].userName);
		fflush(stdin);
		if (strlen(userInfo[count].userName) >= 30)
			IncorrectInput();
		else break;
	}
	while (1)
	{
		gotoxy(10, 7);
		printf("\t\t\t\t\t\t\t");
		gotoxy(10, 7);
		printf("�� �� : ");
		scanf(" %[^\n]", userInfo[count].userAddress);
		fflush(stdin);
		if (strlen(userInfo[count].userAddress) >= 128)
			IncorrectInput();
		else break;
	}
	int result = 0;
	char tempCellphone[30];
	while (1)
	{
		gotoxy(10, 9);
		printf("\t\t\t\t\t\t\t");
		gotoxy(10, 9);
		printf("����ó ('-'�� ������ ���ڸ� �־��ּ���.): ");
		scanf("%s", tempCellphone);
		fflush(stdin);
		result = cellphoneFormCheck(userInfo, count, count, tempCellphone);
		if (result == -1)
		{
			IncorrectInput();
			continue;
		}
		else if (result == 0)
			result = duplicationCheck(userInfo, count, count);
		if (result == -1)
		{
			IncorrectInput();
			continue;
		}
		else if (result == 0) break;

	}
	gotoxy(27, 19);
	printf("ȸ�� �߰��� �Ϸ�Ǿ����ϴ�!\n");

	return maxID;
}

int cellphoneFormCheck(UserInfo userInfo[], int count, int input, char tempCellphone[])
{
	int i;
	int j = 0;

	if (strlen(tempCellphone) != 11) return -1;
	for (i = 0; i < 11; i++)
	{
		if (tempCellphone[i]<48 || tempCellphone[i]>57) return -1;
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

	return 0;
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

void IncorrectInput(void)
{
	gotoxy(25, 24);
	printf("\t\t\t\t");
	Sleep(100);
	gotoxy(25, 24);
	printf("�ùٸ� �Է��� �ƴմϴ�!");
}

void showData(UserInfo userInfo [], int count)
{
	int i=0;
	int line = 0;
	char choice;
	int pages = (count / 16)+1;
	int pageCount = 1;
	while(1)
	{
		clearExceptHeadline();
		gotoxy(1, 4);
		printf("    Id\t\t�̸�\t\t�ּ�\t\t    ����ó\n");
		line = 0;
		for (; i < 16*pageCount; i++)
		{
			if (userInfo[i].userId < 0) continue;
			gotoxy(5, 5 + line);
			printf("%d", userInfo[i].userId);
			gotoxy(15, 5 + line);
			printf("%s", userInfo[i].userName);
			gotoxy(25, 5 + line);
			printf("%s", userInfo[i].userAddress);
			gotoxy(52, 5 + line);
			printf("%s", userInfo[i].userCellphone);
			line++;
		}
		gotoxy(1, 22);
		printf("1. ���� ������");
		gotoxy(35, 22);
		printf("%d / %d", pageCount, pages);
		gotoxy(60, 22);
		printf("2. ���� ������");
		gotoxy(23, 23);
		printf("�޴��� ���ư����� 0�� �����ּ��� ");
		while (1)
		{
			gotoxy(56, 23);
			choice = getch();
			if (choice == '1')
			{
				if (pageCount > 1)
				{
					pageCount--;
					i -= 32;
					break;
				}
				else IncorrectInput();
			}
			else if (choice == '2')
			{
				if (pageCount < pages)
				{
					pageCount++;
					break;
				}
				else IncorrectInput();
			}
			else if (choice == '0')
				return;
			else
				IncorrectInput();
		}
	}
}


int initData(UserInfo userInfo[], FILE* fp)
{
	int count = 0;
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
	fprintf(writeFile," ȸ�� ���̵�\t ȸ�� �̸�\t ȸ�� �ּ�\t ����ó\n");
	for (i = 0; i < count; i++)
	{
		if (userInfo[i].userId < 0)continue;
		fprintf(writeFile, "%d\t%s\t%s\t%s\n", userInfo[i].userId, userInfo[i].userName, userInfo[i].userAddress, userInfo[i].userCellphone);
	}
}

int searchData(UserInfo userInfo [], int count)
{
	char methodChoice;
	int searchId;
	int i, result;
	char searchInfo[256] = { 0 };
	gotoxy(31, 9);
	printf("1. Id�� ã��");
	gotoxy(31, 11);
	printf("2. �̸����� ã��");
	gotoxy(31, 13);
	printf("3. ����ó�� ã��");
	methodChoice = UserChoice();
	while (1)
	{
		if (methodChoice != '1' && methodChoice != '2' &&methodChoice != '3')
		{
			IncorrectInput();
			methodChoice = UserChoice();
		}
		else break;
	}
	clearExceptHeadline();
	if (methodChoice == '1')
	{
		while (1)
		{
			gotoxy(30, 11);
			printf("\t\t\t\t\t\t\t");
			gotoxy(30, 11);
			printf("I D : ");
			scanf("%d", &searchId);
			fflush(stdin);
			if (searchId < 0)
				IncorrectInput();
			else break;
		}
		for (i = 0; i < count; i++)
			if (userInfo[i].userId == searchId) break;
		if (i == count) i = -1;
	}
	else if (methodChoice == '2')
	{
		gotoxy(30, 11);
		printf("\t\t\t\t\t\t\t");
		gotoxy(30, 11);
		printf("�� �� : ");
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
		gotoxy(30, 11);
		printf("\t\t\t\t\t\t\t");
		gotoxy(30, 11);
		printf("����ó : ");
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
		gotoxy(22, 15);
		printf("ã���ô� ȸ���� �������� �ʽ��ϴ�.\n");
		return -1;
	}
	else
	{
		clearExceptHeadline();
		gotoxy(1, 6);
		printf("	Id\t �̸�\t\t �ּ�\t\t ����ó\n");
		printf("	%d\t%s\t%2s\t%s\n", userInfo[i].userId, userInfo[i].userName, userInfo[i].userAddress, userInfo[i].userCellphone);
		return i;
	}
}


void endProgram(char userChoice, UserInfo userInfo[], int user_count, FILE *readFile, FILE *writeFile)
{
	char methodChoice;
	gotoxy(23, 9);
	printf("�����ϱ����� �����Ͻðڽ��ϱ�?");
	gotoxy(30, 11);
	printf("1. ��   2. �ƴϿ�");
	methodChoice = UserChoice();
	while (1)
	{
		if (methodChoice != '1' && methodChoice != '2')
		{
			IncorrectInput();
			methodChoice = UserChoice();
		}
		else break;
	}
	if (methodChoice == '1')
	{
		printfData(userInfo, writeFile, user_count);
		gotoxy(26, 15);
		printf("�����ϰ� �����մϴ�.");
	}
	else if (methodChoice == '2')
	{
		gotoxy(27, 15);
		printf("�������� �ʰ� �����մϴ�.");
	}
	fclose(readFile);
	gotoxy(20, 25);
}

void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

char UserChoice(void)
{
	int choice;
	gotoxy(23, 23);
	printf("���ϴ� ����� �Է����ּ��� : ");
	choice = getch();
	return choice;
}

void clearExceptHeadline(void)
{
	int i;
	gotoxy(1, 3);
	for (i = 0; i < 22; i++)
		printf("\t\t\t\t\t\t\t\t\n");
}