#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

int validate_phn(struct AddressBook* ,char*);
int validate_email(struct AddressBook* ,char*);
int search_name(struct AddressBook *,int*);
int search_mobile(struct AddressBook *,int*);
int search_email(struct AddressBook *,int*);
void edit_contact_name(struct AddressBook* ,int*,int,int);
void edit_contact_number(struct AddressBook* ,int*,int,int);
void edit_contact_email(struct AddressBook* ,int*,int,int);

void print_box_header()
{
     printf("+-----+---------------------------+-----------------+------------------------------+\n");
     printf("| ID  | Name                      | Mobile No       | Mail ID                      |\n");
     printf("+-----+---------------------------+-----------------+------------------------------+\n");
}

void print_box_footer() {
    printf("+-----+---------------------------+-----------------+------------------------------+\n");
}

//displays all saved contacts in a clean table format...
void listContacts(struct AddressBook *addressBook) 
{
    /* Define the logic for print the contacts */
	printf("All Contact Details\n");
	char a[100];
	int size = addressBook->contactCount;
	
	//it will print every contact detail...
	print_box_header(); //for a pattern...
	for(int i=0;i<size;i++)
	{
		printf("| %-3d | %-25s | %-15s | %-28s |\n",i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
		print_box_footer();
	}
}


void initialize(struct AddressBook *addressBook){
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}


void saveAndExit(struct AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


//takes the contact details from user and validates mobile,email before saving...
void createContact(struct AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */
	int size = addressBook->contactCount;
	getchar();
	printf("\nEnter the Name: ");
	scanf("%[^\n]",addressBook->contacts[size].name);
	
	int flag=0;
	
	//the loop will repeat until it is a valid mobile number...
	do
	{
		getchar();
		printf("Enter the Mobile Number: ");
		scanf("%[^\n]",addressBook->contacts[size].phone);
		
		//it checks whether the number is valid number or not and where the number is already existed...
		if(validate_phn(addressBook,addressBook->contacts[size].phone))
			flag =1;
		else
			flag=0;
	}while(!flag);

	int valid=1;
	
	//the loop will repeat until it is a valid e-mail...
	do
	{
		getchar();
		printf("Enter the email: ");
		scanf("%[^\n]",addressBook->contacts[size].email);

		//for checking whether the e-mail is valid or not...
		if(validate_email(addressBook,addressBook->contacts[size].email))
			valid = 0;
		else
			valid = 1;
	}while(valid);
	
	//if every input is entered correctly the contact will be saved...
	printf("Contact saved successfully\n");

	(addressBook->contactCount)++; //after creating a successful contact the contactCount will be incremented...
}

//searches contacts by name, mobile, or email and prints matching results...
void searchContact(struct AddressBook *addressBook) 
{
    /* Define the logic for search */
	printf("\n1.search by name\n");
	printf("2.search by mobile\n");
	printf("3.search by email\n");
	printf("4.Exit\n");
	int opt;
	printf("Select an option : "); //to select the option...
	scanf("%d",&opt);
	
	int duplicate[addressBook->contactCount]; //for storing the indexes if multiple names,emails are same....
	int indx = -1;
	
		switch(opt)
		{
			case 1:	indx = search_name(addressBook,duplicate); //it searches by name function...
				break;
			case 2:	indx = search_mobile(addressBook,duplicate);//it searches by mobile number function...
				break;
			case 3:	indx = search_email(addressBook,duplicate);//it searches by email function...
				break;
		}
	//If no contacts were found...
	if(indx == 0)
	{
		printf("No contacts were found\n");
		return ;
	}
}


//Allows editing a specific contact or multiple contacts that have same name/email, user can select which one should edit using the index...
void editContact(struct AddressBook *addressBook)
{
    /* Define the logic for Editcontact */
	if (addressBook->contactCount == 0) //if there is no contacts...
	{
        	printf("Address book is empty!\n");
        	return;
    	}
	
	printf("1.search by name\n2.search by mobile\n3.search by email\n4.Exit\n");
	int opt;
	printf("\nSelect an option : ");
	scanf("%d",&opt);
	
	int duplicate[addressBook->contactCount];
	int ind_c=0;
	
	switch(opt)
	{
			case 1: ind_c = search_name(addressBook,duplicate);
				break;
			case 2: ind_c = search_mobile(addressBook,duplicate);
				break;
			case 3: ind_c = search_email(addressBook,duplicate);
				break;
			case 4: return;
			default: printf("Invalid option\n");
				 return ;		
	}
	if(ind_c==0)
	{
		printf("No matching contact found\n");
		return;
	}
	
	int choice;
	if(ind_c > 1)
	{
		printf("\nThere are %d contacts with the same details.\n", ind_c);
        	for (int i = 0; i < ind_c; i++)
        	{
            		int idx = duplicate[i];
            		printf("[%d] %s | %s | %s\n", i + 1,addressBook->contacts[idx].name, addressBook->contacts[idx].phone, addressBook->contacts[idx].email);
		}
		printf("\nEnter the contact number to edit (1 - %d): ", ind_c);
        	scanf("%d", &choice);
	
			if (choice < 1 || choice > ind_c)
        		{
            			printf("Invalid choice!\n");
            			return;
        		}
        		
	}
	else
		choice = 1;

	int contactIndex = duplicate[choice - 1];
    	printf("\nEditing contact: %s\n", addressBook->contacts[contactIndex].name);
	
	int field;
	do
	{
		printf("\nWhat do u want to edit: \n1.Name\n2.Number\n3.email\n4.Exit\n");

		printf("Enter an option: ");
		scanf("%d",&field);
		switch(field)
			{
				case 1: edit_contact_name(addressBook,&contactIndex,1,choice);
					break;
				case 2: edit_contact_number(addressBook,&contactIndex,1,choice);
					break;
				case 3: edit_contact_email(addressBook,&contactIndex,1,choice);
					break;
			}
	}while(field<=3);
}

// Deletes one specific contact and it displays all duplicate contacts,later asks for which one to remove...
void deleteContact(struct AddressBook *addressBook)
{
    /* Define the logic for deletecontact */
	if (addressBook->contactCount == 0)
    	{
        	printf("Address book is empty!\n");
        	return;
    	}
	
	printf("1.search by name\n2.search by mobile\n3.search by email\n4.Exit\n");
	int opt;
	printf("\nSelect an option : ");
	scanf("%d",&opt);
	int duplicate[addressBook->contactCount];
	int indx=0;
	switch(opt)
	{
		case 1:	indx = search_name(addressBook,duplicate); //searching using name by a func...
			break;
		case 2:	indx = search_mobile(addressBook,duplicate);//searching using mobile number by a func...
			break;
		case 3:	indx = search_email(addressBook,duplicate);//searching using email by a func...
			break;
		default: printf("Invalid option\n");
			return;
	}
	
	if(indx == 0)
	{
        	printf("No matching contacts found!\n");
        	return;
    	}

	printf("\nThere are %d contact(s) with matching details:\n", indx);
    	for (int i = 0; i < indx; i++)
    	{
        	int idx = duplicate[i];
        	printf("| %-3d | %-25s | %-15s | %-28s |\n", i + 1, addressBook->contacts[idx].name,addressBook->contacts[idx].phone, addressBook->contacts[idx].email);
    	}
 
    	int selectedIndex;
    	printf("\nEnter the contact number to delete (1 - %d): ", indx);
    	scanf("%d", &selectedIndex);

    	if (selectedIndex < 1 || selectedIndex > indx)
    	{
        	printf("Invalid index selection!\n");
        	return;
    	}

    	int contactIndex = duplicate[selectedIndex - 1];
    	printf("\nAre you sure you want to delete '%s'? (y/n): ", addressBook->contacts[contactIndex].name);
    	char confirm;
    	scanf(" %c", &confirm);

    	if (confirm == 'y' || confirm == 'Y')
    	{
        	for (int i = contactIndex; i < addressBook->contactCount - 1; i++)
        	{
            		addressBook->contacts[i] = addressBook->contacts[i + 1];
        	}
        	addressBook->contactCount--; //after deleting we should decrement the contactcount...
        	printf("Contact deleted successfully!\n");
    	}
    	else
        	printf("Delete cancelled.\n");
}

//for checking whether the number is valid or not...
int validate_phn(struct AddressBook* addressBook,char* phn)
{
	int i=0,size=addressBook->contactCount;
	while(phn[i])
	{
		if(phn[i]>='0' && phn[i]<='9')
			i++;
		else
			break;
	}
	int duplicate=0;
	for(int j=0;j<size;j++)
	{
		if(!(strcmp(phn,addressBook->contacts[j].phone))) //checking whether the nuber is existed previously or not...
		{
			puts("\nRE-ENTER!\nNumber already existed");
			duplicate=1;
			break;
		}
	}
	if(i==10 && duplicate==0) //conforming whether the number is 10 digits and not existed previously...
		return 1;
	else
		return 0;
}

//checking whether email is valid or not...
int validate_email(struct AddressBook* addressBook,char* mail)
{
	int len = strlen(mail);
	
	for(int s=0;mail[s]!='\0';s++)
	{
		//checking whether mail contains capital letters and not containg '@', '.com' in it....
		if((mail[s]>='A' && mail[s]<='Z') ||!(strchr(mail,'@'))||!(strstr(mail,".com")))
		{
			puts("ENTER THE CHARACTERS IN LOWER CASE, THERE SHOULD BE A \"@\" ,\".com\" IN THE E-MAIL");
			return 0;
		}
		
		//mail can have small alphabets,numbers,@ and .com at end...
		if((mail[s]>='a' && mail[s]<='z')|| mail[0]!='@' || strcmp((mail+(len-4)),".com")|| mail[len-1]!='@'||(mail[s]>='0' && mail[s] <='9'))
			continue;
		else
		{
			puts("\nEMAIL SHOULD CONTAIN \"@\"  AND \".com\" AT LAST OF MAIL"); 
			return 0;
		}
	}
	return 1;
}

//for searching the name of a contact...
int search_name(struct AddressBook *addressBook,int* duplicate)
{
	char name[50];
	int size= addressBook->contactCount;
	getchar();
	printf("Enter the name: ");
	scanf("%[^\n]",name);
	int count=0;
	
	print_box_header();
	for(int i=0;i<size;i++)
	{
		if(strstr(addressBook->contacts[i].name, name) != NULL) //for partial match using strstr()
		{
			printf("| %-3d | %-25s | %-15s | %-28s |\n",i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
	                print_box_footer();
			duplicate[count++] = i;//it stores the indexes of duplicate contacts...
		}
	}
	
	if(count>0)
		return count;
	else
	{
		printf("Contact with that name is not found!\n");
		return 0;
	}
}

//for searching the contact using mobile number...
int search_mobile(struct AddressBook *addressBook,int* duplicate)
{
	char mobile[50];
	int size= addressBook->contactCount;
	getchar();
	printf("Enter the mobile number: ");
	scanf("%[^\n]",mobile);
	int count=0;
	print_box_header();
	for(int i=0;i<size;i++)
	{
		if((strcmp(mobile,addressBook->contacts[i].phone))==0)
		{
			printf("| %-3d | %-25s | %-15s | %-28s |\n",i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                        print_box_footer();
			duplicate[count++] = i;//it stores the indexes of duplicate contacts...
		}
	}
	if(count>0)
		return count;
	else{
		printf("\tContact with that NUMBER is not found!\n");
		return 0;
	}
}

//for searching the contact using email...
int search_email(struct AddressBook *addressBook,int* duplicate)
{
	char email_id[50];
	int size= addressBook->contactCount;
	getchar();
	printf("Enter the Email id: ");
	scanf("%[^\n]",email_id);
	int count=0;
	print_box_header();
	for(int i=0;i<size;i++)
	{
		if(!(strcmp(email_id,addressBook->contacts[i].email)))
		{
			printf("| %-3d | %-25s | %-15s | %-28s |\n",i+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                        print_box_footer();
			duplicate[count++] = i;//it stores the indexes of duplicate contacts...
		}
	}
	if(count>0)
		return count;
	else{
		printf("\tContact with that Email is not found!\n");
		return 0;
	}
}

//for editing the contact name...
void edit_contact_name(struct AddressBook* addressBook,int* arr,int index_c,int choice)
{
	char temp_name[50];
	for(int i=0;i<index_c;i++)
	{
		getchar();
		printf("Enter the name for contact [%d] from %s To: ",(arr[i]+1),addressBook->contacts[arr[i]].name);
		scanf("%[^\n]",temp_name);
		strcpy(addressBook->contacts[arr[i]].name,temp_name); //using strcpy we are updating the name...
	}
	printf("Name updated successfulyy!!!\n");
}

//for editing the contact number...
void edit_contact_number(struct AddressBook* addressBook,int* arr,int index_c,int choice)
{
	char temp_number[50];
	for(int i=0;i<index_c;i++)
	{
		int flag=1;
		do
		{
			getchar();
			printf("Enter the nuber for contact [%d] from %s To: ",(arr[i]+1),addressBook->contacts[arr[i]].phone);
			scanf("%[^\n]",temp_number);

			//before updating we have check whether the number is valid or not...
			if(validate_phn(addressBook,temp_number))
				flag =0;
		}while(flag);
		strcpy(addressBook->contacts[arr[i]].phone,temp_number);//using strcpy we are updating the number...
	}
	printf("Number updated successfully!!!\n");
	
}

//for updating the email...
void edit_contact_email(struct AddressBook* addressBook,int* arr,int index_c,int choice)
{
	char temp_mail[50];
	for(int i=0;i<index_c;i++)
	{
		getchar();
		printf("Enter the E-mail for contact [%d] from %s To: ",(arr[i]+1),addressBook->contacts[arr[i]].email);
		scanf("%[^\n]",temp_mail);
		int valid=1;
		do
		{
			if(validate_email(addressBook,temp_mail)) //we have check whether the email is valid or not...
				valid =0;
		}while(valid);
		strcpy(addressBook->contacts[arr[i]].email,temp_mail);//using strcpy we are updating the email...
	}
	
	printf("E-mail updated successfully!!!\n");
}
