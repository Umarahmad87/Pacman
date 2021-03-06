/*
 * Board.h
 *
 *  Created on: May 2, 2014
 *      Author: Sibt ul Hussain
 */
#ifndef _BOARD_H_
#define _BOARD_H_

#include <GL/glut.h>
#include <iostream>
#include "util.h"
using namespace std;
const int BOARD_Y = 28;
const int BOARD_X = 36;
enum BoardParts {
	NILL, // Prohibitive Empty space 0
	TLC, // Left corner top 1
	TRC, //Right corner top 2
	BLC, // Left corner bottom 3
	BRC, //Right corner bottom 4
	BT, // Border Drawing top 5
	BB, // Border Drawing bottom 6
	BL, // Border Drawing left 7
	BR, // Border Drawing right 8
	HL, // Horizontal line 9
	VL, // Vertical line 10
	GG, // Ghost Gate 11
	BTLC, // Border Left corner top 12
	BTRC, //Border Right corner top 13
	BBLC, //Border Left corner bottom 14
	BBRC, //Border Right corner bottom 15
	PEBB, // Pebbles 16
	VE, // Valid Empty, means pacman can move over here... 17
	SB, // Solid Ball 18
	GH, // Ghoust House 19
	SBR, // straight line with bottom right corner 20
	SBL, // straight line with bottom left corner 21
	// vertical straight lines for different border...
	VTR, // 22
	VTL, // 23
	VBR, //24
	VBL, // 25
	Extra
};
// defining some utility functions...
static int board_array[BOARD_X][BOARD_Y] = {
		{ 26, 26, 26, 26, 26, 26,26, 26, 26, 26,26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26 },
		{ 26,26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,26, 26, 26 },
		{ 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,26, 26, 26, 26, 26, 26, 26, 26 },
		{ BBRC, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,SBL, SBR, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, BBLC },
		{ 7, 16, 16, 16,16, 16, 16, 16, 16, 16, 16, 16, 16, 10, 10, 16, 16, 16, 16, 16, 16, 16,16, 16, 16, 16, 16, BR },
		{ 7, 16, BRC, 9, 9, BLC, 16, BRC, 9, 9, 9,BLC, 16, 10, 10, 16, BRC, 9, 9, 9, BLC, 16, BRC, 9, 9, BLC, 16, BR },
/*6 (1,26) */	{7, 16, 10, 26, 26, 10, 16, 10, 26, 26, 26, 10, 16, 10, 10, 16, 10, 26, 26, 26,10, 16, 10, 26, 26, 10, 16, BR },
		{ 7, 16, TRC, 9, 9, TLC, 16, TRC, 9, 9, 9, TLC, 16, TRC, TLC, 16, TRC,9, 9, 9, TLC, 16, TRC, 9, 9, TLC, 16, BR },
		{ 7, SB, 16, 16, 16,16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,16, 16, 16, 16, 16, SB, BR },
		{ 7, 16, BRC, 9, 9, BLC, 16, BRC,BLC, 16, BRC, 9, 9, 9, 9, 9, 9, BLC, 16, BRC, BLC, 16, BRC, 9,9, BLC, 16, BR },
		{ 7, 16, 2, 9, 9, 1, 16, 10, 10, 16, TRC, 9,9, 3, 4, 9, 9, 1, 16, 10, 10, 16, 2, 9, 9, 1, 16, BR },
		{ 7, 16,16, 16, 16, 16, 16, 10, 10, 16, 16, 16, 16, 10, 10, 16, 16, 16,16, 10, 10, 16, 16, 16, 16, 16, 16, BR },
		{ BTRC, 6, 6, 6, 6,BLC, 16, 10, TRC, 9, 9, BLC, 17, 10, 10, 17, BRC, 9, 9, TLC, 10,16, BRC, 6, 6, 6, 6, 12 },
		{ 26, 26, 26, 26, 26, 7, 16, 10, BRC, 9,9, TLC, 17, TRC, TLC, 17, TRC, 9, 9, BLC, 10, 16, 8, 26, 26, 26, 26,26 },
		{ 26, 26, 26, 26, 26, 7, 16, 10, 10, 17, 17, 17, 17, 17, 17, 17,17, 17, 17, 10, 10, 16, 8, 26, 26, 26, 26, 26 },
		{ 26, 26, 26, 26, 26, 7,16, 10, 10, 17, BRC, 6, 6, 11, 11, 6, 6, BLC, 17, 10, 10, 16, 8,26, 26, 26, 26, 26 },
		{ 5, 5, 5, 5, 5, TLC, 16, TRC, TLC, 17, 8, 19,19, 19, 19, 19, 19, 7, 17, TRC, TLC, 16, TRC, 5, 5, 5, 5, 5 },
		{17, 17, 17, 17, 17, 17, 16, 17, 17, 17, 8, 19, 19, 19, 19, 19,	19, 7, 17, 17, 17, 16, 17, 17, 17, 17, 17, 17 },
		{ BB, BB, BB,BB, BB, BLC, 16, BRC, BLC, 17, 8, 19, 19, 19, 19, 19, 19, 7, 17,BRC, BLC, 16, BRC, BB, BB, BB, BB, BB },
		{ 26, 26, 26, 26, 26, 7, 16,10, 10, 17, TRC, BT, BT, BT, BT, BT, BT, TLC, 17, 10, 10, 16, 8,26, 26, 26, 26, 26 },
		{ 26, 26, 26, 26, 26, 7, 16, 10, 10, 17, 17, 17, 17,17, 17, 17, 17, 17, 17, 10, 10, 16, 8, 26, 26, 26, 26, 26 },
		{ 26, 26,26, 26, 26, 7, 16, 10, 10, 17, BRC, HL, HL, HL, HL, HL, HL, BLC,VE, 10, 10, 16, 8, 26, 26, 26, 26, 26 },
		{ BBRC, 5, 5, 5, 5, TLC, 16,TRC, TLC, 17, TRC, HL, HL, BLC, BRC, HL, HL, TLC, 17, TRC, TLC,16, TRC, 5, 5, 5, 5, BBLC },
		{ 7, 16, 16, 16, 16, 16, 16, 16,16, 16, 16, 16, 16, VL, VL, 16, 16, 16, 16, 16, 16, 16, 16, 16,16, 16, 16, BR },
		{ 7, 16, BRC, HL, HL, BLC, 16, BRC, HL, HL,HL, BLC, 16, VL, VL, 16, BRC, HL, HL, HL, BLC, 16, BRC, HL, HL,BLC, 16, BR },
		{ 7, 16, TRC, HL, BLC, VL, 16, TRC, HL, HL, HL,TLC, 16, TRC, TLC, 16, TRC, HL, HL, HL, TLC, 16, VL, BRC, HL,TLC, 16, BR },
/* 26(1,26)*/{ 7, SB, 16, 16, VL, VL, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,16, 16, 16, 16, VL, VL, 16, 16, SB, BR },
		{ VTR, HL, BLC, 16,VL, VL, 16, BRC, BLC, 16, BRC, HL, HL, HL, HL, HL, HL, BLC, 16,BRC, BLC, 16, VL, VL, 16, BRC, HL, VTL },
		{ VBR, HL, TLC, 16,TRC, TLC, 16, VL, VL, 16, TRC, HL, HL, BLC, BRC, HL, HL, TLC,16, VL, VL, 16, TRC, TLC, 16, TRC, HL, VBL },
		{ 7, 16, 16, 16,16, 16, 16, VL, VL, 16, 16, 16, 16, VL, VL, 16, 16, 16, 16, VL,VL, 16, 16, 16, 16, 16, 16, BR },
		{ 7, 16, BRC, HL, HL, HL, HL,TLC, TRC, HL, HL, BLC, 16, VL, VL, 16, BRC, HL, HL, TLC, TRC,HL, HL, HL, HL, BLC, 16, BR },
		{ 7, 16, TRC, HL, HL, HL, HL, HL,HL, HL, HL, TLC, 16, TRC, TLC, 16, TRC, HL, HL, HL, HL, HL, HL,HL, HL, TLC, 16, BR },
		{ 7, 16, 16, 16, 16, 16, 16, 16, 16, 16,16, 16, PEBB, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,16, BR },
		{ BTRC, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB,BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BTLC },
		{ 26, 26, 26, 26, 26,26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,26, 26 },
		{ 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,26, 26, 26, 26, 26, 26, 26, 26, 26, 26 } };


static int board_array1[BOARD_X][BOARD_Y] = {
		{ 26, 26, 26, 26, 26, 26,26, 26, 26, 26,26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26 },
		{ 26,26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,26, 26, 26 },
		{ 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,26, 26, 26, 26, 26, 26, 26, 26 },
		{ BBRC, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,SBL, SBR, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, BBLC },
		{ 7, 16, 16, 16,16, 16, 16, 16, 16, 16, 16, 16, 16, 10, 10, 16, 16, 16, 16, 16, 16, 16,16, 16, 16, 16, 16, BR },
		{ 7, 16, BRC, 9, 9, BLC, 16, BRC, 9, 9, 9,BLC, 16, 10, 10, 16, BRC, 9, 9, 9, BLC, 16, BRC, 9, 9, BLC, 16, BR },
/*6 (1,26) */	{7, 16, 10, 26, 26, 10, 16, 10, 26, 26, 26, 10, 16, 10, 10, 16, 10, 26, 26, 26,10, 16, 10, 26, 26, 10, 16, BR },
		{ 7, 16, TRC, 9, 9, TLC, 16, TRC, 9, 9, 9, TLC, 16, TRC, TLC, 16, TRC,9, 9, 9, TLC, 16, TRC, 9, 9, TLC, 16, BR },
		{ 7, SB, 16, 16, 16,16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,16, 16, 16, 16, 16, SB, BR },
		{ 7, 16, BRC, 9, 9, BLC, 16, BRC,BLC, 16, BRC, 9, 9, 9, 9, 9, 9, BLC, 16, BRC, BLC, 16, BRC, 9,9, BLC, 16, BR },
		{ 7, 16, 2, 9, 9, 1, 16, 10, 10, 16, TRC, 9,9, 3, 4, 9, 9, 1, 16, 10, 10, 16, 2, 9, 9, 1, 16, BR },
		{ 7, 16,16, 16, 16, 16, 16, 10, 10, 16, 16, 16, 16, 10, 10, 16, 16, 16,16, 10, 10, 16, 16, 16, 16, 16, 16, BR },
		{ BTRC, 6, 6, 6, 6,BLC, 16, 10, TRC, 9, 9, BLC, 17, 10, 10, 17, BRC, 9, 9, TLC, 10,16, BRC, 6, 6, 6, 6, 12 },
		{ 26, 26, 26, 26, 26, 7, 16, 10, BRC, 9,9, TLC, 17, TRC, TLC, 17, TRC, 9, 9, BLC, 10, 16, 8, 26, 26, 26, 26,26 },
		{ 26, 26, 26, 26, 26, 7, 16, 10, 10, 17, 17, 17, 17, 17, 17, 17,17, 17, 17, 10, 10, 16, 8, 26, 26, 26, 26, 26 },
		{ 26, 26, 26, 26, 26, 7,16, 10, 10, 17, BRC, 6, 6, 11, 11, 6, 6, BLC, 17, 10, 10, 16, 8,26, 26, 26, 26, 26 },
		{ 5, 5, 5, 5, 5, TLC, 16, TRC, TLC, 17, 8, 19,19, 19, 19, 19, 19, 7, 17, TRC, TLC, 16, TRC, 5, 5, 5, 5, 5 },
		{17, 17, 17, 17, 17, 17, 16, 17, 17, 17, 8, 19, 19, 19, 19, 19,	19, 7, 17, 17, 17, 16, 17, 17, 17, 17, 17, 17 },
		{ BB, BB, BB,BB, BB, BLC, 16, BRC, BLC, 17, 8, 19, 19, 19, 19, 19, 19, 7, 17,BRC, BLC, 16, BRC, BB, BB, BB, BB, BB },
		{ 26, 26, 26, 26, 26, 7, 16,10, 10, 17, TRC, BT, BT, BT, BT, BT, BT, TLC, 17, 10, 10, 16, 8,26, 26, 26, 26, 26 },
		{ 26, 26, 26, 26, 26, 7, 16, 10, 10, 17, 17, 17, 17,17, 17, 17, 17, 17, 17, 10, 10, 16, 8, 26, 26, 26, 26, 26 },
		{ 26, 26,26, 26, 26, 7, 16, 10, 10, 17, BRC, HL, HL, HL, HL, HL, HL, BLC,VE, 10, 10, 16, 8, 26, 26, 26, 26, 26 },
		{ BBRC, 5, 5, 5, 5, TLC, 16,TRC, TLC, 17, TRC, HL, HL, BLC, BRC, HL, HL, TLC, 17, TRC, TLC,16, TRC, 5, 5, 5, 5, BBLC },
		{ 7, 16, 16, 16, 16, 16, 16, 16,16, 16, 16, 16, 16, VL, VL, 16, 16, 16, 16, 16, 16, 16, 16, 16,16, 16, 16, BR },
		{ 7, 16, BRC, HL, HL, BLC, 16, BRC, HL, HL,HL, BLC, 16, VL, VL, 16, BRC, HL, HL, HL, BLC, 16, BRC, HL, HL,BLC, 16, BR },
		{ 7, 16, TRC, HL, BLC, VL, 16, TRC, HL, HL, HL,TLC, 16, TRC, TLC, 16, TRC, HL, HL, HL, TLC, 16, VL, BRC, HL,TLC, 16, BR },
/* 26(1,26)*/{ 7, SB, 16, 16, VL, VL, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,16, 16, 16, 16, VL, VL, 16, 16, SB, BR },
		{ VTR, HL, BLC, 16,VL, VL, 16, BRC, BLC, 16, BRC, HL, HL, HL, HL, HL, HL, BLC, 16,BRC, BLC, 16, VL, VL, 16, BRC, HL, VTL },
		{ VBR, HL, TLC, 16,TRC, TLC, 16, VL, VL, 16, TRC, HL, HL, BLC, BRC, HL, HL, TLC,16, VL, VL, 16, TRC, TLC, 16, TRC, HL, VBL },
		{ 7, 16, 16, 16,16, 16, 16, VL, VL, 16, 16, 16, 16, VL, VL, 16, 16, 16, 16, VL,VL, 16, 16, 16, 16, 16, 16, BR },
		{ 7, 16, BRC, HL, HL, HL, HL,TLC, TRC, HL, HL, BLC, 16, VL, VL, 16, BRC, HL, HL, TLC, TRC,HL, HL, HL, HL, BLC, 16, BR },
		{ 7, 16, TRC, HL, HL, HL, HL, HL,HL, HL, HL, TLC, 16, TRC, TLC, 16, TRC, HL, HL, HL, HL, HL, HL,HL, HL, TLC, 16, BR },
		{ 7, 16, 16, 16, 16, 16, 16, 16, 16, 16,16, 16, PEBB, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,16, BR },
		{ BTRC, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB,BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BTLC },
		{ 26, 26, 26, 26, 26,26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,26, 26 },
		{ 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,26, 26, 26, 26, 26, 26, 26, 26, 26, 26 } };






static int board_array2[BOARD_X][BOARD_Y] = {
		{ 26, 26, 26, 26, 26, 26,26, 26, 26, 26,26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26 },
		{ 26,26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,26, 26, 26 },
		{ 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,26, 26, 26, 26, 26, 26, 26, 26 },
		{ 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,SBL, SBR, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
		{ VE, 16, 16, 16,16, 16, 16, 16, 16, 16, 16, 16, 16, 10, 10, 16, 16, 16, 16, 16, 16, 16,16, 16, 16, 16, 16, VE },
		{ BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB,BLC, 16, 10, 10, 16, BRC, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB },
/*6 (1,26) */{26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, BL, 16, 10, 10, 16, BR, 26, 26, 26,26, 26, 26, 26, 26, 26, 26, 26 },
		{	BBRC, BT , BT , BT , BT , BT, BT, BT, BT, BT, BT, TLC, 16, TRC, TLC, 16, TRC,BT, BT, BT, BT, BT, BT, BT, BT, BT, BT, BBLC },
		{ 7, SB, 16, 16, 16,16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,16, 16, 16, 16, 16, SB, BR },
		{ 7, 16, BRC, HL, HL, BLC, 16, BRC,BLC, 16, BRC, 9, 9, 9, 9, 9, 9, BLC, 16, BRC, BLC, 16, BRC, 9,9, BLC, 16, BR },
		{ 7, 16, 10, 26, 26, 10, 16, 10, 10, 16, TRC, 9,9, 3, 4, 9, 9, 1, 16, 10, 10, 16, 10, 26, 26, 10, 16, BR },
		{ 7, 16,10, 26, 26, 10, 16, 10, 10, 16, 16, 16, 16, 10, 10, 16, 16, 16,16, 10, 10, 16, 10, 26, 26, 10, 16, BR },
		{ 7, 16,10 , 26, 26,10, 16, 10, TRC, 9, 9, BLC, 17, 10, 10, 17, BRC, 9, 9, TLC, 10,16, 10, 26, 26, 10, 16, BR },
		{ 7, 16, 10, 26, 26, 10, 16, 10, BRC, 9,9, TLC, 17, TRC, TLC, 17, TRC, 9, 9, BLC, 10, 16, 10, 26, 26, 10, 16,BR },
		{ 7, 16, 10, 26, 26, 10, 16, 10, 10, 17, 17, 17, 17, 17, 17, 17,17, 17, 17, 10, 10, 16, 10, 26, 26, 10, 16, BR },
		{ 7, 16, 10, 26, 26, 10,16, 10, 10, 17, BRC, 6, 6, 11, 11, 6, 6, BLC, 17, 10, 10, 16,   10, 26, 26, 10, 16, BR },
		{ 7, 16, TRC, 9, 9, TLC, 16, TRC, TLC, 17, 8, 19,19, 19, 19, 19, 19, 7, 17, TRC, TLC, 16, TRC, 9, 9, TLC, 16, BR },
		{7, 16, 16, 16, 16, 16, 16, 17, 17, 17, 8, 19, 19, 19, 19, 19,	19, 7, 17, 17, 17,  16,    16, 16, 16, 16, 16, BR },
		{ BTRC, BB, BB,BB, BB, BLC, 16, BRC, BLC, 17, 8, 19, 19, 19, 19, 19, 19, 7, 17,BRC, BLC, 16, BRC, BB , BB, BB, BB, BTLC },
		{ 26, 26, 26, 26, 26, 7, 16,10, 10, 17, TRC, BT, BT, BT, BT, BT, BT, TLC, 17, 10, 10, 16, 8, 26 , 26, 26, 26, 26 },
		{ 26, 26, 26, 26, 26, 7, 16, 10, 10, 17, 17, 17, 17,17, 17, 17, 17, 17, 17, 10, 10, 16, 8, 26, 26, 26, 26, 26 },
		{ 26, 26,26, 26, 26, 7, 16, 10, 10, 17, BRC, HL, HL, HL, HL, HL, HL, BLC,VE, 10, 10, 16, 8, 26, 26, 26, 26, 26 },
		{ BBRC, 5, 5, 5, 5, TLC, 16,TRC, TLC, 17, TRC, HL, HL, BLC, BRC, HL, HL, TLC, 17, TRC, TLC,16, TRC, 5, 5, 5, 5, BBLC },
		{ 7, 16, 16, 16, 16, 16, 16, 16,16, 16, 16, 16, 16, VL, VL, 16, 16, 16, 16, 16, 16, 16, 16, 16,16, 16, 16, BR },
		{ 7, 16, BRC, HL, HL, BLC, 16, BRC, HL, HL,HL, BLC, 16, VL, VL, 16, BRC, HL, HL, HL, BLC, 16, BRC, HL, HL,BLC, 16, BR },
		{ 7, 16, TRC, HL, BLC, VL, 16, TRC, HL, HL, HL,TLC, 16, TRC, TLC, 16, TRC, HL, HL, HL, TLC, 16, VL, BRC, HL,TLC, 16, BR },
/* 26(1,26)*/{ 7, SB, 16, 16, VL, VL, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,16, 16, 16, 16, VL, VL, 16, 16, SB, BR },
		{ VTR, HL, BLC, 16,VL, VL, 16, BRC, BLC, 16, BRC, HL, HL, HL, HL, HL, HL, BLC, 16,BRC, BLC, 16, VL, VL, 16, BRC, HL, VTL },
		{ VBR, HL, TLC, 16,TRC, TLC, 16, VL, VL, 16, TRC, HL, HL, BLC, BRC, HL, HL, TLC,16, VL, VL, 16, TRC, TLC, 16, TRC, HL, VBL },
		{ 7, 16, 16, 16,16, 16, 16, VL, VL, 16, 16, 16, 16, VL, VL, 16, 16, 16, 16, VL,VL, 16, 16, 16, 16, 16, 16, BR },
		{ 7, 16, BRC, HL, HL, HL, HL,TLC, TRC, HL, HL, BLC, 16, VL, VL, 16, BRC, HL, HL, TLC, TRC,HL, HL, HL, HL, BLC, 16, BR },
		{ 7, 16, TRC, HL, HL, HL, HL, HL,HL, HL, HL, TLC, 16, TRC, TLC, 16, TRC, HL, HL, HL, HL, HL, HL,HL, HL, TLC, 16, BR },
		{ 7, 16, 16, 16, 16, 16, 16, 16, 16, 16,16, 16, PEBB, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,16, BR },
		{ BTRC, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BB,BB, BB, BB, BB, BB, BB, BB, BB, BB, BB, BTLC },
		{ 26, 26, 26, 26, 26,26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,26, 26 },
		{ 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,26, 26, 26, 26, 26, 26, 26, 26, 26, 26 } };









class Board {
protected:
	int pebbles_left;
	int xcellsize, ycellsize;
	int lwidth;
	float cwidth;
	//array for eating
	int tp_array[31][28];
	ColorNames pcolor, bcolor, gcolor;

	float x_axis;
	float y_axis;
	float x_cell;
	float y_cell;
	int Mov;
	int increment;

public:
	int record;
	int movement;

	static const int BOARD_X;
	static const int BOARD_Y;
	Board(int xsize =20 , int ysize= 20 );

	virtual ~Board(void);
	virtual int Radius();
	//draw the board
	virtual void Draw(int);
	virtual void Load_Level(int);
	virtual string Score();
	virtual void Score(int);
	virtual void Reset(int x,int y);
	virtual void Movement();
	virtual void Movement2();
	virtual void Search(int,int);
	virtual void Start(int);
	virtual void Score_Reset();
	virtual int score2();
	virtual void Frightn(int);
	virtual	int Frightn();
	void SetColor(int);
	virtual bool Block_left();
	virtual bool Block_right();
	virtual bool Block_up();
	virtual bool Block_down();
	/*void Inc(int n){
		this->increment=n;
	}*/
	int Pebbles(){
		return pebbles_left;
	}
	void Pebbles_Reset(){
		pebbles_left=246;
	}
	static int GetBoardX() {
		return BOARD_X;
	}
	static int GetBoardY() {
		return BOARD_Y;
	}
	int GetMidX() {
		return BOARD_Y * xcellsize / 2.0;
	}
	int GetMidY() {
		return BOARD_X * ycellsize / 2.0;
	}
	int GetCellSize() {
		return xcellsize;
	}
	void GetInitPacmanPosition(int &x, int &y) {
		x = 14 * xcellsize;
		y = 9 * ycellsize + ycellsize / 2;
	}
	void GetInitPinkyPosition(int &x, int &y) {
		x = 11 * xcellsize/* - xcellsize / 2.0*/;
		y = 18 * ycellsize - ycellsize / 2.0;
	}
	void GetInitTextPosition(int &x, int &y) {
		x = 13 * xcellsize;
		y = 14 * ycellsize;
	}
	void xyCell(){
		cout<<"xcell size="<<xcellsize<<endl;
		cout<<"ycell size="<<ycellsize<<endl;
	}
	void Xpp();
		void Xmm();
		void Ypp();
		void Ymm();
		virtual int RemovePebbles();
		void GetPixel(float &x, float &y){
				x=x_axis;
				y=y_axis;
			//	cout<<"x_cell="<<x_cell<<" y_cell="<<y_cell<<endl;

		}
		void GetCell(float &x, float &y){
					x=x_cell;
					y=y_cell;
					//cout<<"x_cell="<<x_cell<<" y_cell="<<y_cell<<endl;
			}
		float getX(){
				return x_axis;
			}
		float getY(){
				return y_axis;
				}
		int	GetMove(){
				return Mov;
			}
		void Move(int n){
			Mov+=n;
		}
};

class Pacman:public Board {
	int score;
	int radius;
public:
	//static int Move=0;
	Pacman(int x=13, int y=9);
	int RemovePebbles();
	string Score();
	void Score(int);
	int score2();
	int Radius();
	void Score_Reset();
	void Reset(int x=13,int y=9);
	void Movement();
	void Load_Level(int);
	bool Block_left();
	bool Block_right();
	bool Block_up();
	bool Block_down();
	virtual ~Pacman(){}


};
#endif
