#include <vector>

void shuffle(std::vector<int> &list, int size = 0) {
    if( size <= 0 )
        size = list.size();
    else
        list.resize(size);
    
    for( int i = 0; i < size; i ++ )
        list[i] = i;
    for( int i = size - 1; i > 0; i -- ) {
        int j   = rand() % (i + 1);
        int t   = list[i];
        list[i] = list[j];
        list[j] = t;
    }
}