#include <iostream>
#include <string>
#include <sstream>
/*
You will see this a lot: (capacity + firstElement++) % capacity
it essentially works to give the index of the element even when firstElement is negative.
The reason I have it like this is because adding elements to the back is going right
and adding to the front goes to the left. Left is negative, and right is positive. I add
elements from the front to the back of the true size of the array, leaving space in between for
elements to get pushed back.
*/

using namespace std;

//template <class T>
class stackQueue
{
private:
    //Actual array to store items
    int* items;
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
        int* newArray;
        newArray = new int[newCap];

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

public:

    stackQueue()
    {
        items = new int[10];
        capacity = 10;
        numItems = 0;
        firstElement = 0;
        LastElement = 0;
    }
    //i'm using g++ and there is a bug with to_string, credit to @galik from stackoverflow
    template<typename ValueType>
    static string stringulate(ValueType v)
    {
        std::ostringstream oss;
        oss << v;
        return oss.str();
    }

    //Insert x to the "back" of the list of items.
    void addBack(int x)
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
    void addFront(int x)
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
    int removeBack()
    {
        //Write down value to be returned
        int output = items[LastElement--];

        //decrease item count by one
        numItems--;

        //return popped item
        return output;
    }

    //Remove and return the item currently at the "front" of the list
    int removeFront()
    {
        //get the value at index then increment down firstElement
        int output = items[(capacity + firstElement++) % capacity];

        numItems--;

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
};

int main()
{
    stackQueue S;

    S.addFront(1);
    S.addFront(2);
    S.addFront(3);
    S.addBack(4);
    S.addBack(5);
    S.addBack(6);
    S.addFront(7);
    S.addFront(8);
    S.addFront(9);
    S.addBack(10);

    S.display();


    for (int i = 0; i < 5; i++)
    {
        cout << S.removeBack() << "\t";
    }
    cout << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << S.removeFront() << "\t";
    }
    cout << endl;

    S.display();

    S.addBack(1);
    S.addBack(2);
    S.addBack(3);
    S.addFront(4);
    S.addFront(5);
    S.addFront(6);
    S.addBack(7);
    S.addBack(8);
    S.addBack(9);
    S.addFront(10);

    S.display();


    return 0;
}