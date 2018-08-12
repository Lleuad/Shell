#include "cradle.h"
#include "expr.h"
#include "bool.h"

//Parse and Translate an Identifier
//<ident> ::= <function> "()" | <variable>
void Ident(){
    GetName();
    if (Look == '('){
        Match('(');
        Match(')');
        FuncCall(Value);
    }else{
        LoadVar(Value);
    }
}

//Parse and Translate a Math Factor
//<factor> ::= [<addop>] <unsigned-factor>
//<unsigned-factor> :: = "(" <expression> ")" | <ident> | <number>
void Factor(){
    int neg = 0;

    switch (Look){
        case '+':
            Match('+');
            break;
        case '-':
            Match('-');
            neg = 1;
            break;
    }

    if (Look == '('){
        Match('(');
        Expression();
        Match(')');
    }else if ( IsAlpha(Look) ){
        Ident();
    }else{
        GetNum();
        LoadConst(Value);
    }
    if (neg) Negate();
}

//Recognize and Translate a Multiply
void Multiply(){
    Match('*');
    Factor();
    PopMul();
}

//Recognize and Translate a Divide
void Divide(){
    Match('/');
    Factor();
    PopDiv();
}

//Parse and Translate a Math Term
//<term> ::= <factor> [ <mulop> <factor> ]*
//<mulop> ::= "*" | "/"
void Term(){
    Factor();

    while ( IsMulop(Look) ){
        Push();
        switch (Look){
            case '*':
                Multiply();
                break;
            case '/':
                Divide();
                break;
        }
    }
}

//Recognize and Translate an Add
void Add(){
    Match('+');
    Term();
    PopAdd();
}

//Recognize and Translate a Subtract
void Subtract(){
    Match('-');
    Term();
    PopSub();
}

//Parse and Translate an Expression
//<expression> ::= <term> [ <addop> <term> ]*
//<addop> ::= "+" | "-"
void Expression(){
    Term();

    while ( IsAddop(Look) ){
        Push();
        switch (Look){
            case '+':
                Add();
                break;
            case '-':
                Subtract();
                break;
        }
    }
}

//Parse and Translate an Assignment Statement
//<assignment> ::= <ident> "=" <expression>
void Assignment(){
    char *Name;
    if (!(Name = malloc(ValueSize * sizeof (char)))) MemError();
    strcpy(Name, Value);

    Match('=');
    BoolExpression();
    Store(Name);
    free(Name);
}
