#include <stdio.h>
#include "file.h"


//Function to save all contacts into a CSV file
void saveContactsToFile(struct AddressBook *addressBook) 
{
	
	FILE* fp = fopen("contacts.csv","w"); //opens the file in write mode...
	
	if(fp)
	{
		fprintf(fp,"#%d\n",addressBook->contactCount);//writing the total no.of contacts on the top...
		
		// Loop through each contact and save details in CSV file...
		for(int i=0;i<addressBook->contactCount;i++)
		{
			fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
		}
		fclose(fp); //closing the file...
	}
}

//Function to load all contacts into a CSV file
void loadContactsFromFile(struct AddressBook *addressBook) 
{

    	FILE* fl = fopen("contacts.csv","r"); //opening the file in read mode...
	fscanf(fl,"#%d\n",&addressBook->contactCount);

	//if file is not existed...
	if(fl == NULL)
	{
		printf("File is not available\n");
		return;
	}

	fscanf(fl,"#%d\n",&addressBook->contactCount);
    	for(int i=0;i<addressBook->contactCount;i++) //reads each contact’s details line by line...
    	{
		//prints the contacts details using comma separatedly...
      		fscanf(fl,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    	}

    	fclose(fl);//closing the file...
}
