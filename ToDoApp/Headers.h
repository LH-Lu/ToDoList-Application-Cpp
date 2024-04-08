#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<exception>
#include<ios>
#include<limits>



class Tasks {

public:
	std::string TaskName;
	bool Priority = false;
	bool Done = false;

public:
	// Function performs the edit of task
	void TaskEditor();
};



// Function opens / creates / overwrites a file and read data from it or writes data to it
void ReadWriteFile(Tasks TaskArray[], int& idx, const std::string FileName, const char OpsType);
// Function prints the list of tasks
void PrintTasks(Tasks TaskArray[], int NumOfTasks);
// Function adds, deletes or edits tasks depending on OpsType
void DoTasks(Tasks TaskArray[], int& NumOfTasks, const int MaxTasks, char OpsType);
// Function adds new tasks to the memory
void AddTasks(Tasks TaskArray[], int& NumOfTasks, const int MaxTasks);
// Funciton edits tasks
void EditTasks(Tasks TaskArray[], int NumOfTasks);
// Function deletes tasks from the memory
void DeleteTasks(Tasks TaskArray[], int& NumOfTask);