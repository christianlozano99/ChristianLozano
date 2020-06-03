//Christian Lozano NID:4233003

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "KindredSpirits.h"

// Functional Prototypes
// makes reflection
int isReflection(node *a, node *b)
{
	int flag1 , flag2 ;	//flag to say if its a reflection or not

	//return success if both trees dont exist

	if (a == NULL && b == NULL)
		return 1;

	//fail if one exists and ther other doesnt
	if (a == NULL || b == NULL)
		return 0;

	//recursively go thorught the trees 
	flag1 = isReflection(a->left, b->right);
	flag2 = isReflection(a->right, b->left);

	//checks if it fails or not
	if (flag1 == 0 || flag2 == 0)
		return 0;



	//check to see if the data matches its location
	if (a->data == b->data)
		return 1;

	// checks if data is the same if not return 0
	if (a->data != b->data)
		return 0;
	


	//returns if flag=1 if reflection flag=0 if not
	
}
//creates node not sure if we could use the on in the test cases so made my own with s at end of create
//node so it does give error
node *creates_node(int data)
{
	//makes new memory for it
	node *newnode = malloc(sizeof(node));
	//puts in passed data and intalizes each child to NULL
	newnode->data = data;
	newnode->left = newnode->right = NULL;

	return newnode;
}
//what actaully swaps around the values and makes a reflection of the tree
void makeReflection_helper(node *newroot)
{	
	// base case
	if (newroot == NULL)
		return;
	// swaps
	else
	{
		node *temp_node;	//holds node to avoid derefrencing

		//recursive calls
		makeReflection_helper(newroot->left);
		makeReflection_helper(newroot->right);

		//temp holds left while left equal to right and then right is equal to old left which is now right
		temp_node = newroot->left;
		newroot->left = newroot->right;
		newroot->right = temp_node;
	}

}
//makes a copy of a tree given its root
node * copyofnormal(node *root)
{
	//base case 
	if (root == NULL)
		return NULL;
	//calls function to make new node
	node *new_tree = creates_node(root ->data);

	//recursively goes through tree and makes a tree
	new_tree->left = copyofnormal(root->left);
	new_tree->right = copyofnormal(root->right);

}

//reflects a tree given its root
node *makeReflection(node *root)
{
	//has temp tree to not affect real one and makes a copy of the orginal
	node *temp_tree = root;
	node *new_tree = copyofnormal(temp_tree);

	//calls helper function which does the actaul flipping
	makeReflection_helper(new_tree);

	//returns pointer to the new tree that is a reflection 
	return new_tree;
}

//makes tree into a pre order array
int makeintoprearray(node *treeToPaper, int array1[], int i)
{
	//base case 
	if (treeToPaper == NULL)
		return i;

	//i will be the index ta the data will be putting into
	//reccursively calls to keep going through tree and insets in
	//pre order manner MLR, increments i after using it to insert into that index
	array1[i++] = treeToPaper->data;
	i = makeintoprearray(treeToPaper->left, array1, i);
	i = makeintoprearray(treeToPaper->right, array1, i);

	return i;

}

//makes tree into a post order array
int makeintopostarray(node *treeToPaper2, int array2[], int j)
{
	//base case
	if (treeToPaper2 == NULL)
		return j;

	// j will be the index that the data wil be put into 
	//recursively calls to keep going through all of tree
	//post order manner LRM
	j = makeintopostarray(treeToPaper2->left, array2, j);
	j = makeintopostarray(treeToPaper2->right, array2, j);

	//increments the j after using it and puts data into it
	array2[j++]=treeToPaper2->data;

	//returns the incremented index to put data into
	return j;

}

//gets how many active nodes are in a tree
int treesize(node* tree)
{
	//intialize size
	int size=0;
	//base case
	if (tree == NULL)
		return 0;

	//returns size and incrimetns after everyuse 
	size += treesize(tree->left);
	size += treesize(tree->right);
	size++;

	return size;
}

//checks and sees if its a kindred spirit
int kindredSpirits(node *a, node *b)
{
	int treeAsize=treesize(a), treeBsize=treesize(b);	//calls tree size to allocate for that much space
	int *postAarray, *preAarray, *postBarray, *preBarray;	//intalizing pointer to arrays
	int k, PreAvsPostBflag=1, PreBvsPostAflag=1;	//A and B flags and k counter for for loop


	if (treeAsize != treeBsize)
		return 0;
	//Allocates memory for the A postorder array and preorder array
	postAarray = calloc(treeAsize, sizeof(int));
	preAarray = calloc(treeAsize, sizeof(int));
	
	//Allocates memory for the B postorder array and preorder array
	postBarray = calloc(treeBsize, sizeof(int));
	preBarray = calloc(treeBsize, sizeof(int));

	//making A into a post and pree order array
	makeintopostarray(a, postAarray, 0);
	makeintoprearray(a, preAarray, 0);

	//making Binto a post and pre order array
	makeintopostarray(b, postBarray, 0);
	makeintoprearray(b, preBarray, 0);

	//goes through the arrays to see if they are the same and has flag
	//to indcated if they are the same everywhere
	for (k=0; k < treeAsize; k++)
	{
		if (preAarray[k] != postBarray[k])
			PreAvsPostBflag = 0;

		if (preBarray[k] != postAarray[k])
			PreBvsPostAflag = 0;
	}

	//checks if either kindred spirit conditons are not staisfied 
	if (PreAvsPostBflag == 0 && PreBvsPostAflag == 0)
		return 0;

	//returns 1 if there is a kindred spirit statisfied
	else 
		return 1;

	//free the memory used for the arrays
	free(postAarray);
	free(preAarray);
	free(postBarray);
	free(preBarray);
}

double difficultyRating(void)
{
	return 2;
}

double hoursSpent(void)
{
	return 9;
}
