/** 
* 
* Solution to course project # 6
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
* 
* @author Mari Altandzhiyan
* @idnumber 0MI0600486 -  GCC или VC
* 
* <предназначение на кода>
* 
**/

#include <iostream>
#include <fstream>
using namespace std;

void ReadArray(char *arr, int size)
{
    while (*arr != '\0')
    {
        cin.getline(arr, size);
        arr++;
    }
}

void AddNewFilm() //administratorska rolq, za obavqne na nov film, vseki film zapochva s ovenka 5
{
    char film;//dinamichna pamet!!
    const int size= 100;
    cout << "Write the title, year, genre, producer and actors:"<<endl;
    cin >> film;
    fstream myFyle;
    myFyle.open("IMDB.txt", ios::out);//(write into txt) output from the program to the file
    if (myFyle.is_open())
    {
        myFyle << film;
        myFyle.close();
    }
}

void SearchFilmByTitle()// za administrator i potrebiyel, za tyrsene na film po zaglavie
{
    

}
void SearchFilmByGenre()// za administrator i potrebitel , tyrsene sprqmo zhanr
{

}
void SeeAllTheFilms()// za administrator i potrebitel, da se wivdat wsichi filmi
{

}
void ChangeFilm()//za administrator, promqna na film
{

}
void DeleteFilm()//za administrator, iztrivane na film
{

}
int RateFilm()//za potrebitel, ocenka na film(1-10)
{
    return 0;
}
void SortAndFilterFilms()// za administrator i potrebitel, sortirane i filtrirane na filmi
{

}
void ExitProgram()//za administrator i potrebitel, izhod ot programata
{
   
}


void MenuForAdmin() // menu za wyzmovni izbori za administratotr
{
    int number;//number from the menu
    cout << "Which number from the menu dou you want to chose? ";
    cin >> number;
    switch (number)
    {
    case 1: 
        AddNewFilm();
        break;
    case 2: 
        SearchFilmByTitle();
        break;
    case 3:
        SearchFilmByGenre();
        break;
    case 4: 
        SeeAllTheFilms();
        break;
    case 5: 
        ChangeFilm();
        break;
    case 6: 
        DeleteFilm();
        break;
    case 7: 
        SortAndFilterFilms();
        break;
    case 8: 
        ExitProgram();
        break;
    default:
        cout << "Incorect input";
        break;
    }

    //proverka dali cifrata sushtestvuva v menuto
 //case???? za vsicki wyzmovni izbora   
}
void MenuForUser() // menu za wyzmovni izbori za potrebitel
{
    int number;//number from the menu
    cout << "Which number from the menu dou you want to chose? ";
    cin >> number;
    //proverka dali cifrata sushtestvuva v menuto
    switch (number)
    {
  
    case 1:
        SearchFilmByTitle();
        break;
    case 2:
        SearchFilmByGenre();
        break;
    case 3: 
        SeeAllTheFilms();
        break;
    case 4: 
        RateFilm();
        break;
    case 5:
        SortAndFilterFilms();
        break;
    case 6: 
        ExitProgram();
        break;
    default:
        cout << "Incorect input";
        break;
    }
  //case???? za vsicki wyzmovni izbora
}
//funkciq, da priema ii glawni i malki
// bukwi bez zna`nie, da ima edno i syshti znachenie

int main()
{
    char role; //admin or user
    cout << "What is your role: ";
    cin >> role;//izbor na potrebitel ili na administrator
    if (role=='a')
    {
        cout << "1. Add new film"<<endl;
        cout << "2. Search film by title" << endl;
        cout << "3. Search film by genre" << endl;
        cout << "4. See all films" << endl;
        cout << "5. Change film" << endl;
        cout << "6. Delete film"<<endl;
        cout << "7. Sort films by rating" << endl;
        cout << "8. Exit" << endl;

        MenuForAdmin();
    }
    else if (role =='u')
    {
        cout << "1. Search film by title" << endl;
        cout << "2. Search film by genre" << endl;
        cout << "3. See all films" << endl;
        cout << "4. Rate film" << endl;
        cout << "5. Sort films by rating" << endl;
        cout << "6. Exit" << endl;

        MenuForUser();
    }
    else
    {
        cout<<"Invalid input";
    }



}

