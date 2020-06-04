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
bool checkCollision(Student **arr, Student* newStudent, int size);
void generateStudent(int num);
void printStudent(Student **arr, int size);
void delStudent(Student **arr, int inid, int size);

int main() {
  int size = 100;
  int inid;
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
	//If there will be a collision with a chain of 3
	if (checkCollision(arr, newStudent, size) == true) {
	  //Double the size of hash table
	  size = size * 2;
	  //Create temp array
	  Student* temp = newStudent();
	  for (int i = 0; i < size/2; i++ ) {
	    temp[i] = list[i];
	  }
	  //Resize arr and clear it
	  temp = new Student*[size];
	   for (int i = 0; i < size; i++ ) {
	    list[i] = NULL;
	  }
	   //Readd students to new list
	   
	}
	
      
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
      cout << "Enter ID to delete" << endl;
      cin >> inid;
      cin.ignore();
      delStudent(arr, inid, size);
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
    //If next's next is NULL
    else if (arr[code]->next->next == NULL) {
      arr[code]->next->next = newStudent;
      (arr[code)->next->next)->prev = arr[code]->next->next;
    }
  }
}

//Check for collisions
bool checkCollision(Student **arr, Student* newStudent, int size) {
  //Get code
  int code = newStudent-> id % size;
  //If that index already has three chains
  if (arr[code]->next->next != NULL) {
    return true;
  }
  else {
    return false;
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
  cout << "-------------------------" << endl;
  for (int i = 0; i < size; i++) {
    if (arr[i] != NULL) {
      cout << "First name: " << arr[i]->fname << endl;
      cout << "Last name: " << arr[i]->lname << endl;
      cout << "ID: " << arr[i]->id << endl;
      cout << "GPA: " << arr[i]->gpa << endl;
      cout << "-------------------------" << endl;
      //If there is a chain
      if (arr[i]->next != NULL) {
	cout << "First name: " << arr[i]->next->fname << endl;
	cout << "Last name: " << arr[i]->next->lname << endl;
	cout << "ID: " << arr[i]->next->id << endl;
	cout << "GPA: " << arr[i]->next->gpa << endl;
	cout << "-------------------------" << endl;
	if (arr[i]->next->next != NULL) {
	  cout << "First name: " << arr[i]->next->fname << endl;
	  cout << "Last name: " << arr[i]->next->lname << endl;
	  cout << "ID: " << arr[i]->next->id << endl;
	  cout << "GPA: " << arr[i]->next->gpa << endl;
	  cout << "-------------------------" << endl;
	}
      }
    }
  }
}				  


//Delete a student
void delStudent(Student **arr, int inid, int size) {
  //Find index that the id is at
  int index = inid % size;
  //If student doesn't exist
  if (arr[index] == NULL) {
    cout << "This student does not exist!" << endl;
  }
  //If student exists and is the first node
  else if (arr[index] != NULL && arr[index]->id == inid) {
    //If there is no chaining
    if (arr[index]->next == NULL) {
      arr[index] = NULL;
    }
    //If there is
    else {
      //Replace the first one with the next one
      Student* temp = arr[index]->next;
      temp->prev = NULL;
      arr[index] = temp;
      
    }
  }
  //If there is chaining
  else {
    //If there is no next
    if (arr[index]->next == NULL) {
      cout << "This student does not exist! " << endl;
    }
    else {
      //If the second chain's id matches
      if (arr[index]->next->id == inid) {
	//If it's next is NULL
	if (arr[index]->next->next == NULL) {
	  
	}
      }
    }
  }
  

}
