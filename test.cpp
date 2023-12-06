//STL
#include <vector>
#include <string>
#include <iostream>

//MSTL
#include <sorts.hh>
#include <sorts_2.hh>
#include <list.h>


template<typename T>
std::ostream& operator<<(std::ostream& stream, std::vector<T> vec)
{
    std::cout << "Vector<" << "..." << ">: {";
    
    typename std::vector<T>::iterator it = vec.begin();

    while ( it != vec.end() )
    {
        stream << *it++;

        if (it != vec.end())
        {
            stream << ", ";
        }
    }

    stream << "};\n";

    return stream;
}


template<>
std::ostream& operator<<(std::ostream& stream, std::vector<std::string> vec)
{
    std::cout << "Vector<" << "..." << ">: {";
    
    typename std::vector<std::string>::iterator it = vec.begin();

    while ( it != vec.end() )
    {

        stream <<"\"";
        stream << *it++;
        stream <<"\"";
        if (it != vec.end())
        {
            stream << ", ";
        }
    }

    stream << "};\n";

    return stream;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, mstd::List<T> vec)
{
    std::cout << "List<" << "..." << ">: {";
    
    for(int i = 0; i < vec.size(); ++i)
    {
        stream << vec[i];

        if (i != vec.size() - 1)
        {
            stream << ", ";
        }
    }

    stream << "};\n";

    return stream;
}

int main()
{
//Демонстрация работы со своими структурами данных
    mstd::List<int> abs = {3, 443, 123, 593, 1, 0 ,4, -1 , 4, 1};
    mstd::List<int> list = {-1, 0, 1, 1, 3, 4, 4, 123, 443, 593};
    
    std::cout << list;
    
    std::cout << "\n\n" << "Они: " << (abs == list) << "\n\n";
    std::cout << abs;
    std::cout << list;

//Работа совместно со стандартной библиотекой stl
    std::vector<std::string> strs = {"d23jisfd", "cadok", "ass", "cdo9e", "abijd", "zx", "adir"};
    std::vector<std::string> strs_good{"abijd", "adir", "ass", "cadok", "cdo9e", "d23jisfd", "zx"};
    
    sort::stats st = sort::quickSort(strs.begin(), strs.end());

    std::cout << "\n\n" << "Они: " << (strs == strs_good) << "\n\n";

    std::cout << strs;
    std::cout << strs_good;


    std::cout << st.comp_count << " ||TEST|| " << st.copy_count;
}