// STL
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>

// MSTL
#include <sorts.hh>
#include <sorts_2.hh>
#include <list.h>

#include <random>
#include <chrono>

// Многопоточность
#include <thread>
#include <mutex>
std::mutex file_mutex;

std::vector<std::vector<int>> generate_100_massive(int size_massives, int count_massive)
{
    std::vector<std::vector<int>> arrays;

    // Генератор случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(0, 100);

    std::vector<int> tmp_list;

    for (int i = 0; i < count_massive; ++i)
    {
        for (int i = 0, random_number; i < size_massives; ++i)
        {
            random_number = distribution(gen);
            tmp_list.push_back(random_number);
        }
        arrays.push_back(tmp_list);
        tmp_list.clear();
    }

    return arrays;
}

std::vector<std::vector<int>> generate_100_massive_sort(int size_massives, int count_massive)
{
    std::vector<std::vector<int>> arrays;

    std::vector<int> tmp_list;

    for (int i = 0; i < count_massive; ++i)
    {
        for (int i = 0, random_number; i < size_massives; ++i)
        {
            tmp_list.push_back(i);
        }
        arrays.push_back(tmp_list);
        tmp_list.clear();
    }

    return arrays;
}

std::vector<std::vector<int>> generate_100_massive_sort_reserved(int size_massives, int count_massive)
{
    std::vector<std::vector<int>> arrays;

    std::vector<int> tmp_list;

    for (int i = 0; i < count_massive; ++i)
    {
        for (int i = 0, random_number; i < size_massives; ++i)
        {
            tmp_list.push_back(-i);
        }
        arrays.push_back(tmp_list);
        tmp_list.clear();
    }

    return arrays;
}


struct statistic
{
    long unsigned comp_count;
    long unsigned copy_count;
    long unsigned nanoseconds;

    statistic() : comp_count(0), copy_count(0), nanoseconds(0) {}
};

statistic measureTime(std::vector<int>::iterator begin, std::vector<int>::iterator end, sort::stats (*func)(std::vector<int>::iterator, std::vector<int>::iterator))
{
    statistic sta;

    auto startTime = std::chrono::steady_clock::now();

    sort::stats st = func(begin, end);

    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

    sta.comp_count = st.comp_count;

    sta.copy_count = st.copy_count;

    sta.nanoseconds = duration.count();

    return sta;
}

template <typename T>
std::ostream &operator<<(std::ostream &stream, std::vector<T> vec)
{
    std::cout << "Vector<"
              << "..."
              << ">: {";

    typename std::vector<T>::iterator it = vec.begin();

    while (it != vec.end())
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

enum functions
{
    bubble,
    insert,
    select_s,
    shell,
    cocktail,
    quick,
    comb,
    heap
};

sort::stats (*__select(functions choice))(std::vector<int>::iterator, std::vector<int>::iterator)
{
    switch (choice)
    {
    case bubble:
        return sort::bubbleSort;
    case insert:
        return sort::insertSort;
    case select_s:
        return sort::selectSort;
    case shell:
        return sort::shellSort;
    case cocktail:
        return sort::cocktailSort;
    case quick:
        return sort::quickSort;
    case comb:
        return sort::combSort;
    case heap:
        return sort::heapSort;
    default:
        throw mstd::exception("Use bad sort");
    }
}

const char *select_2(functions choice)
{
    switch (choice)
    {

    case bubble:
        return "bubble";
    case insert:
        return "insert";
    case select_s:
        return "select";
    case shell:
        return "shell";
    case cocktail:
        return "cocktail";
    case quick:
        return "quick";
    case comb:
        return "comb";
    case heap:
        return "heap";
    default:
        throw mstd::exception("Use bad sort");
    }
}


enum functions_generate
{
    randomchik,
    sortik,
    sort_reserved
};

const char *select_4(functions_generate choice)
{
    switch (choice)
    {

    case randomchik:
        return "_random.csv";

    case sortik:
        return "_sort.csv";

    case functions_generate::sort_reserved:
        return "_reserved.csv";

    default:
        throw mstd::exception("Use bad sort");
    }
}

std::vector<std::vector<int>> (*_select_3(functions_generate choice))(int, int)
{
    switch (choice)
    {
        case functions_generate::randomchik:
            return generate_100_massive;
        case functions_generate::sortik:
            return generate_100_massive_sort;
        case functions_generate::sort_reserved:
            return generate_100_massive_sort_reserved;
    default:
        throw mstd::exception("Use bad sort");
    }
}


void work(functions choice,functions_generate choice_2, int minSize = 100,  int maxSize = 5000, int step = 100, int count_massive = 20)
{

    sort::stats (*Sort)(std::vector<int>::iterator, std::vector<int>::iterator){__select(choice)};
    std::vector<std::vector<int>> (*func)(int, int){_select_3(choice_2)};
    

    std::string file_name(select_2(choice));

    file_name += select_4(choice_2);

    std::ofstream file(file_name.c_str());

    file << "Mass_Size,Copy_Count,Comp_Count,Time\n";

    const int numThreads = std::thread::hardware_concurrency();

    std::vector<std::thread> threads;

    for (int size_for_massive = minSize; size_for_massive <= maxSize; size_for_massive += step)
    {
        threads.clear();
        std::vector<std::vector<int>> arrays_random = func(size_for_massive, count_massive);

        for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([&, i]() {
            
            for (int j = i; j < arrays_random.size(); j+=numThreads)
            {
                std::vector<int> array = arrays_random[j];
                statistic stats = measureTime(array.begin(), array.end(), Sort);
                std::lock_guard<std::mutex> lock(file_mutex);
                file << size_for_massive << ',' << stats.copy_count << ',' << stats.comp_count << ',' << stats.nanoseconds << '\n';
            }
        });
        }

        for (auto& thread : threads) {
            thread.join();
        }
        
        // if (size_for_massive == 10000)
        // {
        //     size_for_massive = 24000;
        // }
        // if (size_for_massive == 25000 || size_for_massive == 50000)
        // {
        //     size_for_massive = size_for_massive * 2 - 1000;
        // }
        
    }

    file.close();

}

int main()
{
// // //Меняем bubble
    
//     work(bubble, sortik);

//     work(bubble, randomchik);

//     work(bubble, sort_reserved);

// // //Меняем quick 
//     work(quick, sortik);

//     work(quick, randomchik);

//     work(quick, sort_reserved);

// // //Меняем heap
//     work(heap, sortik);

//     work(heap, randomchik);

//     work(heap, sort_reserved);

// //Меняем comb
        
//     work(functions::comb, randomchik);

//     work(comb, sort_reserved);

// // cocktail
//     work(cocktail, sortik);

//     work(cocktail, randomchik);

//     work(cocktail, sort_reserved);

// //shell
//     work(shell, sortik);

//     work(shell, randomchik);

//     work(shell, sort_reserved); 

// //select
//     work(select_s, sortik);

//     work(select_s, randomchik);

//     work(select_s, sort_reserved); 

// //insert
//     work(insert, sortik);

//     work(insert, randomchik);

//     work(insert, sort_reserved); 


}