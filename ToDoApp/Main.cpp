#include"Headers.h"

int main() {
	
	// Const declarations
	const std::string FileName = "ToDo.txt";
	const int MaxTasks = 5;

	// Declarations
	Tasks TaskArray[MaxTasks];
	int NumOfTasks = 0;
	char FnOps = 'x';
	
	// Step 1: Open file and read to memory --> close file
	try {
		ReadWriteFile(TaskArray, NumOfTasks, FileName, 'R');
	}
	catch (int Error) {
		return 0;
	}

	while (FnOps != 'Q') {
		// Step 2: Print list of tasks
		PrintTasks(TaskArray, NumOfTasks);
		std::cout << std::endl;

		// Step 3: Asks user for program function
		std::cout << "What do you want to do? (A)dd tasks, (E)dit tasks, (D)elete tasks or (Q)uit program? ";
		std::cin >> FnOps;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Flush '\n' from buffer.
		std::cout << std::endl;

		switch (FnOps) {
		case ('A'):
		case ('E'):
		case ('D'):
			DoTasks(TaskArray, NumOfTasks, MaxTasks, FnOps);
			std::cout << std::endl;
			break;

		case ('Q'):
			std::cout << "Ending program and saving file!" << std::endl;
			break;

		default:
			std::cout << "Wrong input entered >_< Please enter A, E, D or Q only." << std::endl;
			std::cout << std::endl;
			break;
		}
	}
	
	// Step 4: Write to file and save file
	try {
		ReadWriteFile(TaskArray, NumOfTasks, FileName, 'W');
	}
	catch (int Error) {
		return 0;
	}
	std::cout << "File saved successfully!\n";
	return 0;
}