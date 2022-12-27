// 1-deffinir la structure de la table
typedef struct TypeTS TypeTS;
struct TypeTS{
       char NomEntite[20];
       char CodeEntite[20];
       char TypeEntite[20];
       char isconstante[3];
       int valeurInt;
       float valeurFloat;
       char valeurChar[20];
};

//La decalaration de la structure d'une case
typedef struct CaseListe CaseListe;
 struct CaseListe {
       struct CaseListe *svt;
       struct CaseListe *prec;
       TypeTS entite;
};

//2- declarer la table
CaseListe *tete=NULL;
CaseListe *queue=NULL;

//3- initialiser le compteur de la table
int CpTabSym=0;

//4-doubledec
int dec= 0;

//valeur
char val[20];
char valeurReturn[20];
//declaration de la liste des idf 
typedef struct listIdf listIdf;
 struct listIdf {
       struct listIdf *svt;
       struct listIdf *prec;
       char idf[20];
};
listIdf *teteIdf=NULL;
listIdf *queueIdf=NULL;
int pos =0;

//declaration de la liste des idf 
typedef struct listAffect listAffect;
 struct listAffect {
       struct listAffect *svt;
       struct listAffect *prec;
       char idf[20];
};
listAffect *queueAffec=NULL;
listAffect *teteAffec=NULL;


//4- Programmer la fonction recherche dans la table 
int recherche (char entite[]){
       CaseListe *courant; CaseListe *suivant;
       
       if (tete!=NULL)
       {
       courant=tete;
       suivant=courant->svt;
       int i=0;
       if (strcmp(entite, tete->entite.NomEntite)==0)
       {
         return i;
       }
       while (suivant!=NULL)
       {
              if (strcmp(entite, courant->entite.NomEntite)==0)
              {
                     //l'entite se trouve a la position
                    return i;
              }
              courant=suivant;
              suivant=courant->svt;
              i++;
       }
       queue=courant;
           
       if (strcmp(entite, queue->entite.NomEntite)==0)
       {
              
              return i;
       }
       return -1;
       }
         return -1;
      
}

TypeTS *rechercheEssai (char entite[]){
       CaseListe *courant; CaseListe *suivant;
       
       if (tete!=NULL)
       {
       courant=tete;
       suivant=courant->svt;
       int i=0;
       if (strcmp(entite, tete->entite.NomEntite)==0)
       {
         return &tete->entite;
       }
       while (suivant!=NULL)
       {
              if (strcmp(entite, courant->entite.NomEntite)==0)
              {
                    return &courant->entite;
              }
              courant=suivant;
              suivant=courant->svt;
              i++;
       }
       queue=courant;
           
       if (strcmp(entite, queue->entite.NomEntite)==0)
       {
              
              return &queue->entite;
       }
       return NULL;
       }
         return NULL;
      
}


//5- programmer la fonction inserer

void inserer(char enitite[], char code[]){
      CaseListe *courant; CaseListe *suivant;
      CaseListe *caseAjout=(CaseListe*) malloc(sizeof(CaseListe));
      if (tete!=NULL)
       {
       courant=tete;
       suivant=courant->svt;
       
       if(rechercheEssai(enitite)==NULL){
              
              strcpy(caseAjout->entite.NomEntite,enitite);
              strcpy(caseAjout->entite.CodeEntite,code);
              strcpy(caseAjout->entite.isconstante,"Non");
              strcpy(caseAjout->entite.valeurChar,"");
              
              caseAjout->prec=queue;
              caseAjout->svt=NULL;
              queue->svt=caseAjout;
              CpTabSym++;
       }else {dec=1;}
       }else{//Traitement du premier element
          tete=caseAjout;
          strcpy(tete->entite.NomEntite,enitite);
          strcpy(tete->entite.CodeEntite,code);
          strcpy(tete->entite.TypeEntite,"class");
          strcpy(caseAjout->entite.isconstante,"Non");
       
          tete->svt=NULL;
          tete->prec=NULL;
       }
       
}

//6- la fct afficher 
void afficher(){
       printf("\n\n***************Table de symbole***************\n");
       CaseListe *courant; CaseListe *suivant;
       if (tete!=NULL)
       {
       courant=tete;
       suivant=courant->svt;
       printf("_______________________________________________________________________________\n");
       printf("\t|NomEntite  |  CodeEntite | TypeEntite  | Constante | Valeur\n");
       printf("_______________________________________________________________________________\n");
       while (suivant!=NULL)
       {
              if(strcmp(courant->entite.TypeEntite,"class")==-1)
                printf("\t|%10s |%12s |%12s |%10s |%10s\n",courant->entite.NomEntite,courant->entite.CodeEntite,courant->entite.TypeEntite,courant->entite.isconstante,courant->entite.valeurChar);
              
              courant=suivant;
              suivant=courant->svt;
       }
             
              
                printf("\t|%10s |%12s |%12s |%10s |%10s\n",courant->entite.NomEntite,courant->entite.CodeEntite,courant->entite.TypeEntite,courant->entite.isconstante,courant->entite.valeurChar);
              
       }else{
         printf("La partie declaration est vide !\n");
       }
       
}

//7- inserer le type 
void insererType(char entite[],char type[]){
    TypeTS *entiteExiste = rechercheEssai(entite);
    if (entiteExiste!=NULL)
    {
           strcpy(entiteExiste->TypeEntite,type);
    }
    
}

//8- déclaration de la variable ?
int DoubleDeclaration(char entite[]){
      int position,encours;
      if (dec==0){
    position=recherche(entite);

    CaseListe *courant; CaseListe *suivant;
    if (tete!=NULL)
     {
        courant=tete;
        suivant=courant->svt;
        encours=0; 
        while (encours!=position)
         {
            courant=suivant;
            suivant=courant->svt;
            encours++;
         }
          
        return 0;

      }
    }else { 
        dec=0;
           return -1;}
    
}

int isDeclared(char entite[]){
             if(recherche(entite)!=-1){
                    return 0;
             }
             else return -1;
}


int typeEnregistrer(char entite[]){
       TypeTS *entiteRchercher = rechercheEssai(entite);
       if (entiteRchercher!=NULL)
       {
              if (strcmp(entiteRchercher->TypeEntite,"")==0)
              {
                     return -1;
              }
              else return 0;
              
       }
       
}
    
//9-Constante 
void isConstante(char entite[]){   
    TypeTS *entiteRchercher = rechercheEssai(entite);
    if (entiteRchercher!=NULL)
    {
        strcpy(entiteRchercher->isconstante,"Oui");   
    }
    
}

//10-Insere la valeur des variables apres l'affectation
insererValeur (char entite[],char valeur[]){
    int position,encours;
    position=recherche(entite); char *endPtr;
    CaseListe *courant; CaseListe *suivant;
    courant=tete;
    suivant=courant->svt;
    encours=0;      
    if(position !=-1){
       while (encours!=position)
       {
           courant=suivant;
           suivant=courant->svt;
           encours++;
       }
    }
              strcpy(courant->entite.valeurChar,valeur);   
}

//11-tester le signe de formatage
int testeSignFormatage(char sign, char type[20]){
       if (strcmp(type,"Entier")==0){
             if(sign=='d'){
                    return 0;
             }else {return -1 ;}
       }
       if (strcmp(type,"Reel")==0){
             if(sign=='f'){
                    return 0;
             }else {return -1 ;}
       }
       if (strcmp(type,"Chaine")==0){
             if(sign=='s'){
                    return 0;
             }else{ return -1 ;}
       }
}

//12-Traitement de la chaine à lire ==> In
int traitementLire(char chaineEcrire[],char idf[]){
    char type[20];
    TypeTS*entiteRchercher=rechercheEssai(idf);
    if(entiteRchercher !=NULL){
       strcpy(type,entiteRchercher->TypeEntite);     
             if (strlen(chaineEcrire)<=4)
             {
                  return  testeSignFormatage(chaineEcrire[2],type);
              }    else {return -1;}
       } else {return -1;}
}

//13-Traitement de la chaine à ecrire ==> Out
int traitementEcrire(char chaineEcrire[]){
  char type[20]; int i=0,j,k,compteur=0, retour=0, taille=strlen(chaineEcrire), isSign=1; char idf[20];
  TypeTS*entiteRchercher;
   listIdf *courant, *preced; 
   courant=NULL; preced=NULL;
   if (queueIdf!=NULL){
       courant=queueIdf;  
       preced=queueIdf->prec;
   }else{
          if (teteIdf!=NULL)
          {
              courant=teteIdf;
          }
         else{
                courant=NULL;
         } 
   }   
   if (courant==NULL)
   { 
       while (i<taille && retour ==0)
       {      
              if (chaineEcrire[i]=='%'){
               if (chaineEcrire[i+1]=='d' | chaineEcrire[i+1]=='s' | chaineEcrire[i+1]=='f'){
                 if (chaineEcrire[i+2]=='"' | chaineEcrire[i+2]==' '){
                   //il y a un caractere à afficher
                       retour=-1;
                   }      
                 }
              }
           i++;
       }
       return retour;
   }else{
       while (retour==0 && courant!=NULL && i<taille){
            if (chaineEcrire[i]=='%'){
               if (chaineEcrire[i+1]=='d' | chaineEcrire[i+1]=='s' | chaineEcrire[i+1]=='f'){
                 if (chaineEcrire[i+2]=='"' | chaineEcrire[i+2]==' '){
                   //il y a un caractere à afficher
                       isSign=0;
                       strcpy(idf,courant->idf);
                       entiteRchercher=rechercheEssai(idf);
                      if(entiteRchercher !=NULL){
                         strcpy(type,entiteRchercher->TypeEntite); 
                          retour=  testeSignFormatage(chaineEcrire[i+1],type);
                       }
                     courant=preced;
                     if (courant!=NULL)
                     {
                         preced=courant->prec;
                     }else{
                     }
                   }      
                 }
              }
           i++;
       }  
       if (i==taille)
       {
        if (courant==NULL && isSign==1)
        {
               return -1;
        }  
       }
    if (retour==0 && isSign==0){
        return 0; teteIdf=NULL; queueIdf=NULL;
    }else { return -1;}
   }
}

//14- rechercher lid dans la liste des idfs
listIdf *rechercheIdf (char idf[]){
       listIdf *courant; listIdf *suivant;
       
       if (teteIdf!=NULL)
       {
       courant=teteIdf;
       suivant=courant->svt;
       int i=0;
       if (strcmp(idf, teteIdf->idf)==0)
       {
         return teteIdf;
       }
       while (suivant!=NULL)
       {
              if (strcmp(idf,teteIdf->idf)==0)
              {
                    return courant;
              }
              courant=suivant;
              suivant=courant->svt;
              i++;
       }
       queueIdf=courant;
           
       if (strcmp(idf, queueIdf->idf)==0)
       {
              return queueIdf;
       }
       return NULL;
       }
         return NULL;
      
}

//15-Ajouter un element à liste idf 

void ajouterElement(char idf[]){
      listIdf *courant; listIdf *suivant;
      listIdf *caseAjout=(listIdf*) malloc(sizeof(listIdf));
      if (teteIdf!=NULL)
       {
       courant=teteIdf;
       suivant=courant->svt;
       
       if(rechercheIdf(idf)==NULL){
              strcpy(caseAjout->idf,idf);
              caseAjout->prec=queueIdf;
              caseAjout->svt=NULL;
              queueIdf->svt=caseAjout;
              queueIdf=caseAjout;
              CpTabSym++;
       }else {dec=1;}
       }else{//Traitement du premier element
          teteIdf=caseAjout;
          strcpy(teteIdf->idf,idf);
          teteIdf->svt=NULL;
          teteIdf->prec=NULL;
       }
}



//16- verifier si le type principale correspond au type donné
int verifierType(char typeEnre[], char type []){
       if(strcmp(typeEnre,type)==0){
              return 0;
       }
       return -1;

}


//17-Si l'idf est une constante
int idfEstCst(char entite[]){
       TypeTS *entiteRchercher = rechercheEssai(entite);
    if (entiteRchercher!=NULL)
    {
           if(strcmp(entiteRchercher->isconstante,"Oui")==0){
              return 0;
           }
           else return 1;
           
}}

//18-Si la taille du tableau est plus grande que l'index
int indexOutBound(char idf_tab[], char index[]){
  TypeTS*entiteRchercher=rechercheEssai(idf_tab);
  if (entiteRchercher!=NULL)
  {
    if ((atoi(entiteRchercher->valeurChar))>atoi(index) && atoi(index)>=0)
    {
           return 0;
    }else return -1;
    
  }   
}

//19-Si la constante est declarer
int constanteDec(char constante[]){
  TypeTS*entiteRchercher=rechercheEssai(constante);
  if (entiteRchercher!=NULL)
  {
    if (strcmp(entiteRchercher->valeurChar,"")==0 && strcmp(entiteRchercher->isconstante,"Oui"))
    {
           return 0;
    }else { return -1;}
    
  } 
}

//20-Compatibilité des types
int CompatibiliteType(char idf[], int nbLigne){
       TypeTS* entiteIdfRchercher=rechercheEssai(idf);
       TypeTS* entiteAffecCourant=NULL;
       listAffect *courant; listAffect *suivant;
       int i;
       if (entiteIdfRchercher!=NULL && teteAffec!=NULL){
           courant=teteAffec;
           suivant=courant->svt;
           while (courant!=NULL)
           {
              entiteAffecCourant= rechercheEssai(courant->idf);
              if (entiteAffecCourant!=NULL){
                if (verifierType(entiteIdfRchercher->TypeEntite,entiteAffecCourant->TypeEntite)!=0){
                  printf("erreur semantique : le type de %s n'est pas le meme avec %s a la ligne %d\n",idf,entiteAffecCourant->NomEntite,nbLigne);
                     return 1;
              }
              courant=suivant;
              if (courant!=NULL){ suivant=courant->svt;}
              }else{
                 if (courant->idf[0]=='"'){
                     if (verifierType(entiteIdfRchercher->TypeEntite,"Chaine")!=0){
                      printf("erreur semantique : le type de %s n'est pas le meme avec %s a la ligne %d\n",idf,courant->idf,nbLigne);
                            return 1;
                     }
                 }
                 else{
                    for ( i = 0; i < strlen(courant->idf); i++)
                    {
                       if (courant->idf[i]=='.'){
                          if (verifierType(entiteIdfRchercher->TypeEntite,"Reel")!=0){
                            printf("erreur semantique : le type de %s n'est pas le meme avec %s a la ligne %d\n",idf,courant->idf,nbLigne);
                            return 1;
                            break;
                          }
                       }
                       
                    }
                    
                 }                  
                  courant=suivant;
                  if (courant!=NULL){ suivant=courant->svt;}
              }
           }           
       }
       teteAffec=NULL; queueAffec=NULL;
       return 0;
}

//14- rechercher lid dans la liste des idfAffec
listAffect *rechercheIdfAffec (char idf[]){
       listAffect *courant; listAffect *suivant;
       if (teteAffec!=NULL)
       {
       courant=teteAffec;
       suivant=courant->svt;
       int i=0;
       if (strcmp(idf, teteAffec->idf)==0)
       {
         return teteAffec;
       }
       while (suivant!=NULL)
       {
              if (strcmp(idf,teteAffec->idf)==0)
              {
                    return courant;
              }
              courant=suivant;
              suivant=courant->svt;
              i++;
       }
       queueAffec=courant;
           
       if (strcmp(idf, queueAffec->idf)==0)
       {
              return queueAffec;
       }
       return NULL;
       }
         return NULL;
      
}

void ajouterElementAffec(char idf[]){
      listAffect *courant; listAffect *suivant;
      listAffect *caseAjout=(listAffect*) malloc(sizeof(listAffect));
      if (teteAffec!=NULL)
       {
       courant=teteAffec;
       suivant=courant->svt;
       
       if(rechercheIdfAffec(idf)==NULL){
              strcpy(caseAjout->idf,idf);
              caseAjout->prec=queueAffec;
              caseAjout->svt=NULL;
              queueAffec->svt=caseAjout;
              queueAffec=caseAjout;
       }else {dec=1;}
       }else{//Traitement du premier element
          teteAffec=caseAjout;
          strcpy(teteAffec->idf,idf);
          teteAffec->svt=NULL;
          teteAffec->prec=NULL;
       }
}


