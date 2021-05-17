// $Id: listmap.tcc,v 1.15 2019-10-30 12:44:53-07 - - $

#include "listmap.h"
#include "debug.h"

//
/////////////////////////////////////////////////////////////////
// Operations on listmap.
/////////////////////////////////////////////////////////////////
//

//
// listmap::~listmap()
//
template <typename key_t, typename mapped_t, class less_t>
listmap<key_t,mapped_t,less_t>::~listmap() {
   while(begin()!=end()) {
     erase(begin());
     ++begin();
   }
   //Idk if it has to remove anchor?"
   DEBUGF ('l', reinterpret_cast<const void*> (this));
}

//
// iterator listmap::insert (const value_type&)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::insert (const value_type& pair) {
   iterator curr = begin();
   less_t lesser;
   if(empty()) {
     node *n_ptr = new node(curr.get(),curr.get(),pair);
     curr.get()->next = n_ptr;
     curr.get()->prev = n_ptr;
     cout << "empty" << endl;
     return n_ptr;
   } else {
     curr = find(pair.first);
     if(curr != end()) {
       curr.get()->value.second = pair.second;
       cout << "swap value" << endl;
       return curr.get();
     }
   }
   for(;;) {
     if(curr != end() && !lesser(curr.get()->value.first,pair.first)) {
       node *n_ptr = new node(curr.get(),curr.get()->prev,pair);
       curr.get()->prev->next = n_ptr;
       curr.get()->prev = n_ptr;
       cout << "put in front or middle " << endl;
       return n_ptr;
     }
     ++curr;
     if(curr == end()) {
       node *n_ptr = new node(curr.get(),curr.get()->prev,pair);
       curr.get()->prev->next = n_ptr;
       curr.get()->prev = n_ptr;
       cout << "put in back" << endl;
       return n_ptr;
     }
   }
   DEBUGF ('l', &pair << "->" << pair);
   return iterator();
}

//
// listmap::find(const key_type&)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::find (const key_type& that) {
   iterator curr = begin();
   while(curr != end()) {
     if(curr.get()->value.first == that) {break;}
     ++curr;
   }
   DEBUGF ('l', that);
   return curr;
}

template <typename key_t, typename mapped_t, class less_t>
void listmap<key_t,mapped_t,less_t>::find_key(const key_type& that) {
  cout << "Print all pair for value" << endl;
  iterator curr = begin();
  while(curr != end()) {
    if(curr.get()->value.second == that) {
      cout << curr.get()->value << endl;
    }
    ++curr;
  }
}




//
// iterator listmap::erase (iterator position)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::erase (iterator position) {
   position.get()->next->prev = position.get()->prev;
   position.get()->prev->next = position.get()->next;
   cout << "here"<< endl;
   position.get()->next = nullptr;
   position.get()->prev = nullptr;
   delete(position.get());
   DEBUGF ('l', &*position);
   return iterator();
}

