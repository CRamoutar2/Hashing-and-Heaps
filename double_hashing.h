//Chethram Ramoutar
//Linear probing header file used for implementing and testing hash tables. 

#ifndef DOUBLE_HASHING_H
#define DOUBLE_HASHING_H

#include <vector>
#include <algorithm>
#include <functional>
#include "quadratic_probing.h"


// Double Hashing implementation.
template <typename HashedObj>
class HashTableDouble {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableDouble(size_t size = 101) : array_(NextPrime(size))
    { MakeEmpty(); 
      Total_Collisions = 0; //resets the number of probes
      R_val = 97; //default value if user doesn't input
      }
  
  bool Contains(const HashedObj & x) const {
    return IsActive(FindPos(x));
  }
  
  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;
    
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();    
    return true;
  }
    
  bool Insert(HashedObj && x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }

  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }
    // For Part A, , getter functions
  int get_total_elem_size(){
      return current_size_;
  }

  int get_table_size(){
      return array_.size();
  }
  
  int get_total_col(){
      return Total_Collisions;
  }

  size_t get_probes(){
    num_of_probes = Total_Collisions + 1;
    return num_of_probes;
  }

  void reset_probe(){
    Total_Collisions = 0;
    num_of_probes = Total_Collisions;
  }

  //For Part B

  size_t get_R(){
      return R_val;
  }

 private:        
  struct HashEntry {
    HashedObj element_;
    EntryType info_;
    
    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }
    
    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };
    

  std::vector<HashEntry> array_;
  size_t current_size_;
  mutable size_t Total_Collisions;
  size_t R_val; 
  size_t num_of_probes;

  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  size_t FindPos(const HashedObj & x) const {  //modified findpos for double hashing
    size_t offset = DoubleInternalHash(x); 
    size_t current_pos = InternalHash(x);
      
    while (array_[current_pos].info_ != EMPTY &&
	   array_[current_pos].element_ != x) {
      //current_pos = (current_pos + offset * DoubleInternalHash(x)) % array_.size();  // Compute the probe
      current_pos += DoubleInternalHash(x);
      Total_Collisions++;
      if (current_pos >= array_.size())
	current_pos -= array_.size();
    }
    return current_pos;
  }

  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrime(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;
    
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE)
	Insert(std::move(entry.element_));
  }
  
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size( );
  }

  //For Part 2
  size_t DoubleInternalHash(const HashedObj & x) const {  //Compute the R-(x mod R) equation 
    static std::hash<HashedObj> hf;
    return R_val - (hf(x) % R_val);
  }
};

#endif  // DOUBLE_HASHING_H
