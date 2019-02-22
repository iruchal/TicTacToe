#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tictactoe.h"


int main (int argc, char *argv[]){
	unsigned short i = 0;
	char b3 [10];
	
	char winningUser;
	int userInput;
	struct strategy_struct record;
	FILE *fp;
	fp = fopen ("strategyfile.bin", "rb+");

	userInput = atoi(argv[1]);							/* converts the string input to integer */


		for (i=0; i<=19682; ++i){
			b3fromus(b3,i);
			winningUser = winner(i);
			if((get_move(b3)-'0') == userInput){
				if (winningUser == '1' || winningUser == '2'){					
					record.best_move = -1;
					record.winner = winner(i);
					set_record(fp, i, &record);
				}
					else {

						evaluate_move(fp,i,&record);
						set_record(fp,i,&record);
					}
				}
			}
			fclose(fp);
			return 0;
	}

