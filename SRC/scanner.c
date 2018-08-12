#include "cradle.h"
#include "scanner.h"

struct KWcode KWlist[] = {
    {"IF",       'I'},
    {"ELSE",     'L'},
    {"WHILE",    'W'},
    {"LOOP",     'P'},
    {"REPEAT",   'R'},
    {"FOR",      'F'},
    {"DO",       'D'},
    {"BREAK",    'B'},
    {"ENDIF",    'E'},
    {"ENDWHILE", 'E'},
    {"ENDLOOP",  'E'},
    {"UNTIL",    'U'},
    {"ENDFOR",   'E'},
    {"ENDDO",    'E'},
    {"END",      'E'},
    {NULL,       'x'}
};

//Table Lookup
char Lookup(struct KWcode T[], char *s){
    int i = -1;
    while (T[++i].Value && strcmp(s, T[i].Value));

    return T[i].Token;
}

//Lexical Scanner
void Scan(){
    if (Token == 'x') Token = Lookup(KWlist, Value);
    DEBUG;
    DEBUGRET;
}
