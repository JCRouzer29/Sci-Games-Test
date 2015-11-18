////////////////////////////////////////////////////////////////////////////
/*/	
 *	Creator:		Joshua C. Rouzer
 *	Title:			main
 *	Last Edited:	11/18/2015
 *	Summary:		Program entry point
/*/
////////////////////////////////////////////////////////////////////////////

#include "Person.h"

#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#include <ctime>
//#include <vld.h>		//Visual Leak Detector, debugging purposes

#define SAFE_RELEASE(x)		delete x;		x = nullptr;
#define RELEASE_ARRAY(x)	delete [] x;	x = nullptr;
#define BUTTER_SWAP(x, y)	x ^= y;		y ^= x;		x ^= y;

//Function will load entire contents of file into string buffer
string LoadFile(const char* path){
	ifstream file(path);
	string buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

	return buffer;
}

int LoadNextNumber(string file, int startLoc, int *endLoc){
	char nextChar = file[startLoc];
	string charList;
	//By starting at startLoc, traverse until you find a character which is a number
	//	start tracking the number until you find a non-number character.
	while(true){
		//Range 48-57
		if(nextChar >= '0' && nextChar <= '9'){//Add another number
			charList.push_back(nextChar);
		}
		else if(!charList.empty()){//Whitespace AFTER number
			break;
		}

		//If you find '\0' (End of File) BEFORE any numbers then return -1
		if(nextChar == '\0' && charList.empty()){
			return -1;
		}
		//Increment and determine next character
		nextChar = file[(++(*endLoc))];
	}

	//Convert series of chars (number) into int
	int _return = stoi(charList);

	//Return number
	return _return;
}

//Loop the rest of the numbers, recording each in pairs
list<Person> LoadPeople(string file, int start, pair<short, short> range){
	list<Person> _return;
	Person Someone;

	int nextNum = start;
	int returned = 0;
	do{
		//Get a number
		returned = LoadNextNumber(file, nextNum, &nextNum);
		if(returned < 0){	break;	}

		//Give to next Person
		Someone.SetBirth(returned);

		//Get another number
		returned = LoadNextNumber(file, nextNum, &nextNum);
		if(returned < 0){	break;	}

		//Also give to Person
		Someone.SetEnd(returned);

		//Verify Person's stats
	//Check that they're born on a valid year
		if(Someone.GetBirth() < range.first){
			//Make it the first year
			Someone.SetBirth(range.first);
		}
	//Check that they end on a valid year
		if(Someone.GetEnd() > range.second){
			//Make it the last year
			Someone.SetEnd(range.second);
		}
	//Check their birth year is BEFORE end year
		if(Someone.GetBirth() > Someone.GetEnd()){
			//Swap the years
			Someone.Swap();
		}

		//Add Person to list
		_return.push_back(Someone);

	} while(returned >= 0);

	return _return;
}

list<Person> LoadFromFile(pair<short, short> **PeopleArray, unsigned short &min, unsigned short &max){
	list<Person> _return;
	string filename;

	//Request file to load
	cout << "Please input your filename.\n";
	cin >> filename;
	cout << "\n";

	//Load year range data
	string file = LoadFile(filename.c_str());
	if(!file.empty()){
		int nextNum = 0;
		min = LoadNextNumber(file, 0, &nextNum);
		max = LoadNextNumber(file, nextNum, &nextNum);

		*PeopleArray = new pair<short, short>[(max - min) + 1];

		pair<short, short> range(min, max);
		_return = LoadPeople(file, nextNum, range);
	}
	else{
		cout << "ERROR: Failed to find file\n";
		RELEASE_ARRAY(*PeopleArray)
		return _return;
	}
	return _return;
}
list<Person> CustomList(unsigned short &min, unsigned short &max){
	list<Person> _return;
	min = max = 0;

//Insert custom equation or list into _return


	return _return;
}
list<Person> RandomList(unsigned short &nMin, unsigned short &nMax){
	list<Person> _return;
	unsigned int count;

	cout << "How many people in your list?\n";
	cin >> count;
	cout << "\nWhat is the lowest year?\n";
	cin >> nMin;
	cout << "\nWhat is the highest year?\n";
	cin >> nMax;

	if(nMax < nMin){ 
		BUTTER_SWAP(nMin, nMax);
	}
	int length = (nMax - nMin) + 1;

	Person Someone;
	unsigned short birth, end;
	for(unsigned int iter = 0; iter < count; iter++){
		birth = (rand() % length) + nMin;
		Someone.SetBirth(birth);
		end = (rand() % length) + nMin;
		Someone.SetEnd(end);

		if(Someone.GetBirth() > Someone.GetEnd()){ 
			Someone.Swap();
		}

		_return.push_back(Someone);
	}

	return _return;
}

int main(){
	srand((unsigned int)time(0));
	pair<short, short> *PeopleArray = nullptr;
	list<Person> MidwayList, StatTrackingList;
	unsigned short min, max, length;
	char input;

	cout << "How is this list being provided?\n" <<
		"1) Load from file.\n2) Custom list.\n3) Randomly generated list.\n";
	cin >> input;

	switch(input){
		case '1':
			MidwayList = LoadFromFile(&PeopleArray, min, max);
			if(!PeopleArray){	return 1;	}
			break;
		case '2':
			MidwayList = CustomList(min, max);
			break;
		case '3':
			MidwayList = RandomList(min, max);
			PeopleArray = new pair<short, short>[(max - min) + 1];

			break;
		default:
			cout << "ERROR: Please choose from provided methods of input.\n";
			RELEASE_ARRAY(PeopleArray)
			return 2;
	}

	length = (max - min) + 1;
	if(length == 1 && !MidwayList.size()){
		cout << "ERROR: Please create custom list argument\n";
		return 3;
	}

	//Load people from the List to Array
	Person Someone;
	const int HeadCount = MidwayList.size();
	StatTrackingList = MidwayList;
	while(MidwayList.size()){
		Someone = MidwayList.front();
		PeopleArray[Someone.GetBirth()	- min].first++;
		MidwayList.pop_front();
		PeopleArray[Someone.GetEnd()	- min].second--;
		//Note: These are spaced out so that the processor can better multitask, even slightly.
		//	whenever one item is in use in a multithread capable program, it causes
		//	processes to slow down.
	}//*/

	//Calculate out list values
	//Run down through the list, adding/subtracting .first value from previous
	//	Then assign that value to the .second value
	int livePeople = 0, MostLiving = 0, MostLivingYear = 0;
	int HighestBorn = 0, BornYear = 0, LowestEnd = 0, EndYear = 0;
	for(int iter = 0; iter < length; iter++){
		pair<short, short> current = PeopleArray[iter];
		//Add the births
		livePeople += current.first;
	//Stat-tracking
		if(current.first > HighestBorn){
			HighestBorn = current.first;
			BornYear = min + iter;
		}
		//Subtract the ends
		livePeople += current.second;
	//Stat-tracking
		if(current.second < LowestEnd){
			LowestEnd = current.second;
			EndYear = min + iter;
		}
		//Consolidation
		current.first += current.second;

		//Re-purpose second variable
		current.second = livePeople;

	//Stat-tracking
		if(livePeople > MostLiving){
			MostLiving = livePeople;
			MostLivingYear = min + iter;
		}
	}

	//Output data
	cout << "Most Living People (" << MostLiving;
	cout << ") was in the year: " << MostLivingYear << '\n';

	ofstream output("Results.txt", ios_base::trunc);
	if(output.is_open()){
		output << "Total People: " << HeadCount << '\n';
		output << "Most People Alive at one time: " << MostLiving << '\n';
		output << "That was in the year: " << MostLivingYear << "\n\n";

		output << "Year with the most people BORN: " << BornYear << " at " << HighestBorn << '\n';
		output << "Year with the most people's END: " << EndYear << " at " << abs(LowestEnd) << '\n';

		output << "\nEach Person's years were as follows:\n";
		while(StatTrackingList.size()){
			Someone = StatTrackingList.front();
			output << Someone.GetBirth() << ", " << Someone.GetEnd() << '\n';
			StatTrackingList.pop_front();
		}
	}
	output.close();

	system("Pause");

	//Cleanup
	RELEASE_ARRAY(PeopleArray);

	return 0;
}