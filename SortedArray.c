//
//  SortedArray.c
//  
//

#include "SortedArray.h"
#include <assert.h>

/*
 * Assumptions
 * -----------
 *  The items are sorted
 *  Items will be non-NULL
 *  There are no duplicate items
 *  n_items will be > 0
 */

/* Validates if the given array is sorted or not
 * @param items     - pointer to the array
 * @param n_items   - no. of elements in the array
 * @param ascending - if the elements of the array are sorted in ascending order or not
 * @return int      - returns 1 if the elements are arranged in a sorted fashion else 0
 *                    returns -1 if the input is invalid
 */
static
int isSorted(const int* const items,
             const int n_items, const int ascending)
{
    if (items == NULL || n_items < 0) {
        return -1;
    }
    int low = (ascending) ? 0 : n_items - 1;
    int i, cnt;
    for (i = low, cnt = 0; cnt < n_items - 1; ++cnt) {
        int next = (ascending) ? i + 1 : i - 1;
        if (items[i] > items[next]) {
            return 0;
        }
        i = next;
    }
    return 1;
}

/* @brief Validates if the given sorted array includes duplicate elements or not
 * @param items   - pointer to the array
 * @param n_items - no. of elements in the array
 * @return int    - returns 1 if there are duplicates else 0
 *                  returns -1 if the input is invalid
 */
static
int hasDuplicates(const int* const items,
                   const int n_items, const int ascending)
{
    if (items == NULL || n_items < 0) {
        return -1;
    }
    if (!isSorted(items, n_items, ascending)) {
        return -1;
    }
    int low = (ascending) ? 0 : n_items - 1;
    int i, cnt;
    for (i = low, cnt = 0; cnt < n_items - 1; ++cnt) {
        int next = (ascending) ? i + 1 : i - 1;
        // In a sorted array, duplicates will co-exist
        if (items[i] == items[next]) {
            return 1;
        }
        i = next;
    }
    return 0;
}

/* @brief Checks if the given index is within the bounds of the array
 * @param index   - index of the array to be verified
 * @param n_items - no. of elements in the array
 * @return int    - returns 1 if the index is valid else 0
 *                  returns -1 if the input is invalid
 */
static
int isValid(const int index, const int n_items)
{
    if (n_items < 0) {
        return -1;
    }
    if (index < 0 || index >= n_items) {
        return 0;
    }
    return 1;
}

/* @brief This function performs a simple linear search on the given sorted array
 * based on the key and SearchType provided and returns the SearchResult
 * along with the index
 * @param items[in]      - Pointer to a sorted array
 * @param n_items[in]    - Size of the array
 * @param ascending[in]  - if the elements of the array are sorted in ascending order or not
 * @param key[in]        - the value to be searched for in the array
 * @param type[in]       - search type
 * @param index[out]     - index of the result once a match is found
 *                         returns -1 if no match is found, i.e @return == NotFound
 * @return SearchResult  - the value of the SearchResult based on the search
 */
SearchResult
Search(const int* const items,
       const int n_items,
       const int ascending,
       const int key,
       const SearchType type,
       int* index)
{
    assert(items != NULL);
    assert(n_items > 0);
    assert(isSorted(items, n_items, ascending));
    assert(hasDuplicates(items, n_items, ascending) == 0);
    
    //find the bounds of the array
    const int low = (ascending) ? 0 : n_items - 1;
    const int high = (ascending) ? n_items - 1 : 0;
    
    //Check if the result is likely to be in the array based on
    //the key and the type
    int inRange = 1;
    (*index) = -1; //clear the index
    
    switch (type) {
        case LessThan:
            if (key <= items[low]) {
                inRange = 0;
            }
            break;
        case LessThanEquals:
            if (key < items[low]) {
                inRange = 0;
            }
            break;
        case Equals:
            if (key < items[low] || key > items[high]) {
                inRange = 0;
            }
            break;
        case GreaterThanEquals:
            if (key > items[high]) {
                inRange = 0;
            }
            break;
        case GreaterThan:
            if (key >= items[high]) {
                inRange = 0;
            }
            break;
    }
    
    if (inRange == 0) {
        return NotFound;
    }
    
    int i, cnt;
    for (i = low, cnt = 0; cnt < n_items; ++cnt) {
        switch (type) {
            case LessThan:
                if (items[i] >= key) {
                    (*index) = (ascending) ? i - 1 : i + 1;
                    assert(isValid((*index), n_items));
                    return FoundLess;
                }
                break;
            case LessThanEquals:
                if (items[i] >= key) {
                    if (items[i] == key) {
                        (*index) = i;
                        return FoundExact;
                    } else {
                        (*index) = (ascending) ? i - 1 : i + 1;
                        assert(isValid((*index), n_items));
                        return FoundLess;
                    }
                }
                break;
            case Equals:
                if (items[i] == key) {
                    // index must be valid since items[i] was just accessed
                    (*index) = i;
                    return FoundExact;
                }
                break;
            case GreaterThanEquals:
                if (items[i] >= key) {
                    // index must be valid since items[i] was just accessed
                    (*index) = i;
                    if (items[(*index)] == key) {
                        return FoundExact;
                    } else {
                        return FoundGreater;
                    }
                }
                break;
            case GreaterThan:
                if (items[i] > key) {
                    // index must be valid since items[i] was just accessed
                    (*index) = i;
                    return FoundGreater;
                }
                break;
        }
        i = (ascending) ? i + 1 : i - 1;
    }
    
    if ((type == LessThan || type == LessThanEquals) &&
        key > items[high]) {
        (*index) = high;
        return FoundLess;
    } else {
        (*index) = -1;
    }
    return NotFound;
}
/**********************************************
 * Test code *
 *********************************************/
static void
testSearch(int* arr, int size, int ascending,
           int keys[NumSearchTypeEntries][NumSearchResultEntries],
           int indices[NumSearchTypeEntries][NumSearchResultEntries])
{
    if (arr == NULL || keys == NULL || indices == NULL || size <= 0) {
        return;
    }
    int index = -1;
    
    printf("Working on data set in %s order\n", (ascending) ? "ascending" : "descending");
    
    SearchResult res = Search(arr, size, ascending, keys[LessThan][FoundLess], LessThan, &index);
    assert(res == FoundLess);
    assert(index == indices[LessThan][FoundLess]);
    res = Search(arr, size, ascending, keys[LessThan][NotFound], LessThan, &index);
    assert(res == NotFound);
    assert(index == indices[LessThan][NotFound]);
    
    res = Search(arr, size, ascending, keys[LessThanEquals][FoundLess], LessThanEquals, &index);
    assert(res == FoundLess);
    assert(index == indices[LessThanEquals][FoundLess]);
    res = Search(arr, size, ascending, keys[LessThanEquals][FoundExact], LessThanEquals, &index);
    assert(res == FoundExact);
    assert(index == indices[LessThanEquals][FoundExact]);
    res = Search(arr, size, ascending, keys[LessThanEquals][NotFound], LessThanEquals, &index);
    assert(res == NotFound);
    assert(index == indices[LessThanEquals][NotFound]);
    
    res = Search(arr, size, ascending, keys[Equals][FoundExact], Equals, &index);
    assert(res == FoundExact);
    assert(index == indices[Equals][FoundExact]);
    res = Search(arr, size, ascending, keys[Equals][NotFound], Equals, &index);
    assert(res == NotFound);
    assert(index == indices[Equals][NotFound]);
    
    res = Search(arr, size, ascending, keys[GreaterThanEquals][FoundGreater] , GreaterThanEquals, &index);
    assert(res == FoundGreater);
    assert(index == indices[GreaterThanEquals][FoundGreater]);
    res = Search(arr, size, ascending, keys[GreaterThanEquals][FoundExact], GreaterThanEquals, &index);
    assert(res == FoundExact);
    assert(index == indices[GreaterThanEquals][FoundExact]);
    res = Search(arr, size, ascending, keys[GreaterThanEquals][NotFound], GreaterThanEquals, &index);
    assert(res == NotFound);
    assert(index == indices[GreaterThanEquals][NotFound]);
    
    res = Search(arr, size, ascending, keys[GreaterThan][FoundGreater], GreaterThan, &index);
    assert(res == FoundGreater);
    assert(index == indices[GreaterThan][FoundGreater]);
    res = Search(arr, size, ascending, keys[GreaterThan][NotFound], GreaterThan, &index);
    assert(res == NotFound);
    assert(index == indices[GreaterThan][NotFound]);
}

int main()
{
    printf("Working on testcase 1: Validating isSorted() function\n");
    //Testcase 1: test isSorted() function
    int arr[] = {0, 2, 4, 6, 8, 10};
    assert(isSorted(arr, sizeof(arr)/sizeof(arr[0]), 1));
    int arr_1[] = {0, 2, 4, 6, 7, 8, 7, 10};
    assert(isSorted(arr_1, sizeof(arr_1)/sizeof(arr_1[0]), 1) == 0);
    printf("Working on testcase 1: Validating isSorted() function: Completed successfully\n");
    
    //Testcase 2: test hasDuplicates() function
    printf("Working on testcase 2: Validating hasDuplicates() function\n");
    int arr_2[] = {2, 5, 11, 14, 15, 18, 19, 20};
    assert(hasDuplicates(arr_2, sizeof(arr_2)/sizeof(arr_2[0]), 1) == 0);
    assert(hasDuplicates(arr_1, sizeof(arr_1)/sizeof(arr_1[0]), 1) == -1);
    int arr_3[] = {21, 17, 13, 10, 9, 8 , 5, 5, 4, 3, 2, 0};
    assert(hasDuplicates(arr_3, sizeof(arr_3)/sizeof(arr_3[0]), 0) == 1);
    printf("Working on testcase 2: Validating hasDuplicates() function: Completed successfully\n");
    
    //Testcase 3: test isValid() function
    printf("Working on testcase 3: Validating isValid() function\n");
    assert(isValid(5, 6));
    assert(isValid(-1, 6) == 0);
    assert(isValid(0, 4));
    printf("Working on testcase 3: Validating isValid() function: Completed successfully\n");
    
    //Testcase 4: test Search() function with all different searchType and searchResult combinations
    printf("Working on testcase 4: Validating Search() function\n");
    int arr_a[] = {2, 5, 11, 14, 15, 18, 19, 20, 22, 25, 27, 28, 100};
    
    int keys_a[NumSearchTypeEntries][NumSearchResultEntries];
    int indices_a[NumSearchTypeEntries][NumSearchResultEntries];
    keys_a[LessThan][FoundLess] = 101;
    indices_a[LessThan][FoundLess] = 12;
    keys_a[LessThan][NotFound] = -1;
    indices_a[LessThan][NotFound] = -1;
    
    keys_a[LessThanEquals][FoundLess] = 99;
    indices_a[LessThanEquals][FoundLess] = 11;
    keys_a[LessThanEquals][FoundExact] = 100;
    indices_a[LessThanEquals][FoundExact] = 12;
    keys_a[LessThanEquals][NotFound] = 1;
    indices_a[LessThanEquals][NotFound] = -1;
    
    keys_a[Equals][FoundExact] = 25;
    indices_a[Equals][FoundExact] = 9;
    keys_a[Equals][NotFound] = 0;
    indices_a[Equals][NotFound] = -1;
    
    keys_a[GreaterThan][FoundGreater] = 19;
    indices_a[GreaterThan][FoundGreater] = 7;
    keys_a[GreaterThan][NotFound] = 100;
    indices_a[GreaterThan][NotFound] = -1;
    
    keys_a[GreaterThanEquals][FoundGreater] = 23;
    indices_a[GreaterThanEquals][FoundGreater] = 9;
    keys_a[GreaterThanEquals][FoundExact] = 100;
    indices_a[GreaterThanEquals][FoundExact] = 12;
    keys_a[GreaterThanEquals][NotFound] = 101;
    indices_a[GreaterThanEquals][NotFound] = -1;
    
    testSearch(arr_a, sizeof(arr_a)/sizeof(arr_a[0]), 1 /*ascending*/, keys_a, indices_a);
    printf("Working on testcase 4: Validating Search() function: Completed successfully\n");
    
    printf("Working on testcase 5: Validating Search() function\n");
    int arr_d[] = {33, 29, 28, 26, 21, 17, 13, 10, 9, 8 , 5, 4, 3, 2, 0};
    
    int keys_d[NumSearchTypeEntries][NumSearchResultEntries];
    int indices_d[NumSearchTypeEntries][NumSearchResultEntries];
    keys_d[LessThan][FoundLess] = 34;
    indices_d[LessThan][FoundLess] = 0;
    keys_d[LessThan][NotFound] = -2;
    indices_d[LessThan][NotFound] = -1;
    
    keys_d[LessThanEquals][FoundLess] = 30;
    indices_d[LessThanEquals][FoundLess] = 1;
    keys_d[LessThanEquals][FoundExact] = 21;
    indices_d[LessThanEquals][FoundExact] = 4;
    keys_d[LessThanEquals][NotFound] = -3;
    indices_d[LessThanEquals][NotFound] = -1;
    
    keys_d[Equals][FoundExact] = 10;
    indices_d[Equals][FoundExact] = 7;
    keys_d[Equals][NotFound] = 1;
    indices_d[Equals][NotFound] = -1;
    
    keys_d[GreaterThan][FoundGreater] = 19;
    indices_d[GreaterThan][FoundGreater] = 4;
    keys_d[GreaterThan][NotFound] = 50;
    indices_d[GreaterThan][NotFound] = -1;
    
    keys_d[GreaterThanEquals][FoundGreater] = 23;
    indices_d[GreaterThanEquals][FoundGreater] = 3;
    keys_d[GreaterThanEquals][FoundExact] = 13;
    indices_d[GreaterThanEquals][FoundExact] = 6;
    keys_d[GreaterThanEquals][NotFound] = 34;
    indices_d[GreaterThanEquals][NotFound] = -1;
    
    testSearch(arr_d, sizeof(arr_d)/sizeof(arr_d[0]), 0 /*descending*/, keys_d, indices_d);
    
    printf("Working on testcase 5: Validating Search() function: Completed successfully\n");
    
    return 0;
}

/* Regression Testing to be performed
 * 1. Memory consumption: Run valgrind or any other tool to make sure there aren't any leaks
 * 2. Behavior in multi-threaded systems: There are no data structures or anything shared, so should work fine
 * 3. Performance of the algorithm at run time: time complexity: O(n), space complexity: O(1) since the algorithm does not make
 * any allocations except for few local variables. Needs to be validated
 * 4. Performance needs to be evaluated for large no. of elements in the array and system under high load
 */


