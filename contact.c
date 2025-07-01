#include "contact.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "file.h"

int validateName(const char *name) 
{ 
    for (int i = 0; name[i] != '\0'; i++) 
    {
        if (!(isalpha(name[i]) || isspace(name[i]))) 
        {
            return 0; 
        }
    }
    return 1; 
}

int validatePhoneNumber(const char *phone) 
{
    if (strlen(phone) != 10) 
    {
        return 0; 
    }
    for (int i = 0; phone[i] != '\0'; i++) 
    {
        if (!isdigit(phone[i])) 
        {
            return 0; 
        }
    }
    return 1; 
}

int validateEmail(const char *email) 
{
    int len = strlen(email);
    const char *gmailDomain = "@gmail.com";

    if (len < strlen(gmailDomain) || strcmp(email + len - strlen(gmailDomain), gmailDomain) != 0)
    {
        return 0;
    }

    for (int i = 0; i < len - strlen(gmailDomain); i++)
    {
        if (!(islower(email[i]) || isdigit(email[i]) || email[i] == '_')) 
        {
            return 0; 
        }
    }
    return 1; 
}


void initialize(AddressBook *addressBook)
 {
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook); 
}

void save(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook);  
}

void createContact(AddressBook *addressBook)
 {
    char name[50];
    char number[20];
    char mail[50];

    do 
    {
        printf("Enter the name: ");
        scanf(" %[^\n]", name);
        if (!validateName(name))
        {
            printf("Error: Name must contain only alphabets and spaces.\n");
        }
    } while (!validateName(name));

    do 
    {
        printf("Enter the phone number: ");
        scanf("%s", number);
        if (!validatePhoneNumber(number)) 
        {
            printf("Error: Phone number must be exactly 10 digits.\n");
        }
    } while (!validatePhoneNumber(number));

    do 
    {
        printf("Enter mail id: ");
        scanf("%s", mail);
        if (!validateEmail(mail)) 
        {
            printf("Error: Email must contain only lowercase letters, digits, underscores, and end with '@gmail.com'.\n");
        }
    } while (!validateEmail(mail));

    int isDuplicate = 0;
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].name, name) == 0 ||strcmp(addressBook->contacts[i].phone, number) == 0 ||strcmp(addressBook->contacts[i].email, mail) == 0) 
        {
            isDuplicate = 1;
            printf("Warning: A contact with the same ");
            if (strcmp(addressBook->contacts[i].name, name) == 0)
            {
                printf("name ");
            }
            if (strcmp(addressBook->contacts[i].phone, number) == 0) 
            {
                printf("phone number ");
            }
            if (strcmp(addressBook->contacts[i].email, mail) == 0) 
            {
                printf("email ");
            }
            printf("already exists.\n");

            char confirm[10];
            printf("Do you want to proceed and create this contact anyway? (Yes/No): ");
            scanf("%s", confirm);
            if (strcasecmp(confirm, "No") == 0) 
            {
                printf("Contact creation canceled.\n");
                return;  
            }
            break;  
        }
    }

    int index = addressBook->contactCount;
    strcpy(addressBook->contacts[index].name, name);
    strcpy(addressBook->contacts[index].phone, number);
    strcpy(addressBook->contacts[index].email, mail);
    addressBook->contactCount++;

    save(addressBook);
    printf("Contact created successfully!\n");
}



void searchContact(AddressBook *addressBook) 
{
    int searchChoice;
    char searchTerm[50];

    do 
    {
        printf("Search options\n");
        printf("1. Search by Name\n");
        printf("2. Search by Phone Number\n");
        printf("3. Search by Email\n");
        printf("Enter your choice: ");
        scanf("%d", &searchChoice);

        if (searchChoice < 1 || searchChoice > 3) 
        {
            printf("Error: Invalid choice. Please enter a valid option.\n");
        }
    } while (searchChoice < 1 || searchChoice > 3);  

    printf("Enter search term: ");
    scanf(" %[^\n]", searchTerm);
    searchTerm[strcspn(searchTerm, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if ((searchChoice == 1 && strcasecmp(addressBook->contacts[i].name, searchTerm) == 0) ||(searchChoice == 2 && strcmp(addressBook->contacts[i].phone, searchTerm) == 0) ||(searchChoice == 3 && strcmp(addressBook->contacts[i].email, searchTerm) == 0))
            {
            
            if (found == 0) 
            {
                printf("\n");
            }

            printf("Contact Found: %s\n", addressBook->contacts[i].name);
            printf("Phone: %s\n", addressBook->contacts[i].phone);
            printf("Email: %s\n", addressBook->contacts[i].email);
            printf("------------------------------------------\n");
            found = 1;
        }
    }

    if (!found) 
    {
        printf("No contacts found matching the search term.\n");
    }
}




void editContact(AddressBook *addressBook) 
{
    int editChoice;
    char searchTerm[50];

    do 
    {
        printf("Edit options\n");
        printf("1. Edit by Name\n");
        printf("2. Edit by Phone Number\n");
        printf("3. Edit by Email\n");
        printf("Enter your choice: ");
        scanf("%d", &editChoice);

        if (editChoice < 1 || editChoice > 3) 
        {
            printf("Error: Invalid choice. Please enter a valid option.\n");
        }
    } while (editChoice < 1 || editChoice > 3);  

    printf("Enter the search term: ");
    scanf(" %[^\n]", searchTerm);
    searchTerm[strcspn(searchTerm, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if ((editChoice == 1 && strcasecmp(addressBook->contacts[i].name, searchTerm) == 0) ||(editChoice == 2 && strcmp(addressBook->contacts[i].phone, searchTerm) == 0) ||(editChoice == 3 && strcmp(addressBook->contacts[i].email, searchTerm) == 0)) 
        {
            found = 1;
            printf("Contact found: %s, %s, %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

            if (editChoice == 1) 
            {
                printf("Enter new name: ");
                scanf(" %[^\n]", addressBook->contacts[i].name);
            } 
            else if (editChoice == 2) 
            {
                printf("Enter new phone number: ");
                scanf("%s", addressBook->contacts[i].phone);
            } 
            else if (editChoice == 3) 
            {
                printf("Enter new email: ");
                scanf("%s", addressBook->contacts[i].email);
            }

            save(addressBook);
            printf("Contact edited successfully!\n");
            return;
        }
    }

    if (!found) 
    {
        printf("Contact not found.\n");
    }
}


void deleteContact(AddressBook *addressBook) 
{
    int deleteChoice;
    char searchTerm[50];

    do 
    {
        printf("Delete options\n");
        printf("1. Delete by Name\n");
        printf("2. Delete by Phone Number\n");
        printf("3. Delete by Email\n");
        printf("Enter your choice: ");
        scanf("%d", &deleteChoice);

        if (deleteChoice < 1 || deleteChoice > 3) 
        {
            printf("Error: Invalid choice. Please enter a valid option.\n");
        }
    } while (deleteChoice < 1 || deleteChoice > 3);  

    printf("Enter the search term: ");
    scanf(" %[^\n]", searchTerm);
    searchTerm[strcspn(searchTerm, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if ((deleteChoice == 1 && strcasecmp(addressBook->contacts[i].name, searchTerm) == 0) ||(deleteChoice == 2 && strcmp(addressBook->contacts[i].phone, searchTerm) == 0) ||(deleteChoice == 3 && strcmp(addressBook->contacts[i].email, searchTerm) == 0)) 
        {
            found = 1;

            printf("Contact found: %s, %s, %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

            char confirm[10];
            printf("Are you sure you want to delete this contact? (Yes/No): ");
            scanf("%s", confirm);

            if (strcasecmp(confirm, "Yes") == 0) 
            {
                for (int j = i; j < addressBook->contactCount - 1; j++) 
                {
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                }
                addressBook->contactCount--;

                save(addressBook);
                printf("Contact deleted successfully!\n");
            } 
            else if (strcasecmp(confirm, "No") == 0) 
            {
                printf("Deletion canceled.\n");
            } 
            else 
            {
                printf("Invalid input. Deletion operation aborted.\n");
            }

            return;
        }
    }

    if (!found) 
    {
        printf("Contact not found.\n");
    }
}


void listContacts(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0)
    {
        printf("\nNo contacts available.\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount - 1; i++) 
    {
        for (int j = i + 1; j < addressBook->contactCount; j++) 
        {
            if (strcasecmp(addressBook->contacts[i].name, addressBook->contacts[j].name) > 0) 
            {
                Contact temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
        }
    }

    printf("\n====================================\n");
    printf(" Name                      Phone No.       Email\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        printf("%-25s %-15s %-25s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    printf("====================================\n");
}
