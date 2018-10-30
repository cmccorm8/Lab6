// SortedDriver.cpp

// tom bailey   1445  25 mar 2014
// Construct sorted sequences and call functions that
//   process the sorted sequences.

//Chance McCormick
//Cosc 2030
//10/30/2018


#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"//CHANGE: this to unixTimer.h if on mac/linux
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty;
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{
	
	double temp1;
	double temp2;
	double temp3;
	double tempDistance;
	double tempDistance1;
	double isolatedNum=0;
	double MinDistance;
	temp1 = number.at(0);			//gets the first two elements 
	temp2 = number.at(1);
	double distance = abs(temp2 - temp1);// and find the distance between the two
	for (int i = 1; i < number.size()-1; i++) // starts at 2nd element because we already no the distance between the 1st and second element
	{
		temp1 = number.at(i);	// gets the current element
		temp2 = number.at(i + 1);	// gets the next element
		temp3 = number.at(i - 1); // gets the previous element
		tempDistance1 = abs(temp1 - temp3); // finds the distance between curr element and previous
		tempDistance = abs(temp2 - temp1);	// finds the distance between the curr element and next element
		MinDistance = min(tempDistance1, tempDistance);  // takes the minimum of the two distances 
		if (MinDistance > distance)  // tests for the greatest distance and stores in distance
		{
			distance = MinDistance;
			isolatedNum = number.at(i);  //returns the most isolated element

		}

	}
	return isolatedNum;
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int
unmatched(list<string> & A, list<string> & B)
{
	
	std::list<string>::iterator it2 = B.begin(); // set a pointer the the first element in List B and calls it 'it2'
	
	int counter = 0;
	
	for (std::list<std::string>::const_iterator it = A.begin(); it != A.end();)  // sets a pointer to the first element in List A and calls it 'it'
	{
		
		if(*it2==*it)		//tests to see if the curr element of A is = to the curr element of B
		{
			it++;			// if = iterate A
			counter++;		// keep track of the number of times A is iterated
		}
		
		else if(*it < *it2) // it the curr element of A is less than  curr B iterate A

		{
			
			it++;
			
		}
		else if (*it > *it2) // If the curr element of B is less than curr A iterate B
		{
			std::advance(it2, 1);
		}
		
	}
	return A.size()-counter;  // subtracts the size of A by the number of times the counter was iterated to get 
							// the number of elements in B that are not in A
	
}


int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}
