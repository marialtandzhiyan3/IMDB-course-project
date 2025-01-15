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
#include<istream>
#include <cstring>

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
   
    ifstream inputFile("IMBD1.txt");
    inputFile.open("IMDB1.txt", fstream::in);

    //"Enter the title of the move you want to change"
    //TO DO: make the program to choose the element you want to change
    cout << "Enter the starting text to find: " << endl;
    cin.ignore();
    char* searchKey = ReadUserInput();
    cout << "Enter the new content for the line: " << endl;
    char* newContent = ReadUserInput();


    if (!inputFile) {
        cout << "Failed to open the file!" << endl;
        return;
    }


    char lines[100][100]; // Assume max 100 lines for simplicity
    int currentLine = 0;
    bool lineModified = false;

    // Read the file line by line into the array
    
    while (inputFile.getline(lines[currentLine], 100)) {
        // Check if the line starts with the search key
        if (!lineModified && std::strncmp(lines[currentLine], searchKey, std::strlen(searchKey)) == 0) {
            // Replace the line with the new content
            strncpy_s(lines[currentLine], newContent,100 - 1);
            lines[currentLine][100 - 1] = '\0'; // Ensure null-termination
            lineModified = true;
        }
        currentLine++;
    }
    inputFile.close();

    if (!lineModified) {
        cout << "Error: No line starting with '" << searchKey << "' was found.\n";
        return;
    }

    // Write the updated lines back to the file
    std::ofstream outputFile("IMDB1.txt");
    if (!outputFile) {
        cout << "Failed to open the file!" << endl;
        return;
    }

    for (int i = 0; i < currentLine; i++) {
        outputFile << lines[i] << '\n';
    }
    outputFile.close();
    cout << "The line starting with '" << searchKey << "' has been updated successfully.\n";
}

  

//TO DO:make with dynamic memory
void DeleteFilm(const char* searchKey)
{
    ifstream inputFile;
    inputFile.open("IMDB1.txt", fstream::in);

    if (!inputFile) {
       cout<< "Failed to open the file!" << endl;
        return;
    }

    char lines[100][100]; // Assume a maximum of 100 lines for simplicity
    int currentLine = 0;
    bool lineDeleted = false;

    // Read the file line by line into the array
    while (inputFile.getline(lines[currentLine], 100)) {
        // Check if the line starts with the search key
        if (!lineDeleted && std::strncmp(lines[currentLine], searchKey, std::strlen(searchKey)) == 0) {
            lineDeleted = true; // Mark that a line has been deleted
            continue; // Skip adding this line to the array
        }
        currentLine++;
    }
    inputFile.close();

    if (!lineDeleted) {
        cout << "Error: No line starting with '" << searchKey << "' was found.\n";
        return;
    }

    // Write the updated lines back to the file
    std::ofstream outputFile("IMDB1.txt");
    if (!outputFile) {
       cout << "Failed to open the file!" << endl;
        return;
    }

    for (int i = 0; i < currentLine; i++) {
        outputFile << lines[i] << '\n';
    }
    outputFile.close();
    std::cout << "The line starting with '" << searchKey << "' has been deleted successfully.\n";

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
        //DeleteFilm();
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
    /*
    char role; //admin or user
    cout << "What is your role:(a-administrator, u-user)";
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
  */


    char searchKey[100];

    std::cout << "Enter the starting text to delete: ";
    std::cin.getline(searchKey, 100);

   DeleteFilm(searchKey);

    /*
    //const char* filename = "IMBD1.txt";
    //int lineToChange = 2;
    //const char* newContent = "AAAAAAAAAA";
    char searchKey[100];
    char newContent[100];
    cout << "Enter the starting text to find: ";
    cin.getline(searchKey, 100);

    cout << "Enter the new content for the line: ";
    cin.getline(newContent, 100);

   

    ChangeFilm(searchKey, newContent);
      */
    return 0;

}

