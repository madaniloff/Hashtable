//This program implements a student list and stores the students in a hash table. Also includes a random student generator
//Author: Mark Daniloff
//Date: 6/5/2020

#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctype.h>
#include <cctype>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <iomanip>
#include <fstream>
#include <ctime>

using namespace std;

//Struct for student
struct Student {
  char fname[30];
  char lname[30];
  int id;
  float gpa;
  Student *next;
  Student *prev;
};

//Initialize functions
void addStudent(Student **arr, Student* newStudent, int size);
void generateStudent(int num);
void printStudent(Student **arr, int size);

int main() {
  int size = 100;
  srand(time(NULL));
  Student** arr = new Student*[100];
  bool running = true;
  while (running == true) {
    char input[7];
    cout <<  "Enter ADD, PRINT, DELETE  or QUIT:" << endl;
    cin.get(input, 7);
    cin.ignore();
    //ADD
    if (strcmp(input, "ADD") == 0) {
      char input2[9];
      cout << "Enter ADD or GENERATE: " << endl;
      cin.get(input2, 9);
      cin.ignore();
      //MANUAL ADD
      if (strcmp(input2, "ADD") == 0) {
	Student* newStudent = new Student();
	newStudent->prev = NULL;
	newStudent->next = NULL;
	//Prompt user to enter first name, last name, id, and gpa
	cout << "First name: " << endl;
	cin >> newStudent->fname;
	cin.ignore();
	cout << "Last name: " << endl;
	cin >> newStudent->lname;
	cin.ignore();
	cout << "ID: " << endl;
	cin >> newStudent->id;
	cin.ignore();
	cout << "GPA: " << endl;
	cin >> newStudent->gpa;
	cin.ignore();
	//Add all fields to hash function
	addStudent(arr, newStudent, size);
      }
      //GENERATE
      else if (strcmp(input2, "GENERATE") == 0) {
	int num;
	//Ask user how many students they want to generate
	cout << "Enter amount of students to generate: " << endl;
	cin >> num;
	cin.ignore();
	generateStudent(num);
      }
    }
    //PRINT
    else if (strcmp(input, "PRINT") == 0) {
      printStudent(arr, size);
    }
    //DELETE
    else if (strcmp(input, "DELETE") == 0) {
      
    }
    //QUIT
    else if (strcmp(input, "QUIT") == 0) {
      running = false;
    }
  }
}

//Generators or manually creates student
void addStudent(Student **arr, Student* newStudent, int size) {
  //Create code
  int code = newStudent->id % size;
  //If there is no collision
  if (arr[code] == NULL) {
    arr[code] = newStudent;
  }
  //If there is a collision
  else {
    //If the next is NULL
    if (arr[code]->next == NULL) {
      arr[code]->next = newStudent;
      (arr[code]->next)->prev = arr[code]->next;
    }
    else {
      while (arr[code]->next != NULL) {
	arr[code] = arr[code]->next;
	(arr[code]->next)->prev = arr[code]->next;
      }
    }
  }
}

//Generates students
void generateStudent(int num) {
  //Open first name and last name files


  //Generate random number between 0 and 20
  int randF = rand() % 21;
  int randL = rand() % 21;
  while (num > 0) {

    num--;
  }
}

//Print out the students
void printStudent(Student **arr, int size) {
  for (int i = 0; i < size; i++) {
    if (arr[i] != NULL) {
      cout << "First name: " << arr[i]->fname << endl;
      cout << "Last name: " << arr[i]->lname << endl;
      cout << "ID: " << arr[i]->id << endl;
      cout << "GPA: " << arr[i]->gpa << endl;
      cout << "-------------------------" << endl;
      //If there is a chain
      if (arr[i]->next != NULL) {
	while (arr[i]->next != NULL) {
	  cout << "First name: " << arr[i]->next->fname << endl;
	  cout << "Last name: " << arr[i]->next->lname << endl;
	  cout << "ID: " << arr[i]->next->id << endl;
	  cout << "GPA: " << arr[i]->next->gpa << endl;
	  cout << "-------------------------" << endl;
	  arr[i] = arr[i]->next;
	  (arr[i]->next)->prev = arr[i]->next;
	}
      }
    }
  }				  
}
