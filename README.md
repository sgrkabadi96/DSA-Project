# INFORMATION ABOUT CREATED FILES-


1. Signup.txt -File contains all the details of the users who have 
   created their account.
  
   FILE PRINT FORMAT:    UserID[UID]    EmailID    Password

2. Loaddata.txt - File contains details or data about the inbox of users
 
   FILE PRINT FORMAT:    UserID[UID]    Inboxcount    MailID  Message  
 
   -UserID Depicts the Id of the user 
   -Inboxcount Depicts the inboxcount of the user at the instant 
    particular message was received
   -MailID Depicts the MailD of the user who has sent the Message
   -Message Depicts the message sent by the user

3. Id.txt - File contains only one integer
  
   FILE PRINT FORMAT: x{Some integer}
   
   -This number represents number of users those have created account. So
    that when the program is 
    ran and new user is creating account his details are stored at proper
    index number in structure
    array signup signu[300] created in the code globally.

4. Brute.txt - File contains some search topics those are stored into "TRIE"
   Data stricture when the program is run.
   
   FILE PRINT FORMAT: Searchtopics
   
5. Other than these files we have created certain files with name of some 
   search topics as mentioned in the Disclaimer of the main.c file.
  
   FILES PRINT FORMAT: priority[INT]
                       Title
                       Link

   Priority- We have set some priority to some links. After storming into 
   Doubly    linked list.We have used bubble sort to sort these links 
   according to priority.
  
   Title-Depicts name of the link or webpage name.
  
   Link- Link that will open the webpage.
 
   
FILENAMES OF SEARCH TOPICS WE HAVE CREATED: 

cricket.txt , algorithm.txt , viratkohli.txt , references.txt [ This contains the links that we have referred ]

6.  Events.txt: More about this is mentioned in the calendar section below.

7.  Cities.txt: More about this is mentioned in the Maps section below.
  

INFORMATION ABOUT FEATURES:

1-To Browse:
*************[PLEASE DO SEARCH ONLY WITH LOWER CASE LETTERS]***************
  
 ->Autocomplete feature is used here.If the user types half string of those 
   search topics mentioned above
 
 it will refer/suggest the topics to the user.
  
 Ex- If V is searched then it will recommend viratkohli.
   
 IT WILL RECOMMEND ONLY THOSE WORDS WHICH ARE STORED IN BRUTE.TXT FILE

2-Settings:

[ WE HAVE NOT STORED THE HISTORY IN FILE SO ITS NOT PRESENT ONCE PROGRAM IS CLOSED ]
  

 ->Settings contains following functionalities:
   
   1-History: Links which are opened by the user are displayed.
   2-Delete particular history: User can delete any history of their choice.
   3-Clear search history: Complete search history is deleted.
   4-Recover search history: Completely deleted search history 
     can be recovered.

3-Gmail: 
   
    
   1- Signup[Creating new account]
       
       MailId , UserID , and password of the user who creates his account 
       is stored in signup.txt file.
       We load this file every time program is run as mentioned above.
            
           SOME CREATED IDS

       ID     MAIL ID                   PWD
       0  rohan@kletech.com          rohan2003
       1  siri@kletech.com           siri2003
       2  smitha@kletech.com         smitha2003
       3  sagar@kletech.com          sagar2003
       4  prakashhegde@kletech.com   prakashkle



   2- Sign in 
       Messages are stored in loaddata.txt file as mentioned above. And
       when the program is run these 
       messages are stored into appropriate data structure.
       
       User gets the access to 
       1-Inbox
       2-Compose 
       3-Sent messages.[ ONLY THIS IS NOT SAVED IN FILE ]

4-MAPS:

[ WE HAVE NOT STORED THE HISTORY IN FILE SO ITS NOT PRESENT ONCE PROGRAM IS CLOSED ]

City names are stored in the cities.txt 

1.Search functionality - Asks user to enter source/destiny name, use   them as mentioned in the cities.txt;
[PLEASE USE 1ST LETTER AS CAPTILAL]

2.Print Nearby Cities - Similary for the print nearby cities name of city given as input must be same as mentioned in cities.txt 

3. Print Cities – prints the cities present in structure for refrenece


5-Calendar:

[WE HAVE NOT STORED THE EVENTS THAT ARE ADDED BY USER, SO ONCE THE PROGRAMS ENDS THE EVENTS ADDED BY USER WILL NOT BE STORED IN FILE]


 Events name with date, month and name are stored in events.txt

1.	Give date as input in format dd/mm/yyyy (dd mm yyyy for terminal)  

2.	 For deleting particular event give input as (dd / mm) 

  
      [DO LOG IN WITH YOUR MAIL ID IN MAIL FUNCTION  AND CHECK THE INBOX SIR]
      EMAIL ID: prakashhegde@kletech.com 
       
      PASSWORD: prakashkle
