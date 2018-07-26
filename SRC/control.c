#include "cradle.h"
#include "control.h"
#include "bool.h"
#include "expr.h"

//Recognize and Translate an "Other"
void Other(){
    Emit("%s\n", GetName());
}

//Recognize and Translate an IF Construct
//<IF-statement> ::= IF <condition> <block> ["ELSE" <block>] "ENDIF"
void DoIf(char *L){
    char* L1;
    char* L2;
    Match('I');
    BoolExpression();
    L1 = NewLabel();
    L2 = NULL;
    Emit("BEQ %s\n", L1);
    Block(L);
    if (Look == 'L') {
        Match('L');
        L2 = NewLabel();
        Emit("BRA %s\n", L2);
        PostLabel(L1);
        Block(L);
    }
    Match('E');
    PostLabel(L2 ? L2 : L1);
    free(L1);
    free(L2);
}

//Recognize and Translate a WHILE Construct
//<WHILE-statement> ::= "WHILE" <condition> <block> "ENDWHILE"
void DoWhile(){
    char *L1, *L2;
    Match('W');
    L1 = NewLabel();
    L2 = NewLabel();
    PostLabel(L1);
    BoolExpression();
    Emit("BEQ %s\n", L2);
    Block(L2);
    Match('E');
    Emit("BRA %s\n", L1);
    PostLabel(L2);
    free(L1);
    free(L2);
}

//Recognize and Translate a LOOP Construct
//<LOOP-statement> ::= "LOOP" <block> "ENDLOOP"
void DoLoop(){
    char *L1, *L2;
    Match('P');
    L1 = NewLabel();
    L2 = NewLabel();
    PostLabel(L1);
    Block(L2);
    Match('E');
    Emit("BRA %s\n", L1);
    PostLabel(L2);

    free(L1);
    free(L2);
}

//Recognize and Translate a REPEAT Construct
//<REPEAT-statement> ::= "REPEAT" <block> "UNTIL" <condition>
void DoRepeat(){
    char *L1, *L2;
    Match('R');
    L1 = NewLabel();
    L2 = NewLabel();
    PostLabel(L1);
    Block(L2);
    Match('U');
    BoolExpression();
    Emit("BEQ %s\n", L1);
    PostLabel(L2);

    free(L1);
    free(L2);
}

//Recognize and Translate a FOR Construct
//<FOR-statement> ::= "FOR" <name> "=" <expr1> <expr2> <block> "ENDFOR"
void DoFor(){
    char *L1, *L2, *Name;
    Match('F');
    L1 = NewLabel();
    L2 = NewLabel();
    Name = GetName();
    Match('=');
    Expression();
    Emit("SUBQ #1, D0\n");
    Emit("LEA %s(PC), A0\n", Name);
    Emit("MOVE D0, (A0)\n");
    Expression();
    Emit("MOVE D0, -(SP)\n");
    PostLabel(L1);
    Emit("LEA %s(PC), A0\n", Name);
    Emit("MOVE (A0), D0\n");
    Emit("ADDQ #1, D0\n");
    Emit("MOVE D0, (A0)\n");
    Emit("CMP (SP), D0\n");
    Emit("BGT %s\n", L2);
    Block(L2);
    Match('E');
    Emit("BRA %s\n", L1);
    PostLabel(L2);
    Emit("ADDQ #2, SP\n");

    free(L1);
    free(L2);
    free(Name);
}

//Recognize and Translate a DO Construct
//<DO-statement> ::= "DO" <expr> <block> "ENDDO"
void DoDo(){
    char *L1, *L2;
    Match('D');
    L1 = NewLabel();
    L2 = NewLabel();
    Expression();
    Emit("SUBQ #1, D0\n");
    PostLabel(L1);
    Emit("MOVE D0, -(SP)\n");
    Block(L2);
    Emit("MOVE (SP)+, D0\n");
    Emit("DBRA D0, %s\n", L1);
    Emit("SUBQ #2, SP\n");
    PostLabel(L2);
    Emit("ADDQ #2, SP\n");

    free(L1);
    free(L2);
}

//Recognize and Translate a BREAK Statement
//<BREAK-statement> ::= "BREAK"
void DoBreak(char *L){
    Match('B');
    if (L) Emit("BRA %s\n", L);
    else Abort("Can't break from global scope.\n");
}

//Recognize and Translate a Statement Block
//<block> ::= [ <statement> ]*
void Block(char *L){
    while ( !(Look == 'E' || Look == 'L' || Look == 'U') ){
        Fin();
        switch (Look) {
            case 'I':
                DoIf(L);
                break;
            case 'W':
                DoWhile();
                break;
            case 'P':
                DoLoop();
                break;
            case 'R':
                DoRepeat();
                break;
            case 'F':
                DoFor();
                break;
            case 'D':
                DoDo();
                break;
            case 'B':
                DoBreak(L);
                break;
            default:
                Assignment();
                break;
        }
        Fin();
    }
}

//Parse and Translate a Program
//<program> ::= <block> END
void DoProgram(){
    Block(NULL);
    if (Look != 'E') Expected("End");
    Emit("END\n");
}
