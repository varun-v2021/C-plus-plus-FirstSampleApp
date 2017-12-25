/*
 * MainClass.cpp
 *
 *  Created on: Dec 8, 2017
 *      Author: Varun_Venkatesh
 */
#include "MainClass.hpp"
Pointer.hpp
#include <iostream>
#include <memory>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include<boost/lambda/lambda.hpp>


using namespace std;

MainClass::MainClass() {
	// TODO Auto-generated constructor stub
	cout << "Main Class constructor\n";
}

MainClass::~MainClass() {
	// TODO Auto-generated destructor stub
	cout << "Main Class destructor\n";
}

int MainClass::getValue() {
	return MainClass::value; //value cannot be accessed here if it is a non-static variable
}

int MainClass::value = 0;

class A {
public:
	void show() {
		cout << "A::show()\n";
	}
};

//Shallow copy example. This class doesn't contain any pointers which require
//dynamic memory allocation. If there is a requirement for dynamic memory allocation
//then we would need deep copy
Pointer::Pointer(const Pointer& p) {
	x = p.x;
	y = p.y;
}

//********* DEEP COPY EXAMPLE **************//
// Example for a deep copy. Have to implement copy constructor and
// assignment operator overloaded
class Person {
private:
	char* _name;
	int _id;
public:
	Person& operator=(const Person& p);
	Person(const Person& p);
};

//Deep copy constructor
Person::Person(const Person& p) {
	_name = new char[strlen(p._name) + 1]; //allocating memory dynamically
	_id = p._id;
	strcpy(_name, p._name);
}

//IMPORTANT - shallow copy or copying using default copy constructor
/*
 Person::Person(const Person& p){
 //below doesnt dynamically allocate memory by default.
 _name = p._name; //assigning pointer only without copying the memory pointer is pointing to
 _id = p._id;
 } */

/*
 * The following steps are a typical for the assignment operator.

 1. No self-assignment. Test to make sure you aren't assigning an object to itself, eg x = x. Of course no one would write that statement, but it can happen when one side of the assignment is not so obviously the same object. Self assignment fails because the memory associated with the current value of the left-hand-side is deallocated before the assignment, which would invalidate using it from the right-hand-side.
 2. Delete the associated memory. Same as copy constructor.
 3. Copy all the members. Same as copy constructor.
 4. IMPORTANT - Return *this. This is necessary to allow multiple assignment, eg x = y = z;
 * */
Person& Person::operator=(const Person& p) {
	cout << "... assignment operator called ... \n";
	if (this != &p) {  // make sure not same object
		delete[] _name;                     // Delete old name's memory.
		_name = new char[strlen(p._name) + 1]; // Get new space
		strcpy(_name, p._name);              // Copy new name
		_id = p._id;                         // Copy id
	}
	return *this;    // Return ref for multiple assignment
}    //end operator=

void func(const char* x) {
	cout << x << endl;
}

class X {
};
class Y {
};

class P {
public:
	virtual void func1();
};

class Q: public P {
public:
	void func1() {
		cout << "func1 implementation in Q\n";
	}
};

//Example for dynamic cast

struct Base {
	//Virtual is used to make sure Derived destructor is also called on delete
	virtual ~Base() {
		cout << "Base class destructor\n";
	} //virtual keyword makes a Derived class polymorphic

};

struct Derived: Base {
	~Derived() {
		cout << "Derived class destructor\n";
	}
	void name() {
	}
};

//Example for static cast,
// observe, there is no virtual used. Hence static casting

struct B {
	int m = 0;
	void hello() const {
		std::cout << "Hello world, this is B!\n";
	}
};
struct D: B {
	void hello() const {
		std::cout << "Hello world, this is D!\n";
	}
};

enum class E {
	ONE = 1, TWO, THREE
};
enum EU {
	ONE = 1, TWO, THREE
};

class MyClass {
public:
	int value;
	//Important to overload this compare symbol
	bool operator<(const MyClass& x) const {
		return value < x.value;
	}
};

void makeSquare(vector<int>& v) {
	for_each(v.begin(), v.end(),
			cout << boost::lambda::_1 * boost::lambda::_1 << " ");
}

int learnFunction() {
	MainClass mainC;
	cout << "mainC.getValue(): " << mainC.getValue() << endl;
	cout << "MainClass::getValue(): " << MainClass::getValue() << endl;
	auto_ptr<A> p1(new A);
	p1->show();

	// returns the memory address of p1
	cout << p1.get() << endl;

	auto_ptr<A> p2(p1);
	p2->show();

	// p1 is empty now
	cout << p1.get() << endl;

	// p1 gets copied in p2
	cout << p2.get() << endl;
	cout << ".... Unique pointer prints ... \n";

	/*when using unique_ptr there can only be at most one unique_ptr at any one
	 *  resource and when that unique_ptr is destroyed,
	 *  the resource is automatically claimed.
	 *   Also, since there can only be one unique_ptr to any resource,
	 *   so any attempt to make a copy of unique_ptr will cause a compile time error.
	 *
	 *    unique_ptr<A> ptr1 (new A);
	 // Error: can't copy unique_ptr
	 unique_ptr<A> ptr2 = ptr1;
	 */
	/*But, unique_ptr can be moved using the new move semantics
	 * i.e. using std::move() function to transfer ownership of the contained pointer
	 *  to another unique_ptr.*/

	unique_ptr<A> up1(new A);
	up1->show();

	// returns the memory address of p1
	cout << up1.get() << endl;

	// transfers ownership to p2
	unique_ptr<A> up2 = move(up1);
	up2->show();
	cout << up1.get() << endl;
	cout << up2.get() << endl;

	// transfers ownership to p3
	unique_ptr<A> up3 = move(up2);
	up3->show();
	cout << up1.get() << endl;
	cout << up2.get() << endl;
	cout << up3.get() << endl;

	cout << "... shared pointer prints ...\n";

	shared_ptr<A> sp1(new A);
	cout << sp1.get() << endl;
	sp1->show();
	shared_ptr<A> sp2(sp1);
	sp2->show();
	cout << sp1.get() << endl;
	cout << sp2.get() << endl;

	// Returns the number of shared_ptr objects
	//referring to the same managed object.
	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;

	// Relinquishes ownership of p1 on the object
	//and pointer becomes NULL
	sp1.reset();
	cout << sp1.get() << endl;
	cout << sp2.use_count() << endl;
	cout << sp2.get() << endl;

	cout << "... Shallow and Deep copy prints ...\n";
	Pointer p; // calls default constructor
	Pointer s = p; // copy constructor is used to initialize in declaration.
	Pointer q(p); //copy constructor is used to build q.
	p = s;  // assignment operator, no constructor or copy constructor.

	/*Casting example*/
	//char *y = "xyz";   //C++ forbids converting char * to string warning
	char *y = new char;
	strcpy(y, "xyz");
	func(const_cast<const char*>(y));
	X *x;
	Y *y1;
	//this one doesn't care or check what type is being casted into what type
	x = reinterpret_cast<X*>(y1);

	cout << "... prints for using dynamic_cast ....\n";
	Base* b1 = new Base;
	if (Derived* d = dynamic_cast<Derived*>(b1)) {
		std::cout << "downcast from b1 to d successful\n";
		d->name(); // safe to call
	}

	Base* b2 = new Derived;
	if (Derived* d = dynamic_cast<Derived*>(b2)) {
		std::cout << "downcast from b2 to d successful\n";
		d->name(); // safe to call
	}

	//At run-time d1 is actually Derived class which is not really Base class
	//Derived* d1 = new Derived;
	Base* d1 = new Derived;
	if (Derived* d2 = dynamic_cast<Derived*>(d1)) {
		std::cout << "explicit upcast from d1 to Base successful\n";
	}

	cout << "... Example for Implicit Upcasting ...\n";
	Derived* d3 = new Derived;
	Base* b3 = d3; //implicit upcasting

	delete b1;
	delete b2;

	cout << "... prints for static_cast ...\n";
	/*
	 * If new_type is a pointer or reference to some class D and the type of expression
	 * is a pointer or reference to its non-virtual base B, static_cast performs a downcast.
	 * This downcast is ill-formed if B is ambiguous, inaccessible,
	 * or virtual base (or a base of a virtual base) of D.
	 * Such static_cast makes no runtime checks to ensure that the object's
	 * runtime type is actually D, and may only be used safely if this
	 * precondition is guaranteed by other means,
	 * such as when implementing static polymorphism.
	 * Safe downcast may be done with dynamic_cast.
	 * */

	short i = 2;
	int j = i; //implicit upcasting
	cout << j << endl;

	D d;
	B& br = d; // upcast via implicit conversion
	br.hello();
	D& another_d = static_cast<D&>(br); // downcast
	another_d.hello();

	cout << "... using Vector printouts ...\n";
	vector<int> vect;
	vect.push_back(3);
	vect.push_back(4);
	vect.push_back(5);
	vector<int>::iterator itr1;
	for (itr1 = vect.begin(); itr1 != vect.end(); itr1++) {
		cout << *itr1 << endl;
	}

	cout << "... using Map printouts ...\n";
	map < string, string > mMap;
	mMap.insert(pair<string, string>("1", "abc"));
	mMap.insert(pair<string, string>("2", "xyz"));
	map<string, string>::iterator itr = mMap.begin();
	while (itr != mMap.end()) {
		cout << "key: " << itr->first << endl;
		cout << "value: " << itr->second << endl;
		itr++;
	}

	cout << "... using Set printouts ...\n";

	MyClass o1;
	o1.value = 66;
	MyClass o2;
	o2.value = 77;

	set<int> sSet;
	set<MyClass> mySet;

	mySet.insert(o1);
	mySet.insert(o2);

	sSet.insert(99);
	sSet.insert(100);

	set<MyClass>::iterator itr3;
	for (itr3 = mySet.begin(); itr3 != mySet.end(); itr3++) {
		cout << itr3->value << " OR " << (*itr3).value << endl;
	}

	set<int>::iterator itr2;
	for (itr2 = sSet.begin(); itr2 != sSet.end(); itr2++) {
		cout << *itr2 << endl;
	}

	Base *ptr = new Derived;
	delete ptr;

	//Boost related code snippet
	cout << "... boost related print outs \n ...";
	vector<int> v;
	for (int i = 1; i <= 10; i++)
		v.push_back(i);
	makeSquare(v);

	return 0;
}
