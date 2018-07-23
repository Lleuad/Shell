#ifndef EXPR_H_
#define EXPR_H_

void Ident(void);      //Parse and Translate an Identifier
void Factor(void);     //Parse and Translate a Math Factor
void Multiply(void);   //Recognize and Translate a Multiply
void Divide(void);     //Recognize and Translate a Divide
void Term(void);       //Parse and Translate a Math Term
void Add(void);        //Recognize and Translate an Add
void Subtract(void);   //Recognize and Translate a Subtract
void Expression(void); //Parse and Translate an Expression
void Assignment(void); //Parse and Translate an Assignment Statement

#endif//EXPR_H_
