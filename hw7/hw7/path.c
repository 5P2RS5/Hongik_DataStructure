#include <stdio.h>
#include "backend.h"


/****************************************
Implement Breadth-First Search on the graph constructed in "backend.c" and
use it in the find_path() below.

You can access functions and data structures constructed in "backend.c" via
"backend.h"
*****************************************/


char adj_mat[N][N];
char words[5757][5];
char data[100];


void file_r()
{
    FILE *f;
    f = fopen("words.dat", "r");
    int i;
    for (i = 0; i < 5762; i++) {
        fgets(data, sizeof(data), f);
        if(data[0] == '*')
        {
            continue;
        }
        int j;
        for (j = 0; j < 5; j++) {
            words[i - 4][j] = data[j];
        }
    }
    fclose(f);
}

void init_G_matrix()
{
  int i,j,l;

  for (i=0;i<N;i++)
    for (j=0;j<N;j++)
      adj_mat[i][j]=adjacent(words[i],words[j]);
}

int state_and_parent[5757][2];// [0] == state [1] == parent
                              // state = 0 == undiscovered, 1 == discovered

int shortest_path(char s[5], char t[5])
{
    int i;
    for(i = 0; i < 5757; i++) //상태와 부모 초기화
    {
      state_and_parent[i][0] = 0;
      state_and_parent[i][1] = -1;
    }

    int a = search_index(s);
    int b = search_index(t);

    int Q_Q[5757];
    for(i = 0; i < 5757; i++)
    {
      Q_Q[i] = -1;
    }

    state_and_parent[a][0] = 1;
    Q_Q[0] = a;
    int j = 1;
    int cur_idx = 0;
    while(1)
    {
      int cur = Q_Q[cur_idx];

      if(cur == -1)
        break;

      for(i = 0; i < 5757; i++)
      {
        if(adj_mat[cur][i] == 1)
        {
          if(state_and_parent[i][0] == 0)
          {
            state_and_parent[i][0] = 1;
            Q_Q[j] = i;
            state_and_parent[i][1] = cur;
            j++;
            if(b == i)
              return 1;
          }
        }
      }
      cur_idx++;
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
