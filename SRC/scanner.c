#include "cradle.h"
#include "scanner.h"

#define KWNUM 15
const char *KWlist[KWNUM] = {"IF", "ELSE", "WHILE", "LOOP", "REPEAT", "FOR", "DO", "BREAK",
                             "ENDIF", "ENDWHILE", "ENDLOOP", "UNTIL", "ENDFOR", "ENDDO", "END"};
const char KWcode[KWNUM + 1] = "xILWPRFDBEEEUEEE";

//Table Lookup
int Lookup(const char *T[], char* s, int n){
    int i = n;
    while(i-- && strcmp(s, T[i]));

    return i;
}

//Lexical Scanner
void Scan(){
    GetName();
    Token = KWcode[Lookup(KWlist, Value, KWNUM) + 1];
}
