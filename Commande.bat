flex lexical.l
bison -d synt.y
gcc lex.yy.c synt.tab.c -lfl -ly -o compilISIL2020.exe
compilISIL2020.exe<expLangage.txt