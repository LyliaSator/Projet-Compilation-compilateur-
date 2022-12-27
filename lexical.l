%{
#include "synt.tab.h"
#include "Fonctions.h"
extern nb_ligne;
extern YYSTYPE yylval;


%}
lettres [a-zA-Z]
chiffres [+-]?[0-9]+
chiffre [0-9]+
nombre [+-]?[1-9][0-9]*
nombreVirg [+-]?[1-9][0-9]*.[0-9]+
constante ({chiffres}|{nombre})
constanteVirg ({constante}|{nombreVirg})
idf "$"{lettres}((({lettres}|{chiffre})*|_)(({lettres}|{chiffre})*))*
texte \"[^"]*\"
idf_tab "@"{lettres}(((({lettres}|{chiffre})*|_)({lettres}|{chiffre})*))*
expression {idf}|{nombre}|{nombreVirg}
commentaire "##"(([.]*|#)[^#])*"##"
%%
import return mc_import;
ISIL.io return bib_io;
ISIL.lang return bib_lang;
public return mc_public;
private return mc_private;
protected return mc_protected;
class return mc_class;
Entier {
       yylval.string=strdup(yytext);
       return mc_entier;
        }
Reel {
       yylval.string=strdup(yytext);
       return mc_reel;
        } 
Chaine {
       yylval.string=strdup(yytext);
       return mc_chaine;
        }
CONST return mc_constant;
For return mc_boucle ;
main return mc_main;
In return mc_lecture;
Out return mc_ecriture;

{idf} {
       if (yyleng <=25) {
              yylval.string=strdup(yytext);
              inserer(yytext,"idf");
              return idf;}
       else printf("idf trop long %s",yytext);}
{constante}  {
       if(-32768<=atoi(yytext) && atoi(yytext)<=32767){
       yylval.string=strdup(yytext);
       return cst ;}else{
              printf("valeur non acceptee a la ligne %d \n",nb_ligne);
       }}
{constanteVirg}  {
       yylval.string=strdup(yytext);
       return cstF;}

{idf_tab} {
       if (yyleng <=25) {
               yylval.string=strdup(yytext);
              inserer(yytext,"idf_tab");
              return idf_tab;}
       else printf("idf_tab trop long %s",yytext);}
{commentaire} {}
"[" return cr_ov;
"]" return cr_fr;
"{" return aco_ov;
"}" return aco_fr;
";" return pvg;
"," return vrg;
":=" return afc; 
"(" return par_ouv;
")" return par_fer;
"<" return inf; 
">" return sup;
"<=" return inf_egl;
">=" return sup_egl;
"=" return egl;
"!=" return diff;
"++" return increment;
"--" return decrement;
"+" return addition;
"-" return soustraction;
"*" return multip;
"/" return division;

[ \t]
\n nb_ligne++;
{texte} { yylval.string=strdup(yytext); return chaine_ecrire;} 
. {printf("erreur lexicale a la ligne %d sur l'enitite %s\n",nb_ligne,yytext);
       return erreur;}

