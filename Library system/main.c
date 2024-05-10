#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ininite loop sort
typedef struct
{
    char username [20];
    char password[20];
} username_password;

typedef struct
{
    int month;
    int year;
} date;

typedef struct
{
    char ISBN [20];
    char title [200];
    char author_name [100];
    int quantity;
    float price;
    date pub_date;
} book;

book b[100];
int count=0;

int log_in()
{

    char username[20], password[20];
    char j,flag=0,i=0;

    username_password x[10];

    FILE *f;
    f = fopen("credentials.txt","r");

    while (!feof(f))
    {
        fscanf(f,"%s\n%s",x[i].username,x[i].password);
        i++;
    }
    fclose(f);

    system("cls");

    printf("Please enter username : ");
    gets(username);
    printf("Please enter password : ");
    gets(password);

    for(j = 0 ; j < i ; j++)
    {
        if(strcmp(username,x[j].username) == 0 && strcmp(password,x[j].password) == 0)
        {
            flag=1;
            system("cls");
            printf("Welcome back sir!\n\n");
            printf("\n\n\n\n\n");
            printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
            printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
            printf("\n\t\t\t        =                 WELCOME                   =");
            printf("\n\t\t\t        =                   TO                      =");
            printf("\n\t\t\t        =                 LIBRARY                   =");
            printf("\n\t\t\t        =               MANAGEMENT                  =");
            printf("\n\t\t\t        =                 SYSTEM                    =");
            printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
            printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
            menu();
        }
    }

    if (!flag)
    {
        printf("\nUsername or password does not exist!\n\n");
        main();
    }
}


void load ()
{
    int i = 0, j;

    FILE *f;
    f = fopen("books.txt","r");

    while (!feof(f))
    {
        fscanf(f,"%[^,],%[^,],%[^,],%d,%f,%d-%d\n",b[count].ISBN,b[count].title,b[count].author_name,&b[count].quantity,&b[count].price,&b[count].pub_date.month,&b[count].pub_date.year);
        count++;
    }
    fclose(f);
    /*for(j=0;j<count;j++)
    {
        printf("%s,%s,%s,%d,%f,%d-%d\n",b[j].ISBN,b[j].title,b[j].author_name,b[j].quantity,b[j].price,b[j].pub_date.month,b[j].pub_date.year);
    }*/
}


void menu()
{
    while(1)
    {
        char request[20];
        printf("1-ADD\n2-DELETE\n3-MODIFY\n4-QUERY SEARCH\n5-ADVANCED SEARCH\n6-PRINT\n7-SAVE\n8-QUIT\n\n");
        gets(request);
        int sort_choice;

        if(strcmp(request,"1")==0)
            add();
        else if(strcmp(request,"2")==0)
            delete_book();
        else if(strcmp(request,"3")==0)
            modify();
        else if(strcmp(request,"4")==0)
            QUERY_search_book();
        else if(strcmp(request,"5")==0)
            ADVANCED_search_book();
        else if(strcmp(request,"6")==0)
        {
            printf("How you want to sort the books ?\n1-Sort by title\n2-Sort by date\n3-Sort by price\n");
            scanf("%d",&sort_choice);
            if(sort_choice==1)
            {
                sortbytitle();
                getchar();
            }
            else if(sort_choice==2)
            {
                sortbydate();
                getchar();
            }
            else if(sort_choice==3)
            {
                sortbyprice();
                getchar();
            }

        }
        else if(strcmp(request,"7")==0)
            save();
        else if(strcmp(request,"8")==0)
            quit();
        else
            menu();
    }
}


void quit()
{
    char x[5];
    printf("Are you sure you want to quit without saving ?\nPut Y if yes and N if no\n");

    gets(x);
    if(strcmp(x,"Y")==0 || strcmp(x,"y")==0)
    {
        exit(0);
    }
    else if(strcmp(x,"N")==0 || strcmp(x,"n")==0)
    {
        menu();
    }
    else
    {
        quit();
    }

}


void QUERY_search_book()
{
    int i=0;
    char targetisbn[20];

    printf("Enter the ISBN of the book: ");
    gets(targetisbn);
    while(i < count)
    {
        if(!strcmp(b[i].ISBN,targetisbn))
        {
            print_book_data(i);
            menu();
        }
        i++;
    }
    printf("The specified ISBN is not found\n");
}


void ADVANCED_search_book()
{
    int i,flag=0;
    char keyword[100];
    printf("Enter a keyword: ");
    gets(keyword);
    for(i=0; i<count; i++)
    {
        if(strstr(b[i].title,keyword)!=NULL)
        {
            print_book_data(i);
            flag = 1;
        }

    }
    if(flag == 0)
        printf("No matches are found.\n");
}


void delete_book()
{
    int i=0,pos=0;
    char deleteisbn[20];
    printf("Enter ISBN of the book want to be deleted: ");
    gets(deleteisbn);
    while(pos <= count)
    {
        if(!strcmp(b[pos].ISBN,deleteisbn))
        {
            for(i=pos; i<count-1; i++)
            {
                b[i] = b[i + 1];
            }
            count -= 1;
            printf("The book has been deleted successfully.\n\n");
            menu();

        }
        pos++;
    }
    printf("There is no book Associated with this ISBN.\n\n");
}


void sort_type()
{
    char sort_choice[11];

    system("cls");
    printf("How you want to sort the books ?\n\n1-Sort by title\n2-Sort by date\n3-Sort by price\n");
    gets(sort_choice);

    if(strcmp(sort_choice,"1") == 0)
    {
        sortbytitle();

    }
    else if(strcmp(sort_choice,"2") == 0)
    {
        sortbydate();

    }
    else if(strcmp(sort_choice,"3") == 0)
    {
        sortbyprice();

    }
    else
    {
        system("cls");
        printf("\nWrong input please try again!\n\n");
        menu();
    }
}


void sortbyprice()
{
    printf("\nSort by price :\n\n");

    book temp;
    int i, pass;

    for(pass = 1 ; pass < count ; pass++)
    {
        for(i = 0 ; i < count-1 ; i++)
        {
            if(b[i].price > b[i+1].price)
            {
                temp = b[i];
                b[i] = b[i+1];
                b[i+1] = temp;
            }
        }
    }

    for(i = 0 ; i < count ; i++)
        print_book_data(i);
}


void sortbydate()
{
    printf("\nSort by date :\n");
    book temp;
    int i,pass;
    for(pass=1; pass<count; pass++)

    {
        for(i=0; i<count-1; i++)
        {
            if(b[i].pub_date.year<b[i+1].pub_date.year)
            {
                temp=b[i];
                b[i]=b[i+1];
                b[i+1]=temp;
            }
            else if(b[i].pub_date.year==b[i+1].pub_date.year)
            {
                if(b[i].pub_date.month<b[i+1].pub_date.month)
                {
                    temp=b[i];
                    b[i]=b[i+1];
                    b[i+1]=temp;
                }
            }
        }
    }
    for(i=0; i<count; i++)
        print_book_data(i);
}


void sortbytitle()
{
    printf("\nSort by title :\n\n");

    book temp;
    int i,pass;
    for(pass=1; pass<count; pass++)

    {
        for(i=0; i<count-1; i++)//i=1
        {
            if(strcmp(b[i].title,b[i+1].title)>0)
            {
                temp=b[i];
                b[i]=b[i+1];
                b[i+1]=temp;
            }

        }
    }
    for(i=0; i<count; i++)
        print_book_data(i);

}


void save()
{
    int i;

    FILE *f;
    f = fopen("books.txt","w");

    for( i = 0 ; i < count ; i++)
    {
        fprintf(f,"%s,%s,%s,%d,%.2f,%d-%d\n",b[i].ISBN, b[i].title, b[i].author_name, b[i].quantity, b[i].price, b[i].pub_date.month, b[i].pub_date.year);
    }
    fclose(f);
}


int isvalid(char month[], char year[])
{
    int x,y,i;
    for(i=0; i<strlen(month); i++)
    {
        if(!(month[i]>='0' && month[i]<='9'))
            return 0;
    }
    for(i=0; i<strlen(year); i++)
    {
        if(!(year[i]>='0' && year[i]<='9'))
            return 0;
    }
    // month =10 year= 3000
    x=atoi(month);
    if(!(x>=1 && x<=12))
        return 0;

    y=atoi(year);
    if(y>=1900 && y<=2022)
        return 1;
    else
        return 0;
}


void modify()
{
    printf("MODIFY\n\n");// azbotha lw el ktab mwgod a2olo

    int i=0;
    char target_ISBN[20],month[20],year[20];

    printf("Enter the ISBN of the book: ");
    gets(target_ISBN);

    while(i < count)
    {
        if(!strcmp(b[i].ISBN,target_ISBN))
        {
            printf("\nBook old data :\n\n");
            print_book_data(i);

            printf("\nNew Book data :\n\n");
            printf("ISBN: ");
            gets(b[i].ISBN);
            printf("Title: ");
            gets(b[i].title);
            printf("Author: ");
            gets(b[i].author_name);
            printf("Quantity: ");
            scanf("%d", &b[i].quantity);
            printf("Price: ");
            scanf("%f", &b[i].price);
            getchar();
            do
            {
                printf("enter month: ");
                gets(month);
                printf("enter year: ");
                gets(year);
            }
            while(!isvalid(month,year));
            b[i].pub_date.month=atoi(month);
            b[i].pub_date.year=atoi(year);
            //scanf("%d-%d", &b[i].pub_date.month, &b[i].pub_date.year);

        }
        i++;
    }

}


void print_book_data(int i)
{
    char Months[12][20] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    printf("ISBN: %s\n",b[i].ISBN);
    printf("Title: %s\n",b[i].title);
    printf("Author: %s\n",b[i].author_name);
    printf("Quantity: %d\n",b[i].quantity);
    printf("Price: %.2f$\n",b[i].price);
    printf("Published: %s-%d\n\n",Months[b[i].pub_date.month-1],b[i].pub_date.year);
}


int isvalidISBN(char ISBN[])
{
    int i;
       for(i=0; i<strlen(ISBN); i++)
    {
        if(!(ISBN[i]>='0' && ISBN[i]<='9'))
            return 0;
    }

    if((strlen(ISBN))!=13)
        return 0;
else
    return 1;

}


void add()
{
    char user_month[20],user_year[20];
    printf("\nNew Book data :\n\n");

    do
    {
        printf("ISBN: ");
        gets(b[count].ISBN);
    }
    while(!isvalidISBN(b[count].ISBN));


    printf("Title: ");
    gets(b[count].title);
    printf("Author: ");
    gets(b[count].author_name);
    printf("Quantity: ");
    scanf("%d", &b[count].quantity);
    printf("Price: ");
    scanf("%f", &b[count].price);
    getchar();
    do
    {
        printf("Enter month: ");
        gets(user_month);
        printf("Enter year: ");
        gets(user_year);
    }
    while(!isvalid(user_month,user_year));

    b[count].pub_date.month=atoi(user_month);
    b[count].pub_date.year=atoi(user_year);


    count++;
}


int main()
{
    system("color 03");
    int i;
    load();
    char choice[10];

    printf("1-Log in\n2-Quit\n");
    gets(choice);

    if(strcmp(choice,"1") == 0)
        log_in();
    else if(strcmp(choice,"2") == 0)
        exit(0);
    else
    {
        printf("\nWrong input please try again!\n\n");
        main();
    }


    return 0;
}
