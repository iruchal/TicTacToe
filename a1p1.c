#include<stdio.h>
#include<stdlib.h>
#include "tictactoe.h"

int main(int argc , char *argv[])
{
  

  unsigned short us;
  char b3[10];
  char board[60];
  char pos = '0';
  int i = 0;
  

  us = atoi(argv[1]) ;

   
  printf("Board number: %5d\n", us);
  b3fromus(b3, us);
  printf("Board b3: %9s\n", b3);


boardfromb3(board,b3);
printf("%s\n", board);

printf("Move: %c\n", get_move(b3) );
printf("Turn: %c\n", get_turn(b3) );
printf("Winner: %c\n\n", winner(us) );

boardtob3(b3,board);

for (i = 0; i<9; ++i){
  printf("%d -> %hd\n", i, next(us,pos+i));
}


return 0;
}

