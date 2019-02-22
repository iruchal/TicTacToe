#include <stdio.h>
#include <string.h>
#include "tictactoe.h"
#include <stdlib.h>



unsigned short b3tous (char b3[10]) {
  unsigned short us = 0;
  int i=0;
  int power = 1;

    for (i=8; i>=0; --i){                     /* This loop decrements. As the index decreases, the power increases by multiples of 3 each time. */
      us = us + ((b3[i] - '0') * power);      /* The "- 0" converts the char to an integer */
      power = power * 3;
    }
return us;
}

void b3fromus(char b3[10], unsigned short us) {
  int i=8;
  b3[9] = '\0';

  while (us > 0){                             
    b3[i] = (us % 3) + '0';
    us = us / 3;
    i = i - 1;
  }
  if (i > 0){
    for(;i>=0;i--){
      b3[i] = '0';
    }
  }

}

void debug (unsigned short us) {
  
  char b3[10];
  char board[60];
  char pos = '0';
  int i = 0;
  
  printf("Board number: %5d\n", us);
  b3fromus(b3, us);
  printf("Board b3: %9s\n", b3);
  printf("Board pic: \n");


boardfromb3(board,b3);
printf("%s\n", board);

printf("Move: %c\n", get_move(b3) );
printf("Turn: %c\n", get_turn(b3) );
printf("Winner: %c\n\n", winner(us) );

boardtob3(b3,board);

for (i = 0; i<9; ++i){
  printf("%d -> %hd\n", i, next(us,pos+i));
}

}

void debugTwo (unsigned short us){
    char b3[10];
  char board[60];
  char pos = '0';
  int i = 0;
  struct strategy_struct record;
  FILE* fp = fopen("strategyfile.bin", "rb");
  get_record(fp, us, &record); 

  printf("Board number: %5d\n", us);
  b3fromus(b3, us);
  printf("Board b3: %9s\n", b3);


boardfromb3(board,b3);
printf("%s\n", board);

printf("Move: %c\n", get_move(b3) );
printf("Turn: %c\n", get_turn(b3) );
printf("Winner: %c\n\n", winner(us) );

boardtob3(b3,board);
printf("best_move= %d, winner= %c", record.best_move, record.winner);
for (i = 0; i<9; ++i){
  printf("%d -> %hd\n", i, next(us,pos+i));
}
}



void boardfromb3(char board[60], char b3[10]) {

  int index, i, secondNum = 0;
  int b = 1;
  strcpy(board,"   |   |   \n---+---+---\n   |   |   \n---+---+---\n   |   |   \0");
  


for (i=0; i<=8; ++i){                 /* Each index is a slot for an 'X' or 'O' to be placed. */
    index = 3 * i + b;                /* This line calculates the first number of the piece index. Uses the (mx+b) formula, b increments each loop iteration.*/
    secondNum = (i/3) * 12;           /* The updated index is the sum of the first and second number resulting in the piece index */
    index += secondNum;
    ++b;


    switch(b3[i] - '0')
    {
      case 2:
        board[index] = 'X';         
        break;

      case 1:
        board[index] = 'O';
        break;

      case 0:
        board[index] = ' ';
        break;

      default:
        fprintf( stderr, "Error: bad value in b3\n" );
              exit(-1);
              break;
    }

  }
  return;
 
}


void boardtob3(char b3[10], char board[60]) {

  int index, i, secondNum = 0;                                          
  int b = 1;
  
  


for (i=0; i<=8; ++i){                             /* reuse of previous code from boardfromb3 function */
    index = 3 * i + b;
    secondNum = (i/3) * 12;
    index += secondNum;
    ++b;


    switch(board[index])
    {
      case 'X':
        b3[i] = '2';
        break;

      case 'O':
        b3[i] = '1';
        break;

      case ' ':
        b3[i] = '0';
        break;

      default:
        fprintf( stderr, "Error: bad value in b3\n" );
              exit(-1);
              break;
    }

  }
  return;
 
}


char get_move( char b3[10] ) {

int i,moveNumber = 0;
  
for (i=0; i<=8; ++i){                       /* As long as user doesn't input null, move number is incremented*/
  if (b3[i]!= '0'){
    moveNumber += 1;
  }
}
  return moveNumber + '0';
}

char get_turn(char b3[10]){

char moveNumb = get_move(b3);
int turn;
moveNumb = moveNumb - '0';
turn = moveNumb + 1;                                

if (moveNumb % 2 == 0){                 /* If the move number mod 2 results in 0, it is X's turn since X always goes first. Otherwise, it is O's turn */
turn = 2;
}
else {
  turn = 1;
}

return turn + '0';

}


char winner (unsigned short us){
  unsigned short dupUS = us;
  char b3[10];
  int i = 0;
  char gameWinner;

  b3fromus(b3,dupUS);                                     /* Recall of b3fromus function to convert from b3 to us.*/
                                                          /* Conditional statements for every possible way a user can win */


    /* Check for rows*/

  if (b3[0] == '1' && b3[1] == '1' && b3[2] == '1'){
    gameWinner = '1';
    return gameWinner;
  }

  else if (b3[3] == '1' && b3[4] == '1' &&  b3[5] == '1'){
     gameWinner = '1';
    return gameWinner; 
  }
   else if (b3[6] == '1' && b3[7] == '1' &&  b3[8] == '1'){
     gameWinner = '1';
    return gameWinner; 
  }

  else if (b3[0] == '2' && b3[1] == '2' && b3[2] == '2'){
    gameWinner = '2';
    return gameWinner;
  }
  else if (b3[3] == '2' && b3[4] == '2' && b3[5] == '2'){
    gameWinner = '2';
    return gameWinner;
  }
  else if (b3[6] == '2' && b3[7] == '2' && b3[8] == '2'){
    gameWinner = '2';
    return gameWinner;
  }

  /* Check for columns*/

  else if (b3[0] == '1' && b3[3] == '1' && b3[6] == '1'){
    gameWinner = '1';
    return gameWinner;
  }
  else if (b3[1] == '1' && b3[4] == '1' && b3[7] == '1'){
    gameWinner = '1';
    return gameWinner;
  }
  else if (b3[2] == '1' && b3[5] == '1' && b3[8] == '1'){
    gameWinner = '1';
    return gameWinner;
  }


  else if (b3[0] == '2' && b3[3] == '2' && b3[6] == '2'){
    gameWinner = '2';
    return gameWinner;  }
  else if (b3[1] == '2' && b3[4] == '2' && b3[7] == '2'){
    gameWinner = '2';
    return gameWinner;
  }
  else if (b3[2] == '2' && b3[5] == '2' && b3[8] == '2'){
    gameWinner = '2';
    return gameWinner;
  }


   /* Check for diagonals*/
  
  else if (b3[0] == '1' && b3[4] == '1' && b3[8] == '1'){
    gameWinner = '1';
    return gameWinner;
  }
  else if (b3[2] == '1' && b3[4] == '1' && b3[6] == '1'){
    gameWinner = '1';
    return gameWinner;
  }

  else if (b3[0] == '2' && b3[4] == '2' && b3[8] == '2'){
    gameWinner = '2';
    return gameWinner;
  }
  else if (b3[2] == '2' && b3[4] == '2' && b3[6] == '2'){
    gameWinner = '2';
    return gameWinner;
  }

 for(i = 0;i<=8;i++){
        if(b3[i] == '0'){
          gameWinner = ' ';
          return gameWinner;
        }
      }
      return ' ';

    }


    unsigned short next(unsigned short us, char pos){

      unsigned short boardNum;
      char currentTurn;
      char currB3[10];
      b3fromus(currB3, us);
      
      
      currentTurn = get_turn(currB3);


      if (currB3[pos - '0'] != '0'){            /* - '0' converts the char to int */
        return 0;
      }

      else if (currB3[pos - '0']== '0'){        
        currB3[pos - '0'] = currentTurn;        
        boardNum = b3tous(currB3);              /* - The b3tous function called, converts boardNum to unsigned  */
        return boardNum;
      }
      return ' ';
    }

    void get_record( FILE *fp, unsigned short us, struct strategy_struct *record) {
    
      fseek (fp, sizeof(struct strategy_struct)*us, SEEK_SET);
      fread (record, sizeof(struct strategy_struct),1,fp);
}

void set_record( FILE *fp, unsigned short us, struct strategy_struct *record) {
    
      fseek (fp, sizeof(struct strategy_struct)*us, SEEK_SET);
      fwrite (&record, sizeof(struct strategy_struct),1,fp);
}


    void evaluate_move (FILE *fp,unsigned short board,struct strategy_struct *record) {
  int i = 0;

  char nextBoard;
  char turn;
  char newB3[10];
  char userWinner;
  int foundTie = 0;
  char legal_move;
  char tempTie;
  struct strategy_struct rec;

  for(i=0;i<9;i++){
     nextBoard = next(board,i + '0');
     if(nextBoard == 0){
       continue;
     }
     b3fromus(newB3,board);
     turn = get_turn(newB3);

     get_record(fp,nextBoard,&rec);
     userWinner = winner(nextBoard);
     if(userWinner == turn){
       record->best_move = i;
       record->winner = turn;
       return;
     } else if(userWinner == '0'){
       foundTie = 1;
       tempTie = i;
     } else {
       legal_move = i;
     }
  }

  if(foundTie){
    record->best_move = tempTie;
    record->winner = '0';
  } else {
    record->best_move = legal_move;
    if(turn == '1'){
      record->winner = '2';
    } else {
      record->winner = '1';
    }
  }

}







