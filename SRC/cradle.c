#include "cradle.h"

//Report Error and Halt
void Abort(const char* s){
    Error(s);
    exit(1);
}

//Report What Was Expected
void Expected_s(const char* s){
    fprintf(stderr, "Error: Got '%c', Expected %s.\n", Look, s);
    exit(1);
}

void Expected_c(char c){
    fprintf(stderr, "Error: Got '%c', '%c' Expected.\n", Look, c);
    exit(1);
}

//Match a Specific Input Character
void Match(char x){
    if(Look == x){
        GetChar();
        SkipWhite();
    }else{
        Expected(x);
    }
}

//Get an Identifier
char* GetName(){
    char* Token = calloc(TOKENSIZE, sizeof(char));
    if ( !IsAlpha(Look) ) Expected("Name");
    for (int i = 0; i < TOKENSIZE && IsAlNum(Look); i++, GetChar()){
        Token[i] = (char)toupper(Look);
    }
    SkipWhite();

    return Token;
}

//Get a Number
char* GetNum(){
    char* Token = calloc(TOKENSIZE, sizeof(char));
    if ( !IsDigit(Look) ) Expected("Integer");
    for (int i = 0; i < TOKENSIZE && IsDigit(Look); i++, GetChar()){
        Token[i] = Look;
    }
    SkipWhite();

    return Token;
}

//Get a Boolean Literal
int GetBoolean(){
    int bool;
    if (!IsBoolean(Look)) Expected("Boolean Literal");
    bool = (toupper(Look) == 'T');
    GetChar();
    SkipWhite();
    return bool;
}

//Generate a Unique Label
char* NewLabel(){
    char* Label = malloc(2 + 2*sizeof Lcount);
    sprintf(Label, "L%X", Lcount++);
    if (!Lcount) Abort("Lcount overflow");
    return Label;
}

//Output a String with Tab
void Emit(const char* fmt, ...){
    va_list vlist;
    va_start(vlist, fmt);

    fprintf(stdout, "%c", TAB);
    vfprintf(stdout, fmt, vlist);

    va_end(vlist);
}

//Initialize
void Init(){
    Lcount = 0;
    GetChar();
    SkipWhite();
}

