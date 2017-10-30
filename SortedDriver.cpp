// SortedDriver.cpp

// tom bailey   1445  25 mar 2014
// Construct sorted sequences and call functions that 
//   process the sorted sequences.
// Edited by: Chris Schultz
// Date: 30 October 2017

#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"
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

// finds the most isolated number in a vector (furthest distance between values)
// COME BACK TO ME -- works in PDF examples but not in other tests?
double mostIsolated(vector<double> & number) {
	double diff, diffL, diffR, tempIso;
	int size = number.size();

	// loop to test the differences on either side of the vector value
	for (int i = 0; i < size; i++) {
		// special case for beginning of the loop
		if (i == 0){
			diffR = abs(number[i + 1] - number[i]);
			diff = diffL = diffR;
		}
		// if it is not at the beginning or the end
		else if (i > 0 && i != size - 1) {
			diffR = abs(number[i + 1] - number[i]);
			if (diffL > diff && diffR > diff) {
				if (diffL <= diffR) {
					diff = diffL;
				}
				else {
					diff = diffR;
				}
				tempIso = number[i];
			}
			diffL = diffR;
		}
		// if it is at the end
		else if (i == size - 1) {
			if (diffL > diff)
			{
				tempIso = number[i];
			}
		}
	}
	return tempIso;
}

// compare strings to finds words in string A that are not in string B
// determines how many are the same, and then subtracts that from the total
int unmatched(list<string> & A, list<string> & B) {
	int same = 0;
	std::list<string>::iterator itA = A.begin();
	std::list<string>::iterator itB = B.begin();
	while (itA != A.end() && itB != B.end()) {
		if (*itA == *itB) {
			itA++;
			same++;
		}
		else if (*itA > *itB) {
			*itB++;
		}
		else {
			*itA++;
		}
	}
	return A.size() - same;
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