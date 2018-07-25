#ifndef BOOL_H_
#define BOOL_H_

void Relation(void);        //Parse and Translate a Relation
void Equals(void);          //Recognize and Translate a Relational "Equals"
void NotEquals(void);       //Recognize and Translate a Relational "Nat Equals"
void Less(void);            //Recognize and Translate a Relational "Less Than"
void Greater(void);         //Recognize and Translate a Relational "Greater Than"
void BoolFactor(void);      //Parse and Translate a Boolean Factor
void BoolTerm(void);        //Parse and Translate a Boolean Term
void BoolOr(void);          //Recognize and Translate a Boolean OR
void BoolXor(void);         //Recognize and Translate a Boolean XOR
void BoolExpression(void);  //Parse and Translate a Boolean Expression

#endif //BOOL_H_
