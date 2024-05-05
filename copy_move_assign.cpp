#include <iostream>
using namespace std;

class Array
{
    int *elements;
    int size;
public:
    // constructor
    Array(int sz, int multiple)
    {
        cout << "Constructor called!" << endl;
        size = sz;
        elements = new int[size];
        for(int i = 0; i < size; i++)
        {
            elements[i] = i * multiple;
        }
    }
    // copy constructor
    Array(const Array& arry)
    {
        cout << "Copy constructor called!" << endl;
        size = arry.size;
        elements = new int[size];
        std::copy(arry.elements, arry.elements + size, elements);
    }
    // assignment operator
    Array& operator = (const Array& arry)
    {
        cout << "Assignement operator called!" << endl;
        if(this != &arry)
        {
            cout << "Assigning!" << endl;
            delete[] elements;
            elements = new int[arry.size];
            size = arry.size;
            for(int i = 0; i < size; i++)
            {
                elements[i] = arry.elements[i];
            }
        }
        return *this;
    }
    // move constructor
    Array(Array&& arry)
    {
        cout << "Move constructor called!" << endl;
        size = arry.size;
        elements = arry.elements;
       // std::move(arry.elements, arry.elements + arry.size, elements);
        
        arry.elements = nullptr;
        arry.size = 0;
    }
    // Move assignment oeprator
    Array& operator =(Array&& arry)
    {
        cout << "Move assignment called!" << endl;
        if(this != &arry)
        {
            size = arry.size;
            elements = arry.elements;
            arry.elements = nullptr;
            arry.size = 0;
        }
        return *this;
    }
    // destructor
    ~Array()
    {
        if(elements)
        {
            delete[] elements;
        }
        
    }
    
    void printElements()
    {
        for(int i = 0; i < size; i++)
        {
            cout << elements[i] << " ";
        }
        cout << endl;
    }
};


int main()
{
    Array arry(20, 5);
    // call to copy constructor
    Array arryCopy(arry);
    cout << "Printing array copy: " << endl;
    arryCopy.printElements();
    
    Array orgArrayForAssignmentOperation(10, 7);
    cout << "Printig original array for assignment operation:" << endl;
    orgArrayForAssignmentOperation.printElements();
    orgArrayForAssignmentOperation = arry;
    cout << "Printig original array for assignment operation after assignment:" << endl;
    orgArrayForAssignmentOperation.printElements();
    
    cout << "Trying to assign the same object!" << endl;
    orgArrayForAssignmentOperation = orgArrayForAssignmentOperation;
    
    cout << "Calling move constructor" << endl;
    Array objectMovedToThis(std::move(orgArrayForAssignmentOperation));
    cout << "Printing the moved copy of the object" << endl;
    objectMovedToThis.printElements();
    
    cout << "Using move assignment operator to assigne!" << endl;
    Array assignedObject(5, 3);
    
    assignedObject = std::move(objectMovedToThis);
    assignedObject.printElements();
    
    cout << "Copy constructor will be called if object assigned to unconstructed object" << endl;
    Array copiedObject = assignedObject;
    copiedObject.printElements();

    cout << "Move constructor will be called if object assigned to unconstructed object using std::move" << endl;
    Array movedObject = std::move(assignedObject);
    movedObject.printElements();
}

