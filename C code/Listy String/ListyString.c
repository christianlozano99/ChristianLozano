//Christian Lozano COP 3502C NID:4233003
//Program assignment 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListyString.h"




void takeoff(ListyString *listy, char key);

int processInputFile(char *filename)
{
	//intializing all string holders and varibles used 
	int i=0,n;
	char inputBuff[1023];
	char key[1023];
	char str[1023];
	ListyString*listy;
	ListyNode*head;
	FILE * ifp = NULL;
//opens file
	ifp = fopen(filename,"r");
//if file is NULL or doesnt exist then return 1
	if(ifp==NULL )
	{
		return 1;
	}
	
//scanning the part of the file that will be processed
	fscanf(ifp, "%s", inputBuff);
	listy=createListyString(inputBuff);


//processes all the diffrent inputs 
	while(fscanf(ifp, "%s" , inputBuff) != EOF)
	{
		//printf("\n%s\t",inputBuff);
		//InputFile = inputBuff;
		if (strcmp(inputBuff, "!") == 0)		//prints string if ! is read
		{
			printListyString(listy);
		}

		if(strcmp(inputBuff,"?")==0)		//prints string length if ? is read
		{
			printf("%d",listyLength(listy));
		}

		if(strcmp(inputBuff, "~")==0)	//reverses listy string if ~ is read
		{
			reverseListyString(listy);
		}

		if (strcmp(inputBuff, "+")==0)	//adds string to end of list and moves NULL pointer
		{
			fscanf(ifp, "%s", inputBuff);		//scans for what we want to add at end 
			listyCat(listy, inputBuff);
		}
		
		if (strcmp(inputBuff, "-")==0)	//delets if - is read in by the file 
		{
			fscanf(ifp, "%s", inputBuff);	// searching for what chars to delete in the linked list
			strcpy(key,inputBuff);
			//printf("%s\n",inputBuff );
			//replaceChar(listy, key[0], NULL);
			//takeoff(listy, key[0]);
		}
		
		if (strcmp(inputBuff, "@")==0)	//if @ is read then replace given key with the string
		{
			fscanf(ifp, "%s", inputBuff);	//reading for the key
			strcpy(key, inputBuff);

			fscanf(ifp, "%s", inputBuff);	// reading for the string
			strcpy(str, inputBuff);

			replaceChar(listy, key[0], str);	
		}
		
		
			
		
	}



	fclose(ifp);		//closing out file
	ifp=NULL;			//setting ifp out to NULL


	return 0;			// returnining to main
	
}


//allocateing space for new node and setting data
ListyNode *CreateListyNode(char data)
{
	ListyNode *temp = malloc(sizeof(ListyNode));	// allocates space

	temp->data = data;		//sets linked list data
	temp->next = NULL;		// sets next one to NULL meaning its end

	return temp;			//return the node
}


//from dr.szumlaski's notes , function to insert data into nodes.
ListyNode *Insert_node(ListyNode *head, char data)
{
	ListyNode *h ;


	if (head == NULL)
		return CreateListyNode(data);


	h = head;

	while(h->next != NULL)
	{	
		h = h->next;
	}

	h->next = CreateListyNode(data);

	return head;
}

//creates the string made out of linked lists and calls functions to make linked list
ListyString *createListyString(char *str)
{
	int i,j,len;
	ListyString *listy = malloc(sizeof(ListyString));
	listy->length = 0;
	listy->head = NULL;

	if(str == NULL || (strcmp(str, "") == 0))
	{
		listy->head=NULL;
		listy->length=0;
		return listy;
	}




	len = strlen(str);
	for(i=0; i < len; i++)
	{
		listy->head=Insert_node(listy->head,  str[i]);
		listy->length++;
	}
	return listy;
}


//frees all memory in the linked list or returns NULL if it doesnt exist
ListyString *destroyListyString(ListyString *listy)
{

	if(listy==NULL)
		return NULL;

	free(listy->head);
	free(listy);

	return NULL;
}

//clones the listy string 
ListyString *cloneListyString(ListyString *listy)
{
	//intiazlizing varibles that are going tp be used 
	int i;
	char pass[listy->length];
	ListyString *NewListy = malloc(sizeof(ListyString));	//allocating space for the copy of the linked list
	ListyNode*temp;
	NewListy->length = 0;
	NewListy->head = NULL;


	if(listy == NULL )
		return NULL;


	temp=listy->head;	//setting the intial node location
	for(i=0; i < listy->length; i++)
	{
		
		pass[i]=temp->data;	//making linked list into a string 

		temp=temp->next;
	}
	

	NewListy=createListyString(pass);	//passing the string into creat Listy which makes it a linked list
	return NewListy;

}


void takeoff(ListyString *listy, char key)
{
	// Store head node 
	if(listy==NULL)			//if the listy doesnt exist then jsut return
		return;

	ListyNode* trash = NULL;
	ListyNode * current =listy->head ;	//intializing varibles that are begore and after the head and at the head 
	ListyNode * after=listy->head->next;

	while (current->next != NULL) 
	{ 
		if(after->data==key)
		{
			trash=after;
			current=after->next;
			after=current->next;

			free(trash);

		}

		if(current->next->data!=key)
			current=current->next->next;
	


	}


}

//replaces key with str string
void replaceChar(ListyString *listy, char key, char *str)
{
	int i,j,len=strlen(str);		//intializing all things i will be using
	ListyString*copy;

	//make a copy 
	copy=cloneListyString(listy);



	//for loop to go through the orginal linked list 
	for (i = 0; i < listy->length ; i++)
	{
		if(copy->head->data == key)		//if the orginal data in given head in key then 
		{								//make a loop that inserts the strong passed in at that node/key
			for(j=0;j<len;j++ )
			{
				listy->head=Insert_node(listy->head,str[j]);
			}
		}

		if(copy->head->data!=key)		//if in the orginal string it is not the key at give head data then just put the orginal data back in
			listy->head=Insert_node(listy->head,copy->head->data);

		copy->head=copy->head->next;
		listy->head=listy->head->next;
	}

	listy->length=listy->length+len-1;
	free(copy);						//free the copy that i made of the orginal string 
}

void reverseListyString(ListyString *listy)
{
	if(listy==NULL)			//if the listy doesnt exist then jsut return
		return;

	ListyNode* before = NULL;
	ListyNode * current =listy->head ;	//intializing varibles that are begore and after the head and at the head 
	ListyNode* after = NULL;


	while (current != NULL) 
	{ 
		// Store next 
		after  = current->next;

		// Reverse current node's pointer 
		current->next = before;    
		// Move pointers one position ahead. 
		before = current; 
		current = after; 
	}

	listy->head = before; 

}

//concates str to the end of the linked list
ListyString *listyCat(ListyString *listy, char *str)
{
	int i,j=0,k, len;				//intializing head location and varibes 
	ListyNode*temp=listy->head;


	if(str==NULL)			//if str is NULL then just go back since noting to add
		return listy;

	len=strlen(str);		//scan this now to avoid segfaults of str len of NULL

	if(listy->length == 0 )		//if the linked list was empty then insert str len many nodes with the new strong
	{
		
		for(k=0; k < len; k++)
		{
			listy->head=Insert_node(listy->head,  str[k]);
			listy->length++;
		}
			
		

		return listy;		//return listy with added string
	}
	

	for (i = 0; i < (listy->length)+len ; i++)	//if ther was a linked list already this adds it ot then end
	{
		if(i<listy->length)
			{

					//do nothing if the head is stil in the existing linked list
			}

		if(i>=listy->length)		//insert nodes with the new string characters at the end 
		{
			temp=Insert_node(listy->head,str[j++]);
		}



		temp=temp->next;	//scrolls thorugh the linked list

	}

	listy->length=listy->length+len;		//adds current linked list to string passed in to update length

	return listy;							//return new linked list
}

int listyCmp(ListyString *listy1, ListyString *listy2)
{
	int i,j;						//initalzing varilbes that will be used 


	if(listy1 == NULL && listy2 == NULL)		//if listy1 and 2 are NULL then they are the same
		return 0;

	if(listy1 == NULL && listy2->length==0)		//if listy 1 is NULL but listy2 is empty but exists,then not the same
		return 1;

	if(listy2 == NULL && listy1->length==0)	//if listy 2 is NULL but listy1 is empty but exists,then not the same
		return 1;


	ListyNode*temp1=listy1->head;		// intialzing head to temporary struct to pass through linked list
	ListyNode*temp2=listy2->head;
	char pass1[listy1->length];
	char pass2[listy2->length];			//strings to hold the string that the linked lists make


	temp1=listy1->head;

	for(i=0; i < listy1->length; i++)	//makes listy1 into a string
	{
		
		pass1[i]=temp1->data;

		temp1=temp1->next;
	}

	temp2=listy2->head;
	for(j=0; j < listy2->length; j++)	//makes listy2 into a string 
	{
		
		pass2[j]=temp2->data;

		temp2=temp2->next;
	}

	if(strcmp(pass1,pass2)==0)	//if the lsity1 string is the same as listy 2 string then return 0
		return 0;

	if(strcmp(pass1,pass2)!=0)	// if the listy1 strin and the lsity 2 string are not the amse then return 1 
		return 1;



}

int listyLength(ListyString *listy)	
{
	if(listy==NULL)
		return -1;									//returns -1 if the listy is non existent

	if(listy!=NULL && listy->head==NULL)			//returns 0 if it does exist but is empty
		return 0;

	return listy->length;							//returns length if it has values in it
}

void helper_print(ListyNode *head)
{
	if(head==NULL)			//base case 
		return;

	printf("%c", head->data);		//prints character at head then passes next into the same fucntion untill
	helper_print(head->next);		//it reaches the base case
}
//prints the string 
void printListyString(ListyString *listy)
{
	
	if(listy==NULL || listy->head==NULL)	//returns a print statment saying that string is empty if it is NULL
	{
		printf("(empty string)\n");
		return;
	}

	helper_print(listy->head);	//call of recursive function to print
	printf("\n");

}

//diffculty rating 
double difficultyRating(void)
{
	return 4;
}
//hours spent working on it
double hoursSpent(void)
{
	return 40;
}


int main(int argc,char **argv)
{
	char *filename;


	processInputFile(argv[1]);

	return 0;
}
