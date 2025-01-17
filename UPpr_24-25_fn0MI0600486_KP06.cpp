/** 
* 
* Solution to course project # 6
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
* 
* @author Mari Altandzhiyan
* @idnumber 0MI0600486 -  GCC èëè VC
* 
* <ïðåäíàçíà÷åíèå íà êîäà>
* 
**/

#include <iostream>
#include <fstream>
#include<istream>
//#include <cstring>

using namespace std;


size_t calculateSize(char* arr) {
    size_t count = 0;
    for (size_t i = 0; arr[i] != '\0'; ++i) {
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

bool ArraysÀreEqual(char* arr1, char* arr2) {
    size_t len1 = calculateSize(arr1), len2 = calculateSize(arr2);
    if (len1 != len2) return false;

    for (size_t i = 0; i < len1; ++i) {
        if (arr1[i] != arr2[i]) return false;
    }

    return true;
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

char* CopyCharArray(char* source, char* destination, size_t num) {
    size_t i = 0;
    for (; i < num && source[i] != '\0'; ++i) {
        destination[i] = source[i];
    }
    destination[i] = '\0'; // Null-terminate the destination
    return destination;
}

char* ReadLine(std::ifstream& inputFile) {
    const size_t initialBufferSize = 256; // Starting size of the buffer
    size_t bufferSize = initialBufferSize;
    char* buffer = new char[bufferSize]; // Dynamically allocate memory
    size_t length = 0;

    while (inputFile) {
        inputFile.getline(buffer + length, bufferSize - length); // Read into the remaining space
        length += strlen(buffer + length);

        if (inputFile.fail() && !inputFile.eof()) {
            // Expand the buffer if it's not enough
            inputFile.clear(); // Clear fail state
            bufferSize *= 2;   // Double the buffer size
            char* newBuffer = new char[bufferSize];
            //TO DO: write own strcpy 
            CopyCharArray(buffer, newBuffer, calculateSize(buffer));
            delete[] buffer; // Free the old buffer
            buffer = newBuffer;
        }
        else {
            break; // Successfully read the line or reached EOF
        }
    }

    // Null-terminate the line if not already done
    if (length >= bufferSize) {
        char* newBuffer = new char[length + 1];
        CopyCharArray(buffer, newBuffer, calculateSize(buffer));
        delete[] buffer;
        buffer = newBuffer;
    }
    buffer[length] = '\0';

    return buffer; // Return the dynamically allocated line
}

// Element: title, year, genre, producer, actors, rating
// corespondingly, their numbers are 1,2,3...
char* GetMovieElement(char* line, char delimiter, int elementNumber) {
    int currentElement = 0; // Tracks the current element number
    size_t start = 0;       // Start index for the current element
    size_t lineLength = strlen(line); // Length of the input line
    char* result = new char;

    for (size_t i = 0; i <= lineLength; ++i) {
        if (line[i] == delimiter || line[i] == '\0') { // Delimiter or end of string
            currentElement++;
            if (currentElement == elementNumber) {
                size_t length = i - start; // Length of the current element
                //strncpy(result, &line[start], length); // Copy the element to result
                return CopyCharArray(&line[start], result, length);
            }
            start = i + 1; // Move start to the next character after the delimiter
        }
    }

    // If elementNumber is out of range, return an empty string
    result[0] = '\0';
    return result;
}

// Element: title, year, genre, producer, actors, rating
// corespondingly, their numbers are 1,2,3...
void SearchByElement(int elementNumber)
{
    ifstream inputFile;
    inputFile.open("IMDB.txt", fstream::in);

    cout << "Search for: ";
    cin.ignore();
    char* elementToSearchFor = ReadUserInput();
    bool moviesFound = false;

    if (!inputFile) {
        cout << "Failed to open the file!" << endl;
        return;
    }

    // Read the file line by line
    while (inputFile) {
        char* line = ReadLine(inputFile);
        if (*line != '\0') { // Skip empty lines
            char* element = GetMovieElement(line, '|', elementNumber);
            if (isContained(elementToSearchFor, element))
            {
                cout << line << endl;
                moviesFound = true;
            }
            //delete[] title;
        }
        //delete[] title;
        delete[] line;
    }

    if (!moviesFound)
    {
        cout << "No such movies found." << endl;
    }

    inputFile.close();
}

void SearchFilmByTitle()
{
    SearchByElement(1);
}

void SearchFilmByGenre()
{
    SearchByElement(3);
}

void SeeAllTheFilms()
{
    ifstream inputFile;
    inputFile.open("IMDB.txt", fstream::in);
    char ch;

    if (!inputFile) {
        cout << "Failed to open the file!" << endl;
        return;
    }

    inputFile >> ch; // Try reading a character

    // If EOF is reached immediately, the file is empty
    if (inputFile.eof()) {
        cout << "Empty movie DB!" << endl;
        return;
    }

    // Move the cursor back to the beginning
    inputFile.seekg(0);

    // Read the file line by line
    while (inputFile) {
        char* line = ReadLine(inputFile);
        cout << line << endl;
        delete[] line;
    }

    inputFile.close();
}

void ChangeFilm()
{
    ifstream inputFile;
    inputFile.open("IMDB.txt", fstream::in);
    ofstream tempFile;
    tempFile.open("temp.txt", fstream::out);

    if (!inputFile) {
        cout << "Failed to open the file!" << endl;
        return;
    }

    cout << "Enter the title of the film you want to change: ";
    cin.ignore();
    char* titleToChange = ReadUserInput();
    bool movieFound = false;

    // Read the file line by line
    while (inputFile) {
        char* line = ReadLine(inputFile);
        if (*line != '\0') { // Skip empty lines
            char* title = GetMovieElement(line, '|', 1);
            if (ArraysÀreEqual(titleToChange, title))
            {
                cout << "Which element do you want to change?" << endl;
                cout << "1. Title" << endl;
                cout << "2. Year" << endl;
                cout << "3. Genre" << endl;
                cout << "4. Producer" << endl;
                cout << "5. Actors" << endl;
                cout << "6. Rating" << endl;
                int choice;
                cin >> choice;
                cin.ignore(); // Ignore the newline character

                char* newElement;
                cout << "Enter new value: ";
                newElement = ReadUserInput();

                char* year = GetMovieElement(line, '|', 2);
                char* genre = GetMovieElement(line, '|', 3);
                char* producer = GetMovieElement(line, '|', 4);
                char* actors = GetMovieElement(line, '|', 5);
                char* rating = GetMovieElement(line, '|', 6);

                switch (choice) {
                case 1:
                    title = newElement;
                    break;
                case 2:
                    year = newElement;
                    break;
                case 3:
                    genre = newElement;
                    break;
                case 4:
                    producer = newElement;
                    break;
                case 5:
                    actors = newElement;
                    break;
                case 6:
                    rating = newElement;
                    break;
                default:
                    cout << "Invalid choice!" << endl;
                    delete[] newElement;
                    continue;
                }

                char* newMovie = ConcatCharArrays(title, year, genre, producer, actors, rating);
                tempFile << newMovie << endl;
                delete[] newMovie;
                movieFound = true;
            }
            else
            {
                tempFile << line << endl;
            }
        }
        delete[] line;
    }

    if (!movieFound)
    {
        cout << "No such movie found." << endl;
    }

    inputFile.close();
    tempFile.close();

    // Delete the original file and rename the temporary one
    remove("IMDB.txt");
    rename("temp.txt", "IMDB.txt");

}

 
void DeleteFilm()
{
    
    ifstream inputFile;
    inputFile.open("IMDB.txt", fstream::in);
    ofstream tempFile;
    tempFile.open("temp.txt", fstream::out);

    if (!inputFile) {
        cout << "Failed to open the file!" << endl;
        return;
    }

    cout << "Enter the title of the film you want to delete: ";
    cin.ignore();
    char* titleToDelete = ReadUserInput();
    bool movieFound = false;

    // Read the file line by line
    while (inputFile) {
        char* line = ReadLine(inputFile);
        if (*line != '\0') { // Skip empty lines
            char* title = GetMovieElement(line, '|', 1);
            if (ArraysÀreEqual(titleToDelete, title)) {
                cout << "Are you sure you want to delete this movie? (y/n): ";
                char confirmation;
                cin >> confirmation;
                if (confirmation == 'y' || confirmation == 'Y') {
                    movieFound = true;
                }
                else {
                    tempFile << line << endl;
                }
            }
            else {
                tempFile << line << endl;
            }
        }
        delete[] line;
    }

    if (!movieFound) {
        cout << "No such movie found." << endl;
    }

    inputFile.close();
    tempFile.close();

    // Delete the original file and rename the temporary one
    remove("IMDB.txt");
    rename("temp.txt", "IMDB.txt");

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
    exit(0);
}

void MenuForAdmin() 
{
    int number;//number from the menu
    cout << "Which number from the menu dou you want to chose? ";
    cin >> number;

    if (number < 1 && number>8)
    {
        cout << "Incorect input";
        return;
    }

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

    if (number < 1 && number>8)
    {
        cout << "Incorect input";
        return;
    }
   
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
    
    char* role=new char; //admin or user
    cout << "What is your role:(administrator or user) ";
    ReadUserInput();
    char administrator[] = "administrator";
    char user[] = "user";
    if (ArraysÀreEqual(role, administrator ))
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
    else if (ArraysÀreEqual(user, role))
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
  


    delete[] role;
    return 0;

}

