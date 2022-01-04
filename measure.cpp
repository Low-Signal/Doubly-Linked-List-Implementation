#include <iostream>
#include <string>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include "List.h"

using namespace std;
using namespace cop4530;

// Change to change the number of test for each size list
#define NUMREPEATS 3

int main(int argc, char ** argv){
   List<int> testList[NUMREPEATS];

   // Initializes the number of elements and the range of the elements.
   int cnt = 100;
   int range = cnt / 3;
   
   /* Main loop for testing three sets of NUMREPEATS list
    with 100, 1000, and 10000 elements.*/
   for(int i = 0; i < 3; i++)
   {
      // Fills the lists with random numbers
      for (int j = 0; j < NUMREPEATS; j++) 
      {
         // initialize a random seed;
         srand (time(NULL));

         for (int k = 0; k < cnt; k++) 
         {
            int item = rand() % range + 1;
            testList[j].push_back(item);
         }
      }

      // Tracks the total time of the loop
      int totalTime = 0;

      // Measures the time the reverse function takes over the NUMREPEATS list.
      for (int j = 0; j < NUMREPEATS; j++) 
      {
         auto r_start_single = chrono::steady_clock::now();

         testList[j].reverse();

         auto r_end_single = chrono::steady_clock::now();

         int usec = chrono::duration_cast<chrono::microseconds>(r_end_single - r_start_single).count();
         cout << "reverse run time " << j+1 << " for " << cnt << " element list:" << usec << " usec" << endl;

         totalTime += usec;
      }

      // Prints the average run time of the reverse function
      cout << "reverse " << cnt << "-item list: " << totalTime/NUMREPEATS << " usec" << endl;

      // Clears the current NUMREPEATS list.
      for(int j = 0; j < NUMREPEATS; j++)
         testList[j].clear();
      
      /* Sets up a new element count and range for the next iteration
      used to test 100, 1000, and 10000 elements*/
      cnt = cnt*10;
      range = cnt/3;
   }

   // Resets the count and range for the deduplicate function.
   cnt = 100;
   range = cnt/3;

   /* Main loop for testing three sets of NUMREPEATS list
    with 100, 1000, and 10000 elements.*/
   for(int i = 0; i < 3; i++)
   {
      // Fills the lists with random numbers
      for (int j = 0; j < NUMREPEATS; j++) 
      {
         // initialize a random seed;
         srand (time(NULL));

         for (int k = 0; k < cnt; k++) 
         {
            int item = rand() % range + 1;
            testList[j].push_back(item);
         }
      }

      // Tracks the total time of the loop
      int totalTime = 0;

      /* Measures the time the deduplicate function
       takes over the NUMREPEATS list.*/
      for (int j = 0; j < NUMREPEATS; j++) 
      {
         auto d_start_single = chrono::steady_clock::now();

         testList[j].deduplicate();

         auto d_end_single = chrono::steady_clock::now();

         int usec = chrono::duration_cast<chrono::microseconds>(d_end_single - d_start_single).count();
         cout << "deduplicate run time " << j+1 << " for " << cnt << " element list:" << usec << " usec" << endl;

         totalTime += usec;
      }

      // Prints the average run time of the deduplicate function
      cout << "deduplicate " << cnt << "-item list: " << totalTime/NUMREPEATS << " usec" << endl;

      // Clears the current NUMREPEATS list.
      for(int j = 0; j < NUMREPEATS; j++)
         testList[j].clear();
      
      /* Sets up a new element count and range for the next iteration
      used to test 100, 1000, and 10000 elements*/
      cnt = cnt*10;
      range = cnt/3;
   }
   return 0;
}
