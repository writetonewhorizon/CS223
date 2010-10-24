/***************************************************************************
 *   Copyright (C) 2008 by Michael Fischer                                 *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/
/*
 *  eval.h
 *
 *  Created by Michael Fischer on 4/10/2006
 *  fischer-michael@cs.yale.edu
 *  For use in Yale course CPSC 223b, Spring 2006
 *
 *  Derived from C++ code by 
 *  Alice E. Fischer  June 9, 2002
 */

#ifndef EVAL_H
#define EVAL_H

//--------------------------------------------------------------------------
// A. Fischer, June 9, 2002
//
// Parse and evaluate a prefix expression.  All operators are binary; 
// they are: +, -, *, /, % (a mod b) and ^ (a to the power b) 
// Whitespace must be used to delimit both operators and operands. 
// Operands must start with a digit and may or may not have a decimal point.
// Operands must not exceed 30 keystrokes.

#include "stack.h"

typedef
enum { bad, number, op, lpar, rpar, end }
  Intype;

typedef struct eval* Eval;
typedef const struct eval* const_Eval;

/* prototypes */

Eval newEval( const char* expr );
void freeEval( Eval );
void instructions( void );
void printEval( const_Eval ev );
void printAnds( const Stack Ands );
void printAtors( const Stack Ators );

double evaluateEval( Eval );
Intype classifyEval( const_Eval );
void   forceEval( Eval, int rprec );
void   dispatchEval( Eval );
double expErrorEval( const_Eval );

#endif
