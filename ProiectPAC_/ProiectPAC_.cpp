#include <iostream>

#include"../Server/Server.h"
#include"../Server/Server.cpp"
#include"../Server/LogIn.h"
#include"../Server/LogIn.cpp"
#include"../Server/Menu.h"
#include"../Server/Menu.cpp"



#include"../sqlite/sqlite3.h"
#include"Carte.h"


int main()
{
    Carte obj;
    obj.showInfo();
}


//Proiectul Database Project contine metoda de rulare a serverului
//pentru a rula serverul e nevoie sa instalati Putty
//main ul de aici acceseaza functia "function" din celalalt proiect,
//functie care ruleaza serverul

//video pentru a urmari cum a fost creat serverul si pentru a intelege codul de acolo:
//  https://www.youtube.com/watch?v=WDn-htpBlnU
// in descrierea videoclipului gasiti link si sa instalati Putty
// trebuie adaugate cele doua antete de sus in fiecare functie care va apela serverul
//pentru commit uri va recomand sa faceti niste afisari cu serverul