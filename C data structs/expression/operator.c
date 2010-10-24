/***************************************************************************
 *   Copyright (C) 2008 by Michael Fischer                                 *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/
/*
 *  operator.c
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
#include "operator.h"


struct operator {
	char symb;		
	int  prec; 
};

Operator newOperator( char opchar )
{
  Operator op = safe_malloc( sizeof *op );
  op->symb = opchar;
  switch (opchar){
    case '+': case '-':           op->prec = 1; break;
    case '*': case '/': case '%': op->prec = 2; break;
    case '^':                     op->prec = 3; break;
    default:                      op->prec = -1; break;
  }
  return op;
}   

void freeOperator( Operator op )
{
  free( op );
}

int precedenceOperator( const_Operator op) 
{ 
  return op->prec;
}	 

char symbolOperator( const_Operator op )
{
  return op->symb;

}	 

void printOperator( const_Operator op )
{
  printf( "Symbol: %c  Precedence: %d\n", op->symb, op->prec );
}
