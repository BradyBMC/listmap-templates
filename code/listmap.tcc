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
     return n_ptr;
   } else {
     curr = find(pair.first);
     if(curr != nullptr) {
       curr.get()->value.second = pair.second;
       return curr.get();
     }
   }
   for(;;) {
     if(!lesser(curr.get()->value.first,pair.first)) {
       node *n_ptr = new node(curr.get(),curr.get()->prev,pair);
       curr.get()->prev->next = n_ptr;
       curr.get()->prev = n_ptr;
       break; 
     }
     ++curr;
     if(curr == end()) {
       node *n_ptr = new node(curr.get(),curr.get()->prev,pair);
       curr.get()->prev->next = n_ptr;
       curr.get()->prev = n_ptr;
       break;
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
   DEBUGF ('l', that);
   return iterator();
}

//
// iterator listmap::erase (iterator position)
//
template <typename key_t, typename mapped_t, class less_t>
typename listmap<key_t,mapped_t,less_t>::iterator
listmap<key_t,mapped_t,less_t>::erase (iterator position) {
   DEBUGF ('l', &*position);
   return iterator();
}

