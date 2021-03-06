// TestCode2018.cpp   学生管理系统
/*
   本代码基于平台只限于Microsotf Visual studio 2017版本（兼容2015版本）
   Microsotf Visual C++6.0版本请自行删改
   copyright（2017-2018） 作者：山西农业大学软件学院 2017级 软件1703班 张瑞显
*/



#include "stdafx.h"
#include<stdlib.h>
#include<string.h>
#define N 10


struct student
{
	int   number;
	char  name[20];
	float Cprogram;
	float HighMath;
	float English;
};

//为了解决_gcvt函数需要另一个字符数组而临时建立的存储空间
char studentProgram1[N][80] = {}; //C语言成绩存储空间
char studentProgram2[N][80] = {}; //高数成绩存储空间
char studentProgram3[N][80] = {}; //英语成绩存储空间


typedef struct student stStu;
stStu student[N];
int arrayLength;

//用户的信息
struct User {
	char name[20];
	char password[20];
};

typedef struct User stUser;

//为了解决从硬盘读入信息而临时建立的存储空间
struct pro
{
	char   number;
	char  name[20];
	char  Cprogram;
	char  HighMath;
	char  English;
};
struct pro plus[N];


//功能函数区域
void loadUserInfor(struct User*userInfor, char *filename);
void saveUserInfor(struct User userInfor, char *filename);
void displayMenu();
void welcome();
int  login();
void inputMenu();
int inputInfor(stStu student[], int length);
void updateInfor(stStu student[], int length);
void delInfor(stStu student[], int length);
void saveToFile(stStu student[], int length);
void outputInfor(stStu student[], int length);
void queryByName(stStu student[], int length, char name[]);
void calculationMenu();
void calculation(stStu student[], int length);
void calculation_Cprogram(stStu student[], int length);
void calculation_HighMath(stStu student[], int length);
void calculation_Engilsh(stStu student[], int length);
void CprogramMenu();
void HighMathMenu();
void EnglishMenu();
int  programMax_Cprogram(stStu student[], int length);
int programMax_HighMath(stStu student[], int length);
int programMax_English(stStu student[], int length);

/*
1.读取用户信息函数
2.存储用户信息函数
3.主菜单函数
4.欢迎界面函数
5.登陆程序函数
6.二级菜单函数
7.增加学生信息函数
8.修改学生信息函数
9.删除学生信息函数
10.保存学生信息函数
11.显示学生信息函数
12.查找学生信息函数
13.成绩汇总统计 计算目录函数
14.成绩统计汇总函数
15.C语言成绩汇总计算函数
16.高数成绩汇总计算函数
17.英语成绩汇总计算函数
18.C语言成绩函数目录
19.高数成绩函数目录
20.英语成绩函数目录
21.C英语成绩最高分计算函数
22.高数成绩最高分计算函数
23.英语成绩最高分计算函数


*/





//读取用户信息
void loadUserInfor(struct User* userInfor, char *filename) {
	FILE *fp = NULL;
	fp = fopen(filename, "rb");
	if (fp == NULL) {
		printf("打开文件出错！\n");
		exit(0);
	}
	fread(userInfor, sizeof(struct User), 1, fp);
	fclose(fp);
}

//存储用户信息
void saveUserInfor(struct User userInfor, char *filename) {
	FILE *fp = NULL;
	fp = fopen(filename, "wb");
	if (fp == NULL) {
		printf("打开文件出错！\n");
		exit(0);
	}
	fwrite(&userInfor, sizeof(struct User), 1, fp);
	fclose(fp);
}


//欢迎界面
void welcome() {

	printf("**********************************************************************\n");
	printf("                      您好,欢迎使用学生管理系统!                      \n");
	printf("**********************************************************************\n");
	printf("\n");
}

//主菜单
void displayMenu() {
	printf("\n********************************************************************\n");
	printf("*                     学生成绩管理系统                             *\n");
	printf("*                                                                  *\n");
	printf("*                     1.输入学生信息                               *\n");
	printf("*                     2.输出学生信息                               *\n");
	printf("*                     3.查找学生信息                               *\n");
	printf("*                     4.成绩汇总统计                               *\n");
	printf("*                                                                  *\n");
	printf("*                     0.退出系统                                   *\n");
	printf("********************************************************************\n");
}


//登陆程序
int login() {
	struct User currentUser, sysUser = { 0 };
	//currentUser 指代已经存储的用户名  sysUser指代新用户名
	loadUserInfor(&sysUser, "user.txt");


	//判断已存储数据是否为空
	if (strlen(sysUser.name) == 0) {
		printf("输入用户名进行程序初始化\n");
		gets_s(sysUser.name);
		printf("请输入您要设置的登陆密码\n");
		gets_s(sysUser.password);
		saveUserInfor(sysUser, "user.txt");

		//清屏 美观
		system("cls");
		welcome();
	}


	//登陆判断程序
	printf("请输入用户名\n");
	scanf("%s", &currentUser.name);
	printf("请输入密码\n");
	scanf("%s", &currentUser.password);

	if (strcmp(currentUser.name, sysUser.name) == 0 && strcmp(currentUser.password, sysUser.password) == 0) {
		return 1;
	}
	else {
		return 0;
	}

}

//二级菜单
void inputMenu()
{
	int choice;
	system("cls");
	printf("\n********************************************************************\n");
	printf("*                     学生成绩管理系统                             *\n");
	printf("*                                                                  *\n");
	printf("*                     1.增加学生信息                               *\n");
	printf("*                     2.修改学生信息                               *\n");
	printf("*                     3.删除学生信息                               *\n");
	printf("*                     4.保存学生信息                               *\n");
	printf("*                                                                  *\n");
	printf("*                     0.返回上级菜单                               *\n");
	printf("********************************************************************\n");

	printf("\n请选择你要进行的操作(1,2,3,4,0)\n");
	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		arrayLength = inputInfor(student, N);
		printf("当前系统中已经存有:%d个学生信息\n", arrayLength);
		break;
	case 2:
		updateInfor(student, N);
		break;
	case 3:
		delInfor(student, arrayLength);
		printf("已删除");
		break;
	case 4:
		saveToFile(student, arrayLength);
		break;
	case 0:
		system("cls");
		break;

	default:
		break;
	}
}



//增加学生信息函数
int inputInfor(stStu student[], int length)
{

	int i = arrayLength;
	while (i<length)

	{
		printf("请输入以下信息：\n");
		printf("注意：输入0自动结束\n");
		printf("学号:");

		//优化死循环
		scanf("%d", &student[i].number);

		if (getchar() != -1) {
			fflush(stdin);
		}
		//scanf()返回值问题

		if (student[i].number == 0)
		{
			break;
		}
		printf("姓名:");
		scanf("%s", student[i].name);


		printf("C语言成绩：");
		scanf("%s", _gcvt(student[i].Cprogram, 10, studentProgram1[i]));


		printf("高数成绩：");
		scanf("%s", _gcvt(student[i].HighMath, 10, studentProgram2[i]));



		printf("英语成绩：");
		scanf("%s", _gcvt(student[i].English, 10, studentProgram3[i]));


		i++;

	}


	return i;
}


//修改学生信息
void updateInfor(stStu student[], int length)
{
	int number;
	int endFlag = 0;
	int i;
	while (!endFlag)
	{
		printf("输入学号:");
		scanf("%d", &number);

		for (i = 0; i < length; i++) {
			if (number == student[i].number) {
				endFlag = 1;
				break;
			}

		}

		if (endFlag == 0) {
			printf("输入学号错误！请重新输入：");
		}
	}
	printf("修改学号：");
	scanf("%d", &student[i].number);


	printf("修改姓名：");
	scanf("%s", student[i].name);;


	printf("修改C语言成绩：");
	scanf("%s", studentProgram1[i]);

	printf("修改高数成绩：");
	scanf("%s", studentProgram2[i]);


	printf("修改英语成绩：");
	scanf("%s", studentProgram3[i]);


}


//删除学生信息

void delInfor(stStu student[], int length)
{
	int endFlag = 0;
	int number, i, k;
	while (!endFlag)
	{
		printf("请输入您要删除的学号：");
		scanf("%d", &number);
		for (i = 0; i < length; i++) {
			if (number == student[i].number) {
				endFlag = 1;
				k = i;
				break;

			}
		}
		printf("\n");
		if (endFlag == 0) {
			printf("输入学号错误！请重新输入：");
		}
	}
	for (i = k; i < length; i++) {
		student[i] = student[i + 1];
	}
	arrayLength = arrayLength - 1;

}


//保存学生信息
void saveToFile(stStu student[], int length)
{
	FILE*fp = NULL;
	int i = 0;
	fp = fopen("student.txt", "wb");
	if (fp == NULL) {
		printf("打开文件出错\n");
		exit(0);
	}
	fprintf(fp, "%d", arrayLength);
	fprintf(fp, "\r\n");
	for (i = 0; i < length; i++) {
		fprintf(fp, "%d %s %s %s %s", student[i].number, student[i].name, studentProgram1[i], studentProgram2[i], studentProgram3[i]);
		fprintf(fp, "\r\n");

	}
	fclose(fp);
	printf("保存完成\n");
}

//显示学生信息
void outputInfor(stStu student[], int length)
{

	printf("学号     姓名     C语言成绩        高数成绩         英语程序 \n");
	printf("------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < length; i++) {
		printf("%4d      %s         %s             %s            %s\n", student[i].number, student[i].name, studentProgram1[i], studentProgram2[i], studentProgram3[i]);
	}
	printf("\n");
}


//查找学生信息
void queryByName(stStu student[], int length, char name[])
{
	int i = 0;
	printf(" ");
	printf("学号     姓名     C语言成绩        高数成绩         英语程序 \n");
	printf("------------------------------------------------------------------------------------------------\n");
	for (i = 0; i < length; i++) {
		if (strcmp(name, student[i].name) == 0) {
			printf("%4d      %s         %s          %s              %s\n", student[i].number, student[i].name, studentProgram1[i], studentProgram2[i], studentProgram3[i]);
			break;
		}
	}if (i >= length) {
		printf("不存在\n");
	}
}



//C语言成绩分段计算程序
void calculation_Cprogram(stStu student[], int length)
{
	int i;
	int index;
	int all = 0;
	int arrayResult[N + 1] = { 0 };
	for (i = 0; i < length; i++) {
		index = atoi(studentProgram1[i]) / 10;
		arrayResult[index]++;
	}
	for (i = 0; i < 6; i++) {
		all += arrayResult[i];
	}
	printf("0分到59分的人数为%d\n", all);

	for (i = 6; i < 9; i++) {
		printf("%d分到%d分的人数为%d\n", i * 10, i * 10 + 9, arrayResult[i]);
	}
	printf("90分到100分的人数为%d\n", arrayResult[9] + arrayResult[10]);
}

//高数成绩分段计算程序
void calculation_HighMath(stStu student[], int length)
{
	int i;
	int index;
	int all = 0;
	int arrayResult[N + 1] = { 0 };
	for (i = 0; i < length; i++) {
		index = atoi(studentProgram2[i]) / 10;
		arrayResult[index]++;
	}
	for (i = 0; i < 6; i++) {
		all += arrayResult[i];
	}
	printf("0分到59分的人数为%d\n", all);

	for (i = 6; i < 9; i++) {
		printf("%d分到%d分的人数为%d\n", i * 10, i * 10 + 9, arrayResult[i]);
	}
	printf("90分到100分的人数为%d\n", arrayResult[9] + arrayResult[10]);
}

//英语成绩分段计算程序
void calculation_Engilsh(stStu student[], int length)
{
	int i;
	int index;
	int all = 0;
	int arrayResult[N + 1] = { 0 };
	for (i = 0; i < length; i++) {
		index = atoi(studentProgram3[i]) / 10;
		arrayResult[index]++;
	}
	for (i = 0; i < 6; i++) {
		all += arrayResult[i];
	}
	printf("0分到59分的人数为%d\n", all);

	for (i = 6; i < 9; i++) {
		printf("%d分到%d分的人数为%d\n", i * 10, i * 10 + 9, arrayResult[i]);
	}
	printf("90分到100分的人数为%d\n", arrayResult[9] + arrayResult[10]);
}


//成绩统计汇总程序
void calculation(stStu student[], int length)
{
	int choice;
	calculationMenu();
	printf("\n请选择你要进行的操作(1,2,3,0)\n");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		CprogramMenu();
		break;
	case 2:
		HighMathMenu();
		break;
	case 3:
		EnglishMenu();
		break;
	case 0:
		break;

	default:
		break;
	}

}

//成绩汇总统计 计算目录
void calculationMenu()
{
	system("cls");
	printf("\n********************************************************************\n");
	printf("*                     学生成绩管理系统                             *\n");
	printf("*                                                                  *\n");
	printf("*                     1.C语言成绩汇总                              *\n");
	printf("*                     2.高数成绩汇总                               *\n");
	printf("*                     3.英语成绩汇总                               *\n");
	printf("*                                                                  *\n");
	printf("*                                                                  *\n");
	printf("*                     0.返回上级菜单                               *\n");
	printf("********************************************************************\n");
}


//C语言成绩统计目录
void CprogramMenu()
{
	int all = 0;
	int choice;
	system("cls");
	printf("\n********************************************************************\n");
	printf("*                     学生成绩管理系统                             *\n");
	printf("*                                                                  *\n");
	printf("*                     1.C语言成绩最高分                            *\n");
	printf("*                     2.C语言成绩平均分                            *\n");
	printf("*                     3.按分数段统计                               *\n");
	printf("*                                                                  *\n");
	printf("*                                                                  *\n");
	printf("*                     0.返回上级菜单                               *\n");
	printf("********************************************************************\n");

	printf("\n请选择你要进行的操作(1,2,3,4,0)\n");
	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		printf("最高分为:%d", programMax_Cprogram(student, arrayLength));
		break;
	case 2:

		for (int i = 0; i < arrayLength; i++) {
			all += atoi(studentProgram1[i]);
		}
		printf("平均分为:%d", all / arrayLength);
		break;
	case 3:
		calculation_Cprogram(student, arrayLength);
		break;

	case 0:
		system("cls");
		break;

	default:
		break;
	}
}

//高数成绩统计目录
void HighMathMenu()
{
	int all = 0;
	int choice;
	system("cls");
	printf("\n********************************************************************\n");
	printf("*                     学生成绩管理系统                             *\n");
	printf("*                                                                  *\n");
	printf("*                     1.高数成绩最高分                            *\n");
	printf("*                     2.高数成绩平均分                            *\n");
	printf("*                     3.按分数段统计                               *\n");
	printf("*                                                                  *\n");
	printf("*                                                                  *\n");
	printf("*                     0.返回上级菜单                               *\n");
	printf("********************************************************************\n");

	printf("\n请选择你要进行的操作(1,2,3,4,0)\n");
	scanf("%d", &choice);

	switch (choice)
	{
	case 1:
		printf("最高分为:%d", programMax_HighMath(student, arrayLength));
		break;
	case 2:

		for (int i = 0; i < arrayLength; i++) {
			all += atoi(studentProgram2[i]);
		}
		printf("平均分为:%d", all / arrayLength);
		break;
	case 3:
		calculation_HighMath(student, arrayLength);
		break;

	case 0:
		system("cls");
		break;

	default:
		break;

	}
}

//英语成绩统计目录
void EnglishMenu()
{
	int all = 0;
	int choice;
	system("cls");
	printf("\n********************************************************************\n");
	printf("*                     学生成绩管理系统                             *\n");
	printf("*                                                                  *\n");
	printf("*                     1.英语成绩最高分                             *\n");
	printf("*                     2.英语成绩平均分                             *\n");
	printf("*                     3.按分数段统计                               *\n");
	printf("*                                                                  *\n");
	printf("*                                                                  *\n");
	printf("*                     0.返回上级菜单                               *\n");
	printf("********************************************************************\n");

	printf("\n请选择你要进行的操作(1,2,3,4,0)\n");
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		printf("最高分为:%d", programMax_English(student, arrayLength));
		break;
	case 2:

		for (int i = 0; i < arrayLength; i++) {
			all += atoi(studentProgram3[i]);
		}
		printf("平均分为:%d", all / arrayLength);
		break;
	case 3:
		calculation_Engilsh(student, arrayLength);
		break;

	case 0:
		system("cls");
		break;

	default:
		break;
	}
}

//C成绩最大值计算函数
int  programMax_Cprogram(stStu student[], int length)
{
	int i;
	int max;
	max = atoi(studentProgram1[1]);
	for (i = 0; i < arrayLength; i++) {
		if (atoi(studentProgram1[i]) > max) {
			max = atoi(studentProgram1[i]);
		}
	}
	return max;
}

//高数成绩最大值计算函数
int programMax_HighMath(stStu student[], int length)
{
	int i;
	int max;
	max = atoi(studentProgram2[1]);
	for (i = 0; i < arrayLength; i++) {
		if (atoi(studentProgram2[i]) > max) {
			max = atoi(studentProgram2[i]);
		}
	}
	return max;
}

//英语成绩最大值计算函数
int programMax_English(stStu student[], int length)
{
	int i;
	int max;
	max = atoi(studentProgram3[1]);
	for (i = 0; i < arrayLength; i++) {
		if (atoi(studentProgram3[i]) > max) {
			max = atoi(studentProgram3[i]);
		}
	}
	return max;
}


int main()
{
	char stuName[20];
	int choice;
	FILE*fp = NULL;
	int i = 0;
	welcome();
	printf("正在读取数据请稍后.....\n");

	//打开文件
	fp = fopen("student.txt", "r");

	//若打开文件失败
	if (fp == NULL) {
		exit(0);
	}

	//读取结构体数据的总数
	fscanf(fp, "%d", &arrayLength);

	//数据总数非法
	if (arrayLength <= 0) {
		fclose(fp);
	}

	//读取数据
	for (i; i < arrayLength; i++) {
		fscanf(fp, "%d %s %s %s %s", &student[i].number, &student[i].name, &studentProgram1[i], &studentProgram2[i], &studentProgram3[i]);
	}

	printf("文件预计由数据%d个，实际读到%d个\n", arrayLength, i);
	printf("\n");
	while (!login())
	{
		printf("用户名或密码错误，请重新输入！\n");
	}
	while (1)
	{
		displayMenu();
		printf("\n请选择你要进行的操作(1,2,3,4,0)\n");
		scanf("%d", &choice);

		//跳入其他菜单或者其他应用程序
		switch (choice)
		{
		case 1:
			inputMenu();
			break;
		case 2:

			if (arrayLength == 0) {
				printf("系统中没有学生信息，请加入信息后重新进行\n");

			}
			else
			{
				outputInfor(student, arrayLength);
			}
			break;
		case 3:
			printf("请输入您要查找的姓名:");
			scanf("%s", stuName);
			queryByName(student, arrayLength, stuName);
			break;

		case 4:
			calculation(student, arrayLength);
			break;

		case 0:
			exit(0);
			break;

		default:
			break;
		}
	}

	return 0;

}

