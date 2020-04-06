#pragma once 

#include "IrisRecord.h"
#include "SortingMachineGregBailey.hpp"


typedef Sequence<IrisRecord> IrisSequence;
//----------------------------------
//
// Create Comparer class
//

class PetalLengthComparer
{
public:
   static bool areOrdered (IrisRecord& lhs, IrisRecord& rhs)
   //! restores lhs, rhs
   {
      return lhs.pLength <= rhs.pLength;
   }; // areOrdered
};

typedef SortingMachine1<IrisRecord, ZipComparer> IrisRecordSorter;
