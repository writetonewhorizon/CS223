/***************************************************************************
 *   Copyright (C) 2008 by Michael Fischer                                 *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/
/*
 *  evalmain.c
 *
 *  Created by Michael Fischer on 4/10/2006
 *  fischer-michael@cs.yale.edu
 *  For use in Yale course CPSC 223b, Spring 2006
 *
 *  Derived from C++ code by 
 *  Alice E. Fischer  June 9, 2002
 */

#include <stdio.h>
#include "eval.h"

// =========================================================================
int main( void ) 
{
  char buf[256];
  double answer;
  
  instructions();
  for(;;){
    printf( "\nEnter an expression:\n\t" );
    int n = scanf( "%255[^\n]%*c", buf );
    if (n != 1 || buf[0] == ';') break;
    Eval ev = newEval( buf );
    answer = evaluateEval( ev );
    freeEval( ev );
    printf( "%g = %s\n", answer, buf );
  }
  printf( "\nNormal termination\n" );
}
