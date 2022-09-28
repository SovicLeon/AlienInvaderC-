#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
using namespace std;

void barva (int k) {
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
}

void gotoxy(int xpos, int ypos) {
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos;
    scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput,scrn);
}

void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void enemy(int x, int y) {
    barva(2);
    gotoxy(x,y);
    cout << char(0) << char(95) << char(0);
    gotoxy(x,y+1);
    cout << char(47) << char(0) << char(92);
    gotoxy(x,y+2);
    cout << char(219) << char(219) << char(219);
    gotoxy(x,y+3);
    cout << char(92) << char(95) << char(47);
    barva(15);
}

void enemyHit(int x, int y) {
    barva(12);
    gotoxy(x,y);
    cout << char(0) << char(95) << char(0);
    gotoxy(x,y+1);
    cout << char(47) << char(0) << char(92);
    gotoxy(x,y+2);
    cout << char(219) << char(219) << char(219);
    gotoxy(x,y+3);
    cout << char(92) << char(95) << char(47);
    barva(15);
}

void enemyBlank(int x, int y) {
    barva(2);
    gotoxy(x,y);
    cout << char(0) << char(0) << char(0);
    gotoxy(x,y+1);
    cout << char(0) << char(0) << char(0);
    gotoxy(x,y+2);
    cout << char(0) << char(0) << char(0);
    gotoxy(x,y+3);
    cout << char(0) << char(0) << char(0);
    barva(15);
}

void player(int x, int y) {
    barva(3);
    gotoxy(x,y);
    cout << char(47) << char(219) << char(92);
    gotoxy(x,y+1);
    cout << char(223) << char(223) << char(223);
    barva(15);
}

void playerBlank(int x, int y) {
    barva(15);
    gotoxy(x,y);
    cout << char(0) << char(0) << char(0);
    gotoxy(x,y+1);
    cout << char(0) << char(0) << char(0);
    barva(15);
}

void projectile(int x, int y){
    gotoxy(x,y);
    cout << char(186);
}

void projectileBlank(int x, int y){
    gotoxy(x,y);
    cout << char(0);
}

int randX(int maxX, int minX) {
    srand(time(0));
    int x;
    x = rand()%(maxX-minX+1)+minX;
    return x;
}

int main () {
    char tipka=0;
    ShowConsoleCursor(false);                   // skrije kurzor
    int hits = 0;
    double cas = 0.0;
    double stevec = 0;

    gotoxy(3,0);                                // pozicija in nastavitev statistik zgoraj in igralnega polja
    cout << "HITS: " << " TIME: " << cas;
    gotoxy(0,1);
    cout << char(201);
    gotoxy(1,1);
    for(int i=0; i<=52; i++) {
        cout << char(205);
    }
    cout << char(187);
    for(int i=2; i<=26; i++) {
        gotoxy(0,i);
        cout << char(186);
    }
    gotoxy(0,27);
    cout << char(200);
    for(int i=2; i<=26; i++) {
        gotoxy(54,i);
        cout << char(186);
    }
    gotoxy(54,27);
    cout << char(188);
    for(int i=1; i<=53; i++) {
        gotoxy(i,27);
        cout << char(205);
    }



    int direction = 1;                          // smer v katero gre in 1 je desno oz. poz. smer
    int pozicijaXE = randX(1,25);               // nastavi zacetno x pozicijo za nasprotnika
    enemy(pozicijaXE,3);                        // postavi nasprotnika na neko pozicijo

    gotoxy(5,28);
    cout << "PRESS ESC TO END GAME";

    int pozicijaXR;                             // pozicija projectile oz. rakete oz. rocket ker je ze XP zaseden
    int pozicijaYR;
    int projectileBool = false;

    int zacetniX=1;                             // zacetni x je tam ko spawnamo igralca
    int pozicijaXP=zacetniX;                    // pozicijaXP je pozicija igralca

    while(tipka!=27) {                          //dokler uporabnik ne pritisne esc se izvaja ta zanka
        player(pozicijaXP,25);

        if(kbhit()){                            // ce stisnem kako tipko vzame vnos ce ni vnosa pocaka 100ms, zbrise prejsni vnos pa loopa in caka vedno ce je vnos
            tipka = getch();
        } else {
            tipka = 0;
            Sleep(10);
            stevec+=10;
        }

        if(tipka==75&&pozicijaXP!=1) {          // ce je pritisnjena tipka puscica levo
            playerBlank(pozicijaXP,25);         // zbrise igralca in premakne pozicijo za 1 levo
            pozicijaXP--;
        } else if(tipka==77&&pozicijaXP!=50) {  // ce je pritisnjena tipka puscica desno
            playerBlank(pozicijaXP,25);         // zbrise igralca in premakne pozicijo za 1 desno
            pozicijaXP++;
        } else if(tipka==32&&projectileBool==false){        // projektil
            projectileBool = true;
            pozicijaXR = pozicijaXP+1;
            pozicijaYR = 24;
            projectile(pozicijaXR,pozicijaYR);
        } else if(tipka==0) {
            projectileBlank(pozicijaXR,pozicijaYR);         // prikaz in brisanje projektila
            if(pozicijaYR>2&&projectileBool==true){
                pozicijaYR--;
                projectile(pozicijaXR,pozicijaYR);
            } else if (pozicijaYR <=10) {
                projectileBool = false;
            }

            if((pozicijaXR>=pozicijaXE&&pozicijaXR<=pozicijaXE+3)&&(pozicijaYR>=3&&pozicijaYR<=6)){
                enemyBlank(pozicijaXE,3);
                enemyHit(pozicijaXE,3);
                projectileBlank(pozicijaXR,pozicijaYR);
                hits++;
                Sleep(150);
                stevec+=150;
                projectileBool = false;
                pozicijaXR = pozicijaXP;
                pozicijaYR = 25;
            }


            enemyBlank(pozicijaXE,3);           // premik nasprotnika pa brisanje
            if(pozicijaXE<50&&direction==1){
                pozicijaXE++;
            } else if(pozicijaXE>1&&direction==0){
                pozicijaXE--;
            } else if(direction==0) {
                direction=1;
            } else if(direction==1) {
                direction=0;
            }
            enemy(pozicijaXE,3);
        }

        cas = stevec/1000;
        gotoxy(3,0);                                // nastavitev statistik zgoraj
        cout << "HITS: " << hits << " TIME: " << cas;
    }
    cout << string(26,'\n');
    system("cls");
    cout << "\nYOU HAVE HIT THE ENEMY " << hits << " TIMES" << " IN " << cas << " SEC";   // END SCREEN
    cout << "\nYOU HAVE A HIT PER SECOND RATIO(OR SCORE) OF " << hits/cas << "\n\n";
}
