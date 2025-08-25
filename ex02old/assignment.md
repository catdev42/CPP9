Of course. Here is the assignment formatted for clarity.

***

## Exercise 02: PmergeMe

### Project Details
*   **Files to turn in:** `Makefile`, `main.cpp`, `PmergeMe.cpp`, `PmergeMe.hpp`
*   **Turn-in directory:** ex02
*   **Forbidden functions:** None

### Program Constraints
*   The name of the program must be `PmergeMe`.
*   Your program must accept a positive integer sequence as command-line arguments.
*   Your program must use the **merge-insert sort algorithm** (also known as the **Ford-Johnson algorithm**) to sort the sequence.
*   If an error occurs (e.g., invalid input), an error message must be displayed on the standard error.
*   You must use at least **two different container types** to implement the sort. It is strongly advised to implement the algorithm for each container separately, avoiding a single generic function.
*   Your program must be able to handle at least 3000 different integers.

### Required Output
You must display the following information line-by-line on the standard output:

1.  **First line:** An explicit text followed by the unsorted positive integer sequence.
    *   Example: `Before: 3 5 9 7 4`
2.  **Second line:** An explicit text followed by the sorted positive integer sequence.
    *   Example: `After: 3 4 5 7 9`
3.  **Third line:** A message indicating the time taken by your algorithm using the **first container**.
    *   Example: `Time to process a range of 5 elements with std::vector : 0.00031 us`
4.  **Fourth line:** A message indicating the time taken by your algorithm using the **second container**.
    *   Example: `Time to process a range of 5 elements with std::deque : 0.00014 us`

The time format is flexible, but the precision must be sufficient to show a clear difference between the two containers. The time measured should include all operations (data management and sorting).

### Usage Examples

**Standard Use:**
````shell
$> ./PmergeMe 3 5 9 7 4
Before: 3 5 9 7 4
After:  3 4 5 7 9
Time to process a range of 5 elements with std::[..] : 0.00031 us
Time to process a range of 5 elements with std::[..] : 0.00014 us
````

**Large Input (Linux):**
````shell
$> ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
Before: 141 79 526 321 [...]
After:  79 141 321 526 [...]
Time to process a range of 3000 elements with std::[..] : 62.14389 us
Time to process a range of 3000 elements with std::[..] : 69.27212 us
````

**Large Input (macOS):**
````shell
$> ./PmergeMe `jot -r 3000 1 100000 | tr '\n' ' '`
[...]
````

**Error Handling:**
````shell
$> ./PmergeMe "-1" "2"
Error
````

Similar code found with 1 license type