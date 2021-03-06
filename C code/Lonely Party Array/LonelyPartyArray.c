//Christian Lozano 
//ch158330
// COP 3502, Fall 2018
#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"





 LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
{

	int i,j;

	//allocates how many fragments in struct LPA
	LonelyPartyArray*LPA = malloc(sizeof(LonelyPartyArray));
	



	LPA -> size = 0;				 				//used up cells
	LPA -> num_fragments = num_fragments;		 	//how many frag
	LPA -> fragment_length = fragment_length;		//how long frag is
	LPA -> num_active_fragments=0;					//set to one because incoming key by defult in set
	
	//if either the two arguments are passed in return null
	if(LPA -> num_fragments <= 0 || LPA -> fragment_length <= 0)
		return NULL;

	//allocating fragments array to be an array of num_fragmens and setting to null with callloc
	// and puting how long each one is so the cells in each frag, and intalizing to 0

	LPA -> fragments = (int**)calloc(num_fragments, sizeof(int*));
	LPA -> fragment_sizes = (int*)calloc(fragment_length, sizeof(int));

	//out put message
	printf( "-> A new LonelyPartyArray has emerged from the void. (capacity: %d, fragments: %d)\n",(num_fragments*fragment_length),num_fragments);

	return LPA;

}




LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
{
// dont free if null 
	//for loop for all fragments 
	if (party!=NULL)
	{
		printf("-> The LonelyPartyArray has returned to the void.\n");
	//frees all memory used in the progtam
		free(party -> fragments);
		free(party -> fragment_sizes);
		free(party);
	}

	return NULL;
}

int set(LonelyPartyArray *party, int index, int key)
{
	int i,j,k,l,p,m,fragment_length,low,high;
	fragment_length= party -> fragment_length,set;
	//i and j are calcualtions for what indicies the key will get stored in
	i = index/ (fragment_length);
	j = index % (fragment_length);
	party -> fragment_sizes[i]=0; 

	// low and highs of the indcies per fragment
	low = fragment_length*i;
	high=low+fragment_length-1;

	//condtion to make a new fragment and put key there
	if (index<=(party->num_fragments * party->fragment_length)-1)
	{
	
		if(party -> fragments[i]==NULL)
		{
			//allocates memory for fragment[i] and sets all to null
			party -> fragments[i] = (int*)calloc(fragment_length, sizeof(int));		
			party -> num_active_fragments++;												// keeping track of how many active fragments i have
			printf("-> Spawned fragment %d. (capacity: %d, indices: %d..%d)\n",i,party->fragment_length,low,high);
			//loops thorugh the whole fragment if its at the key spot sets it and if not sets it to unused
			for(k=0; k<= fragment_length;k++)
			{
				if (k==j ){
					party->size++;
					party->fragment_sizes[i]++;
					party -> fragment_sizes[i]++;  


				}
			

					if(k!=j && l!=i)
					{
						party -> fragments[i][k]=UNUSED;
					}



			}
		}

		
			//if the fragment is unsed increases size to keep track
			if (party->fragments[i][j]!=0 && party->fragments[i][j]==UNUSED)
			{
				party->size++;
				party -> fragment_sizes[i]++;  


			}
		
			//sets key
		party -> fragment_sizes[i]++;  
		party->fragments[i][j]=key;
	
		//successful set 

		return LPA_SUCCESS;
	}

	//if not sucessful invalid and return faliure
	
		printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d, offset: %d)\n",index,i,j);

	return LPA_FAILURE;
	
}


int get(LonelyPartyArray *party, int index)
{
	int i,j,k,l,valid,fragment_length,value=0;
	fragment_length= party -> fragment_length;
	//how to find key with right indices i and j
	i = index/ (fragment_length);
	j = index % (fragment_length);
	valid=party->num_fragments*fragment_length;
	
	//if the index is in bounds and is not null then it returns whats inside of it
	if(index<valid && party -> fragments[i]!=NULL )
	{
		value=party->fragments[i][j];
		return value;
					
	}
	//if the fragment is null and the index is inbounds then retuns null
	if(party -> fragments[i]==NULL && index<valid )
	{
		 	return UNUSED;

	}
	//if the fragment index is too high and not allocated memory for then it retuns falure
	if(index>=valid )
	{

		printf("-> Bloop! Invalid access in get(). (index: %d, fragment: %d, offset: %d)\n",index,i,j);
	 	return LPA_FAILURE;

	}
}

int delete(LonelyPartyArray *party, int index)
{
	int i,j,k,valid,fragment_length,low,high;

	//how to find key with right indices i and j
	fragment_length= party -> fragment_length;
	i = index/ (fragment_length);
	j = index % (fragment_length);
	valid=party->num_fragments*fragment_length;
	low = fragment_length*i;
	high=low+fragment_length-1;



	//if the party at that point is empty and not allocated for
	if(party->fragments[i]==0)
	{
		party -> fragments[i] = (int*)calloc(fragment_length, sizeof(int));		
		party->fragments[i]=NULL;

		return LPA_FAILURE;
	}

	//if index is too big
	if(index>(party->num_fragments * party->fragment_length)-1 )
	{

		printf("-> Bloop! Invalid access in delete(). (index: <%d>, fragment: <%d>, offset: <%d>)\n",index,i,j);
	 	return LPA_FAILURE;
	}
	//if cell is not there to begin with
	if(index<=valid && party->fragments[i][j]==UNUSED)
	{
			return LPA_FAILURE;
	}

	if(index<=valid && party->fragments[i][j]!=UNUSED )
	{
		if(party->fragments[i][j]!=UNUSED && party->fragments[i][j]!=0)
		{
	
			//keeps track of the sizes when a delete happens
			party -> fragment_sizes[i]--; 
			party-> fragments[i][j]=UNUSED;
			party -> size--;
			

			
			if(party->fragment_sizes[i]==0)
			{
				party->fragments[i]=NULL;
				printf("-> Deallocated fragment %d. (capacity: %d, indices: %d..%d)\n",i,party->fragment_length,low,high);
				party -> num_active_fragments--;
			}


			return LPA_SUCCESS;
		}
		//sets party fragment at i to null if delteed 
		party->fragments[i]=NULL;

	 	return LPA_FAILURE;
	}

}

int containsKey(LonelyPartyArray *party, int key)
{
	return 0;
}

int isSet(LonelyPartyArray *party, int index)
{
	return 0;
}
LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party)
{
	return NULL;
}

int printIfValid(LonelyPartyArray *party, int index) // fuck up at 12
{
	int i,j,k,l,valid,fragment_length,value=0;
	//how to find key with right indices i and j
	i = index/ (party -> fragment_length);
	j = index % (party -> fragment_length);
	//retuns faliure if the index is too big
	if(index>=party->fragment_length*party->num_fragments)
		return LPA_FAILURE;
//sucess if ther is a key at that index and shows user what key
	if(party->fragments[i]!=NULL && i>=0 && j>=0 && party->fragments[i][j]!=UNUSED){
		printf("%d\n",party->fragments[i][j]);
		return LPA_SUCCESS;
}


	return LPA_FAILURE;
}


int getSize(LonelyPartyArray *party)
{
	//size fo the party
	if(party==NULL)
		return -1;

	return party->size;
}

int getCapacity(LonelyPartyArray *party)
{
	//maximum numbers we can store in the array
	return party->num_fragments*party->fragment_length;
}

int getAllocatedCellCount(LonelyPartyArray *party)
{
	//how many cells are being allocated for
	int allocted,i;
	if(party==NULL)
		return -1;

	return party->fragment_length*party->num_active_fragments;
}

long long unsigned int getArraySizeInBytes(LonelyPartyArray *party)
{
	//how many bytes are being used in each array
	if(party==NULL)
		return 0;
	
	return party->fragment_length*party->num_fragments*sizeof(int);
}

long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party)
{
	//attempt to get right values
	int value,structs,parts;
	if(party==NULL)
		return 0;

	structs=sizeof(LPA)+sizeof(LPA*);
	parts=sizeof(party->fragments)*sizeof(party->fragment_length)+(sizeof(party->fragment_sizes)+sizeof(party->num_active_fragments))*sizeof(int)+sizeof(int)*party->size;

	value= structs+parts;
	return value;
}

double difficultyRating(void)
{
	return 4;
}

double hoursSpent(void)
{
	return 40;
}

