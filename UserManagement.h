#ifndef __USERMANAGEMENT_H__
#define __USERMANAGEMENT_H__

typedef struct userinfo{
	int userId;
	char userName[30];
	char userAddress[128];
	char userCellphone[30];
}UserInfo;

void gotoxy(int x, int y);
void deleteData(UserInfo userInfo [], int i);
int initData(UserInfo userInfo [], FILE* fp);
void setUserInfo(char buffer [], UserInfo *userInfo);
void printfData(UserInfo userInfo [], FILE *writeFile, int count);
void showData(UserInfo userInfo [], int count);
int insertMember(UserInfo userInfo [], int count, int maxID);
void searchData(UserInfo userInfo [], int count, int *searchResult);
void updateData(UserInfo userInfo[], int i, int user_count);
int cellphoneFormCheck(UserInfo userInfo [], int count, int input, char tempCellphone []);
void userManagement(int userChoice, UserInfo userInfo[], int user_count, int result, FILE *readFile, FILE *writeFile, int maxID);
char backToMenu(int userChoice);
int duplicationCheck(UserInfo userInfo [], int count, int input);
void cellphoneInput(UserInfo userInfo [], int input, char tempCellphone []);
void endProgram(int userChoice, UserInfo userInfo[], int user_count, FILE *readFile, FILE *writeFile);
int findMaxId(UserInfo userInfo [], int user_count);
int UserChoice(void);
void IncorrectInput(void);
void clearScreenPartially(int x, int y);
void clearExceptBottomLine(int x, int y);
void color(int colorNumber);
int selectData(int searchResult [], UserInfo userInfo []);
void showChosenData(UserInfo userInfo [], int i, int line, int y);

#endif