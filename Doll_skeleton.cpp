#include "Doll.h"
//Please disregard how creepy the file name is... Just write the code.

//Prints the Doll's id and name using the printReverse function
void Doll::printDoll() { 
	cout << "Doll " << id << ": ";
	
	/*It looks gross, but endl fixes a bug when compiling with g++ where printReverse() is called out of order. Weird threading issue???
	Using flush() doesn't fix this... endl is not needed if you use Visual Studio */
	cout << endl; 
	printReverse(name, name.length());
	cout << endl;
}

/* Put your function implementations for the Doll class here */

void Doll::insert(Doll* new_doll)
{
	if (innerDoll == NULL)			 //checks if innerDoll is empty
	{
		innerDoll = new_doll;		 //sets inner doll to the new doll
	}
	else 
	{
		innerDoll->insert(new_doll); //recursion to insert the doll inside the last inserted doll
	}
}

void Doll::open()
{
	//open statement
	cout << "Opening doll:" << endl;
	this->printDoll();                 //prints doll info

	if (innerDoll != NULL)			   //if the doll is full, open the next
	{
		innerDoll->open();			   //recursive call
	}
}

Doll* Doll::removeCenter() 
{	
	//special case for last doll is NULL
	if (innerDoll == NULL)
	{
		return this;
	}

	//checks if the next doll is NULL
	if (this->innerDoll->innerDoll == NULL)
	{
		Doll *copyDoll;					 //creates new doll
		copyDoll = this->innerDoll;		 //copies inner doll to new doll
		this->innerDoll = NULL;			 //sets inner doll to NULL since this is the new center
		return copyDoll;			
	}
	else 
	{
		this->innerDoll->removeCenter(); //recursive call
	}
	
}

void Doll::printReverse(const string& str, int length)
{
	//base case, all the string as been printed
	if (length < 0) {

		cout << endl;                   //for spacing
		return;

	}
	//recursive case
	else 
	{
		cout << str[length];			//prints 1 character at a time starting from index length 
		printReverse(str, length - 1);  //recursive call

	}




}
