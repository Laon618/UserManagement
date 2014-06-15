#include <stdio.h>
#include "UserManagement.h"
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#pragma warning(disable:4996)


int USER_SIZE = 50;
int user_count = 0;

int main(void)
{
	UserInfo *userInfo;
	FILE *readFile;
	FILE *writeFile;

	int userChoice = 13;
	int result=0;
	userInfo = (UserInfo*) malloc(sizeof(UserInfo) *USER_SIZE);

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



void userManagement(int userChoice, UserInfo userInfo[], int user_count, int result, FILE *readFile, FILE *writeFile, int maxID)
{
	int searchResult[50] = { 0 };
	while (1)
	{
		if (userChoice == 13)
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

		if (userChoice == 49)
		{
			system("cls");
			gotoxy(30, 2);
			printf("1. ȸ�� ��� ����\n");
			showData(userInfo, user_count);
			userChoice = 13;
		}
		else if (userChoice == 50)
		{
			system("cls");
			gotoxy(30, 2);
			printf("2. ȸ�� �߰��ϱ�\n\n");
			maxID = insertMember(userInfo, user_count, maxID);
			user_count++;
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == 51)
		{
			system("cls");
			gotoxy(30, 2);
			printf("3. ȸ�� �˻��ϱ�\n\n");
			char more= '1';
			clearScreenPartially(1, 3);
			searchData(userInfo, user_count, searchResult);

			if (searchResult[0] != 0)
			{
				int line = 0;
				int j;
				int i;
				gotoxy(1, 6);
				printf("	Id\t �̸�\t\t �ּ�\t\t ����ó\n");
				for (j = 0; searchResult[j] != 0; j++)
				{
					i = searchResult[j];
					showChosenData(userInfo, i, line, 7);
					line++;
				}
				userChoice = backToMenu(userChoice);
			}
			else
				userChoice = 13;
		}
		else if (userChoice == 52)
		{
			system("cls");
			gotoxy(30, 2);
			printf("4. ȸ�� �����ϱ�\n\n");
			searchData(userInfo, user_count, searchResult);
			if (searchResult[0] != 0)
				result = selectData(searchResult, userInfo);
			else
			{
				userChoice = 13;
				continue;
			}
			clearScreenPartially(1, 13);
			updateData(userInfo, result, user_count);
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == 53)
		{
			system("cls");
			gotoxy(30, 2);
			printf("5. ȸ�� �����ϱ�\n\n");
			searchData(userInfo, user_count, searchResult);
			if (searchResult[0] != 0)
				result = selectData(searchResult, userInfo);
			else
			{
				userChoice = 13;
				continue;
			}
			deleteData(userInfo, result);
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == 54)
		{
			system("cls");
			gotoxy(30, 2);
			printf("6. �����ϱ�\n");
			printfData(userInfo, writeFile, user_count);
			gotoxy(27, 12);
			printf("������ �Ϸ�Ǿ����ϴ�!\n");
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == 55)
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
		memset(searchResult, 0, sizeof(searchResult));
		if (user_count % USER_SIZE == (USER_SIZE-1))
		{
			USER_SIZE *= 2;
			userInfo = (UserInfo *) realloc(userInfo, sizeof(UserInfo) * USER_SIZE);
		}
	}
}
char backToMenu(int userChoice)
{
	gotoxy(25, 24);
	printf("\t\t\t\t");
	gotoxy(21, 23);
	printf("�޴��� ���ư����� ���͸� �����ּ��� ");
	while (1)
	{
		userChoice = getch();
		if (userChoice == 13)
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
	clearScreenPartially(1, 3);
	gotoxy(1, 6);
	printf("	Id\t �̸�\t\t �ּ�\t\t ����ó\n");
	showChosenData(userInfo, i, 0, 7);
	if (methodChoice == '1')
	{
		clearScreenPartially(30, 11);
		while (1)
		{
			clearExceptBottomLine(30, 11);
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
		clearScreenPartially(30, 11);
		while (1)
		{
			clearExceptBottomLine(30, 11);
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
		clearScreenPartially(10, 9);
		while (1)
		{
			clearExceptBottomLine(10, 9);
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
	clearScreenPartially(10, 5);
	while (1)
	{
		clearExceptBottomLine(10, 5);
		printf("�� �� : ");
		scanf("%s", userInfo[count].userName);
		fflush(stdin);
		if (strlen(userInfo[count].userName) >= 30)
			IncorrectInput();
		else break;
	}
	clearScreenPartially(10, 7);
	while (1)
	{
		clearExceptBottomLine(10, 7);
		printf("�� �� : ");
		scanf(" %[^\n]", userInfo[count].userAddress);
		fflush(stdin);
		if (strlen(userInfo[count].userAddress) >= 128)
			IncorrectInput();
		else break;
	}
	int result = 0;
	char tempCellphone[30];
	clearScreenPartially(10, 9);
	while (1)
	{
		clearExceptBottomLine(10, 9);
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
	int choice;
	int pages = (count / 16)+1;
	int pageCount = 1;
	while(1)
	{
		clearScreenPartially(1,3);
		gotoxy(1, 4);
		printf("    Id\t\t�̸�\t\t�ּ�\t\t    ����ó\n");
		line = 0;
		for (; i < 16*pageCount; i++)
		{
			if (userInfo[i].userId < 0) continue;
			showChosenData(userInfo, i, line, 5);
			line++;
		}
		gotoxy(1, 22);
		printf("<- ���� ������");
		gotoxy(35, 22);
		printf("%d / %d", pageCount, pages);
		gotoxy(60, 22);
		printf("-> ���� ������");
		gotoxy(21, 23);
		printf("�޴��� ���ư����� ���͸� �����ּ��� ");
		while (1)
		{
			gotoxy(56, 23);
			choice = getch();
			if (choice == 0 || choice == 0xe0)
			{
				choice = getch();
				if (choice == 75)
				{
					if (pageCount > 1)
					{
						pageCount--;
						i -= 32;
						break;
					}
					else IncorrectInput();
				}
				
				if (choice == 77)
				{
					if (pageCount < pages)
					{
						pageCount++;
						break;
					}
					else IncorrectInput();
				}
			}
			if (choice == 75 || choice == 77)
				continue;
			else if (choice == 13)
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



void searchData(UserInfo userInfo [], int count, int *searchResult)
{
	int methodChoice;
	int searchId;
	int i, result;
	int resultCount = 0;
	char searchInfo[256] = { 0 };
	gotoxy(31, 9);
	printf("1. Id�� ã��");
	gotoxy(31, 11);
	printf("2. �̸����� ã��");
	gotoxy(31, 13);
	printf("3. ����ó�� ã��");
	gotoxy(31, 15);
	printf("Enter. �޴��� ���ư���");
	methodChoice = UserChoice();
	while (1)
	{
		if (methodChoice == 13) break;
		if (methodChoice < 48 || methodChoice > 51)
		{
			IncorrectInput();
			methodChoice = UserChoice();
		}
		else break;
	}
	clearScreenPartially(1,3);
	if (methodChoice == 49)
	{
		while (1)
		{
			clearExceptBottomLine(30, 11);
			printf("I D : ");
			scanf("%d", &searchId);
			fflush(stdin);
			if (searchId < 0)
				IncorrectInput();
			else break;
		}
		for (i = 0; i < count; i++)
		if (userInfo[i].userId == searchId)
		{
			searchResult[resultCount] = i;
			resultCount++;
		}
	}
	else if (methodChoice == 50)
	{
		clearExceptBottomLine(30, 11);
		printf("�� �� : ");
		scanf("%s", searchInfo);
		fflush(stdin);
		for (i = 0; i < count; i++)
		{
			if (userInfo[i].userId < 0) continue;
			result = strcmp(searchInfo, userInfo[i].userName);
			if (result == 0) 
			{
				searchResult[resultCount] = i;
				resultCount++;
			}
		}
	}
	else if (methodChoice == 51)
	{
		clearExceptBottomLine(30, 11);
		printf("����ó : ");
		scanf("%s", searchInfo);
		fflush(stdin);
		for (i = 0; i < count; i++)
		{
			if (userInfo[i].userId < 0) continue;
			result = strcmp(searchInfo, userInfo[i].userCellphone);
			if (result == 0)
				searchResult[resultCount] = i;
		}
	}
	else if (methodChoice == 13)
		return;
	if (searchResult[0] == 0)
	{
		int more;
		clearScreenPartially(22, 15);
		printf("ã���ô� ȸ���� �������� �ʽ��ϴ�.\n");
		gotoxy(26, 17);
		printf("�ٽ� �˻��Ͻðڽ��ϱ�?\n");
		gotoxy(28, 18);
		printf("1. ��   2. �ƴϿ�\n");
		more = UserChoice();
		while (1)
		{
			if (more == 50) return;
			else if (more == 49)
			{
				clearScreenPartially(1, 3);
				searchData(userInfo, count, searchResult);
			}
			else
			{
				IncorrectInput();
				more = UserChoice();
			}
		}
	}
	clearScreenPartially(1, 3);
}


void endProgram(int userChoice, UserInfo userInfo[], int user_count, FILE *readFile, FILE *writeFile)
{
	int methodChoice;
	gotoxy(23, 9);
	printf("�����ϱ����� �����Ͻðڽ��ϱ�?");
	gotoxy(30, 11);
	printf("1. ��   2. �ƴϿ�");
	methodChoice = UserChoice();
	while (1)
	{
		if (methodChoice != 49 && methodChoice != 50)
		{
			IncorrectInput();
			methodChoice = UserChoice();
		}
		else break;
	}
	if (methodChoice == 49)
	{
		printfData(userInfo, writeFile, user_count);
		gotoxy(26, 15);
		printf("�����ϰ� �����մϴ�.");
	}
	else if (methodChoice == 50)
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

int UserChoice(void)
{
	int choice;
	gotoxy(23, 23);
	printf("���ϴ� ����� �Է����ּ��� : ");
	choice = getch();
	return choice;
}

void clearScreenPartially(int x, int y)
{
	int i;
	gotoxy(x, y);
	for (i = y; i < 25; i++)
		printf("\t\t\t\t\t\t\t\t\t        ");
	gotoxy(x, y);
}

void clearExceptBottomLine(int x, int y)
{
	int i;
	gotoxy(x, y);
	for (i = y; i < 24; i++)
		printf("\t\t\t\t\t\t\t\t\t        ");
	gotoxy(x, y);
}

void showChosenData(UserInfo userInfo[], int i, int line, int y)
{
	gotoxy(5, y + line);
	printf("%d", userInfo[i].userId);
	gotoxy(15, y + line);
	printf("%s", userInfo[i].userName);
	gotoxy(25, y + line);
	printf("%s", userInfo[i].userAddress);
	gotoxy(52, y + line);
	printf("%s", userInfo[i].userCellphone);
}

int selectData(int *searchResult, UserInfo userInfo[])
{
	int j;
	int i = 0;
	int chosenData = 0;
	int choice;
	gotoxy(1, 6);
	printf("	Id\t �̸�\t\t �ּ�\t\t ����ó\n");
	if (searchResult[0] == 0)
		return 13;
	if (searchResult[1] == 0)
	{
		i = searchResult[0];
		showChosenData(userInfo, i, 0, 7);
		return searchResult[0];
	}
	else
	{
		while (1)
		{
			int line = 0;
			for (j = 0; searchResult[j] != 0; j++)
			{
				if (j == chosenData)
					color(112);
				i = searchResult[j];
				showChosenData(userInfo, i, line, 7);
				line++;
				color(7);
			}
			gotoxy(15, 23);
			printf("����ȭ��ǥ�� �̿��Ͽ� ���ϴ� ȸ���� �������ּ��� ");
			while (1)
			{
				gotoxy(1, 24);
				printf("\t\t\t\t\t\t\t\t\t");
				gotoxy(60, 23);
				choice = getch();
				if (choice == 0 || choice == 0xe0)
				{
					choice = getch();
					if (choice == 72)
					{
						if (chosenData > 0)
						{
							chosenData--;
							break;
						}
					}

					if (choice == 80)
					{
						if (searchResult[chosenData+1] != 0)
						{
							chosenData++;
							break;
						}
					}
				}
				if (choice == 72 || choice == 80)
					continue;
				else if (choice == 13)
					return searchResult[chosenData];
				else
					IncorrectInput();
			}
		}
	}
}

void color(int colorNumber)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNumber);
}