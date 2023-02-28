#include<iostream>

using namespace std;

class Doll
{
	public:
		//Accessors
		string getName() { return name; }
		static unsigned int getCount() { return count; }

		//Helper functions

		//Prints the name of this Doll, but flipped.
		void printDoll();

		//Recursive functions
		void insert(Doll* new_doll);
		void open();
		Doll* removeCenter();
		static void printReverse(const string& str, int length);

		//Constructor
		Doll(string name) { this->name = name; innerDoll = NULL; generateId(); }

	private:
		unsigned int id; //The id for this Doll. Determined by when it was read in
		static unsigned int count; //How many Dolls have been read in. You won't need to update this
		string name; //Name of the Doll. This will be backwards.
		Doll* innerDoll; //Pointer to the Doll in this one. NULL if there is none

		void generateId() { id = count++; } //Sets this Doll's id and increments the count of Dolls that exist

};