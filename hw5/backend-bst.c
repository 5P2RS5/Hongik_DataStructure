#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend-bst.h"

#define POOL_SIZE 10

// record structure
struct record {
  char name[3];
  char number[4];
  struct record * left;
  struct record * right;
};

void print_name(struct record *);
void print_number(struct record *);

// pool of memory
static struct record pool[POOL_SIZE]; // static because pool is strictly private
struct record * top=pool;  // a pointer variable for pool stack top.

// comparison function for records
int compare(char key[3], struct record *);

// data
struct record * data = NULL; // Initially NULL.


void init_pool() // Initialize the pool; Use right instead of next!!!
{
  int i;
  struct record *r=pool;
  struct record *s;

  pool[POOL_SIZE-1].right=NULL;

  for(i=1;i<POOL_SIZE;i++) {
    s=r++;
    s->right=r;
  }
}

// Get a node from the pool. Returns NULL if pool is empty.
// When calling new_node(), make sure to check if it is NULL.
struct record * new_node()
{
  struct record *r;

  if(top==NULL)
    return NULL;

  r=top;
  top=r->right;  // Again, right instead of next.
  return r;
}

// Push a node to the pool.
void free_node(struct record *r)
{
  r->right=top;  // Again, right instead of next.
  top=r;
}


/***********************
Address Book by binary search tree
**************************/

void search(char name[3])
{
  struct record *r; // Pointer to record being compared.
                    //data or left/right field of a node.
  int result;
  r=data;

  while (r!=NULL) {
    if ((result=compare(name,r))<0)
      r=r->left;
    else if (result==0) {
      print_name(r);
      printf(" : ");
      print_number(r);
      printf(" was found.\n");
      return;
    }
    else // case >0
      r=r->right;
  }
  printf("Couldn't find the name.\n");
}


void add(char *name, char *number)
{
  struct record *p;
  struct record *q;
  struct record *r;
  int chk = 7;
  p = data;


  while(p != NULL)
  {
    chk = compare(name, p);

    if(chk == 0 || chk < 0)
    {
      q = p;
      p = p->left;
    }
    else
    {
      q = p;
      p = p->right;
    }
  }
  //printf("%d\n", chk);

  r = new_node();
  if(r == NULL)
  {
    printf("Can't add.  The pool is empty!\n");
  }
  else{
    int a, b;
    for(a = 0; a < 3; a++)
    {
      r->name[a] = name[a];
    }
    for(b = 0; b < 4; b++)
    {
      r->number[b] = number[b];
    }
    r->left = NULL;
    r->right = NULL;

    if(data == NULL)
    {
      data = r;
    }
    else
    {
      chk = compare(name, q);
      if(chk <= 0)
      {
        q->left = r;
      }
      else
      {
        q->right = r;
      }
    }

    printf("The name was successfully added!\n");
  }
}


// The most complicated.
void delete(char name[3])
{
  int chk;
  struct record *r = NULL;
  struct record *p = data;
  while(p != NULL)
  {
    chk = compare(name, p);
    if(chk == 0)
    {
      break;
    }
    else if(chk > 0)
    {
      r = p;
      p = p->right;
    }
    else
    {
      r = p;
      p = p->left;
    }
  }

  if(chk != 0)
  {
    printf("Couldn't find the name.\n");
  }
  else
  {
    if(p->left == NULL && p->right == NULL)
    {
      if(p == data)
      {
        data = NULL;
        free_node(p);
      }
      else
      {
        if(r->left == p)
        {
          r->left = NULL;
        }
        else
        {
          r->right = NULL;
        }
        free_node(p);
      }
    }
    else if((p->left == NULL && p->right != NULL) || (p->left != NULL && p->right == NULL))
    {
      if(p == data)
      {
        if(p->left == NULL)
        {
          data = p->right;
        }
        else
        {
          data = p->left;
        }
      }
      else{
        if(r->left == p)
        {
          if(p->left == NULL)
          {
            r->left = p->right;
          }
          else
          {
            r->left = p->left;
          }
        }
        else
        {
          if(p->left == NULL)
          {
            r->right = p->right;
          }
          else
          {
            r->right = p->left;
          }
        }
      }
      free_node(p);
    }
    else
    {
      struct record *fsuccessor = p;
      struct record *successor;
      successor = p->right;
      while(successor->left != NULL)
      {
        fsuccessor = successor;
        successor = successor->left;
      }
      if(fsuccessor->left == successor)
      {
        fsuccessor->left = successor->right;
      }
      else if (fsuccessor->right == successor)
      {
        fsuccessor->right = successor->right;
      }
      if(p == data)
      {
        successor->right = p->right;
        successor->left = p->left;
        data = successor;
      }
      else
      {
        if(r->left == p)
        {
          r->left = successor;
          successor->right = p->right;
          successor->left = p->left;
        }
        else
        {
          r->right = successor;
          successor->right = p->right;
          successor->left = p->left;
        }
      }
      free_node(p);
    }
    printf("The name was deleted.\n");
  }
}


/* Just a wrapper of strncmp().
Regard strncmp(a,b) as a-b.
Negative value if key is less than r.
​0​ if key and r are equal.
Positive value if key is greater than r. */
int compare(char key[3], struct record *r)
{
    return strncmp(key, r->name, 3);
}


void print_data(char * s, int n)
{
  int i;
  for (i=0; i<n; i++)
    putchar(s[i]);
}

void print_name(struct record *r)
{
  print_data(r->name, 3);
}

void print_number(struct record *r)
{
  print_data(r->number, 4);
}

void print_inorder(struct record *t)
{
  if(t == NULL)
  {
    return;
  }
  print_inorder(t->left);
  print_name(t);
  printf(" : ");
  print_number(t);
  printf("\n");
  print_inorder(t->right);
}

void print_list()
{
  print_inorder(data);
}

// returns the height of the BST.
int height(struct record *t)
{
  if(t == NULL)
  {
    return -1;
  }
  else
  {
    if(height(t->left) < height(t->right))
    {
      return height(t->right)+1;
    }
    else
    {
      return height(t->left)+1;
    }
  }
}

void print_height()
{
  printf("The Address Book BST's height is %d.\n", height(data));
}
