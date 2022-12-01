#include <iostream>
#include <vector>

int main() {
    int d, K, alpha;
    std::cin >> d >> K >> alpha;

    if (d < 3 || K < 4) {
        std::cerr << "Prefix covering design is not valid because d should be at least 3 and K should be at least 4 by definition" << std::endl;
        return 0;
    }

    std::vector<std::vector<int>> prefix_covering_design(d); // prefix_covering_design[n] = nth sequence of this PCD
    std::vector<int> seq_len(d); // seq_len[n] = number of elements in nth sequence of this PCD
    std::vector<int> min_pos(K + 1, -1); // min_pos[val] = minimum level on which element val occurs
    std::vector<int> max_pos(K + 1, -1); // max_pos[val] = maximum level on which element val occurs
    std::vector<int> number_of_occurrences(K + 1, 0); // number_of_occurences[val] = in how many sequences element val is located
    for (int seq_ind = 0; seq_ind < d; seq_ind++) {
        std::cin >> seq_len[seq_ind]; // first given a number of elements in the sequence and then all sequence elements
        prefix_covering_design[seq_ind].resize(seq_len[seq_ind] + 1);
        for (int pos = 1; pos <= seq_len[seq_ind]; pos++) {
            int cur_elem;
            std::cin >> cur_elem;
            prefix_covering_design[seq_ind][pos] = cur_elem;
            if (cur_elem <= 0 || cur_elem > K) {
                std::cerr << "Prefix covering design is not valid because element " << cur_elem << " is outside of the [1, K] range" << std::endl;
                return 0;
            }
            if (min_pos[cur_elem] == -1 || min_pos[cur_elem] > pos) {
                min_pos[cur_elem] = pos;
            }
            if (max_pos[cur_elem] == -1 || max_pos[cur_elem] < pos) {
                max_pos[cur_elem] = pos;
            }
            number_of_occurrences[cur_elem]++;
        }
    }

    // check singleton condition
    for (int val = 1; val <= K; val++) {
        if (number_of_occurrences[val] == 0) {
            std::cerr << "Prefix covering design is not valid because element " << val << " does not occur in any sequence" << std::endl;
            return 0;
        }
        if (number_of_occurrences[val] >= 2 && min_pos[val] + max_pos[val] > alpha + 1) {
            std::cerr << "Prefix covering design is not valid because element " << val << " violates singleton condition" << std::endl;
            return 0;
        }
    }

    // check triplet condition
    for (int val1 = 1; val1 <= K; val1++) {
        for (int val2 = val1 + 1; val2 <= K; val2++) {
            for (int val3 = val2 + 1; val3 <= K; val3++) { // go through all triples of elements
                bool coverage_for_this_triple_exists = false;
                for (int seq1 = 0; seq1 < d; seq1++) {
                    for (int len1 = 0; len1 <= seq_len[seq1]; len1++) {
                        for (int seq2 = seq1 + 1; seq2 < d; seq2++) {
                            for (int len2 = 0; len2 <= seq_len[seq2]; len2++) {
                                for (int seq3 = seq2 + 1; seq3 < d; seq3++) {
                                    for (int len3 = 0; len3 <= seq_len[seq3]; len3++) { // go through all possible triples of prefixes
                                        if (len1 + len2 + len3 <= alpha) { // if sum of lengths of the prefixes is suitable for triplet condition
                                            bool val1_found = false;
                                            bool val2_found = false;
                                            bool val3_found = false;
                                            for (int i = 1; i <= len1; i++) {
                                                if (prefix_covering_design[seq1][i] == val1) {
                                                    val1_found = true;
                                                }
                                                if (prefix_covering_design[seq1][i] == val2) {
                                                    val2_found = true;
                                                }
                                                if (prefix_covering_design[seq1][i] == val3) {
                                                    val3_found = true;
                                                }
                                            }
                                            for (int i = 1; i <= len2; i++) {
                                                if (prefix_covering_design[seq2][i] == val1) {
                                                    val1_found = true;
                                                }
                                                if (prefix_covering_design[seq2][i] == val2) {
                                                    val2_found = true;
                                                }
                                                if (prefix_covering_design[seq2][i] == val3) {
                                                    val3_found = true;
                                                }
                                            }
                                            for (int i = 1; i <= len3; i++) {
                                                if (prefix_covering_design[seq3][i] == val1) {
                                                    val1_found = true;
                                                }
                                                if (prefix_covering_design[seq3][i] == val2) {
                                                    val2_found = true;
                                                }
                                                if (prefix_covering_design[seq3][i] == val3) {
                                                    val3_found = true;
                                                }
                                            }
                                            if (val1_found && val2_found && val3_found) { // if among s_{seq1}[...len1], s_{seq2}[...len2] and s_{seq3}[...len3] occur all val1, val2 and val3, triplet condition is met
                                                coverage_for_this_triple_exists = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (!coverage_for_this_triple_exists) {
                    std::cerr << "Prefix covering design is incorrect because for elements " << val1 << ", " << val2 << " and " << val3 << " triplet condition is not satisfied" << std::endl;
                    return 0;
                }
            }
        }
    }

    std::cout << "Prefix covering design is valid" << std::endl;
    return 0;
}

/*

Input for prefix covering design for d=4, K=40, alpha=21:

4 40 21
15 1 2 3 4 5 6 7 8 9 10 40 19 28 37 26
15 11 12 13 14 15 16 17 18 19 20 30 9 38 27 36
15 21 22 23 24 25 26 27 28 29 30 20 39 8 7 37
15 31 32 33 34 35 36 37 38 39 40 10 29 18 17 27




Input for prefix covering design for d=5, K=40, alpha=18:

5 40 18
13 1 2 3 4 5 6 7 8 24 31 38 30 14
13 9 10 11 12 13 14 15 16 32 40 6 31 22
13 17 18 19 20 21 22 23 24 8 7 39 15 30
13 25 26 27 28 29 30 31 32 40 16 23 39 6
12 33 34 35 36 37 38 39 40 16 32 15 23


*/
