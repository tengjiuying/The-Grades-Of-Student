#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>//定义了通过控制台进行数据输入和数据输出的函数，主要是一些用户通过按键盘产生的对应操作，比如getch()函数等
#include <windows.h>//system()函数要在Windows下操作
#include <ctype.h>//定义了一批C语言字符分类函数，用于测试字符是否属于特定的字符类别，如字母字符、控制字符等等
//如本次程序中用到的isprint函数，isprint函数功能：检查ch是否是可打印字符(包括空格),其ASCII码在0x20到0x7E之间
#define YES 1
#define NO 0
typedef struct
{
	int num;
	float math_score;
	float engl_score;
	float chin_score;
	float phy_score;
	float chem_score;
	double aver_score;
	double sum_score;
	char sex;
}StudentDate;//学生基本信息

typedef struct student
{
	char name[20];//学生姓名
	StudentDate one;//学生其他信息
	int rank;//成绩排名
	struct student *next;
}Student, *List;

Student *startCheck(void);//开始检查、定义函数，此函数返回一个指向链表头的指针*/
Student *createListHead(void);//创建链表的头

void menu(void);//主菜单

void sortList(Student *pHead);//排序链表

void readListWithFile(Student *pHead, char *file_name);//从文件中读取数据，并保存在链表中

void sorttList(Student *pHead);//排序链表

int userChioce(Student *pHead);//用户选择

int sortMenu(void);//打印选择菜单

void passwordCheck(void);//密码检测

void correctWord(void);//修改密码

void addStudentInfo(Student *pHead);//向链表的末尾添加数据

int scanMenu(void);//浏览菜单

void findStudentInfo(Student *pHead);//查找学生信息

void delStudentInfo(Student *pHead);//删除某一个学生信息

void alterStudentInfo(Student *pHead);//修改学生信息

void saveList(Student *pHead);//将链表保存在文件里

void printList(Student *pHead);//打印链表

void statisStudentInfo(Student *pHead);//查看学生信息

int statisMenu(void);//查看菜单

void gotoxy(int x, int y);//改变光标位置函数/*gotoxy（x，y）将光标移动到指定行y和列x*/

void inputData(Student *pHead, Student *node);//输入信息，并检测是否合法

int main(void)
{
	Student *pHead;
	
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//得到窗口句柄
	SMALL_RECT rc = { 0, 0, 94 - 1, 30 - 1 };   //{Y位置,X位置,宽,高}
	SetConsoleWindowInfo(hOut, true, &rc);// 重置窗口位置和大小

	system("color 37");//设置控制台颜色
	pHead = startCheck();//读取信息
	
	while (1)
	{
		if (9 == userChioce(pHead)) //按9时退出系统
		{
			break;
		}
	}

	return 0;
}

void menu(void)
{
	system("CLS");//清屏
	printf("\n\n\n\t\t\t\t┌─────────────────┐\n");
	printf("\t\t\t\t│         学生成绩统计系统         │\n");
	printf("\t\t\t\t├─────────────────┤\n");
	printf("\t\t\t\t│         1   增加学生记录         │\n");
	printf("\t\t\t\t├─────────────────┤\n");
	printf("\t\t\t\t│         2   删除学生记录         │\n");
	printf("\t\t\t\t├─────────────────┤\n");
	printf("\t\t\t\t│         3   修改学生记录         │\n");
	printf("\t\t\t\t├─────────────────┤\n");
	printf("\t\t\t\t│         4   查找学生信息         │\n");
	printf("\t\t\t\t├─────────────────┤\n");
	printf("\t\t\t\t│         5   统计学生成绩         │\n");
	printf("\t\t\t\t├─────────────────┤\n");
	printf("\t\t\t\t│         6   查看学生成绩         │\n");
	printf("\t\t\t\t├─────────────────┤\n");
	printf("\t\t\t\t│         7   修改登陆密码         │\n");
	printf("\t\t\t\t├─────────────────┤\n");
	printf("\t\t\t\t│         8      关于              │\n");
	printf("\t\t\t\t├─────────────────┤\n");
	printf("\t\t\t\t│         9    退出系统            │\n");
	printf("\t\t\t\t└─────────────────┘\n");
}

void gotoxy(int x, int y)//x为列坐标,y为行坐标
{
	COORD pos = { x, y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	/*GetStdHandle（）返回标准的输入、输出或错误的设备的句柄，也就是获得输入、输出/错误的屏幕缓冲区的句柄*/
	SetConsoleCursorPosition(hOut, pos);
}

Student *startCheck(void)
{
	Student *pHead;
	FILE  *fp1;
	char password[20] = "123456";
	int i;

	if ((fp1 = fopen("password.dat", "rb")) == NULL)//（为了输入数据打开一个二进制文件）若密码文件不存在，新建密码文件
	{
		fp1 = fopen("password.dat", "wb");//为了输出数据打开一个二进制文件，将fopen函数的返回值赋给指针变量fp
		fwrite(password, 20, 1, fp1);
		fclose(fp1);
		printf("密码初始化完成！（默认密码为：123456）");
		passwordCheck();
	}
	else
	{
		passwordCheck();
	}
	//读条
	system("CLS");
	system("title 学生成绩统计系统-载入中");//将标题栏命名为“学生成绩统计系统”
	printf("\n\n\t\t\t欢迎进入本系统！正在载入.....");
	printf("\n\n\n\n\t\t\t┏━━━━━━━━━━┓\n");
	printf("\t\t\t┃                    ┃\n");
	printf("\t\t\t┗━━━━━━━━━━┛\n");
	gotoxy(26, 7);
	for ( i = 0; i < 10; i++)
	{
		printf("█");
		Sleep(100);
	}

	pHead = createListHead();
	readListWithFile(pHead, "stud.dat");

	return pHead;
}

Student *createListHead(void)
{
	Student *pHead;

	pHead = (List)malloc(sizeof(Student));
	pHead->next = NULL;

	return pHead;
}

void readListWithFile(Student *pHead, char *file_name)
{
	FILE *fp;
	Student *p1, *p2;
	int count, rank = 0;
	StudentDate dat;
	char stu_name[20];

	fp = fopen(file_name, "r");//为了输入数据打开一个已存在的文本文件。只读
	if (fp == NULL)
	{
		fp = fopen(file_name, "w");//为了输出数据，打开一个文本文件。只写
		fclose(fp);
		return;
	}
	fseek(fp, 0L, 2);/*fseek()用来移动文件流的读写位置,fseek(文件类型指针fp，位移量，起始点)*/
	count = ftell(fp);/*使用ftell来取得目前读写的位置*/
	/*主要是fseek和ftell两个结合起来用更加能够确定文件当前的位置*/
	p1 = pHead;
	fp = fopen(file_name, "r");
	while (!feof(fp))
	{
		p2 = (List)malloc(sizeof(Student));
		fscanf(fp, "%d%s %c%f%f%f%f%f\n", &p2->one.num, p2->name, &p2->one.sex, &p2->one.chin_score,
			&p2->one.math_score, &p2->one.engl_score, &p2->one.chem_score, &p2->one.phy_score);/*用fscanf函数从磁盘文件上读入ASCII字符*/
		p2->one.sum_score = (double)(p2->one.chin_score + p2->one.chin_score + p2->one.engl_score +
			p2->one.chem_score + p2->one.phy_score);
		p2->one.aver_score = p2->one.sum_score / 5;
		p2->next = NULL;
		p1->next = p2;
		p1 = p2;
		if (ftell(fp) == count)
		{
			break;
		}
	}
	//将链表排序，并初始化排名
	for (p1 = pHead->next; p1 != NULL; p1 = p1->next)
	{
		for (p2 = p1->next; p2 != NULL; p2 = p2->next)
		{
			if (p2->one.aver_score > p1->one.aver_score)
			{
				dat = p2->one;
				strcpy(stu_name, p2->name);
				p2->one = p1->one;
				strcpy(p2->name, p1->name);
				p1->one = dat;
				strcpy(p1->name, stu_name);
			}
		}
		p1->rank = ++rank;
	}
	fclose(fp);
}

void sortList(Student *pHead)//排序链表
{
	Student *p1, *p2;
	StudentDate dat;
	char stu_name[20];
	int bum, count = 0, rank;

	system("title 学生成绩统计系统-查看");//将标题栏命名为“学生成绩统计系统”
	bum = sortMenu();
	if (bum == 1)//按平均分高低排序
	{
		for (p1 = pHead->next; p1 != NULL; p1 = p1->next)
		{
			for (p2 = p1->next; p2 != NULL; p2 = p2->next)
			{
				if (p2->one.aver_score > p1->one.aver_score)
				{
					dat = p2->one;
					rank = p2->rank;
					strcpy(stu_name, p2->name);
					p2->one = p1->one;
					p2->rank = p1->rank;
					strcpy(p2->name, p1->name);
					p1->one = dat;
					p1->rank = rank;
					strcpy(p1->name, stu_name);
				}
			}
		}
	}
	else
	{
		if (bum == 2)//按学号高低排序
		{
			for (p1 = pHead->next; p1 != NULL; p1 = p1->next)
			{
				for (p2 = p1->next; p2 != NULL; p2 = p2->next)
				{
					if (p2->one.num < p1->one.num)
					{
						dat = p2->one;
						rank = p2->rank;
						strcpy(stu_name, p2->name);
						p2->one = p1->one;
						p2->rank = p1->rank;
						strcpy(p2->name, p1->name);
						p1->one = dat;
						p1->rank = rank;
						strcpy(p1->name, stu_name);
					}
				}
			}
		}
		else
		{
			if (bum == 3)
			{
				return;
			}
			else
			{
				sortList(pHead);
			}
		}
	}
	printList(pHead);
}

void printList(Student *pHead)//打印链表
{
	int count = 0;
	pHead = pHead->next;
	system("CLS");
	printf("\t\t\t\t计科3班成绩！");
	printf("\n\n  ┏━━━┳━━━━┳━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━┓");
	printf("\n  ┃ 学号 ┃ 姓 名  ┃性别┃语  文┃数  学┃英  语┃化  学┃物  理┃平均分┃总  分┃名次┃\n");
	while (pHead)
	{ 
		printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
		printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", pHead->one.num,
			pHead->name, pHead->one.sex, pHead->one.chin_score, pHead->one.math_score,
			pHead->one.engl_score, pHead->one.chem_score
			, pHead->one.phy_score, pHead->one.aver_score, pHead->one.sum_score, pHead->rank);
		pHead = pHead->next;
		count++;
	}
		printf("  ┗━━━┻━━━━┻━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━┛\n");
	printf("\t\t\t该班一共%d个人!", count);
	getch();
}

int userChioce(Student *pHead)
{
	int bum;

	system("title 学生成绩统计系统-主菜单");//将标题栏命名为“学生成绩统计系统”
	menu();
	printf("请按键选择: ");
	bum = (int)(getch() - '0');
	switch (bum)
	{
	case 1:
		addStudentInfo(pHead);
		break;
	case 2:
		delStudentInfo(pHead);
		break;
	case 3:
		alterStudentInfo(pHead);
		break;
	case 4:
		findStudentInfo(pHead);
		break;
	case 5:
		statisStudentInfo(pHead);
		break;
	case 9:
		break;
	case 6:
		sortList(pHead);
		break;
	case 7:
		correctWord();
		break;
	case 8:
		MessageBox(NULL, TEXT("特性：进入系统需输入密码，可以修改密码；展示学生信息时，以表格的方式呈现；输入学生信息时，不能输入已存在的学号；以链表、文件为基础；作者:TengFeng"), TEXT("关于"), MB_OK);
		break; 
	default:
		break;
	}

	return bum;
}

int sortMenu(void)//打印选择菜单
{
	int bum;

	system("CLS");
	printf("\n\n\n");
	printf("\t\t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t┃                       以什么方式查询 ？                  ┃\n");
	printf("\t\t┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t┃                    1   按成绩的高低                      ┃\n");
	printf("\t\t┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t┃                    2   按学号的升次                      ┃\n");
	printf("\t\t┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t┃                    3   返回主菜单                        ┃\n");
	printf("\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("请按键选择：");
	bum = (int)(getch() - '0');
	system("CLS");

	return bum;
}

void passwordCheck(void)
{
	char password[20], inputword[20];
	int i = 0, j = 0;
	char c = 0;//因为'\0'的ASCll码为0,所以char c=0和char c='\0'是一样的，由于\0属于不可显示字符，所以才用的这种写法
	/*即字符可以用ASCll码代替*/
	FILE *fp = fopen("password.dat", "rb");

	system("title 学生成绩统计系统-密码输入");//将标题栏命名为“学生成绩统计系统”
	fread(password, 20, 1, fp);//这个函数从fp所指向的文件读入1个20个字节的数据，存储到数组password中
	for (i = 0; i < 5; i++)
	{
		j = 0;
		printf("\n\n\n\t\t你还有%d次机会输入正确密码: ", 3-i);
		printf("\n\n\n\n\t\t\t┏━━━━━━━━┓\n");
		printf("\t\t\t┃                ┃\n");
		printf("\t\t\t┗━━━━━━━━┛\n");
		gotoxy(26, 8);/*gotoxy（x，y）将光标移动到指定行y和列x*/
		while ((c = getch()) != 13 && j < 20)
		{
			if (c == '\b' && j >0)
			{
				putchar('\b');
				putchar(' ');
				putchar('\b');
				j--;
			}
			else
			{
				if (isprint(c))//isprint()函数为检测C是否为可打印的函数 
				{
					putchar('*');
					inputword[j] = c;
					j++;
				}
			}
		}
		inputword[j] = '\0';
		if (strcmp(inputword, password) == 0)
		{
			return;
		}
		else
		{
			system("CLS");
			printf("\t\t\t密码输入错误");
		}
	}
	if (5 == i)
	{
		system("CLS");
		printf("\n\n\n\t\t你已浪费所有机会！程序即将退出！");
		Sleep(2000);
		exit(0);
	}
	fclose(fp);
	system("CLS");

	return;
}

void correctWord(void)//修改密码
{
	char password[20];
	FILE *fp;
	int i = 0;
	char c;

	system("title 学生成绩统计系统-修改密码");//将标题栏命名为“学生成绩统计系统”
	system("CLS");
	printf("\n\n\n\n\t\t\t请输入新的密码：");

	while ((c = getch()) != 13 && i < 20)
	//“13”对应的字符是CR,即回车的意思,这里是在捕捉用户有没有点击回车键.如果没有,那么输出一个“*”字符,
	//然后把刚刚捕捉到的字符赋值给password数组的一个元素,之后数值指针下移一个单位.
	//这段函数的意思是捕捉用户输入的键盘数据的ASCII玛值,以获取回车键为最终跳出循环即结束标志. 
	{
		if (c == '\b'&&i > 0)
		{
			putchar('\b');/*\b退格键*/
			putchar(' ');
			putchar('\b');
			i--;
		}
		else
		{
			if (isprint(c))//isprint为检测C是否为可打印的函数 
			{
				putchar('*');
				password[i] = c;
				i++;
			}
		}
	}
	password[i] = '\0';
	printf("\n\t\t\t是否将密码修改为<%s>? Y or N:", password);
	c = getch();
	if (c == 'Y' || c == 'y')
	{
		fp = fopen("password.dat", "wb");
		fwrite(password, 20, 1, fp);//向文件写一个数据块
		fclose(fp);
		printf("\n\t\t\t修改成功！\n");
	}
	else
	{
		return;
	}
	getch();
}

void addStudentInfo(Student *pHead)//向链表末尾添加数据
{
	FILE *fp;
	Student *p1, *p2, *p3 = pHead;
	StudentDate dat;
	int judge = YES, rank = 0;
	char bum, stu_name[20];

	system("title 学生成绩统计系统-添加");//将标题栏命名为“学生成绩统计系统”
	fp = fopen("stud.dat", "a");/*打开文件，向文本文件添加数据*/
	while (pHead->next)
	{
		pHead = pHead->next;
	}
	while (judge)
	{


		p1 = (List)malloc(sizeof(Student));
		inputData(p3, p1);
		p1->next = NULL;
		pHead->next = p1;//把p1所指的结点连接到表尾
		pHead = p1;//pHead移到表尾
		fprintf(fp, "%d %s %c %.1f %.1f %.1f %.1f %.1f\n", p1->one.num, p1->name, p1->one.sex, p1->one.chin_score,
			p1->one.math_score, p1->one.engl_score, p1->one.chem_score, p1->one.phy_score);
		printf("是否继续添加？(Y/N)");
		bum = getch();
		if (bum == 'n' || bum == 'N')
		{
			break;
		}
		
	}
	//并交换排名，降序，按平均分从大到小排列
	for (p1 = p3->next; p1 != NULL; p1 = p1->next)
	{
		for (p2 = p1->next; p2 != NULL; p2 = p2->next)
		{
			if (p2->one.aver_score > p1->one.aver_score)
			{
				dat = p2->one;
				strcpy(stu_name, p2->name);
				p2->one = p1->one;
				strcpy(p2->name, p1->name);
				p1->one = dat;
				strcpy(p1->name, stu_name);
			}
		}
		p1->rank = ++rank;
	}
	fclose(fp);
}

int scanMenu(void)
{
	int bum;

	system("CLS");
	printf("\n\n\n");
	printf("\t\t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t┃                       以什么方式查询 ？                  ┃\n");
	printf("\t\t┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t┃                    1   按学生的学号                      ┃\n");
	printf("\t\t┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t┃                    2   按学生的姓名                      ┃\n");
	printf("\t\t┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t┃                    3   返回主菜单                        ┃\n");
	printf("\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("请按键选择：");
	bum = (int)(getch() - '0');
	system("CLS");

	return bum;
}

void findStudentInfo(Student *pHead)
{
	int bum, count = 0;
	int num;
	char student_name[20];

	pHead = pHead->next;
	system("title 学生成绩统计系统-查找");//将标题栏命名为“学生成绩统计系统”
	bum = scanMenu();
	if (bum == 1)
	{
		printf("请输入学生的学号：");
		scanf("%d", &num);
		while (pHead)
		{
			if (pHead->one.num == num)
			{
				if (count == 0)
				{
					printf("\n\t\t\t已经查到！\n");
					printf("\n\n\n\n  ┏━━━┳━━━━┳━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━┓");
					printf("\n  ┃ 学号 ┃ 姓 名  ┃性别┃语  文┃数  学┃英  语┃化  学┃物  理┃平均分┃总  分┃名次┃\n");
					count = 1;
				}
				printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
				printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", pHead->one.num,
					pHead->name, pHead->one.sex, pHead->one.chin_score, pHead->one.math_score,
					pHead->one.engl_score, pHead->one.chem_score
					, pHead->one.phy_score, pHead->one.aver_score, pHead->one.sum_score, pHead->rank);
				break;
			}
			pHead = pHead->next;
		}
		if (pHead == NULL)
		{
			printf("\n\t\t\t没有该学生记录！\n");
		}
		else
		{
			printf("  ┗━━━┻━━━━┻━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━┛\n");
		}
	}
	else
	{
		if (bum == 2)
		{
			printf("请输入学生姓名：");
			scanf("%s", student_name);
			while (pHead)
			{
				if (strcmp(student_name, pHead->name) == 0)
				{
					if (count == 0)
					{
						printf("\n\t\t\t已经查到！\n");
						printf("\n\n\n\n  ┏━━━┳━━━━┳━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━┓");
						printf("\n  ┃ 学号 ┃ 姓 名  ┃性别┃语  文┃数  学┃英  语┃化  学┃物  理┃平均分┃总  分┃名次┃\n");
						count = 1;
					}
					printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
					printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", pHead->one.num,
						pHead->name, pHead->one.sex, pHead->one.chin_score, pHead->one.math_score,
						pHead->one.engl_score, pHead->one.chem_score
						, pHead->one.phy_score, pHead->one.aver_score, pHead->one.sum_score, pHead->rank);
				}
				pHead = pHead->next;
			}
			if (count == 0)
			{
				printf("\n\t\t\t没有该学生记录！");
			}
			else
			{
				printf("  ┗━━━┻━━━━┻━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━┛\n");
			}
		}
		else
		{
			if (bum == 3)
			{
				return;/*返回主界面*/
			}
			else
			{
				findStudentInfo(pHead);
			}
		}

	}
	getch();
}

void delStudentInfo(Student *pHead)
{
	Student *p1, *p2 = pHead;
	int bum;
	int num, count = 0;
	char student_name[20], c;

	system("title 学生成绩统计系统-删除");//将标题栏命名为“学生成绩统计系统”
	bum = scanMenu();
	if (bum == 1)
	{
		p1 = pHead->next;
		printf("\n\t\t\t请输入要删除学生的学号：");
		scanf("%d", &num);
		while (p1)
		{
			if (p1->one.num == num)
			{
				count = 1;/*学号存在就用count=1表示，不存在就是用count不等于0输出“该学号不存在”*/
				printf("\n\t\t\t删除成功，删除的学生学号为：%d", num);
				if (p1->next == NULL)
				{
					pHead->next = NULL;
					break;
				}
				else
				{
					pHead->next = p1->next;
					free(p1);
					p1 = pHead->next;
				}
			}
			else
			{
				pHead = pHead->next;
				p1 = pHead->next;
			}
		}
	}
	else
	{
		if (bum == 2)
		{
			p1 = pHead->next;
			printf("\n\t\t\t请输入要删除的学生姓名：");
			scanf("%s", student_name);
			//统计一共有多少个学生
			while (p1)
			{
				if (strcmp(p1->name, student_name) == 0)
				{
					count++;
				}
				p1 = p1->next;
			}
			if (count > 0)
			{
				printf("'\n\n\n\t\t\t一共有%d个人的信息 全部删除(Y) or 逐一删除(N)?", count);//选择全部删除，还是逐一删除
				c = getch();
				//全部删除
				if (c == 'y' || c == 'Y')
				{
					p1 = pHead->next;
					while (p1)
					{
						if (strcmp(p1->name, student_name) == 0)
						{
							printf("\n\t\t\t删除成功，姓名为: %s", student_name);
							if (p1->next == NULL)
							{
								pHead->next = NULL;
								break;
							}
							else
							{
								pHead->next = p1->next;
								free(p1);
								p1 = pHead->next;
							}
						}
						else
						{
							pHead = pHead->next;
							p1 = pHead->next;
						}
					}
					
				}
				else
				{
					//逐一删除
					p1 = pHead->next;
					while (p1)
					{
						if (strcmp(p1->name,student_name) == 0)
						{
							printf("\n姓名:%s,学号:%d,性别:%c  是否删除(y or n)?", p1->name, p1->one.num, p1->one.sex);
							c = getch();
							if (c == 'y'|| c == 'Y')
							{
								if (p1->next == NULL)
								{
									pHead->next = NULL;
									break;
								}
								else
								{
									pHead->next = p1->next;
									free(p1);
									p1 = pHead->next;
								}
								printf("成功！");
							}
							else
							{
								pHead = pHead->next;
								p1 = pHead->next;
							}
						}
						else
						{
							pHead = pHead->next;
							p1 = pHead->next;
						}
					}
				}
				
			}
		}
		else
		{
			if (bum == 3)
			{
				return;
			}
			else
			{
				delStudentInfo(pHead);
			}
		}
	}
	if (count == 0)
	{
		printf("\n\t\t\t没有该学生信息！");
	}
	else
	{
		saveList(p2);
	}
	getch();
}

void saveList(Student *pHead)
{
	FILE *fp;
	
	fp = fopen("stud.dat", "w+");/*为了读和写建立一个新文件*/
	pHead = pHead->next;
	while (pHead)
	{
		fprintf(fp, "%d %s %c %.1f %.1f %.1f %.1f %.1f\n", pHead->one.num, pHead->name, pHead->one.sex, pHead->one.chin_score,
			pHead->one.math_score, pHead->one.engl_score, pHead->one.chem_score, pHead->one.phy_score);
		pHead = pHead->next;
	}
	fclose(fp);
}

void alterStudentInfo(Student *pHead)
{
	int bum, count = 0, j = 0;
	int num;
	char student_name[20];
	Student *p1 = pHead->next;

	system("title 学生成绩统计系统-修改");//将标题栏命名为“学生成绩统计系统”
	bum = scanMenu();
	if (bum == 1)
	{
		printf("\n\t\t\t请输入要修改学生的学号：");
		scanf("%d", &num);
		while (p1)
		{
			j++;//统计学生数量
			if (p1->one.num == num)
			{
				inputData(pHead, p1);
				break;
			}
			p1 = p1->next;
		}
		if (p1 == NULL)
		{
			getch();
			printf("没有该学生信息！");
		}
	}
	else
	{
		if (bum == 2)
		{
			printf("\n\t\t\t请输入要修改学生的姓名：");
			scanf("%s", student_name);
			while (p1)
			{
				j++;
				if (strcmp(p1->name, student_name) == 0)
				{
					inputData(pHead, p1);
					count = 1;/*用于判定输入的姓名是否存在*/
				}
				p1 = p1->next;
			}
			if (count == 0)
			{
				printf("\n\t\t\t没有该学生信息！");
				getch();/*返回主界面*/
			}
		}
		else
		{
			if (3 == bum)
			{
				return;
			}
			else
			{
				alterStudentInfo(pHead);
			}
		}
	}
	saveList(pHead);
}

void statisStudentInfo(Student *pHead)
{
	double aver_score[5] = {0,0,0,0,0};
	Student *p1 = pHead->next;
	int count = 0;
	int bad = 0, bum;

	system("title 学生成绩统计系统-统计");//将标题栏命名为“学生成绩统计系统”
	bum = statisMenu();
	if (bum == 1)
	{
		while (p1)
		{
			aver_score[0] = aver_score[0] + p1->one.chin_score;
			aver_score[1] = aver_score[1] + p1->one.math_score;
			aver_score[2] = aver_score[2] + p1->one.engl_score;
			aver_score[3] = aver_score[3] + p1->one.chem_score;
			aver_score[4] = aver_score[4] + p1->one.phy_score;
			p1 = p1->next;
			count++;
		}
		aver_score[0] = aver_score[0] / count;
		aver_score[1] = aver_score[1] / count;
		aver_score[2] = aver_score[2] / count;
		aver_score[3] = aver_score[3] / count;
		aver_score[4] = aver_score[4] / count;
		p1 = pHead->next;
		printf("\n\n  ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
		printf("  ┃\t\t\t语文的平均分为:%.1f，没有达到达到平均分的学生有                 ┃\n", aver_score[0]);
		printf("  ┣━━━┳━━━━┳━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━┫\n");
		printf("  ┃ 学号 ┃ 姓 名  ┃性别┃语  文┃数  学┃英  语┃化  学┃物  理┃平均分┃总  分┃名次┃\n");
		printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
		while (p1)
		{
			if (p1->one.chin_score < aver_score[0])
			{
				if (bad == 0)
				{
					printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
						p1->one.engl_score, p1->one.chem_score
						, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				else
				{
					printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
					printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
						p1->one.engl_score, p1->one.chem_score
						, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				bad = 1;
			}
			p1 = p1->next;
		}
		bad = 0;
		p1 = pHead->next;
		printf("  ┣━━━┻━━━━┻━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━┫\n");
		printf("  ┃\t\t\t数学的平均分为:%.1f，没有达到达到平均分的学生有                 ┃\n", aver_score[1]);
		printf("  ┣━━━┳━━━━┳━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━┫\n");
		printf("  ┃ 学号 ┃ 姓 名  ┃性别┃语  文┃数  学┃英  语┃化  学┃物  理┃平均分┃总  分┃名次┃\n");
		printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
		while (p1)
		{
			if (p1->one.math_score < aver_score[1])
			{
				if (bad == 0)
				{
					printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
						p1->one.engl_score, p1->one.chem_score
						, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				else
				{
					printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
					printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
						p1->one.engl_score, p1->one.chem_score
						, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				bad = 1;
			}
			p1 = p1->next;
		}
		bad = 0;
		p1 = pHead->next;
		printf("  ┣━━━┻━━━━┻━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━┫\n");
		printf("  ┃\t\t\t英语的平均分为:%.1f，没有达到达到平均分的学生有                 ┃\n", aver_score[2]);
		printf("  ┣━━━┳━━━━┳━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━┫\n");
		printf("  ┃ 学号 ┃ 姓 名  ┃性别┃语  文┃数  学┃英  语┃化  学┃物  理┃平均分┃总  分┃名次┃\n");
		printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
		while (p1)
		{
			if (p1->one.engl_score < aver_score[2])
			{
				if (bad == 0)
				{
					printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
						p1->one.engl_score, p1->one.chem_score
						, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				else
				{
					printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
					printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
						p1->one.engl_score, p1->one.chem_score
						, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				bad = 1;
			}
			p1 = p1->next;
		}
		bad = 0;
		p1 = pHead->next;
		printf("  ┣━━━┻━━━━┻━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━┫\n");
		printf("  ┃\t\t\t化学的平均分为:%.1f，没有达到达到平均分的学生有                 ┃\n", aver_score[3]);
		printf("  ┣━━━┳━━━━┳━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━┫\n");
		printf("  ┃ 学号 ┃ 姓 名  ┃性别┃语  文┃数  学┃英  语┃化  学┃物  理┃平均分┃总  分┃名次┃\n");
		printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
		while (p1)
		{
			if (p1->one.chem_score < aver_score[3])
			{
				if (bad == 0)
				{
					printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
						p1->one.engl_score, p1->one.chem_score
						, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				else
				{
					printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
					printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
						p1->one.engl_score, p1->one.chem_score
						, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				bad = 1;
			}
			p1 = p1->next;
		}
		bad = 0;
		p1 = pHead->next;
		printf("  ┣━━━┻━━━━┻━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━┫\n");
		printf("  ┃\t\t\t物理的平均分为:%.1f，没有达到达到平均分的学生有                 ┃\n", aver_score[4]);
		printf("  ┣━━━┳━━━━┳━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━┫\n");
		printf("  ┃ 学号 ┃ 姓 名  ┃性别┃语  文┃数  学┃英  语┃化  学┃物  理┃平均分┃总  分┃名次┃\n");
		printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
		while (p1)
		{
			if (p1->one.phy_score < aver_score[4])
			{
				if (bad == 0)
				{
					printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
						p1->one.engl_score, p1->one.chem_score
						, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				else
				{
					printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
					printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
						p1->one.engl_score, p1->one.chem_score
						, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				bad = 1;
			}
			p1 = p1->next;
		}
		printf("  ┗━━━┻━━━━┻━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━┛\n");
		printf("\t\t\t\t\t\t该班一共%d个人!", count);
	}
	else
	{
		if (bum == 2)
		{
			bad = 0;
			printf("\n\n  ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
			printf("  ┃\t\t\t\t语文成绩大于90分或小于60的学生有                        ┃\n");
			printf("  ┣━━━┳━━━━┳━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━┫\n");
			printf("  ┃ 学号 ┃ 姓 名  ┃性别┃语  文┃数  学┃英  语┃化  学┃物  理┃平均分┃总  分┃名次┃\n");
			printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
			p1 = pHead->next;
			while (p1)
			{
				if (p1->one.chin_score < 60 || p1->one.chin_score >= 90)
				{
					if (bad == 0)
					{
						printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
							p1->one.engl_score, p1->one.chem_score
							, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					else
					{
						printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
						printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
							p1->one.engl_score, p1->one.chem_score
							, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					bad = 1;
				}
				p1 = p1->next;
			}
			bad = 0;
			printf("  ┣━━━┻━━━━┻━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━┫\n");
			printf("  ┃\t\t\t\t数学成绩大于90分或小于60的学生有                        ┃\n");
			printf("  ┣━━━┳━━━━┳━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━┫\n");
			printf("  ┃ 学号 ┃ 姓 名  ┃性别┃语  文┃数  学┃英  语┃化  学┃物  理┃平均分┃总  分┃名次┃\n");
			printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
			p1 = pHead->next;
			while (p1)
			{
				if (p1->one.math_score < 60 || p1->one.math_score >= 90)
				{
					if (bad == 0)
					{
						printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
							p1->one.engl_score, p1->one.chem_score
							, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					else
					{
						printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
						printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
							p1->one.engl_score, p1->one.chem_score
							, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					bad = 1;
				}
				p1 = p1->next;
			}
			bad = 0;
			printf("  ┣━━━┻━━━━┻━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━┫\n");
			printf("  ┃\t\t\t\t英语成绩大于90分或小于60的学生有                        ┃\n");
			printf("  ┣━━━┳━━━━┳━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━┫\n");
			printf("  ┃ 学号 ┃ 姓 名  ┃性别┃语  文┃数  学┃英  语┃化  学┃物  理┃平均分┃总  分┃名次┃\n");
			printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
			p1 = pHead->next;
			while (p1)
			{
				if (p1->one.engl_score < 60 || p1->one.engl_score >= 90)
				{
					if (bad == 0)
					{
						printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
							p1->one.engl_score, p1->one.chem_score
							, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					else
					{
						printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
						printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
							p1->one.engl_score, p1->one.chem_score
							, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					bad = 1;
				}
				p1 = p1->next;
			}
			bad = 0;
			printf("  ┣━━━┻━━━━┻━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━┫\n");
			printf("  ┃\t\t\t\t化学成绩大于90分或小于60的学生有                        ┃\n");
			printf("  ┣━━━┳━━━━┳━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━┫\n");
			printf("  ┃ 学号 ┃ 姓 名  ┃性别┃语  文┃数  学┃英  语┃化  学┃物  理┃平均分┃总  分┃名次┃\n");
			printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
			p1 = pHead->next;
			while (p1)
			{
				if (p1->one.chem_score < 60 || p1->one.chem_score >= 90)
				{
					if (bad == 0)
					{
						printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
							p1->one.engl_score, p1->one.chem_score
							, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					else
					{
						printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
						printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
							p1->one.engl_score, p1->one.chem_score
							, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					bad = 1;
				}
				p1 = p1->next;
			}
			bad = 0;
			printf("  ┣━━━┻━━━━┻━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━┫\n");
			printf("  ┃\t\t\t\t物理成绩大于90分或小于60的学生有                        ┃\n");
			printf("  ┣━━━┳━━━━┳━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━━┳━━┫\n");
			printf("  ┃ 学号 ┃ 姓 名  ┃性别┃语  文┃数  学┃英  语┃化  学┃物  理┃平均分┃总  分┃名次┃\n");
			printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
			p1 = pHead->next;
			while (p1)
			{
				if (p1->one.phy_score < 60 || p1->one.phy_score >= 90)
				{
					if (bad == 0)
					{
						printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
							p1->one.engl_score, p1->one.chem_score
							, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					else
					{
						printf("  ┣━━━╋━━━━╋━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━━╋━━┫\n");
						printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
							p1->one.engl_score, p1->one.chem_score
							, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					bad = 1;
				}
				p1 = p1->next;
			}
			printf("  ┗━━━┻━━━━┻━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━━┻━━┛\n");
		}
		else
		{
			if (bum == 3)
			{
				return;
			}
			else
			{
				statisStudentInfo(pHead);
			}
		}
	}
	getch();
}

int statisMenu(void)
{
	int bum;

	system("CLS");
	printf("\n\n\n");
	printf("\t\t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t┃                   以什么方式统计学生信息？               ┃\n");
	printf("\t\t┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t┃                      1   按平均分                        ┃\n");
	printf("\t\t┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t┃                      2   按是否合格                      ┃\n");
	printf("\t\t┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t┃                      3   返回主菜单                      ┃\n");
	printf("\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("请按键选择：");
	bum = (int)(getch() - '0');
	system("CLS");

	return bum;
}

void inputData(Student *pHead, Student *node)
{
	Student *p1 = node, *p2, *p3 = pHead;
	
	system("CLS");
	printf("\n\n\t请依次输入学生的学号、姓名、性别、语文、数学、英语、化学、物理成绩\n");
	printf("\t注意:姓名不能有空格，性别男用M表示，女佣W表示，\n\t各科成绩应该大于0小于100，输入数据时请用空格隔开\n");
	scanf("%d%s %c%f%f%f%f%f", &p1->one.num, p1->name, &p1->one.sex, &p1->one.chin_score, &p1->one.math_score,
		&p1->one.engl_score, &p1->one.chem_score, &p1->one.phy_score);
	// 判断输入的学号是否已经存在
	p2 = p3->next;
	while (1)
	{
		if (p2 == NULL)
		{
			break;
		}
		if (p2->one.num == p1->one.num && p2 != node)
		{
			printf("该学号已存在，请重新输入学号:");
			scanf("%d", &p1->one.num);
			p2 = p3->next;
		}
		else
		{
			p2 = p2->next;
		}
	}
	//性别是否合法
	while (1)
	{
		if (p1->one.sex != 'W'&& p1->one.sex != 'M')
		{
			p1->one.sex = getchar();
			printf("性别输入不合法，请重新输入: ");
			p1->one.sex = getchar();
			
		}
		else
		{
			break;
		}
	}
	//成绩是否合法
	while (1)
	{
		if (p1->one.chin_score<0 || p1->one.chin_score >100)
		{
			printf("语文成绩输入不合法，请重新输入:");
			scanf("%f", &p1->one.chin_score);
		}
		if (p1->one.math_score<0 || p1->one.math_score >100)
		{
			printf("数学成绩输入不合法，请重新输入:");
			scanf("%f", &p1->one.math_score);
		}
		if (p1->one.engl_score<0 || p1->one.engl_score >100)
		{
			printf("英语成绩输入不合法，请重新输入:");
			scanf("%f", &p1->one.engl_score);
		}
		if (p1->one.chem_score<0 || p1->one.chem_score >100)
		{
			printf("化学成绩输入不合法，请重新输入:");
			scanf("%f", &p1->one.chem_score);
		}
		if (p1->one.phy_score<0 || p1->one.phy_score >100)
		{
			printf("物理成绩输入不合法，请重新输入:");
			scanf("%f", &p1->one.phy_score);
		}
		if (p1->one.chin_score >= 0 && p1->one.chin_score <= 100 && p1->one.math_score >= 0 
			&& p1->one.math_score <= 100&& p1->one.engl_score >= 0 && p1->one.engl_score <= 100 
			&& p1->one.chem_score >= 0 && p1->one.chem_score <= 100
			&& p1->one.phy_score >= 0 && p1->one.phy_score <= 100)
		{
			break;
		}
	}
	p1->one.sum_score = (double)(p1->one.chin_score + p1->one.chin_score + p1->one.engl_score +
		p1->one.chem_score + p1->one.phy_score);
	p1->one.aver_score = p1->one.sum_score / 5;
}
