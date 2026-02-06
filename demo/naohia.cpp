#include <iostream>
#include <string>
using namespace std;
//test comment

/*
process of creating a class:
1. declaration/specification (high-level details)
2. class implementation (low-level details)
ideally decouple these processes
*/
class person //class creation
{
    //public: //access modifier, now everyone can use
private: // prevent external ways to modify data members outside of constructors
    //data members:
    string name;
    int age;
    string nationality;

    //member functions:

    /*
    constuctor function 
    - no return type
    - is automatically invoked - programmer no need to call it out
    - function name same as class name
    used to initialize data members
    */

public:
    //DEFAULT CONSTRUCTOR, once you set your own constructor the default one gets overwritten. if want to restore the others, need to add this back
    //oh ye constructors can be overloaded (like function overloading)
    person()
    {
    }

    person(string nm, int age2, string racism) //again, no return type, function parameters named diff for ease of use
    {
        name = nm; //LHS - data member, RHS - data input by user. this is why parameters is named diff
        age = age2;
        nationality = racism;

        //can do error handling here
        if (age < 0 || age > 100)
        {
            age = 0; //default age
        }
        else {
            age = age2;
        }
    }
   
    void profiling //usually is public so others can use
    {
        cout << "nihao " << name << endl;
        cout << "i am " << age << endl;
        cout << " " << nationality << endl << endl;    
    }
    void setname //allow for changing variables if need be
    {
        name = newname;
    }
    void getname //user input for name
    {
        return name;
    }
}

int main() //using the class here
{
    person p1; //create an obj named "p1" of class "person", each has a default constructor
    //initializing data members
    /*
    p1.name = "leeeeen";
    p1.age = 67;
    p1.nationality = "myanmmarese";
    */
    p1.setname("leeeeeeeeeen"); //new way of setting variables
    cout << p1.getname() << endl;

    person p2; //blank values
    /*p2.name = "demon";
    p2.age = 1;
    p2.nationality = "awaken";
    */

    //creating object + initialize data members (only works w own set constructors)
    person p3 ("ch", 13, "furry"); //memory space allocated for this alr, regardless if values have been assigned
    //fyi no way of updating this after its initialized, unless separate function is added

    //invalid examples:
    person p4 ("vvvvv", -34578, "gay") //1st abuse case - initialize invalid inputs w defined constructor

    person p5;
    p5.age = -63 //2nd case of abuse - initialize invalid inputs w default constructor 

    //calling member function
    p1.profiling(); //calling member func 
    p2.profiling();
    p3.profiling(); 
    p4.profiling();
    //empty definitions output blanks/gibberishh, depending on output type (if left blank)
}

//decoupled class declaration - whatever happens w these functions is the implementation - low level
//this will go to a header file, just class specifications. header file name matches class name.
class person2
{
    private:
    string name3;
    int year;
    string residency;
    static int count; //static member - shared across ALL objects

    public:
    person2();
    person2(string nm3, int dob, string location);
    void SetName(string newname);
    string GetName;
    void profiling2(); 
    void countcheck();

}

//implementation (as a cpp file, implementation details - again file name is the same. to make sure it matches, add include header file)
//#include "filename.h" MUST BE ADDED SO THE DECLARATION GOES THROUGH
person2::person2() //association w function in class
{
    count++;
}

person2::person2(string nm3, int dob, string location)
{
    count++; //need to add for all constructors since its a private 
    name3 = nm3; //LHS - data member, RHS - data input by user. this is why parameters is named diff
        year = dob;
        residency = location;

        //can do error handling here
        if (year < 0 || year > 100)
        {
            year = 0; //default age
        }
        else {
            year = dob;
        } 
}

void person2::SetName(){
    return name3;
}

void person2::GetName(){
    name3 = GetName;
}

void person2::profiling2()
    {
        cout << "nihao " << name3 << endl;
        cout << "i am " << year << endl;
        cout << " " << residency << endl << endl;    
    }

int person2::checkcount(){ //for static variable
    cout << "objects created: " << count << endl;
}

void main() //main file, just include header files accordingly. drag all files into the same folder fyi
{
    person2 p9 ("ni", 25, "bangala");
    p9.profiling2();

    //WE LOVE POINTERS WOOOOOOOOOOOOOOOOOOO
    person2* ptr = nullptr;
    ptr = new person2("abs", 2, "usa");

    (*ptr).profiling2(); //reading/deferencing, not writing
    ptr->profiling2(); //just using pointer, w/o deferencing (just calling objects). functionally the same
    //pointers can avoid ambiguiity so that you can put the same name
    person2::checkcount();
}

//for each class: 1 header file + 1 cpp file. inside main file (main.cpp or wtv), add all as necessary. (modular design)
//note: struct and class is mostly same, diff being data members/functions in c++ is private for data security
//struct is public by default, for backwards compatibility w C
/*
Encapsulation - hide unecessary or important details accordingly
protected data type - accesssible only by code defined within either its own class or "child" classes related via INHERITANCE
#include <iostream>
#include <string>
using namespace std;

/*
process of creating a class:
1. declaration/specification (high-level details)
2. class implementation (low-level details)
ideally decouple these processes
*/
class person //class creation
{
    //public: //access modifier, now everyone can use
private: // prevent external ways to modify data members outside of constructors
    //data members:
    string name;
    int age;
    string nationality;

    //member functions:

    /*
    constuctor function 
    - no return type
    - is automatically invoked - programmer no need to call it out
    - function name same as class name
    used to initialize data members
    */

public:
    //DEFAULT CONSTRUCTOR, once you set your own constructor the default one gets overwritten. if want to restore the others, need to add this back
    //oh ye constructors can be overloaded (like function overloading)
    person()
    {
    }

    person(string nm, int age2, string racism) //again, no return type, function parameters named diff for ease of use
    {
        name = nm; //LHS - data member, RHS - data input by user. this is why parameters is named diff
        age = age2;
        nationality = racism;

        //can do error handling here
        if (age < 0 || age > 100)
        {
            age = 0; //default age
        }
        else {
            age = age2;
        }
    }
   
    void profiling() //usually is public so others can use
    {
        cout << "nihao " << name << endl;
        cout << "i am " << age << endl;
        cout << " " << nationality << endl << endl;    
    }
    void setname(string newname) //allow for changing variables if need be
    {
        name = newname;
    }
    void getname(string name) //user input for name
    {
        return name;
    }
};

int main() //using the class here
{
    person p1; //create an obj named "p1" of class "person", each has a default constructor
    //initializing data members
    /*
    p1.name = "leeeeen";
    p1.age = 67;
    p1.nationality = "myanmmarese";
    */
    p1.setname("leeeeeeeeeen"); //new way of setting variables
    cout << p1.getname() << endl;

    person p2; //blank values
    /*p2.name = "demon";
    p2.age = 1;
    p2.nationality = "awaken";
    */

    //creating object + initialize data members (only works w own set constructors)
    person p3 ("ch", 13, "furry"); //memory space allocated for this alr, regardless if values have been assigned
    //fyi no way of updating this after its initialized, unless separate function is added

    //invalid examples:
    person p4 ("vvvvv", -34578, "gay") //1st abuse case - initialize invalid inputs w defined constructor

    person p5;
    p5.age = -63 //2nd case of abuse - initialize invalid inputs w default constructor 

    //calling member function
    p1.profiling(); //calling member func 
    p2.profiling();
    p3.profiling(); 
    p4.profiling();
    //empty definitions output blanks/gibberishh, depending on output type (if left blank)
}

//decoupled class declaration - whatever happens w these functions is the implementation - low level
//this will go to a header file, just class specifications. header file name matches class name.
class person2
{
    private:
    string name3;
    int year;
    string residency;
    static int count; //static member - shared across ALL objects

    public:
    person2();
    person2(string nm3, int dob, string location);
    void SetName(string newname);
    string GetName;
    void profiling2(); 
    void countcheck();

}

//implementation (as a cpp file, implementation details - again file name is the same. to make sure it matches, add include header file)
//#include "filename.h" MUST BE ADDED SO THE DECLARATION GOES THROUGH
person2::person2() //association w function in class
{
    count++;
}

person2::person2(string nm3, int dob, string location)
{
    count++; //need to add for all constructors since its a private 
    name3 = nm3; //LHS - data member, RHS - data input by user. this is why parameters is named diff
        year = dob;
        residency = location;

        //can do error handling here
        if (year < 0 || year > 100)
        {
            year = 0; //default age
        }
        else {
            year = dob;
        } 
}

void person2::SetName(){
    return name3;
}

void person2::GetName(){
    name3 = GetName;
}

void person2::profiling2()
    {
        cout << "nihao " << name3 << endl;
        cout << "i am " << year << endl;
        cout << " " << residency << endl << endl;    
    }

int person2::checkcount(){ //for static variable
    cout << "objects created: " << count << endl;
}

void main() //main file, just include header files accordingly. drag all files into the same folder fyi
{
    person2 p9 ("ni", 25, "bangala");
    p9.profiling2();

    //WE LOVE POINTERS WOOOOOOOOOOOOOOOOOOO
    person2* ptr = nullptr;
    ptr = new person2("abs", 2, "usa");

    (*ptr).profiling2(); //reading/deferencing, not writing
    ptr->profiling2(); //just using pointer, w/o deferencing (just calling objects). functionally the same
    //pointers can avoid ambiguiity so that you can put the same name
    person2::checkcount();
}

//for each class: 1 header file + 1 cpp file. inside main file (main.cpp or wtv), add all as necessary. (modular design)
//note: struct and class is mostly same, diff being data members/functions in c++ is private for data security
//struct is public by default, for backwards compatibility w C
/*
Encapsulation - hide unecessary or important details accordingly
protected data type - accesssible only by code defined within either its own class or "child" classes related via INHERITANCE
*/