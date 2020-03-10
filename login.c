#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
/*creating a user defined structure to store induvidual user's username and password*/
/*---------------------------------------------------------------------------------*/
typedef struct {
    char username[30];
    char password[30];
}User_details;
/*---------------------------------------------------------------------------------*/






/*A function that takes a string(given with variable password) as an argument and then addsa hexadecimal value
(given with variable key) to each character of string*/
/*-----------------------------------------------------------------------------------------------------------------*/
char *encrypt(char password[],int key)
{
    unsigned int i;
    for(i=0;i<strlen(password);++i)
    {
        password[i] = password[i] - key;
    }
    return  password;
}
/*-----------------------------------------------------------------------------------------------------------------*/







/*A function that takes a string(given with variable password) as an argument and then subtracts a hexadecimal value
(given with variable key) from  each character of string*/
/*-----------------------------------------------------------------------------------------------------------------*/

char *decrypt(char password[],int key)
{
    unsigned int i;
    for(i=0;i<strlen(password);++i)
    {
        password[i] = password[i] + key;
    }
    return password;
}
/*-----------------------------------------------------------------------------------------------------------------*/











/*Login function------------------------------------------------------------------------------------------------------
Basic functionality- Takes in username and password from user and compares with decrypted string in each line  in users.txt
Algorithm :
Step1 accept username and password from user
Step2 initialize a file pointer to read from users.txt
Step3 While reading each line in users.txt, split the string that you get from each line  in users.txt with delimiter ','
Step4 Decrypt the values and compare it with user provided details, if it matches break the loop and 
      return the line no(useful for referencing user details later*/

/*-----------------------------------------------------------------------------------------------------------------*/

int login()
{
    User_details* user=(User_details*) malloc(sizeof(User_details));
    printf("Enter the username");
    scanf("%s",user->username);  
    printf("Enter the password");
    scanf("%s",user->password);    
    FILE* filePointer;
    char line_string[100];
    filePointer = fopen("users.txt", "r");
    int count=0;
    while(fgets(line_string, 100, filePointer)) 
    {
        char * username= strtok(line_string, ",");
        char  * password= strtok(NULL, ",");
        strcpy(username,decrypt(username,0xFAC));
        strcpy(password,decrypt(password,0xFAC));
        printf("%s,%s\n",username,password);
        if(   strcmp(username,user->username)==0   &&  strcmp(password,user->password)==0    )
        {
            printf("success");
            return count;
        }    
        else
        {
            count=count+1;
        }   
    }
    fclose(filePointer);
    printf("fail");
    return -1;
}

/*END OF login function-----------------------------------------------------------------------------------------------------------------*/














/* User Register function------------------------------------------------------------------------------------------------------
Basic functionality- Takes in username and password from user , checks if it is a valid string and not there in users.txt,
                     if it satisifes, then the username and password is appended to users.txt after encryption
Algorithm :
Step1 accept username and password from user
Step2 initialize a file pointer to append to users.txt
Step3 check for a valid string and its not there in users.txt
Step4 append it by writing to the file*/

/*-----------------------------------------------------------------------------------------------------------------*/
int user_register()
{
    User_details* user=(User_details*) malloc(sizeof(User_details));
    printf("Enter the username");
    scanf("%s",user->username);  
    printf("Enter the password");
    scanf("%s",user->password); 
    strcpy(user->username,encrypt(user->username,0xFAC)); 
    strcpy(user->password,encrypt(user->password,0xFAC));     
    char ch, file_name[25];
    FILE *fp;
    fp = fopen("users.txt","a+"); 
    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    fprintf(fp,"%s,%s,%s",user->username,user->password, asctime(tm));
}
/*--END OF REGISTER Function----------------------------------------------------------------------------------------------*/





void main()
{
user_register();
login();

}

