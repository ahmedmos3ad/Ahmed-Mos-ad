void query()
{
    char find[50];
    int i;
    int flag=0;
    printf("\nInput Book Title you want to find>");
    fflush(stdin);
    gets(find);
    for (i=0; i<counter; i++)
    {
        if (strcasecmp(book[i].title,find)==0)
        {
            printf("\n\nTitle:%s\nAuthor:%s\nPublisher:%s\nRelease Date: %d,%s,%d\nCategory:%s\nCopies:%d\nCurrent Copies:%d\n\n",book[i].title,book[i].author,book[i].publisher,
                   &book[i].D.year,book[i].D.month,&book[i].D.day,book[i].category,book[i].copies,book[i].currentCopies);
            flag=1;
        }
    }

    if (flag==0)
        printf("\n\nError! B not found\a\n");


}
