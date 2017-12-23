#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int day;
    int month;
    int year;
} date;
typedef struct
{
    char title[50];
    char author[50];
    char publisher[50];
    date D;
    char ISBN[15];
    int copies;
    int currentCopies;
    char category[10];
    int del;
    int rank;
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
    int borrowcount;
    int del;
} members;
typedef struct
{
    char ISBN[15];
    int ID;
    date borrowed;
    date due;
    date returned;
    int del;
} borrows;

books book[100];
members member[100];
borrows borrow[100];
int bookcounter=0,membercounter=0,borrowcounter=0;
int ID;

void scanbooks()
{
    FILE *ptrB;
    ptrB=fopen("Books.txt","r");
    while(!feof(ptrB))
    {
        fscanf(ptrB,"%[^,],",book[bookcounter].title);
        fscanf(ptrB,"%[^,],",book[bookcounter].author);
        fscanf(ptrB,"%[^,],",book[bookcounter].publisher);
        fscanf(ptrB,"%d,%d,%d,",&book[bookcounter].D.day,&book[bookcounter].D.month,&book[bookcounter].D.year);
        fscanf(ptrB,"%[^,],",&book[bookcounter].ISBN);
        fscanf(ptrB,"%[^,],",book[bookcounter].category);
        fscanf(ptrB,"%d,",&book[bookcounter].copies);
        fscanf(ptrB,"%d,",&book[bookcounter].currentCopies);
        fscanf(ptrB,"%[^\n]");
        book[bookcounter].del=0;
        bookcounter++;
    }
    fclose(ptrB);
}

void scanmembers()
{
    FILE *ptrM;
    ptrM=fopen("Members.txt","r");
    while(!feof(ptrM))
    {
        fscanf(ptrM,"%[^,],",member[membercounter].firstname);
        fscanf(ptrM,"%[^,],",member[membercounter].lastname);
        fscanf(ptrM,"%d,",&member[membercounter].ID);
        fscanf(ptrM,"%[^,],",member[membercounter].adress);
        fscanf(ptrM,"%d,",&member[membercounter].phone);
        fscanf(ptrM,"%d,",&member[membercounter].age);
        fscanf(ptrM,"%[^,],",member[membercounter].email);
        fscanf(ptrM,"%d,",&member[membercounter].borrowcount);
        fscanf(ptrM,"%[^\n]");
        membercounter++;
        member[membercounter].del=0;
    }
    fclose(ptrM);
}

void scanborrows()
{
    FILE *ptrBB;
    ptrBB=fopen("Borrows.txt","r");
    while(!feof(ptrBB))
    {
        fscanf(ptrBB,"%[^,]%*c%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%[^\n]",borrow[borrowcounter].ISBN,&borrow[borrowcounter].ID,
               &borrow[borrowcounter].borrowed.day,&borrow[borrowcounter].borrowed.month,&borrow[borrowcounter].borrowed.year,
               &borrow[borrowcounter].due.day,&borrow[borrowcounter].due.month,&borrow[borrowcounter].due.year,
               &borrow[borrowcounter].returned.day,&borrow[borrowcounter].returned.month,&borrow[borrowcounter].returned.year);
        borrowcounter++;
        borrow[borrowcounter].del=0;
    }
    fclose(ptrBB);
}

void scanfiles()
{
    void scanbooks();
    void scanborrows();
    void scanmembers();
}



void loadbooks()
{
    int i=0;
    FILE *ptrB;
    ptrB=fopen("Books.txt","r");
    if (ptrB==NULL)
        printf("Error:File not found!\a");
    else
    {
        printf("Book title\tAuthor   \tPublisher\tDate      ISBN      Category     Copies    C.Copies\n");
        while (i<bookcounter)
        {
            printf("%s\t%s\t%s\t%d/%d/%d  %s      %s  %d  %d",book[i].title,book[i].author,book[i].publisher,
                   book[i].D.day,book[i].D.month,book[i].D.year,book[i].ISBN,book[i].category,book[i].copies,book[i].currentCopies);
            i++;
        }
    }
}

void loadmembers()
{
    FILE *ptrM;
    ptrM=fopen("Members.txt","r");
    if (ptrM==NULL)
        printf("Error:File not found!\a");
    else
    {
        int i=0;
        printf("Name   \tID\tAdress     Phone    Age  E-mail    Borrowed-Books");
        while (i<membercounter)
        {
            printf("%s %s\t %d \t %s \t 0%d \t %d \t %s  %d\n",member[i].firstname,member[i].lastname,
                   member[i].ID,member[i].adress,member[i].phone,member[i].age,member[i].email,member[i].borrowcount);
            i++;
        }
    }
}

void loadborrows()
{   int i=0;
    FILE *ptrBB;
    ptrBB=fopen("Borrows.txt","r");
    if (ptrBB==NULL)
        printf("Error:File not found!\a");
    else
    printf("ISBN   \tID\tDATE BORROWED    DATE DUE    DATE RETURNED\n");
    while (i<borrowcounter)
    {
        printf("%s---%d---%d/%d/%d---%d/%d/%d---%d/%d/%d",borrow[i].ISBN,borrow[i].ID,
               borrow[i].borrowed.day,borrow[i].borrowed.month,borrow[i].borrowed.year,
               borrow[i].due.day,borrow[i].due.month,borrow[i].due.year,
               borrow[i].returned.day,borrow[i].returned.month,borrow[i].returned.year);
        i++;
    }
}

void addbook(int c)
{
    int d,y,m;
    int flag=1;
    while(flag==1 && bookcounter<1000)
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
        book[c].D.day=0;
        while (d<1 || d>31)
        {
            printf("Input Day>");
            scanf("%d",&d);
        }
        book[c].D.day=d;
        while (m<1 || m>12)
        {
            printf("Input Month(IN NUMBERS)>");
            fflush(stdin);
            scanf("%d",&m);
        }
        book[c].D.month=m;
        while (y<1 || y>2025)
        {
            printf("Input Year>");
            fflush(stdin);
            scanf("%d",&y);
        }
        book[c].D.year=y;
        printf("Input ISBN>");
        fflush(stdin);
        gets(book[c].ISBN);
        printf("Input Category>");
        fflush(stdin);
        gets(book[c].category);
        printf("Input number of copies>");
        fflush(stdin);
        scanf("%d",&book[c].copies);
        printf("Input number of current copies>");
        fflush(stdin);
        scanf("%d",&book[c].currentCopies);
        book[bookcounter].del=0;
        bookcounter++;
        printf("\n\nAnother Book? (yes->1,no->0)");
        scanf("%d",&flag);

    }
    if (bookcounter==1000)printf("\nMemory Full! \a\n");

}
void searchbook()
{
    int i=0;
    FILE *ptrB;
    ptrB=fopen("Books.txt","r");
    char find[50];
    int found_book_counter=0;
    printf("\nInput any information about the book you want to find>");
    getchar();
    scanf("%[^\n]",find);
    while(i<bookcounter)
    {
        if ((strcasecmp(book[i].title,find)==0)||(strcasecmp(book[i].author,find)==0)
                ||(strcasecmp(book[i].publisher,find)==0)||(strcasecmp(book[i].ISBN,find)==0))
        {
            printf("\n\nTitle:%s\nAuthor:%s\nPublisher:%s\nRelease Date: %d,%d,%d\nISBN:%s\nCategory:%s\nCopies:%d\nCurrent Copies:%d\n\n",book[i].title,book[i].author,book[i].publisher,
                   book[i].D.day,book[i].D.month,book[i].D.year,book[i].ISBN,book[i].category,book[i].copies,book[i].currentCopies);
            found_book_counter++;
        }
        i++;
    }
    if (found_book_counter==0)
        printf("\n\nError! Book not found\a\n");
}
void deletebook()
{
    printf("Are you sure you want to delete a Book?(1-Yes,2-No)>");
    int choice;
    int flag=1;
    char c;
    int temp=0;
    FILE *ptrB;
    scanf("%d",&choice);
    if (choice==1)
    {
        while (flag==1)
        {
            int i=0;
            ptrB=fopen("Books.txt","r");
            char find[50];
            int found_book_counter=0;
            printf("\nInput any information about the book you want to find>");
            getchar();
            scanf("%[^\n]",find);
            scanbooks();
            while(i<bookcounter)
            {
                if ((strcasecmp(book[i].title,find)==0)||(strcasecmp(book[i].author,find)==0)||(strcasecmp(book[i].publisher,find)==0))
                {
                    printf("\n\nTitle:%s\nAuthor:%s\nPublisher:%s\nRelease Date: %d,%d,%d\nISBN:%s\nCategory:%s\nCopies:%d\nCurrent Copies:%d\n\n",book[i].title,book[i].author,book[i].publisher,
                           book[i].D.year,book[i].D.month,book[i].D.day,book[i].ISBN,book[i].category,book[i].copies,book[i].currentCopies);
                    found_book_counter++;
                    book[i].del=1;
                }
                i++;
            }
            if (found_book_counter==0)
                printf("\n\nError! Book not found\a\n");
            printf("Delete another book?(1-Yes,2-No)>");
            scanf("%d",&flag);
        }
    }
}

void removeemptylinesbooks()
{
    FILE *fp2;
    FILE *ptrB;
    ptrB=fopen("Books.txt","r");
    char line[300];
    char x[]="blank.txt";
    fp2=fopen(x,"w");
    while (!feof(ptrB))
    {
        fgets(line,300, ptrB);
        if (strcmp(line, "\n") == 0)
        {
            continue;
        }
        fputs(line, ptrB);
        strcpy(line,"\0");
    }
    fclose(ptrB);
    fclose(fp2);
    fclose(x);
    remove("Books.txt");
    rename(x,"Books.txt");
}


void borrowbook()
{
    int flag=1,found_member_counter=0;
    int i=0;
    char find[50];
    FILE *ptrBB,*ptrM,*ptrB;
    ptrBB=fopen("Borrows.txt","a");
    ptrM=fopen("Members.txt","r");
    ptrB=fopen("Books.txt","r");
    time_t my_time;
    struct tm * timeinfo;
    time (&my_time);
    timeinfo = localtime (&my_time);
    timeinfo->tm_year+1900;
    timeinfo->tm_mon+1;
    timeinfo->tm_mday;

    printf("Input member ID>");
    scanf("%d",&member[i].borrowcount);
    while(flag==1)
    {
        scanmembers();
        if (member[i].borrowcount==3)
            printf("Number of borrows exceeded, please return a book first then try again.\n");
        else
        {
            int i=0;
            FILE *ptrB;
            ptrB=fopen("Books.txt","r");
            char find[50];
            int found_book_counter=0;
            printf("\nInput the book ISBN you want to borrow>");
            getchar();
            scanf("%[^\n]",find);
            scanbooks();
            while(i<bookcounter)
            {
                if ((strcasecmp(book[i].ISBN,find)==0))
                {
                    printf("\n\nTitle:%s\nAuthor:%s\nPublisher:%s\nRelease Date: %d,%d,%d\nISBN:%s\nCategory:%s\nCopies:%d\nCurrent Copies:%d\n\n",book[i].title,book[i].author,book[i].publisher,
                           book[i].D.day,book[i].D.month,book[i].D.year,book[i].ISBN,book[i].category,book[i].copies,book[i].currentCopies);
                    found_book_counter++;
                }
                i++;
            }
            if (found_book_counter==0)
                printf("\n\nError! Book not found\a\n");

            if (book[i].currentCopies=0)
                printf("No current copies available, Please try again later!\n");
            else
                book[i].currentCopies=book[i].currentCopies-1;
            borrow[i].returned.day=timeinfo->tm_mday;
            borrow[i].returned.year=timeinfo->tm_year+1900;
            borrow[i].returned.month=timeinfo->tm_mon+1;
            borrow[i].due.day=timeinfo->tm_mday+5;
            borrow[i].due.year=timeinfo->tm_year+1900;
            borrow[i].due.month=timeinfo->tm_mon+1;
            borrow[i].due.day=0;
            borrow[i].due.year=0;
            borrow[i].due.month=0;
            member[i].borrowcount++;

            if(borrow[i].due.day>31)
            {
                borrow[i].due.day-31;
                borrow[i].due.month++;

            }
            if(borrow[i].due.month>12)
            {
                borrow[i].due.month-12;
                borrow[i].due.year++;
            }

        }
        printf("Borrow Another book?\n1-Yes.\n2-No.\n");
        scanf("%d",&flag);
    }
}


void removemember()
{
    printf("Are you sure you want to remove a Member?(1-Yes,2-No)");
    FILE *ptrM;
    int choice,flag=1;
    scanf("%d",&choice);
    if (choice==1)
    {
        while (flag==1)
        {
            int i=0;
            ptrM=fopen("Members.txt","r");
            int find;
            int found_member_counter=0;
            printf("\nInput The ID of the Member you want to delete>");
            scanf("%d",&find);
            while(i<membercounter)
            {
                if (member[i].ID==find)
                {
                    printf("Name:%s %s\nID:%d\nAdress:%s\nPhone Number:0%d\nAge:%d\nEmail:%s\n",member[i].firstname,member[i].lastname,member[i].ID,member[i].adress,member[i].phone,member[i].age,member[i].email);
                    found_member_counter++;
                    member[i].del=1;
                }
                i++;
            }
            if (found_member_counter==0)
                printf("\n\nError! Member not found\a\n");
            printf("Delete another Member?(1-Yes,2-No)>");
            scanf("%d",&flag);
        }
    }
}


void savebook()
{
    int i;
    FILE *ptrB;
    ptrB=fopen("Books.txt","w");
    if (ptrB==NULL)
    {
        printf("Error: File not found!\a");
        exit(1);
    }
    else
    {
        for(i=0; i<bookcounter; i++)
        {
            if (book[i].del!=1)
                fprintf(ptrB,"%s,%s,%s,%d,%d,%d,%s,%d,%d",book[i].title,book[i].author,book[i].publisher,
                        &book[i].D.day,book[i].D.month,&book[i].D.year,book[i].category,book[i].copies,book[i].currentCopies);

        }
    }
    fclose(ptrB);
    printf("\n\nChanges Saved Successfully\n\n");
}
void savemember()
{
    int i;
    FILE *ptrM,*ptrMN;
    ptrM=fopen("Members.txt","r");
    ptrMN=fopen("Membersnew.txt","a");
    scanmembers();
    if (ptrM==NULL)
    {
        printf("Error: File not found!\a");
        exit(1);
    }
    else
    {
        for(i=3; i<membercounter; i++)
        {
            if (member[i].del==0)
            {
                fprintf(ptrMN,"%s %s,%d,%s,0%d,%d,%s",member[i].firstname,member[i].lastname,member[i].ID,member[i].adress,member[i].phone,member[i].age,member[i].email,member[i].borrowcount);
            }
        }
        rewind(ptrMN);
        fclose(ptrM);
        fclose(ptrMN);
        remove("Members.txt");
        rename("Membersnew.txt","Members.txt");

    }
}
void saveborrow()
{
    int i;
    FILE *ptrBorrow,*ptrBorrowN;
    ptrBorrow=fopen("Borrows.txt","r");
    ptrBorrowN=fopen("Borrownew.txt","a");
    if (ptrBorrow==NULL)
    {
        printf("Error: File not found!\a");
        exit(1);
    }
    else
    {
        for(i=5; i<borrowcounter; i++)
        {
            if (borrow[i].del==0)
            {
                fprintf(ptrBorrowN,"%s,%d,%d/%d/%d,%d/%d/%d,%d/%d/%d",borrow[i].ISBN,borrow[i].ID,
                        borrow[i].borrowed.day,borrow[i].borrowed.month,borrow[i].borrowed.year,
                        borrow[i].due.day,borrow[i].due.month,borrow[i].due.year,
                        borrow[i].returned.day,borrow[i].returned.month,borrow[i].returned.year);
            }
        }
        rewind(ptrBorrowN);
        fclose(ptrBorrowN);
        fclose(ptrBorrow);
        remove("Borrows.txt");
        rename("Borrownew.txt","Borrows.txt");
    }
}
void save()
{
    savebook();
    savemember();
    saveborrow();
}

void addmember(int c)
{
    FILE *ptrU;
    ptrU=fopen("Members.txt","a");
    members m;
    int flag=1;
    while(flag==1 && membercounter<1000)
    {
        printf("Input First Name>");
        fflush(stdin);
        gets(member[c].firstname);
        printf("Input Last Name>");
        fflush(stdin);
        gets(member[c].lastname);
        printf("ID>");
        scanf("%d",&member[c].ID);
        printf("Input Address>");
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
        member[c].borrowcount=0;
        fprintf(ptrU,"\n%s,%s,%d,%s,%d,%d,%s,%d",member[c].firstname,member[c].lastname,member[c].ID,member[c].adress,member[c].phone,member[c].age,member[c].email,member[c].borrowcount);
        m=member[membercounter];
        printf("\n\nAnother user? (yes->1,no->0)");
        scanf("%d",&flag);

    }
    if (membercounter==1000)printf("\nMemory Full! \a\n");
}

void searchmember()
{
    int i=0;
    FILE *ptrM;
    ptrM=fopen("Members.txt","r");
    char find[50];
    int found_member_counter=0;
    printf("\nInput any information about the member you want to find>");
    getchar();
    scanf("%[^\n]",find);
    while (i<membercounter)
    {
        if ((strcasecmp(member[i].ID,find)==0) || (strcasecmp(member[i].firstname,find)==0) || (strcasecmp(member[i].lastname,find)==0) || (strcasecmp(member[i].email,find)==0))
        {
            printf("\n\nName:%s %s\nAdress:%s\nPhone:0%d\nAge:%d\nEmail:%s\n",member[i].firstname,member[i].lastname,member[i].ID,member[i].adress,member[i].phone,member[i].age,member[i].email);
            found_member_counter++;
        }
        i++;
    }
    if (found_member_counter==0)

        printf("\n\nError! Member not found\a\n");
}

void newcopy()
{
    int i=0,newcopies;
    FILE *ptrB;
    ptrB=fopen("Books.txt","a");
    char find[50];
    int found_book_counter=0;
    printf("\nInput any information about the book you want to find>>");
    getchar();
    scanf("%[^\n]",find);
    while(i<bookcounter)
    {
        if ((strcasecmp(book[i].title,find)==0)||(strcasecmp(book[i].author,find)==0)
                ||(strcasecmp(book[i].publisher,find)==0)||(strcasecmp(book[i].ISBN,find)==0))
        {
            printf("Enter the number of copies you want to add>>");
            scanf("%d",&newcopies);
            book[i].copies+=newcopies;
            book[i].currentCopies+=newcopies;
            found_book_counter++;
            printf("Copy/copies added successfully");
        }
        i++;
    }
    if (found_book_counter==0)
        printf("\n\nError! Book not found\a\n");
}
void returnbook()
{
    int i=0,findid;
    char find[50];
    int found_book_counter=0;
    int found_member_counter=0;
    printf("Enter member ID>");
    scanf("%d",&findid);
    printf("Enter the ISBN of the book you want to return> ");
    getchar();
    scanf("%[^\n]",find);
    for (i=0; i<membercounter; i++)
    {
        if (member[i].ID==findid)
        {
            member[i].borrowcount-=1;
            found_member_counter++;
        }
        if (found_member_counter!=0)
        {
            for (i=0; i<bookcounter; i++)
            {
                if ((strcasecmp(book[i].ISBN,find)==0))
                {
                    book[i].currentCopies+=1;
                    found_book_counter=1;
                }
            }
        }

        if (found_book_counter==0) printf("Wrong ISBN!");
        if (found_member_counter==0);
        printf("Wrong ID!");
    }
}
/*
void overdue();
void popular();
;*/



void main()
{
    bookcounter=0;
    membercounter=0;
    borrowcounter=0;
    scanbooks();
    scanmembers();
    scanborrows();
    printf("Welcome to the Library Data Base!\n");
    int a=1,b=1,c=1,y,z,f=1;
    printf("Would you like to load full information?\n1-Yes.\n2-No.\n");
    scanf("%d",&a);
    if (a==1)
    {
        printf("Choose option please:\n1-Load all books.\n2-Look all members.\n3-Load all borrowings.\n");
        scanf("%d",&f);
        switch (f)
        {
        case 1:
            loadbooks();
            break;
        case 2:
            loadmembers();
            break;
        case 3:
            loadborrows();
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
                    addbook(bookcounter);
                    break;
                case 2:
                    searchbook(bookcounter);
                    break;
                case 3:
                    newcopy();
                    break;
                case 4:
                    deletebook();
                    break;
                }
                break;
            }
            case 2:
                printf("1-Register a new Member.\n2-Remove a Member.\n3-Search a Member.\n");
                scanf("%d",&b);
                switch (b)
                {
                case 1:
                    addmember(a);
                    break;
                case 2:
                    removemember();
                    break;
                case 3:
                    searchmember();
                    break;
                }
                break;
            case 3:
                printf("1-Borrowing.\n2-Returning a book.\n");
                scanf("%d",&b);
                switch (b)
                {
                case 1:
                    borrowbook();
                    break;
                    /*case 2:
                        returnbook();
                        break;*/
                }
                break;

            /* case 4:
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
                    savebook();
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

