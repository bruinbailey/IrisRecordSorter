// author Dr.H on 10/25/2019
// compiled with g++ -std=c++1z driver.cpp
// This code read EmployeeRecords from a text file into a Sequence, then sort
// the records using SortingMachine(exchangeSort) based on ZIP codes as decided by
// ZipComparer in EmployeeSorter.h, and finally output the sorted data.
// In function sortData, unsorted EmployeeRecords are copied from IrisSequence
// into SortingMachine that uses a List, and copy sorted data back to IrisSequence.

#include <fstream>
#include<iostream>
#include "IrisSorter.h"
#include "IrisRecord.h"

using namespace std;
 
void doInputPersonDataFromFile(IrisSequence& irisData)
{
   string filename = "iris.txt";
   ifstream infile(filename);
   bool successful;
   IrisRecord r;
   int dataSize;

    if (!infile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
   //input.openFile(filename, File::openForRead, successful);
   if (infile.is_open()) {
       // The first item in the data file is an integer
       // it represents how many records are in the data file.
       infile>>dataSize;
       for (int j = 0; j < dataSize; j++) {
           infile>>r.pLength;
           infile>>r.pWidth;
           infile>>r.sLength;
           infile>>r.sWidth;
           infile>>r.species;

           irisData.add(r,0);
       } // end for
       infile.close();
        
   } // end if

 } // doInputPersonDataFromFile>
 
//------------------------------------------------------------

void sortData (IrisSequence& s)
   //! updates s
   //! ensures sorted(s) and perms(#s, s)
{
   IrisRecordSorter irisSorter;

   for (int k = 0, z = s.length(); k < z; k++) {
      IrisRecord r;

      s.remove(r, 0);
      irisSorter.add(r);
   } // end for

   irisSorter.changeToExtractionMode();
   
   for (int k = 0, z = irisSorter.size(); k < z; k++) {
      IrisRecord r;

      irisSorter.removeFirst(r);
      s.add(r, s.length());
   } // end for
} // sortData

//------------------------------------------------------------

int main(int argc, char* argv[])
{

    IrisSequence iSequence;

    doInputPersonDataFromFile(iSequence);
    cout << "Unsorted employees" << endl;
    iSequence.outputSequence();
    cout<< endl;

    sortData(iSequence);

   // Now do something with sorted data in iSequence
    cout << "Sorted employees" << endl;
    iSequence.outputSequence();
    cout<< endl;

    return 0;
}

