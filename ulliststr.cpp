#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"
#include <iostream>
ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

/**
 * Returns a const reference to the back element
 *   - MUST RUN in O(1)
 */
std::string const & ULListStr::back() const {
  return tail_->val[tail_->last-1];
}

/**
 * Returns a const reference to the front element
 *   - MUST RUN in O(1)
 */
std::string const & ULListStr::front() const {
  return head_->val[head_->first];
}
/**
 * Removes a value from the back of the list
 *   - MUST RUN in O(1)
 */
void ULListStr::pop_back() {
  if (tail_ == NULL) return; // if list is empty exit
  //tail_->val[tail_->last-1] = "";
  //tail_->last = "";

  tail_->last = tail_->last-1;
  //check if tail array is now empty to deallocate 
  if (tail_->last == tail_->first) {
    Item* newTail = tail_->prev;
    delete tail_;
    tail_ = newTail;

    if (tail_ != NULL) tail_->next = NULL;
    
  } 
  size_--;
  if (size_ == 0) head_ = NULL;
  //std::cout<<"donezies: " << std::endl;

}
/**
 * Removes a value from the front of the list
 *   - MUST RUN in O(1)
 */
void ULListStr::pop_front(){
  
  if (head_ == NULL) return; 
  //head_->val[head_->first] = "";
  //head_->first = NULL;
  head_->first = head_->first+1;
  //check if head array is now empty to deallocate 
  if ((head_->first == head_->last)||  head_->first == ARRSIZE) {
    //std::cout<< "now deallocating" << std::endl;
    Item* newHead = head_->next;
    delete head_;
    head_ = newHead;
    if (head_ != NULL) head_->prev = NULL;
    //std::cout<<"hrererer"<<std::endl;

  }
  size_--;
  if (size_ == 0) tail_ = NULL;

  std::cout<<"done w popfront"<<std::endl;
}
/**
 * Adds a new value to the front of the list.
 * If there is room before the 'first' value in
 * the head node add it there, otherwise, 
 * allocate a new head node.
 *   - MUST RUN in O(1)
 */
void ULListStr::push_front(const std::string& val) 
{
  if (head_ == NULL || head_->first==0) {
    //allocate a new Item 
    Item* i = new Item;
    if (tail_ == NULL) { // this is the first item ever added
      tail_ = i; 
    } else {
      i->next = head_;
      head_->prev = i;
    }
    head_ = i;
    //new first position is the last spot open  
    head_->first = ARRSIZE;
    head_->last = ARRSIZE;
  } 
  //put val one ahead of first  
  head_->first = head_->first-1;
  head_->val[head_->first] = val;
  //std::cout << "did one push front " << std::endl;
  size_ ++;
}

/**
 * Adds a new value to the back of the list
 *   - MUST RUN in O(1)
 */
void ULListStr::push_back(const std::string& val)
{
  //std::cout << "pushing back " << val << std::endl;
  if (tail_ == NULL || tail_->last==ARRSIZE) {
    //std::cout << "need to allocate new item" <<std::endl;
    // allocate a new Item 
    // put i in the FRONT spot of the new array created 
    Item* i = new Item;
    if (head_ == NULL) { //this is the first item ever added
      head_ = i;
    } else {
      tail_->next = i;
      i->prev = tail_;
    }
    tail_ = i;
    //new last position is the first spot open  
    /*tail_->first = 0;
    tail_->last = 0;*/
  } 
  //put at the index right after the tail node 
  //move tail node back one 
  //std::cout<<"put " << val << " at " << (int)tail_->last << std::endl;
  //std::cout << "tail last = " << tail_->last<< std::endl;
  //set(tail_->last, val);
  tail_->last = tail_->last + 1; //incr last to be 1 past the last element present 
  tail_->val[tail_->last-1] = val;
  //std::cout<< "after set" << std::endl;
  //std::cout<< "value of tail last is " << tail_->val[tail_->last] << std::endl;
  //tail_->val[tail_->last] = val;
  size_++;
  //std::cout << "done with push_back" << std::endl;
}

/** 
 * Returns a pointer to the item at index, loc,
 *  if loc is valid and NULL otherwise
 *   - MUST RUN in O(n) 
 */
std::string* ULListStr::getValAtLoc(size_t loc) const{
  //std::cout << "getting val at loc" << loc << std::endl;
  Item* currItem = head_;
  std::string* currStr = &head_->val[head_->first];
  size_t index = 0;
  size_t itemIndex = head_->first;
  while (index!=loc) {
    //std::cout << "currStr is " << currStr<< std::endl;
    index++;
    itemIndex++;
    //std::cout << "itemindex: " << itemIndex << std::endl;
    if (itemIndex == ARRSIZE) {
      itemIndex = 0;
      //move onto the next Item 
      //std::cout << "shoujld move to next" << std::endl;
      if (currItem->next != NULL) {
        //std::cout<<"move to next" << std::endl;
        currItem = currItem->next;
        currStr = &currItem->val[0];
      } else return NULL;
    } else {
      //currStr = &currItem->val[itemIndex];
      currStr++;
    }
    
    
  }
  //std::cout<<"return " << std::endl;
  return currStr;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    //std::cout <<"unable to get" << std::endl;
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
