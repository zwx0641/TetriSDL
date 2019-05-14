

#include <SDL.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#ifndef _TETRIS_CONSTS  //to avoid repeatness of the constants
#define _TETRIS_CONSTS

#define ROWS 30     //width of the play area
#define COLS 10     //height of the play area

/*
 * AAA   A     A    AA
 *  A    AAA   A   AA
 *             A
 * AA      A   A   AA
 * AA    AAA        AA
 */


/* *a**
   *a**
   *a**
   *a**
*/
 const int shape_bar[4][4] = {
 		{0, 0, 0, 0},
 		{0, 0, 0, 0},
 		{1, 1, 1, 1},
 		{0, 0, 0, 0}
 };

/* ****
   *aa*
   *aa*
   ****
*/
 const int shape_square[4][4] = {
 		{0, 0, 0, 0},
 		{0, 1, 1, 0},
 		{0, 1, 1, 0},
 		{0, 0, 0, 0}
 };

/* ****
   *a**
   *aaa
   ****
*/
 const int shape_j[4][4] = {
 		{0, 0, 0, 0},
 		{1, 0, 0, 0},
 		{1, 1, 1, 0},
 		{0, 0, 0, 0}
 };

/*  **a*
    aaa*
    ****
    ****
*/
 const int shape_l[4][4] = {
 		{0, 0, 1, 0},
 		{1, 1, 1, 0},
 		{0, 0, 0, 0},
 		{0, 0, 0, 0}
 };

/* *aa*
   aa**
   ****
   ****
*/
 const int shape_s[4][4] = {
 		{0, 1, 1, 0},
 		{1, 1, 0, 0},
 		{0, 0, 0, 0},
 		{0, 0, 0, 0}
 };

/*  aa**
    *aa*
    ****
    ****
*/
 const int shape_z[4][4] = {
 		{1, 1, 0, 0},
 		{0, 1, 1, 0},
 		{0, 0, 0, 0},
 		{0, 0, 0, 0}
 };

/* *a**
   aaa*
   ****
   ****
*/
 const int shape_t[4][4] = {
 		{0, 1, 0, 0},
 		{1, 1, 1, 0},
 		{0, 0, 0, 0},
 		{0, 0, 0, 0}
 };

//The array of all shapes
 const int (*shapes[7])[4][4] = {
 	&shape_bar,
 	&shape_square,
 	&shape_l,
 	&shape_j,
 	&shape_s,
 	&shape_z,
 	&shape_t,
 };


#endif
