#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backend.h"
#include "memory.h"

void print_name(struct record *);
void print_number(struct record *);
void print_data(char *, int);

// data
struct record * data = NULL; // Initially NULL.


void init()
{
  init_pool();
}


void add(char *name, char *number)
{
  struct record * p;
  int i, j;

  p = new_node();

  if(p == NULL)
  {
    printf("Can't add.  The address book is full!\n");
  }
  else
  {
    for(i = 0; i < 3; i++)
    {
      p->name[i] = name[i];
    }
    for(j = 0; j < 4; j++)
    {
      p->number[j] = number[j];
    }
    if(data == NULL)
    {
      data = p;
      data->next = NULL;
    }
    else
    {
      p->next = data;
      data = p;
    }
  }
}


/* Just a wrapper of strncmp(), except for the case r is NULL.
Regard strncmp(a,b) as a-b, that is,
Negative value if key is less than r.
​0​ if key and r are equal.
Positive value if key is greater than r. */
int compare(char key[3], struct record *r)
{
  if (r==NULL)
    return -1;
  else
    return strncmp(key, r->name, 3);
}


void search(char name[3])
{
  struct record *r=data;
  int result;

  while(r!=NULL && (result=compare(name,r))!=0)
    r=r->next;
  if(r==NULL)
    printf("Couldn't find the name.\n");
  else {
    print_name(r);
    printf(" : ");
    print_number(r);
    printf(" was found.\n");
  }
}


void delete(char name[3])
{
  if(data == NULL)
  {
    printf("Couldn't find the name.\n");
  }
  struct record *r=data;
  struct record *d=data;
  int result;
  int i = 0;

  while(r!=NULL && (result=compare(name,r))!=0)
  {
    if(i == 0){
      r=r->next;
      i += 1;
    }
    else
    {
      r=r->next;
      d=d->next;
    }
  }
  if(r==NULL)
    {
      printf("Couldn't find the name.\n");
    }
  else
   {
     printf("The name was deleted.\n");
     if(i == 0)
     {
       data = d->next;
       free_node(d);
     }
     else
     {
       d->next = r->next;
       free_node(r);
     }
   }
}

// Prints ith name.
void print_name(struct record *r)
{
  print_data(r->name, 3);
}

// Prints ith number.
void print_number(struct record *r)
{
  print_data(r->number, 4);
}

void print_data(char * s, int n)
{
  int i;
  for (i=0; i<n; i++)
    putchar(s[i]);
}

void print_list()
{
  struct record * p;
  p = data;
  while(p != NULL)
  {
    print_name(p);
    printf(" : ");
    print_number(p);
    printf("\n");
    p = p->next;
  }
}
