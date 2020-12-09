#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include<iomanip>

using namespace std;

class Word
{
private:
	string strWord;
	int count = 0;
	void setCount(int argCount) { count = argCount; }
public:

	bool isEmpty() { return count == 0; }//return whether the Word is empty
	void incCount() { count++; }		//increment count
	
	//getter and setter functions
	int getCount() { return count; }
	void setWord(string argWord) { strWord = argWord; }
	string getWord() { return strWord; }

	//constructors
	Word();								//default constructor for word
	Word(string);						//constructor for setting word
};

class HashTable
{
private:
	int numBuckets;							//number of buckets in the hash table
	int filledBuckets = 0;					//number of filled buckets
	int numProbes = 0;						//number of times an array element was accessed
	Word* arrBuckets;						//buckets making up hash table
	map<char, int> alphaToPrimeNum;			//map each letter to a prime number for key calculation	

	void incSize() { filledBuckets++; }		//increment number of filled buckets
	void incProbes() { numProbes++; }		//increment number of array element accesses
	void clearProbes() { numProbes = 0; }	//set numProbes to 0
	int calcKey(string);					//calculate hash key

	//getter and setter functions
	void setNumBuckets(int argNumBuckets) { numBuckets = argNumBuckets; }

	//initialize array
	void initParameters();					//initialize array parameters and map
public:
	int* arrUpdates;						//number of updates when size of hashtable is i
	int* arrCost;							//number of probes when size of hashtable is i
	double* arrRatio;						//ratio of cost to updates when size of hashtable is i

	void update(string);					//adds a value to the hash table
	void populateTableFromTxt(string);		//populates table from a given txt file
	void calcRatios();						//calculates ratios of cost to updates

	//getter and setter functions
	int getNumBuckets() { return numBuckets; }
	int size() { return filledBuckets; }
	int probes() { return numProbes; }

	void printTable();						//print hash table
		
	//constructor
	HashTable(int);
	//destructor
	~HashTable();
};	

template<typename T>
void printArr(T[], int);

int main()
{
	const int HASHSIZE = 4001;
	HashTable myTable(HASHSIZE);
	myTable.populateTableFromTxt("RomeoAndJuliet.txt");
	myTable.calcRatios();

	cout << "Number of unique words: " << myTable.size() << endl;
	printArr(myTable.arrRatio, myTable.getNumBuckets());


	system("PAUSE");
	return 0;
}

template<typename T>
void printArr(T arr[], int size)
{
	for (size_t i = 0; i < size; i++)
		cout << fixed << setprecision(2) << arr[i] << ", ";
}

//Hash Table Methods
int HashTable::calcKey(string key)
{
	unsigned long int primeMultiplier = 1;
	
	for (size_t i = 0; i < key.size(); i++)		//iterate through every char of key
		primeMultiplier *= alphaToPrimeNum[key[i]];	//multiply primeMultiplier by 
												//prime number mapped to cur char (key[i])	
	return primeMultiplier % getNumBuckets();	//mod primeMultiplier by numBuckets to get
												//index in hashTable
}

void HashTable::update(string key)
{
	int initIndex = calcKey(key);					//for determining when table is full
	int index = initIndex;							//current index 
	arrUpdates[size()]++;							//inc tracker for updates called at cur size of table
	clearProbes();									//reset probes for this run of update function

	while (true)
	{
		incProbes();	//inc number of times an array is probed
		if (arrBuckets[index].isEmpty())
		{//if bucket is empty add key to table
			arrCost[size()] += probes();			//add number of probes at current size
			incSize();								//inc size of table
			arrBuckets[index] = Word(key);			//set word
			arrBuckets[index].incCount();			//inc count of word
			return;
		}
		if (arrBuckets[index].getWord() == key)
		{//if bucket is not empty but is the same word inc count of word
			arrCost[size()] += probes();
			arrBuckets[index].incCount();
			return;
		}
		index++;
		if (index >= getNumBuckets())
			index = 0;	//index rolls over to 0 once it is equal to number of buckets in hash table
		if (index == initIndex)
		{	//if index is the same as the start then all values have been checked and the table is full
			cout << "\nERROR: HASH TABLE IS FULL\n";
			return;
		}
	}
}

void HashTable::populateTableFromTxt(string fileName)
{
	fstream FILE;					//declare fstream type for file
	FILE.open(fileName, ios::in);	//open file
	if (FILE.is_open())				//check that file has opened properly
	{
		string curWord;
		while (FILE >> curWord)		//place next word from FILE stream into curWord
			update(curWord);		//update curWord into hash table

		FILE.close();				//close file
	}
	else
		cout << "\nERROR: FILE DID NOT OPEN PROPERLY\n";
}

void HashTable::calcRatios()
{
	cout << setprecision(2);
	for (size_t i = 0; i < getNumBuckets(); i++)
	{
		if (arrUpdates[i] != 0)
			arrRatio[i] = double(arrCost[i]) / double(arrUpdates[i]);
		else
			arrRatio[i] = 0;
	}
}

void HashTable::printTable()
{
	for (size_t i = 0; i < getNumBuckets(); i++)
	{
		if (arrBuckets[i].isEmpty())
			cout << "---EMPTY---";
		else
			cout << arrBuckets[i].getWord() << ": " << arrBuckets[i].getCount() << endl;
	}
}

HashTable::HashTable(int argNumBuckets)
{
	setNumBuckets(argNumBuckets);
	arrBuckets = new Word[numBuckets];
	arrCost = new int[numBuckets];
	arrUpdates = new int[numBuckets];
	arrRatio = new double[numBuckets];

	initParameters();
}

HashTable::~HashTable()
{	//clean up all dynamically allocated arrays
	delete[] arrBuckets;
	arrBuckets = nullptr;
	delete[] arrUpdates;
	arrUpdates = nullptr;
	delete[] arrCost;
	arrCost = nullptr;
	delete[] arrRatio;
	arrRatio = nullptr;
}

void HashTable::initParameters()
{
	int primeArr[26] = { 2,3,5,7,11,13,17,19,23,
					29,31,37,41,43,47,53,59,61,
					67,71,73,79,83,89,97,101 };

	for (size_t i = 0; i < getNumBuckets(); i++)
	{
		arrCost[i] = 0;			//initialize cost counter array
		arrUpdates[i] = 0;			//initialize updates counter array
	}

	for (size_t i = 0; i < 26; i++)	//map chars a-z to the first 26 prime numbers
		alphaToPrimeNum[97 + i] = primeArr[i];
}

//Word Methods
Word::Word()
{
	setWord("");
	setCount(0);
}
Word::Word(string argWord)
{
	setWord(argWord);
	setCount(0);
}