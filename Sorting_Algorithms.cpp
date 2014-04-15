// Joseph Mercedes
// DSA Program 2
// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2013

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds one string
class Data {
public:
  string data;
  Data(const string &s) { data = s; }
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l) {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    string line;
    getline(input, line);
    l.push_back(new Data(line));
  }

  input.close();
}

// Output the data to a specified input file
void writeDataList(const list<Data *> &l) {
  string filename;
  cout << "Enter name of output file: ";
  cin >> filename;

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->data << endl;
  }

  output.close();
}

void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  list<Data *> theList;
  loadDataList(theList);

  cout << "Data loaded.  Executing sort..." << endl;

  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  writeDataList(theList);
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

int length;
int data;
list<Data *> buckets [1000];
list<Data *>::iterator it;
int numDig;
list<Data *> sortedList;
int counts [1000000];
Data * countptrs [1000000];

bool compare(Data *A, Data *B){
	int i1=20;
	int i2=20;
		
	while((A->data)[i1]!='.') {
		i1--;
	}
	while((B->data)[i2]!='.'){
		i2--;
	}
	if (i1 == i2) {
		return A->data<B->data;
	} 
	else 
	return i1 < i2;
}

int dec_place;
string subStr;
int subInt;

void bucketSort(list<Data *> &l){
	// go through the original list l
	//		find decimal point
	//		set number of most sig digits to take
	//		take substring of that size from data string
	//		convert substring to int
	//		use int to index into proper linked list in array to push data ptr in
	// go through each bucket
	//		sort bucket
	//		append bucket to end of your final sorted list (splice)
	// replace original list l with your final sorted list so that l is now sorted

	int dec_place;

	for (it=l.begin();it!=l.end();it++){
		dec_place = 20;
		while(((*it)->data)[dec_place]!='.'){
			dec_place--;
		}		
		numDig = dec_place-17;
		if (numDig<0) numDig=0;

		subStr = ((*it) -> data).substr(0,numDig);
		subInt = atoi(subStr.c_str());
		buckets[subInt].push_back(*it);
	}
	
	for (int i=0;i<1000;i++){
		buckets[i].sort(compare);
		sortedList.splice(sortedList.end(),buckets[i]);
	}

	sortedList.swap(l);
}

void countingSort(list<Data *> &l){

	// Go through the list one element at a time
	//		convert string to float and convert that to int (mult by 1000)
	//		push int to bucket
	// splice each bucket one at a time to the sorted list

	for (it=l.begin();it!=l.end();it++){
		float f = 1000*atof( ( (*it)->data ).c_str() );
		int g=f;
		countptrs[g] = *it;
		counts[g]++;
	}

	for (int i=0;i<1000000;i++){
		while (counts[i]--) {
			sortedList.push_back(countptrs[i]);
		}
	}
	sortedList.swap(l);
}

list<Data *>::iterator holePos;
list<Data *>::iterator tmpIter;

void insertionSort(list<Data *> &l) {

	it = l.begin(); it++;
	for (it; it!=l.end(); ++it) {
		holePos = it;
		tmpIter = holePos; 
		tmpIter--;
		while (holePos!=l.begin() && (*holePos)->data < (*tmpIter)->data) {
			iter_swap(holePos,tmpIter);
			holePos--;
			tmpIter--;
		}
	}

}

void sortDataList(list<Data *> &l) {
	int length = l.size();
	int subStr1;
	int subStr2;
	int dec;
	dec = (*(l.begin()))->data.find('.');
	it = l.begin();
	subStr1 = atoi(((*it) -> data).substr(0,9).c_str());
	it++;
	subStr2 = atoi(((*it) -> data).substr(0,9).c_str());

	if(length < 110000){
		bucketSort(l);
	}
	else if(length>200000 && dec<10){
		countingSort(l);
	}
	else if(length>200000 && dec>10 && subStr1!=subStr2){		
		bucketSort(l);
	}
	else if(length>200000 && dec>10 && subStr1==subStr2){
		insertionSort(l);
	}
}