#include <iostream>
#include <string>
#include <sstream>
/*
    Author: @Juan Velazquez
    Class: CSCI 2380
You will see this a lot: (capacity + firstElement++) % capacity
it essentially works to give the index of the element even when firstElement is negative.
The reason I have it like this is because adding elements to the back is going right
and adding to the front goes to the left. Left is negative, and right is positive. I add
elements from the front to the back of the true size of the array, leaving space in between for
elements to get pushed back.
*/

using namespace std;

template <class T>
class stackQueue
{
private:
    //Actual array to store items
    T* items;
    //Maximum amount of elements
    int capacity;

    //To keep track of the amount of items in the array
    int numItems;
    //Tracks the first element
    int firstElement;
    //Tracks the lastElement
    int LastElement;

    //Make the structure larger
    void resize(int newCap)
    {
        //Step 1: Create a new (bigger) array of size newCap
        T* newArray;
        newArray = new T[newCap];

        //Step 2: copy value from old array over to the new array, but in order to keep
        //the array circular you need to move the first elements to the back of the new array
        for (int i = firstElement; i <= LastElement; i++)
        {
            newArray[(newCap + i) % newCap] = items[(capacity + i)%capacity];
        }

        //Step 3: set old capcity varible to newcapacity value
        capacity = newCap;

        //Step 3.5: take care of memory leak
        delete[] items;

        //Step 4: point items variable at the new array
        items = newArray;

    }

    void clear()
    {
        firstElement = 0;
        LastElement = 0;
        
    }

public:

    stackQueue()
    {
        items = new T[10];
        capacity = 10;
        numItems = 0;
        firstElement = 0;
        LastElement = 0;
    }

    //Insert x to the "back" of the list of items.
    void addBack(T x)
    {
        //RESIZE THE ARRAY BEFORE addBack
        if (numItems == capacity)
        {
            resize(2 * capacity);
        }

        //add the element after the last
        if (empty())
        {
            items[LastElement] = x;
        }
        else
        {
        items[++LastElement] = x;
        }

        numItems++;
    }

    //Add x to the "front" of the list of items.
    void addFront(T x)
    {
        if (numItems == capacity)
        {
            resize(2 * capacity);
        }

        if (empty())
        {
            items[(capacity + firstElement) % capacity] = x;
        }
        else
        {
            items[(capacity + --firstElement) % capacity] = x;
        }

        numItems++;
    }

    //Remove and return the item currently at the "back" of the list
    T removeBack()
    {
        //Write down value to be returned
        T output = items[LastElement--];

        //decrease item count by one
        numItems--;

        //in the case that this causes the array to be empty reset the stackqueue
        if (empty())
        {
            clear();
        }

        //return popped item
        return output;
    }

    //Remove and return the item currently at the "front" of the list
    T removeFront()
    {
        //get the value at index then increment down firstElement
        T output = items[(capacity + firstElement++) % capacity];

        numItems--;

        //in the case that this causes the array to be empty reset the stackqueue
        if (empty())
        {
            clear();
        }

        return output;
    }

    //Is the stackQueue empty?
    bool empty()
    {
        if (numItems == 0)
            return true;
        else
            return false;
    }

    void display()
    {
        //my implementation bugs out when the array is empty so this is why jankiness
        if (!empty())
        {
            string stream = "[ ";

            for (int i = firstElement; i <= LastElement; i++)
            {
                stream += stringulate(items[(capacity + i) % capacity]) + ", ";
            }

            stream.pop_back();
            stream.pop_back();

            stream += " ]";

            cout << stream << endl;
        }
        else
        {
            cout << "[]" << endl;
        }
    }
    //i'm using g++ and there is a bug with to_string, credit to @galik from stackoverflow
    template<typename ValueType>
    static string stringulate(ValueType v)
    {
        std::ostringstream oss;
        oss << v;
        return oss.str();
    }
};

int main()
{
    stackQueue <int> intStk;
    stackQueue <string> strStk;

    intStk.addBack(0);
    intStk.addBack(1);
    intStk.addFront(3);

    strStk.addBack("one");
    strStk.addBack("two");
    strStk.addFront("three");

    intStk.display();
    strStk.display();

    return 0;
}