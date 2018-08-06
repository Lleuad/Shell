#ifndef SCANNER_H_
#define SCANNER_H_

struct KWcode {
    const char *Value;
    const char Token;
};

//int Lookup(const char **, char *, int); //Table Lookup
char Lookup(struct KWcode *, char *); //Table Lookup
void Scan(void); //Lexical Scanner

#endif //SCANNER_H_
