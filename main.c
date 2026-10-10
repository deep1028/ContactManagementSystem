#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Contact{
    char id[20];
    char name[50];
    char phone[20];
    char email[100];
    char address[100];
    char category[30];
};

struct Node{
    struct Contact contact;
    struct Node *next;
};

struct Node *start = NULL;

void addContact(){
    struct Node *newNode;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    if(newNode == NULL){
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Contact ID: ");
    scanf("%s", newNode -> contact.id);

    printf("Enter Contact Name: ");
    scanf(" %[^\n]", newNode -> contact.name);

    printf("Enter Phone Number: ");
    scanf("%s", newNode -> contact.phone);

    printf("Enter EMail ID: ");
    scanf("%s", newNode -> contact.email);

    printf("Enter Address: ");
    scanf(" %[^\n]", newNode -> contact.address);

    printf("Enter Category: ");
    scanf(" %[^\n]", newNode -> contact.category);

    newNode -> next = NULL;

    if(start == NULL){
        start = newNode;
    } else {
        struct Node *temp = start;

        while(temp -> next != NULL){
            temp = temp -> next;
        }
        temp -> next = newNode;
    }

    printf("Contact added Successfully!\n");
}

void displayContacts(){
    if(start == NULL){
        printf("No Contacts available.\n");
        return;
    }

    struct Node *temp = start;

    while(temp != NULL){
        printf("\n-------------------------------\n");
        printf("Contact ID : %s\n", temp -> contact.id);
        printf("Name       : %s\n", temp -> contact.name);
        printf("Phone Number: %s\n", temp -> contact.phone);
        printf("EMail ID   : %s\n", temp -> contact.email);
        printf("Address    : %s\n", temp -> contact.address);
        printf("Category   : %s\n", temp -> contact.category);

        temp = temp -> next; 
    }
    printf("-----------------------------\n");
}

void deleteContact(){
    char id[20];
    printf("Enter Contact ID to delete: ");
    scanf("%s", id);

    struct Node *temp = start;
    struct Node *prev = NULL;

    while(temp != NULL && strcmp(temp -> contact.id, id) != 0){
        prev = temp;
        temp = temp -> next;
    }

    if(temp == NULL){
        printf("Contact not found.\n");
        return;
    }

    if(prev == NULL){
        start = temp -> next;
    } else {
        prev -> next = temp -> next;
    }
    free(temp);
    printf("Contact deleted Successfully!\n");
}

int main(){
    addContact();
    addContact();
    addContact();

    displayContacts();

    deleteContact();

    displayContacts();
    return 0;
}