#include <vector>
#include <iostream>
#include <exception>
#include <chrono>
#include <iterator>
#include <string>

namespace mstd
{

//#Полезные функции
template<typename T>
inline void swapNative(T &first, T &second)
{
    T tmp(first);

    first = second;

    second = tmp;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, std::vector<T> vec)
{
    std::cout << "Vector<...>: (";
    
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

//#1

/**
 *  @brief  Select Sort for two iterators.
 *  @param  begin  First parametr for this function. This parametr = begin iterator. Doesn't use bad Iterator!
 * 
 *  @param  end  First parametr for this function. This parametr = end iterator. Doesn't use bad Iterator!
 */
template<class Iterator>
void bubbleSort(Iterator begin, Iterator end) 
{
    bool update;
    
    while(begin != end--) 
    {
        update = false;
        
        for(Iterator it = begin; it != end; ++it)
        {
            if(*it > *(it + 1))
            {
                swapNative(*it, *(it + 1));

                update = true;
            }
        }

        if (!update)
            break;
    }

}

/**
 *  @brief  Select Sort for two iterators.
 *  @param  begin  First parametr for this function. This parametr = begin iterator. Doesn't use bad Iterator!
 * 
 *  @param  end  First parametr for this function. This parametr = end iterator. Doesn't use bad Iterator!
 */
template<class Iterator>
void insertSort(Iterator begin, Iterator end)
{
    if (begin == end)
    {
        return;
    }

    for(Iterator it = begin + 1; it != end; ++it)
    {
        for(Iterator it2 = begin; it2 != it; ++it2)
        {
            if(*it2 > *(it))
            {
                swapNative(*it2, *(it));
            }
        }
    }
}

/**
 *  @brief  Select Sort for two iterators.
 *  @param  begin  First parametr for this function. This parametr = begin iterator. Doesn't use bad Iterator!
 * 
 *  @param  end  First parametr for this function. This parametr = end iterator. Doesn't use bad Iterator!
 */
template<class Iterator>
void selectSort(Iterator begin, Iterator end)
{
    Iterator it_min;
    
    for(Iterator it = begin; it != end - 1; ++it)
    {
        
        it_min = it;

        for(Iterator it2 = it + 1; it2 != end; ++it2)
        {
            if( *it_min > *it2 )
            {
                it_min = it2;
            }
        }

        swapNative(*it_min, *it);
    }
}

//#2


using t_size = int;

template<class Iterator>
inline t_size distance(Iterator begin, Iterator end)
{
    t_size count = 0;

    while(begin != end)
    {
        ++begin;
        ++count;
    }
    return count;
}

/**
 *  @brief  Shell Sort for two iterators.
 *  @param  begin  First parametr for this function. This parametr = begin iterator. Doesn't use bad Iterator!
 * 
 *  @param  end  First parametr for this function. This parametr = end iterator. Doesn't use bad Iterator!
 */
template<class Iterator>
void shellSort(Iterator begin, Iterator end)
{
    size_t length = mstd::distance(begin, end);
    size_t step = length / 2;

    while(step > 0)
    { 
        for (Iterator i = begin; i != end; ++i)
        {
            for (Iterator j = i; j >= begin + step && (*j < *(j - step)); j -= step)
            {
                mstd::swapNative(j, j - step);
            }
        }
        step /= 2;
    }
}

/**
 *  @brief  Cocktail/Sheker Sort for two iterators.
 *  @param  begin  First parametr for this function. This parametr = begin iterator. Doesn't use bad Iterator!
 * 
 *  @param  end  First parametr for this function. This parametr = end iterator. Doesn't use bad Iterator!
 */

template<class Iterator>
void cocktailSort(Iterator begin, Iterator end)
{
    for(--end; begin < end ; --end, ++begin)
    {
        for(Iterator it = begin; it < end; ++it)
            if( *(it + 1) < *it )
                swapNative(*(it+1), *it);

        for(Iterator it = end - 1; it > begin; --it)
            if(  *it < *(it - 1) )
                swapNative(*(it-1), *it);
    }
    
}

/**
 *  @brief  Quick Sort for two iterators.
 *  @param  begin  First parametr for this function. This parametr = begin iterator. Doesn't use bad Iterator!
 * 
 *  @param  end  First parametr for this function. This parametr = end iterator. Doesn't use bad Iterator!
 */
template<class Iterator>
void quickSort(Iterator begin, Iterator end)
{
    if (mstd::distance(begin, end) > 1)
    {
        Iterator left = begin;
        Iterator right = std::prev(end); 
        Iterator middle = begin + mstd::distance(begin, end) / 2 ;

        do
        {
            while (*left < *middle)
                ++left;
            while (*middle < *right)
                --right;

            if (left <= right)
            {
                swapNative(*left, *right);
                ++left;
                --right;
            }
        } while (left <= right);

        quickSort(begin, right);
        quickSort(left, end);
    }
}

//#3

}

// //Для реверсии операторов, если нужно
// bool operator<(const std::string& first, const std::string& second)
// {
//     return first > second;
// }


// bool operator>(const std::string& first, const std::string& second)
// {
//     return first < second;
// }


using namespace mstd;

int main()
{

    // std::vector<int> b = {7, 3, 5, 123, 3, 3 ,1, 0};

    // std::cout << "\nБыло: " << b;


    // auto start = std::chrono::high_resolution_clock::now();
    // cocktailSort( b.begin(), b.end());
    // auto end = std::chrono::high_resolution_clock::now();



    // std::cout << "\nСтало: " << b;

    // auto elapsed_seconds = end - start;

    // std::cout << "Затраченное время: " << elapsed_seconds.count() << "\n";


    std::vector<std::string> b = {"asdi", "sadio", "zasdi", "calka"};

    std::cout << "\nБыло: " << b;


    auto start = std::chrono::high_resolution_clock::now();
    cocktailSort( b.begin(), b.end());
    auto end = std::chrono::high_resolution_clock::now();



    std::cout << "\nСтало: " << b;

    auto elapsed_seconds = end - start;

    std::cout << "Затраченное время: " << elapsed_seconds.count() << "\n";
}