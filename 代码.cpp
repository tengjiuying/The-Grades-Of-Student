#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>//������ͨ������̨���������������������ĺ�������Ҫ��һЩ�û�ͨ�������̲����Ķ�Ӧ����������getch()������
#include <windows.h>//system()����Ҫ��Windows�²���
#include <ctype.h>//������һ��C�����ַ����ຯ�������ڲ����ַ��Ƿ������ض����ַ��������ĸ�ַ��������ַ��ȵ�
//�籾�γ������õ���isprint������isprint�������ܣ����ch�Ƿ��ǿɴ�ӡ�ַ�(�����ո�),��ASCII����0x20��0x7E֮��
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
}StudentDate;//ѧ��������Ϣ

typedef struct student
{
	char name[20];//ѧ������
	StudentDate one;//ѧ��������Ϣ
	int rank;//�ɼ�����
	struct student *next;
}Student, *List;

Student *startCheck(void);//��ʼ��顢���庯�����˺�������һ��ָ������ͷ��ָ��*/
Student *createListHead(void);//���������ͷ

void menu(void);//���˵�

void sortList(Student *pHead);//��������

void readListWithFile(Student *pHead, char *file_name);//���ļ��ж�ȡ���ݣ���������������

void sorttList(Student *pHead);//��������

int userChioce(Student *pHead);//�û�ѡ��

int sortMenu(void);//��ӡѡ��˵�

void passwordCheck(void);//������

void correctWord(void);//�޸�����

void addStudentInfo(Student *pHead);//�������ĩβ�������

int scanMenu(void);//����˵�

void findStudentInfo(Student *pHead);//����ѧ����Ϣ

void delStudentInfo(Student *pHead);//ɾ��ĳһ��ѧ����Ϣ

void alterStudentInfo(Student *pHead);//�޸�ѧ����Ϣ

void saveList(Student *pHead);//�����������ļ���

void printList(Student *pHead);//��ӡ����

void statisStudentInfo(Student *pHead);//�鿴ѧ����Ϣ

int statisMenu(void);//�鿴�˵�

void gotoxy(int x, int y);//�ı���λ�ú���/*gotoxy��x��y��������ƶ���ָ����y����x*/

void inputData(Student *pHead, Student *node);//������Ϣ��������Ƿ�Ϸ�

int main(void)
{
	Student *pHead;
	
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//�õ����ھ��
	SMALL_RECT rc = { 0, 0, 94 - 1, 30 - 1 };   //{Yλ��,Xλ��,��,��}
	SetConsoleWindowInfo(hOut, true, &rc);// ���ô���λ�úʹ�С

	system("color 37");//���ÿ���̨��ɫ
	pHead = startCheck();//��ȡ��Ϣ
	
	while (1)
	{
		if (9 == userChioce(pHead)) //��9ʱ�˳�ϵͳ
		{
			break;
		}
	}

	return 0;
}

void menu(void)
{
	system("CLS");//����
	printf("\n\n\n\t\t\t\t��������������������������������������\n");
	printf("\t\t\t\t��         ѧ���ɼ�ͳ��ϵͳ         ��\n");
	printf("\t\t\t\t��������������������������������������\n");
	printf("\t\t\t\t��         1   ����ѧ����¼         ��\n");
	printf("\t\t\t\t��������������������������������������\n");
	printf("\t\t\t\t��         2   ɾ��ѧ����¼         ��\n");
	printf("\t\t\t\t��������������������������������������\n");
	printf("\t\t\t\t��         3   �޸�ѧ����¼         ��\n");
	printf("\t\t\t\t��������������������������������������\n");
	printf("\t\t\t\t��         4   ����ѧ����Ϣ         ��\n");
	printf("\t\t\t\t��������������������������������������\n");
	printf("\t\t\t\t��         5   ͳ��ѧ���ɼ�         ��\n");
	printf("\t\t\t\t��������������������������������������\n");
	printf("\t\t\t\t��         6   �鿴ѧ���ɼ�         ��\n");
	printf("\t\t\t\t��������������������������������������\n");
	printf("\t\t\t\t��         7   �޸ĵ�½����         ��\n");
	printf("\t\t\t\t��������������������������������������\n");
	printf("\t\t\t\t��         8      ����              ��\n");
	printf("\t\t\t\t��������������������������������������\n");
	printf("\t\t\t\t��         9    �˳�ϵͳ            ��\n");
	printf("\t\t\t\t��������������������������������������\n");
}

void gotoxy(int x, int y)//xΪ������,yΪ������
{
	COORD pos = { x, y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	/*GetStdHandle�������ر�׼�����롢����������豸�ľ����Ҳ���ǻ�����롢���/�������Ļ�������ľ��*/
	SetConsoleCursorPosition(hOut, pos);
}

Student *startCheck(void)
{
	Student *pHead;
	FILE  *fp1;
	char password[20] = "123456";
	int i;

	if ((fp1 = fopen("password.dat", "rb")) == NULL)//��Ϊ���������ݴ�һ���������ļ����������ļ������ڣ��½������ļ�
	{
		fp1 = fopen("password.dat", "wb");//Ϊ��������ݴ�һ���������ļ�����fopen�����ķ���ֵ����ָ�����fp
		fwrite(password, 20, 1, fp1);
		fclose(fp1);
		printf("�����ʼ����ɣ���Ĭ������Ϊ��123456��");
		passwordCheck();
	}
	else
	{
		passwordCheck();
	}
	//����
	system("CLS");
	system("title ѧ���ɼ�ͳ��ϵͳ-������");//������������Ϊ��ѧ���ɼ�ͳ��ϵͳ��
	printf("\n\n\t\t\t��ӭ���뱾ϵͳ����������.....");
	printf("\n\n\n\n\t\t\t������������������������\n");
	printf("\t\t\t��                    ��\n");
	printf("\t\t\t������������������������\n");
	gotoxy(26, 7);
	for ( i = 0; i < 10; i++)
	{
		printf("��");
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

	fp = fopen(file_name, "r");//Ϊ���������ݴ�һ���Ѵ��ڵ��ı��ļ���ֻ��
	if (fp == NULL)
	{
		fp = fopen(file_name, "w");//Ϊ��������ݣ���һ���ı��ļ���ֻд
		fclose(fp);
		return;
	}
	fseek(fp, 0L, 2);/*fseek()�����ƶ��ļ����Ķ�дλ��,fseek(�ļ�����ָ��fp��λ��������ʼ��)*/
	count = ftell(fp);/*ʹ��ftell��ȡ��Ŀǰ��д��λ��*/
	/*��Ҫ��fseek��ftell������������ø����ܹ�ȷ���ļ���ǰ��λ��*/
	p1 = pHead;
	fp = fopen(file_name, "r");
	while (!feof(fp))
	{
		p2 = (List)malloc(sizeof(Student));
		fscanf(fp, "%d%s %c%f%f%f%f%f\n", &p2->one.num, p2->name, &p2->one.sex, &p2->one.chin_score,
			&p2->one.math_score, &p2->one.engl_score, &p2->one.chem_score, &p2->one.phy_score);/*��fscanf�����Ӵ����ļ��϶���ASCII�ַ�*/
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
	//���������򣬲���ʼ������
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

void sortList(Student *pHead)//��������
{
	Student *p1, *p2;
	StudentDate dat;
	char stu_name[20];
	int bum, count = 0, rank;

	system("title ѧ���ɼ�ͳ��ϵͳ-�鿴");//������������Ϊ��ѧ���ɼ�ͳ��ϵͳ��
	bum = sortMenu();
	if (bum == 1)//��ƽ���ָߵ�����
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
		if (bum == 2)//��ѧ�Ÿߵ�����
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

void printList(Student *pHead)//��ӡ����
{
	int count = 0;
	pHead = pHead->next;
	system("CLS");
	printf("\t\t\t\t�ƿ�3��ɼ���");
	printf("\n\n  ���������ש��������ש����ש������ש������ש������ש������ש������ש������ש������ש�����");
	printf("\n  �� ѧ�� �� �� ��  ���Ա���  �ĩ���  ѧ��Ӣ  �逸��  ѧ����  ��ƽ���֩���  �֩����Ω�\n");
	while (pHead)
	{ 
		printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
		printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", pHead->one.num,
			pHead->name, pHead->one.sex, pHead->one.chin_score, pHead->one.math_score,
			pHead->one.engl_score, pHead->one.chem_score
			, pHead->one.phy_score, pHead->one.aver_score, pHead->one.sum_score, pHead->rank);
		pHead = pHead->next;
		count++;
	}
		printf("  ���������ߩ��������ߩ����ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ�����\n");
	printf("\t\t\t�ð�һ��%d����!", count);
	getch();
}

int userChioce(Student *pHead)
{
	int bum;

	system("title ѧ���ɼ�ͳ��ϵͳ-���˵�");//������������Ϊ��ѧ���ɼ�ͳ��ϵͳ��
	menu();
	printf("�밴��ѡ��: ");
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
		MessageBox(NULL, TEXT("���ԣ�����ϵͳ���������룬�����޸����룻չʾѧ����Ϣʱ���Ա��ķ�ʽ���֣�����ѧ����Ϣʱ�����������Ѵ��ڵ�ѧ�ţ��������ļ�Ϊ����������:TengFeng"), TEXT("����"), MB_OK);
		break; 
	default:
		break;
	}

	return bum;
}

int sortMenu(void)//��ӡѡ��˵�
{
	int bum;

	system("CLS");
	printf("\n\n\n");
	printf("\t\t��������������������������������������������������������������\n");
	printf("\t\t��                       ��ʲô��ʽ��ѯ ��                  ��\n");
	printf("\t\t�ǩ�����������������������������������������������������������\n");
	printf("\t\t��                    1   ���ɼ��ĸߵ�                      ��\n");
	printf("\t\t�ǩ�����������������������������������������������������������\n");
	printf("\t\t��                    2   ��ѧ�ŵ�����                      ��\n");
	printf("\t\t�ǩ�����������������������������������������������������������\n");
	printf("\t\t��                    3   �������˵�                        ��\n");
	printf("\t\t��������������������������������������������������������������\n");
	printf("�밴��ѡ��");
	bum = (int)(getch() - '0');
	system("CLS");

	return bum;
}

void passwordCheck(void)
{
	char password[20], inputword[20];
	int i = 0, j = 0;
	char c = 0;//��Ϊ'\0'��ASCll��Ϊ0,����char c=0��char c='\0'��һ���ģ�����\0���ڲ�����ʾ�ַ������Բ��õ�����д��
	/*���ַ�������ASCll�����*/
	FILE *fp = fopen("password.dat", "rb");

	system("title ѧ���ɼ�ͳ��ϵͳ-��������");//������������Ϊ��ѧ���ɼ�ͳ��ϵͳ��
	fread(password, 20, 1, fp);//���������fp��ָ����ļ�����1��20���ֽڵ����ݣ��洢������password��
	for (i = 0; i < 5; i++)
	{
		j = 0;
		printf("\n\n\n\t\t�㻹��%d�λ���������ȷ����: ", 3-i);
		printf("\n\n\n\n\t\t\t��������������������\n");
		printf("\t\t\t��                ��\n");
		printf("\t\t\t��������������������\n");
		gotoxy(26, 8);/*gotoxy��x��y��������ƶ���ָ����y����x*/
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
				if (isprint(c))//isprint()����Ϊ���C�Ƿ�Ϊ�ɴ�ӡ�ĺ��� 
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
			printf("\t\t\t�����������");
		}
	}
	if (5 == i)
	{
		system("CLS");
		printf("\n\n\n\t\t�����˷����л��ᣡ���򼴽��˳���");
		Sleep(2000);
		exit(0);
	}
	fclose(fp);
	system("CLS");

	return;
}

void correctWord(void)//�޸�����
{
	char password[20];
	FILE *fp;
	int i = 0;
	char c;

	system("title ѧ���ɼ�ͳ��ϵͳ-�޸�����");//������������Ϊ��ѧ���ɼ�ͳ��ϵͳ��
	system("CLS");
	printf("\n\n\n\n\t\t\t�������µ����룺");

	while ((c = getch()) != 13 && i < 20)
	//��13����Ӧ���ַ���CR,���س�����˼,�������ڲ�׽�û���û�е���س���.���û��,��ô���һ����*���ַ�,
	//Ȼ��Ѹող�׽�����ַ���ֵ��password�����һ��Ԫ��,֮����ֵָ������һ����λ.
	//��κ�������˼�ǲ�׽�û�����ļ������ݵ�ASCII��ֵ,�Ի�ȡ�س���Ϊ��������ѭ����������־. 
	{
		if (c == '\b'&&i > 0)
		{
			putchar('\b');/*\b�˸��*/
			putchar(' ');
			putchar('\b');
			i--;
		}
		else
		{
			if (isprint(c))//isprintΪ���C�Ƿ�Ϊ�ɴ�ӡ�ĺ��� 
			{
				putchar('*');
				password[i] = c;
				i++;
			}
		}
	}
	password[i] = '\0';
	printf("\n\t\t\t�Ƿ������޸�Ϊ<%s>? Y or N:", password);
	c = getch();
	if (c == 'Y' || c == 'y')
	{
		fp = fopen("password.dat", "wb");
		fwrite(password, 20, 1, fp);//���ļ�дһ�����ݿ�
		fclose(fp);
		printf("\n\t\t\t�޸ĳɹ���\n");
	}
	else
	{
		return;
	}
	getch();
}

void addStudentInfo(Student *pHead)//������ĩβ�������
{
	FILE *fp;
	Student *p1, *p2, *p3 = pHead;
	StudentDate dat;
	int judge = YES, rank = 0;
	char bum, stu_name[20];

	system("title ѧ���ɼ�ͳ��ϵͳ-���");//������������Ϊ��ѧ���ɼ�ͳ��ϵͳ��
	fp = fopen("stud.dat", "a");/*���ļ������ı��ļ��������*/
	while (pHead->next)
	{
		pHead = pHead->next;
	}
	while (judge)
	{


		p1 = (List)malloc(sizeof(Student));
		inputData(p3, p1);
		p1->next = NULL;
		pHead->next = p1;//��p1��ָ�Ľ�����ӵ���β
		pHead = p1;//pHead�Ƶ���β
		fprintf(fp, "%d %s %c %.1f %.1f %.1f %.1f %.1f\n", p1->one.num, p1->name, p1->one.sex, p1->one.chin_score,
			p1->one.math_score, p1->one.engl_score, p1->one.chem_score, p1->one.phy_score);
		printf("�Ƿ������ӣ�(Y/N)");
		bum = getch();
		if (bum == 'n' || bum == 'N')
		{
			break;
		}
		
	}
	//���������������򣬰�ƽ���ִӴ�С����
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
	printf("\t\t��������������������������������������������������������������\n");
	printf("\t\t��                       ��ʲô��ʽ��ѯ ��                  ��\n");
	printf("\t\t�ǩ�����������������������������������������������������������\n");
	printf("\t\t��                    1   ��ѧ����ѧ��                      ��\n");
	printf("\t\t�ǩ�����������������������������������������������������������\n");
	printf("\t\t��                    2   ��ѧ��������                      ��\n");
	printf("\t\t�ǩ�����������������������������������������������������������\n");
	printf("\t\t��                    3   �������˵�                        ��\n");
	printf("\t\t��������������������������������������������������������������\n");
	printf("�밴��ѡ��");
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
	system("title ѧ���ɼ�ͳ��ϵͳ-����");//������������Ϊ��ѧ���ɼ�ͳ��ϵͳ��
	bum = scanMenu();
	if (bum == 1)
	{
		printf("������ѧ����ѧ�ţ�");
		scanf("%d", &num);
		while (pHead)
		{
			if (pHead->one.num == num)
			{
				if (count == 0)
				{
					printf("\n\t\t\t�Ѿ��鵽��\n");
					printf("\n\n\n\n  ���������ש��������ש����ש������ש������ש������ש������ש������ש������ש������ש�����");
					printf("\n  �� ѧ�� �� �� ��  ���Ա���  �ĩ���  ѧ��Ӣ  �逸��  ѧ����  ��ƽ���֩���  �֩����Ω�\n");
					count = 1;
				}
				printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
				printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", pHead->one.num,
					pHead->name, pHead->one.sex, pHead->one.chin_score, pHead->one.math_score,
					pHead->one.engl_score, pHead->one.chem_score
					, pHead->one.phy_score, pHead->one.aver_score, pHead->one.sum_score, pHead->rank);
				break;
			}
			pHead = pHead->next;
		}
		if (pHead == NULL)
		{
			printf("\n\t\t\tû�и�ѧ����¼��\n");
		}
		else
		{
			printf("  ���������ߩ��������ߩ����ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ�����\n");
		}
	}
	else
	{
		if (bum == 2)
		{
			printf("������ѧ��������");
			scanf("%s", student_name);
			while (pHead)
			{
				if (strcmp(student_name, pHead->name) == 0)
				{
					if (count == 0)
					{
						printf("\n\t\t\t�Ѿ��鵽��\n");
						printf("\n\n\n\n  ���������ש��������ש����ש������ש������ש������ש������ש������ש������ש������ש�����");
						printf("\n  �� ѧ�� �� �� ��  ���Ա���  �ĩ���  ѧ��Ӣ  �逸��  ѧ����  ��ƽ���֩���  �֩����Ω�\n");
						count = 1;
					}
					printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
					printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", pHead->one.num,
						pHead->name, pHead->one.sex, pHead->one.chin_score, pHead->one.math_score,
						pHead->one.engl_score, pHead->one.chem_score
						, pHead->one.phy_score, pHead->one.aver_score, pHead->one.sum_score, pHead->rank);
				}
				pHead = pHead->next;
			}
			if (count == 0)
			{
				printf("\n\t\t\tû�и�ѧ����¼��");
			}
			else
			{
				printf("  ���������ߩ��������ߩ����ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ�����\n");
			}
		}
		else
		{
			if (bum == 3)
			{
				return;/*����������*/
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

	system("title ѧ���ɼ�ͳ��ϵͳ-ɾ��");//������������Ϊ��ѧ���ɼ�ͳ��ϵͳ��
	bum = scanMenu();
	if (bum == 1)
	{
		p1 = pHead->next;
		printf("\n\t\t\t������Ҫɾ��ѧ����ѧ�ţ�");
		scanf("%d", &num);
		while (p1)
		{
			if (p1->one.num == num)
			{
				count = 1;/*ѧ�Ŵ��ھ���count=1��ʾ�������ھ�����count������0�������ѧ�Ų����ڡ�*/
				printf("\n\t\t\tɾ���ɹ���ɾ����ѧ��ѧ��Ϊ��%d", num);
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
			printf("\n\t\t\t������Ҫɾ����ѧ��������");
			scanf("%s", student_name);
			//ͳ��һ���ж��ٸ�ѧ��
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
				printf("'\n\n\n\t\t\tһ����%d���˵���Ϣ ȫ��ɾ��(Y) or ��һɾ��(N)?", count);//ѡ��ȫ��ɾ����������һɾ��
				c = getch();
				//ȫ��ɾ��
				if (c == 'y' || c == 'Y')
				{
					p1 = pHead->next;
					while (p1)
					{
						if (strcmp(p1->name, student_name) == 0)
						{
							printf("\n\t\t\tɾ���ɹ�������Ϊ: %s", student_name);
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
					//��һɾ��
					p1 = pHead->next;
					while (p1)
					{
						if (strcmp(p1->name,student_name) == 0)
						{
							printf("\n����:%s,ѧ��:%d,�Ա�:%c  �Ƿ�ɾ��(y or n)?", p1->name, p1->one.num, p1->one.sex);
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
								printf("�ɹ���");
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
		printf("\n\t\t\tû�и�ѧ����Ϣ��");
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
	
	fp = fopen("stud.dat", "w+");/*Ϊ�˶���д����һ�����ļ�*/
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

	system("title ѧ���ɼ�ͳ��ϵͳ-�޸�");//������������Ϊ��ѧ���ɼ�ͳ��ϵͳ��
	bum = scanMenu();
	if (bum == 1)
	{
		printf("\n\t\t\t������Ҫ�޸�ѧ����ѧ�ţ�");
		scanf("%d", &num);
		while (p1)
		{
			j++;//ͳ��ѧ������
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
			printf("û�и�ѧ����Ϣ��");
		}
	}
	else
	{
		if (bum == 2)
		{
			printf("\n\t\t\t������Ҫ�޸�ѧ����������");
			scanf("%s", student_name);
			while (p1)
			{
				j++;
				if (strcmp(p1->name, student_name) == 0)
				{
					inputData(pHead, p1);
					count = 1;/*�����ж�����������Ƿ����*/
				}
				p1 = p1->next;
			}
			if (count == 0)
			{
				printf("\n\t\t\tû�и�ѧ����Ϣ��");
				getch();/*����������*/
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

	system("title ѧ���ɼ�ͳ��ϵͳ-ͳ��");//������������Ϊ��ѧ���ɼ�ͳ��ϵͳ��
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
		printf("\n\n  ����������������������������������������������������������������������������������������\n");
		printf("  ��\t\t\t���ĵ�ƽ����Ϊ:%.1f��û�дﵽ�ﵽƽ���ֵ�ѧ����                 ��\n", aver_score[0]);
		printf("  �ǩ������ש��������ש����ש������ש������ש������ש������ש������ש������ש������ש�����\n");
		printf("  �� ѧ�� �� �� ��  ���Ա���  �ĩ���  ѧ��Ӣ  �逸��  ѧ����  ��ƽ���֩���  �֩����Ω�\n");
		printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
		while (p1)
		{
			if (p1->one.chin_score < aver_score[0])
			{
				if (bad == 0)
				{
					printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
						p1->one.engl_score, p1->one.chem_score
						, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				else
				{
					printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
					printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
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
		printf("  �ǩ������ߩ��������ߩ����ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ�����\n");
		printf("  ��\t\t\t��ѧ��ƽ����Ϊ:%.1f��û�дﵽ�ﵽƽ���ֵ�ѧ����                 ��\n", aver_score[1]);
		printf("  �ǩ������ש��������ש����ש������ש������ש������ש������ש������ש������ש������ש�����\n");
		printf("  �� ѧ�� �� �� ��  ���Ա���  �ĩ���  ѧ��Ӣ  �逸��  ѧ����  ��ƽ���֩���  �֩����Ω�\n");
		printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
		while (p1)
		{
			if (p1->one.math_score < aver_score[1])
			{
				if (bad == 0)
				{
					printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
						p1->one.engl_score, p1->one.chem_score
						, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				else
				{
					printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
					printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
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
		printf("  �ǩ������ߩ��������ߩ����ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ�����\n");
		printf("  ��\t\t\tӢ���ƽ����Ϊ:%.1f��û�дﵽ�ﵽƽ���ֵ�ѧ����                 ��\n", aver_score[2]);
		printf("  �ǩ������ש��������ש����ש������ש������ש������ש������ש������ש������ש������ש�����\n");
		printf("  �� ѧ�� �� �� ��  ���Ա���  �ĩ���  ѧ��Ӣ  �逸��  ѧ����  ��ƽ���֩���  �֩����Ω�\n");
		printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
		while (p1)
		{
			if (p1->one.engl_score < aver_score[2])
			{
				if (bad == 0)
				{
					printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
						p1->one.engl_score, p1->one.chem_score
						, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				else
				{
					printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
					printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
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
		printf("  �ǩ������ߩ��������ߩ����ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ�����\n");
		printf("  ��\t\t\t��ѧ��ƽ����Ϊ:%.1f��û�дﵽ�ﵽƽ���ֵ�ѧ����                 ��\n", aver_score[3]);
		printf("  �ǩ������ש��������ש����ש������ש������ש������ש������ש������ש������ש������ש�����\n");
		printf("  �� ѧ�� �� �� ��  ���Ա���  �ĩ���  ѧ��Ӣ  �逸��  ѧ����  ��ƽ���֩���  �֩����Ω�\n");
		printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
		while (p1)
		{
			if (p1->one.chem_score < aver_score[3])
			{
				if (bad == 0)
				{
					printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
						p1->one.engl_score, p1->one.chem_score
						, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				else
				{
					printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
					printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
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
		printf("  �ǩ������ߩ��������ߩ����ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ�����\n");
		printf("  ��\t\t\t�����ƽ����Ϊ:%.1f��û�дﵽ�ﵽƽ���ֵ�ѧ����                 ��\n", aver_score[4]);
		printf("  �ǩ������ש��������ש����ש������ש������ש������ש������ש������ש������ש������ש�����\n");
		printf("  �� ѧ�� �� �� ��  ���Ա���  �ĩ���  ѧ��Ӣ  �逸��  ѧ����  ��ƽ���֩���  �֩����Ω�\n");
		printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
		while (p1)
		{
			if (p1->one.phy_score < aver_score[4])
			{
				if (bad == 0)
				{
					printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
						p1->one.engl_score, p1->one.chem_score
						, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				else
				{
					printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
					printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
						p1->one.engl_score, p1->one.chem_score
						, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				bad = 1;
			}
			p1 = p1->next;
		}
		printf("  ���������ߩ��������ߩ����ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ�����\n");
		printf("\t\t\t\t\t\t�ð�һ��%d����!", count);
	}
	else
	{
		if (bum == 2)
		{
			bad = 0;
			printf("\n\n  ����������������������������������������������������������������������������������������\n");
			printf("  ��\t\t\t\t���ĳɼ�����90�ֻ�С��60��ѧ����                        ��\n");
			printf("  �ǩ������ש��������ש����ש������ש������ש������ש������ש������ש������ש������ש�����\n");
			printf("  �� ѧ�� �� �� ��  ���Ա���  �ĩ���  ѧ��Ӣ  �逸��  ѧ����  ��ƽ���֩���  �֩����Ω�\n");
			printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
			p1 = pHead->next;
			while (p1)
			{
				if (p1->one.chin_score < 60 || p1->one.chin_score >= 90)
				{
					if (bad == 0)
					{
						printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
							p1->one.engl_score, p1->one.chem_score
							, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					else
					{
						printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
						printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
							p1->one.engl_score, p1->one.chem_score
							, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					bad = 1;
				}
				p1 = p1->next;
			}
			bad = 0;
			printf("  �ǩ������ߩ��������ߩ����ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ�����\n");
			printf("  ��\t\t\t\t��ѧ�ɼ�����90�ֻ�С��60��ѧ����                        ��\n");
			printf("  �ǩ������ש��������ש����ש������ש������ש������ש������ש������ש������ש������ש�����\n");
			printf("  �� ѧ�� �� �� ��  ���Ա���  �ĩ���  ѧ��Ӣ  �逸��  ѧ����  ��ƽ���֩���  �֩����Ω�\n");
			printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
			p1 = pHead->next;
			while (p1)
			{
				if (p1->one.math_score < 60 || p1->one.math_score >= 90)
				{
					if (bad == 0)
					{
						printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
							p1->one.engl_score, p1->one.chem_score
							, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					else
					{
						printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
						printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
							p1->one.engl_score, p1->one.chem_score
							, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					bad = 1;
				}
				p1 = p1->next;
			}
			bad = 0;
			printf("  �ǩ������ߩ��������ߩ����ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ�����\n");
			printf("  ��\t\t\t\tӢ��ɼ�����90�ֻ�С��60��ѧ����                        ��\n");
			printf("  �ǩ������ש��������ש����ש������ש������ש������ש������ש������ש������ש������ש�����\n");
			printf("  �� ѧ�� �� �� ��  ���Ա���  �ĩ���  ѧ��Ӣ  �逸��  ѧ����  ��ƽ���֩���  �֩����Ω�\n");
			printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
			p1 = pHead->next;
			while (p1)
			{
				if (p1->one.engl_score < 60 || p1->one.engl_score >= 90)
				{
					if (bad == 0)
					{
						printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
							p1->one.engl_score, p1->one.chem_score
							, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					else
					{
						printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
						printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
							p1->one.engl_score, p1->one.chem_score
							, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					bad = 1;
				}
				p1 = p1->next;
			}
			bad = 0;
			printf("  �ǩ������ߩ��������ߩ����ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ�����\n");
			printf("  ��\t\t\t\t��ѧ�ɼ�����90�ֻ�С��60��ѧ����                        ��\n");
			printf("  �ǩ������ש��������ש����ש������ש������ש������ש������ש������ש������ש������ש�����\n");
			printf("  �� ѧ�� �� �� ��  ���Ա���  �ĩ���  ѧ��Ӣ  �逸��  ѧ����  ��ƽ���֩���  �֩����Ω�\n");
			printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
			p1 = pHead->next;
			while (p1)
			{
				if (p1->one.chem_score < 60 || p1->one.chem_score >= 90)
				{
					if (bad == 0)
					{
						printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
							p1->one.engl_score, p1->one.chem_score
							, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					else
					{
						printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
						printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
							p1->one.engl_score, p1->one.chem_score
							, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					bad = 1;
				}
				p1 = p1->next;
			}
			bad = 0;
			printf("  �ǩ������ߩ��������ߩ����ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ�����\n");
			printf("  ��\t\t\t\t����ɼ�����90�ֻ�С��60��ѧ����                        ��\n");
			printf("  �ǩ������ש��������ש����ש������ש������ש������ש������ש������ש������ש������ש�����\n");
			printf("  �� ѧ�� �� �� ��  ���Ա���  �ĩ���  ѧ��Ӣ  �逸��  ѧ����  ��ƽ���֩���  �֩����Ω�\n");
			printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
			p1 = pHead->next;
			while (p1)
			{
				if (p1->one.phy_score < 60 || p1->one.phy_score >= 90)
				{
					if (bad == 0)
					{
						printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
							p1->one.engl_score, p1->one.chem_score
							, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					else
					{
						printf("  �ǩ������贈�������贈���贈�����贈�����贈�����贈�����贈�����贈�����贈�����贈����\n");
						printf("  �� %-5d�� %-6s ��  %c ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f ��%5.1f �� %-3d��\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.chin_score, p1->one.math_score,
							p1->one.engl_score, p1->one.chem_score
							, p1->one.phy_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					bad = 1;
				}
				p1 = p1->next;
			}
			printf("  ���������ߩ��������ߩ����ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ������ߩ�����\n");
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
	printf("\t\t��������������������������������������������������������������\n");
	printf("\t\t��                   ��ʲô��ʽͳ��ѧ����Ϣ��               ��\n");
	printf("\t\t�ǩ�����������������������������������������������������������\n");
	printf("\t\t��                      1   ��ƽ����                        ��\n");
	printf("\t\t�ǩ�����������������������������������������������������������\n");
	printf("\t\t��                      2   ���Ƿ�ϸ�                      ��\n");
	printf("\t\t�ǩ�����������������������������������������������������������\n");
	printf("\t\t��                      3   �������˵�                      ��\n");
	printf("\t\t��������������������������������������������������������������\n");
	printf("�밴��ѡ��");
	bum = (int)(getch() - '0');
	system("CLS");

	return bum;
}

void inputData(Student *pHead, Student *node)
{
	Student *p1 = node, *p2, *p3 = pHead;
	
	system("CLS");
	printf("\n\n\t����������ѧ����ѧ�š��������Ա����ġ���ѧ��Ӣ���ѧ������ɼ�\n");
	printf("\tע��:���������пո��Ա�����M��ʾ��ŮӶW��ʾ��\n\t���Ƴɼ�Ӧ�ô���0С��100����������ʱ���ÿո����\n");
	scanf("%d%s %c%f%f%f%f%f", &p1->one.num, p1->name, &p1->one.sex, &p1->one.chin_score, &p1->one.math_score,
		&p1->one.engl_score, &p1->one.chem_score, &p1->one.phy_score);
	// �ж������ѧ���Ƿ��Ѿ�����
	p2 = p3->next;
	while (1)
	{
		if (p2 == NULL)
		{
			break;
		}
		if (p2->one.num == p1->one.num && p2 != node)
		{
			printf("��ѧ���Ѵ��ڣ�����������ѧ��:");
			scanf("%d", &p1->one.num);
			p2 = p3->next;
		}
		else
		{
			p2 = p2->next;
		}
	}
	//�Ա��Ƿ�Ϸ�
	while (1)
	{
		if (p1->one.sex != 'W'&& p1->one.sex != 'M')
		{
			p1->one.sex = getchar();
			printf("�Ա����벻�Ϸ�������������: ");
			p1->one.sex = getchar();
			
		}
		else
		{
			break;
		}
	}
	//�ɼ��Ƿ�Ϸ�
	while (1)
	{
		if (p1->one.chin_score<0 || p1->one.chin_score >100)
		{
			printf("���ĳɼ����벻�Ϸ�������������:");
			scanf("%f", &p1->one.chin_score);
		}
		if (p1->one.math_score<0 || p1->one.math_score >100)
		{
			printf("��ѧ�ɼ����벻�Ϸ�������������:");
			scanf("%f", &p1->one.math_score);
		}
		if (p1->one.engl_score<0 || p1->one.engl_score >100)
		{
			printf("Ӣ��ɼ����벻�Ϸ�������������:");
			scanf("%f", &p1->one.engl_score);
		}
		if (p1->one.chem_score<0 || p1->one.chem_score >100)
		{
			printf("��ѧ�ɼ����벻�Ϸ�������������:");
			scanf("%f", &p1->one.chem_score);
		}
		if (p1->one.phy_score<0 || p1->one.phy_score >100)
		{
			printf("����ɼ����벻�Ϸ�������������:");
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
