#pragma once
#include<string>
#include<iostream>
using namespace std;


//
// Create IrisRecord
//
class IrisRecord {
   public:
      float pLength;
      float pWidth;
      float sLength;
      float sWidth;
      string species;
      
      IrisRecord () {}
      ~IrisRecord () {}

      void clear(void)
      {
         pLength=0;
         pWidth=0;
         sLength=0;
         sWidth=0;
         species="";
      } // clear

      IrisRecord& operator = (IrisRecord& rhs)
      {
         pLength = rhs.pLength;
         pWidth = rhs.pWidth;
         sLength = rhs.sLength;
         sWidth = rhs.sWidth;
         species = rhs.species;

         return *this;
      } // operator =

      void transferFrom(IrisRecord& source)
      {
         pLength=source.pLength ;
         pWidth=source.pWidth ;
         sLength=source.sLength ;
         sWidth=source.sWidth ;
         species=source.species ;

      } // transferFrom

      friend ostream& operator << (ostream &os, IrisRecord& r)
      {
         os << "(" << r.pLength << "," << r.pWidth<< "," << r.sLength<< "," << r.sWidth << "," << r.species <<  ")";
         return os;
      } // operator <<
};
