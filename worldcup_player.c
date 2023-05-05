//Written by Otis Ding
//Student ID: 251220811
//This program covers the player portion of the database using a linked list

//Our include statements for our header file and the c libraries we'll be using
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "worldcup_player.h"

//Node structure for our players
struct playNode{

    //Defining all the fields we want this structure to have
    int code;
    char name[NAME_LEN + 1];
    int age;
    char club[CLUB_LEN + 1];
    struct playNode *next;
};

//Declaring a first variable to represent the start/head of the linked list
struct playNode *first = NULL;

//Insert function
//Prompts user for input and creates a new node of the linked list to store the data of a new player
void insert(){

    //Declaring some variables for user input
    int trialCode;
    char name[NAME_LEN + 1];
    char clubName[CLUB_LEN + 1];
    int trialAge;
    char space;

    //Making a new node where we'll store the user input
    struct playNode *newNode;
    newNode = malloc(sizeof(struct playNode));

    //Prompts user for user input
    printf("Please enter the player code: ");
    scanf("%d", &trialCode);

    //Checks if input is valid
    if (trialCode < 0){
        printf("Error: Code cannot be negative\n");
        return;
    }

    //Iterates through the linked list comparing codes to make sure the new code is unique
    for (struct playNode *p = first; p != NULL; p = p->next){
        if (trialCode == p->code){
            printf("Error: Duplicate Player Code\n");
            return;
        }
    }
    //Stores the new code into the new node's field
    newNode->code = trialCode;

    //Prompts the user for the player's name
    printf("Please enter the player's name: ");

    //Uses our own read_line function to store the user input into our variable
    read_line(name, NAME_LEN + 1);

    //Copies the user's input string into our new node's name field
    strcpy(newNode->name, name);

    //Prompts the user for the player's age
    printf("Please enter the player's age: ");
    scanf("%d", &trialAge);
    //Checks if the age is valid
    if ((trialAge < 17) || (trialAge > 99)){
        printf("Error: Invalid Age\n");
        return;
    }

    //Stores the age into new node's age field
    newNode->age = trialAge;
    
    //Using the same method above for the name
    printf("Please enter the professional club affiliation of the player: ");
    read_line(clubName, CLUB_LEN + 1);
    strcpy(newNode->club, clubName);

    //inserts the new node into the front of the linked list
    newNode->next = first;
    first = newNode;
}

//Search function
//Takes user input and searches for the player with the inputed player code, then prints it
void search(){
    int input;

    //Prompts the user for the player's code
    printf("Please enter the code of the player you would like to see: ");
    scanf("%d", &input);

    //Iterates through the linked list until the player's code is found
    for (struct playNode *p = first; p != NULL; p = p->next){
        if (p->code == input){
            //Outputs the data of the specified player
            printf("Player Code   Player Name                                          Player Age   Club Affiliation\n");
            printf("%-13d %-52s %-12d %s\n", p->code, p->name, p->age, p->club);
            return;
        }
    }

    //If the entire list is iterated through and no output occurs, then the inputed code doesn't exist in the list
    printf("Error: Code not found in database\n");
    return;
}

//Update function
//Allows the user to input a player code and update the player with that code
void update(){

    //Same variables as insert()
    int input;
    char name[NAME_LEN + 1];
    char clubName[CLUB_LEN + 1];
    int trialAge;

    //Prompts the user for the code to update
    printf("Please enter the code of the player you would like to update: ");
    scanf("%d", &input);

    //For loop to iterate through the list until the player we want is found
    for (struct playNode *p = first; p != NULL; p = p->next){

        //Checks if the player code matches the input
        if (p->code == input){

            //Same steps as in insert, as we reassign the values of the node's fields
            printf("Please enter the updated player's name: ");
            read_line(name, NAME_LEN + 1);
            strcpy(p->name, name);

            printf("Please enter the updated player's age: ");
            scanf("%d", &trialAge);
            if ((trialAge < 17) || (trialAge > 99)){
                printf("Error: Invalid Age\n");
                return;
            }
            p->age = trialAge;
            

            printf("Please enter the updated professional club affiliation of the player: ");
            read_line(clubName, CLUB_LEN + 1);
            strcpy(p->club, clubName);
        }
    }
}

//Print function
//Outputs the entire list of players
void print(){

    //Headers
    printf("Player Code   Player Name                                          Player Age   Club Affiliation\n");
    
    //For loop go through the entire linked list and output each one
    for (struct playNode *p = first; p != NULL; p = p->next){
        printf("%-13d %-76s %-12d %-s", p->code, p->name, p->age, p->club);
        printf("\n");
    }
}

//Delete function
//Allows the user to select a player code to delete from the database
void delete(){

    //Declare variables for the user input, and the pointers we'll use to delete the specified node
    int input;
    struct playNode *curr, *prev;

    //Gets user input
    printf("Please enter the code for the player you would like to delete: ");
    scanf("%d", &input);

    //For loop to continue until curr lands on the node we want to delete
    for (curr = first, prev = NULL; curr != NULL && curr->code != input; prev = curr, curr = curr->next);
    
    //If curr is null then that means the inputed code doesn't exist in the database
    if (curr == NULL){
        printf("Error: Player Code not found");
        return;
    }

    //If prev is null then that means the node we want to delete is the first one
    if (prev == NULL){
        //We just reassign first to be the second node in the list, thus effectively deleting the first node
        first = first->next;
    } else {
        //Otherwise we reassign prev's next to be the node after curr, thus skipping over curr's node
        prev->next = curr->next;
    }

    //We then free up curr's memory, and return to end the function
    free(curr);
    return;
}

//Read_line function
//Used to take in user input even when strings are involved
void read_line(char str[], int n){
    int ch;
    int i= 0;

    //has ch getchar() first to take the user's \n character that they use after their last input
    ch = getchar();
    ch = 'a';

    //Continues to getchar() and add it to the string until the user enters a new line character
    while (ch != '\n'){
        ch = getchar();
        if (i < n){
            str[i++] = ch;
        }
    }
    //Closes off the string
    str[i] = '\0';
}

//Player function
//Function that allows the user to select any of the available functions related to the players database
void player(){

    //Variable for user input
    char input;

    //Notify players of where they are in the program
    printf("You have chosen to access the players.\n");

    //Prompts the user for input
    printf("Please enter a command (Players): ");
    scanf(" %c", &input);

    //Switch statement to go to the specified function and filter out bad input
    switch(input){
        case 'i': insert();
            break;
        case 's': search();
            break;
        case 'u': update();
            break;
        case 'p': print();
            break;
        case 'd': delete();
            break;
        default: printf("Illegal Code\n");
    }

    printf("\n");


}