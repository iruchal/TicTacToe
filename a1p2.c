#include <stdio.h>
#include "tictactoe.h"

int main() {

    int i = 0;
    struct strategy_struct structure ;

    FILE* strategyfile;

    structure.best_move = -1 ;
    structure.winner = ' ';

    strategyfile = fopen("strategyfile.bin", "wb");

    for(i = 0; i <= 19682; i++){
    	fseek(strategyfile, sizeof(struct strategy_struct)*i, SEEK_SET);
        fwrite(&structure, sizeof(struct strategy_struct), 1, strategyfile);
    } 

    return 0;

	}


