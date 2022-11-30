#include <iostream>
#include <vector>
#include <set>

int main() {
    int d, v, k;
    std::cin >> d >> v >> k;
    if (v % d != 0) {
        std::cerr << "Construction is not suitable because v is not divisible by d" << std::endl;
        return 0;
    }

    std::vector<std::vector<int>> elements_of_blocks(d, std::vector<int>(k)); // elements_of_blocks[n] = nth block of covering design
    std::vector<std::vector<int>> blocks_for_elements(v + 1); // blocks_for_elements[a] = indices of blocks where element a is located
    for (int block_ind = 0; block_ind < d; block_ind++) {
        for (int pos = 0; pos < k; pos++) {
            std::cin >> elements_of_blocks[block_ind][pos];
            if (elements_of_blocks[block_ind][pos] <= 0 || elements_of_blocks[block_ind][pos] > v) {
                std::cerr << "Covering design is not valid because element " << elements_of_blocks[block_ind][pos] << " is outside of the [1, v] range" << std::endl;
                return 0;
            }
            blocks_for_elements[elements_of_blocks[block_ind][pos]].push_back(block_ind);
        }
    }

    for (int a = 1; a <= v; a++) {
        for (int b = a + 1; b <= v; b++) { // for every pair of elements check that there exists a sequence where both of them are located
            bool a_and_b_are_located_in_one_sequence = false;
            for (int aseq : blocks_for_elements[a]) {
                for (int bseq : blocks_for_elements[b]) { // go through sequences where a is located and sequences where b is located and check for a common one
                    if (aseq == bseq) {
                        a_and_b_are_located_in_one_sequence = true;
                    }
                }
            }
            if (!a_and_b_are_located_in_one_sequence) {
                std::cerr << "Covering design is not valid because elements " << a << " and " << b << " do not occur in the same sequence" << std::endl;
                return 0;
            }
        }
    }

    int v_prime = v / d;
    std::set<int> elements_from_first_v_prime_levels;
    for (int seq_ind = 0; seq_ind < d; seq_ind++) {
        for (int pos = 0; pos < v_prime; pos++) {
            elements_from_first_v_prime_levels.insert(elements_of_blocks[seq_ind][pos]); // collect all elements from the first v' levels
        }
    }
    if (static_cast<int>(elements_from_first_v_prime_levels.size()) < v) { // if not all elements from first v' levels are distinct
        std::cerr << "Covering design is not valid because first v/d elements from all sequences do not create a multimatching" << std::endl;
    }

    std::cout << "Covering design is valid" << std::endl;
    return 0;
}

/*

Input example for covering design with d=7, v=7, k=3:

7 7 3
1 2 3
4 1 5
6 1 7
2 4 6
5 2 7
7 3 4
3 5 6

*/
