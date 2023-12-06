#ifndef __SORTS_2_HH__
#define __SORTS_2_HH__
#include <iterator>

namespace sort
{

    struct stats
    {
        std::size_t comp_count;
        std::size_t copy_count;

        stats(): comp_count(0), copy_count(0){}

        stats& operator+=( const stats& other)
        {
            this->comp_count += other.comp_count;

            this->copy_count += other.copy_count;

            return *this; 
        }
    };

    // #Полезные функции

    template <typename T>
    inline void swapNative(T &first, T &second, stats& st)
    {
        T tmp(first);

        first = second;

        second = tmp;

        st.copy_count += 1;
    }

    // #1

    /**
     *  @brief  Select Sort for two iterators.
     *  @param  begin  First parametr for this function. This parametr = begin iterator. Doesn't use bad Iterator!
     *
     *  @param  end  First parametr for this function. This parametr = end iterator. Doesn't use bad Iterator!
     */
    template <class Iterator>
    stats bubbleSort(Iterator begin, Iterator end)
    {
        stats st;

        bool update;

        while (begin != end--)
        {
            update = false;

            for (Iterator it = begin; it != end; ++it)
            {
                st.comp_count += 1;
                if (*it > *(it + 1))
                {

                    swapNative(*it, *(it + 1), st);

                    update = true;
                }
            }

            if (!update)
                break;
        }

        return st;
    }

    /**
     *  @brief  Select Sort for two iterators.
     *  @param  begin  First parametr for this function. This parametr = begin iterator. Doesn't use bad Iterator!
     *
     *  @param  end  First parametr for this function. This parametr = end iterator. Doesn't use bad Iterator!
     */
    template <class Iterator>
    stats insertSort(Iterator begin, Iterator end)
    {
        stats st;
        if (begin == end)
        {
            return st;
        }
        

        for (Iterator it = begin + 1; it != end; ++it)
        {
            for (Iterator it2 = begin; it2 != it; ++it2)
            {
                st.comp_count += 1;
                if (*it2 > *(it))
                {
                    swapNative(*it2, *it, st);
                }
            }
        }
        return st;
    }

    /**
     *  @brief  Select Sort for two iterators.
     *  @param  begin  First parametr for this function. This parametr = begin iterator. Doesn't use bad Iterator!
     *
     *  @param  end  First parametr for this function. This parametr = end iterator. Doesn't use bad Iterator!
     */
    template <class Iterator>
    stats selectSort(Iterator begin, Iterator end)
    {
        Iterator it_min;
        stats st;
        for (Iterator it = begin; it != end - 1; ++it)
        {

            it_min = it;

            for (Iterator it2 = it + 1; it2 != end; ++it2)
            {
                st.comp_count += 1;   
                if (*it_min > *it2)
                {
                    it_min = it2;
                }
            }

            swapNative(*it_min, *it, st);
        }
        return st;
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
    stats shellSort(Iterator begin, Iterator end)
    {
        size_t length = sort::distance(begin, end);
        size_t step = length / 2;

        stats st;

        while (step > 0)
        {
            for (Iterator i = begin; i != end; ++i)
            {
                for (Iterator j = i; j >= begin + step && (*j < *(j - step)); j -= step)
                {
                    ++st.comp_count;
                    sort::swapNative(*j, *(j - step), st);
                }
            }
            step /= 2;
        }
        return st;
    }

    /**
     *  @brief  Cocktail/Sheker Sort for two iterators.
     *  @param  begin  First parametr for this function. This parametr = begin iterator. Doesn't use bad Iterator!
     *
     *  @param  end  First parametr for this function. This parametr = end iterator. Doesn't use bad Iterator!
     */
    template <class Iterator>
    stats cocktailSort(Iterator begin, Iterator end)
    {
        stats st;
        for (--end; begin < end; --end, ++begin)
        {
            for (Iterator it = begin; it < end; ++it)
            {
                ++st.comp_count;
                if (*(it + 1) < *it)
                {
                    swapNative(*(it + 1), *it, st);
                }
            }
            for (Iterator it = end - 1; it > begin; --it)
            {
                ++st.comp_count;
                if (*it < *(it - 1))
                {
                    swapNative(*(it - 1), *it, st);
                }
            }
        }
        return st;
    }

    /**
     *  @brief  Quick Sort for two iterators.
     *  @param  begin  First parametr for this function. This parametr = begin iterator. Doesn't use bad Iterator!
     *
     *  @param  end  First parametr for this function. This parametr = end iterator. Doesn't use bad Iterator!
     */
    template <typename Iterator>
    stats quickSort(Iterator first, Iterator last)
    {
        stats st;
        if (first != last)
        {
            Iterator left = first;
            Iterator right = last;
            Iterator pivot = left++;
            while (left != right)
            {
                ++st.comp_count;
                if (*left < *pivot)
                {
                    ++left;
                }
                else
                {
                    while ((left != --right) && (*pivot < *right))
                        ;
                    sort::swapNative(*left, *right, st);
                }
            }
            --left;
            sort::swapNative(*first, *left, st);
            st += sort::quickSort(first, left);
            st += sort::quickSort(right, last);
        }

        return st;
    }

    // #3

    /**
     *  @brief  Comb Sort for two iterators.
     *  @param  begin  First parametr for this function. This parametr = begin iterator. Doesn't use bad Iterator!
     *
     *  @param  end  First parametr for this function. This parametr = end iterator. Doesn't use bad Iterator!
     */
    template <class Iterator>
    stats combSort(Iterator begin, Iterator end)
    {
        stats st;

        size_t step = sort::distance(begin, end);

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
                ++st.comp_count;
                if (*(begin + (i - step)) > *(begin + i))
                {
                    swapNative(*(begin + (i - step)), *(begin + i), st);
                    isSort = false;
                }
            }
        }
        return st;
    }

    template <class Iterator>
    stats heapify(Iterator begin, int N, int i, stats& st)
    {   

        int largest = i;

        int l = 2 * i + 1;

        int r = 2 * i + 2;

        st.comp_count+=3;

        if (l<N &&*(begin + l)> * (begin + largest))
            largest = l;

        if (r<N &&*(begin + r)> * (begin + largest))
            largest = r;

        if (largest != i)
        {
            swapNative(*(begin + i), *(begin + largest), st);

            heapify(begin, N, largest,st);
        }

        return st;
    }

    /**
     *  @brief  Heap Sort for two iterators.
     *  @param  begin  First parametr for this function. This parametr = begin iterator. Doesn't use bad Iterator!
     *
     *  @param  end  First parametr for this function. This parametr = end iterator. Doesn't use bad Iterator!
     */
    template <class Iterator>
    stats heapSort(Iterator begin, Iterator end)
    {

        stats st;

        int N = std::distance(begin, end);

        if (N == 0 || N == 1)
        {
            return st;
        }

        for (int i = N / 2 - 1; i >= 0; i--)
            heapify(begin, N, i, st);

        for (int i = N - 1; i > 0; i--)
        {
            swapNative(*begin, *(begin + i), st);

            heapify(begin, i, 0, st);
        }
        return st;
    }


}

#endif