// recursive function prints a tree
// root at the left of the screen, leaves at the right 


#include "stdafx.h"
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctime>


#define SIZE 20
#define DEFAULT_SIZE 15
#define DEFAULT_TREE '1'
#define RANDOM_TREE '2'


struct TreeItem
{
	TreeItem* left;
	TreeItem* right;
	int info;
};


TreeItem* createTreeItem(int info);

void addTreeItem(TreeItem** tree, TreeItem* item);

void removeTree(TreeItem* root);

int findMaximalTreeItem(TreeItem* root);

int findMinimalTreeItem(TreeItem* root);

int countDigits(int number);

int getNumberLength(int number);

int getMaximalItemLength(TreeItem* root);

void printTree(TreeItem* root, int maximalLength, int depth);

TreeItem* createRandomTree(TreeItem* root, int amount);

TreeItem* createDefaultTree(TreeItem* root);


int main()
{
	srand(time(NULL));

	TreeItem* root = NULL;
	int choice = 0;

	printf("\nPress to print 1 - default tree\n\t\t2 - random tree\t");
	choice = getchar();

	switch (choice)
	{
		case DEFAULT_TREE: root = createDefaultTree(root); break;
		case RANDOM_TREE: root = createRandomTree(root, SIZE); break;
		default: printf("Incorrect input.\n"); _getch(); return 0;
	}
	
	printTree(root, getMaximalItemLength(root), 0);
	removeTree(root);
	
	_getch();
	return 0;
}


TreeItem* createTreeItem(int info)
{
	TreeItem* item = (TreeItem*)malloc(sizeof(TreeItem));
	if (item == NULL)
	{
		printf("Memory allocation error");
		exit(1);
	}

	item->left = NULL;
	item->right = NULL;
	item->info = info;

	return item;
}


void addTreeItem(TreeItem** tree, TreeItem* item)
{
	if (*tree == NULL)
	{
		*tree = item;
		return;
	}

	if (item->info < (*tree)->info)
		addTreeItem(&(*tree)->left, item);

	else if (item->info >(*tree)->info)
		addTreeItem(&(*tree)->right, item);
}


void removeTree(TreeItem* root)
{
	if (root == NULL)
		return;

	removeTree(root->left);
	removeTree(root->right);

	free(root);
}


int findMaximalTreeItem(TreeItem* root)
{
	if (root->right == NULL)
		return root->info;

	findMaximalTreeItem(root->right);
}


int findMinimalTreeItem(TreeItem* root)
{
	if (root->left == NULL)
		return root->info;

	findMinimalTreeItem(root->left);
}


int countDigits(int number)
{
	if (!number)
		return 1;

	int counter = 0;
	while (number)
	{
		number /= 10;
		counter++;
	}

	return counter;
}


int getNumberLength(int number)
{
	int length = countDigits(number);

	return number >= 0 ? length : length + 1;
}


int getMaximalItemLength(TreeItem* root)
{
	int maximumLength = getNumberLength(findMaximalTreeItem(root)),
		minimumLength = getNumberLength(findMinimalTreeItem(root));

	return maximumLength > minimumLength ? maximumLength : minimumLength;
}


void printTree(TreeItem* root, int maximalLength, int depth)
{
	if (root == NULL)
		return;

	int indent = (maximalLength + 3) * depth;

	printTree(root->right, maximalLength, depth + 1);
	printf("%*.d\n", indent, root->info);
	printTree(root->left, maximalLength, depth + 1);
}


TreeItem* createRandomTree(TreeItem* root, int amount)
{
	if (root != NULL)
		return root;

	int counter = 0;
	while (counter <= amount)
	{
		int info = rand() % 100 + 1;
		addTreeItem(&root, createTreeItem(info));
		counter++;
	}

	return root;
}

TreeItem* createDefaultTree(TreeItem* root)
{
	if (root != NULL)
		return root;

	int array[] = { 49, 83, 28, 97, 71,
		40, 18, 99, 92, 72,
		69, 44, 32, 19, 11 };

	for (int i = 0; i < DEFAULT_SIZE; i++)
		addTreeItem(&root, createTreeItem(array[i]));

	return root;
}