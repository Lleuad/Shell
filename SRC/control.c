#include "cradle.h"
#include "control.h"

//Recognize and Translate an "Other"
void Other(){
    Emit("%s\n", GetName());
}

//Recognize and Translate a Statement Block
//<block> ::= [ <statement> ]*
void Block(){
    while (Look != 'e') Other();
}

//Parse and Translate a Program
//<program> ::= <block> END
void DoProgram(){
    Block();
    if (Look != 'e') Expected("End");
    Emit("END\n");
}
