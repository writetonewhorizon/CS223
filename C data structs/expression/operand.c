/***************************************************************************
 *   Copyright (C) 2008 by Michael Fischer                                 *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/
/*
 *  operand.c
 *
 *  Created by Michael Fischer on 4/10/2006
 *  fischer-michael@cs.yale.edu
 *  For use in Yale course CPSC 223b, Spring 2006
 *
 *  Derived from C++ code by 
 *  Alice E. Fischer  June 9, 2002
 */

#include <stdio.h>
#include "util.h"
#include "operand.h"

Operand newOperand( double val )
{
  Operand dbl = safe_malloc( sizeof *dbl );
  *dbl = val;
  return dbl;
}   

void freeOperand( Operand x )
{
  free( x );
}

double value( const_Operand x )
{
  return *x;
}	 

void printOperand( const_Operand x )
{
  printf( "%g ", value( x ) );  
}
