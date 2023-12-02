//STL
#include <vector>
#include <string>
#include <iostream>

//MSTL
#include <sorts.hh>
#include <sorts_2.hh>
#include <list.h>




// mstd::List< mstd::List<int> >   generate_100_massive(int size_massives)
// {
//     mstd::List< mstd::List<int> > arrays;

//     for(int i = 0; i < 100; ++i)
//     {
//         arrays.push_back( mstd::List<int>() );

//     }
// }

int main()
{

    mstd::List< mstd::List<int> > arrays;

    arrays.push_back( mstd::List<int>() );

    arrays[0].push_back(0);

    std::cout << arrays[0][0];

    return 0;
}