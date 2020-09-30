#include "sequentialsort.h"

void sequentialSort(int* first, int* last)
{
    std::list<int> result_list(first, last + 1);
    for (int order_mask = 1; order_mask < 1000000; order_mask *= 10)
    {
        std::vector<std::list<int>> state_vector(10);
        for (auto value : result_list)
        {
            int index = abs(value / order_mask) % 10;
            state_vector[index].push_back(value);
        }
        result_list.clear();
        for (auto list : state_vector)
        {
            result_list.splice(result_list.end(), list);
        }
    }
    int* i = first;
    auto j = result_list.begin();
    for (; i <= last, j != result_list.end(); i++, j++)
    {
        *i = *j;
    }
}