#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include "tm.h"
// Function prototypes
struct tm* TimeActuel();
int estBissextile(int annee);
int checkMois(int mois);


char afficher_reservation_salles();
char afficher_reservation_club();
char profReservation();
char reponse(int x, int y);
void pageProf();
void pageAdmin();
void menuIdentifiant();
typedef struct user {
    char nomUser[20];
    char prenomUser[20];
    char Email[20];
    char password[20];
    char tele[11];
} user;

typedef struct salle {
    char blocSalle;
    char typeSalles[20];
    int numSalle;
} salle;

typedef struct pHeure {
    int debut_heure;
    int debut_minute;
    int fin_heure;
    int fin_minute;
} pHeure;

typedef struct date {
    int jour;
    int mois;
    int annee;
} date;
typedef struct reservation1 {
    char nom[50];
    salle salleTravaille;
     date dateR;
    char nomFiliere[20];
    char noMCours[20];
    pHeure heure;
} reservation1;
typedef struct reservationclub {
    char nom[50];
    salle salleTravaille;
     date dateR;
    char nomClub[20];
    char nomActivite[20];
    pHeure heure;
} reservationclub;

typedef struct reservation2 {
    salle salleTravaille;
     date dateR;
     pHeure heureR;
    char nom[20];
    char code[100];
} reservation2;

struct tm* TimeActuel() {
    time_t timer;
    struct tm* timeActuel;
    time(&timer);
    return localtime(&timer);
}
int estBissextile(int annee) {
    return (annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0);
}

int checkMois(int mois) {
    return mois >= 1 && mois <= 12;
}
int checkDate(date dateEntrer) {
        int joursDansLeMois;

    if (!checkMois(dateEntrer.mois)) {
        return 0;
    }
    switch (dateEntrer.mois) {
        case 2:
            joursDansLeMois = estBissextile(dateEntrer.annee) ? 29 : 28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            joursDansLeMois = 30;
            break;
        default:
            joursDansLeMois = 31;
            break;
    }

    return (dateEntrer.jour >= 1 && dateEntrer.jour <= joursDansLeMois);
}
int verifierSemaine(date dateUtilisateur, struct tm* timeActuel) {
    int joursRestantsDansLaSemaine = 7 - timeActuel->tm_wday;
    int joursEcart = dateUtilisateur.jour - timeActuel->tm_mday;

    if (joursEcart > joursRestantsDansLaSemaine || joursEcart < 0) {
        return 0;
    }

    return 1;
}
int estPlageHoraireValide(pHeure plage) {
    if ((plage.debut_heure == 8 && plage.debut_minute == 30 && plage.fin_heure == 10 && plage.fin_minute == 30) ||
        (plage.debut_heure == 8 && plage.debut_minute == 30 && plage.fin_heure == 12 && plage.fin_minute == 30) ||
        (plage.debut_heure == 10 && plage.debut_minute == 30 && plage.fin_heure == 12 && plage.fin_minute == 30) ||
        (plage.debut_heure == 14 && plage.debut_minute == 30 && plage.fin_heure == 16 && plage.fin_minute == 30) ||
        (plage.debut_heure == 14 && plage.debut_minute == 30 && plage.fin_heure == 18 && plage.fin_minute == 30) ||
        (plage.debut_heure == 16 && plage.debut_minute == 30 && plage.fin_heure == 18 && plage.fin_minute == 30)) {
        return 1;}
    else
    return 0;
}

int ClubPlageHoraireValide(pHeure plage) {
    if ((plage.debut_heure == 18 && plage.debut_minute == 30 && plage.fin_heure == 19 && plage.fin_minute == 30) ||
        (plage.debut_heure == 18 && plage.debut_minute == 30 && plage.fin_heure == 20 && plage.fin_minute == 30) ||
        (plage.debut_heure == 18 && plage.debut_minute == 30 && plage.fin_heure == 21 && plage.fin_minute == 30) ||
        (plage.debut_heure == 18 && plage.debut_minute == 30 && plage.fin_heure == 22 && plage.fin_minute == 30) ||
        (plage.debut_heure == 19 && plage.debut_minute == 30 && plage.fin_heure == 20 && plage.fin_minute == 30) ||
        (plage.debut_heure == 19 && plage.debut_minute == 30 && plage.fin_heure == 21 && plage.fin_minute == 30) ||
        (plage.debut_heure == 19 && plage.debut_minute == 30 && plage.fin_heure == 22 && plage.fin_minute == 30) ||
        (plage.debut_heure == 20 && plage.debut_minute == 30 && plage.fin_heure == 21 && plage.fin_minute == 30) ||
        (plage.debut_heure == 20 && plage.debut_minute == 30 && plage.fin_heure == 22 && plage.fin_minute == 30) ||
        (plage.debut_heure == 21 && plage.debut_minute == 30 && plage.fin_heure == 22 && plage.fin_minute == 30)) {
        return 1;}
    else
    return 0;
}
pHeure genererHeureValide(int x,int y) {
    pHeure heureValide;
    textbackground(12);

    do {
            textcolor(15);
      gotoxy(x,y);cscanf("%d", &heureValide.debut_heure);
      gotoxy(x+3,y);cscanf("%d",&heureValide.debut_minute);
      gotoxy(x+7,y);cscanf("%d:%d", &heureValide.fin_heure);
      gotoxy(x+10,y);cscanf("%d", &heureValide.fin_minute);
        if(!estPlageHoraireValide(heureValide)){
               textcolor(7);gotoxy(x,y);cprintf("   INVALID  ");
               getch();
               getch();
               gotoxy(x,y); cprintf("  :   /  :   ");
             }
    } while (!estPlageHoraireValide(heureValide));

    return heureValide;
}
pHeure genererHeureValideClub(int x,int y) {
    pHeure heureValide;
    textbackground(12);

    do {
            textcolor(15);
      gotoxy(x,y);cscanf("%d", &heureValide.debut_heure);
      gotoxy(x+3,y);cscanf("%d",&heureValide.debut_minute);
      gotoxy(x+7,y);cscanf("%d:%d", &heureValide.fin_heure);
      gotoxy(x+10,y);cscanf("%d", &heureValide.fin_minute);
        if(!ClubPlageHoraireValide(heureValide)){
               textcolor(7);gotoxy(x,y);cprintf("   INVALID  ");
               getch();
               getch();
               gotoxy(x,y); cprintf("  :   /  :   ");
             }
    } while (!ClubPlageHoraireValide(heureValide));

    return heureValide;
}
pHeure saisirHeure(){
      pHeure heure;
        scanf("%d",&heure.debut_heure);
        scanf("%d" ,&heure.fin_heure);
       return heure;
   }
int verifierDate(date dateUtilisateur, struct tm* timeActuel) {
    if (dateUtilisateur.annee < timeActuel->tm_year + 1900 ||
        (dateUtilisateur.annee == timeActuel->tm_year + 1900 && dateUtilisateur.mois < timeActuel->tm_mon + 1) ||
        (dateUtilisateur.annee == timeActuel->tm_year + 1900 && dateUtilisateur.mois == timeActuel->tm_mon + 1 && dateUtilisateur.jour <= timeActuel->tm_mday)) {
        return 0;
    }
    return 1;
}
date saisirDateValide(int x ,int y) {
    date dateSaisie;
    struct tm* timeActuel;
    int dateValide = 0;

    while (!dateValide) {
         textcolor(15);
        timeActuel = TimeActuel();
        gotoxy(x,y);cscanf("%d", &dateSaisie.jour);
        gotoxy(x+5,y);cscanf("%d", &dateSaisie.mois);
        gotoxy(x+10,y);cscanf("%d", &dateSaisie.annee);

        if (verifierDate(dateSaisie, timeActuel) && verifierSemaine(dateSaisie, timeActuel) && checkDate(dateSaisie)) {
            dateValide = 1;
        } else {
            gotoxy(x,y);cprintf("         ");

         textcolor(7);gotoxy(x,y);cprintf("   INVALIDE  ");
         getch();
         gotoxy(x,y);cprintf("    /   /     ");
        }
    }

    return dateSaisie;
}
char* modePasse(int x,int y) {
    char c;
    int i = 0;
    char* password = (char*)malloc(30 * sizeof(char));

    if (password == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }

    gotoxy(x,y);
    do {
        c = getch();
        if (c != 13 && i < 30) {
            password[i++] = c;
            cprintf("*");
        }
    } while (c != 13);

    password[i] = '\0'; // Null-terminate the string
    return password;
}
int isAlphabetic( char* chaine) {
    while (*chaine) {
        if (!isalpha(*chaine)) {
            return 0;
        }
        chaine++;
    }
    return 1;
}
char* enterChaine(int x,int y) {
    char chaine[20];
    do {
      gotoxy(x,y);cscanf("%s", chaine);
        if(isAlphabetic(chaine) == 0){
           gotoxy(x,y);
        cprintf("          ");
            gotoxy(x,y);printf("INVALIDE!");
                       gotoxy(x,y);

            cprintf("           ");

        }
    } while (isAlphabetic(chaine) == 0);
    return strdup(chaine);
}

int checkUser(char* type) {
    if (strcmp(type,"etud") == 0 || strcmp(type,"admin") == 0 || strcmp(type,"prof") == 0) {
        return 1;
    } else {
        return 0;
    }
}
int isNumeriqueTele(char* chaine) {
    while (*chaine) {
        if (!isdigit(*chaine)) {
            return 0;
        }
        chaine++;
    }
    return 1;
}

char* entrerTele(int x, int y) {
    char tele[11];
    char* teleResult;

    do {
        gotoxy(x, y);
        cscanf("%s", tele);
        if (isNumeriqueTele(tele) == 0 ||(isNumeriqueTele(tele)==1&& strlen(tele) !=10)) {
            gotoxy(x, y);cprintf("              ");
           gotoxy(x, y); printf("Invalid");
            gotoxy(x, y);
            cprintf("              ");
        }
    } while (isNumeriqueTele(tele) == 0 ||(isNumeriqueTele(tele)==1&& strlen(tele) !=10));

    teleResult = (char*)malloc((strlen(tele) + 1) * sizeof(char));

    if (teleResult == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }

    strcpy(teleResult, tele);

    return teleResult;
}

int isValidGmail(char* gmail) {
    if (strstr(gmail, "@gmail.com")) {
        return 1;
    } else
        return 0;
}
char* enterGmail(int x,int y) {
    char gmail[50];
    char* validGmail;
    do {
        gotoxy(x,y);cscanf("%s", gmail);
        if (!isValidGmail(gmail)) {
              gotoxy(x,y);cprintf("              ");
           gotoxy(x,y); cprintf("Invalid");
              gotoxy(x,y);cprintf("              ");

        }
    } while (!isValidGmail(gmail));

     validGmail = (char*)malloc((strlen(gmail) + 1) * sizeof(char));

    if (validGmail == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }

    strcpy(validGmail, gmail);

    return validGmail;
}
char* identifiantUser(int x ,int y) {
    char* identifiant = (char*)malloc(30* sizeof(char));
    if (identifiant == NULL) {
        printf("Erreur d'allocation de m้moire\n");
        exit(1);}
textbackground(12);
    do {
            textcolor(15);
    gotoxy(56,y);cscanf("%s",identifiant);
    if(checkUser(identifiant) == 0){
        gotoxy(56,y);cprintf("           ");
       textcolor(3);gotoxy(x+2,17);cprintf("INVALIDE IDENTIFIANT");
       getch();getch();
       gotoxy(x+2,17);cprintf("                       ");

    }
    } while (checkUser(identifiant) == 0);

    return identifiant;

}
char* saisirTypeSalle(int x,int y) {
    char saisie[20];
  textbackground(12);
    do {
            textcolor(15);
      gotoxy(x,y);cscanf("%s", saisie);

        if (strcmp(saisie, "TP") == 0 || strcmp(saisie, "TD") == 0 || strcmp(saisie, "cours") == 0) {
            char* typeChoisi = (char*)malloc(strlen(saisie) + 1);
            strcpy(typeChoisi, saisie);
            getch();
            return typeChoisi;
        } else {
            gotoxy(x,y);cprintf("          ");
            textcolor(7);gotoxy(x,y);cprintf("INVALID");
            getch();
            getch();
            gotoxy(x-1,y);cprintf("        ");
        }
    } while(1);
}
char nomBloc(int x,int y) {
    char bloc;
    textbackground(12);
    do {
            textcolor(15);
       gotoxy(x,y); cscanf(" %c", &bloc);
        if(bloc != 'A' && bloc != 'B'){
                gotoxy(x,y);cprintf("      ");
                 textcolor(7);gotoxy(x,y);cprintf("INVALID");
                 getch();
                gotoxy(x,y);cprintf("         ");
        }
    } while (bloc != 'A' && bloc != 'B');
    getch();
    return bloc;
}

int checkNumSalle(int x,int y) {
    int numSalle;
    do {
            textcolor(15);
       gotoxy(x,y); cscanf("%d", &numSalle);
        if (numSalle < 1 || numSalle > 10){
                gotoxy(x,y);cprintf("        ");
           textcolor(7); gotoxy(x,y);cprintf("INVALID");
               getch();
               getch();
                gotoxy(x,y);cprintf("        ");

        }
    } while (numSalle < 1 || numSalle > 10);
    return numSalle;
}
int checkNumSalle1(int x,int y) {
    int numSalle;
    do {
            textcolor(15);
       gotoxy(x,y); cscanf("%d", &numSalle);
        if (numSalle < 1 || numSalle > 20){
                gotoxy(x,y);cprintf("        ");
           textcolor(7); gotoxy(x,y);cprintf("INVALID");
               getch();
               getch();
                gotoxy(x,y);cprintf("        ");

        }
    } while (numSalle < 1 || numSalle > 20);
    return numSalle;
}

int compareHeure(pHeure heure1, pHeure heure2) {
    if (heure1.debut_heure == heure2.debut_heure &&heure1.debut_minute == heure2.debut_minute &&heure1.fin_heure == heure2.fin_heure &&heure1.fin_minute == heure2.fin_minute)
        return 1;
    else
        return 0;
}
int compareDate(date date1, date date2) {
    if((date1.jour == date2.jour) && (date1.mois == date2.mois) &&(date1.annee == date2.annee))
        return 1;
    else
        return 0;
}
int compareSalle(salle salle1,salle salle2){

    if((salle1.blocSalle==salle2.blocSalle)&&(salle1.numSalle==salle2.numSalle)&&(strcmp(salle1.typeSalles,salle2.typeSalles)==0)){
        return 1;
     }else {
     return 0;}

     }
int reservationClubExistante(reservationclub nouvelleReservation) {
    FILE *Club = fopen("reservationClub.bin", "rb");
        reservationclub reservationExistante;

    if(Club==NULL){
        printf("Erreur d'ouverture fichies reservationClub.bin");
        exit(1);
    }
    while (fread(&reservationExistante, sizeof(reservationclub), 1, Club) == 1) {
        if (compareSalle(reservationExistante.salleTravaille, nouvelleReservation.salleTravaille) &&compareDate(reservationExistante.dateR, nouvelleReservation.dateR) &&compareHeure(reservationExistante.heure, nouvelleReservation.heure)) {
            return 1;
        }
    }

    return 0;
}
void afficherChargement(int tempsPause,int x,int y) {
    int pourcentage;
    int largeurCarre = 50;
int i;
textcolor(2);
   gotoxy(x,y-1); cprintf("Chargement  : ");
    for (pourcentage = 5; pourcentage <= 100; pourcentage++) {
        int nombreCaracteresRemplis = (int)(pourcentage / 100.0 * largeurCarre);

        for ( i = 0; i < largeurCarre; i++) {
            if (i < nombreCaracteresRemplis) {
               gotoxy(x+i,y);cprintf("฿");
            } else {
                printf(" ");
            }
        }
        printf(" %d%%", pourcentage);
        fflush(stdout);

        Sleep(tempsPause/4);
    }

}
void afficherRESERVATIONCours(reservation1 uneReservation,int x,int y) {
    textcolor(15);gotoxy(x,y);cprintf("ษอออออออออออออออหอออออออออออออหออออออออออออออออหออออออออออหอออออออออหอออออออออออออออออออหออออออออออออออออป");
    gotoxy(x,y+1); textcolor(0); cprintf("บ               บ             บ                บ          บ         บ                   บ                บ");
    textcolor(15); gotoxy(x,y+2);cprintf("ศอออออออออออออออสอออออออออออออสออออออออออออออออสออออออออออสอออออออออสอออออออออออออออออออสออออออออออออออออผ");

         gotoxy(x+4,y+1);cprintf(" %s", uneReservation.nom);
      gotoxy(x+20,y+1);cprintf("%s", uneReservation.noMCours);
      gotoxy(x+32,y+1);cprintf("%s", uneReservation.nomFiliere);
     gotoxy(x+53,y+1); cprintf("%d", uneReservation.salleTravaille.numSalle);
     gotoxy(x+63,y+1); cprintf("%c", uneReservation.salleTravaille.blocSalle);
      gotoxy(x+74,y+1);cprintf("%d/%d/%d", uneReservation.dateR.jour, uneReservation.dateR.mois, uneReservation.dateR.annee);
     gotoxy(x+90,y+1); cprintf("%d:%d / %d:%d",uneReservation.heure.debut_heure,uneReservation.heure.debut_minute,uneReservation.heure.fin_heure,uneReservation.heure.fin_minute);

}
void affCour(){
      textbackground(4);

    textcolor(4);
    textcolor(15);gotoxy(30,2);cprintf("ษอออออออออออออออออออออออออออออออออออออออออออออออออออออป");
    textcolor(15);textcolor(12);gotoxy(30,3);cprintf("บ");textcolor(0);cprintf("                   AFFICHAGE EMPLOI                  ");textcolor(12); cprintf("บ");
    textcolor(15);gotoxy(30,4);cprintf("ศอออออออออออออออออออออออออออออออออออออออออออออออออออออผ");
    textcolor(15);gotoxy(8,5);cprintf("ษอออออออออออออออหอออออออออออออหออออออออออออออออหออออออออออหอออออออออหอออออออออออออออออออหออออออออออออออออป");
   gotoxy(8,6); textcolor(0); cprintf("บ     NOM       บ    COURS     บ    FILIER      บ SALLE    บ  BLOC   บ     DATE          บ    HORAIRE    บ");
    textcolor(15);gotoxy(8,7);cprintf("ศอออออออออออออออสอออออออออออออสออออออออออออออออสออออออออออสอออออออออสอออออออออออออออออออสออออออออออออออออผ");

    }
char reponse(int x, int y) {
    char rep;
    textbackground(11);
      textcolor(15);gotoxy(x, y);cprintf("ษออออออออออออออออออออออออออออออออออป");
    textcolor(15);gotoxy(x, y+1);cprintf("บ  REVIENT AU MENU PROFFESSEUR:    บ");
    textcolor(15);gotoxy(x, y+2);cprintf("ศออออออออออออออออออออออออออออออออออผ");
    gotoxy(x+32, y+1);
    cscanf(" %c", &rep);
    return rep;
}
char reponse1(int x, int y) {
    char rep;
    textbackground(11);
     textcolor(15);gotoxy(x, y);cprintf("ษอออออออออออออออออออออออออออออออออป");
   textcolor(15);gotoxy(x, y+1);cprintf("บ  REVIENT AU MENU ETUDIANT:      บ");
   textcolor(15);gotoxy(x, y+2);cprintf("ศอออออออออออออออออออออออออออออออออผ");
    gotoxy(x+32, y+1);
    cscanf(" %c", &rep);
    return rep;
}
char reponse2(int x,int y) {
    char rep;
    textbackground(11);
    textcolor(15);gotoxy(x+15, y-1);cprintf("ษอออออออออออออออออออออออออออออออออออป");
      textcolor(15);gotoxy(x+15, y);cprintf("บ  REVIENT AU MENU ADMINSTRATION:   บ");
    textcolor(15);gotoxy(x+15, y+1);cprintf("ศอออออออออออออออออออออออออออออออออออผ");
    gotoxy(x+50, y);
    cscanf(" %c", &rep);
    return rep;
}
char afficher_reservation_salles(int n){
    FILE *Salle;
    char rep;
    reservation1 newreservation;
         int i=3;

    affCour();
    textbackground(12);
   Salle=fopen("reservation.bin","rb+");
        if (Salle == NULL) {
        printf("Erreur d'ouverture du fichier de reservation\n");
        exit(1);
    }
    while(fread(&newreservation,sizeof(reservation1),1,Salle)==1){
            afficherRESERVATIONCours(newreservation,8,6+i);
           i+=3;
    }
    fclose(Salle);
    if(n==1)
    rep=reponse(13,i+7);
    else
    rep=reponse1(13,i+7);
    return  rep;

}


void creation_reservation_club(reservationclub newreservation){

    FILE *Club;

    Club=fopen("reservationClub.bin","ab+");
        if (Club == NULL) {
        printf("ERREUR");
        exit(1);
    }else{

   if(reservationClubExistante(newreservation)==1){
    textbackground(12);
    textcolor(15);gotoxy(38,30);cprintf("ECHEC DE RESERVATION SALE DEJA RESERVER");
   }else{
      fwrite(&newreservation,sizeof(reservationclub),1,Club);
            textbackground(0);
            afficherChargement(100,33,30);
              textcolor(2);gotoxy(33,32);cprintf("\nRESERVATION EFFECTUER AVEC SUCCES");
   }
    fclose(Club);
    }
}
char clubReservation() {
       char rep;

    reservationclub newreservation;
        textbackground(4);
    textcolor(4);
    textcolor(15);gotoxy(30,5);cprintf("ษอออออออออออออออออออออออออออออออออออออออออออออออออออออป");
    textcolor(15);textcolor(12);gotoxy(30,6);cprintf("บ");textcolor(0);cprintf("                   RESERVATION CLUB                  ");textcolor(12); cprintf("บ");
    textcolor(15);gotoxy(30,7);cprintf("ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออน");
   textcolor(15); gotoxy(30,8);cprintf("บ                                                     บ");
   textcolor(12); gotoxy(30,9);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,10);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,11);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,12);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,13);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,14);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,15);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,16);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,17);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,18);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,19);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,20);cprintf("บ                                                     บ");
  textcolor(12); gotoxy(30,21);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,22);cprintf("บ                                                     บ");
  textcolor(12); gotoxy(30,23);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,24);cprintf("บ                                                     บ");
  textcolor(12); gotoxy(30,25);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,26);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,27);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,28);cprintf("ศอออออออออออออออออออออออออออออออออออออออออออออออออออออผ");


    gotoxy(33,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,10);cprintf("ณ NOM:                ณ");
   gotoxy(33,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


    gotoxy(58,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,10);cprintf("ณ CLUB:               ณ");
   gotoxy(58,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   gotoxy(33,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,14);cprintf("ณACTIVITE:            ณ");
   gotoxy(33,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


   gotoxy(58,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,14);cprintf("ณ DATE:   /    /      ณ");
   gotoxy(58,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


   gotoxy(33,17);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,18);cprintf("ณHORAIRE:  :   /  :   ณ");
   gotoxy(33,19);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");
   gotoxy(58,17);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,18);cprintf("ณ BLOC:               ณ");
   gotoxy(58,19);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


   gotoxy(33,20);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,21);cprintf("ณTYPE SALLE:          ณ");
   gotoxy(33,22);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   gotoxy(58,20);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,21);cprintf("ณ NUM:                ณ");
   gotoxy(58,22);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(47,24);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(47,25);cprintf("ณ  SUBMIT(Entre)     ณ");
    gotoxy(47,26);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

        strcpy(newreservation.nom,enterChaine(39,10));
        strcpy(newreservation.nomClub,enterChaine(66,10));
        strcpy(newreservation.nomActivite,enterChaine(44,14));

    newreservation.dateR=saisirDateValide(66,14);
    newreservation.heure=genererHeureValideClub(42,18);
    newreservation.salleTravaille.blocSalle=nomBloc(66,18);
    strcpy(newreservation.salleTravaille.typeSalles,saisirTypeSalle(45,21));
    newreservation.salleTravaille.numSalle=checkNumSalle(64,21);
    creation_reservation_club(newreservation);
    rep=reponse1(10,36);
    gotoxy(50,45);
    return rep;
}
reservationclub clubReservation1() {
    reservationclub newreservation;
        textbackground(4);

    textcolor(4);
    textcolor(15);gotoxy(30,5);cprintf("ษอออออออออออออออออออออออออออออออออออออออออออออออออออออป");
    textcolor(15);textcolor(12);gotoxy(30,6);cprintf("บ");textcolor(0);cprintf("                   RESERVATION CLUB                  ");textcolor(12); cprintf("บ");
    textcolor(15);gotoxy(30,7);cprintf("ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออน");
   textcolor(15); gotoxy(30,8);cprintf("บ                                                     บ");
   textcolor(12); gotoxy(30,9);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,10);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,11);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,12);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,13);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,14);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,15);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,16);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,17);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,18);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,19);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,20);cprintf("บ                                                     บ");
  textcolor(12); gotoxy(30,21);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,22);cprintf("บ                                                     บ");
  textcolor(12); gotoxy(30,23);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,24);cprintf("บ                                                     บ");
  textcolor(12); gotoxy(30,25);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,26);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,27);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,28);cprintf("ศอออออออออออออออออออออออออออออออออออออออออออออออออออออผ");


    gotoxy(33,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,10);cprintf("ณ NOM:                ณ");
   gotoxy(33,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


    gotoxy(58,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,10);cprintf("ณ CLUB:               ณ");
   gotoxy(58,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   gotoxy(33,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,14);cprintf("ณACTIVITE:            ณ");
   gotoxy(33,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


   gotoxy(58,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,14);cprintf("ณ DATE:   /    /      ณ");
   gotoxy(58,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


   gotoxy(33,17);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,18);cprintf("ณHORAIRE:  :   /  :   ณ");
   gotoxy(33,19);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");
   gotoxy(58,17);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,18);cprintf("ณ BLOC:               ณ");
   gotoxy(58,19);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


   gotoxy(33,20);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,21);cprintf("ณTYPE SALL:           ณ");
   gotoxy(33,22);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   gotoxy(58,20);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,21);cprintf("ณ NUM:                ณ");
   gotoxy(58,22);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(47,24);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(47,25);cprintf("ณ  SUBMIT(Entre)     ณ");
    gotoxy(47,26);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

        strcpy(newreservation.nom,enterChaine(39,10));
        strcpy(newreservation.nomClub,enterChaine(66,10));
        strcpy(newreservation.nomActivite,enterChaine(44,14));

    newreservation.dateR=saisirDateValide(66,14);
    newreservation.heure=genererHeureValideClub(42,18);
    newreservation.salleTravaille.blocSalle=nomBloc(66,18);
    strcpy(newreservation.salleTravaille.typeSalles,saisirTypeSalle(45,21));
    newreservation.salleTravaille.numSalle=checkNumSalle(64,21);
        textbackground(0);afficherChargement(100,33,31);

   return newreservation;
}
reservationclub clubReservation2() {
    reservationclub newreservation;
        textbackground(4);

    textcolor(4);
    textcolor(15);gotoxy(30,5);cprintf("ษอออออออออออออออออออออออออออออออออออออออออออออออออออออป");
    textcolor(15);textcolor(12);gotoxy(30,6);cprintf("บ");textcolor(0);cprintf("         INFO DE RESERVATION DE CLUB A ANNULER       ");textcolor(12); cprintf("บ");
    textcolor(15);gotoxy(30,7);cprintf("ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออน");
   textcolor(15); gotoxy(30,8);cprintf("บ                                                     บ");
   textcolor(12); gotoxy(30,9);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,10);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,11);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,12);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,13);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,14);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,15);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,16);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,17);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,18);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,19);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,20);cprintf("บ                                                     บ");
  textcolor(12); gotoxy(30,21);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,22);cprintf("บ                                                     บ");
  textcolor(12); gotoxy(30,23);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,24);cprintf("บ                                                     บ");
  textcolor(12); gotoxy(30,25);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,26);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,27);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,28);cprintf("ศอออออออออออออออออออออออออออออออออออออออออออออออออออออผ");


    gotoxy(33,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,10);cprintf("ณ NOM:                ณ");
   gotoxy(33,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


    gotoxy(58,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,10);cprintf("ณ CLUB:               ณ");
   gotoxy(58,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   gotoxy(33,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,14);cprintf("ณACTIVITE:            ณ");
   gotoxy(33,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


   gotoxy(58,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,14);cprintf("ณ DATE:   /    /      ณ");
   gotoxy(58,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


   gotoxy(33,17);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,18);cprintf("ณHORAIRE:  :   /  :   ณ");
   gotoxy(33,19);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");
   gotoxy(58,17);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,18);cprintf("ณ BLOC:               ณ");
   gotoxy(58,19);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


   gotoxy(33,20);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,21);cprintf("ณTYPE SALL:           ณ");
   gotoxy(33,22);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   gotoxy(58,20);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,21);cprintf("ณ NUM:                ณ");
   gotoxy(58,22);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(47,24);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(47,25);cprintf("ณ  SUBMIT(Entre)     ณ");
    gotoxy(47,26);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

        strcpy(newreservation.nom,enterChaine(39,10));
        strcpy(newreservation.nomClub,enterChaine(66,10));
        strcpy(newreservation.nomActivite,enterChaine(44,14));

    newreservation.dateR=saisirDateValide(66,14);
    newreservation.heure=genererHeureValideClub(42,18);
    newreservation.salleTravaille.blocSalle=nomBloc(66,18);
    strcpy(newreservation.salleTravaille.typeSalles,saisirTypeSalle(45,21));
    newreservation.salleTravaille.numSalle=checkNumSalle(64,21);
        textbackground(0);afficherChargement(100,33,31);

   return newreservation;
}
void afficher_club(reservationclub newreservation,int x,int y){
       textcolor(15);gotoxy(x,y);cprintf("ษอออออออออออออออหอออออออออออออหออออออออออออออออหออออออออออหอออออออออหอออออออออออออออออออหออออออออออออออออป");
  gotoxy(x,y+1); textcolor(0); cprintf("บ               บ             บ                บ          บ         บ                   บ                บ");
    textcolor(15); gotoxy(x,y+2);cprintf("ศอออออออออออออออสอออออออออออออสออออออออออออออออสออออออออออสอออออออออสอออออออออออออออออออสออออออออออออออออผ");
  gotoxy(x+4,y+1);cprintf("%s",newreservation.nom);
  gotoxy(x+20,y+1);cprintf("%s ",newreservation.nomClub);
  gotoxy(x+32,y+1);cprintf("%s",newreservation.nomActivite);
  gotoxy(x+53,y+1);cprintf("%d",newreservation.salleTravaille.numSalle);
  gotoxy(x+63,y+1);cprintf("%c",newreservation.salleTravaille.blocSalle);
  gotoxy(x+74,y+1);cprintf(" %d/%d/%d",newreservation.dateR.jour,newreservation.dateR.mois,newreservation.dateR.annee);
  gotoxy(x+90,y+1);cprintf("%d/%d--%d/%d",newreservation.heure.debut_heure,newreservation.heure.debut_minute,newreservation.heure.fin_heure,newreservation.heure.fin_minute);

}



void affCub(){
      textbackground(4);

    textcolor(4);
    textcolor(15);gotoxy(30,2);cprintf("ษอออออออออออออออออออออออออออออออออออออออออออออออออออออป");
    textcolor(15);textcolor(12);gotoxy(30,3);cprintf("บ");textcolor(0);cprintf("                   AFFICHAGE SALLES                  ");textcolor(12); cprintf("บ");
    textcolor(15);gotoxy(30,4);cprintf("ศอออออออออออออออออออออออออออออออออออออออออออออออออออออผ");
    textcolor(15);gotoxy(8,5);cprintf("ษอออออออออออออออหอออออออออออออหออออออออออออออออหออออออออออหอออออออออหอออออออออออออออออออหออออออออออออออออป");
  gotoxy(8,6); textcolor(0); cprintf("บ     NOM       บ    CLUB     บ  ACTIVITE      บ SALLE    บ  BLOC   บ     DATE          บ    HORAIRE     บ");
textcolor(15);    gotoxy(8,7);cprintf("ศอออออออออออออออสอออออออออออออสออออออออออออออออสออออออออออสอออออออออสอออออออออออออออออออสออออออออออออออออผ");

    }

char afficher_reservation_club(){
    FILE *Club;    int i=3;
    char rep;
    reservationclub newreservation;

    Club=fopen("reservationClub.bin","rb+");
        if (Club == NULL) {
        printf("Erreur d'ouverture du fichier de reservationClub\n");
        exit(1);
    }
    affCub();
    while(fread(&newreservation,sizeof(reservationclub),1,Club)==1){
        afficher_club(newreservation,8,6+i);
              i+=3;
    }
    rep=reponse1(40,7+i);
    fclose(Club);
    return rep;
}
void writeUserDataToFile(user User) {
    FILE* file = fopen("dataUseres.bin", "ab");
    if (file == NULL) {
        printf("Error opening file dataUsers for writing.\n");
        return;
    }
    fwrite(&User, sizeof(user), 1, file);
    fclose(file);
}



void login(){
           user U;
           char password[20];
          textbackground(0);
          clrscr();

    textbackground(4);

    textcolor(4);
    textcolor(15);gotoxy(30,5);cprintf("ษอออออออออออออออออออออออออออออออออออออออออออออออออออออป");
    textcolor(15);textcolor(12);gotoxy(30,6);cprintf("บ");textcolor(0);cprintf("                       SIGN UP                       ");textcolor(12); cprintf("บ");
    textcolor(15);gotoxy(30,7);cprintf("ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออน");
   textcolor(15); gotoxy(30,8);cprintf("บ                                                     บ");
   textcolor(12); gotoxy(30,9);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,10);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,11);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,12);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,13);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,14);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,15);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,16);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,17);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,18);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,19);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,20);cprintf("บ                                                     บ");
  textcolor(12); gotoxy(30,21);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,22);cprintf("บ                                                     บ");
  textcolor(12); gotoxy(30,23);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,24);cprintf("บ                                                     บ");
  textcolor(12); gotoxy(30,25);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,26);cprintf("ศอออออออออออออออออออออออออออออออออออออออออออออออออออออผ");


    gotoxy(32,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(32,10);cprintf("ณ NOM:               ณ");
   gotoxy(32,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");



    gotoxy(56,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(56,10);cprintf("ณ Email:               ณ");
   gotoxy(56,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


   gotoxy(32,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(32,14);cprintf("ณ PRENOM:            ณ");
   gotoxy(32,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");



   gotoxy(56,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(56,14);cprintf("ณ TELE:               ณ");
   gotoxy(56,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");



   gotoxy(32,17);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(32,18);cprintf("ณPASSWORD:            ณ");
   gotoxy(32,19);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");



   gotoxy(56,17);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(56,18);cprintf("ณ CONFIRME:           ณ");
   gotoxy(56,19);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");



    gotoxy(45,22);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(45,23);cprintf("ณ  SUBMIT(ENTRE)     ณ");
    gotoxy(45,24);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");
   strcpy(U.nomUser, enterChaine(39, 10));
    strcpy(U.Email, enterGmail(65, 10));
    strcpy(U.prenomUser, enterChaine(41, 14));
    strcpy(U.tele, entrerTele(63, 14));

    getch();
      do{
        textcolor(5);
       strcpy(U.password, modePasse(43, 18));
       strcpy(password, modePasse(67, 18));
       gotoxy(43,18);cprintf("          ");
       gotoxy(67,18);cprintf("          ");
       if(strcmp(U.password, password) != 0){
            textcolor(6);gotoxy(49,20);cprintf("Invalide Password!");
            getch();
            getch();
            gotoxy(49,20);cprintf("                   ");
       }

      }while(strcmp(U.password, password) != 0);
        textbackground(0);afficherChargement(100,31,29);

    gotoxy(50, 30);

       writeUserDataToFile(U);
       clrscr();
       menuIdentifiant();
       }

  int verifierConnexion(char email[],char password[]) {

    FILE* fichier = fopen("dataUseres.bin", "rb");
    user readUser;

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier dataUseres.bin en lecture.\n");
        return 0;
    }
    while (fread(&readUser, sizeof(user), 1, fichier) == 1) {
        if (strcmp(email, readUser.Email) == 0 && strcmp(password, readUser.password) == 0) {
            fclose(fichier);
            return 1;
        }
    }

    fclose(fichier);

    return 0;
}

void connextion(){
  char email [50];
  char password[20];
  textbackground(0);
  clrscr();
  textbackground(4);
    textcolor(15);
    gotoxy(30,5);cprintf("ษอออออออออออออออออออออออออออออออออออออออออออออออป");
    textcolor(12);gotoxy(30,6);cprintf("บ");
    textcolor(0);cprintf("                   CONNEXION                   ");
    textcolor(12);cprintf("บ");
    textcolor(15);gotoxy(30,7);cprintf("ฬอออออออออออออออออออออออออออออออออออออออออออออออน");
    textcolor(15);gotoxy(30,8);cprintf("บ                                               บ");
    textcolor(12);gotoxy(30,9);cprintf("บ                                               บ");
   textcolor(15);gotoxy(30,10);cprintf("บ                                               บ");
   textcolor(12);gotoxy(30,11);cprintf("บ                                               บ");
   textcolor(15);gotoxy(30,12);cprintf("บ                                               บ");
  textcolor(12); gotoxy(30,13);cprintf("บ                                               บ");
  textcolor(15); gotoxy(30,14);cprintf("บ                                               บ");
   textcolor(12);gotoxy(30,15);cprintf("บ                                               บ");
   textcolor(15);gotoxy(30,16);cprintf("บ                                               บ");
   textcolor(12);gotoxy(30,17);cprintf("บ                                               บ");
  textcolor(15); gotoxy(30,18);cprintf("ศอออออออออออออออออออออออออออออออออออออออออออออออผ");


   gotoxy(45,10);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(45,11);cprintf("ณ EMAIL:               ณ");
   gotoxy(45,12);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   gotoxy(45,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(45,14);cprintf("ณPASSWORD:             ณ");
   gotoxy(45,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");
   strcpy(email,enterGmail(54,11));
   getch();
   strcpy(password,modePasse(55,14));
   verifierConnexion(email,password);
   if(verifierConnexion(email,password)){
           textbackground(0);afficherChargement(100,30,21);
           clrscr();
           menuIdentifiant();
   }
   else{
            gotoxy(45,16); textcolor(4);cprintf("vous devez creer un compte ");
            getch();
            gotoxy(45,16);cprintf("                          ");
            clrscr();
            login();

   }
   gotoxy(50,30);
    }

void page(){
     int chouix ;
     textbackground(4);
    textcolor(15);gotoxy(45,2);cprintf("ษอออออออออออออออออออออออออออป");
    textcolor(15);gotoxy(45,3);cprintf("บ                           บ");
    textcolor(12);gotoxy(30,4);cprintf("ษออออ");
                      textcolor(15);cprintf("อออออ");
                           textcolor(12);cprintf("อออออน");
                           textcolor(0);cprintf("BIENVENUE AU SALLE MANAGER ");
                            textcolor(12)  ;            cprintf("ฬอออออ");
                textcolor(15);                                cprintf("อออออ");
               textcolor(12);                                      cprintf("อออออป");
    textcolor(15);gotoxy(30,5);cprintf("บ              บ                           บ               บ");
   textcolor(15); gotoxy(30,6);cprintf("บ              ศอออออออออออออออออออออออออออผ               บ");
    textcolor(12);gotoxy(30,7);cprintf("บ                                                          บ");
    textcolor(12);gotoxy(30,8);cprintf("บ                                                          บ");
    textcolor(15);gotoxy(30,9);cprintf("บ                                                          บ"),
   textcolor(15);gotoxy(30,10);cprintf("บ                                                          บ");
   textcolor(12);gotoxy(30,11);cprintf("บ                                                          บ");
   textcolor(12);gotoxy(30,12);cprintf("บ                                                          บ");
   textcolor(15);gotoxy(30,13);cprintf("บ                                                          บ"),
   textcolor(15);gotoxy(30,14);cprintf("บ                                                          บ");
   textcolor(12);gotoxy(30,15);cprintf("บ                                                          บ");
   textcolor(12);gotoxy(30,16);cprintf("บ                                                          บ");
   textcolor(15);gotoxy(30,17);cprintf("บ                                                          บ");
  textcolor(15); gotoxy(30,18);cprintf("บ                                                          บ");
   textcolor(12);gotoxy(30,19);cprintf("บ                                                          บ");
   textcolor(15);gotoxy(30,20);cprintf("ศออออ");
                      textcolor(12);cprintf("อออออ");
                            textcolor(15);cprintf("อออออ");
                                  textcolor(12);cprintf("อออออ");
                                         textcolor(15);cprintf("อออออ");
                                               textcolor(12);cprintf("อออออ");
                                                     textcolor(15);cprintf("อออออ");
                                                            textcolor(12);cprintf("อออออ");
                                                                  textcolor(15);cprintf("อออออ");
                                                                       textcolor(12);cprintf("อออออ");
                                                                            textcolor(15);cprintf("อออออ");
                                                                        textcolor(12);cprintf("ออออผ");

textcolor(15);
    gotoxy(35,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(35,10);cprintf("ณ   1:SIGN UP:      ณ");
   gotoxy(35,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(62,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(62,10);cprintf("ณ   2:CONNEXION:    ณ");
   gotoxy(62,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   gotoxy(50,14);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(50,15);cprintf("ณ CHOIX :           ณ");
   gotoxy(50,16);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   do{
   gotoxy(60,15);cscanf("%d",&chouix);
    if(chouix<1||chouix>2){
        gotoxy(60,15);cprintf("INVALID");
   getch();
   gotoxy(60,15);cprintf("         ");
    }
   }while(chouix<1||chouix>2);
   if(chouix==1){
        clrscr();
    login();
   }
   else{
        clrscr();
    connextion();
   }
}

void annulerReservationClub(){
    int a=0;
        reservationclub nouvelleReservation,reservationExistante;

        FILE *fichier = fopen("reservationClub.bin", "rb+");
    if(fichier==NULL){
        printf("Erreur d'ouverture fichies reservationClub.bin");
        exit(1);
    }else{
             FILE* temp=fopen("temp3.bin","ab+");
       if(temp==NULL){
              printf("Erreur d'ouverture de temp.bin");

       }
        nouvelleReservation=clubReservation2();

      while(fread(&reservationExistante,sizeof(reservationclub),1,fichier)==1){
       if(!(compareSalle(reservationExistante.salleTravaille, nouvelleReservation.salleTravaille) &&compareDate(reservationExistante.dateR, nouvelleReservation.dateR) &&compareHeure(reservationExistante.heure, nouvelleReservation.heure))){
           fwrite(&reservationExistante,sizeof(reservation1),1,temp);

    }else a=1;
   }
   fclose(fichier);
   fclose(temp);
   remove("reservationClub.bin");
   rename("temp3.bin","reservationClub.bin");
   if(a==1){
            textbackground(11);
                   textcolor(15);gotoxy(30,34);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
                    textcolor(4);gotoxy(30,35);cprintf("ณRESERVATION ANUULER AVEC SUCCESณ");
                   textcolor(15);gotoxy(30,36);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");
   }
   else{
                            textbackground(11);
                    textcolor(15);gotoxy(30,34);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
                     textcolor(4);gotoxy(30,35);cprintf("ณRESERVATION N'EXIST PAS   ณ");
                    textcolor(15);gotoxy(30,36);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   }
  }
}

void  pageEtudiant(){
      int choix ;
      char reponse;
     textbackground(4);
    textcolor(15);gotoxy(45,2);cprintf("ษอออออออออออออออออออออออออออป");
    textcolor(15);gotoxy(45,3);cprintf("บ                           บ");
    textcolor(12);gotoxy(30,4);cprintf("ษออออ");
                      textcolor(15);cprintf("อออออ");
                           textcolor(12);cprintf("อออออน");
                           textcolor(0);cprintf("       ESPACE ETUDIANT     ");
                            textcolor(12)  ;            cprintf("ฬอออออ");
                textcolor(15);                                cprintf("อออออ");
               textcolor(12);                                      cprintf("อออออป");
    textcolor(15);gotoxy(30,5);cprintf("บ              บ                           บ               บ");
   textcolor(15); gotoxy(30,6);cprintf("บ              ศอออออออออออออออออออออออออออผ               บ");
    textcolor(12);gotoxy(30,7);cprintf("บ                                                          บ");
    textcolor(12);gotoxy(30,8);cprintf("บ                                                          บ");
    textcolor(15);gotoxy(30,9);cprintf("บ                                                          บ"),
   textcolor(15);gotoxy(30,10);cprintf("บ                                                          บ");
   textcolor(12);gotoxy(30,11);cprintf("บ                                                          บ");
   textcolor(12);gotoxy(30,12);cprintf("บ                                                          บ");
   textcolor(15);gotoxy(30,13);cprintf("บ                                                          บ"),
   textcolor(15);gotoxy(30,14);cprintf("บ                                                          บ");
   textcolor(12);gotoxy(30,15);cprintf("บ                                                          บ");
   textcolor(12);gotoxy(30,16);cprintf("บ                                                          บ");
   textcolor(15);gotoxy(30,17);cprintf("บ                                                          บ");
   textcolor(15);gotoxy(30,18);cprintf("บ                                                          บ");
   textcolor(12);gotoxy(30,19);cprintf("บ                                                          บ");
  textcolor(15); gotoxy(30,20);cprintf("บ                                                          บ");
   textcolor(12);gotoxy(30,21);cprintf("บ                                                          บ");
   textcolor(15);gotoxy(30,22);cprintf("ศออออ");
                      textcolor(12);cprintf("อออออ");
                            textcolor(15);cprintf("อออออ");
                                  textcolor(12);cprintf("อออออ");
                                         textcolor(15);cprintf("อออออ");
                                               textcolor(12);cprintf("อออออ");
                                                     textcolor(15);cprintf("อออออ");
                                                            textcolor(12);cprintf("อออออ");
                                                                  textcolor(15);cprintf("อออออ");
                                                                       textcolor(12);cprintf("อออออ");
                                                                            textcolor(15);cprintf("อออออ");
                                                                        textcolor(12);cprintf("ออออผ");

textcolor(15);
    gotoxy(35,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(35,10);cprintf("ณ    1:AFFICHER RESERVATION DES COURS             ณ");
   gotoxy(35,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(35,12);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(35,13);cprintf("ณ   2:AFFICHER RESERVATION DES CLUBS:             ณ");
    gotoxy(35,14);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(35,15);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(35,16);cprintf("ณ   3:EFFECTUER UNE RESERVATION DE CLUB           ณ");
    gotoxy(35,17);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   gotoxy(50,18);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(50,19);cprintf("ณ CHOIX :           ณ");
   gotoxy(50,20);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

      do{
        textcolor(15);
      gotoxy(60,19);cscanf("%d",&choix);
        if(choix<1||choix>3){
        textcolor(7) ;  gotoxy(60,19);cprintf("INVALID");
       getch();
       getch();
       gotoxy(60,19);cprintf("         ");
         }
        }while(choix<1||choix>3);
    switch (choix){
         case 1:
            textbackground(0);
             afficherChargement(100,37,26);
             clrscr();
         reponse=afficher_reservation_salles(2);
      break;
         case 2:
            textbackground(0);
            afficherChargement(100,37,26);
             clrscr();

         reponse=afficher_reservation_club();
         break;

         case 3:
            textbackground(0);
            afficherChargement(100,37,26);
             clrscr();
         reponse=clubReservation();
         break;
  }
        textcolor(15);
        if(choix<1||choix>3){
        textcolor(7) ;  gotoxy(50,22);cprintf("INVALID");
       getch();
       getch();
       gotoxy(50,22);cprintf("         ");
         }

    if (reponse == 'O' || reponse == 'o') {
        textbackground(0);
        clrscr();
        pageEtudiant();
    }
     }
int reservationExistante(reservation1 nouvelleReservation) {
    FILE *fichier = fopen("reservation.bin", "rb");
        reservation1 reservationExistante;
    if(fichier==NULL){
        printf("Erreur d'ouverture fichies reservation.bin");
        exit(1);
    }
    while (fread(&reservationExistante, sizeof(reservation1), 1, fichier) == 1) {
        if (compareSalle(reservationExistante.salleTravaille, nouvelleReservation.salleTravaille) &&compareDate(reservationExistante.dateR, nouvelleReservation.dateR) &&compareHeure(reservationExistante.heure, nouvelleReservation.heure)) {
            return 1;
        }
    }

    return 0;
}
void reserverSalles(reservation1 nouvelleReservation)
{
    FILE *fichier = fopen("reservation.bin", "ab+");
    if(fichier==NULL){
        printf("Erreur d'ouverture fichies reservationClub.bin");
        exit(1);
    }
    else{
        if(reservationExistante(nouvelleReservation)==1){
    textbackground(12);
    textcolor(15);gotoxy(38,30);cprintf("ECHEC DE RESERVATION SALE DEJA RESERVER");
        }
        else{
      fwrite(&nouvelleReservation,sizeof(reservationclub),1,fichier);
            textbackground(0);
            afficherChargement(100,33,30);
              textcolor(2);gotoxy(33,32);cprintf("\nRESERVATION EFFECTUER AVEC SUCCES");
        }
      fclose(fichier);
    }
  }
reservation1 profReservation1() {
    reservation1 newreservation;
    char rep;
        textbackground(4);

    textcolor(4);
    textcolor(15);gotoxy(30,5);cprintf("ษอออออออออออออออออออออออออออออออออออออออออออออออออออออป");
    textcolor(15);textcolor(12);gotoxy(30,6);cprintf("บ");textcolor(0);cprintf("                   RESERVATION  PROF                 ");textcolor(12); cprintf("บ");
    textcolor(15);gotoxy(30,7);cprintf("ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออน");
   textcolor(15); gotoxy(30,8);cprintf("บ                                                     บ");
   textcolor(12); gotoxy(30,9);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,10);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,11);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,12);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,13);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,14);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,15);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,16);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,17);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,18);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,19);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,20);cprintf("บ                                                     บ");
  textcolor(12); gotoxy(30,21);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,22);cprintf("บ                                                     บ");
  textcolor(12); gotoxy(30,23);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,24);cprintf("บ                                                     บ");
  textcolor(12); gotoxy(30,25);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,26);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,27);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,28);cprintf("ศอออออออออออออออออออออออออออออออออออออออออออออออออออออผ");


    gotoxy(33,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,10);cprintf("ณ NOM:                ณ");
   gotoxy(33,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


    gotoxy(58,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,10);cprintf("ณ COUR:               ณ");
   gotoxy(58,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   gotoxy(33,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,14);cprintf("ณFILIER:              ณ");
   gotoxy(33,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


   gotoxy(58,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,14);cprintf("ณ DATE:   /    /      ณ");
   gotoxy(58,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


   gotoxy(33,17);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,18);cprintf("ณHORAIRE:  :   /  :   ณ");
   gotoxy(33,19);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");
   gotoxy(58,17);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,18);cprintf("ณ BLOC:               ณ");
   gotoxy(58,19);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


   gotoxy(33,20);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,21);cprintf("ณTYPE SALL:           ณ");
   gotoxy(33,22);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   gotoxy(58,20);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,21);cprintf("ณ NUM:                ณ");
   gotoxy(58,22);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(47,24);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(47,25);cprintf("ณ  SUBMIT(Entre)     ณ");
    gotoxy(47,26);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

        strcpy(newreservation.nom,enterChaine(39,10));
        strcpy(newreservation.noMCours,enterChaine(66,10));
        strcpy(newreservation.nomFiliere,enterChaine(44,14));

    newreservation.dateR=saisirDateValide(66,14);
    newreservation.heure=genererHeureValide(42,18);
    newreservation.salleTravaille.blocSalle=nomBloc(66,18);
    strcpy(newreservation.salleTravaille.typeSalles,saisirTypeSalle(45,21));
    newreservation.salleTravaille.numSalle=checkNumSalle(64,21);
    reserverSalles(newreservation);
    rep=reponse(43,32);
    return newreservation;

}
reservation1 profReservation2() {
    reservation1 newreservation;
    char rep;
        textbackground(4);

    textcolor(4);
    textcolor(15);gotoxy(30,5);cprintf("ษอออออออออออออออออออออออออออออออออออออออออออออออออออออป");
    textcolor(15);textcolor(12);gotoxy(30,6);cprintf("บ");textcolor(0);cprintf("            INFO DE RESERVATION A ANUULER            ");textcolor(12); cprintf("บ");
    textcolor(15);gotoxy(30,7);cprintf("ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออน");
   textcolor(15); gotoxy(30,8);cprintf("บ                                                     บ");
   textcolor(12); gotoxy(30,9);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,10);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,11);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,12);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,13);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,14);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,15);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,16);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,17);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,18);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,19);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,20);cprintf("บ                                                     บ");
  textcolor(12); gotoxy(30,21);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,22);cprintf("บ                                                     บ");
  textcolor(12); gotoxy(30,23);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,24);cprintf("บ                                                     บ");
  textcolor(12); gotoxy(30,25);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,26);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,27);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,28);cprintf("ศอออออออออออออออออออออออออออออออออออออออออออออออออออออผ");


    gotoxy(33,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,10);cprintf("ณ NOM:                ณ");
   gotoxy(33,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


    gotoxy(58,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,10);cprintf("ณ COUR:               ณ");
   gotoxy(58,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   gotoxy(33,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,14);cprintf("ณFILIER:              ณ");
   gotoxy(33,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


   gotoxy(58,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,14);cprintf("ณ DATE:   /    /      ณ");
   gotoxy(58,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


   gotoxy(33,17);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,18);cprintf("ณHORAIRE:  :   /  :   ณ");
   gotoxy(33,19);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");
   gotoxy(58,17);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,18);cprintf("ณ BLOC:               ณ");
   gotoxy(58,19);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


   gotoxy(33,20);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,21);cprintf("ณTYPE SALL:           ณ");
   gotoxy(33,22);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   gotoxy(58,20);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,21);cprintf("ณ NUM:                ณ");
   gotoxy(58,22);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(47,24);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(47,25);cprintf("ณ  SUBMIT(Entre)     ณ");
    gotoxy(47,26);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

        strcpy(newreservation.nom,enterChaine(39,10));
        strcpy(newreservation.noMCours,enterChaine(66,10));
        strcpy(newreservation.nomFiliere,enterChaine(44,14));

    newreservation.dateR=saisirDateValide(66,14);
    newreservation.heure=genererHeureValide(42,18);
    newreservation.salleTravaille.blocSalle=nomBloc(66,18);
    strcpy(newreservation.salleTravaille.typeSalles,saisirTypeSalle(45,21));
    newreservation.salleTravaille.numSalle=checkNumSalle(64,21);
    return newreservation;

}
void annulerReservationSalle(){
    int a=0;
          reservation1 reservationExistante,ReservationASupprimer;
        FILE *fichier = fopen("reservation.bin", "rb+");
    if(fichier==NULL){
        printf("Erreur d'ouverture fichies reservation.bin");
        exit(1);
    }else{
             FILE* temp=fopen("temp2.bin","ab+");
         if(temp==NULL){
            printf("Erreur d'ouverture de temp2.bin");

         }
       ReservationASupprimer=profReservation2();

      while(fread(&reservationExistante,sizeof(reservation1),1,fichier)==1){
       if(!(compareSalle(reservationExistante.salleTravaille, ReservationASupprimer.salleTravaille) &&compareDate(reservationExistante.dateR, ReservationASupprimer.dateR) &&compareHeure(reservationExistante.heure, ReservationASupprimer.heure))){
           fwrite(&reservationExistante,sizeof(reservation1),1,temp);

    }else a++;
   }
   fclose(fichier);
   fclose(temp);
   remove("reservation.bin");
   rename("temp2.bin","reservation.bin");
   if(a!=0){
            textbackground(11);
                   textcolor(15);gotoxy(10,33);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
                    textcolor(4);gotoxy(10,34);cprintf("ณRESERVATION ANUULER AVEC SUCCESณ");
                   textcolor(15);gotoxy(10,35);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");
               }
    else{
                    textbackground(11);
                    textcolor(15);gotoxy(10,33);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
                     textcolor(4);gotoxy(10,34);cprintf("ณRESERVATION N'EXIST PAS   ณ");
                    textcolor(15);gotoxy(10,35);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

               }
  }
}
char profReservation() {
    reservation1 newreservation;
    char rep;
        textbackground(4);

    textcolor(4);
    textcolor(15);gotoxy(30,5);cprintf("ษอออออออออออออออออออออออออออออออออออออออออออออออออออออป");
    textcolor(15);textcolor(12);gotoxy(30,6);cprintf("บ");textcolor(0);cprintf("                   RESERVATION  PROF                 ");textcolor(12); cprintf("บ");
    textcolor(15);gotoxy(30,7);cprintf("ฬอออออออออออออออออออออออออออออออออออออออออออออออออออออน");
   textcolor(15); gotoxy(30,8);cprintf("บ                                                     บ");
   textcolor(12); gotoxy(30,9);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,10);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,11);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,12);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,13);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,14);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,15);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,16);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,17);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,18);cprintf("บ                                                     บ");
   textcolor(12);gotoxy(30,19);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,20);cprintf("บ                                                     บ");
  textcolor(12); gotoxy(30,21);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,22);cprintf("บ                                                     บ");
  textcolor(12); gotoxy(30,23);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,24);cprintf("บ                                                     บ");
  textcolor(12); gotoxy(30,25);cprintf("บ                                                     บ");
   textcolor(15);gotoxy(30,26);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,27);cprintf("บ                                                     บ");
  textcolor(15); gotoxy(30,28);cprintf("ศอออออออออออออออออออออออออออออออออออออออออออออออออออออผ");


    gotoxy(33,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,10);cprintf("ณ NOM:                ณ");
   gotoxy(33,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


    gotoxy(58,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,10);cprintf("ณ COUR:               ณ");
   gotoxy(58,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   gotoxy(33,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,14);cprintf("ณFILIER:              ณ");
   gotoxy(33,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


   gotoxy(58,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,14);cprintf("ณ DATE:   /    /      ณ");
   gotoxy(58,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


   gotoxy(33,17);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,18);cprintf("ณHORAIRE:  :   /  :   ณ");
   gotoxy(33,19);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");
   gotoxy(58,17);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,18);cprintf("ณ BLOC:               ณ");
   gotoxy(58,19);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


   gotoxy(33,20);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(33,21);cprintf("ณTYPE SALL:           ณ");
   gotoxy(33,22);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   gotoxy(58,20);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(58,21);cprintf("ณ NUM:                ณ");
   gotoxy(58,22);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(47,24);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(47,25);cprintf("ณ  SUBMIT(Entre)     ณ");
    gotoxy(47,26);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

        strcpy(newreservation.nom,enterChaine(39,10));
        strcpy(newreservation.noMCours,enterChaine(66,10));
        strcpy(newreservation.nomFiliere,enterChaine(44,14));

    newreservation.dateR=saisirDateValide(66,14);
    newreservation.heure=genererHeureValide(42,18);
    newreservation.salleTravaille.blocSalle=nomBloc(66,18);
    strcpy(newreservation.salleTravaille.typeSalles,saisirTypeSalle(45,21));
    newreservation.salleTravaille.numSalle=checkNumSalle(64,21);
    reserverSalles(newreservation);
    rep=reponse(10,35);
    return rep;

}
void carre(int x,int y){
    textbackground(4);
    textcolor(15);gotoxy(x,y);cprintf("ษอออออออออออออออออออออป");
     textcolor(0);gotoxy(x,y+1);cprintf("บ                     บ");
     textcolor(15);gotoxy(x,y+2);cprintf("ศอออออออออออออออออออออผ");


  }
  void affSalle(){
      textbackground(4);

    textcolor(4);
    textcolor(15);gotoxy(30,2);cprintf("ษอออออออออออออออออออออออออออออออออออออออออออออออออออออป");
    textcolor(15);textcolor(12);gotoxy(30,3);cprintf("บ");textcolor(0);cprintf("                   AFFICHAGE SALLES                  ");textcolor(12); cprintf("บ");
    textcolor(15);gotoxy(30,4);cprintf("ศอออออออออออออออออออออออออออออออออออออออออออออออออออออผ");
    textcolor(15);gotoxy(21,6);cprintf("ษออออออออออออออออออออออออหออออออออออออออออออออออออหออออออออออออออออออออออออป");
   gotoxy(21,7); textcolor(0); cprintf("บ           TP           บ           TD           บ        COURS           บ");
textcolor(15);    gotoxy(21,8);cprintf("ศออออออออออออออออออออออออสออออออออออออออออออออออออสออออออออออออออออออออออออผ");

    }
void affichierlesSalles(){

    FILE* sallefichier;
    int i=0,j=0,k=0;
    int I=0,J=0,K=0;
        textbackground(0);

        clrscr();
    sallefichier=fopen("Salles.bin","rb+");
    if (sallefichier == NULL) {
        printf("Erreur d'ouverture du fichier des salles\n");
        exit(1);
    }else{

    salle Salle;
    char rep;
    do{
            textbackground(4);
       textcolor(15);gotoxy(45,1);cprintf("ษอออออออออออออออออออออป");
      textcolor(0);gotoxy(45,2);cprintf("บ   BLOC :            บ");
     textcolor(15);gotoxy(45,3);cprintf("ศอออออออออออออออออออออผ");
     rep=nomBloc(55,2);
    }while(rep!='A'&&rep!='B');
    clrscr();

          affSalle();

    if(rep=='A'){
        while(fread(&Salle,sizeof(salle),1,sallefichier)==1){
            if(Salle.blocSalle=='A'){
                    if(strcmp(Salle.typeSalles,"TP")==0){
                        i+=3;
                        I++;
                                   carre(22,6+i);
                         gotoxy(30,7+i);cprintf("%d",Salle.numSalle);
                         if(I>10)
                         break;

                    }
                    else if(strcmp(Salle.typeSalles,"TD")==0){
                        j+=3;
                        J++;;
                            textbackground(0);
                                   carre(48,j+6);
                         gotoxy(56,7+j);cprintf("%d",Salle.numSalle);
                         if(J>10)
                         break;
                            }
                   else if(strcmp(Salle.typeSalles,"cours")==0){

                        k+=3;
                        K++;;
                            textbackground(0);
                                   carre(73,k+6);
                         gotoxy(85,7+k);cprintf("%d",Salle.numSalle);
                         if(K>10)
                         break;

                   }


            }

        }
    }else if (rep=='B'){
        while(fread(&Salle,sizeof(salle),1,sallefichier)==1){
            if(Salle.blocSalle=='A'){
                    if(strcmp(Salle.typeSalles,"TP")==0){
                        i+=3;
                        I++;
                                   carre(22,6+i);
                         gotoxy(30,7+i);cprintf("%d",Salle.numSalle);
                         if(I>10)
                         break;

                    }
                    else if(strcmp(Salle.typeSalles,"TD")==0){
                        j+=3;
                        J++;;
                                   carre(48,j+6);
                         gotoxy(56,7+j);cprintf("%d",Salle.numSalle);
                         if(J>10)
                         break;
                            }
                   else if(strcmp(Salle.typeSalles,"cours")==0){

                        k+=3;
                        K++;;
                                   carre(73,k+6);
                         gotoxy(85,7+k);cprintf("%d",Salle.numSalle);
                         if(K>10)
                         break;

                   }


            }

        }
    fclose(sallefichier);
}
}
}
void  pageProf(){
      int choix ;
      char rep;
      int x,y;
     textbackground(4);
    textcolor(15);gotoxy(45,2);cprintf("ษอออออออออออออออออออออออออออป");
    textcolor(15);gotoxy(45,3);cprintf("บ                           บ");
    textcolor(12);gotoxy(30,4);cprintf("ษออออ");
                      textcolor(15);cprintf("อออออ");
                           textcolor(12);cprintf("อออออน");
                           textcolor(0);cprintf("     ESPACE PROFESSEUR     ");
                            textcolor(12)  ;            cprintf("ฬอออออ");
                textcolor(15);                                cprintf("อออออ");
               textcolor(12);                                      cprintf("อออออป");
    textcolor(15);gotoxy(30,5);cprintf("บ              บ                           บ               บ");
   textcolor(15); gotoxy(30,6);cprintf("บ              ศอออออออออออออออออออออออออออผ               บ");
    textcolor(12);gotoxy(30,7);cprintf("บ                                                          บ");
    textcolor(12);gotoxy(30,8);cprintf("บ                                                          บ");
    textcolor(15);gotoxy(30,9);cprintf("บ                                                          บ"),
   textcolor(15);gotoxy(30,10);cprintf("บ                                                          บ");
   textcolor(12);gotoxy(30,11);cprintf("บ                                                          บ");
   textcolor(12);gotoxy(30,12);cprintf("บ                                                          บ");
   textcolor(15);gotoxy(30,13);cprintf("บ                                                          บ"),
   textcolor(15);gotoxy(30,14);cprintf("บ                                                          บ");
   textcolor(12);gotoxy(30,15);cprintf("บ                                                          บ");
   textcolor(12);gotoxy(30,16);cprintf("บ                                                          บ");
   textcolor(15);gotoxy(30,17);cprintf("บ                                                          บ");
   textcolor(15);gotoxy(30,18);cprintf("บ                                                          บ");
   textcolor(12);gotoxy(30,19);cprintf("บ                                                          บ");
  textcolor(15); gotoxy(30,20);cprintf("บ                                                          บ");
   textcolor(12);gotoxy(30,21);cprintf("บ                                                          บ");
   textcolor(15);gotoxy(30,22);cprintf("ศออออ");
                      textcolor(12);cprintf("อออออ");
                            textcolor(15);cprintf("อออออ");
                                  textcolor(12);cprintf("อออออ");
                                         textcolor(15);cprintf("อออออ");
                                               textcolor(12);cprintf("อออออ");
                                                     textcolor(15);cprintf("อออออ");
                                                            textcolor(12);cprintf("อออออ");
                                                                  textcolor(15);cprintf("อออออ");
                                                                       textcolor(12);cprintf("อออออ");
                                                                            textcolor(15);cprintf("อออออ");
                                                                        textcolor(12);cprintf("ออออผ");

textcolor(15);
    gotoxy(35,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(35,10);cprintf("ณ    1:AFFICHER RESERVATION DES COURS             ณ");
   gotoxy(35,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(35,12);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(35,13);cprintf("ณ   2:AFFICHER les  SALLES                        ณ");
    gotoxy(35,14);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(35,15);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(35,16);cprintf("ณ   3: EFFECTUER UNE RESERVATION D'UNE SALLE      ณ");
    gotoxy(35,17);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   gotoxy(50,18);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(50,19);cprintf("ณ CHOIX :           ณ");
   gotoxy(50,20);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

      do{
        textcolor(15);
      gotoxy(60,19);cscanf("%d",&choix);
        if(choix<1||choix>3){
        textcolor(7) ;  gotoxy(60,19);cprintf("INVALID");
       getch();
       getch();
       gotoxy(60,19);cprintf("         ");
         }
        }while(choix<1||choix>3);
    switch (choix){
         case 1:
            textbackground(0);
             afficherChargement(100,37,26);
             clrscr();
         rep=afficher_reservation_salles(1);
      break;
         case 2:
            textbackground(0);
            afficherChargement(100,37,26);
             clrscr();
             textbackground(0);
           affichierlesSalles();
           x=wherex();
           y=wherey();
           gotoxy(x+67,y+1);
           cprintf("REVENIR AU MENU PROF :");
           fflush(stdin);
           cscanf("%c",&rep);
         break;

         case 3:
            textbackground(0);
            afficherChargement(100,37,26);
             clrscr();
         gotoxy(20,2);rep=profReservation();
         break;
  }
        textcolor(15);
        if(choix<1||choix>3){
        textcolor(7) ;  gotoxy(50,22);cprintf("INVALID");
       getch();
       getch();
       gotoxy(50,22);cprintf("         ");
         }

    if (rep == 'O' || rep == 'o') {
        textbackground(0);
        clrscr();
        pageProf();
    }

     }
 void pageIdentifient(){

  textbackground(4);
    textcolor(15);
    gotoxy(30,9);cprintf("ษอออออออออออออออออออออออออออออออออออออออออออออออป");
    textcolor(12);gotoxy(30,10);cprintf("บ");
    textcolor(0);cprintf("                    WELCOME                    ");
    textcolor(12);cprintf("บ");
    textcolor(15);gotoxy(30,11);cprintf("ฬอออออออออออออออออออออออออออออออออออออออออออออออน");
    textcolor(15);gotoxy(30,12);cprintf("บ                                               บ");
   textcolor(12);gotoxy(30,13);cprintf("บ                                               บ");
   textcolor(15);gotoxy(30,14);cprintf("บ                                               บ");
  textcolor(12); gotoxy(30,15);cprintf("บ                                               บ");
   textcolor(15);gotoxy(30,16);cprintf("บ                                               บ");
   textcolor(12);gotoxy(30,17);cprintf("บ                                               บ");
  textcolor(15); gotoxy(30,18);cprintf("ศอออออออออออออออออออออออออออออออออออออออออออออออผ");


   gotoxy(42,12);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(42,13);cprintf("ณ                        ณ");
   gotoxy(42,14);textcolor(12);cprintf("ณ");textcolor(15);cprintf(" IDENTIFIANT:           ");textcolor(12);cprintf("ณ");
   textcolor(15);gotoxy(42,15);cprintf("ณ                        ณ");
   gotoxy(42,16);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");
   gotoxy(50,30);
   }
salle ajouterCrierSalle(){
    salle newSalle;
     textbackground(4);
    textcolor(15);gotoxy(45,2);cprintf("ษอออออออออออออออออออออออออออป");
    textcolor(15);gotoxy(45,3);cprintf("บ                           บ");
    textcolor(12);gotoxy(30,4);cprintf("ษออออ");
                      textcolor(15);cprintf("อออออ");
                           textcolor(12);cprintf("อออออน");
                           textcolor(0);cprintf("       INFO DE SALLE       ");
                            textcolor(12)  ;            cprintf("ฬอออออ");
                textcolor(15);                                cprintf("ออออ");
               textcolor(12);                                      cprintf("ออออป");
    textcolor(15);gotoxy(30,5);cprintf("บ              บ                           บ             บ");
   textcolor(15); gotoxy(30,6);cprintf("บ              ศอออออออออออออออออออออออออออผ             บ");
    textcolor(12);gotoxy(30,7);cprintf("บ                                                        บ");
    textcolor(12);gotoxy(30,8);cprintf("บ                                                        บ");
    textcolor(15);gotoxy(30,9);cprintf("บ                                                        บ"),
   textcolor(15);gotoxy(30,10);cprintf("บ                                                        บ");
   textcolor(12);gotoxy(30,11);cprintf("บ                                                        บ");
   textcolor(12);gotoxy(30,12);cprintf("บ                                                        บ");
   textcolor(15);gotoxy(30,13);cprintf("บ                                                        บ"),
   textcolor(15);gotoxy(30,14);cprintf("บ                                                        บ");
   textcolor(12);gotoxy(30,15);cprintf("บ                                                        บ");
   textcolor(12);gotoxy(30,16);cprintf("บ                                                        บ");
   textcolor(15);gotoxy(30,17);cprintf("ศออออ");
                      textcolor(12);cprintf("อออออ");
                            textcolor(15);cprintf("อออออ");
                                  textcolor(12);cprintf("ออออ");
                                         textcolor(15);cprintf("อออออ");
                                               textcolor(12);cprintf("ออออ");
                                                     textcolor(15);cprintf("อออออ");
                                                            textcolor(12);cprintf("อออออ");
                                                                  textcolor(15);cprintf("อออออ");
                                                                       textcolor(12);cprintf("อออออ");
                                                                            textcolor(15);cprintf("อออออ");
                                                                        textcolor(12);cprintf("ออออผ");

textcolor(15);
    gotoxy(35,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(35,10);cprintf("ณ  BLOC :             ณ");
   gotoxy(35,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

     gotoxy(61,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(61,10);cprintf("ณ   NUM :            ณ");
    gotoxy(61,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(35,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(35,14);cprintf("ณ TYPE :             ณ");
    gotoxy(35,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   gotoxy(61,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(61,14);cprintf("ณ SUBNET (ENTRER)     ณ");
   gotoxy(61,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   newSalle.blocSalle=nomBloc(47,10);
   newSalle.numSalle=checkNumSalle1(73,10);
   strcpy(newSalle.typeSalles,saisirTypeSalle(45,14));
    textbackground(0);afficherChargement(100,37,20);
    return newSalle;

    }
salle ajouterCrierSalle1(){
    salle newSalle;
     textbackground(4);
    textcolor(15);gotoxy(45,2);cprintf("ษอออออออออออออออออออออออออออป");
    textcolor(15);gotoxy(45,3);cprintf("บ                           บ");
    textcolor(12);gotoxy(30,4);cprintf("ษออออ");
                      textcolor(15);cprintf("อออออ");
                           textcolor(12);cprintf("อออออน");
                           textcolor(0);cprintf("INFO DE SALLE A SUPPRIMER  ");
                            textcolor(12)  ;            cprintf("ฬอออออ");
                textcolor(15);                                cprintf("ออออ");
               textcolor(12);                                      cprintf("ออออป");
    textcolor(15);gotoxy(30,5);cprintf("บ              บ                           บ             บ");
   textcolor(15); gotoxy(30,6);cprintf("บ              ศอออออออออออออออออออออออออออผ             บ");
    textcolor(12);gotoxy(30,7);cprintf("บ                                                        บ");
    textcolor(12);gotoxy(30,8);cprintf("บ                                                        บ");
    textcolor(15);gotoxy(30,9);cprintf("บ                                                        บ"),
   textcolor(15);gotoxy(30,10);cprintf("บ                                                        บ");
   textcolor(12);gotoxy(30,11);cprintf("บ                                                        บ");
   textcolor(12);gotoxy(30,12);cprintf("บ                                                        บ");
   textcolor(15);gotoxy(30,13);cprintf("บ                                                        บ"),
   textcolor(15);gotoxy(30,14);cprintf("บ                                                        บ");
   textcolor(12);gotoxy(30,15);cprintf("บ                                                        บ");
   textcolor(12);gotoxy(30,16);cprintf("บ                                                        บ");
   textcolor(15);gotoxy(30,17);cprintf("ศออออ");
                      textcolor(12);cprintf("อออออ");
                            textcolor(15);cprintf("อออออ");
                                  textcolor(12);cprintf("ออออ");
                                         textcolor(15);cprintf("อออออ");
                                               textcolor(12);cprintf("ออออ");
                                                     textcolor(15);cprintf("อออออ");
                                                            textcolor(12);cprintf("อออออ");
                                                                  textcolor(15);cprintf("อออออ");
                                                                       textcolor(12);cprintf("อออออ");
                                                                            textcolor(15);cprintf("อออออ");
                                                                        textcolor(12);cprintf("ออออผ");

textcolor(15);
    gotoxy(35,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(35,10);cprintf("ณ  BLOC :             ณ");
   gotoxy(35,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

     gotoxy(61,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(61,10);cprintf("ณ   NUM :            ณ");
    gotoxy(61,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(35,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(35,14);cprintf("ณ TYPE :             ณ");
    gotoxy(35,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   gotoxy(61,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(61,14);cprintf("ณ SUBNET (ENTRER)     ณ");
   gotoxy(61,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   newSalle.blocSalle=nomBloc(47,10);
   newSalle.numSalle=checkNumSalle1(73,10);
   strcpy(newSalle.typeSalles,saisirTypeSalle(45,14));
    textbackground(0);afficherChargement(100,37,20);
    return newSalle;

    }
salle ajouterCrierSalle2(){
    salle newSalle;
     textbackground(4);
    textcolor(15);gotoxy(45,2);cprintf("ษอออออออออออออออออออออออออออป");
    textcolor(15);gotoxy(45,3);cprintf("บ                           บ");
    textcolor(12);gotoxy(30,4);cprintf("ษออออ");
                      textcolor(15);cprintf("อออออ");
                           textcolor(12);cprintf("อออออน");
                           textcolor(0);cprintf("  INFO DE SALLE A MODIFIER ");
                            textcolor(12)  ;            cprintf("ฬอออออ");
                textcolor(15);                                cprintf("ออออ");
               textcolor(12);                                      cprintf("ออออป");
    textcolor(15);gotoxy(30,5);cprintf("บ              บ                           บ             บ");
   textcolor(15); gotoxy(30,6);cprintf("บ              ศอออออออออออออออออออออออออออผ             บ");
    textcolor(12);gotoxy(30,7);cprintf("บ                                                        บ");
    textcolor(12);gotoxy(30,8);cprintf("บ                                                        บ");
    textcolor(15);gotoxy(30,9);cprintf("บ                                                        บ"),
   textcolor(15);gotoxy(30,10);cprintf("บ                                                        บ");
   textcolor(12);gotoxy(30,11);cprintf("บ                                                        บ");
   textcolor(12);gotoxy(30,12);cprintf("บ                                                        บ");
   textcolor(15);gotoxy(30,13);cprintf("บ                                                        บ"),
   textcolor(15);gotoxy(30,14);cprintf("บ                                                        บ");
   textcolor(12);gotoxy(30,15);cprintf("บ                                                        บ");
   textcolor(12);gotoxy(30,16);cprintf("บ                                                        บ");
   textcolor(15);gotoxy(30,17);cprintf("ศออออ");
                      textcolor(12);cprintf("อออออ");
                            textcolor(15);cprintf("อออออ");
                                  textcolor(12);cprintf("ออออ");
                                         textcolor(15);cprintf("อออออ");
                                               textcolor(12);cprintf("ออออ");
                                                     textcolor(15);cprintf("อออออ");
                                                            textcolor(12);cprintf("อออออ");
                                                                  textcolor(15);cprintf("อออออ");
                                                                       textcolor(12);cprintf("อออออ");
                                                                            textcolor(15);cprintf("อออออ");
                                                                        textcolor(12);cprintf("ออออผ");

textcolor(15);
    gotoxy(35,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(35,10);cprintf("ณ  BLOC :             ณ");
   gotoxy(35,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

     gotoxy(61,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(61,10);cprintf("ณ   NUM :            ณ");
    gotoxy(61,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(35,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(35,14);cprintf("ณ TYPE :             ณ");
    gotoxy(35,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   gotoxy(61,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(61,14);cprintf("ณ SUBNET (ENTRER)     ณ");
   gotoxy(61,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   newSalle.blocSalle=nomBloc(47,10);
   newSalle.numSalle=checkNumSalle1(73,10);
   strcpy(newSalle.typeSalles,saisirTypeSalle(45,14));
    textbackground(0);afficherChargement(100,37,20);
    return newSalle;

    }
salle ajouterCrierSalle3(){
    salle newSalle;
     textbackground(4);
    textcolor(15);gotoxy(45,2);cprintf("ษอออออออออออออออออออออออออออป");
    textcolor(15);gotoxy(45,3);cprintf("บ                           บ");
    textcolor(12);gotoxy(30,4);cprintf("ษออออ");
                      textcolor(15);cprintf("อออออ");
                           textcolor(12);cprintf("อออออน");
                           textcolor(0);cprintf("   NOUVEAU INFO DE SALLE   ");
                            textcolor(12)  ;            cprintf("ฬอออออ");
                textcolor(15);                                cprintf("ออออ");
               textcolor(12);                                      cprintf("ออออป");
    textcolor(15);gotoxy(30,5);cprintf("บ              บ                           บ             บ");
   textcolor(15); gotoxy(30,6);cprintf("บ              ศอออออออออออออออออออออออออออผ             บ");
    textcolor(12);gotoxy(30,7);cprintf("บ                                                        บ");
    textcolor(12);gotoxy(30,8);cprintf("บ                                                        บ");
    textcolor(15);gotoxy(30,9);cprintf("บ                                                        บ"),
   textcolor(15);gotoxy(30,10);cprintf("บ                                                        บ");
   textcolor(12);gotoxy(30,11);cprintf("บ                                                        บ");
   textcolor(12);gotoxy(30,12);cprintf("บ                                                        บ");
   textcolor(15);gotoxy(30,13);cprintf("บ                                                        บ"),
   textcolor(15);gotoxy(30,14);cprintf("บ                                                        บ");
   textcolor(12);gotoxy(30,15);cprintf("บ                                                        บ");
   textcolor(12);gotoxy(30,16);cprintf("บ                                                        บ");
   textcolor(15);gotoxy(30,17);cprintf("ศออออ");
                      textcolor(12);cprintf("อออออ");
                            textcolor(15);cprintf("อออออ");
                                  textcolor(12);cprintf("ออออ");
                                         textcolor(15);cprintf("อออออ");
                                               textcolor(12);cprintf("ออออ");
                                                     textcolor(15);cprintf("อออออ");
                                                            textcolor(12);cprintf("อออออ");
                                                                  textcolor(15);cprintf("อออออ");
                                                                       textcolor(12);cprintf("อออออ");
                                                                            textcolor(15);cprintf("อออออ");
                                                                        textcolor(12);cprintf("ออออผ");

textcolor(15);
    gotoxy(35,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(35,10);cprintf("ณ  BLOC :             ณ");
   gotoxy(35,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

     gotoxy(61,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(61,10);cprintf("ณ   NUM :            ณ");
    gotoxy(61,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(35,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(35,14);cprintf("ณ TYPE :             ณ");
    gotoxy(35,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   gotoxy(61,13);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
   gotoxy(61,14);cprintf("ณ SUBNET (ENTRER)     ณ");
   gotoxy(61,15);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

   newSalle.blocSalle=nomBloc(47,10);
   newSalle.numSalle=checkNumSalle1(73,10);
   strcpy(newSalle.typeSalles,saisirTypeSalle(45,14));
    textbackground(0);afficherChargement(100,37,20);
    return newSalle;

    }
void ajouter() {
    int a = 0;
    salle sallexiste;
    salle nouvelleSalle;
    char rep;
    FILE *fichier = fopen("Salles.bin", "ab+");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier");
        exit(1);
    } else {
        do {
            clrscr();
            a = 0;
            rewind(fichier);
            nouvelleSalle = ajouterCrierSalle();

            while (fread(&sallexiste, sizeof(salle), 1, fichier) == 1) {
                if (compareSalle(nouvelleSalle, sallexiste) == 1) {
                    a = 1;
                }
            }

            if (a == 0) {
                fwrite(&nouvelleSalle, sizeof(salle), 1, fichier);
                gotoxy(35, 28);
                textbackground(11);
                   textcolor(15);gotoxy(30,21);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
                    textcolor(4);gotoxy(30,22);cprintf("ณSalle ajoutee avec succesณ");
                   textcolor(15);gotoxy(30,23);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");
            } else {
                                textbackground(11);

                   textcolor(15);gotoxy(30,21);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
                    textcolor(4);gotoxy(30,22);cprintf("ณCette salle existe deja  ณ");
                   textcolor(15);gotoxy(30,23);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");
            }
                            textbackground(11);

                    textcolor(15);gotoxy(60,21);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
                     textcolor(4);gotoxy(60,22);cprintf("ณAJOUTER UNE AUTRE FOIX:  ณ");
                    textcolor(15);gotoxy(60,23);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

             fflush(stdin);
             gotoxy(85,22);
             cscanf("%c",&rep);
             textbackground(0);
             if(rep=='o'||rep=='O'){
              afficherChargement(100, 37, 25);

             }
             else{
                    gotoxy(2,29);
                getch();
             }

        } while (rep=='o'||rep=='O');

        fclose(fichier);

    }
}
void suprimerSalle(){
        salle salleCourante, salleASupprimer;
        int salleTrouvee = 0;

    char rep;
    do {

    FILE *fichier = fopen("Salles.bin", "rb+");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier");
        exit(1);
    }
    else{
        FILE *tempFichier = fopen("temp.bin", "wb");
        if (tempFichier == NULL) {
            printf("Erreur lors de la creation du fichier temporaire");
            exit(1);
        }
    else {
             clrscr();
            salleASupprimer=ajouterCrierSalle1();
               salleTrouvee=0;

            while (fread(&salleCourante, sizeof(salle), 1, fichier) == 1) {
            if (!compareSalle(salleCourante, salleASupprimer)) {
                fwrite(&salleCourante, sizeof(salle), 1, tempFichier);
            } else {
                salleTrouvee = 1;
            }
            }
        fclose(fichier);
        fclose(tempFichier);
            if (salleTrouvee) {
            remove("Salles.bin");
            rename("temp.bin", "Salles.bin");
            textbackground(11);
                   textcolor(15);gotoxy(30,21);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
                    textcolor(4);gotoxy(30,22);cprintf("ณSalle suprimer avec succes ณ");
                   textcolor(15);gotoxy(30,23);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");
               }
               else{
                    textbackground(11);
                    textcolor(15);gotoxy(30,21);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
                     textcolor(4);gotoxy(30,22);cprintf("ณCette salle n'existe pas  ณ");
                    textcolor(15);gotoxy(30,23);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

               }
                    textbackground(11);
                    textcolor(15);gotoxy(60,21);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
                     textcolor(4);gotoxy(60,22);cprintf("ณSUPPRIMER UNE AUTRE FOIX:   ณ");
                    textcolor(15);gotoxy(60,23);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

             fflush(stdin);
             gotoxy(88,22);
             cscanf("%c",&rep);
             textbackground(0);
             if(rep=='o'||rep=='O'){
              afficherChargement(100, 37, 25);

             }
             else{
                gotoxy(2,29);
                  getch();
             }

        }
    }
         textbackground(0);
        } while (rep=='o'||rep=='O');
}
void modifierSalle(){

salle salleCourante, salleAModifier;
    int salleTrouvee = 0;

    char rep;
    do {

    FILE *fichier = fopen("Salles.bin", "rb+");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier");
        exit(1);
    }
    else {
             clrscr();
            salleAModifier=ajouterCrierSalle2();
            salleTrouvee = 0;
            while (fread(&salleCourante, sizeof(salle), 1, fichier) == 1) {
                if (compareSalle(salleAModifier, salleCourante) == 1) {
                    salleTrouvee = 1;
                    fseek(fichier, -sizeof(salle), SEEK_CUR);
                     salleCourante=ajouterCrierSalle3();
                fwrite(&salleCourante, sizeof(salle), 1, fichier);
                 textbackground(11);
                   textcolor(15);gotoxy(30,21);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
                    textcolor(4);gotoxy(30,22);cprintf("ณSalle Modifier avec succes ณ");
                   textcolor(15);gotoxy(30,23);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");
                                   break;

               }
                }
            }
        fclose(fichier);
            if (salleTrouvee==0) {
                    textbackground(11);
                    textcolor(15);gotoxy(30,21);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
                     textcolor(4);gotoxy(30,22);cprintf("ณCette salle n'existe pas  ณ");
                    textcolor(15);gotoxy(30,23);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

               }

                    textbackground(11);
                    textcolor(15);gotoxy(60,21);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
                     textcolor(4);gotoxy(60,22);cprintf("ณMODIIFIER UNE AUTRE FOIS:   ณ");
                    textcolor(15);gotoxy(60,23);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

             fflush(stdin);
             gotoxy(88,22);
             cscanf("%c",&rep);
             textbackground(0);
             if(rep=='o'||rep=='O'){
              afficherChargement(100, 37, 25);

             }
             else{
                gotoxy(2,29);
                  getch();
             }



         textbackground(0);
        } while (rep=='o'||rep=='O');
}

void pageAdmin(){
    int x, y;
  int choix ;

      char rep;
        do{
                clrscr();
          textbackground(4);

    textcolor(15);gotoxy(50,2);cprintf("ษอออออออออออออออออออออออออออป");
    textcolor(15);gotoxy(50,3);cprintf("บ                           บ");
    textcolor(12);gotoxy(27,4);cprintf("ษอออออ");
                      textcolor(15);cprintf("ออออออ");
                                            textcolor(12);cprintf("ออออออ");

                           textcolor(15);cprintf("อออออน");
                           textcolor(0);cprintf("   ESPACE ADMINISTRATION   ");
                            textcolor(15)  ;            cprintf("ฬอออออ");
                textcolor(12);                                cprintf("ออออออ");
                                textcolor(15);                                cprintf("อออออ");

               textcolor(12);                                      cprintf("อออออป");
    textcolor(15);gotoxy(27,5);cprintf("บ                      บ                           บ                     บ");
   textcolor(15); gotoxy(27,6);cprintf("บ                      ศอออออออออออออออออออออออออออผ                     บ");
    textcolor(12);gotoxy(27,7);cprintf("บ                                                                        บ");
    textcolor(12);gotoxy(27,8);cprintf("บ                                                                        บ");
    textcolor(15);gotoxy(27,9);cprintf("บ                                                                        บ"),
   textcolor(15);gotoxy(27,10);cprintf("บ                                                                        บ");
   textcolor(12);gotoxy(27,11);cprintf("บ                                                                        บ");
   textcolor(12);gotoxy(27,12);cprintf("บ                                                                        บ");
   textcolor(15);gotoxy(27,13);cprintf("บ                                                                        บ"),
   textcolor(15);gotoxy(27,14);cprintf("บ                                                                        บ");
   textcolor(12);gotoxy(27,15);cprintf("บ                                                                        บ");
   textcolor(12);gotoxy(27,16);cprintf("บ                                                                        บ");
   textcolor(15);gotoxy(27,17);cprintf("บ                                                                        บ");
   textcolor(15);gotoxy(27,18);cprintf("บ                                                                        บ");
   textcolor(12);gotoxy(27,19);cprintf("บ                                                                        บ");
  textcolor(12); gotoxy(27,20);cprintf("บ                                                                        บ");
   textcolor(15);gotoxy(27,21);cprintf("บ                                                                        บ");
   textcolor(15);gotoxy(27,22);cprintf("บ                                                                        บ");
   textcolor(15);gotoxy(27,23);cprintf("บ                                                                        บ");
   textcolor(15);gotoxy(27,24);cprintf("บ                                                                        บ");

   gotoxy(27,25);
                               cprintf("ศออออ");
                      textcolor(12);cprintf("อออออ");
                            textcolor(15);cprintf("อออออ");
                                  textcolor(12);cprintf("อออออ");
                                         textcolor(15);cprintf("อออออ");
                                               textcolor(12);cprintf("อออออ");
                                                     textcolor(15);cprintf("อออออ");
                                                            textcolor(12);cprintf("อออออ");
                                                                  textcolor(15);cprintf("อออออ");
                                                                       textcolor(12);cprintf("อออออ");
                                                                             textcolor(15);cprintf("อออออ");
                                                                                  textcolor(12);cprintf("อออออ");
                                                                                                                                                                    textcolor(12);cprintf("อออออ");
                                                                                  textcolor(15);cprintf("ออออ");

                                                                                        textcolor(12);cprintf("ออออผ");

textcolor(15);
     gotoxy(32,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(32,10);cprintf("ณ1- AFFICHIER SALLES DISPONIBLE ณ");
    gotoxy(32,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

     gotoxy(65,9);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(65,10);cprintf("ณ2-  AJOUTER  NOUVEAU SALLE     ณ");
    gotoxy(65,11);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(32,12);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(32,13);cprintf("ณ3-     SUPPRIMER  SALLE        ณ");
    gotoxy(32,14);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(65,12);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(65,13);cprintf("ณ4-     MODIFIER SALLE          ณ");
    gotoxy(65,14);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(32,15);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(32,16);cprintf("ณ5-   ACCEDER AU MENU PROF      ณ");
    gotoxy(32,17);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(65,15);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(65,16);cprintf("ณ6-  ACCEDER AU MENU ETUDIANT   ณ");
    gotoxy(65,17);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(32,18);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(32,19);cprintf("ณ7- ANNULER RESERVATION ETUDIANTณ");
    gotoxy(32,20);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(65,18);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(65,19);cprintf("ณ8-  ANNULER RESERVATION PROF   ณ");
    gotoxy(65,20);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");

    gotoxy(52,21);cprintf("ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฟ");
    gotoxy(52,22);cprintf("ณ   CHOIX:           ณ");
    gotoxy(52,23);cprintf("ภฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤู");


      do{
        textcolor(15);
      gotoxy(64,22);cscanf("%d",&choix);
        if(choix<1||choix>8){
        textcolor(7) ;  gotoxy(64 ,22);cprintf("INVALID");
       getch();
       getch();
       gotoxy(64,22);cprintf("        ");
         }
        }while(choix<1||choix>8);
    switch (choix) {
                    case 1:
                           affichierlesSalles();
                        break;
                    case 2:
                        textbackground(0);
                        afficherChargement(100,34,27);
                          ajouter();
                        break;
                    case 3:
                        textbackground(0);
                        afficherChargement(100,34,27);
                        clrscr();
                        suprimerSalle();
                        break;
                    case 4:
                         textbackground(0);
                        afficherChargement(100,34,27);
                        clrscr();

                        modifierSalle();
                        break;
                    case 5:
                          textbackground(0);
                        afficherChargement(100,34,30);
                        clrscr();

                        pageProf();
                        break;
                    case 6:
                         textbackground(0);
                        afficherChargement(100,34,27);
                        clrscr();

                        pageEtudiant();
                        break;
                    case 7:
                        textbackground(0);
                            clrscr();

                       annulerReservationClub();
                    case 8 :
                        textbackground(0);
                        clrscr();
                        annulerReservationSalle();
                }
                 x=wherex();
                y=wherey();
                fflush(stdin);
                rep=reponse2(x,y);
              textbackground(0);

      }while(rep =='o'||rep=='O');



     }

void menuIdentifiant(){
    char *id;
    pageIdentifient();
    id=identifiantUser(52,14);
    if(strcmp(id,"admin")==0){
          clrscr();
    textbackground(0);
        pageAdmin();
    }
      else if(strcmp(id,"prof")==0){
             textbackground(0);

          clrscr();
        pageProf();
    }
      else if(strcmp(id,"etud")==0){
                textbackground(0);

          clrscr();
        pageEtudiant();
    }

  }
int main()
{


     page();

    return 0;
}
