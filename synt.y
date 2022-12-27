%{
int nb_ligne= 1;
char TypeEnregistrer[20];
char valeur[20]="";
char idfType[20]="";
char type[10]="";
char constante[20]="";
int bibArithm=0;
int bibInOut=0;
int bibArithmeDetecte=0;
int bibIODetecte=0;
int isOperateur=0;
int priorite = 0;
%}

%union{
int entier;
char* string;
float reel;
}


%token     

mc_import bib_io bib_lang
mc_public mc_private mc_protected
erreur <string>cst <string>cstF <string>chaine_ecrire 
mc_class mc_main mc_lecture mc_ecriture mc_boucle
<string>mc_entier  <string>mc_reel <string>mc_chaine mc_constant
aco_ov aco_fr cr_ov cr_fr par_ouv par_fer pvg vrg
<string>idf_tab <string>idf
increment decrement
inf sup inf_egl sup_egl diff egl afc addition soustraction multip division 

%start S

%%

S: LISTE_BIB HEADER_CLASS aco_ov CORPS aco_fr{printf("programme syntaxiquement correct");
                    YYACCEPT;}
;

LISTE_BIB: BIB LISTE_BIB 
            |
;

BIB: mc_import NOM_BIB pvg
;

NOM_BIB:bib_io  { bibInOut=1;};
    | bib_lang  {bibArithm=1;};
;

HEADER_CLASS: MODIFICATEUR mc_class idf 
;

MODIFICATEUR: mc_public
              |mc_private
              |mc_protected
;

CORPS: LISTE_DEC LISTE_OPERATION 
;

LISTE_OPERATION: mc_main par_ouv par_fer aco_ov OPERATIONS aco_fr
                |
;

LISTE_DEC: DEC LISTE_DEC
            |
;

DEC: DEC_VAR
       |DEC_TAB
       |DEC_CONST
;

DEC_VAR: TYPE LISTE_IDF pvg
;

TYPE: mc_entier {strcpy(TypeEnregistrer,$1);}
     | mc_reel {strcpy(TypeEnregistrer,$1);}
     | mc_chaine {strcpy(TypeEnregistrer,$1);}
;

LISTE_IDF: idf vrg LISTE_IDF  {if(DoubleDeclaration($1)==0){insererType($1,TypeEnregistrer);}
                              else{
                               printf("erreur semantique : double declaration de %s a la ligne %d\n",$1,nb_ligne);
                              }
                               }
          |idf {if(DoubleDeclaration($1)==0){insererType($1,TypeEnregistrer);}
                              else{
                               printf("erreur semantique : double declaration de %s a la ligne %d\n",$1,nb_ligne);
                              }
                               }
;

CONSTANTE: cst  {if(isOperateur==0){strcpy(valeur,$1);
                strcpy(type,"Entier");ajouterElementAffec($1);}
                else {ajouterElementAffec($1);}
                }
          |cstF { if(isOperateur==0){strcpy(valeur,$1);
                 strcpy(type,"Reel");ajouterElementAffec($1);}
                 else {ajouterElementAffec($1);}
                 }
          |chaine_ecrire {if(isOperateur==0){strcpy(valeur,$1);
                strcpy(type,"Chaine");ajouterElementAffec($1);}
                else{ ajouterElementAffec($1);}
                }
;

DEC_CONST: mc_constant TYPE idf afc CONSTANTE pvg  {if(DoubleDeclaration($3)==0){insererType($3,TypeEnregistrer); isConstante($3);
                                  if(verifierType(TypeEnregistrer,type)==0){
                                    insererValeur($3, valeur);
                                    CompatibiliteType($1,nb_ligne);
                                     strcpy(valeur," ");}
                                    else {
                                        printf("type incoherent de la constante %s a la ligne %d \n",$3,nb_ligne);
                                    }}
                              else{
                               printf("erreur semantique : double declaration de %s a la ligne %d\n",$3,nb_ligne);
                              }}
          | mc_constant TYPE idf pvg {if(DoubleDeclaration($3)==0){insererType($3,TypeEnregistrer); isConstante($3);}
                              else{
                               printf("erreur semantique : double declaration de %s a la ligne %d\n",$3,nb_ligne);
                              }}
;

DEC_TAB: TYPE LISTE_IDF_TAB pvg
;

LISTE_IDF_TAB: idf_tab cr_ov cst cr_fr vrg LISTE_IDF_TAB {if(DoubleDeclaration($1)==0){
                                           insererType($1,TypeEnregistrer); }
                              else{
                               printf("erreur semantique : double declaration de %s a la ligne %d\n",$1,nb_ligne);
                              }
                              if(atoi($3)<0){
                                  printf("erreur semantique : la taille de tableau %s est negative a la ligne %d\n",$1,nb_ligne);
                              }else{insererValeur($1,$3);}
                               }
              |idf_tab cr_ov cst cr_fr {if(DoubleDeclaration($1)==0){insererType($1,TypeEnregistrer);}
                              else{
                               printf("erreur semantique : double declaration de %s a la ligne %d\n",$1,nb_ligne);
                              }
                              if(atoi($3)<0){
                                  printf("erreur semantique : la taille de tableau %s est negative a la ligne %d\n",$1,nb_ligne);
                              }else{insererValeur($1,$3);}
                               }
;

OPERATIONS: INST  OPERATIONS
          |
;

INST: INST_BOUCLE
        |INST_AFF   {if((bibArithm==0)&&(bibArithmeDetecte==0)) 
			                    {printf("manque de bibliotheque arithmetique \n");
			                     bibArithmeDetecte=1;}}
        |INST_InOut {if((bibInOut==0)&&(bibIODetecte==0)) {
						          printf("manque de bibliotheque d'entree sortie \n");
					              bibIODetecte=1;}}
        
;

INST_AFF: idf afc EXP pvg { if(typeEnregistrer($1)==-1){printf("erreur semantique dans la ligne %d la variable %s est non declare\n",nb_ligne,$1);}
                            if(idfEstCst($1)==0 && constanteDec($1)==-1){
                                printf("erreur semantique: la constante %s est deja initialisee\n",$1);
                            }
                            else{
                                if(isOperateur==0){
                                    if(CompatibiliteType($1,nb_ligne)!=1){
                                  insererValeur($1, valeur);
                                  strcpy(valeur," ");
                                  isOperateur=0;}                                 
                                }else{
                                   CompatibiliteType($1,nb_ligne);
                                   isOperateur=0; 
                                }
                            }
                    }
          |idf_tab cr_ov cst cr_fr afc EXP pvg {
              if(typeEnregistrer($1)==-1){printf("erreur semantique dans la ligne %d le tableau %s est non declare\n",nb_ligne,$1);}
              else{if(indexOutBound($1,$3)==-1){printf("erreur semantique dans la ligne %d IndexOutOfBounds pour le tableau %s\n",nb_ligne,$1);}}}
; 

INST_BOUCLE: mc_boucle par_ouv INST_AFF CONDITION ins_INC par_fer aco_ov OPERATIONS aco_fr 
;

INST_InOut : INST_LECTURE      
            |INST_ECRITURE     
; 

INST_LECTURE : mc_lecture par_ouv chaine_ecrire vrg idf par_fer pvg {if(traitementLire($3,$5)==-1){printf("erreur semantique dans la ligne %d la variable %s est mal lu\n",nb_ligne,$5);}}
;

INST_ECRITURE : mc_ecriture par_ouv chaine_ecrire  vrg LISTE_IDF_ECRITURE par_fer pvg { 
             if(traitementEcrire($3)==-1){printf("erreur semantique dans la ligne %d la variable est mal ecrite\n",nb_ligne);}}
             | mc_ecriture par_ouv chaine_ecrire par_fer pvg  { 
             if(traitementEcrire($3)==-1){printf("erreur semantique dans la ligne %d la variable est mal ecrite\n",nb_ligne);}}
;

LISTE_IDF_ECRITURE : idf vrg LISTE_IDF_ECRITURE  {if(typeEnregistrer($1)==-1){printf("erreur semantique dans la ligne %d la variable %s est non declare\n",nb_ligne,$1);}
                                                   else{ajouterElement($1);}}
                   | idf  {if(typeEnregistrer($1)==-1){printf("erreur semantique dans la ligne %d la variable %s est non declare\n",nb_ligne,$1);}
                                                   else{ajouterElement($1);}}
;

IDF_CST: idf {if(typeEnregistrer($1)==-1){printf("erreur semantique dans la ligne %d la variable %s est non declare\n",nb_ligne,$1);}
               else{//on teste la compatibilite des types
                 ajouterElementAffec($1);
               }}
        |idf_tab cr_ov cst cr_fr  {if(indexOutBound($1,$3)==-1){printf("erreur semantique a la ligne %d: index supperieur a la taille du tableau %s \n",nb_ligne,$1); }
        else{
         ajouterElementAffec($1);
        }}
        |CONSTANTE
;  

EXP : IDF_CST Operateur EXP
      |IDF_CST
;

Operateur : division {isOperateur=1;
                        priorite=2;}
           | multip {isOperateur=1;
                    priorite=2;}
           |addition {isOperateur=1;
                        priorite=1;}
           |soustraction {isOperateur=1;
                            priorite=2;}
;


CONDITION: idf COMPARATEUR EXP pvg {if(DoubleDeclaration($1)==0){printf("erreur semantique dans la ligne %d la variable %s est non declare\n",nb_ligne,$1);}}
;

COMPARATEUR : inf
           | inf_egl
           | sup
           | sup_egl
           | egl
           |diff
;


ins_INC : DECREMENTATION
        | INCREMENTATION
;

DECREMENTATION: idf decrement
;

INCREMENTATION: idf increment
;


%%
main()
{yyparse();
afficher();
}
yywrap()
{}

int yyerror(char*message){
    printf("Syntaxe erreur a la ligne : %d",nb_ligne);
}
