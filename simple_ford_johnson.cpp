#include <iostream>
#include <vector>
#include <algorithm>
#include <utility> // For std::pair

// --- Helper Function to Print Vectors ---
void printVector(const std::string& name, const std::vector<int>& vec) {
    std::cout << name << ":\t";
    for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// --- Comparison function for sorting pairs by their first element (the winner) ---
bool comparePairs(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return a.first < b.first;
}

// --- The Ford-Johnson Merge-Insertion Sort Algorithm ---
void mergeInsertionSort(std::vector<int>& arr) {
    if (arr.size() <= 1) {
        return; // Already sorted
    }

    // --- Step 1: Pair elements and identify winners/losers ---
    std::vector< std::pair<int, int> > pairs;
    int leftover = -1;
    bool hasLeftover = (arr.size() % 2 != 0);

    for (size_t i = 0; i + 1 < arr.size(); i += 2) {
        if (arr[i] > arr[i+1]) {
            pairs.push_back(std::make_pair(arr[i], arr[i+1]));
        } else {
            pairs.push_back(std::make_pair(arr[i+1], arr[i]));
        }
    }
    if (hasLeftover) {
        leftover = arr.back();
    }

    // --- Step 2: Sort the pairs based on the 'winner' element ---
    std::sort(pairs.begin(), pairs.end(), comparePairs);

    // --- Step 3: Create the main chain and the pending list ---
    std::vector<int> mainChain;
    std::vector<int> pending;
    for (size_t i = 0; i < pairs.size(); ++i) {
        mainChain.push_back(pairs[i].first);  // Winners form the initial sorted chain
        pending.push_back(pairs[i].second); // Losers are waiting to be inserted
    }

    // --- Step 4: Insert the pending elements into the main chain ---
    // The mainChain is always sorted, so binary search (lower_bound) is valid.

    // Insert the first loser, which we know belongs before the first winner.
    if (!pending.empty()) {
        mainChain.insert(mainChain.begin(), pending[0]);
    }

    // Insert the rest of the pending elements.
    // Note: A true Ford-Johnson uses a more complex insertion order (Jacobsthal numbers)
    // for optimal performance. This version uses a simpler linear order for clarity.
    for (size_t i = 1; i < pending.size(); ++i) {
        std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), pending[i]);
        mainChain.insert(pos, pending[i]);
    }

    // Insert the leftover element if it exists.
    if (hasLeftover) {
        std::vector<int>::iterator pos = std::lower_bound(mainChain.begin(), mainChain.end(), leftover);
        mainChain.insert(pos, leftover);
    }

    // The sort is complete, copy the result back to the original vector.
    arr = mainChain;
}

// --- Main Function to Test the Sort ---
int main() {
    int my_ints[] = {7, 3, 9, 2, 6, 8, 1, 5, 4};
    std::vector<int> data(my_ints, my_ints + sizeof(my_ints) / sizeof(int));

    std::cout << "Classic Ford-Johnson (Merge-Insertion) Sort" << std::endl;
    printVector("Before", data);

    mergeInsertionSort(data);

    printVector("After", data);

    return 0;
}