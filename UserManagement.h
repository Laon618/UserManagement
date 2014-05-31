#ifndef __USERMANAGEMENT_H__
#define __USERMANAGEMENT_H__

typedef struct userinfo{
	int userId;
	char userName[30];
	char userAddress[128];
	char userCellphone[30];
}UserInfo;

void deleteData(UserInfo userInfo [], int i);
int initData(UserInfo userInfo [], FILE* fp);
void setUserInfo(char buffer [], UserInfo *userInfo);
void printfData(UserInfo userInfo [], FILE *writeFile, int count);
void showData(UserInfo userInfo [], int count);
void insertMember(UserInfo userInfo [], int count);
int searchData(UserInfo userInfo [], int count);
void updateData(UserInfo userInfo[], int i);
void cellphoneFormCheck(UserInfo userInfo [], int count);
void userManagement(int userChoice, UserInfo userInfo [], int user_count, int result, FILE *readFile, FILE *writeFile);
char backToMenu(char userChoice);
int duplicationCheck(UserInfo userInfo [], int count);

#endif