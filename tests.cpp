/**
 *
 *
 * @author
 *   Donato Cianci
 */

#include <cstdlib>
#include <stdexcept>
#include <sstream>
#include <chrono>

void printMessage(std::string msg) {
  //Put error message you'd like to output here:

  std::cout << msg << std::endl << std::endl;
}

void merge_sort_tests() {
  std::cout << "Running tests of merge sort algorithm..." << std::endl << std::endl;

  List<int> List1, expected;

  List1.insertAtBack(5);
  List1.insertAtBack(6);
  List1.insertAtBack(1);
  List1.insertAtBack(7);
  List1.insertAtBack(5);
  List1.insertAtBack(-12);
  List1.insertAtBack(0);

  expected.insertAtBack(-12);
  expected.insertAtBack(0);
  expected.insertAtBack(1);
  expected.insertAtBack(5);
  expected.insertAtBack(5);
  expected.insertAtBack(6);
  expected.insertAtBack(7);


  std::cout << "Sorting List: " << List1 <<std::endl;
  std::cout << "Expecting: " << expected << std::endl;

  auto sorted = List1.mergeSort();

  std::cout << "Sorted List: " << sorted << std::endl;

  if (sorted != expected) printMessage("Warning: Bug in merge sort.");
  if (sorted == expected) printMessage("Success! Merge sort appears to be working properly.");


  printMessage("Running check on complexity...");

  constexpr int TEST_RUNS = 3;
  constexpr int SMALL_SIZE = 100;
  constexpr int MEDIUM_SIZE = 10000;
  constexpr int LARGE_SIZE = 10 * MEDIUM_SIZE;

  List<int> unsortedList1;
  for (int i = MEDIUM_SIZE; i>0; i-- ) {
    unsortedList1.insertAtFront(i);
    unsortedList1.insertAtBack(i);
  }

  List<int> unsortedList2;
  for (int i = LARGE_SIZE; i>0; i--) {
    unsortedList2.insertAtFront(i);
    unsortedList2.insertAtBack(i);
  }

  List<int> unsortedSmallList;
  List<int> sortedSmallList;
  for (int i = SMALL_SIZE; i>0; i--) {
    unsortedSmallList.insertAtFront(i);
    unsortedSmallList.insertAtBack(i);
    sortedSmallList.insertAtFront(i);
    sortedSmallList.insertAtFront(i);
  }

  auto testSort = unsortedSmallList.mergeSort();
  if (testSort != sortedSmallList) {
  printMessage("Warning: Bug in merge sort. Smaller list is not sorted correctly. Times may not be meaningful.");
  }

  {
    List<int> sortedList;
    auto tic = std::chrono::high_resolution_clock::now();
    for (int i=0; i<TEST_RUNS; i++) {
      sortedList = unsortedList1;
      sortedList = sortedList.mergeSort();
    }
    auto toc = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = toc - tic;

    std::cout << "Time elapsed: " << elapsed.count() << "ms" << std::endl;
  }
  {
    printMessage("Running merge sort on a list 10X the size of the previous list.");
    List<int> sortedList;
    auto tic = std::chrono::high_resolution_clock::now();
    for (int i=0; i<TEST_RUNS; i++) {
      sortedList = unsortedList2;
      sortedList = sortedList.mergeSort();
    }
    auto toc = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = toc - tic;

    std::cout << "Time elapsed: " << elapsed.count() << "ms" << std::endl;
    std::cout << std::endl << "Should see an elapsed time increase between 11X-13X, depending on"
    << std::endl << " the size of the list." << std::endl;
  }
}
