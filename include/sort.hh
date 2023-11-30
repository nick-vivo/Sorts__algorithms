#ifndef __SORTS_HH__
#define __SORTS_HH__
#include <iterator>
namespace mstd
{

    // #Полезные функции

    template <typename T>
    inline void swapNative(T &first, T &second)
    {
        T tmp(first);

        first = second;

        second = tmp;
    }

    // #1

    /**
     *  @brief  Select Sort for two iterators.
     *  @param  begin  First parametr for this function. This parametr = begin iterator. Doesn't use bad Iterator!
     *
     *  @param  end  First parametr for this function. This parametr = end iterator. Doesn't use bad Iterator!
     */
    template <class Iterator>
    void bubbleSort(Iterator begin, Iterator end)
    {
        bool update;

        while (begin != end--)
        {
            update = false;

            for (Iterator it = begin; it != end; ++it)
            {
                if (*it > *(it + 1))
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
    template <class Iterator>
    void insertSort(Iterator begin, Iterator end)
    {
        if (begin == end)
        {
            return;
        }

        for (Iterator it = begin + 1; it != end; ++it)
        {
            for (Iterator it2 = begin; it2 != it; ++it2)
            {
                if (*it2 > *(it))
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
    template <class Iterator>
    void selectSort(Iterator begin, Iterator end)
    {
        Iterator it_min;

        for (Iterator it = begin; it != end - 1; ++it)
        {

            it_min = it;

            for (Iterator it2 = it + 1; it2 != end; ++it2)
            {
                if (*it_min > *it2)
                {
                    it_min = it2;
                }
            }

            swapNative(*it_min, *it);
        }
    }

    // #2

    using size_t = long int;

    template <class Iterator>
    inline size_t distance(Iterator begin, Iterator end)
    {
        size_t count = 0;

        while (begin != end)
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
    template <class Iterator>
    void shellSort(Iterator begin, Iterator end)
    {
        size_t length = mstd::distance(begin, end);
        size_t step = length / 2;

        while (step > 0)
        {
            for (Iterator i = begin; i != end; ++i)
            {
                for (Iterator j = i; j >= begin + step && (*j < *(j - step)); j -= step)
                {
                    mstd::swapNative(*j, *(j - step));
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
    template <class Iterator>
    void cocktailSort(Iterator begin, Iterator end)
    {
        for (--end; begin < end; --end, ++begin)
        {
            for (Iterator it = begin; it < end; ++it)
                if (*(it + 1) < *it)
                    swapNative(*(it + 1), *it);

            for (Iterator it = end - 1; it > begin; --it)
                if (*it < *(it - 1))
                    swapNative(*(it - 1), *it);
        }
    }

    /**
     *  @brief  Quick Sort for two iterators.
     *  @param  begin  First parametr for this function. This parametr = begin iterator. Doesn't use bad Iterator!
     *
     *  @param  end  First parametr for this function. This parametr = end iterator. Doesn't use bad Iterator!
     */
    template <typename Iterator>
    void quick_sort(Iterator first, Iterator last)
    {
        if (first != last)
        {
            Iterator left = first;
            Iterator right = last;
            Iterator pivot = left++;
            while (left != right)
            {
                if (*left < *pivot)
                {
                    ++left;
                }
                else
                {
                    while ((left != --right) && (*pivot < *right))
                        ;
                    mstd::swapNative(*left, *right);
                }
            }
            --left;
            mstd::swapNative(*first, *left);
            quick_sort(first, left);
            quick_sort(right, last);
        }
    }

    // #3

    /**
     *  @brief  Comb Sort for two iterators.
     *  @param  begin  First parametr for this function. This parametr = begin iterator. Doesn't use bad Iterator!
     *
     *  @param  end  First parametr for this function. This parametr = end iterator. Doesn't use bad Iterator!
     */
    template <class Iterator>
    void combSort(Iterator begin, Iterator end)
    {
        size_t step = mstd::distance(begin, end);

        size_t size = step;

        bool isSort = true;

        while (step > 1 || isSort)
        {

            if (step > 1)
            {
                step /= 1.247330950103979;
            }

            isSort = true;

            for (size_t i = step; i < size; ++i)
            {
                if (*(begin + (i - step)) > *(begin + i))
                {
                    swapNative(*(begin + (i - step)), *(begin + i));
                    isSort = false;
                }
            }
        }
    }

    /**
     *  @brief  Heap Sort for two iterators.
     *  @param  begin  First parametr for this function. This parametr = begin iterator. Doesn't use bad Iterator!
     *
     *  @param  end  First parametr for this function. This parametr = end iterator. Doesn't use bad Iterator!
     */
    template <class Iterator>
    void heapSort(Iterator begin, Iterator end)
    {
        size_t step = mstd::distance(begin, end);

        size_t size = step;

        bool isSort = true;

        while (step > 1 || isSort)
        {

            if (step > 1)
            {
                step /= 1.247330950103979;
            }

            isSort = true;

            for (size_t i = step; i < size; ++i)
            {
                if (*(begin + (i - step)) > *(begin + i))
                {
                    swapNative(*(begin + (i - step)), *(begin + i));
                    isSort = false;
                }
            }
        }
    }

}

#endif