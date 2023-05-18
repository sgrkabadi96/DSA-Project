
/*
*************************************************DISCLAIMER************************************************************
 
                         WE HAVE CREATED SOME FILES AND STORED LINKS INTO THOSE FILES
                                 NAME OF THE FILES- cricket, algorithm
                The above mentioned file names have some links related to those file names
                stored in it. while running the code and checking browsing option please
                do brouse by searching the file name mentioned above
                        
                               EXAMPLE - "cricket" can be browsed.
 
                    FILE brute.txt contains the topics that can be searched using autocomplete
                  EXAMPLE - IF "cri" is typed then our autocomplete feature gives recomenations
                                    
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #include <curses.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>
// #include <term.h>

int MAX_VALID_YR = 9999;
int MIN_VALID_YR = 1800;
int nodecount = 0;

//structure to store detials of seachfeed
struct Searchlist
{
    char search_feed[200];
    struct Searchlist *right, *left;
    char title[100]; //title of the webpage
    int priority;
};

/*  STRUCTURE CONTAINING DETAILS ABOUT INFO OF USERSNOF GMAIL*/
struct signup
{
    int uid;
    char mailid[100];
    char password[100];
    char name[20];
    char inboxx[10][300];
    int inboxcount;
    char inboxname[10][100];
    char sendmessage[10];
    char mailsend[10];
};

// structure for stroting events deatils which is use in calender
struct event
{
    int d, m;
    char eventname[100];
};
typedef struct event Event;
Event events[100];

struct searches
{
    char word[20]; //STRUCTURE STORING DETAILS FROM AI
};
struct trienode
{
    char data;
    int wc;
    struct trienode *child[26];
};
struct trienode *root;

// stucture for storing details of city
struct citydetails
{
    char name[30];
    int district_number;
};

// structure for edges int graph
struct citygraph
{
    int u;
    int v;
    int d;
};

// search history in maps
struct History
{
    char source[20];
    char destiny[20];
    int distance;
};

typedef struct History HISTORY;
HISTORY His[20];
int coh = 0; // coh - count of history

typedef struct citydetails City;
City Cities[30];
int Cofc = 0; // cofc - count of cities

typedef struct citygraph graph;
graph paths[30];
int coe = 0; // coe = count of edges;

struct searches searchdata[10];
int m = 0, count;
struct signup signu[300];

int flag = 0;
typedef struct Searchlist URL;

int distance[20];
int sto = 0; // this is the globalcount that stores datas of autocomplete in char matrix store
int g[100][100];

URL *first = NULL;        //head node of Doubly linked list consisiting searches
URL *historyfirst = NULL; //haad node of Doubly linked list consisting history of seatrched data
URL *recover = NULL;      //head node used to recover deleted history by user

void loadfile(char str[]);
//FUNCTION DESCRIPTION
/*Loads the data from the file into appropriate data structure.We have chosen Doubly Linked List.
  Loadfile function calls "createll" function after one line of a file and storesnin abobe mentioned
  Data structure
 */
void createll(URL *);
//FUNCTION DESCRIPTION
/*
 FUNCTION IS CALLED FROM "LOADFILE"FUNCTION- As mentioned above.
 This creates doubly linked list. Adds new read node at the end of the list.
 */
void bubblesort(void);
//FUNCTION DESCRIPTION
/*
 FUNCTION SORTS THE DOUBLY LINKED LIST
 Function is called to sort the links based on their priority mentioned in the file syntax of topic.txt[MORE ABOUT IT ON "read.txt"
*/
void display(URL *);
//FUNCTION DESCRIPTION
/*
  Displays the data stored in doubly linked list to the user[WE HAVE STORED LINKS THAT ARE PRESENT IN FILES so that
  user gets the option to choose the link they want to open
*/
void linkopen(int, int);
//FUNCTION DESCRIPTION
/*
  Opens The link that user selects frop the options given. We traverse the doubly linked list and open the link chose
 by the user
*/
void history(URL *);
//FUNCTION DESCRIPTION
/*
  calls createldll function passsing the node with particular link opened by the user to store that in
  doubly linked list storing History
 */
void createldll(URL *);
//FUNCTION DESCRIPTION
/*
 Creates Doubly Linked list storing links that user opened
*/
void deletesearched(void);
//FUNCTION DESCRIPTION
/*
 This Displays the contents in history doubly linked list to the user[Displays History]
 Gives the option to Delete particular opened link and deletes it from the history doubly
 linked list.
 */
void signup(void);
//FUNCTION DESCRIPTION
/*
 Function reads the datas of the new user and stores in the file. Begins with reading the data from file named "id.txt"
 which contains an integer value stored in it indicationg number ids already stored. After creating the username
 and password  of the user it stores the drtails in file "signup.txt".
 
 Function also makes sure that user enters valid userid of form [abc@xyz.com] and insists to reenter if not entered
 in mentioned syntax.
*/
void signin(void);
//FUNCTION DESCRIPTION
/*
 Function reads mailid and password from the user.Allows accces to mail and to send messages only if login is succesfull
 checks if the entered mailid matches or is present in (signu) structure if present it captures the index location
 in 'count' variable.[ count represents or gives the index number at which signed in user details are present in signu
 strucrure array.
*/
void recovery(void);
//FUNCTION DESCRIPTION
/*
 Reads the mailid from the user. Asks to enter new passwrd and updates the value in "signup.txt"as well by calling
 "printinfile" function
 */
void printinfile(void);
//FUNCTION DESCRIPTION
/*
 This function is called from rcovery function
 In this function we print the user detials in signup.txt when any user changes their password
*/
void mailopen(void);
//FUNCTION DESCRIPTION
/*
 Gives the logged in user chance to open inbox or to compose mail,etc.
 */
void inbox(void);
//FUNCTION DESCRIPTION
/*
 Displays the mailids of those who have sent the messages to the user and gives the option to view the selected messages.
 */
void sendmails(void);
//FUNCTION DESCRIPTION
/*
 Displays the user the messages they have sent [ WE HAVENT STORED THIS DATA IN FILE SO ONCE PROGRAM IS CLOSED THIS DATA IS LOST]
 */
void compose(void);
//FUNCTION DESCRIPTION
/*
 reads the mailid of the user of whom the message has to be delivered then searches and stores the index number in "flag" variable where the
 details of user whom the messsage has to be delivered is present in "signu" structure array created above.
 Then the message is copied in the inboxx data type inside structure array of selected user.
*/
void loadsignupdata(void);
//FUNCTION DESCRIPTION
/*
 We have stored the details of the users who signup into the file named as "signup.tct". When program is ran these detials are loaded into structure
 array signu. This way detials are not lost.
 */
void storemsgdata(int);
//FUNCTION DESCRIPTION
/*
 In this function we store the inbox detials of the users into the file named as "loaddata.txt".
*/
void loadmsgdata(void);
//FUNCTION DESCRIPTION
/*
 In this function Inbox detials of the users stored in "loaddata.txt" is loaded into their respective data locations in signu structure array
 */
void trieinsertion(int);
//FUNCTION DESCRIPTION
/*
 To Attain 'AUTO COMPLETE' Feature we have used "TRIE DATA STRUCTURE".
 In this function we read the data from searchdata structure array and insert inside trie ndata structure
 */
struct trienode *gettrienode(char);
//FUNCTION DESCRIPTION
/*
 This function is called from trieinsertion function to get new node to insert inside trie
 */
void print_trie(struct trienode *);
//FUNCTION DESCRIPTION
/*
 This functions prints our trie.{Had used to check if our trie is working fine}
 */
int printintosuggestions(char str[]);
//FUNCTION DESCRIPTION
/*
String to be searched in browzer is read from the user from main function and passed as a parameter into this function.
 We check if the read string is present inside trie or not. If its present then we check if the entered string last node
 or no using "islastnode" function and if it isn't we append the string and display the full search topic to the user
*/
int islastnode(struct trienode *temp);
//FUNCTION DESCRIPTION
/*
 This Function is used to check if it is the last node of trie or string searching
 */
char *append(char *slice, char part);
//FUNCTION DESCRIPTION
/*
 In this function We append the half searched string with the topics present inthe brute.txt file that matches the half entered string
 This function is called from print function
 */
void print(struct trienode *, char str[]);
//FUNCTION DESCRIPTION
/*
 In this Function we print the character or string by completing halg read string. this function is called recursively.
  */
void selectchoice(char *);
//FUNCTION DESCRIPTION
/*
 In this function we guve user choise to select from the options available from auto complete reults.
 */

void loadEvents(void);
//FUNCTION DESCRIPTION
/*
This functions loads the events name and date from file eventList to struct Events
 */
int isLeap(int);
//FUNCTION DESCRIPTION
/*
This functions returns  1 if the year given is leap else returns 0;
 */
int isValidDate(int, int, int);
//FUNCTION DESCRIPTION
/*
This function returns 1 if the given date is valid (dd , mm , yyyy) else returns 0
 */
int dayNumber(int, int, int);
//FUNCTION DESCRIPTION
/*
This funtions returns day number for given date if day is monday if returns 1 , for tuesday it returns 2 and so on
 */
char *getMonthName(int);
//FUNCTION DESCRIPTION
/*
THis function returns the name of month for given month number jan for 1 , feb for 2 and so on
 */
char *getDayName(int);
//FUNCTION DESCRIPTION
/*
This funtion returns day name for a given int , returns monday for 1 , tuesday for 2 and so on.
 */
void addevent(int, int, char *);
//FUNCTION DESCRIPTION
/*
This functions adds the event date , month and name to structure event and sorts it in correct order.
A various of bubble sort is been user over here
 */
void printEvents(void);
//FUNCTION DESCRIPTION
/*
This funtion print the all the events in the events in correct order. It prints in the table format and in correct 
sorted order saperated by lines for each month
 */
void sortEvents(void);
//FUNCTION DESCRIPTION
/*
This functions sorts the events in events structure. A variation of bubble sort is been used over here
first sorts date based on month if month is same for two given days then it sorts based on date
 */
void findDay(int, int, int);
//FUNCTION DESCRIPTION
/*
This function prints the day name for the given date
 */
void printCalendar(int);
//FUNCTION DESCRIPTION
/*
This function prints the calender for the given year
the range of valid years is declared globally 
 */
int deleteevent(int, int);
//FUNCTION DESCRIPTION
/*
This function deletes the events from the events structure of calender and make sure the other events are in correct order
 */
int numberOfDays(int, int);
//FUNCTION DESCRIPTION
/*
This funtions returns the number of days in the given month and year  
 */
void printNearbyCities(void);
//FUNCTION DESCRIPTION
/*
This funtioss prints the nearby city for given city and range input of city name and range has been taken in this function
itself and makes call for dfs for rest of the work
 */
void dfs(int, int *, int);
//FUNCTION DESCRIPTION
/*
This funtion is used to detect the cities nearby given city and range
A variation of dfs is been used
 */
void ClearHistory(void);
//FUNCTION DESCRIPTION
/*
This function is used clear the history of search in maps structure
 */
void printHistory(void);
//FUNCTION DESCRIPTION
/*
This function prints the history present in search of maps
 */
void printCities(void);
//FUNCTION DESCRIPTION
/*
THis function prints the cities which are used in our function
 */
void FindThepathbetweenTwocities(int);
//FUNCTION DESCRIPTION
/*
This funtions prints the path and distance between cities
 */
int shortestpath(int, int);
//FUNCTION DESCRIPTION
/*
THis function is helper function of [FindThepathbetweenTwocities] 
 */
void addtoHistory(int, int, int);
//FUNCTION DESCRIPTION
/*
This funtion adds the search to history [Maps]
 */
void createAdjancecyMatrix(void);
//FUNCTION DESCRIPTION
/*
This funtions creates adjacnecy matrix and loads the correct data into it using edge structure
 */
void LoadGraph(void);
//FUNCTION DESCRIPTION
/*
This function load the data of graph in to structure
 */
void LoadCityNames(void);
//FUNCTION DESCRIPTION
/*
This functions Loads the city name from cities to city datails structure
 */
void PrintCityDeatails(void);
//FUNCTION DESCRIPTION
/*
This funtion prints the city details [FOR REFRENCE PURPOSE]
 */
void printgraph(void);
//FUNCTION DESCRIPTION
/*
This funtion prints the Graph [FOR REFRENCE PURPOSE]
 */

int Count_of_events = 0;

char store[10][30];
int main()
{

    char str[20];
    int ch, b, d, choice, bch;
    loadmsgdata();
    LoadCityNames();
    LoadGraph();
    loadEvents();
    printf("\n****************************WELCOME TO GAAGAL BROWZER*************************************\n");
    do
    {

        printf("\n 1-TO BROWZE\n 2-SETTINGS\n 3-GMAIL\n 4-CALENDER\n 5-MAPS\n 6-EXIT ");
        scanf("%d", &b);
        switch (b)
        {

        case 1:

            printf("1-Incognito mode\n0-Continue");
            scanf("%d", &bch);
            printf("______________SEARCH HERE_______________\n");
            FILE *fp;
            fp = fopen("brute.txt", "r");
            int p = 0;
            while (!(feof(fp)))
            {
                fscanf(fp, "%s\n", searchdata[p++].word);
            }
            fclose(fp);
            root = gettrienode('\0');
            trieinsertion(p);
            //                print_trie(root);

            scanf("%s", str);
            sto = 0;
            int a;
            a = printintosuggestions(str);
            if (a == 0)
            {
                break;
            }
            selectchoice(str);

            if (flag == 1)
            {
                first = NULL;
                free(first);
            }
            loadfile(str);
            bubblesort();
            display(first);
            printf("Enter choice");
            scanf("%d", &ch);
            linkopen(ch, bch);
            break;
        case 2:
            printf("\nEnter 1-HISTORY\n2-DELETE PARTICULAR HISTORY\n3-CLEAR SEARCH HISTORY\n4-RECOVER SEARCH HISTORY\n");

            scanf("%d", &d);
            if (d == 1)
            {
                printf("\n*********************HISTORY**************\n\n");
                display(historyfirst);
            }
            if (d == 2)
            {
                deletesearched();
            }
            if (d == 3)
            {
                recover = historyfirst;
                historyfirst = NULL;
            }
            if (d == 4)
            {
                historyfirst = recover;
            }
            break;
        case 3:
            printf("**************************WELCOME TO GAAGLE MAIL********************************\n");
            printf("1-SIGNUP\n2-SIGNIN\n");
            scanf("%d", &choice);
            if (choice == 1)
            {
                signup();
            }
            if (choice == 2)
            {
                loadsignupdata();
                signin();
            }
            break;
        case 4:

            while (1)
            {
                // printf("\n****************************WELCOME TO GAAGAL CALENDER*************************************\n");
                printf("**************************WELCOME TO GAAGLE CALENDER********************************\n");
                int c;

                printf(" 1.Get Calender for year\n");
                printf(" 2.Check if date is valid\n");
                printf(" 3.Find Day for a given date\n");
                printf(" 4.Sort and print Events\n");
                printf(" 5.Add Event to calender\n");
                printf(" 6.Delete Event from calender\n");
                printf(" 9.Back\n\n");
                printf(" Enter your choice : ");
                scanf("%d", &c);
                if (c == 1)
                {
                    int y;
                    printf("Enter the year : ");
                    scanf("%d", &y);
                    printCalendar(y);
                }
                else if (c == 2)
                {
                    printf("Enter Date (dd/mm/yyyy) : ");
                    int dd, mm, yyyy;
                    scanf("%d%d%d", &dd, &mm, &yyyy);
                    if (isValidDate(dd, mm, yyyy) == 1)
                    {
                        printf("The Date is Valid\n");
                    }
                    else
                    {
                        printf("Invalid date\n");
                    }
                }
                else if (c == 3)
                {
                    printf("Enter Date (dd/mm/yyyy) : ");
                    int dd, mm, yyyy;
                    scanf("%d%d%d", &dd, &mm, &yyyy);
                    findDay(dd, mm, yyyy);
                }
                else if (c == 4)
                {
                    sortEvents();
                    printEvents();
                    printf("Events Sorted Successfully\n");
                }
                else if (c == 5)
                {
                    printf("Enter Valid Date (dd/mm) : ");
                    int dd, mm;
                    scanf("%d%d", &dd, &mm);
                    printf("Enter Event Name : ");
                    char eventname[100];
                    scanf("%s", eventname);
                    addevent(dd, mm, eventname);
                    printf("***Event added succesfully in events***\n");
                }
                else if (c == 6)
                {
                    printf("Enter Valid Date (dd/mm) : ");
                    int dd, mm;
                    scanf("%d%d", &dd, &mm);
                    int x = deleteevent(dd, mm);
                    if (x == 1)
                    {
                        printf("***Event deleted succesfully from events***\n");
                    }
                }
                else if (c == 9)
                {
                    // return 0;
                    break;
                }
            }
            break;
        case 5:

            while (1)
            {
                //    printf("\n****************************WELCOME TO GAAGAL MAPS*************************************\n");
                printf("**************************WELCOME TO GAAGLE MAPS********************************\n");
                printf(" 1.Search\n");
                printf(" 2.Get List Of cities\n");
                printf(" 3.Check History\n");
                printf(" 4.Clear History\n");
                printf(" 5.Search for Nearby Cities\n");
                printf(" 6.Search in Incognito Mode\n");
                printf(" 9.Back\n");
                printf(" Enter your choice : ");
                int ch;
                scanf("%d", &ch);
                if (ch == 1)
                {
                    FindThepathbetweenTwocities(0);
                }
                else if (ch == 2)
                {
                    printCities();
                }
                else if (ch == 3)
                {
                    printHistory();
                }
                else if (ch == 4)
                {
                    ClearHistory();
                }
                else if (ch == 5)
                {
                    printNearbyCities();
                }
                else if (ch == 6)
                {
                    FindThepathbetweenTwocities(1);
                }
                else if (ch == 9)
                {
                    break;
                }
            }
            break;
            case 6: exit(0);
        }
    } while (b != 8);
}

void loadfile(char *str)
{
    FILE *fp;
    strcat(str, ".txt"); //adds ".txt" to the text typed by the user

    URL *nw;

    fp = fopen(str, "r");
    if (fp == NULL)
    {
        printf("ERROR");
    }

    while (!feof(fp))
    {

        nw = (URL *)malloc(sizeof(URL));
        nw->right = NULL;
        fscanf(fp, "%d\n%[^\n]\t\n%[^\n]\t", &nw->priority, nw->search_feed, nw->title);
        nodecount++;
        createll(nw);
    }
    flag = 1;

    fclose(fp);
}

void createll(URL *nw)
{
    URL *curr;
    if (first == NULL)
    {
        nw->left = NULL;
        first = nw;
    }
    else
    {
        for (curr = first; curr->right != NULL; curr = curr->right)
            ;
        nw->left = curr;
        curr->right = nw;
    }
}
void bubblesort()
{
    URL *curr;
    URL *temp = NULL;
    int swap;
    URL *t;
    char ttitle[100];
    char searl[100];
    int tp;
    do
    {
        swap = 0;
        curr = first;
        while (curr->right != temp)
        {
            if (curr->priority < curr->right->priority)
            {
                t = curr->right;
                strcpy(ttitle, curr->title);
                strcpy(searl, curr->search_feed);
                tp = curr->priority;
                strcpy(curr->title, t->title);
                strcpy(curr->search_feed, t->search_feed);
                curr->priority = t->priority;
                strcpy(t->title, ttitle);
                strcpy(t->search_feed, searl);
                t->priority = tp;
                swap = 1;
            }
            curr = curr->right;
        }
        temp = curr;
    } while (swap);
}

void display(URL *a)
{
    URL *curr;
    int i = 1;
    for (curr = a; curr != NULL; curr = curr->right)
    {
        printf("\n%d\t", i++);

        printf("%s\n", curr->title);
        printf("%s\n\n\n", curr->search_feed);
    }
}

void linkopen(int ch, int bch)
{
    URL *curr;
    int i = 1, c = 0;

    for (curr = first; i < ch && curr->right != NULL; curr = curr->right, i++)
        ;

    if (bch == 0)
    {
        history(curr);
    }
    char command[500];
    char var[500];
    strcpy(var, "open");
    strcat(var, " ");
    strcat(var, curr->search_feed);

    sprintf(command, "%s", var);
    system(command);

    do
    {
        if (c == 1)
        {

            curr = curr->right;
            if (curr == NULL)
            {
                printf("No more pages");
            }

            if (bch == 0)
            {
                history(curr);
            }
            char command[500];
            char var[500];
            strcpy(var, "open");
            strcat(var, " ");
            strcat(var, curr->search_feed);

            sprintf(command, "%s", var);

            system(command);
        }

        if (c == 2)
        {
            curr = curr->left;

            if (bch == 0)
            {
                history(curr);
            }
            char command[500];
            char var[500];
            strcpy(var, "open");
            strcat(var, " ");
            strcat(var, curr->search_feed);

            sprintf(command, "%s", var);
            system(command);
        }
        if (c > 2)
        {
            break;
        }

        printf("Enter \n 1->next page\n 2->prev page\n 3->menu");
        scanf("%d", &c);

    } while ((c == 1 || c == 2) && (curr->right != NULL || curr->left != NULL));
}

void history(URL *curr)
{

    createldll(curr);
}

void createldll(URL *curr)
{
    URL *nw;
    nw = (URL *)malloc(sizeof(URL));
    nw->left = NULL;
    strcpy(nw->search_feed, curr->search_feed);
    strcpy(nw->title, curr->title);
    if (historyfirst == NULL)
    {
        historyfirst = nw;
    }
    else
    {
        nw->right = historyfirst;
        historyfirst->left = nw;
        historyfirst = nw;
    }
}
void deletesearched()
{
    display(historyfirst);
    int ch;
    URL *curr, *prev;
    prev = NULL;
    int i = 1;
    printf("select your choice to delete");
    scanf("%d", &ch);
    if (historyfirst == NULL)
    {
        return;
    }
    for (curr = historyfirst; curr->right != NULL && i != ch; curr = curr->right, i++)
        ;

    if (curr == historyfirst && curr->right == NULL)
    {
        historyfirst = NULL;
    }
    else
    {
        if (curr->left != NULL)
        {
            prev = curr->left;
        }

        prev->right = curr->right;

        curr = curr->right;
        if (curr != NULL)
            curr->left = prev;
    }
}

void signup()
{
    int id;
    FILE *fsiri;
    fsiri = fopen("id.txt", "r");
    fscanf(fsiri, "%d", &id);
    fclose(fsiri);

    int o;
    FILE *fp;
    fp = fopen("signup.txt", "a");
    struct signup *a;
    a = (struct signup *)malloc(sizeof(a));
    loadsignupdata();
    printf("\n*******CREATE YOUR ACCOUNT**********\n");
    printf("Enter Your Name:\n");
    scanf("%s", a->name);
    printf(" Create username:\n");
    scanf("%s", a->mailid);
    int flag = 0, flag1 = 0, flag2 = 0;
    for (int i = 0; i < m; i++)
    {
        if ((strcmp(a->mailid, signu[i].mailid)) == 0)
        {
            flag = 1;

            break;
        }
    }
    if (flag == 1)
    {
        printf("Userid already exists\n");
        printf("enter 0 to menu\n");
        scanf("%d", &o);
        if (o == 0)
        {
            return;
        }
        signup();
        return;
    }
    else
    {
        int q;
        char str[100];
        strcpy(str, a->mailid);
        q = (int)strlen(str);
        for (int i = 1; i < q - 4; i++)
        {
            if (str[i] == '@')
            {
                flag2 = 1;
            }
            if (str[i] == ' ')
            {
                flag1 = 1;
            }
        }

        if (flag1 == 0 && flag2 == 1)
        {
            if (str[q - 4] != '.' || str[q - 3] != 'c' || str[q - 2] != 'o' || str[q - 1] != 'm')
            {
                flag2 = 0;
            }
        }

        if (flag1 == 1 || flag2 == 0)
        {

            printf("\nThis is not a valid email id.Email id regex should be abc@xy.com");
            signup();
            return;
        }

        printf("Username created\n");

        printf(" Create Password: \n");

        scanf("%s", a->password);
        fprintf(fp, "%d %s %s\n", id++, a->mailid, a->password);

        fclose(fp);
        FILE *fsiri;
        fsiri = fopen("id.txt", "w");
        fprintf(fsiri, "%d", id);
        fclose(fsiri);

        free(a);
    }
}

void loadsignupdata()
{
    FILE *fp;
    fp = fopen("signup.txt", "r");
    m = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%d %s %s", &signu[m].uid, signu[m].mailid, signu[m].password);
        m++;
    }
    fclose(fp);
}

void signin()
{
    char pass[100], user[100];
    printf("Enter MAIL_ID");
    scanf("%s", user);
    printf("Enter passwor");
    scanf("%s", pass);
    loadsignupdata();

    int flag = -1;
    for (int i = 0; i < m; i++)
    {
        if ((strcmp(signu[i].mailid, user)) == 0 && (strcmp(signu[i].password, pass)) == 0)
        {
            flag = i;
            break;
        }
    }
    count = flag;
    if (flag == -1)
    {
        printf("Your detials are invalid\n");

        int ch;
        printf("Press 1 if forgot password:\n Press 2 to signup\n press 3 to exit\n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            recovery();
            break;
        case 2:
            signup();
            break;
        case 3:
            return;
        }
    }
    else
    {

        printf("Login Successfull");
        mailopen();
    }
}

void recovery()
{

    char mailid[100];
    int flag = -1;
    printf("Enter mailid");
    scanf("%s", mailid);
    for (int i = 0; i < m; i++)
    {
        if (strcmp(mailid, signu[i].mailid) == 0)
        {
            flag = i;
            break;
        }
    }
    if (flag != -1)
    {
        char pass[100];
        printf("Enter new password");
        scanf("%s", pass);
        strcpy(signu[flag].password, pass);
        printf("Password changed");
        printinfile();
    }
}

void mailopen()
{
    int o;
    do
    {
        int choice;
        printf("\n1)INBOX  2)COMPOSE  3)SEND 4)Logout and back to menu");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            inbox();
            break;

        case 2:
            compose();
            break;
        case 3:
            sendmails();
            break;
        case 4:
            return;
        }
        printf("Enter 1 to home manu of gmail\n");
        scanf("%d", &o);

    } while (o == 1);
}

void compose()
{
    char mail[100];
    char message[300];
    int count1;
    loadsignupdata();
    printf("Enter mailid to send\n");
    scanf("%s", mail);

    int flag = -1;
    for (int i = 0; i < m; i++)
    {
        if (strcmp(mail, signu[i].mailid) == 0)
        {
            flag = i;
            break;
        }
    }

    if (flag == -1)
    {
        printf("Invalid mail id");
        compose();
        return;
    }
    else
    {
        printf("Enter message\n");
        scanf("%s", message);
        count1 = signu[flag].inboxcount;
        strcpy(signu[flag].inboxx[count1], message);
        strcpy(signu[flag].inboxname[count1], signu[count].mailid);
        signu[flag].inboxcount = count1 + 1;
        storemsgdata(flag);

        strcpy(signu[count].mailsend, mail);
        strcpy(signu[count].sendmessage, message);
        printf("Message Sent\n");
    }
}
void sendmails()
{
    for (int i = 0; i <= signu[count].inboxcount; i++)
    {
        printf("\n%d.To:%s", i, signu[count].mailsend);
    }
}

void printinfile()
{
    FILE *fp;
    fp = fopen("signup.txt", "w");

    for (int i = 0; i < m; i++)
    {
        fprintf(fp, "%d %s %s\n", i, signu[i].mailid, signu[i].password);
    }
    fclose(fp);
}

void inbox()
{
    int ch, op;
    do
    {
        for (int i = 1; i <= signu[count].inboxcount; i++)
        {
            char str[100];
            strcpy(str, signu[count].inboxname[i - 1]);
            printf("\n%d.%s", i, str);
        }

        printf("\nPress the mail no to view or 0  to back");
        scanf("%d", &ch);
        if (ch == 0)
        {
            return;
        }
        if (ch > 0 && ch <= signu[count].inboxcount)
        {
            printf("From:%s\nMessage:\n%s", signu[count].inboxname[ch - 1], signu[count].inboxx[ch - 1]);
        }
        printf("\nPress 0 to view inbox again");
        scanf("%d", &op);

    } while (op == 0);
}

void storemsgdata(int flag)
{
    FILE *fp;
    fp = fopen("loaddata.txt", "a");

    for (int i = 0; i < signu[flag].inboxcount; i++)
    {
        if (i == signu[flag].inboxcount - 1)
        {
            fprintf(fp, "%d %d %s %s\n", signu[flag].uid, signu[flag].inboxcount, signu[flag].inboxname[i], signu[flag].inboxx[i]);
        }
    }

    fclose(fp);
}
void loadmsgdata()
{
    FILE *fptr;
    fptr = fopen("loaddata.txt", "r");

    while (!(feof(fptr)))
    {
        int a, b;
        char name[200];
        char msg[200];
        fscanf(fptr, "%d %d %s %s\n", &a, &b, name, msg);
        signu[a].inboxcount = b;
        if (b != 0)
        {
            strcpy(signu[a].inboxname[b - 1], name);
            strcpy(signu[a].inboxx[b - 1], msg);
        }
    }
    fclose(fptr);
}

struct trienode *gettrienode(char data)
{
    struct trienode *node;
    node = (struct trienode *)malloc(sizeof(struct trienode));
    node->data = data;
    node->wc = 0;
    for (int i = 0; i < 26; i++)
    {
        node->child[i] = NULL;
    }
    return node;
}

void trieinsertion(int a)
{
    int i;
    for (i = 0; i < a; i++)
    {
        struct trienode *temp;
        temp = root;
        char str[20];
        strcpy(str, searchdata[i].word);
        for (int b = 0; str[b] != '\0'; b++)
        {
            // Get the relative position in the alphabet list
            int idx = (int)str[b] - 'a';
            if (temp->child[idx] == NULL)
            {
                temp->child[idx] = gettrienode(str[b]);
            }
            if (str[b + 1] == '\0')
            {
                temp->child[idx]->wc += 1;
            }
            temp = temp->child[idx];
        }
    }
}
// Had used this function to check if data are stored in trie properly.
void print_trie(struct trienode *root)
{
    // Prints the nodes of the trie
    if (!root)
    {
        return;
    }
    struct trienode *temp = root;
    printf("%c \t%d\n", temp->data, temp->wc);
    for (int i = 0; i < 26; i++)
    {
        print_trie(temp->child[i]);
    }
}

int printintosuggestions(char str[])
{
    struct trienode *temp = root;
    int n;
    n = (int)strlen(str);
    for (int level = 0; level < n; level++)
    {
        int index;
        index = str[level] - 'a';

        // no string in the Trie has this prefix
        if (temp->child[index] == NULL)
        {
            printf("Please enter search topics given in brute.txt file\n");
            return 0;
        }
        temp = temp->child[index];
    }
    int a, b;
    b = islastnode(temp);
    a = temp->wc;

    if (b == 1 && a > 0)
    {
        printf("%s", str);
        return -1;
    }
    if (b == 0)
    {
        print(temp, str);
    }

    return 1;
}
int islastnode(struct trienode *temp)
{
    for (int i = 0; i < 26; i++)
        if (root->child[i] != NULL)
        {
            return 0;
        }
    return 1;
}

void print(struct trienode *temp, char str[])
{
    if (islastnode(temp) == 1)
    {
        return;
    }

    if (temp->wc > 0)
    {

        strcpy(store[sto++], str);
        printf("%d %s\n", sto, str);
    }
    for (int i = 0; i < 26; i++)
    {
        if (temp->child[i] != NULL)
        {
            // append current character to currPrefix string
            print(temp->child[i], append(str, i + 97));
        }
    }
}
char *append(char *slice, char part)
{

    char *str = malloc(sizeof(char) * (strlen(slice) + 2));

    int i = 0;
    while (slice[i] != '\0')
    {
        str[i] = slice[i];
        i++;
    }

    str[i++] = part;
    str[i] = '\0';

    return str;
}

void selectchoice(char str[])
{

    int ch;
    scanf("%d", &ch);
    strcpy(str, store[ch - 1]);
}
void loadEvents()
{
    FILE *f = NULL;
    f = fopen("EventsList.txt", "r");
    if (f == NULL)
    {
        printf("File Not found\n");
        return;
    }
    while (!feof(f))
    {
        fscanf(f, "%d %d %s\n", &events[Count_of_events].d, &events[Count_of_events].m, events[Count_of_events].eventname);
        Count_of_events++;
    }
    fclose(f);
}

int isLeap(int year)
{
    int ans = (((year % 4 == 0) &&
                (year % 100 != 0)) ||
               (year % 400 == 0));
    if (ans == 1)
        return 1;
    return 0;
}

int isValidDate(int d, int m, int y)
{

    if (y > MAX_VALID_YR ||
        y < MIN_VALID_YR)
        return 0;
    if (m < 1 || m > 12)
        return 0;
    if (d < 1 || d > 31)
        return 0;

    // For Month Feb
    if (m == 2)
    {
        if (isLeap(y))
            return (d <= 29);
        else
            return (d <= 28);
    }

    // Months of April, June,
    // Sept and Nov must have
    // number of days less than
    // or equal to 30.
    if (m == 4 || m == 6 ||
        m == 9 || m == 11)
        return (d <= 30);

    return 1;
}

int dayNumber(int day, int month, int year)
{
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    year -= month < 3;
    return (year + year / 4 - year / 100 + year / 400 + t[month - 1] + day) % 7;
}

char *getMonthName(int monthNumber)
{
    char *month;

    switch (monthNumber)
    {
    case 0:
        month = "January";
        break;
    case 1:
        month = "February";
        break;
    case 2:
        month = "March";
        break;
    case 3:
        month = "April";
        break;
    case 4:
        month = "May";
        break;
    case 5:
        month = "June";
        break;
    case 6:
        month = "July";
        break;
    case 7:
        month = "August";
        break;
    case 8:
        month = "September";
        break;
    case 9:
        month = "October";
        break;
    case 10:
        month = "November";
        break;
    case 11:
        month = "December";
        break;
    }
    return month;
}

char *getDayName(int day)
{
    char *dayname;

    if (day == 0)
    {
        dayname = "Sunday";
    }
    else if (day == 1)
    {
        dayname = "Monday";
    }
    else if (day == 2)
    {
        dayname = "Tuesday";
    }
    else if (day == 3)
    {
        dayname = "Wednesday";
    }
    else if (day == 4)
    {
        dayname = "Thursday";
    }
    else if (day == 4)
    {
        dayname = "Friday";
    }
    else if (day == 5)
    {
        dayname = "Saturday";
    }
    else if (day == 6)
    {
        dayname = "Sunday";
    }
    return dayname;
}
int numberOfDays(int monthNumber, int year)
{
    // January
    if (monthNumber == 0)
        return (31);

    // February
    if (monthNumber == 1)
    {
        // If the year is leap then Feb
        // has 29 days
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
            return (29);
        else
            return (28);
    }

    // March
    if (monthNumber == 2)
        return (31);

    // April
    if (monthNumber == 3)
        return (30);

    // May
    if (monthNumber == 4)
        return (31);

    // June
    if (monthNumber == 5)
        return (30);

    // July
    if (monthNumber == 6)
        return (31);

    // August
    if (monthNumber == 7)
        return (31);

    // September
    if (monthNumber == 8)
        return (30);

    // October
    if (monthNumber == 9)
        return (31);

    // November
    if (monthNumber == 10)
        return (30);

    // December
    if (monthNumber == 11)
        return (31);
    return 0;
}

void printCalendar(int year)
{
    if (year > MAX_VALID_YR || year < MIN_VALID_YR)
    {
        printf("Enter Valid year number (%d-%d)\n", MIN_VALID_YR, MAX_VALID_YR);
        return;
    }
    printf("\n     Calendar - %d\n\n", year);
    int days;

    int current = dayNumber(1, 1, year);
    for (int i = 0; i < 12; i++)
    {
        days = numberOfDays(i, year);

        printf("\n ------------%s-------------\n",
               getMonthName(i));

        printf(" Sun   Mon  Tue  Wed  Thu  Fri  Sat\n");

        int k;
        for (k = 0; k < current; k++)
            printf("     ");

        for (int j = 1; j <= days; j++)
        {
            printf("%5d", j);

            if (++k > 6)
            {
                k = 0;
                printf("\n");
            }
        }
        if (k)
            printf("\n");

        current = k;
    }

    return;
}

void findDay(int d, int m, int y)
{
    int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int s;
    if ((y % 400 == 0) || ((y % 4 == 0) && (y % 100 != 0)))
        month[1] = 29;
    for (int i = 0; i < m - 1; i++)
        s = s + month[i];
    s = s + (d + y + (y / 4) - 2);
    s = s % 7;
    char *dayname = getDayName(s);
    printf("The day is : %s \n", dayname);
}

void sortEvents()
{
    for (int i = 0; i < Count_of_events; i++)
    {
        for (int j = 0; j < Count_of_events; j++)
        {
            if (events[i].m < events[j].m)
            {
                Event t = events[i];
                events[i] = events[j];
                events[j] = t;
            }
            else if (events[i].m == events[j].m)
            {
                if (events[i].d < events[j].d)
                {

                    Event t = events[i];
                    events[i] = events[j];
                    events[j] = t;
                }
            }
        }
    }
}

void printEvents()
{
    printf("\nDay | Month | Event_name \n");
    printf("-------------------------------------\n");
    for (int i = 0; i < Count_of_events; i++)
    {
        printf("%2d  |  %2d   |  %s\n", events[i].d, events[i].m, events[i].eventname);
        if (events[i].m != events[i + 1].m)
        {
            printf("-------------------------------------\n");
        }
    }
}

void addevent(int dd, int mm, char *name)
{
    events[Count_of_events].d = dd;
    events[Count_of_events].m = mm;
    strcpy(events[Count_of_events].eventname, name);
    Count_of_events++;
    sortEvents();
}

int deleteevent(int dd, int mm)
{
    int i;
    int f = 0;
    for (i = 0; i < Count_of_events; i++)
    {
        if (events[i].d == dd && events[i].m == mm)
        {
            f = 1;
            break;
        }
    }
    if (f == 0)
    {
        printf("***No event found on that date***\n");
        return 0;
    }
    while (i - 1 < Count_of_events)
    {
        events[i] = events[i + 1];
        i++;
    }
    Count_of_events--;
    return 1;
}
void LoadGraph()
{
    FILE *f = NULL;
    f = fopen("Graph.txt", "r");
    if (f == NULL)
    {
        printf("File Not found\n");
        return;
    }
    while (!feof(f))
    {
        fscanf(f, "%d %d %d\n", &paths[coe].u, &paths[coe].v, &paths[coe].d);
        coe++;
    }
    fclose(f);
}

void LoadCityNames()
{
    FILE *fptr = NULL;
    Cofc = 0;
    fptr = fopen("CityNames.txt", "r");
    if (fptr == NULL)
        printf("Not found");
    while (!feof(fptr))
    {
        fscanf(fptr, "%s %d\n", Cities[Cofc].name, &Cities[Cofc].district_number);
        // idx++;
        Cofc++;
    }
    fclose(fptr);
}

void PrintCityDeatails()
{
    for (int i = 0; i < Cofc; i++)
    {
        printf("%s ", Cities[i].name);
        printf("%d\n", Cities[i].district_number);
    }
}

void printgraph()
{
    for (int i = 0; i < coe; i++)
    {
        printf("%d %d %d\n", paths[i].u, paths[i].v, paths[i].d);
    }
}

int check(char s[])
{
    char t[20];
    for (int i = 0; i < Cofc; i++)
    {

        strcpy(t, Cities[i].name);

        if (strcmp(t, s) == 0)
        {
            return i;
        }
    }
    return -1;
}

int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

int distance[20];

int g[100][100];

void createAdjancecyMatrix()
{
    for (int i = 0; i < Cofc; i++)
    {
        for (int j = 0; j < Cofc; j++)
        {
            if (i != j)
            {
                g[i][j] = INT_MAX / 2;
            }
            else if (i == j)
            {
                g[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < coe; i++)
    {
        graph path = paths[i];
        g[path.u][path.v] = path.d;
        g[path.v][path.u] = path.d;
    }
}

int path[100];
int end;

int findPath(int s, int d, int distance, int *visited, int idx)
{
    if (s == d && distance == 0)
    {
        end = idx;
        path[idx] = -99;
        return 1;
    }
    if (s == d)
        return 0;
    visited[s] = 1;
    path[idx] = s;
    idx++;
    for (int i = 0; i < Cofc; i++)
    {
        if (g[s][i] != 0 && visited[i] == 0)
        {
            int ans = findPath(i, d, distance - g[s][i], visited, idx);
            if (ans == 1)
            {
                return 1;
            }
        }
    }
    visited[s] = 0;
    idx--;
    return 0;
}

void addtoHistory(int s, int d, int dis)
{
    // char stemp[20] = Cities[s].name;
    // char dtemp[20] = Cities[d].name;
    strcpy(His[coh].source, Cities[s].name);
    strcpy(His[coh].destiny, Cities[d].name);
    His[coh].distance = dis;
    coh++;
}

int shortestpath(int s, int d)
{
    int visited[Cofc];
    for (int i = 0; i < Cofc; i++)
    {
        visited[i] = 0;
    }

    for (int i = 0; i < Cofc; i++)
    {
        for (int j = 0; j < Cofc; j++)
        {
            if (i != j)
            {
                g[i][j] = INT_MAX / 2;
            }
            else if (i == j)
            {
                g[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < coe; i++)
    {
        graph path = paths[i];
        g[path.u][path.v] = path.d;
        g[path.v][path.u] = path.d;
    }
    int distance[Cofc];
    for (int i = 0; i < Cofc; i++)
    {
        distance[i] = g[s][i];
    }

    visited[s] = 1;
    int n = Cofc, minv;
    for (int i = 0; i < n - 1; i++)
    {

        int mindis = INT_MAX / 2;
        for (int j = 0; j < n; j++)
        {
            if (visited[j] == 0)
            {
                if (distance[j] < mindis)
                {
                    mindis = distance[j];
                    minv = j;
                }
            }
        }

        visited[minv] = 1;
        for (int j = 0; j < n; j++)
        {
            if (visited[j] == 0)
            {
                distance[j] = min(distance[j], g[minv][j] + distance[minv]);
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }
    findPath(s, d, distance[d], visited, 0);
    printf("\n             ******Shortest Way to go from your source to destiny*******        \n");

    for (int i = 0; i < end; i++)
    {
        printf("%s -> ", Cities[path[i]].name);
    }
    printf("%s ", Cities[d].name);

    return distance[d];
}

void FindThepathbetweenTwocities(int inco)
{
    char s[20];
    printf("Enter the source : ");
    scanf("%s", s);
    int s_cityno = check(s);
    if (s_cityno == -1)
    {
        printf("*******Invalid City Name*******\n");
        return;
    }
    printf("Enter the distination : ");
    char d[20];
    scanf("%s", d);
    int d_cityno = check(d);
    if (d_cityno == -1)
    {
        printf("*******Invalid City Name*******\n");
        return;
    }
    int distance = shortestpath(s_cityno, d_cityno);
    if (inco == 0)
    {
        addtoHistory(s_cityno, d_cityno, distance);
    }
    printf(", Distance = %d Km", distance);
    printf("\n              ********************************************************\n");
}

void printCities()
{
    printf("     **** Cities ****         \n");
    for (int i = 0; i < Cofc; i++)
    {
        printf("%s\n", Cities[i].name);
    }
}

void printHistory()
{
    if (coh == 0)
    {
        printf("********History is Empty***********\n");
        return;
    }
    printf("Source   Destiny  Distance \n");
    for (int i = 0; i < coh; i++)
    {
        printf("%s    %s   %d\n", His[i].source, His[i].destiny, His[i].distance);
    }
}

void ClearHistory()
{
    coh = 0;
}

void dfs(int s, int *v, int dis)
{
    if (dis < 0)
    {
        return;
    }

    v[s] = 1;
    printf("%s\n", Cities[s].name);

    for (int i = 0; i < Cofc; i++)
    {
        if (g[s][i] != (INT_MAX / 2) && g[s][i] > 0 && v[i] == 0)
        {
            dfs(i, v, (dis - g[s][i]));
        }
    }
}

void printNearbyCities()
{
    char s[20];
    int dis;
    printf("Enter your city name and distance(in Km) to check nearby places : ");
    scanf("%s", s);
    scanf("%d", &dis);
    int s_no = -1;

    for (int i = 0; i < Cofc; i++)
    {
        if (strcmp(s, Cities[i].name) == 0)
        {
            s_no = Cities[i].district_number;
            break;
        }
    }
    if (s_no == -1)
    {
        printf("*******Invalid City Name*******\n");
        return;
    }

    int visited[Cofc];
    for (int i = 0; i < Cofc; i++)
    {
        visited[i] = 0;
    }
    dfs(s_no, visited, dis);
}
