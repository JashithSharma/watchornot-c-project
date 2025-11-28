Watch Or Not – Entertainment Recommendation System (C Project)
This repository contains my Mini Project for the C Programming course.
The project is a command-line entertainment recommendation system that interacts with the user through a character named Dr. Z, the librarian of the fictional Watch or Not library.
It recommends Movies or Series based on user choices and includes both Bollywood and Hollywood suggestions across 12 genres.
The project follows the repository structure required in the official PDF and includes the complete project report inside /docs.

## 1. Abstract

The purpose of this project is to design a simple, interactive C program that helps users decide what to watch.
The system takes user input (movie/series, mode, genre) and provides curated suggestions using structured data, conditional logic, string handling, and randomization.
The program includes a dynamic “typing effect” for a more engaging user experience and maintains separate Bollywood and Hollywood recommendations for each genre.
Random mode ensures unique suggestions without repeating titles until the list is exhausted.

## 2. Problem Definition

Many users struggle to decide what to watch when browsing through hundreds of movies and series.
The problem is to create a command-line tool that simplifies this decision-making process through:
User-friendly interaction
Fast recommendations
Options for both specific and random suggestions
Support for multiple genres
Easy extension for future content
The system must run in standard C, use basic concepts taught in class (arrays, loops, strings, structures, random numbers, functions), and avoid unnecessarily advanced features.

## 3. System Design
3.1 Algorithm Summary
Display welcome message and introduce Dr. Z.
Ask the user to choose between Movie or Series (3 attempts allowed).
Ask whether the user wants:
Random Mode → random unique suggestions
Specific Mode → choose a genre

If random mode:
Select random title from an array
Prevent repeated suggestions
Continue until user stops or list is exhausted

If specific mode:
Ask for a genre
Normalize input
Display Bollywood + Hollywood suggestions
Display Netflix secret genre codes
End with “Visit the library again soon.”

## 4. Implementation Details
The program is implemented in standard C and uses:
Structures (struct Item) to store movie/series information
Arrays to store Bollywood & Hollywood suggestions
String handling for input normalization
Functions for modularity (typing effect, random logic, genre mapping, etc.)
Random number generation (rand()) for random mode
Pointers to access selected suggestions
Conditional statements & loops for flow control
unistd.h for the typing animation delay using usleep()
Everything is written in a single file src/main.c as per academic project norms.

## 5. Testing & Results
Multiple test cases were used:
Case 1: User chooses Movie + Specific + Romance
Bollywood: Sita Ramam
Hollywood: Jerry Maguire
Correct Netflix codes displayed
Dr. Z personality lines appear correctly

Case 2: User chooses Series + Random
Unique titles are displayed one by one
When all titles are exhausted, the program ends with a message

Case 3: Invalid Inputs
Wrong “movie/series” attempts show humorous warnings
Third wrong input exits the program successfully

Case 4: Genre Normalization
Inputs like romantic, SciFi, sci correctly map to internal genres
All tests passed and produced the expected outputs.

## 6. Conclusion & Future Work

This project successfully demonstrates the use of core C programming concepts in a practical, interactive application.
The system is modular, extendable, and easy to maintain.
The humorous character (Dr. Z) adds personality, making the program more engaging.
