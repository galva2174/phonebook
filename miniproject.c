#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>


typedef struct Contact {
    char name[50];
    char phone[15];
    int fav;
    struct Contact* next;
}Contact;

typedef struct Groups{
    char grpnam[100];
    Contact * grp;
    struct Groups* next;
}GRP;


GRP* allgrps = NULL;
Contact* mostRecentContact = NULL;
Contact* phonebook = NULL;
Contact* Grps = NULL;
int isdigit();

int caseInsensitiveCompare(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        if (toupper(*str1) != toupper(*str2)) {
            return 0; // Not equal
        }
        str1++;
        str2++;
    }
    return *str1 == *str2;
}

int isValidPhoneNumber(const char phone[]) {
    for (int i = 0; i < 10; i++) {
        if (!isdigit(phone[i])) {
            return 0;
        }
    }
    return 1; 
}

Contact* createContact(const char name[], const char phone[]) {
    if (strlen(phone) != 10 || !isValidPhoneNumber(phone)) {
        printf("Invalid phone number. Please enter a ten-digit number\n");
        return NULL;
    }
    Contact* newContact = (Contact*)malloc(sizeof(Contact));
    if (newContact != NULL) {
        strcpy(newContact->name, name);
        strcpy(newContact->phone, phone);
        newContact->fav = 0;
        newContact->next = NULL;
    }
    return newContact;
}

Contact* createfavContact(const char name[], const char phone[]) {
    if (strlen(phone) != 10 || !isValidPhoneNumber(phone)) {
        printf("Invalid phone number. Please enter a ten-digit number\n");
        return NULL;
    }
    Contact* newContact = (Contact*)malloc(sizeof(Contact));
    if (newContact != NULL) {
        strcpy(newContact->name, name);
        strcpy(newContact->phone, phone);
        newContact->fav = 1;
        newContact->next = NULL;
    }
    return newContact;
}

Contact* searchContact(const char name[]) {
    Contact* current = phonebook;

    while (current != NULL) {
        if (caseInsensitiveCompare(current->name, name)) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Contact* searchnum(const char num[]) {
    Contact* current = phonebook;
    while (current != NULL) {
        if (strcmp(current->phone, num) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void insertContact(Contact** head, const char name[], const char phone[], int f) {
    if (searchContact(name) != NULL) {
        printf("Contact with the name '%s' already exists. Cannot insert.\n", name);
        return;
    }

    Contact* newContact;
    if (f == 0) {
        newContact = createContact(name, phone);
    } else {
        newContact = createfavContact(name, phone);
    }

    if (newContact == NULL) {
        printf("Contact not stored\n");
        return;
    }

    if (*head == NULL || strcasecmp(name, (*head)->name) < 0) {
        newContact->next = *head;
        *head = newContact;
    } else {
        Contact* current = *head;
        while (current->next != NULL && strcasecmp(name, current->next->name) > 0) {
            current = current->next;
        }
        newContact->next = current->next;
        current->next = newContact;
    }
    mostRecentContact = newContact;
    printf("Contact added successfully.\n");
}

void RmoveContact(struct Contact** head, const char name[]) {
    struct Contact* current = *head;
    struct Contact* prev = NULL;
    
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Contact removed successfully.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Contact not found.\n");
}

void removebynum(struct Contact** head, const char numb[]) {
    struct Contact* current = *head;
    struct Contact* prev = NULL;
    
    while (current != NULL) {
        if (strcmp(current->phone, numb) == 0) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Contact removed successfully.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Contact not found.\n");
}

void updateContact(const char name[]) {
    Contact* contactToUpdate = searchContact(name);

    if (contactToUpdate == NULL) {
        printf("Contact with the name '%s' not found. Cannot update.\n", name);
        return;
    }

    char newPhone[15];
    char newnam[50];
    char in[1];
    printf("Enter the new name for %s: ", name);
    scanf("%s", newnam);
    printf("Enter the new phone number for %s: ", name);
    scanf("%s", newPhone);
   

    strcpy(contactToUpdate->phone, newPhone);
    strcpy(contactToUpdate->name, newnam);
    if(contactToUpdate->fav == 0){
       printf("Do u want to add %s to favourites (y/n): ", name);
       scanf("%s",in);
       if(strcmp(in,"y") == 0){
       contactToUpdate->fav = 1;}
    }
    else if(contactToUpdate->fav == 1){
       printf("Do u want to remove %s from favourites (y/n): ", name);
       scanf("%s",in);
       if(strcmp(in,"y") == 0){
       contactToUpdate->fav = 0;}
    }
    printf("Contact updated successfully.\n");
}

void updateContactnum(const char num[]) {
    Contact* contactToUpdate = searchnum(num);

    if (contactToUpdate == NULL) {
        printf("Contact with the number '%s' not found. Cannot update.\n", num);
        return;
    }

    char newPhone[15];
    char newnam[50];
    char in[1];
    printf("Enter the new name for %s: ", contactToUpdate->name);
    scanf("%s", newnam);
    printf("Enter the new phone number for %s: ", contactToUpdate->name);
    scanf("%s", newPhone);
   

    strcpy(contactToUpdate->phone, newPhone);
    strcpy(contactToUpdate->name, newnam);
    if(contactToUpdate->fav == 0){
       printf("Do u want to add %s to favourites (y/n): ", contactToUpdate->name);
       scanf("%s",in);
       if(strcmp(in,"y") == 0){
       contactToUpdate->fav = 1;}
    }
    else if(contactToUpdate->fav == 1){
       printf("Do u want to remove %s from favourites (y/n): ", contactToUpdate->name);
       scanf("%s",in);
       if(strcmp(in,"y") == 0){
       contactToUpdate->fav = 0;}
    }
    printf("Contact updated successfully.\n");
}

void totalContacts() {
    int count = 0;
    Contact* current = phonebook;
    while (current != NULL){
        count+=1;
        current = current->next;
    }
    printf("Number of Contacts : %d\n\n",count);
}


void displayContacts(Contact* head) {
    int count = 0;
    Contact* current = head;
    while (current != NULL) {
        count += 1;
        current = current->next;
    }
    if (count == 0) {
        printf("There are no contacts\n\n");
    } else {
        printf("\nPhonebook Contacts:\n");
        Contact* current = head;
        while (current != NULL) {
            printf("Name: %s, Phone: %s\n", current->name, current->phone);
            current = current->next;
        }
    }
}

void displayGrpContacts(GRP * head) {
    int count = 0;
    GRP* current = head;
    while (current != NULL){
        count+=1;
        current = current->next;
    }
    if(count == 0){
        printf("There are no contacts\n\n");
    }
    else{
    GRP* current = head;
    while (current != NULL){
        Contact * grpp = current->grp;
        printf("%s : \n",current->grpnam);
        while(grpp != NULL){
        printf("Name: %s, Phone: %s\n", grpp->name, grpp->phone);
        grpp = grpp->next;}
        current = current->next;
    }
    }
}

void displaySingleGroup(GRP* head, const char groupName[]) {
    GRP* current = head;
    while (current != NULL) {
        if (strcmp(current->grpnam, groupName) == 0) {
            displayGrpContacts(current);
            return;
        }
        current = current->next;
    }
    printf("Group '%s' not found.\n", groupName);
}


void favContacts() {
    int count = 0;
    Contact* current = phonebook;
    while (current != NULL){
        if(current->fav == 1){
          count+=1;
        }
        current = current->next;
    }
    if(count == 0){
        printf("There are no Favourite contacts\n\n");
    }
    else{
    printf("\nFavourite Contacts:\n");
    Contact* temp = phonebook;
    while (temp != NULL) {
        if(temp->fav == 1){
          printf("Name: %s, Phone: %s\n", temp->name, temp->phone);
        }
        temp = temp->next;
    }
    }
}

void mostrctcontact(){
printf("Most Recent Contact Added:\n");
printf("Name:%s, Phone:%s",mostRecentContact->name,mostRecentContact->phone);
}

void freeContacts(Contact** head) {
    while (*head != NULL) {
        Contact* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    printf("All contacts removed successfully.\n");
}


void addToGroup(Contact* contact, const char groupName[]) {
    GRP* current = allgrps;
    while (current != NULL) {
        if (strcmp(current->grpnam, groupName) == 0) {
            Contact* newContact = (Contact*)malloc(sizeof(Contact));
            strcpy(newContact->name, contact->name);
            strcpy(newContact->phone, contact->phone);
            newContact->fav = contact->fav;
            newContact->next = current->grp;
            current->grp = newContact;
            printf("Contact added to the group successfully.\n");
            return;
        }
        current = current->next;
    }
    printf("Group '%s' not found.\n", groupName);
}

void displayGroups() {
    GRP* current = allgrps;
    while (current != NULL) {
        printf("%s\n", current->grpnam);
        current = current->next;
    }
}

void displayGroupContacts(const char groupName[]) {
    GRP* current = allgrps;
    while (current != NULL) {
        if (strcmp(current->grpnam, groupName) == 0) {
            Contact* temp = current->grp;
            if (temp == NULL) {
                printf("\nNo contacts in group '%s'.\n", groupName);
                return;
            }
            printf("\nContacts in group '%s':\n", groupName);
            while (temp != NULL) {
                printf("Name: %s, Phone: %s\n", temp->name, temp->phone);
                temp = temp->next;
            }
            return;
        }
        current = current->next;
    }
    printf("Group '%s' not found.\n", groupName);
}

void removeFromGroup(const char contactName[], const char groupName[]) {
    GRP* current = allgrps;
    while (current != NULL) {
        if (strcmp(current->grpnam, groupName) == 0) {
            Contact* temp = current->grp;
            Contact* prev = NULL;
            while (temp != NULL) {
                if (strcmp(temp->name, contactName) == 0) {
                    if (prev == NULL) {
                        current->grp = temp->next;
                    } else {
                        prev->next = temp->next;
                    }
                    free(temp);
                    printf("Contact removed from the group successfully.\n");
                    return;
                }
                prev = temp;
                temp = temp->next;
            }
            printf("Contact '%s' not found in group '%s'.\n", contactName, groupName);
            return;
        }
        current = current->next;
    }
    printf("Group '%s' not found.\n", groupName);
}

void updateInGroup(const char contactName[], const char groupName[]) {
    GRP* current = allgrps;
    while (current != NULL) {
        if (strcmp(current->grpnam, groupName) == 0) {
            Contact* temp = current->grp;
            while (temp != NULL) {
                if (strcmp(temp->name, contactName) == 0) {
                    updateContact(contactName); // You can modify this to update specific fields
                    printf("Contact updated in the group successfully.\n");
                    return;
                }
                temp = temp->next;
            }
            printf("Contact '%s' not found in group '%s'.\n", contactName, groupName);
            return;
        }
        current = current->next;
    }
    printf("Group '%s' not found.\n", groupName);
}

void createGroup(const char groupName[]) {
    GRP* newGroup = (GRP*)malloc(sizeof(GRP));
    strcpy(newGroup->grpnam, groupName);
    newGroup->grp = NULL;
    newGroup->next = allgrps;
    allgrps = newGroup;
    printf("Group '%s' created successfully.\n", groupName);
}

void createDefaultGroups() {
    createGroup("home");
    createGroup("work");
    createGroup("friends");
}

int main() {
    createDefaultGroups();
    while (1) {
        printf("\nPhonebook Application Menu:\n");
        printf("1.  Add Contact\n");
        printf("2.  Search Contact\n");
        printf("3.  Display Contacts\n");
        printf("4.  Remove Contact\n");
        printf("5.  Update Contact\n");
        printf("6.  Clear all contacts\n");
        printf("7.  View Recently added Contact\n");
        printf("8.  Number of Contacts\n");
        printf("9.  Favourite Contacts\n");
        printf("10. View and edit Group\n");
        printf("0. Exit\n\n");

        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                freeContacts(&phonebook);
                exit(0);
            case 1: {
                char name[50];
                char phone[15];
                char fav[1];
                printf("Enter name : ");
                scanf("%s", name);
                printf("Favourite? (y/n) :");
                scanf("%s", fav);
                if(strcmp(fav,"y") == 0){
                    printf("Enter phone number : ");
                    scanf("%s", phone);
                    insertContact(&phonebook, name, phone, 1);
                }
                else if(strcmp(fav,"Y") == 0){
                    printf("Enter phone number : ");
                    scanf("%s", phone);
                    insertContact(&phonebook, name, phone, 1);
                }
                else{
                    printf("Enter phone number : ");
                    scanf("%s", phone);
                    insertContact(&phonebook, name, phone, 0);
                }
                break;
            }
            case 2: {
                char nu[10];
                char rslt[1];
                char name[50];
                printf("Search by Name(y/n) : \n");
                scanf("%s", rslt);
                if(strcmp(rslt,"y")==0){
                printf("Enter name to search: ");
                scanf("%s", name);
                Contact* result = searchContact(name);
                if (result != NULL) {
                    printf("Contact found - Name: %s, Phone: %s\n", result->name, result->phone);
                } else {
                    printf("Contact with name '%s' not found\n",name);
                }
                break;}
                else{
                   printf("Enter number to search: ");
                   scanf("%s", nu);
                   Contact* result = searchnum(nu);
                   if (result != NULL) {
                       printf("Contact found - Name: %s, Phone: %s\n", result->name, result->phone);
                   } else {
                       printf("Contact with phone number '%s' not found\n", nu);
                   }
                   break;  
                }

            }
            case 3:
                displayContacts(phonebook);
                break;
            case 4: {
                char ans[1];
                char name[50];
                char numb[10];
                printf("Remove by Name(y/n) : \n");
                scanf("%s",ans);
                if(strcmp(ans,"y")==0){
                printf("Enter name to remove: ");
                scanf("%s", name);
                RmoveContact(&phonebook, name);
                break;}
                else{
                    printf("Enter the number of Contact : \n");
                    scanf("%s",numb);
                    removebynum(&phonebook,numb);
                    break;
                }
            }
            case 5:{
                char nam[1];
                char olname[50];
                char num[10];
                printf("Update by Name(y/n) : \n");
                scanf("%s",nam);
                if(strcmp(nam,"y")==0){
                printf("Enter name of contact : ");
                scanf("%s", olname);
                updateContact(olname);
                break;}
                else{
                    printf("Enter number of contact : ");
                    scanf("%s", num);
                    updateContactnum(num);
                break;
                }
            }
            case 6:
                freeContacts(&phonebook);
                break;
            case 7:
                mostrctcontact();
                break;
            case 8:
                totalContacts();
                break;
            case 9:
                favContacts();
                break;
            case 10: {
                int ans = 0;
                int chce;
                 while (ans == 0) {
                    printf("\nGroups: \n");
                    printf("1. View the Groups\n");
                    printf("2. Add contact to Group\n");
                    printf("3. Remove contact from Group\n");
                    printf("4. Update contact in Group\n");
                    printf("5. View Group Contacts\n");
                    printf("0. Exit\n");
                    printf("Enter your choice: \n");
                    scanf("%d", &chce);
                    switch (chce) {
                        case 1:
                            displayGroups();
                            break;
                        case 2: {
                            char groupName[100];
                            char contactName[50];
                            printf("Enter group name: ");
                            scanf("%s", groupName);
                           printf("Enter contact name to add to group: ");
                            scanf("%s", contactName);
                            Contact* contact = searchContact(contactName);
                            if (contact != NULL) {
                                addToGroup(contact, groupName);
                            } else {
                                printf("Contact '%s' not found.\n", contactName);
                            }
                            break;
                        }
                        case 3: {
                            char groupName[100];
                            char contactName[50];
                            printf("Enter group name: ");
                            scanf("%s", groupName);
                            printf("Enter contact name to remove from group: ");
                            scanf("%s", contactName);
                            removeFromGroup(contactName, groupName);
                            break;
                        }
                        case 4: {
                            char groupName[100];
                            char contactName[50];
                            printf("Enter group name: ");
                            scanf("%s", groupName);
                            printf("Enter contact name to update in group: ");
                            scanf("%s", contactName);
                            updateInGroup(contactName, groupName);
                            break;
                        }
                        case 5: {
                            char groupName[100];
                            printf("Enter group name to view contacts: ");
                            scanf("%s", groupName);
                            displayGroupContacts(groupName);
                            break;
                        }
                        case 0:
                            ans = 1;
                            break;
                        default:
                            printf("Invalid choice. Please try again.\n");
                    }
                }
                break;
            }
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}