/***************************************************************************
 *   Copyright (C) 2008 by Michael Fischer                                 *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/
/*
 *  operand.h
 *
 *  Created by Michael Fischer on 4/10/2006
 *  fischer-michael@cs.yale.edu
 *  For use in Yale course CPSC 223b, Spring 2006
 *
 *  Derived from C++ code by 
 *  Alice E. Fischer  June 9, 2002
 */

#ifndef OPERAND_H
#define OPERAND_H

typedef double* Operand;
typedef const double* const_Operand;

// prototypes
Operand newOperand( double val );
void    freeOperand( Operand x );
double  value( const_Operand x );
void    printOperand( const_Operand x );

#endif
