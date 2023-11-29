#include "./include/Sorts.cpp"
#include <vector>
#include <string>
#include <iostream>

int main()
{

    std::vector<std::string> abs = {"asdaos", "Asdu", "djujfi", "zxcq", "asiodj"};
    
    mstd::shellSort(abs.begin(), abs.end());

    std::cout << abs;
}