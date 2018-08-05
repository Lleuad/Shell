//p. 55
#include "cradle.h"
#include "expr.h"
#include "control.h"
#include "bool.h"
#include "scanner.h"

int main(int argc, char *argv[]){
    if (argc && !(freopen(argv[1], "r", stdin))) FileError(argv[1]);
    Init();
    DoProgram();
//  do {
//      Scan();
//      fprintf(stdout, "%s: %c\n", Value, Token);
//      if (Value[0] == CR) Fin();
//  } while ( Value[0] != '.' );
    return 0;
}

