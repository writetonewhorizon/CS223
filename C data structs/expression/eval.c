/***************************************************************************
 *   Copyright (C) 2008 by Michael Fischer                                 *
 *   fischer-michael@cs.yale.edu                                           *
 *                                                                         *
 *   For use in Yale course CPSC 223b, Spring 2008                         *
 ***************************************************************************/
/*
 *  eval.c
 *
 *  Created by Michael Fischer on 4/10/2006
 *  fischer-michael@cs.yale.edu
 *  For use in Yale course CPSC 223b, Spring 2006
 *
 *  Derived from C++ code by 
 *  Alice E. Fischer  June 9, 2002
 */

#include <ctype.h>
#include <math.h>
#include <stdio.h>

#include "util.h"
#include "eval.h"
#include "operand.h"
#include "operator.h"
#include "stack.h"

struct eval {
  const char* instream;		/* input string buffer */
  Stack Ators;			/*Stack of operators. */
  Stack Ands;	     /* Stack of operands and intermediate results. */
  int numbin;		// number of binary operators on stack
};

// -------------------------------------------------- Construct new evaluator object
Eval newEval( const char* expr )
{
  Eval ev = safe_malloc( sizeof *ev );
  ev->instream = expr;
  ev->Ators = newStack();
  ev->Ands = newStack();
   ev->numbin = 0;
  return ev;
}

// ----------------------------------------------------------- Free evaluator object
void freeEval( Eval ev )
{
  while (!isemptyStack( ev->Ators )) {
    freeOperator( topStack( ev->Ators ) );
    popStack( ev->Ators );
  }
  freeStack( ev->Ators );

  while (!isemptyStack( ev->Ands )) {
    freeOperand( topStack( ev->Ands ) );
    popStack( ev->Ands );
  }
  freeStack( ev->Ands );

  free( ev );
}

// ---------------------------------------------------- Instructions for the operator.
void instructions( void )
{
  printf( "This is an infix expression evaluator.\n"
	  "* Operands start with a digit and may or may not have a decimal point.\n"
	  "* Operands must not exceed 31 keystrokes.\n"
	  "* All operators are binary operators.\n"
	  "* Operators are: +, -, *, /, %% (a mod b) and ^ (a to the power b).\n"
      "* Parentheses have their usual meaning.\n"
      "To quit, type semicolon instead of an expression.\n" );
}

// ----------------------------------------------------------------- Print the stacks.
void printEval( const_Eval ev )
{
  printf( "\tRemaining contents of operator stack: " );
  printAtors( ev->Ators );
  printf( "\tRemaining contents of operand stack: " );
  printAnds( ev->Ands );
}

// ------------------------------------------------------------ Print operands stack
void printAnds( const Stack Ands )
{
  Iter si = newIter( Ands );

  printf( "\nStack has %d items: bottom<[ ", sizeStack( Ands ) );
  while (hasNextIter( si )) {
    printOperand( nextIter( si ) );  
  }
  printf( "  ]>top\n" );

  freeIter( si );
}

// ----------------------------------------------------------- Print operators stack
void printAtors( const Stack Ators )
{
  Iter si = newIter( Ators );

  printf( "\nStack has %d items: bottom<[ ", sizeStack( Ators ) );
  while (hasNextIter( si )) {
    printOperator( (const Operator) nextIter( si ) );
  }
  printf( "  ]>top\n" );

  freeIter( si );

}

//------------------------------------------------ Read input and evaluate expression.
double evaluateEval(Eval ev) {
	Intype next; // Classification of next input character.
	char inSymbol; // Read input operators into this.
	Operator inOp; // Operator object constructed from inSymbol.
	double inNumVal; // Read input operands into this.
	Operand And; // Operand value
	int numread;
	int n;

	for (;;) {
		next = classifyEval(ev);
		switch (next) {
		case number:
			n = sscanf(ev->instream, "%lg%n", &inNumVal, &numread);
			ev->instream += numread;
			if (n!=1 || sizeStack(ev->Ands) != ev->numbin)
				return expErrorEval(ev);
			And = newOperand(inNumVal);
			pushStack(ev->Ands, And);
			break;

		case op:
			if (sizeStack(ev->Ands) != ev->numbin+1)
				return expErrorEval(ev);
			inSymbol = *(ev->instream++);
			inOp = newOperator(inSymbol);
			forceEval(ev, precedenceOperator(inOp) );
			pushStack(ev->Ators, inOp);
			ev->numbin++;
			break;

		case lpar:
			if (sizeStack(ev->Ands) != ev->numbin) return expErrorEval(ev);
			inSymbol = *(ev->instream++);
			inOp = newOperator(inSymbol); // put left paren on Ators stack
			pushStack(ev->Ators, inOp);
			break;
			
		case rpar:
			n = sscanf(ev->instream, " %c%n", &inSymbol, &numread);
			ev->instream += numread;
			if (sizeStack(ev->Ands) != ev->numbin+1)
				return expErrorEval(ev);
			forceEval(ev, 0);
			if (isemptyStack(ev->Ators))	expErrorEval(ev); // too many right parens
			Operator op = topStack(ev->Ators);         // remove left paren operator from Ators stack
			freeOperator(op);
			popStack(ev->Ators);
			break;

		case end:
			if (sizeStack(ev->Ands) != ev->numbin+1)
				return expErrorEval(ev);
			forceEval(ev, 0);
			if (!isemptyStack(ev->Ators)) return expErrorEval(ev);
			And = topStack(ev->Ands);
			popStack(ev->Ands);
			double retval = value(And);
			freeOperand(And);
			return retval;
			break;

		case bad:
		default:
			return expErrorEval(ev);
		}
	}
} 

//---------- Decide whether next input char is an operator, a semicolon, the beginning 
// of an operand, or garbage.
Intype classifyEval( const_Eval ev )
{
  char ch = *ev->instream;
  if ( ch == '\0' ) return end;
  if (isdigit( ch )) return number;
  switch(ch){
  case '+': 
  case '-': 
  case '*': 
  case '/': 
  case '%': 
  case '^': return op;
  case '(': return lpar;
  case ')': return rpar;
  default : return bad;
  }
}

// -------------------------------- Evaluate all higher precedence operators on stack.
void forceEval( Eval ev, int rprec ) {		
  while( sizeStack( ev->Ators ) > 0 && 
         precedenceOperator( (const Operator) topStack( ev->Ators ) ) >= rprec ) {
    dispatchEval( ev );
  }
}

// ------------------------------------------------------------ Evaluate one operator.
void dispatchEval( Eval ev ) {
  double result;
  Operand rightp = topStack( ev->Ands ); popStack( ev->Ands );
  Operand leftp  = topStack( ev->Ands ); popStack( ev->Ands );
  double right = value( rightp ); freeOperand( rightp );
  double left = value( leftp ); freeOperand( leftp );
  
  Operator op = topStack( ev->Ators); popStack( ev->Ators );  ev->numbin--;
  printf( "  Evaluating: %g%c%g\n", left, symbolOperator( op ), right );
  switch ( symbolOperator( op ) ) {
  case '+': result = left + right; 		break;
  case '-': result = left - right; 		break;
  case '*': result = left * right; 		break;
  case '/': result = left / right; 		break;
  case '%': result = fmod(left, right); 	break;
  case '^': result = pow (left, right); 	break;
  default: result = HUGE_VAL;	/* shouldn't occur */
  }
  freeOperator( op );
  Operand And = newOperand( result );
  pushStack( ev->Ands, And );
}
// ------------------------------------------------------------------- Error comments.
double expErrorEval( const_Eval ev )
{
  printf( "\tIllegal expression.\n" );
  printEval( ev );
  return HUGE_VAL;	
}
