/* Copyright (c) 2015
   Julian Pfeifle
   julian.pfeifle@upc.edu

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 3, or (at your option) any
   later version: http://www.gnu.org/licenses/gpl.txt.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
--------------------------------------------------------------------------------
*/

#ifndef __TYPES_H_
#define __TYPES_H_

#include <set>
#include <numeric>
#include <vector>
#include <functional>
#include <initializer_list>

class NotImplementedException : public std::exception {};
class InvalidGroupException : public std::exception {};

typedef long double NumberType;  // this might work

class ImpreciseVector : public std::vector<NumberType>
{
public:
   /*using std::vector<NumberType>::vector;
   /*using vector::push_back;
   using vector::operator[];
   using vector::begin;
   using vector::end;
   using vector::size;*/
   ImpreciseVector() : std::vector<NumberType>() {};
   ImpreciseVector(int i) : std::vector<NumberType>(i) {};
   ImpreciseVector(const std::vector<NumberType>& v) : std::vector<NumberType>(v) {};
   ImpreciseVector(std::initializer_list<NumberType> v) : std::vector<NumberType>(v) {};

   friend bool operator <(const ImpreciseVector& v1, const ImpreciseVector& v2 )
   {
      float epsilon = 0.00001;
      std::vector<NumberType> tmp(v1.size());

      for (std::vector<NumberType>::size_type i = 0; i != tmp.size(); i++){
         tmp[i] = v1[i] - v2[i];
      }

      if((std::inner_product(tmp.begin(), tmp.end(), tmp.begin(), 0.0) / (std::inner_product(v1.begin(), v1.end(), v1.begin(), 0.0) * std::inner_product(v2.begin(), v2.end(), v2.begin(), 0.0))) < epsilon) 
         return false;
      else
         return static_cast<std::vector<NumberType>>(v1) < static_cast<std::vector<NumberType>>(v2);
   }
};

typedef std::vector<NumberType> CoxeterVectorType;
typedef ImpreciseVector VectorType; //std::vector<NumberType> VectorType;//
typedef std::set<VectorType> Orbit;

class GeneratorList : public std::vector<CoxeterVectorType> {
public:
   GeneratorList(int r, int c) : std::vector<CoxeterVectorType>(r)
   {
      for (int i=0; i<r; ++i)
         (*this)[i] = CoxeterVectorType(c);
   }

   NumberType& operator ()(int i, int j) {
      return (*this)[i][j];
   }

   const NumberType& operator ()(int i, int j) const {
      return (*this)[i][j];
   }
};

#endif // __TYPES_H_

// Local Variables:
// mode:C++
// c-basic-offset:3
// indent-tabs-mode:nil
// End:
