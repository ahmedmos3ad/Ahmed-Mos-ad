#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char month[20];
    int day;
    int year;
} date;
typedef struct
{
    char title[50];
    char author[50];
    char publisher[50];
    date D;
    int copies;
    int currentCopies;
    char category[10];
} books;
typedef struct
{
    char firstname[20];
    char lastname[20];
    int ID;
    char adress[200];
    int phone;
    int age;
    char email[100];
} members;
struct borrow
{
    members buser;
    books bbook;
    date due;
    date borrowed;
    date returned;
};

books book[100];
members member[100];
struct borrow borrows[100];
int counter=0;
int ID=0;
void loadbooks()
{
    FILE *ptrB;
    ptrB=fopen("Books.txt","r");
    if (ptrB==NULL)
        printf("Error:File not found!\a");
    else
    {
        while(!feof(ptrB))
        {
            fscanf(ptrB,"%[^,]%*c",book[counter].title);
            fscanf(ptrB,"%[^,]%*c",book[counter].author);
            fscanf(ptrB,"%[^,]%*c",book[counter].publisher);
            fscanf(ptrB,"%d,%[^,]%*c%d,",&book[counter].D.year,book[counter].D.month,&book[counter].D.day);
            fscanf(ptrB,"%[^,]%*c",book[counter].category);
            fscanf(ptrB,"%d,",&book[counter].copies);
            fscanf(ptrB,"%d",&book[counter].currentCopies);
            fscanf(ptrB,"\n");
            counter++;


        }
        fclose(ptrB);
        int i=0;
        printf("Book title\tAuthor   \tPublisher\tDate     Category     Copies    C.Copies\n");
        while (i<counter)
        {
            printf("%s\t%s\t%s\t%d,%s,%d  %s  %d  %d\n",book[i].title,book[i].author,book[i].publisher,
                   book[i].D.year,book[i].D.month,book[i].D.day,book[i].category,book[i].copies,book[i].currentCopies);
            i++;
        }
    }
}

void loadmembers()
{
    ID++;
    FILE *ptrM;
    ptrM=fopen("Members.txt","r");
    if (ptrM==NULL)
        printf("Error:File not found!\a");
    else
    {
        while(!feof(ptrM))
        {
            fscanf(ptrM,"%[^,]%*c",member[counter].firstname);
            fscanf(ptrM,"%[^,]%*c",member[counter].lastname);
            fscanf(ptrM,"%d,",&member[counter].ID);
            fscanf(ptrM,"%[^,]%*c",member[counter].adress);
            fscanf(ptrM,"%d,",&member[counter].phone);
            fscanf(ptrM,"%d,",&member[counter].age);
            fscanf(ptrM,"%[^,]%*c",member[counter].email);
            fscanf(ptrM,"\n");
            counter++;
        }
        fclose(ptrM);
        int i;
        printf("Name   \tID\tAdress     Phone    Age  E-mail\n");
        while (i<counter)
        {
            printf("%s %s\t%d\t%s\t%d\t%d\t%s\n",member[i].firstname,member[i].lastname,member[i].ID,member[i].adress,member[i].phone,member[i].age,member[i].email);
            i++;
        }
    }
}
void addbook(int c)
{
    FILE *ptrB;
    ptrB=fopen("Books.txt","a");
    int flag=1;
    while(flag==1 && counter<1000)
    {
        printf("Input Book Title>");
        fflush(stdin);
        gets(book[c].title);
        printf("Input Author>");
        fflush(stdin);
        gets(book[c].author);
        printf("Publisher>");
        gets(book[c].publisher);
        printf("Input Date of Publishing>\n");
        int year=0;
        while (year<1 || year>2025)
        {
            printf("Input Year>");
            fflush(stdin);
            scanf("%d",&year);
        }
        book[c].D.year=year;
        int n=0;
        while (n<1 || n>12)
        {
            printf("Input Month (IN NUMBERS)>");
            fflush(stdin);
            scanf("%d",&n);
        }
        switch (n)
        {
        case 1:
            strcpy(book[c].D.month,"January");
            break;
        case 2:
            strcpy(book[c].D.month,"February");
            break;
        case 3:
            strcpy(book[c].D.month,"March");
            break;
        case 4:
            strcpy(book[c].D.month,"April");
            break;
        case 5:
            strcpy(book[c].D.month,"May");
            break;
        case 6:
            strcpy(book[c].D.month,"June");
            break;
        case 7:
            strcpy(book[c].D.month,"July");
            break;
        case 8:
            strcpy(book[c].D.month,"August");
            break;
        case 9:
            strcpy(book[c].D.month,"September");
            break;
        case 10:
            strcpy(book[c].D.month,"October");
            break;
        case 11:
            strcpy(book[c].D.month,"November");
            break;
        case 12:
            strcpy(book[c].D.month,"December");
            break;
        default:
            continue;
        }
        book[c].D.day=0;
        while (book[c].D.day<1 || book[c].D.day>31)
        {
            printf("Input Day>");
            scanf("%d",&book[c].D.day);
        }
        printf("Input Category>");
        fflush(stdin);
        gets(book[c].category);
        printf("Input number of copies>");
        fflush(stdin);
        scanf("%d",&book[c].copies);
        printf("Input number of current copies>");
        fflush(stdin);
        scanf("%d",&book[c].currentCopies);
        counter++;
        printf("\n\nAnother Book? (yes->1,no->0)");
        scanf("%d",&flag);

    }
    if (counter==1000)printf("\nMemory Full! \a\n");

}
void searchbook()
{
    int i=0;
    FILE *ptrB;
    ptrB=fopen("Books.txt","r");
    char find[50],capital_letter;
    int found_book_counter=0;
    printf("\nInput any information about the book you want to find>");
    getchar();
    scanf("%[^\n]",find);
    while(!feof(ptrB))
    {
        fscanf(ptrB,"%[^,]%*c",book[counter].title);
        fscanf(ptrB,"%[^,]%*c",book[counter].author);
        fscanf(ptrB,"%[^,]%*c",book[counter].publisher);
        fscanf(ptrB,"%d,%[^,]%*c%d,",&book[counter].D.year,book[counter].D.month,&book[counter].D.day);
        fscanf(ptrB,"%[^,]%*c",book[counter].category);
        fscanf(ptrB,"%d,",&book[counter].copies);
        fscanf(ptrB,"%d",&book[counter].currentCopies);
        fscanf(ptrB,"\n");
        counter++;
    }
    fclose(ptrB);
    while(i<counter)
    {
        if ((strcasecmp(book[i].title,find)==0)||(strcasecmp(book[i].author,find)==0)||(strcasecmp(book[i].publisher,find)==0))
            {
                printf("\n\nTitle:%s\nAuthor:%s\nPublisher:%s\nRelease Date: %d,%s,%d\nCategory:%s\nCopies:%d\nCurrent Copies:%d\n\n",book[i].title,book[i].author,book[i].publisher,
                       book[i].D.year,book[i].D.month,book[i].D.day,book[i].category,book[i].copies,book[i].currentCopies);
                found_book_counter++;
            }
        i++;
    }
    if (found_book_counter==0)
        printf("\n\nError! Book not found\a\n");
}
void deletebook()
{
    printf("Are you sure you want to delete a Book?(1-Yes,2-No)");
    int choice;
    scanf("%d",&choice);
    if (choice==1)
    {
        int a;
        searchbook();
        strcpy(book[a].title,"\0");
        strcpy(book[a].author,"\0");
        strcpy(book[a].publisher,"\0");
        book[a].D.day=-1;
        strcpy(book[a].D.month,"\0");
        book[a].D.year=-1;
        strcpy(book[a].category,"\0");
        int start;
        for(start=a; start<counter-1; start++)
            book[start]=book[start+1];

        counter--;
    }
}
void save()
{
    int i;
    FILE *ptrB;
    ptrB=fopen("Books.txt","a");
    if (ptrB==NULL)
    {
        printf("Error: File not found!\a");
        exit(1);
    }
    else
    {
        for(i=0; i<counter; i++)

        {
            fprintf(ptrB,"%s,%s,%s,%d,%s,%d,%s,%d,%d\n",book[i].title,book[i].author,book[i].publisher,
                    &book[i].D.year,book[i].D.month,&book[i].D.day,book[i].category,book[i].copies,book[i].currentCopies);

        }
        fclose(ptrB);
        printf("\n\nChanges Saved Successfully\n\n");
    }
}

void addmember(int c)
{
    FILE *ptrU;
    ptrU=fopen("Members.txt","r");
    members m;
    int flag=1;
    while(flag==1 && counter<1000)
    {
        printf("Input First Name>");
        fflush(stdin);
        gets(member[c].firstname);
        printf("Input Last Name>");
        fflush(stdin);
        gets(member[c].lastname);
        printf("ID>");
        scanf("%d",&member[c].ID);
        printf("Input Category>");
        fflush(stdin);
        gets(member[c].adress);
        printf("Phone>");
        fflush(stdin);
        scanf("%d",&member[c].phone);
        printf("Age>");
        fflush(stdin);
        scanf("%d",&member[c].age);
        printf("Email>");
        fflush(stdin);
        gets(member[c].email);
        fprintf(ptrU,"%s %s,%d,%s,%d,%d,%s\n",member[c].firstname,member[c].lastname,member[c].ID,member[c].adress,member[c].phone,member[c].age,member[c].email);
        m=member[counter];
        printf("\n\nAnother user? (yes->1,no->0)");
        scanf("%d",&flag);

    }
    if (counter==1000)printf("\nMemory Full! \a\n");
}

int searchmember()
{
    FILE *ptrM;
    ptrM=fopen("Members.txt","r");
    char find[50];
    int found_member_counter=0;
    int i;
    printf("\nInput any information about the member you want to find>");
    getchar();
    scanf("%[^\n]",find);
    while(!feof(ptrM))
        {
            fscanf(ptrM,"%[^,]%*c",member[counter].firstname);
            fscanf(ptrM,"%[^,]%*c",member[counter].lastname);
            fscanf(ptrM,"%d,",&member[counter].ID);
            fscanf(ptrM,"%[^,]%*c",member[counter].adress);
            fscanf(ptrM,"%d,",&member[counter].phone);
            fscanf(ptrM,"%d,",&member[counter].age);
            fscanf(ptrM,"%[^,]%*c",member[counter].email);
            fscanf(ptrM,"\n");
            counter++;
        }
        fclose(ptrM);
    while (i<counter)
    {
        if (strcasecmp(member[i].ID,find)==0 || strcasecmp(member[i].firstname,find)==0 || strcasecmp(member[i].lastname,find)==0 || strcasecmp(member[i].email,find)==0)
        {
            printf("\n\nName\tAdress\tPhone\tAge Email",member[i].firstname,member[i].lastname,member[i].ID,member[i].adress,member[i].phone,member[i].age,member[i].email);
            found_member_counter++;
        }
    }
    if (found_member_counter==0)
        printf("\n\nError! Member not found\a\n");
    return i;
}
void removemember()
{
    printf("Are you sure you want to remove a Member?(1-Yes,2-No)");
    int choice;
    scanf("%d",&choice);
    if (choice==1)
    {
        int a;
        searchmember(a);
        strcpy(member[a].firstname,"\0");
        strcpy(member[a].lastname,"\0");
        strcpy(member[a].ID,"\0");
        strcpy(member[a].adress,"\0");
        int start;
        for(start=a; start<counter-1; start++)
            book[start]=book[start+1];

        counter--;
    }
}



/*
void newcopy();
void borrowbook();
void returnbook();
void overdue();
void popular();
;*/



void main()
{
    counter=0;
    printf("Welcome to the Library Data Base!\n");
    int a=1,b=1,c=1,y,z,f=1;
    printf("Would you like to load full information?\n1-Yes.\n2-No.\n");
    scanf("%d",&a);
    if (a==1)
    {
        printf("Choose option please:\n1-Load all books.\n2-Look all members.\n");
        scanf("%d",&f);
        switch (f)
        {
        case 1:
            loadbooks();
            break;
        case 2:
            loadmembers();
            break;
        }
    }
    else
        while (a!=7)
        {
            printf("\n\nChoose option please:\n1-Book Management.\n2-Member Management.\n3-Borrow Management.\n4-Administrative actions.\n5-Exit.\n\n\n>>>");
            scanf("%d",&a);
            switch (a)
            {
            case 1:
            {
                printf("1-Add a new book.\n2-Search for a book.\n3-Add new copy.\n4-Delete book.\n");
                scanf("%d",&b);
                switch (b)
                {
                case 1:
                    addbook(counter);
                    break;
                case 2:
                    searchbook(counter);
                    break;
                /*case 3:
                 newcopy();
                     break;*/
                case 4:
                    deletebook();
                    break;
                }
                break;
            }
            case 2:
                printf("1-Register a new Member.\n2-Remove a Member.\n");
                scanf("%d",&b);
                switch (b)
                {
                case 1:
                    addmember(a);
                    break;
                case 2:
                    removemember();
                    break;
                }
                break;
            /*case 3:
                printf("1-Borrowing.\n2-Returning a book.\n");
                scanf("%d",&b);
                switch (b)
                {
                case 1:
                    borrowbook();
                    break;
                case 2:
                    returnbook()
                    break;
                 }break;
            case 4:
                printf("1-Overdue books.\n2-Most popular books");
                scanf("%d",&b);
                switch (b)
                {
                case 1:
                    overduebook();
                    break;
                case 2:
                    popularbook()
                    break;
            }break;*/
            case 5:
                printf("1-Save and Exit.\n2-Exit without saving.\n>>>");
                scanf("%d",&c);
                switch (c)
                {
                case 1:
                    save();
                    exit(1);
                    break;
                case 2:
                    exit(1);
                    break;
                }
            default:
                printf("Error: choice unavailable\a Try again.");

            }
        }
}

