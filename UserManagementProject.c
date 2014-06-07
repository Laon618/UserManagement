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
			printf("회원정보관리 시스템\n");
			gotoxy(31, 7);
			printf("1. 회원 목록 보기\n");
			gotoxy(31, 9);
			printf("2. 회원 추가하기\n");
			gotoxy(31, 11);
			printf("3. 회원 검색하기\n");
			gotoxy(31, 13);
			printf("4. 회원 수정하기\n");
			gotoxy(31, 15);
			printf("5. 회원 삭제하기\n");
			gotoxy(31, 17);
			printf("6. 저장하기\n");
			gotoxy(31, 19);
			printf("7. 종료하기\n");
			userChoice = UserChoice();
		}

		if (userChoice == '1')
		{
			system("cls");
			gotoxy(30, 2);
			printf("1. 회원 목록 보기\n");
			showData(userInfo, user_count);
			userChoice = '0';
		}
		else if (userChoice == '2')
		{
			system("cls");
			gotoxy(30, 2);
			printf("2. 회원 추가하기\n\n");
			maxID = insertMember(userInfo, user_count, maxID);
			user_count++;
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '3')
		{
			system("cls");
			gotoxy(30, 2);
			printf("3. 회원 검색하기\n\n");
			char more= '1';
			while (more == '1')
			{
				clearExceptHeadline();
				result = searchData(userInfo, user_count);
				if (result == -1)
				{
					gotoxy(26, 17);
					printf("다시 검색하시겠습니까?\n");
					gotoxy(28, 18);
					printf("1. 예   2. 아니요\n");
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
			printf("4. 회원 수정하기\n\n");
			result = searchData(userInfo, user_count);
			if (result != -1) updateData(userInfo, result, user_count);
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '5')
		{
			system("cls");
			gotoxy(30, 2);
			printf("5. 회원 삭제하기\n\n");
			result = searchData(userInfo, user_count);
			if (result != -1) deleteData(userInfo, result);
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '6')
		{
			system("cls");
			gotoxy(30, 2);
			printf("6. 저장하기\n");
			printfData(userInfo, writeFile, user_count);
			gotoxy(27, 12);
			printf("저장이 완료되었습니다!\n");
			userChoice = backToMenu(userChoice);
		}
		else if (userChoice == '7')
		{
			system("cls");
			gotoxy(30, 2);
			printf("7. 종료하기\n\n");
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
	printf("메뉴로 돌아가려면 0을 눌러주세요 ");
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
	printf("이 회원을 정말 삭제하시겠습니까?");
	gotoxy(30, 11);
	printf("1. 예   2. 아니요");
	choice = UserChoice();
	while (1)
	{
		gotoxy(27, 19);
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
	printf("1. 이름 수정");
	gotoxy(31, 15);
	printf("2. 주소 수정");
	gotoxy(31, 17);
	printf("3. 연락처 수정");
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
	printf("	Id\t 이름\t\t 주소\t\t 연락처\n");
	printf("	%d\t%s\t%2s\t%s\n", userInfo[i].userId, userInfo[i].userName, userInfo[i].userAddress, userInfo[i].userCellphone);
	if (methodChoice == '1')
	{
		while (1)
		{
			gotoxy(30, 11);
			printf("\t\t\t\t\t\t\t");
			gotoxy(30, 11);
			printf("이 름 : ");
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
			printf("주 소 : ");
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
			printf("연락처 ('-'를 제외한 숫자만 넣어주세요.) : ");
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
	printf("수정이 완료되었습니다!\n");
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
		printf("이 름 : ");
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
		printf("주 소 : ");
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
		printf("연락처 ('-'를 제외한 숫자만 넣어주세요.): ");
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
	printf("회원 추가가 완료되었습니다!\n");

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
	printf("올바른 입력이 아닙니다!");
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
		printf("    Id\t\t이름\t\t주소\t\t    연락처\n");
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
		printf("1. 이전 페이지");
		gotoxy(35, 22);
		printf("%d / %d", pageCount, pages);
		gotoxy(60, 22);
		printf("2. 다음 페이지");
		gotoxy(23, 23);
		printf("메뉴로 돌아가려면 0을 눌러주세요 ");
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
	fprintf(writeFile," 회원 아이디\t 회원 이름\t 회원 주소\t 연락처\n");
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
	printf("1. Id로 찾기");
	gotoxy(31, 11);
	printf("2. 이름으로 찾기");
	gotoxy(31, 13);
	printf("3. 연락처로 찾기");
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
		printf("이 름 : ");
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
		printf("연락처 : ");
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
		printf("찾으시는 회원이 존재하지 않습니다.\n");
		return -1;
	}
	else
	{
		clearExceptHeadline();
		gotoxy(1, 6);
		printf("	Id\t 이름\t\t 주소\t\t 연락처\n");
		printf("	%d\t%s\t%2s\t%s\n", userInfo[i].userId, userInfo[i].userName, userInfo[i].userAddress, userInfo[i].userCellphone);
		return i;
	}
}


void endProgram(char userChoice, UserInfo userInfo[], int user_count, FILE *readFile, FILE *writeFile)
{
	char methodChoice;
	gotoxy(23, 9);
	printf("종료하기전에 저장하시겠습니까?");
	gotoxy(30, 11);
	printf("1. 예   2. 아니요");
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
		printf("저장하고 종료합니다.");
	}
	else if (methodChoice == '2')
	{
		gotoxy(27, 15);
		printf("저장하지 않고 종료합니다.");
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
	printf("원하는 기능을 입력해주세요 : ");
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