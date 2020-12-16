// QUESTION 4: Word Tree
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// create 26 children per node for all letters in the alphabet
#define N 26

typedef struct Tree Tree;

// our tree structure 
struct Tree
{

  char data;
  // each node has N children
  Tree *children[N];
  // checks to see if it is a leaf or not
  int is_leaf;
};

Tree *
create_Tree (char data)
{
  // creates memory for the Tree
  Tree *node = (Tree *) calloc (1, sizeof (Tree));
  for (int i = 0; i < N; i++)
    node->children[i] = NULL;
  node->is_leaf = 0;
  node->data = data;
  return node;
}

void
recover_mem (Tree * node)
{
  // recovers memory so that it can be reused
  for (int i = 0; i < N; i++)
    {
      if (node->children[i] != NULL)
	{
	  recover_mem (node->children[i]);
	}
      else
	{
	  continue;
	}
    }
  free (node);
}

Tree *
insert (Tree * root, char *word)
{
  // insert a word into the tree
  Tree *temp = root;

  for (int i = 0; word[i] != '\0'; i++)
    {
      // find the position in the alphabet list
      int idx = (int) word[i] - 'a';
      if (temp->children[idx] == NULL)
	{
	  // if there is no corresponding child, create it 
	  temp->children[idx] = create_Tree (word[i]);
	}

      temp = temp->children[idx];
    }
  // marks the node as a leaf
  temp->is_leaf = 1;
  return root;
}

int
search (Tree * root, char *word)
{
  // looks for word in the tree
  Tree *temp = root;

  for (int i = 0; word[i] != '\0'; i++)
    {
      int position = word[i] - 'a';
      if (temp->children[position] == NULL)
	return 0;
      temp = temp->children[position];
    }
  if (temp != NULL && temp->is_leaf == 1)
    return 1;
  return 0;
}

// looks to see if there is branching at the end of the word and returns the largest position where it occurs
int
divergence (Tree * root, char *word)
{

  Tree *temp = root;
  int len = strlen (word);
  if (len == 0)
    return 0;

  int last_index = 0;
  for (int i = 0; i < len; i++)
    {
      int position = word[i] - 'a';
      // if there is a child in this position, we check to see if there is any other child there too
      if (temp->children[position])
	{

	  for (int j = 0; j < N; j++)
	    {
	      // if we find another child, we update our branch position
	      if (j != position && temp->children[j])
		{
		  last_index = i + 1;
		  break;
		}
	    }
	  // moves to next child in sequence
	  temp = temp->children[position];
	}
    }
  return last_index;
}

// finds the longest common substring of a word
char *
find_longest_sub (Tree * root, char *word)
{

  if (!word || word[0] == '\0')
    return NULL;
  // length of the longest substring
  int len = strlen (word);

  // sets the longest substring as the entire word and backtracks
  char *longest_sub = (char *) calloc (len + 1, sizeof (char));
  for (int i = 0; word[i] != '\0'; i++)
    longest_sub[i] = word[i];
  longest_sub[len] = '\0';

  // finds the original string with an exact match
  int branch_idx = divergence (root, longest_sub) - 1;
  if (branch_idx >= 0)
    {

      // if there is branching, we have to update the position to the longest match and update the longest substring
      longest_sub[branch_idx] = '\0';
      longest_sub =
	(char *) realloc (longest_sub, (branch_idx + 1) * sizeof (char));
    }

  return longest_sub;
}

int
is_leaf_node (Tree * root, char *word)
{

  // checks if it is a leaf node
  Tree *temp = root;
  for (int i = 0; word[i]; i++)
    {
      int position = (int) word[i] - 'a';
      if (temp->children[position])
	{
	  temp = temp->children[position];
	}
    }
  return temp->is_leaf;
}

Tree *
delete_tree (Tree * root, char *word)
{

  // deletes a word from the tree if it ends up in a leaf node
  if (!root)
    return NULL;
  if (!word || word[0] == '\0')
    return root;

  // stop if the match is not a leaf node
  if (!is_leaf_node (root, word))
    {
      return root;
    }
  Tree *temp = root;
  // finds the longest substring that is not the current word
  char *longest_sub = find_longest_sub (root, word);
  if (longest_sub[0] == '\0')
    {
      free (longest_sub);
      return root;
    }
  // tracks position in tree
  int i;
  for (i = 0; longest_sub[i] != '\0'; i++)
    {
      int position = (int) longest_sub[i] - 'a';
      // keep moving to the deepest node in the specific substring
      if (temp->children[position] != NULL)
	{
	  temp = temp->children[position];
	}
      // if there is no node, we return
      else
	{
	  free (longest_sub);
	  return root;
	}
    }

  // delete_tree the sequence that corresponds to the word we found
  int len = strlen (word);
  for (; i < len; i++)
    {
      int position = (int) word[i] - 'a';
      // deletes the remaining sequence
      if (temp->children[position])
	{
	  Tree *rm_node = temp->children[position];
	  temp->children[position] = NULL;
	  recover_mem (rm_node);
	}
    }
  free (longest_sub);
  return root;
}

// prints the nodes of the tree
void
print (Tree * root)
{
  if (!root)
    return;
  Tree *temp = root;
  printf ("%c -> ", temp->data);
  for (int i = 0; i < N; i++)
    {
      print (temp->children[i]);
    }
}

void
print_search (Tree * root, char *word)
{
  printf ("Searching for %s: ", word);
  if (search (root, word) == 0)
    printf ("Not Found\n");
  else
    printf ("Found!\n");
}

// main function
int
main ()
{
  Tree *root = create_Tree ('\0');
  root = insert (root, "hello");
  root = insert (root, "world");
  root = insert (root, "computer");
  root = insert (root, "science");
  print_search (root, "hello");
  print_search (root, "sharlene");
  print_search (root, "science");
  print_search (root, "world");
  print_search (root, "what");

  return 0;
}
