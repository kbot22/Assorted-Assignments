/*
Written by Kaleb M. LuceWireman with help from zylabs.

Class: CS3350 1002

The purpose of this program is to compare different
sorting algorithms by using the number of comparisons
and movement that each one uses on the same
10000 strings in an array.

*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;



// all function definitions (there are a lot)
void CopyArray(string* OrigArray, string* CopyArray, int arraySize);

// all functions related to sorting
void SelectionSort(string* numbers, int numbersSize, int& comparisons, int& movements);
void InsertionSort(string* numbers, int numbersSize, int& comparisons, int& movements);
void BubbleSort(string* numbers, int numbersSize, int& comparisons, int& movements);
void Quicksort(string* numbers, int startIndex, int endIndex, int& comparisons, int& movements);
int Partition(string* numbers, int startIndex, int endIndex, int& comparisons, int& movements);
void Merge(string* numbers, int leftFirst, int leftLast, int rightLast, int& comparisons, int& movements);
void MergeSort(string* numbers, int startIndex, int endIndex, int& comparisons, int& movements);




int main(){

// defining variables
const int DEFAULT_ARRAY_SIZE = 10000;
fstream passwords;
string passArray[DEFAULT_ARRAY_SIZE];
string refArray[DEFAULT_ARRAY_SIZE];
int comparisons = 0;
int movements = 0;


//open file
passwords.open("Passwords.txt");


// check if file is opened
if(!(passwords.is_open())){
    cout << "couldn't open file";
    return 1;
}

//input data from file into passArray
for(int i = 0; i <10000; i++){

passwords >> passArray[i];
    
}

//close file
passwords.close();


// copy array to a reference for next sorting algorithm
CopyArray(passArray, refArray, DEFAULT_ARRAY_SIZE);


// sort array using bubble sort and output number of movements and comparisons
BubbleSort(passArray, DEFAULT_ARRAY_SIZE, comparisons, movements);

cout << "Bubble sort:\n" 
    << "Number of comparisons:" << comparisons << endl
    << "Number of movements:" << movements << endl << endl;


// get ready for next algorithm by resetting the array and variables
comparisons = 0;
movements = 0;
CopyArray(refArray, passArray, DEFAULT_ARRAY_SIZE);


// sort array using selection sort and output number of movements and comparisons
SelectionSort(passArray, DEFAULT_ARRAY_SIZE, comparisons, movements);

cout << "Selection sort:\n" 
    << "Number of comparisons:" << comparisons << endl
    << "Number of movements:" << movements << endl << endl;


// get ready for next algorithm by resetting the array and variables
comparisons = 0;
movements = 0;
CopyArray(refArray, passArray, DEFAULT_ARRAY_SIZE);


// sort array using  insertion sort and output number of movements and comparisons
InsertionSort(passArray, DEFAULT_ARRAY_SIZE, comparisons, movements);

cout << "Insertion sort:\n" 
    << "Number of comparisons:" << comparisons << endl
    << "Number of movements:" << movements << endl << endl;


// get ready for next algorithm by resetting the array and variables
comparisons = 0;
movements = 0;
CopyArray(refArray, passArray, DEFAULT_ARRAY_SIZE);


// sort array using merge sort and output number of movements and comparisons
MergeSort(passArray, 0, 9999, comparisons, movements);

cout << "Merge sort:\n" 
    << "Number of comparisons:" << comparisons << endl
    << "Number of movements:" << movements << endl << endl;


// get ready for next algorithm by resetting the array and variables
comparisons = 0;
movements = 0;
CopyArray(refArray, passArray, DEFAULT_ARRAY_SIZE);


// sort array using quick sort and output number of movements and comparisons
Quicksort(passArray, 0, 9999, comparisons, movements);

cout << "Quick sort:\n" 
    << "Number of comparisons:" << comparisons << endl
    << "Number of movements:" << movements << endl;


 return 0;
}

void SelectionSort(string* numbers, int numbersSize, int& comparisons, int& movements) {
   for (int i = 0; i < numbersSize - 1; i++) {
      // Find index of smallest remaining element
      int indexSmallest = i;
      
      for (int j = i + 1; j < numbersSize; j++) {
            comparisons++;
         if (numbers[j] < numbers[indexSmallest]) {
            indexSmallest = j;
         }
      }
         
      // Swap numbers[i] and numbers[indexSmallest]
      string temp = numbers[i];
      numbers[i] = numbers[indexSmallest];
      numbers[indexSmallest] = temp;
      movements+=3;
   }
}

void InsertionSort(string* numbers, int numbersSize, int& comparisons, int& movements) {
   for (int i = 1; i < numbersSize; i++) {
      int j = i;
      while (j > 0 && numbers[j] < numbers[j - 1]) {
         // Swap numbers[j] and numbers [j - 1]
         comparisons++;
         movements += 3;
         string temp = numbers[j];
         numbers[j] = numbers[j - 1];
         numbers[j - 1] = temp;
         j--;
         
      }
   }
}


void BubbleSort(string* numbers, int numbersSize, int& comparisons, int& movements){

for(int i = 0; i < numbersSize - 1; i++){
    for(int j = 0; j < numbersSize - i - 1; j++){
        
        //count correct number of comparisons
        comparisons++;

        //swap values if the value to the left is greater
        if(numbers[j] > numbers[j+1]){
            string temp = numbers[j];
            numbers[j] = numbers[j+1];
            numbers[j+1] = temp;
            movements+=3;
        }
    }
}
}

void Quicksort(string* numbers, int startIndex, int endIndex, int& comparisons, int& movements) {
   // Only sort if at least 2 elements exist
   if (endIndex <= startIndex) {
      return;
   }
          
   // Partition the array
   int high = Partition(numbers, startIndex, endIndex, comparisons, movements);

   // Recursively sort the left partition
   Quicksort(numbers, startIndex, high, comparisons, movements);

   // Recursively sort the right partition
   Quicksort(numbers, high + 1, endIndex, comparisons, movements);
}

int Partition(string* numbers, int startIndex, int endIndex, int& comparisons, int& movements) {
   // Select the middle value as the pivot.
   int midpoint = startIndex + (endIndex - startIndex) / 2;
   
   string pivot;
   // find median of 3 values
   if ((numbers[startIndex] > numbers[midpoint]) ^ (numbers[startIndex] > numbers[endIndex])){
        pivot = numbers[startIndex];
        comparisons+=2;
   }
    else if ((numbers[midpoint] < numbers[startIndex]) ^ (numbers[midpoint] < numbers[endIndex])){
        pivot = numbers[midpoint];
        comparisons+=4;
    }
    else{
        pivot = numbers[endIndex];
      comparisons+=4;
    }

    
   
   // "low" and "high" start at the ends of the partition
   // and move toward each other.
   int low = startIndex;
   int high = endIndex;
   
   bool done = false;
   while (!done) {
      // Increment low while numbers[low] < pivot
      while (numbers[low] < pivot) {
        low = low + 1;
        comparisons++;
      }
      
      // Decrement high while pivot < numbers[high]
      while (pivot < numbers[high]) {
         high = high - 1;
         comparisons++;
      }
      
      // If low and high have crossed each other, the loop
      // is done. If not, the elements are swapped, low is
      // incremented and high is decremented.
      if (low >= high) {
         done = true;
         comparisons++;
      }
      else {
         string temp = numbers[low];
         numbers[low] = numbers[high];
         numbers[high] = temp;
         low = low + 1;
         high = high - 1;
         movements+=3;
      }
   }

   // "high" is the last index in the left partition.
   return high;
}


void Merge(string* numbers, int leftFirst, int leftLast, int rightLast, int& comparisons, int& movements) {
   int mergedSize = rightLast - leftFirst + 1;       // Size of merged partition
   string* mergedNumbers = new string[mergedSize]; // Dynamically allocates temporary
                                             // array for merged numbers
   int mergePos = 0;                         // Position to insert merged number
   int leftPos = leftFirst;                  // Initialize left partition position
   int rightPos = leftLast + 1;              // Initialize right partition position
      
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= leftLast && rightPos <= rightLast) {
      
      if (numbers[leftPos] <= numbers[rightPos]) {
         comparisons++;
         mergedNumbers[mergePos] = numbers[leftPos];
         movements++;
         leftPos++;
      }
      else {
         mergedNumbers[mergePos] = numbers[rightPos];
         comparisons++;
         movements++;
         rightPos++;
      }
      mergePos++;
   }
      
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= leftLast) {
      mergedNumbers[mergePos] = numbers[leftPos];
      movements++;
      leftPos++;
      mergePos++;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= rightLast) {
      mergedNumbers[mergePos] = numbers[rightPos];
      movements++;
      rightPos++;
      mergePos++;
   }
   
   // Copy merged numbers back to numbers
   for (mergePos = 0; mergePos < mergedSize; mergePos++) {
      numbers[leftFirst + mergePos] = mergedNumbers[mergePos];
      movements++;
   }
   
   // Free temporary array
   delete[] mergedNumbers;
}
   
void MergeSort(string* numbers, int startIndex, int endIndex, int& comparisons, int& movements) {
   if (startIndex < endIndex) {
      // Find the midpoint in the partition
      int mid = (startIndex + endIndex) / 2;

      // Recursively sort left and right partitions
      MergeSort(numbers, startIndex, mid, comparisons, movements);
      MergeSort(numbers, mid + 1, endIndex, comparisons, movements);
            
      // Merge left and right partition in sorted order
      Merge(numbers, startIndex, mid, endIndex, comparisons, movements);
   }
}


void CopyArray(string* OrigArray, string* CopyArray, int arraySize){

// Copies the values from OrigArray to CopyArray using a for loop

for(int i=0; i < arraySize; i++){

    CopyArray[i] = OrigArray[i];
}
}
