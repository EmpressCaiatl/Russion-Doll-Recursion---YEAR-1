/*
* Assignment 9 - Recursion
* Sam Black - Skeleton contributor and main
* Isabella - finished skeleton and coded Doll.h and Doll_skeleton.cpp
* 
* Description: In this program, you will have a series of Matryoshka Dolls. Each Matryoshka Doll can contain any number of other
* Dolls inside of it. You will need to implement functions to insert, open, and get the innermost of the dolls. To do this, we will
* be recursively calling 3 functions: Insert(), Open(), and RemoveCenter(). Each Doll will have a name that is read from a file.
* After reading the Doll's name, we will insert it at the center of the current collection of Dolls. After all Dolls have been read,
* the program will open each of them, printing the Dolls we read in. It will then remove each of the dolls from the center until there
* are no more and put them into a vector. This vector will then be sorted alphabetically by Doll name and then printed
*/

#include <fstream>
#include <string>
#include <vector>
#include "Doll.h"

void sortDolls(vector<Doll*>& list, int size); //sortDolls function sorts a vector of Dolls by name. Implement this outside of the class.
bool isBigger(const string& reverse_name_1, const string& reverse_name_2, int offset);
 
unsigned int Doll::count = 0;

int main(int argc, char** argv)
{
	//Variable declarations
	Doll* outerDoll; //Doll that is on the outside, housing all other Dolls
	string name; //Temp variable for the name read from the file
	vector<Doll*> dolls; //We'll need this later to keep all of the dolls

	if (argc != 2) //Check for correct usage
	{
		cout << "ERROR. Program takes one argument" << endl << "Usage: ./a.out <filename>" << endl;
		return EXIT_FAILURE;
	}

	ifstream infile;
	infile.open(argv[1]);

	if (!infile.good()) //Make sure the file opened correctly
	{
		cout << "Unable to open file " << argv[1] << ". Please check that the file name is correct." << endl;
		return EXIT_FAILURE;
	}

	//Now, start reading from the file
	getline(infile, name, ' ');
	outerDoll = new Doll(name); //Create the first doll for the outside

	while (getline(infile, name, ' ')) //Keep reading while we can
		outerDoll->insert(new Doll(name)); //Create a new Doll from the name and insert it into the current collection of Dolls

	cout << "Read " << Doll::getCount() << " dolls " << endl << endl;

	//Now, let's go through all of the Dolls and open them
	cout << "*****Opening dolls*****" << endl << endl;
	outerDoll->open();

	//Next, let's move all of the Dolls to a vector
	bool empty = false;
	dolls.push_back(outerDoll->removeCenter()); //Get the first Doll
	while (dolls[dolls.size() - 1] != outerDoll) //While there are still Dolls to be read
		dolls.push_back(outerDoll->removeCenter()); //Remove the innermost Doll and add it to our list

	//Now, let's sort the Doll vector
	cout << endl << "*****Sorted dolls*****" << endl << endl;
	sortDolls(dolls, dolls.size());

	//Now let's print all of the sorted Dolls
	for (unsigned int i = 0; i < dolls.size(); i++)
		dolls[i]->printDoll();

	return EXIT_SUCCESS; //We're done!
}

//Tells if the first of the two names reversed is alphabetically first
bool isBigger(const string& reverse_name_1, const string& reverse_name_2, int offset = 0)
{
	//Base cases. If we've run out of chars, return the longer one or arbitrarily pick the first
	if (reverse_name_1.length() - offset <= 1 || reverse_name_2.length() - offset <= 1)
		return reverse_name_1.length() >= reverse_name_2.length();

	//If the characters match, keep going
	if (reverse_name_1[reverse_name_1.length() - 1 - offset] == reverse_name_2[reverse_name_2.length() - 1 - offset])
		return isBigger(reverse_name_1, reverse_name_2, offset + 1);

	//Otherwise, just return based on the one with the "bigger" character
	return reverse_name_1[reverse_name_1.length() - 1 - offset] >= reverse_name_2[reverse_name_2.length() - 1 - offset];
}

void sortDolls(vector<Doll*>& list, int size)
{
	//Bubble Sort
	for (int x = 0; x < size - 1; x++)
	{
		for (int y = 0; y < size - x - 1; y++) 
		{
			//check for alphabetical order
			if (isBigger(list[y]->getName(), list[y + 1]->getName())) 
			{
				Doll *tempDoll;             //new temp for storing
				tempDoll = list[y];			//stores name for overwriting
				list[y] = list[y + 1];		//overwrites ... swap
				list[y + 1] = tempDoll;     //swap complete
			}
		}

		sortDolls(list, size - 1);		    //recursive call for sort
	}
}
