#include <stdio.h>
#include "backend.h"


/****************************************
Implement Breadth-First Search on the graph constructed in "backend.c" and
use it in the find_path() below.

You can access functions and data structures constructed in "backend.c" via
"backend.h"
*****************************************/

int state_and_parent[5757][2];// [0] == state [1] == parent
                              // state = 0 == undiscovered, 1 == discovered
int shortest_path(char s[5], char t[5])
{
    int i;
    int Q_Q[5757];
    for(i = 0; i < 5757; i++) //상태와 부모 초기화
    {
      state_and_parent[i][0] = 0;
      state_and_parent[i][1] = -1;
      Q_Q[i] = -1;
    }

    int a = search_index(s);
    int b = search_index(t);

    state_and_parent[a][0] = 1;
    Q_Q[0] = a;
    int j = 1;
    int cur_idx = 0;
    while(1)
    {
      int cur = Q_Q[cur_idx];
      cur_idx++;
      if(cur == -1)
        break;

      struct node *p = adj_list[cur];
      while(p != NULL)
      {
        int spi = p->index;
        if(state_and_parent[spi][0] == 0)
        {
          state_and_parent[spi][0] = 1;
          Q_Q[j] = spi;
          state_and_parent[spi][1] = cur;
          j++;
          if(b == spi)
          {
            return 1;
          }
        }
        p = p->next;
      }
    }
    return 0;
}
void print_path(char start[5], char goal[5])
{
  int path[5757];
  int v = search_index(goal);
  int i = 0;
  while(v != search_index(start))
  {
    path[i] = v;
    v = state_and_parent[v][1];
    i++;
  }
  path[i] = search_index(start);
  int cnt = i;
  for(i; i >= 0; i--)
  {
    printf("          %d ", cnt - i);
    print_word(path[i]);
    printf("\n");
  }
}

void find_path(char start[5], char goal[5])
{
  int i,j,k,l;

  i=search_index(start);
  j=search_index(goal);

  if (i<0) {
    printf("Sorry. ");
    print_five_chars(start);
    printf(" is not in the dicitonary.");
  }
  else if (j<0) {
    printf("Sorry. ");
    print_five_chars(goal);
    printf(" is not in the dicitonary.");
  }
  else {
    int chk = shortest_path(start, goal);
    if(chk == 0)
    {
      printf("Sorry. There is no path from ");
      print_five_chars(start);
      printf(" to ");
      print_five_chars(goal);
      printf(".\n");
    }
    else
    {
      print_path(start, goal);
    }
  }

}
