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
void insertMember(UserInfo userInfo [], int count);
int searchData(UserInfo userInfo [], int count);
void updateData(UserInfo userInfo[], int i, int user_count);
void cellphoneFormCheck(UserInfo userInfo[], int count, int input);
void userManagement(char userChoice, UserInfo userInfo [], int user_count, int result, FILE *readFile, FILE *writeFile);
char backToMenu(char userChoice);
int duplicationCheck(UserInfo userInfo [], int count, int input);
char incorrectInput(void);
void cellphoneInput(UserInfo userInfo [], int input, char tempCellphone []);
void endProgram(char userChoice, UserInfo userInfo [], int user_count, FILE *readFile, FILE *writeFile);

#endif