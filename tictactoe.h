/*
tictactoe.h
Header file
By: Ishan Ruchal(iruchal@uoguelph.ca)
Student ID: 1016494
*/

#ifndef TICTACTOE_H
#include <stdio.h>
#define TICTACTOE_H

struct  strategy_struct
{
	char winner;
	char best_move;
};

unsigned short b3tous(char b3[10]);

void b3fromus(char b3[10], unsigned short us);


void boardfromb3(char board[60], char b3[10]);

void boardtob3(char b3[10], char board[60]);

void debug (unsigned short us);

char get_move( char b3[10] );

char get_turn(char b3[10]);

char winner (unsigned short us);

unsigned short next(unsigned short us, char pos);

void get_record( FILE *fp, unsigned short us, struct strategy_struct *record );

void set_record( FILE *fp, unsigned short us, struct strategy_struct *record);

void evaluate_move (FILE *fp,unsigned short board,struct strategy_struct *record);

#endif
