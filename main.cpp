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
  int num;
  srand(time(NULL));
  Student** arr = new Student*[100];
  bool running = true;
  while (running == true) {
    char input[7];
    cout <<  "Enter ADD, PRINT, DELETE, GEN or QUIT:" << endl;
    cin.get(input, 7);
    cin.ignore();
    //ADD
    if (strcmp(input, "ADD") == 0) {
      char input2[9];
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
	cout << "Rehashing... " << endl;
	//Double the size of hash table
	size = size * 2;
	//Create temp array
	Student** temp = new Student*[size];
	for (int i = 0; i < size/2; i++) {
	  temp[i] = arr[i];
	}
	//Resize arr and clear it
	arr = new Student*[size];
	for (int i = 0; i < size; i++) {
	  arr[i] = NULL;
	}
	//Re-add students to new list
	for (int i = 0; i < size; i++) {
	  if (temp[i] != NULL) {
	    Student* newTemp = temp[i];
	    //If newTemp->next isnt NULL
	    if (newTemp->next != NULL) {
	      Student* tempNext = newTemp->next;
	      //If newTemp->next->next isnt NULL
	      if (tempNext->next != NULL) {
		Student* tempNextNext = tempNext->next;
		tempNextNext->next = NULL;
		tempNextNext->prev = NULL;
		addStudent(arr, tempNextNext, size);
	      }
	      tempNext->next = NULL;
	      tempNext->prev = NULL;
	    }
	    addStudent(arr, newTemp, size);
	  }	     
	}
      } 
    //Add all fields to hash function
    addStudent(arr, newStudent, size);
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
    //GENERATE
    else if (strcmp(input, "GEN") == 0) {
      cout << "Enter number of students to generate: " << endl;
      cin >> num;
      cin.ignore();
      generateStudent(num);
      
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
      (arr[code]->next->next)->prev = arr[code]->next->next;
    }
  }
}

//Check for collisions
bool checkCollision(Student **arr, Student* newStudent, int size) {
  //Get code
  int code = newStudent->id % size;
  //If that index already has three chains
  if (arr[code] != NULL && arr[code]->next != NULL) {
    if (arr[code]->next->next != NULL) {
      return true;
    }
    else {
      return false;
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
	  cout << "First name: " << arr[i]->next->next->fname << endl;
	  cout << "Last name: " << arr[i]->next->next->lname << endl;
	  cout << "ID: " << arr[i]->next->next->id << endl;
	  cout << "GPA: " << arr[i]->next->next->gpa << endl;
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
