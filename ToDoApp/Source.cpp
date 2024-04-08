#include"Headers.h"

// Function opens / creates / overwrites a file and read data from it or writes data to it
void ReadWriteFile(Tasks TaskArray[], int& NumOfTasks, const std::string FileName, const char OpsType) {
	// Declarations
	std::fstream TheFile;
	char PriorityWriteChar, DoneWriteChar;
	int idx;

	// Step 1: Open file. If file does not exist, create a new file
	switch (OpsType) {
	case ('R'):
		TheFile.open(FileName, std::ios::out | std::ios::in | std::ios::app);
		break;

	case ('W'):
		TheFile.open(FileName, std::ios::in | std::ios::out | std::ios::trunc);
		break;
	}

	if (!TheFile.is_open()) {
		std::cout << "File unable to open! Stopping program!\n";
		throw 1;
		return;
	}

	// Step 2: Read data from file to TaskArray / Write data to file from TaskArray, depending on OpsType
	switch (OpsType) {
	case ('R'):
		while (std::getline(TheFile, TaskArray[NumOfTasks].TaskName)) {

			if (TaskArray[NumOfTasks].TaskName[0] == '*') {
				TaskArray[NumOfTasks].Priority = true;
			}
			else {
				TaskArray[NumOfTasks].Priority = false;
			}

			if (TaskArray[NumOfTasks].TaskName[1] == '*') {
				TaskArray[NumOfTasks].Done = true;
			}
			else {
				TaskArray[NumOfTasks].Done = false;
			}

			TaskArray[NumOfTasks].TaskName = TaskArray[NumOfTasks].TaskName.substr(2);

			NumOfTasks++;
		}
		break;

	case ('W'):
		for (idx = 0; idx < NumOfTasks; idx++) {

			if (TaskArray[idx].Priority == true) {
				PriorityWriteChar = '*';
			}
			else {
				PriorityWriteChar = ' ';
			}

			if (TaskArray[idx].Done == true) {
				DoneWriteChar = '*';
			}
			else {
				DoneWriteChar = ' ';
			}

			TheFile << PriorityWriteChar << DoneWriteChar << TaskArray[idx].TaskName << "\n";
		}
		break;
	}

	// Step 3: Close file.
	TheFile.close();
}


// Function prints the list of tasks
void PrintTasks(Tasks TaskArray[], int NumOfTasks) {
	// Declarations
	int idx;
	char PriorityPrintChar, DonePrintChar;

	std::cout << "TOTAL TASKS: " << NumOfTasks << std::endl;

	// Check if there are no tasks
	if (NumOfTasks == 0) {
		std::cout << "There are no tasks. Let's create some tasks :D" << std::endl;
		return;
	}
	
	for (idx = 0; idx < NumOfTasks; idx++) {

		if (TaskArray[idx].Priority == true) {
			PriorityPrintChar = 'P';
		}
		else {
			PriorityPrintChar = ' ';
		}

		if (TaskArray[idx].Done == true) {
			DonePrintChar = 'x';
		}
		else {
			DonePrintChar = ' ';
		}

		if ((idx + 1) < 10) {
			std::cout << "0" << (idx + 1) << "." << "[" << PriorityPrintChar << "]" << "[" << DonePrintChar << "] " << TaskArray[idx].TaskName << std::endl;
		}
		else {
			std::cout << (idx + 1) << "." << "[" << PriorityPrintChar << "]" << "[" << DonePrintChar << "] " << TaskArray[idx].TaskName << std::endl;
		}
	}
}


// Function adds, deletes or edits tasks depending on OpsType
void DoTasks(Tasks TaskArray[], int& NumOfTasks, const int MaxTasks, char OpsType) {

	switch (OpsType) {
	case ('A'):
		AddTasks(TaskArray, NumOfTasks, MaxTasks);
		break;

	case('E'):
		EditTasks(TaskArray, NumOfTasks);
		break;

	case ('D'):
		DeleteTasks(TaskArray, NumOfTasks);
		break;
	}
}

// Function adds new tasks to the memory
void AddTasks(Tasks TaskArray[], int& NumOfTasks, const int MaxTasks) {
	
	char PriorityInput;
	bool check = true;
	
	if (NumOfTasks >= MaxTasks) {
		std::cout << "You've reached the maximum number of tasks! Complete and delete some to add more! :D" << std::endl;
		return;
	}

	std::cout << "What tasks do you want to add? \n";
	std::getline(std::cin, TaskArray[NumOfTasks].TaskName);
	std::cout << std::endl;

	while (check == true) {
		std::cout << "Is this a Priority task? (Y/N): ";
		std::cin >> PriorityInput;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Flush '\n' from buffer.

		switch (PriorityInput) {
		case ('Y'):
			TaskArray[NumOfTasks].Priority = true;
			check = false;
			break;

		case ('N'):
			TaskArray[NumOfTasks].Priority = false;
			check = false;
			break;

		default:
			std::cout << "Wrong input entered >_< Please enter Y or N only.\n";
			check = true;
			break;
		}
	}
	NumOfTasks++;
}

// Funciton edits tasks
void EditTasks(Tasks TaskArray[], int NumOfTasks) {
	
	if (NumOfTasks <= 0) {
		std::cout << "There are no tasks to edit :O Add some tasks!! \n";
		return;
	}

	bool check = true;
	int EditTaskNum;

	while (check == true) {
		std::cout << "Which task do you want to edit. Enter DIGIT (1 - " << NumOfTasks << ")\n";
		std::cin >> EditTaskNum;
		if (EditTaskNum > 0 && EditTaskNum <= NumOfTasks) {
			TaskArray[EditTaskNum - 1].TaskEditor();
			check = false;
		}
		else {
			std::cout << "Wrong input!\n\n";
		}
	}
}

// Function performs the edit of task (CLASS METHOD)
void Tasks::TaskEditor(){
	char FnOps;
	bool check = true;

	while (check == true) {
		std::cout << "What edit would you like to perform? Check/uncheck (P)riority. Check/uncheck (D)one. (E)dit task description. ";
		std::cin >> FnOps;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Flush '\n' from buffer.

		switch (FnOps) {
		case 'P':
			Priority = !Priority;
			check = false;
			break;

		case 'D':
			Done = !Done;
			check = false;
			break;

		case 'E':
			std::cout << "Enter your new task description: \n";
			std::getline(std::cin, TaskName);
			check = false;
			break;

		default:
			std::cout << "Wrong input entered >_< Please enter P, D or E only.\n";
			check = true;
			break;
		}


	}
}

// Function deletes tasks from the memory
void DeleteTasks(Tasks TaskArray[], int& NumOfTasks) {

	if (NumOfTasks <= 0) {
		std::cout << "There are no tasks to delete :O \n";
		return;
	}

	bool check = true;
	int DeleteTaskNum;
	int idx;

	
	while (check == true) {
		std::cout << "Which task do you want to delete. Enter DIGIT (1 - " << NumOfTasks << ")\n";
		std::cin >> DeleteTaskNum;
		if (DeleteTaskNum > 0 && DeleteTaskNum <= NumOfTasks) {
			check = false;
		}
		else {
			std::cout << "Wrong input!\n\n";
		}
	}

	// Delete operation
	for (idx = DeleteTaskNum; idx < NumOfTasks; idx++) {
		TaskArray[idx - 1] = TaskArray[idx];
	}
	NumOfTasks--;
}

