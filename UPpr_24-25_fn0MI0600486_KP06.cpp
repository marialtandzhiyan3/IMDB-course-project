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


void ReadArray(char *arr)
{
    int i = 0;
    while (arr[i] != '\0')
    {
        cin >> arr[i];
        i++;
    }
}

int calculateSize(char* arr) {
    int count = 0;
    for (int i = 0; arr[i] != '\0'; ++i) {
        count++;
    }
    return count;
}

bool isContained(char* subStr, char* mainStr) {
    size_t mainLen = calculateSize(mainStr), subLen = calculateSize(subStr);

    // If substring is longer than main string, it can't be contained
    if (subLen > mainLen) return false;

    // Traverse the main string
    for (size_t i = 0; i <= mainLen - subLen; ++i) {
        size_t j = 0;

        // Check if substring matches starting from current position
        while (j < subLen && mainStr[i + j] == subStr[j]) {
            j++;
        }

        if (j == subLen) return true;
    }

    return false;
}

char* ReadUserInput()
{
    size_t capacity = 10;
    size_t size = 0;
    char* input = new char[capacity];
    char c;

    while ((c = cin.get()) != '\n') {
        if (size == capacity - 1) {
            // Double the capacity if the array is full
            capacity *= 2;
            char* temp = new char[capacity];
            for (size_t i = 0; i < size; ++i) {
                temp[i] = input[i];
            }
            delete[] input;
            input = temp;
        }
        input[size++] = c;
    }
    input[size] = '\0'; // Null-terminate the string
    return input;
}

// Function to concatenate six char arrays
char* ConcatCharArrays(char* arr1, char* arr2, char* arr3, char* arr4, char* arr5, char* arr6) {

    // Allocate memory for the concatenated string (+1 for null terminator +6 for the 6 delimiters)
    char* result = new char[calculateSize(arr1) + calculateSize(arr2) + calculateSize(arr3) + calculateSize(arr4) + calculateSize(arr5) + calculateSize(arr6) + 1 + 6];

    // Copy contents of each array into the result
    size_t currentIndex = 0;
    char* arrays[] = { arr1, arr2, arr3, arr4, arr5, arr6 };
    for (char* arr : arrays) {
        while (*arr != '\0') {
            result[currentIndex++] = *arr++;
           
        }

        //adding delimiter
        result[currentIndex++] = '|';
    }

    // Null-terminate the result
    result[currentIndex] = '\0';

    return result;
}

void AddNewFilm() 
{
    cin.ignore();
    cout << "Enter title:" << endl;
    char* title = ReadUserInput();
    cout << "Enter year:" << endl;
    char* year = ReadUserInput();
    cout << "Enter genre:" << endl;
    char* genre = ReadUserInput();
    cout << "Enter producer:" << endl;
    char* producer = ReadUserInput();
    cout << "Enter actors:" << endl;
    char* actors = ReadUserInput();
    //default rating
    char rating[] = "5";

    char* movie = ConcatCharArrays(title, year, genre, producer, actors, rating);
  
    fstream myFyle;
    myFyle.open("IMDB.txt", ios::app);//(write into txt) output from the program to the file
    if (myFyle.is_open())
    {
        myFyle << movie << endl;
        myFyle.close();
    }

    // Free allocated memory
    delete[] title;
    delete[] year;
    delete[] genre;
    delete[] producer;
    delete[] actors;
    delete[] movie;
}

 
void SearchFilmByTitle()
{
    
}

void SearchFilmByGenre()
{
    
}

void SeeAllTheFilms()
{

}

void ChangeFilm()
{

}

void DeleteFilm()
{

}

void RateFilm()
{

}

void  SortFilmsByRating()
{

}

void  SortFilmsByTitle()
{

}

void ExitProgram()
{
    
}

void MenuForAdmin() 
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
        SortFilmsByRating();
        break;
    case 8:
        SortFilmsByTitle();
        break;
    case 9: 
        ExitProgram();
        break;
    default:
        cout << "Incorect input";
        break;
    }
}
void MenuForUser() 
{
    int number;//number from the menu
    cout << "Which number from the menu do you want to chose? ";
    cin >> number;
   /* if (number < 1 && number>8)
    {
        cout << "Incorect input";
        return -1;
    }
   */
  
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
        SortFilmsByRating();
        break;
    case 6:
        SortFilmsByTitle();
        break;
    case 7: 
        ExitProgram();
        break;
    default:
        cout << "Incorect input";
        break;
    }
 
}


int main()
{
    char role; //admin or user
    cout << "What is your role: ";
    cin >> role;
    if (role=='a')
    {
        cout << "1. Add new film"<<endl;
        cout << "2. Search film by title" << endl;
        cout << "3. Search film by genre" << endl;
        cout << "4. See all films" << endl;
        cout << "5. Change film" << endl;
        cout << "6. Delete film"<<endl;
        cout << "7. Sort films by rating" << endl;
        cout << "8. Sort films by title" << endl;
        cout << "9. Exit" << endl;

        MenuForAdmin();
    }
    else if (role =='u')
    {
        cout << "1. Search film by title" << endl;
        cout << "2. Search film by genre" << endl;
        cout << "3. See all films" << endl;
        cout << "4. Rate film" << endl;
        cout << "5. Sort films by rating" << endl;
        cout << "6. Sort films by title" << endl;
        cout << "7. Exit" << endl;

        MenuForUser();
    }
    else
    {
        cout<<"Invalid input";
    }
}

