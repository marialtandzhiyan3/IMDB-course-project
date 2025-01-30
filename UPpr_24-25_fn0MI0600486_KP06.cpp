/**
*
* Solution to course project # 6
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Mari Altandzhiyan
* @idnumber 0MI0600486 - @compiler VCC
*
* <software like IMDb>
*
**/

#include <iostream>
#include <fstream>
#include<istream>

using namespace std;




size_t calculateSize(char* arr) {
    size_t count = 0;
    for (size_t i = 0; arr[i] != '\0'; ++i)
    {
        count++;
    }
    return count;
}

int my_strcmp(char str1[], char str2[]) {
    size_t i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

bool isContained(char* subStr, char* mainStr) {
    size_t mainLen = calculateSize(mainStr), subLen = calculateSize(subStr);

    // If substring is longer than main string, it can't be contained
    if (subLen > mainLen) return false;

    // Traverse the main string
    for (size_t i = 0; i <= mainLen - subLen; ++i)
    {
        size_t j = 0;

        // Check if substring matches starting from current position
        while (j < subLen && mainStr[i + j] == subStr[j])
        {
            j++;
        }

        if (j == subLen) return true;
    }

    return false;
}

bool ArraysAreEqual(char* arr1, char* arr2)
{
    size_t len1 = calculateSize(arr1), len2 = calculateSize(arr2);
    if (len1 != len2) return false;

    for (size_t i = 0; i < len1; ++i)
    {
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

    while ((c = cin.get()) != '\n')
    {
        if (size == capacity - 1)
        {
            // Double the capacity if the array is full
            capacity *= 2;
            char* temp = new char[capacity];
            for (size_t i = 0; i < size; ++i)
            {
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
char* ConcatTheSixMovieParams(char* arr1, char* arr2, char* arr3, char* arr4, char* arr5, char* arr6) {

    // Allocate memory for the concatenated string (+1 for null terminator +6 for the 6 delimiters)
    char* result = new char[calculateSize(arr1) + calculateSize(arr2) + calculateSize(arr3) + calculateSize(arr4) + calculateSize(arr5) + calculateSize(arr6) + 1 + 6];

    // Copy contents of each array into the result
    size_t currentIndex = 0;
    char* arrays[] = { arr1, arr2, arr3, arr4, arr5, arr6 };
    for (int i = 0; i < 6; ++i) {
        char* arr = arrays[i];
        while (*arr != '\0') {
            result[currentIndex++] = *arr++;
        }

        // Adding delimiter
        result[currentIndex++] = '|';
    }

    // Null-terminate the result
    result[currentIndex] = '\0';

    return result;
}

void AddNewMovie()
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

    char* movie = ConcatTheSixMovieParams(title, year, genre, producer, actors, rating);

    fstream myFyle;
    myFyle.open("IMDB.txt", ios::app);

    fstream ratingsFile;
    ratingsFile.open("ratings.txt", fstream::app);

    if (myFyle.is_open())
    {
        myFyle << movie << endl;
        myFyle.close();
    }
    else
    {
        cout << "Failed to open the file!" << endl;
        return;
    }

    if (ratingsFile.is_open())
    {

        ratingsFile << title << "," << "1" << "," << "5" << endl;
        ratingsFile.close();
    }
    else
    {
        cout << "Failed to open the file!" << endl;
        return;
    }

    // Free allocated memory
    delete[] title;
    delete[] year;
    delete[] genre;
    delete[] producer;
    delete[] actors;
    delete[] movie;

    if (!ratingsFile)
    {
        cout << "Failed to open the file!" << endl;
        return;
    }
}

char* CopyCharArray(char* source, char* destination, size_t num) {
    size_t i = 0;
    for (; i < num && source[i] != '\0'; ++i)
    {
        destination[i] = source[i];
    }
    destination[i] = '\0'; // Null-terminate the destination
    return destination;
}

char* ReadLine(std::ifstream& inputFile)
{
    const size_t initialBufferSize = 256; // Starting size of the buffer
    size_t bufferSize = initialBufferSize;
    char* buffer = new char[bufferSize]; // Dynamically allocate memory
    size_t length = 0;

    while (inputFile)
    {
        inputFile.getline(buffer + length, bufferSize - length); // Read into the remaining space
        length += calculateSize(buffer + length);

        if (inputFile.fail() && !inputFile.eof())
        {
            // Expand the buffer if it's not enough
            inputFile.clear(); // Clear fail state
            bufferSize *= 2;   // Double the buffer size
            char* newBuffer = new char[bufferSize];
            CopyCharArray(buffer, newBuffer, calculateSize(buffer));
            delete[] buffer; // Free the old buffer
            buffer = newBuffer;
        }
        else
        {
            break; // Successfully read the line or reached EOF
        }
    }

    // Null-terminate the line if not already done
    if (length >= bufferSize)
    {
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
// reused also for the ratings files where the elements are title, number of ratings, rating
char* GetMovieElement(char* line, char delimiter, int elementNumber)
{
    int currentElement = 0; // Tracks the current element number
    size_t start = 0;       // Start index for the current element
    size_t lineLength = calculateSize(line); // Length of the input line
    char* result = new char[100];

    for (size_t i = 0; i <= lineLength; ++i)
    {
        if (line[i] == delimiter || line[i] == '\0') { // Delimiter or end of string
            currentElement++;
            if (currentElement == elementNumber)
            {
                size_t length = i - start; // Length of the current element
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

    if (!inputFile)
    {
        cout << "Failed to open the file!" << endl;
        return;
    }

    // Read the file line by line
    while (inputFile)
    {
        char* line = ReadLine(inputFile);
        if (*line != '\0') { // Skip empty lines
            char* element = GetMovieElement(line, '|', elementNumber);
            if (isContained(elementToSearchFor, element))
            {
                cout << line << endl;
                moviesFound = true;
            }
        }
        delete[] line;
    }

    if (!moviesFound)
    {
        cout << "No such movies found." << endl;
    }

    inputFile.close();
}

void SearchMovieByTitle()
{
    SearchByElement(1);
}

void SearchMovieByGenre()
{
    SearchByElement(3);
}

void SeeAllTheMovies()
{
    ifstream inputFile;
    inputFile.open("IMDB.txt", fstream::in);
    char ch;

    if (!inputFile)
    {
        cout << "Failed to open the file!" << endl;
        return;
    }

    inputFile >> ch; // Try reading a character

    // If EOF is reached immediately, the file is empty
    if (inputFile.eof())
    {
        cout << "Empty movie DB!" << endl;
        return;
    }

    // Move the cursor back to the beginning
    inputFile.seekg(0);

    // Read the file line by line
    while (inputFile)
    {
        char* line = ReadLine(inputFile);
        cout << line << endl;
        delete[] line;
    }

    inputFile.close();
}

void ChangeMovie()
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
    while (inputFile)
    {
        char* line = ReadLine(inputFile);
        if (*line != '\0')
        { // Skip empty lines
            char* title = GetMovieElement(line, '|', 1);
            if (ArraysAreEqual(titleToChange, title))
            {
                cout << "Which element do you want to change?" << endl;
                cout << "1. Title" << endl;
                cout << "2. Year" << endl;
                cout << "3. Genre" << endl;
                cout << "4. Producer" << endl;
                cout << "5. Actors" << endl;

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
                default:
                    cout << "Invalid choice!" << endl;
                    delete[] newElement;
                    continue;
                }

                char* newMovie = ConcatTheSixMovieParams(title, year, genre, producer, actors, rating);
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

    // Delete the original file and rename the temporary ones
    remove("IMDB.txt");
    int codeWhenRenamingIMDBfile = rename("temp.txt", "IMDB.txt");
    if (codeWhenRenamingIMDBfile != 0)
    {
        cout << "An erros ocured while renaming the temp IMDB file. Error code: " << codeWhenRenamingIMDBfile << endl;
    }
}

void DeleteMovie()
{
    ifstream inputFile;
    inputFile.open("IMDB.txt", fstream::in);
    ofstream tempFile;
    tempFile.open("temp.txt", fstream::out);

    if (!inputFile)
    {
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
            if (ArraysAreEqual(titleToDelete, title))
            {
                cout << "Are you sure you want to delete this movie? (y/n): ";
                char confirmation;
                cin >> confirmation;
                if (confirmation == 'y' || confirmation == 'Y')
                {
                    movieFound = true;
                    // just skip writing the line to the temp file
                }
                else
                {
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

    // Delete the original file and rename the temporary ones
    remove("IMDB.txt");
    int codeWhenRenamingIMDBfile = rename("temp.txt", "IMDB.txt");
    if (codeWhenRenamingIMDBfile != 0)
    {
        cout << "An erros ocured while renaming the temp IMDB file. Error code: " << codeWhenRenamingIMDBfile << endl;
    }
}

void RateFilm()
{
    ifstream inputFile;
    inputFile.open("IMDB.txt", fstream::in);
    ifstream ratingsFile;
    ratingsFile.open("ratings.txt", fstream::in);
    ofstream tempRatingsFile;
    tempRatingsFile.open("temp_ratings.txt", fstream::out);
    ofstream tempFile;
    tempFile.open("temp.txt", fstream::out);

    if (!inputFile || !ratingsFile)
    {
        cout << "Failed to open the file!" << endl;
        return;
    }

    cout << "Enter the title of the film you want to rate: ";
    cin.ignore();
    char* titleToRate = ReadUserInput();
    bool movieFound = false;

    // Read the file line by line
    while (inputFile)
    {
        char* line = ReadLine(inputFile);
        if (*line != '\0')
        { // Skip empty lines
            char* title = GetMovieElement(line, '|', 1);
            if (ArraysAreEqual(titleToRate, title))
            {
                movieFound = true;
                cout << "Enter your rating (1-10): ";
                float rating;
                cin >> rating;
                if (rating < 1 || rating > 10)
                {
                    cout << "Invalid rating!" << endl;
                    delete[] line;
                    delete[] title;
                    continue;
                }

                // Update the ratings file
                bool ratingUpdated = false;
                while (ratingsFile)
                {
                    char* ratingLine = ReadLine(ratingsFile);
                    if (*ratingLine != '\0')
                    {
                        char* ratingTitle = GetMovieElement(ratingLine, ',', 1);
                        if (ArraysAreEqual(titleToRate, ratingTitle))
                        {
                            int numRatings = atoi(GetMovieElement(ratingLine, ',', 2)); // Convert number of ratings from char arr to int
                            float currentRating = atof(GetMovieElement(ratingLine, ',', 3)); // Convert current rating from char arr to float
                            float newRating = ((currentRating * numRatings) + rating) / (numRatings + 1);
                            tempRatingsFile << ratingTitle << "," << numRatings + 1 << "," << newRating << endl;
                            rating = newRating;
                            ratingUpdated = true;
                        }
                        else
                        {
                            tempRatingsFile << ratingLine << endl;
                        }
                        delete[] ratingTitle;
                    }
                    delete[] ratingLine;
                }

                // Update the main file
                char* year = GetMovieElement(line, '|', 2);
                char* genre = GetMovieElement(line, '|', 3);
                char* producer = GetMovieElement(line, '|', 4);
                char* actors = GetMovieElement(line, '|', 5);
                char ratingArr[10];
                snprintf(ratingArr, sizeof(ratingArr), "%.1f", rating); // Convert rating to char array
                char* newMovie = ConcatTheSixMovieParams(title, year, genre, producer, actors, ratingArr);
                tempFile << newMovie << endl;
                delete[] newMovie;
            }
            else
            {
                tempFile << line << endl;
            }
            delete[] title;
        }
        delete[] line;
    }

    if (!movieFound)
    {
        cout << "No such movie found." << endl;
    }

    inputFile.close();
    ratingsFile.close();
    tempFile.close();
    tempRatingsFile.close();

    // Delete the original files and rename the temporary ones
    remove("IMDB.txt");
    int codeWhenRenamingIMDBfile = rename("temp.txt", "IMDB.txt");
    if (codeWhenRenamingIMDBfile != 0)
    {
        cout << "An erros ocured while renaming the temp IMDB file. Error code: " << codeWhenRenamingIMDBfile << endl;
    }

    remove("ratings.txt");
    int codeWhenRenamingRatingsFile = rename("temp_ratings.txt", "ratings.txt");
    if (codeWhenRenamingRatingsFile != 0)
    {
        cout << "An erros ocured while renaming the temp IMDB file. Error code: " << codeWhenRenamingRatingsFile << endl;
    }

    delete[] titleToRate;
}

void  SortMoviesByRating()
{

    // Open the input file
    ifstream inputFile("IMDB.txt");
    if (!inputFile)
    {
        cout << "Failed to open the file!" << endl;
        return;
    }

    const int MAX_MOVIES = 1000; // Maximum number of movies to process
    char* movies[MAX_MOVIES];    // Array to store movie lines
    float ratings[MAX_MOVIES];   // Array to store movie ratings
    int count = 0;               // Counter for the number of movies

    // Read the file line by line
    while (inputFile && count < MAX_MOVIES)
    {
        char* line = ReadLine(inputFile);
        if (*line != '\0')
        { // Skip empty lines
            char* ratingStr = GetMovieElement(line, '|', 6); // Extract the rating
            float rating = atof(ratingStr); // Convert rating to float
            movies[count] = line; // Store the movie line
            ratings[count] = rating; // Store the rating
            count++;
        
            delete[] ratingStr; // Free the allocated memory for ratingStr
        }
        else
        {
            delete[] line; // Free the allocated memory for empty line
        }
    }

    inputFile.close(); // Close the input file

    // Bubble sort the movies based on ratings in descending order
    for (int i = 0; i < count - 1; ++i)
    {
        for (int j = 0; j < count - i - 1; ++j)
        {
            if (ratings[j] < ratings[j + 1])
            {
                swap(ratings[j], ratings[j + 1]); // Swap ratings
                swap(movies[j], movies[j + 1]); // Swap corresponding movie lines
            }
        }
    }

    // Print the sorted movies
    for (int i = 0; i < count; ++i)
    {
        cout << movies[i] << endl;
        delete[] movies[i]; // Free the allocated memory for each movie line
    }

}

void  SortMoviesByTitle()
{

    // Open the input file
    ifstream inputFile("IMDB.txt");
    if (!inputFile)
    {
        cout << "Failed to open the file!" << endl;
        return;
    }

    const int MAX_MOVIES = 1000; // Maximum number of movies to process
    char* movies[MAX_MOVIES];    // Array to store movie lines
    int count = 0;               // Counter for the number of movies

    // Read the file line by line
    while (inputFile && count < MAX_MOVIES)
    {
        char* line = ReadLine(inputFile);
        if (*line != '\0')
        { // Skip empty lines
            movies[count] = line; // Store the movie line
            count++;
        }
        else
        {
            delete[] line; // Free the allocated memory for empty line
        }
    }
    

    // Bubble sort the movies based on titles alphabetically
    for (int i = 0; i < count - 1; ++i)
    {
        for (int j = 0; j < count - i - 1; ++j)
        {
            char* title1 = GetMovieElement(movies[j], '|', 1);
            char* title2 = GetMovieElement(movies[j + 1], '|', 1);
            if (my_strcmp(title1, title2) > 0)
            {
                swap(movies[j], movies[j + 1]); // Swap corresponding movie lines
            }

           delete[] title1;
           delete[] title2;
        }
    }

    // Print the sorted movies
    for (int i = 0; i < count; ++i)
    {
        cout << movies[i] << endl;
        delete[] movies[i]; // Free the allocated memory for each movie line
    }

    inputFile.close(); // Close the input file
}

void FilterMoviesByRating()
{
    ifstream inputFile;
    inputFile.open("IMDB.txt", fstream::in);

    cout << "Search for: ";
    cin.ignore();
    int elementToSearchFor;
    cin >> elementToSearchFor;
    bool moviesFound = false;

    if (!inputFile)
    {
        cout << "Failed to open the file!" << endl;
        return;
    }

    // Read the file line by line
    while (inputFile)
    {
        char* line = ReadLine(inputFile);
        if (*line != '\0')
        { // Skip empty lines
            char* ratingStr = GetMovieElement(line, '|', 6); // Extract the rating
            float rating = atof(ratingStr); // Convert rating to float
            if (elementToSearchFor <= rating)
            {
                cout << line << endl;
                moviesFound = true;
            }
        }
        delete[] line;
    }

    if (!moviesFound)
    {
        cout << "No such movies found." << endl;
    }

    inputFile.close();
}

void ExitProgram()
{
    exit(0);
}

void MenuForAdmin()
{
    int number; //number from the menu
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
        AddNewMovie();
        break;
    case 2:
        SearchMovieByTitle();
        break;
    case 3:
        SearchMovieByGenre();
        break;
    case 4:
        SeeAllTheMovies();
        break;
    case 5:
        ChangeMovie();
        break;
    case 6:
        DeleteMovie();
        break;
    case 7:
        SortMoviesByRating();
        break;
    case 8:
        SortMoviesByTitle();
        break;
    case 9:
        FilterMoviesByRating();
        break;
    case 10:
        ExitProgram();
        break;
    default:
        cout << "Incorect input";
        break;
    }
}

void MenuForUser()
{
    int number; //number from the menu
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
        SearchMovieByTitle();
        break;
    case 2:
        SearchMovieByGenre();
        break;
    case 3:
        SeeAllTheMovies();
        break;
    case 4:
        RateFilm();
        break;
    case 5:
        SortMoviesByRating();
        break;
    case 6:
        SortMoviesByTitle();
        break;
    case 7:
        FilterMoviesByRating();
        break;
    case 8:
        ExitProgram();
        break;
    default:
        cout << "Incorect input";
        break;
    }

}

int main()
{

    //admin or user
    cout << "What is your role:(admin or user) ";
    char* role = ReadUserInput();
    char admin[] = "admin";
    char user[] = "user";
    if (ArraysAreEqual(role, admin))
    {
        cout << "1. Add new movie" << endl;
        cout << "2. Search movie by title" << endl;
        cout << "3. Search movie by genre" << endl;
        cout << "4. See all movies" << endl;
        cout << "5. Change movie" << endl;
        cout << "6. Delete movie" << endl;
        cout << "7. Sort movies by rating" << endl;
        cout << "8. Sort movies by title" << endl;
        cout << "9. Filter movies by rating" << endl;
        cout << "10. Exit" << endl;

        MenuForAdmin();
    }
    else if (ArraysAreEqual(role, user))
    {
        cout << "1. Search movie by title" << endl;
        cout << "2. Search movie by genre" << endl;
        cout << "3. See all movies" << endl;
        cout << "4. Rate movie" << endl;
        cout << "5. Sort movies by rating" << endl;
        cout << "6. Sort movies by title" << endl;
        cout << "7. Filter movies by rating" << endl;
        cout << "8. Exit" << endl;

        MenuForUser();
    }
    else
    {
        cout << "Invalid input";
    }

    delete[] role;
    return 0;

}