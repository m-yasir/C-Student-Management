#include <string.h>
#include <conio.h>
#include <ctype.h>
#define mlim 50

/*
* Add function to update password
*/

// -------- FUNCTION DECLARATIONS------

void p_ch(char a, int b);
void menu(void);
void m_scr(void);
void fetch_record(void);
void add_record(void);
void delete_record(void);
void All_record(void);
void edit(void);
void reset_mfile(void);
void userCheck(char* username, char* password);
void getCredentials(void);

// ------------x-------------

const char accessUser[] = "admin";
const char accessPwd[] = "admin";

struct user{
	char* username;
	char* password;
};

struct course{
	char name[mlim];
	float marks;
};

struct student
{
	long int Rollno;
	char name[mlim];
	char fname[mlim];
	int Age;
	char gender[mlim];
	char phone[mlim];
	char cnic[mlim];
	struct course c;
}s;

void p_ch(char a, int b) {
	for(int i=1; i<=b; i++) {
		printf("%c", a);
	}
}

void m_scr(void) {
	printf("\t\t\t\t\t");
	p_ch('*',37);
	printf("\n\t\t\t\t\t");
	printf("WELCOME TO STUDENT MANAGEMENT SYSTEM!");
	printf("\n\t\t\t\t\t");
	p_ch('*',37);
	printf("\n\t\t\t\t\t\tDESIGNED BY CASUALDEVS");
	printf("\n\n");
}

void fetch_record(void) {
	m_scr();
	FILE *fp;
	fp = fopen("SMS_record.bin", "rb");
	if (fp == NULL) {
		printf("Records file doesn\'t exist! Press any key to go back to menu...\n");
		getch();
		fflush(stdin);
		menu();
	}
	int rn = 0;
	printf("Enter Roll no to search: ");
	fflush(stdin);
	scanf("%d", &rn);
	system("cls");
	m_scr();
	printf("Student\'s Details Are:\n\n");
	
	while(fread(&s,sizeof(s),1,fp) == 1)
	{ 
		if(s.Rollno == rn)
		{
			p_ch('*',42);
			printf("\n");
			printf("Roll number\t\t: %d\n\n", s.Rollno);
			printf("Student\'s Name\t\t: %s\n\n",s.name);
			printf("Father\'s Name\t\t: %s\n\n", s.fname);
			printf("Age of Student\t\t: %d\n\n",s.Age);
			printf("Gender of Student\t: %s\n\n",s.gender);
			printf("CNIC Number of Student\t: %s\n\n",s.cnic);
			printf("Course Name of Student\t: %s\n",s.c.name);
			printf("Marks of Course of Std\t: %.2f\n",s.c.marks);
			p_ch('*',42);
			printf("\n\n");
			break;
		}
		else
		{
			printf("\nError! No record found!\n");
		}
	}
		fclose(fp);
} 

void add_record(void) {
	char ch = '\0';
	long int i;
	char arn[mlim];
	do
	{
		system("cls");
		m_scr();
		i = 1;
		FILE *fp,*fpr;
		fpr = fopen("SMS_rollno.bin","rb");
		if(fgets(arn,mlim,fpr) == NULL)
		{
			i = 1;
		}
		else
		{
			fgets(arn,mlim,fpr);
			i = atoi(arn);
		}
		fclose(fpr);
		if(i==1)
		{
			fp = fopen("SMS_record.bin", "wb");
		}
		else
		{
			fp = fopen("SMS_record.bin","ab");
		}
		s.Rollno = i;
		printf("Enter Name: ");
		fflush(stdin);
		gets(s.name);
		printf("Enter Father's Name: ");
		fflush(stdin);
		gets(s.fname);
		printf("Enter Age: ");
		fflush(stdin);
		scanf("%d", &s.Age);
		printf("Enter Gender: ");
		fflush(stdin);
		gets(s.gender);
		printf("Enter CNIC\\B-Form Number(with \'-\'): ");
		fflush(stdin);
		gets(s.cnic);
		printf("Enter Phone Number: ");
		fflush(stdin);
		gets(s.phone);
		printf("Enter Course Name: ");
		fflush(stdin);
		gets(s.c.name);
		printf("Enter marks: ");
		s.c.marks = 0.0;
		fflush(stdin);
		scanf("%f",&s.c.marks);
		fwrite(&s,sizeof(s),1,fp);
		fclose(fp);
		i++;
		fpr = fopen("SMS_rollno.bin","wb");
		fprintf(fpr, "%d", i);
		fclose(fpr);
		printf("\nPress A to add more students!");
		ch = toupper(getch());
	}
	while(ch == 'A');
}

void delete_record(void) {
	char ch = '\0';
	int rn;
	do
	{
		rn = 0;
		m_scr();
		printf("Enter Roll no. of student to delete\t: ");
		fflush(stdin);
		scanf("%d", &rn);
		if(rn == 0)
		{
			printf("\t\t\t\tInvalid Input!\n");
			getch();
			break;
		}
		FILE *fp, *fp2;
		fp = fopen("SMS_record.bin", "rb");
		if (fp == NULL) {
			printf("The File doesn\'t exist...");
			fclose(fp);
			break;
		}
		fp2 = fopen("temp.bin", "wb");
		while(fread(&s,sizeof(s),1,fp) == 1)
		{
			if(s.Rollno == rn)
			{
				system("cls");
				m_scr();
				printf("The Record has been Deleted Successfully!");
			}
			else
			{
				fwrite(&s,sizeof(s),1,fp2);
			}
		}
		fclose(fp);	
		fclose(fp2);
		remove("SMS_record.bin");
		rename("temp.bin","SMS_record.bin");
		printf("Press D to delete more records! or Any other key to continue!");
		ch = getch();
	}
	while(ch == 'D');
}

void All_record(void) {
	m_scr();
	FILE *fp = fopen("SMS_record.bin", "rb");
	int i = 1;
	if(fp == NULL)
	{
		system("cls");
		m_scr();
		printf("ERROR! No Record File EXISTS!!");
		printf("\nPress Any key to go back to menu...");
		getch();
		menu();
	}
	else
	{
		while(fread(&s,sizeof(s),1,fp) == 1)
		{
			p_ch('*',42);
			printf("\n");
			printf("\t\t\tStudent Number %d\n\n",i);
			printf("Roll number\t\t: %d\n\n", s.Rollno);
			printf("Student\'s Name\t\t: %s\n\n",s.name);
			printf("Father\'s Name\t\t: %s\n\n", s.fname);
			printf("Age of Student\t\t: %d\n\n",s.Age);
			printf("Gender of Student\t: %s\n\n",s.gender);
			printf("CNIC Number of Student\t: %s\n\n",s.cnic);
			printf("Tel Number of Student\t: %s\n\n",s.phone);
			printf("Course of the Student\t: %s\n\n",s.c.name);
			printf("Marks of the course\t: %.2f\n\n",s.c.marks);
			p_ch('*',42);
			printf("\n\n");
			i++;
		}
	}
	i = 1;
	fclose(fp);
}

void edit(void) {
	char ch = '\0';
	int rn = 0;
	FILE *fp, *fp2;
	do
	{
		system("cls");
		m_scr();
		printf("Enter Roll no of the student to modify: ");
		fflush(stdin);
		scanf("%d", &rn);
		if(rn == 0)
		{
			printf("Error! Invalid Roll no!");
			break;
		}
		fp = fopen("SMS_record.bin", "rb");
		fp2 = fopen("temp.bin", "wb");
		if(fp == NULL)
		{
			printf("Error! The file does not exists!");
			fclose(fp);
			fclose(fp2);
			remove("temp.bin");
			break;	
		}
		else
		{
			while(fread(&s,sizeof(s),1,fp) == 1)
			{
				if(s.Rollno == rn)
				{
					printf("\t\t\t\tOLD RECORD:\n\n");
					printf("Name\t\t: %s\n\n", s.name);
					printf("Father\'s Name\t: %s\n\n", s.fname);
					printf("Age\t\t: %d\n\n", s.Age);
					printf("Gender\t: %s\n\n", s.gender);
					printf("CNIC\t\t: %s\n\n", s.cnic);
					printf("Phone Number\t: %s\n\n\n", s.phone);
					printf("Course Name\t: %s\n\n\n", s.c.name);
					printf("Marks of Course\t: %.2f\n\n\n", s.c.marks);
					printf("Enter New name of the student: ");
					fflush(stdin);
					gets(s.name);
					printf("\nEnter new Father's Name: ");
					fflush(stdin);
					gets(s.fname);
					printf("\nEnter new Age: ");
					fflush(stdin);
					scanf("%d", &s.Age);
					printf("\nEnter new Gender: ");
					fflush(stdin);
					gets(s.gender);
					printf("\nEnter CNIC\\B-Form Number(with \'-\'): ");
					fflush(stdin);
					gets(s.cnic);
					printf("\nEnter new Phone Number: ");
					fflush(stdin);
					gets(s.phone);
					printf("\nEnter new Course Name: ");
					fflush(stdin);
					gets(s.c.name);
					printf("\nEnter new marks of the course: ");
					s.c.marks=0;
					fflush(stdin);
					scanf("%f", &s.c.marks);
				}
				fwrite(&s,sizeof(s),1,fp2);
			}
			printf("\nRecord Modified Successfully!");
			fclose(fp);
			fclose(fp2);
			remove("SMS_record.bin");
			rename("temp.bin","SMS_record.bin");
		}
		printf("\nPress E to modify more records or any other key to return to Main Menu: ");
		ch = toupper(getch());
		printf("\n");
	}
	while(ch == 'E');
}

void reset_mfile(void) {
	system("cls");
	m_scr();
	remove("SMS_record.bin");
	remove("SMS_rollno.bin");
	p_ch('\t',5);
	p_ch('*',30);
	printf("\n");
	p_ch('\t',5);
	printf("  Files Deleted Successfully!\n");
	p_ch('\t',5);
	p_ch('*',30);
}

void menu(void) {
	char ch = '\0';	
	do
	{
		system("cls");
		m_scr();
		p_ch('\t',5);
		p_ch('*',32);
		printf("\n");
		p_ch('\t',5);
		printf("1. Add a Record\n");
		p_ch('\t',5);
		printf("2. View all Record\n");
		p_ch('\t',5);
		printf("3. Search a Record\n");
		p_ch('\t',5);
		printf("4. Delete a Record\n");
		p_ch('\t',5);
		printf("5. Delete Rollno and record files\n");
		p_ch('\t',5);
		printf("6. Edit Record\n");
		p_ch('\t',5);
		printf("7. Exit\n");
		p_ch('\t',5);
		p_ch('*',32);
		printf("\nEnter What you want to do: ");		
		fflush(stdin);
		ch = getch();
		switch(ch)
		{
			case '1':
				system("cls");
				add_record();
				break;
			case '2':
				system("cls");
				All_record();
				break;
			case '3':
				system("cls");
				fetch_record();
				break;
			case '4':
				system("cls");
				delete_record();
				break;
			case '5':
				system("cls");
				reset_mfile();
				break;
			case '6':
				system("cls");
				edit();
				break;
			case '7':
				system("cls");
				m_scr();
				p_ch('\t',5);
				printf("The Program has exited successfully!!");
				exit(0);
				break;
			default:
				system("cls");
				m_scr();
				p_ch('\t',5);
				p_ch('*',30);
				printf("\n\n");
				p_ch('\t',6);
				printf("INVALID INPUT!!\n");
				p_ch('\t',6);
				printf("PLEASE TRY AGAIN!\n\n");
				p_ch('\t',5);
				p_ch('*',30);
				break;
		}
		printf("\nPress any key to return to Main Menu or Q to exit!");
		ch = toupper(getch());
	}
	while(ch != 'Q');
}

void userCheck(char* username, char* password) {
	if (!strcmp(username, accessUser) && !strcmp(password, accessPwd)) {
		menu();
	}
}

void getCredentials(void) {
	m_scr();
	char* username = calloc(mlim, sizeof(char));
	char* password = calloc(mlim, sizeof(char));
	fflush(stdin);
	printf("Enter Username: ");
	gets(username);
	printf("Enter Password: ");
	char ch = '\0';
	int i = 0;
	while (i < mlim || ch != ' ' && ch != '\n' && ch != '\r') {
		ch = getch();
		if (ch != ' ' && ch != '\n' && ch != '\0' && ch != '\b' && ch != '\r') {
			*(password + i) = ch;
			putchar('*');
			i++;
			fflush(stdin);
			continue;
		} else if (ch == '\b' && i != 0) {
			putchar('\b');
			putchar('\0');
			putchar('\b');
			*(password + i) = '\0';
			--i;
		} else if (ch == '\b' && i == 0){
			continue;
		} else {
			break;
		}
	}
	userCheck(username, password);
}
