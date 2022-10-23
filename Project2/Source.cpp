#include <Python.h>
#include <iostream>
#include <iomanip>
#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}


/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}


/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


/*
Description:
	This function will generate a menu when it is used to request user input.
Example:
	MenuButton();
Output:
	Outputs a menu that accepts user input between 1-4 is produced. The appropriate Python function will subsequently be called based on user input.
	 In other words, a user input of 1 will generate a list of unique phrases together with their frequency,
	  a user input of 2 will look up the frequency of a single item, a user input of 3 will create
	 a histogram of each item's frequency, and a user input of 4 will end the program.
Return:
	None

*/
void MenuButton() 
{

	//Make method-specific variables initialized.

	int loopOfMenu = 0;							// Count the amount of menu repetitions.
	int wordCounter = 0;					// Count the instances where a particular search term turned up.
	int itemTotal = 0;						// Variable to hold a quantity of an object based on frequency.dat
	string lookupTerm;							// Gather user information for a search query
	string productName;							// a variable that holds the name of an item from frequency.dat
	string greenColor = "\033[32;1m";			// font color will be set to green for the histogram asterisks
	string defaultColor = "\033[0m";			// default font color set for the console
	ifstream fileInput;							// Open the file in ifstream.

	while (loopOfMenu != 4) 
	{

		// Request and gather user input
		std::cout << "[1] Calculate how many times each item is mentioned." << std::endl;
		std::cout << "[2] Calculate the frequency of a particular item" << std::endl;
		std::cout << "[3] Create a histogram depending on how frequently each item appears" << std::endl;
		std::cout << "[4] Quit" << std::endl;

		std::cin >> loopOfMenu;

		// Verify that user input is accurate. If not, ask for the proper input
		while (std::cin.fail()) 
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please enter a legitimate choice here: ";
			std::cin >> loopOfMenu;
		}


		// Switch statement: Carry out the appropriate action based on user input
		switch (loopOfMenu) 
		{

			//////
			//Case 1: Calculate how many times each item will appear, then produce a list
			//////
		case 1:
			system("CLS");						//Clear the screen to tidy things up
			CallProcedure("TotalingAll");			//Call the Python function "TotalingAll"
			std::cout << std::endl;				//Add a bit of space in between the printed list and menu
			break;

			//////
			//Case 2: Calculate the frequency with which a particular item appears, and then report the outcome
			//////
		case 2:
			// After clearing the screen, gather user input for the search
			system("CLS");
			std::cout << "What item would you like to search for?" << std::endl;
			std::cin >> lookupTerm;

			// Use the search keyword to call the Python function, which will then return an integer word count value
			wordCounter = callIntFunc("CountOccurrences", lookupTerm);

			// print the obtained word count for the statement
			std::cout << std::endl << lookupTerm << " : " << wordCounter << std::endl << std::endl;

			break;

			//////
			//Case 3: Print a histogram showing the frequency of each item. with stars, but similar to scenario 1.
			//////
		case 3:
			system("CLS");						//To organize everything, clear the screen.
			CallProcedure("CollectingData");		// "CollectingData" will call the python function

			fileInput.open("frequency.dat");	// frequency.dat will open from python

			fileInput >> productName;				//Collect first item on list thats's inserted in python
			fileInput >> itemTotal;			//Collect first quantity on list from python

			// Print a histogram for every line in the file. Break after each line has been analyzed
			while (!fileInput.fail()) 
			{
				// White should be the default font color
				std::cout << defaultColor;
				
				// then get ready for the histogram, print the item name
				std::cout << std::setw(14) << std::left << productName << std::setw(6);

				//Set to desired histogram color
				std::cout << greenColor;

				//Print itemTotal of asterisks
				for (int i = 0; i < itemTotal; i++) 
				{

					//Print green asterisks in one line.
					std::cout << std::right << "*";
				}
				//Set the name and quantity of the following item after preparing for the following line
				fileInput >> productName;
				fileInput >> itemTotal;
			}

			//Close frequency.dat 
			fileInput.close();
			std::cout << defaultColor << endl; // resets font color
			break; // ends execution of the nearest enclosing loop

			//////
			//Case 4: Quit option for the program.
			//////
		case 4:

			return;

			//Default case: Invalid input
		default:

			std::cout << "Please input a valid selection.";
			std::cout << std::endl;

			break;
		}
	}
}

//the MenuButton method is invoked to gather user input
void main()
{
	
	MenuButton();

}