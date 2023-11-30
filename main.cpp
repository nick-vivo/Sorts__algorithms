#include <vector>
#include <string>
#include <iostream>
#include <sort.hh>
#include <list.h>
#include <memory.h>

template<typename T>
std::ostream& operator<<(std::ostream& stream, std::vector<T> vec)
{
    std::cout << "Vector<" << "..." << ">: (";
    
    typename std::vector<T>::iterator it = vec.begin();

    while ( it != vec.end() )
    {
        stream << *it++;

        if (it != vec.end())
        {
            stream << ", ";
        }
    }

    stream << ");\n";

    return stream;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, mstd::List<T> vec)
{
    std::cout << "List<" << "..." << ">: (";
    
    mstd::Iterator it = vec.begin();

    while ( it != vec.end() )
    {
        stream << *it++;

        if (it != vec.end())
        {
            stream << ", ";
        }
    }

    stream << ");\n";

    return stream;
}

int main()
{


    mstd::List<int> abs = {3, 443, 123, 593, 1, 0 ,4, -1 , 4};
    
    mstd::quick_sort(abs.begin(), abs.end());



    std::cout << abs;
}