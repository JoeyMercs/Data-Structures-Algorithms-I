// Joseph Mercedes
// Data Structures and Algorithms I
// Programming Project 1 - Lists, Stacks, and Queues

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <iterator>
#include <sstream>
#include <list>

using namespace std;

//SimpleList Class that initializes the Lists to be used with Stacks and Queues
template <class T>
class SimpleList{
    private:
    int length;
    string name;
        class sNode{
            public:
            T data;
            sNode *next, *prev;
        };
    sNode *head, *tail;
    public:
        int getLength(){
        return length;
        }
    virtual void push(T item)=0;
    virtual T pop()=0;
    SimpleList (string str) {
        head = new sNode();
        tail = new sNode();
        name = str;
        head -> next = tail;
        head -> prev = NULL;
        tail -> prev = head;
        tail -> next = NULL;
        length = 0;
    }
    string getName() {return name;}
    protected:
    void pushToHead(T item);
    T popFromHead();
    T popFromTail();
    };

// Pushes a piece of data to the head
template <class T>
void SimpleList<T>::pushToHead(T item){
    sNode *temp = new sNode;
    temp -> data = item;
    temp -> next = head -> next;
    temp -> prev = head;
    (head -> next) -> prev = temp;
    head -> next = temp;
    length ++;
}

// Pops a peice of data from the head
template <class T>
T SimpleList<T>::popFromHead(){
    T t1 = head -> next -> data;
    sNode *temp = head -> next;
    ((head -> next) -> next) -> prev = head;
    head -> next = (head -> next) -> next;
    delete temp;
    length --;
    return t1;
}

//Pops a peice of data from the Tail
template <class T>
T SimpleList<T>::popFromTail(){
    T t1 = tail -> prev -> data;
    sNode *temp = tail -> prev;
    ((tail -> prev) -> prev) -> next = tail;
    tail -> prev = (tail -> prev) -> prev;
    delete temp;
    length --;
    return t1;
}

//Handles the Queues
template <class T>
class Queue: public SimpleList<T> {
    public:
    void push(T item) { SimpleList<T>::pushToHead(item); }
	T pop() { return SimpleList<T>::popFromTail(); }
	Queue<T>(string str) : SimpleList<T>(str)
		{ }
};

//Handles the Stacks
template <class T>
class Stack: public SimpleList<T> {
    public:
    void push(T item) { SimpleList<T>::pushToHead(item); }
    T pop() { return SimpleList<T>::popFromHead(); }
    Stack<T>(string str) : SimpleList<T>(str)
        { }
};

// Iterator that checks whether or not a list exists
template <class T>
bool checkList(string listName, list<SimpleList<T> *> listToCheck, SimpleList<T> **p2SL) {
	typename list<SimpleList<T> *>::iterator iter;
	for(iter = listToCheck.begin(); iter != listToCheck.end(); ++iter) {
		if (!listName.compare((*iter)->getName())) {
			*p2SL = *iter;
			return true;
		}
	}
	return false;
}

// Main function that switches between the create, push, and pop commands and then further switches between the cases of an int, string, or double.
int main(){
    string inFileName;
    string outFileName;
    string line;
    cout << "Enter name of input file: ";
    cin >> inFileName;
    cout << "Enter name of output file: ";
    cin >> outFileName;
    ifstream in;
    in.open(inFileName.c_str());
    ofstream out;
    out.open(outFileName.c_str());

    list<SimpleList<int> *> listSLi;
    list<SimpleList<double> *> listSLd;
    list<SimpleList<string> *> listSLs;

    if (in.is_open()){
        while(getline(in,line)){
            out << "PROCESSING COMMAND: " << line << endl;
            istringstream stream(line);
            string w0,w1,w2;
            stream >> w0 >> w1 >> w2;
            int sArg;
            w0 == "create" ? sArg = 0 : w0 == "push" ? sArg = 1 : sArg = 2;

            switch(sArg){

                // Create Case
                case 0:
                switch(w1[0]){
                    case 'i':
                    SimpleList<int> *pSLi;
                    if(checkList(w1, listSLi, &pSLi)) {
                        out << "ERROR: This name already exists!" << endl;
                    }
                    else{
                        if(w2=="stack"){
                            pSLi = new Stack<int>(w1);
                        }
                        else{
                            pSLi = new Queue<int>(w1);
                        }
                        listSLi.push_front(pSLi);
                    }
                    break;

                    case 's':
                    SimpleList<string> *pSLs;
                    if(checkList(w1,listSLs, &pSLs)) {
                        out << "ERROR: This name already exists!" << endl;
                    }
                    else{
                        if(w2=="stack"){
                            pSLs = new Stack<string>(w1);
                        }
                        else{
                            pSLs = new Queue<string>(w1);
                        }
                        listSLs.push_front(pSLs);
                    }
                    break;

                    case 'd':
                    SimpleList<double> *pSLd;
                    if(checkList(w1,listSLd, &pSLd)) {
                        out << "ERROR: This name already exists!" << endl;
                    }
                    else{
                        if(w2=="stack"){
                            pSLd = new Stack<double>(w1);
                        }
                        else{
                            pSLd = new Queue<double>(w1);
                        }
                        listSLd.push_front(pSLd);
                    }
                    break;
                }
                break;

                //Push Case
                case 1:
                    switch(w1[0]){
                        case 'i':
                        SimpleList<int> *pSLi;
                        if(checkList(w1, listSLi, &pSLi)){
                            pSLi -> push(atoi(w2.c_str()));
                        }
                        else{
                            out << "ERROR: This name does not exist!" << endl;
                        }
                        break;

                        case 's':
                        SimpleList<string> *pSLs;
                        if(checkList(w1, listSLs, &pSLs)){
                            pSLs -> push(w2);
                        }
                        else{
                            out << "ERROR: This name does not exist!" << endl;
                        }
                        break;

                        case 'd':
                        SimpleList<double> *pSLd;
                        if(checkList(w1, listSLd, &pSLd)){
                            pSLd -> push(atof(w2.c_str()));
                        }
                        else{
                            out << "ERROR: This name does not exist!" << endl;
                        }
                        break;
                    }
                break;

                //Pop Case
                case 2:
                    switch(w1[0]){
                        case 'i':
                        SimpleList<int> *pSLi;
                        if(!checkList(w1, listSLi, &pSLi)){
                            out << "ERROR: This name does not exist!" << endl;
                        }
                        else if(pSLi -> getLength() == 0){
                            out << "ERROR: This list is empty!" << endl;
                        }
                        else{
                                int value = pSLi -> pop();
                                out << "Value popped: " << value << endl;
                            }
                        break;

                        case 's':
                        SimpleList<string> *pSLs;
                        if(!checkList(w1, listSLs, &pSLs)){
                            out << "ERROR: This name does not exist!" << endl;
                        }
                        else if(pSLs -> getLength() == 0){
                            out << "ERROR: This list is empty!" << endl;
                        }
                        else{
                                string value = pSLs -> pop();
                                out << "Value popped: " << value << endl;
                            }
                        break;

                        case 'd':
                        SimpleList<double> *pSLd;
                        if(!checkList(w1, listSLd, &pSLd)){
                            out << "ERROR: This name does not exist!" << endl;
                        }
                        else if(pSLd -> getLength() == 0){
                            out << "ERROR: This list is empty!" << endl;
                        }
                        else{
                                double value = pSLd -> pop();
                                out << "Value popped: " << value << endl;
                            }
                        break;
                        }

                    break;
                    }
            }
        }
        in.close();
        out.close();
        return 0;
    }
