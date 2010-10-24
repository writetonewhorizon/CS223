/***************************************************************************
 *   Copyright (C) 2008 by Michael Fischer                                 *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/
/*
 *  operator.h
 *
 *  Created by Michael Fischer on 4/10/2006
 *  fischer-michael@cs.yale.edu
 *  For use in Yale course CPSC 223b, Spring 2006
 *
 *  Derived from C++ code by 
 *  Alice E. Fischer  June 9, 2002
 */

#ifndef OPERATOR_H
#define OPERATOR_H

typedef struct operator* Operator;
typedef const struct operator* const_Operator;

// prototypes
Operator newOperator( char opchar );
void     freeOperator( Operator op );
int      precedenceOperator( const_Operator op);
char     symbolOperator( const_Operator op );
void     printOperator( const_Operator op );

#endif
