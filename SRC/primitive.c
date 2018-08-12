#include "primitive.h"
#include "cradle.h"

//Expression
void Clear(){
    Emit(";CLEAR\n");
    Emit("CLR D0\n");
}

void Negate(){
    Emit(";NEGATE\n");
    Emit("NEG D0\n");
}

void LoadConst(char* Num){
    Emit(";LOADCONST %s\n", Num);
    Emit("MOVE #%s, D0\n", Num);
}

void LoadVar(char *Name){
    if (!InTable(Name)) Undefined(Name);
    Emit(";LOADVAR %s\n", Name);
    Emit("MOVE %s(PC), D0\n", Name);
}

void Push(){
    Emit(";PUSH\n");
    Emit("MOVE D0, -(SP)\n");
}

void PopAdd(){
    Emit(";POPADD\n");
    Emit("ADD (SP)+, D0\n");
}

void PopSub(){
    Emit(";POPSUB\n");
    Emit("SUB (SP)+, D0\n");
    Emit("NEG D0\n");
}

void PopMul(){
    Emit(";POPMUL\n");
    Emit("MULS (SP)+, D0\n");
}

void PopDiv(){
    Emit(";POPDIV\n");
    Emit("MOVE (SP)+, D7\n");
    Emit("EXT.L D7\n");
    Emit("DIVS D0, D7\n");
    Emit("MOVE D7, D0\n");
}

void Store(char *Name){
    if (!InTable(Name)) Undefined(Name);
    Emit(";STORE %s\n", Name);
    Emit("LEA %s(PC), A0\n", Name);
    Emit("MOVE D0, (A0)\n");
}

void FuncCall(char *Name){
    Emit(";CALL %s\n", Name);
    Emit("BSR %s\n", Name);
}

//Boolean
void NotIt(){
    Emit(";NOT\n");
    Emit("NOT D0\n");
}

void PopAnd(){
    Emit(";POPAND\n");
    Emit("AND (SP)+,D0\n");
}

void PopOr(){
    Emit(";POPOR\n");
    Emit("OR (SP)+,D0\n");
}

void PopXor(){
    Emit(";POPXOR\n");
    Emit("EOR (SP)+,D0\n");
}

void PopCompare(){
    Emit(";POPCMP\n");
    Emit("CMP (SP)+, D0\n");
}

void SetEqual(){
    Emit(";SETEQ\n");
    Emit("SEQ D0\n");
    Emit("EXT D0\n");
}

void SetNEqual(){
    Emit(";SETNE\n");
    Emit("SNE D0\n");
    Emit("EXT D0\n");
}

void SetGreater(){
    Emit(";SETGT\n");
    Emit("SLT D0\n");
    Emit("EXT D0\n");
}

void SetGreaterOrEqual(){
    Emit(";SETGE\n");
    Emit("SLE D0\n");
    Emit("EXT D0\n");
}

void SetLess(){
    Emit(";SETLT\n");
    Emit("SGT D0\n");
    Emit("EXT D0\n");
}

void SetLessOrEqual(){
    Emit(";SETLE\n");
    Emit("SGE D0\n");
    Emit("EXT D0\n");
}

//Control
void SetTrue(){
    Emit(";SETT\n");
    Emit("MOVE #-1, D0\n");
}

void SetFalse(){
    Emit(";SETF\n");
    Emit("CLR D0\n");
}

void Branch(char *L){
    Emit(";JMP %s\n", L);
    Emit("BRA %s\n", L);
}

void BranchFalse(char *L){
    Emit(";JEQ %s\n", L);
    Emit("TST D0\n");
    Emit("BEQ %s\n", L);
}


