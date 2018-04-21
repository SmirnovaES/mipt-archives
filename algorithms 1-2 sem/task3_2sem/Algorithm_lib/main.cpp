#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>


int main() {
    //1
    int size = 1000;
    std::vector<int> vect(size);
    std::generate(vect.begin(), vect.end(), [](){
                                                return std::rand() % 100;
                                            });

    //2
    std::vector<int> vect_copy;
    std::copy(vect.begin(), vect.end(), back_inserter(vect_copy));

    //3
    std::random_shuffle(vect_copy.begin(), vect_copy.end() );



    //4
    std::sort(vect_copy.begin(), vect_copy.end(), [] (int left, int right) {
                                                        return left > right;
                                                    });


    //5
    std::reverse(vect_copy.begin(), vect_copy.end());

    //6
    int min = *std::min_element(vect.begin(), vect.end());
    assert(min == *(vect_copy.begin()));

    //7
    int max = *std::max_element(vect.begin(), vect.end());
    assert(max == *(--vect_copy.end()));

    //8
    std::vector<int> permutation(size);
    int count = 0;
    std::generate(permutation.begin(), permutation.end(), [&count](){
                                                                return count++;
                                                        });


    //9
    std::sort(permutation.begin(), permutation.end(), [&vect](int ind_1, int ind_2){
                                                            return vect[ind_1] < vect[ind_2];
                                                    });

    //10
    std::vector<int> sorted;
    std::transform(permutation.begin(), permutation.end(), back_inserter(sorted), [&vect] (int ind) {
                                                                                        return vect[ind];
                                                                                    });


    //11
    assert(std::is_sorted(sorted.begin(), sorted.end()));

    //12
    assert(std::mismatch(vect_copy.begin(), vect_copy.end(), sorted.begin()).first == vect_copy.end());

    //13
    int counts_size = 100;
    std::vector<int> counts(counts_size);
    std::generate(counts.begin(), counts.end(), [&vect, &sorted] () {
                                                    static int ind = 0;
                                                    //14
                                                    assert(std::count(vect.begin(), vect.end(), ind) == std::upper_bound(sorted.begin(), sorted.end(), ind) - std::lower_bound(sorted.begin(), sorted.end(), ind));
                                                    return std::count(vect.begin(), vect.end(), ind++);
                                                });


    //15
    int sum = 0;
    for (int i = 0; i < counts_size; i++) {
        sum += counts[i];
    }
    assert(sum == size);

    //16
    for (int i = 0; i < size; i++) {
        std::cout << sorted[i] << " ";
    }
    return 0;
}
