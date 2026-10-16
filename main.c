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

#define TABLE_SIZE 10

struct HashNode{
    struct Node *contact;
    struct HashNode *next;
};

struct HashNode *hashTable[TABLE_SIZE] = {NULL};

struct Node *start = NULL;

int nextId = 1;

int phoneExists(char phone[]){
    struct Node *temp = start;
    while(temp != NULL){
        if(strcmp(temp -> contact.phone, phone) == 0){
            return 1;
        }
        temp = temp -> next;
    }
    return 0;
}

int emailExists(char email[]){
    struct Node *temp = start;
    while(temp != NULL){
        if(strcmp(temp -> contact.email, email) == 0){
            return 1;
        }
        temp = temp -> next;
    }
    return 0;
}

void addContact(){
    struct Node *newNode;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    if(newNode == NULL){
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Contact Name: ");
    scanf(" %[^\n]", newNode -> contact.name);

    printf("Enter Phone Number: ");
    scanf("%s", newNode -> contact.phone);

    if(phoneExists(newNode -> contact.phone)){
        printf("Error: Phone number already exists!\n");
        free(newNode);
        return;
    }

    printf("Enter Mail ID: ");
    scanf("%s", newNode -> contact.email);

    if(emailExists(newNode -> contact.email)){
        printf("Error: Email already exists!\n");
        free(newNode);
        return;
    }

    sprintf(newNode -> contact.id, "C%03d", nextId++);
    printf("Generated Contact ID: %s\n", newNode -> contact.id);

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

    insertHash(newNode);
    printf("Contact added successfully!\n");
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
    char name[50];

    printf("Enter Contact Name to delete: ");
    scanf(" %[^\n]", name);

    struct Node *temp = start;
    struct Node *matches[100];

    int count = 0;

    while(temp != NULL){
        if(strcmp(temp -> contact.name, name) == 0){
            if(count < 100){
                matches[count] = temp;
                count++;
            }
        }
        temp = temp -> next;
    }
    if(count == 0){
        printf("Contact not found.\n");
        return;
    }
    if(count == 1){
        temp = matches[0];

        printf("\nContact found:\n");
        printf("ID     : %s\n", temp -> contact.id);
        printf("Name   : %s\n", temp -> contact.name);
        printf("Phone  : %s\n", temp -> contact.phone);
        printf("Email  : %s\n", temp -> contact.email);

        char choice;

        printf("\nAre you sure you want to delete this contact? (Y/N): ");
        scanf(" %c", &choice);

        if(choice == 'Y' || choice == 'N'){
            struct Node *curr = start;
            struct Node *prev = NULL;

            while(curr != NULL && curr != temp){
                prev = curr;
                curr = curr -> next;
            }
            if(prev == NULL){
                start = curr -> next;
            } else {
                prev -> next = curr -> next;
            }
            free(curr);
            printf("Contact deleted successfully!\n");
        } else {
            printf("Deletion cancelled.\n");
        }
        return;
    }
    printf("\nMultiple contacts found:\n");
    
    for(int i = 0; i < count; i++){
        printf("\n%d. %s | %s | %s\n", 
            i+1,
            matches[i] -> contact.name,
            matches[i] -> contact.phone,
            matches[i] -> contact.email);
    }

    int choice;

    printf("\nEnter contact number to delete: ");
    scanf("%d", &choice);
    if(choice < 1 || choice > count){
        printf("Invalid choice.\n");
        return;
    }
    temp = matches[choice - 1];

    struct Node *curr = start;
    struct Node *prev = NULL;

    while(curr != NULL && curr != temp){
        prev = curr;
        curr = curr -> next;
    }
    if(prev == NULL){
        start = curr -> next;
    } else {
        prev -> next = start -> next;
    }
    free(curr);
    printf("Contact deleted successfully!\n");

}

void updateContact(){
    char name[50];

    printf("Enter Contact Name to update: ");
    scanf(" %[^\n]", name);

    struct Node *temp = start;
    struct Node *matches[100];

    int count = 0;

    while(temp != NULL){
        if(strcmp(temp -> contact.name, name) == 0){
            if(count < 100){
                matches[count] = temp;
                count++;
            }
        }
        temp = temp -> next;
    }

    if(count == 0){
        printf("Contact not found.\n");
        return;
    }

    if(count == 1){
        temp = matches[0];

        printf("\nContact found:\n");
        printf("ID       : %s\n", temp->contact.id);
        printf("Name     : %s\n", temp->contact.name);
        printf("Phone    : %s\n", temp->contact.phone);
        printf("Email    : %s\n", temp->contact.email);
        printf("Address  : %s\n", temp->contact.address);
        printf("Category : %s\n", temp->contact.category);
    } else {
        printf("\nMultiple contacts found:\n");

        for(int i = 0; i < count; i++){
            printf("\n%d. ID: %s | Name: %s | Phone: %s | Email: %s\n",
                i + 1,
                matches[i] -> contact.id,
                matches[i] -> contact.name,
                matches[i] -> contact.phone,
                matches[i] -> contact.email);
        }
        int choice;

        printf("\nEnter contact number to update: ");
        scanf("%d", &choice);

        if(choice < 1 || choice > count){
            printf("Invalid choice\n");
            return;
        }
        temp = matches[choice - 1];
    }
    printf("\nEnter new details:\n");

    char newPhone[20];
    char newEmail[100];

    printf("Enter new Phone Number: ");
    scanf("%s", newPhone);

    struct Node *check = start;

    while(check != NULL){
        if(check != temp && strcmp(check -> contact.phone, newPhone) == 0){
            printf("Error: Phone number already exists!\n");
            return;
        }
        check = check -> next;
    }
    printf("Enter new Email ID: ");
    scanf("%s", newEmail);

    check = start;

    while(check != NULL){
        if(check != temp && strcmp(check -> contact.email, newEmail) == 0){
            printf("Error: Email already exists!\n");
            return;
        }
        check = check -> next;

    }

    printf("Enter new Name: ");
    scanf(" %[^\n]", temp -> contact.name);

    strcpy(temp -> contact.phone, newPhone);
    strcpy(temp -> contact.emailm, newEmail);

    printf("Enter new Address: ");
    scanf(" %[^\n]", temp -> contact.address);

    printf("Enter new Category: ");
    scanf(" %[^\n]", temp -> contact.category);

    printf("\nContact updated successfully!\n");
}

int hashFunction(char phone[]){
    int sum = 0;
    for(int i = 0; phone[i] != '\0'; i++){
        sum += phone[i];
    }

    return sum % TABLE_SIZE;
}

void insertHash(struct Node *contact){
    int index = hashFunction(contact -> contact.phone);

    struct HashNode *newNode;

    newNode = (struct HashNode *)malloc(sizeof(struct HashNode));

    if(newNode == NULL){
        printf("Hash memory allocation failed!\n");
        return;
    }

    newNode -> contact = contact;
    newNode -> next = hashTable[index];
    hashTable[index] = newNode;
}

void searchByPhone(){
    char phone[20];

    printf("Enter Phone Number to search: ");
    scanf("%s", phone);

    int index = hashFunction(phone);

    struct HashNode *temp = hashTable[index];

    while(temp != NULL){
        if(strcmp(temp -> contact -> contact.phone, phone) == 0){
            printf("\nContact Found!\n");
            printf("ID       : %s\n", temp->contact->contact.id);
            printf("Name     : %s\n", temp->contact->contact.name);
            printf("Phone    : %s\n", temp->contact->contact.phone);
            printf("Email    : %s\n", temp->contact->contact.email);
            printf("Address  : %s\n", temp->contact->contact.address);
            printf("Category : %s\n", temp->contact->contact.category);

            return;
        }
        temp = temp -> next;
    }
    printf("Contact not found.\n");
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