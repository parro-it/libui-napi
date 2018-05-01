/*******************************************************************************
Copyright (c) 2016 Jannis Mohlin Tsiroyannis

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/

#ifndef MAP_TEMPLATE_H_
#define MAP_TEMPLATE_H_

#include <stdlib.h>

/*******************************************************************************
  Generic, typed, hash table implementation
 
  Insertion causes a struct assignment (=) into an internal buffer, owned and
  maintained by the map itself.
  If your type is (or contains) a pointer or other resource that needs to
  be freed, you yourself are of course responsible for freeing that resource
  when appropriate.
 
  Example usage:
 
  // In header files needing access to the map:
  _DECLARE_MAP(int, const char*, struct StrMap, str_map)
 
  // In ONE c file:
  _IMPLEMENT_MAP(int, const char*, struct StrMap, str_map, strcmp, string_hash)
 
 
  Access example:
  struct StrMap map = str_map_create(10, 0);
  char* str = malloc(...);
  const char key = "A string key.";
  str_map_insert(&s_map, 1, key);
  int value;
  if ( str_map_get(&map, key, &value) == 0 )
    printf("Map had \"%s\" mapped to %d\n", key, value);
 
 ******************************************************************************/

#define _DECLARE_MAP( V, K, SN, FN )			\
   SN							\
   {							\
      SN##Element* data;				\
      unsigned int tableSize;				\
      unsigned int insertedElements;			\
      char growing;					\
   };							\
							\
   SN##Element						\
   {							\
      K key;						\
      V value;						\
							\
      SN##Element* next;				\
							\
      char inUse;					\
   };							\
							\
   /**
      Creates a new instance of this map.

      size: the initial size of the hashtable (in
      objects, not bytes).

      growing: a nonzero value will cause the map to
      grow dynamically when needed.

      Returns: an instance of this map.
   */							\
   SN							\
   FN##_create(unsigned int size, char growing);	\
							\
   /**
      Destroys a previously created instance of this map.
   */							\
   void FN##_destroy(SN* table);			\
							\
   /**
      Inserts a key-value pair into the map.

      Returns: 0 on success, 1 if the key is already in
      the map (=no changes made).
   */							\
   int FN##_insert(					\
      SN* table, V value, K key);			\
							\
   /**
      Removes a key-value pair from the map.

      returns: 0 on success, 1 if the key was not in the
      map (=no changes made).
   */							\
   int							\
   FN##_remove(SN* table, K key);			\
							\
   /**
      Gets a value from the map.

      Returns 0 on success and sets "out_value".
      Returns 1 if the key was not in the map.
   */							\
   int							\
   FN##_get(						\
      SN* table,					\
      K key,						\
      V* out_value);					\
							\
   /**
      Gets a pointer to a value from the map.

      Returns valid pointer on success.
      Returns NULL-pointer if the key was not in the map.
   */							\
   V*							\
   FN##_get_ind(					\
      SN* table,					\
      K key);						\
							\
   /**
      Gets the number of key-value pairs in the map.
   */							\
   unsigned int						\
   FN##_get_count(SN* table);				\
							\
   /**
      Execute "func" once for every key in the map.
      Optionally delete each key-value pair after
      executing func.

      func: Must be a function with signature:
            int func(K); This function should return
            non-zero if the given key-value pair should
            be deleted and zero otherwise.
   */							\
   void							\
   FN##_for_each_key(SN* table,				\
		     int (*func) (K) );			\
							\
   /**
      Execute "func" once for every key in the map (as a
      pointer).
      Optionally delete each key-value pair after
      executing func.

      func: Must be a function with signature:
            int func(K*); This function should return
            non-zero if the given key-value pair should
            be deleted and zero otherwise.
   */							\
   void							\
   FN##_for_each_key_ind(SN* table,			\
			 int (*func) (K*) );		\


#define _IMPLEMENT_MAP( V, K, SN, FN, C, H  )				\
   static void FN##_mapGrow(SN* table)					\
   {									\
      unsigned int newSize = table->tableSize * 2 + 1;			\
      SN newTable =							\
	 FN##_create(newSize, table->growing);				\
									\
      for (unsigned int index = 0; index < table->tableSize; ++index)	\
      {									\
	 SN##Element* element = &table->data[index];			\
	 while(element && element->inUse)				\
	 {								\
	    FN##_insert(						\
	       &newTable, element->value, element->key);		\
	    element = element->next;					\
	 }								\
      }									\
									\
      FN##_destroy(table);						\
      *table = newTable;						\
   }									\
									\
   SN									\
   FN##_create(unsigned int size, char growing)				\
   {									\
      SN table;								\
      table.data = calloc(size, sizeof(SN##Element));			\
      table.tableSize = size;						\
      table.insertedElements = 0;					\
      table.growing = growing;						\
      return table;							\
   }									\
									\
   void									\
   FN##_destroy(SN* table)						\
   {									\
      for (unsigned int i = 0; i < table->tableSize; ++i)		\
      {									\
	 SN##Element* element = &table->data[i];			\
	 if (element->next != NULL)					\
	 {								\
	    element = element->next;					\
	    while (element->next != NULL)				\
	    {								\
	       SN##Element* toBeFreed = element;			\
	       element = element->next;					\
	       free(toBeFreed);						\
	    }								\
	    free(element);						\
	 }								\
      }									\
									\
      free(table->data);						\
   }									\
									\
   int									\
   FN##_insert(								\
      SN* table,							\
      V value, K key)							\
   {									\
      if (table->growing &&						\
	  table->insertedElements >= table->tableSize)			\
	 FN##_mapGrow(table);						\
									\
      unsigned int index = H(key) % table->tableSize;			\
      SN##Element* element = &table->data[index];			\
									\
      if (element->inUse)						\
      {									\
	 if ( C(element->key, key) == 0 )				\
	    return 1;							\
	 while (element->next != NULL)					\
	 {								\
	    element = element->next;					\
	    if ( C(element->key, key) == 0 )				\
	       return 1;						\
	 }								\
	 element->next = malloc(sizeof(SN##Element));			\
	 element = element->next;					\
      }									\
									\
      element->key = key;						\
      element->inUse = 1;						\
      element->value = value;						\
      element->next = NULL;						\
      ++(table->insertedElements);					\
      return 0;								\
   }									\
									\
   int									\
   FN##_remove(SN* table, K key)					\
   {									\
      unsigned int index = H(key) % table->tableSize;			\
      SN##Element* element = &table->data[index];			\
									\
      if (!element->inUse)						\
	 return 1;							\
									\
      if ( C(element->key, key) == 0 )					\
      {									\
	 if (element->next)						\
	 {								\
	    SN##Element* next = element->next;				\
	    *element = *(element->next);				\
	    free(next);							\
	 }								\
	 else								\
	    element->inUse = 0;						\
	 --(table->insertedElements);					\
	 return 0;							\
      }									\
      else								\
      {									\
	 SN##Element* previous = element;				\
	 element = element->next;					\
	 while ( element->inUse && C(element->key, key) != 0 )		\
	 {								\
	    if (element->next)						\
	    {								\
	       previous = element;					\
	       element = element->next;					\
	    }								\
	    else							\
	       return 1;						\
	 }								\
	 previous->next = element->next;				\
	 free(element);							\
	 --(table->insertedElements);					\
	 return 0;							\
      }									\
   }									\
									\
   int									\
   FN##_get(								\
      SN* table,							\
      K key,								\
      V* out_value)							\
   {									\
      int index = H(key) % table->tableSize;				\
      SN##Element* element = &table->data[index];			\
									\
      while ( element->inUse )						\
      {									\
	 if ( C(element->key, key) == 0 )				\
	 {								\
	    *out_value = element->value;				\
	    return 0;							\
	 }								\
	 if (element->next)						\
	    element = element->next;					\
	 else								\
	    return 1;							\
      }									\
									\
      return 1;								\
   };									\
									\
   V*									\
   FN##_get_ind(							\
      SN* table,							\
      K key)								\
   {									\
      int index = H(key) % table->tableSize;				\
      SN##Element* element = &table->data[index];			\
									\
      while ( element->inUse )						\
      {									\
	 if ( C(element->key, key) == 0 )				\
	 {								\
	    return &element->value;					\
	 }								\
	 if (element->next)						\
	    element = element->next;					\
	 else								\
	    return NULL;						\
      }									\
									\
      return NULL;							\
   };									\
									\
   unsigned								\
   FN##_get_count(SN* table)						\
   {									\
      return table->insertedElements;					\
   }									\
   									\
   void									\
   FN##_for_each_key(SN* table,						\
		     int (*func) (K) )					\
   {									\
      for (unsigned index = 0; index < table->tableSize; ++index)	\
      {									\
	 int first = 1;							\
	 SN##Element* element = &table->data[index];			\
	 SN##Element* previous = NULL;					\
	 while(element && element->inUse)				\
	 {								\
	    if (func( element->key ))					\
	    {								\
	       if (first)						\
	       {							\
		  if (element->next)					\
		  {							\
		     SN##Element* next = element->next;			\
		     *element = *(element->next);			\
		     free(next);					\
		  }							\
		  else							\
		     element->inUse = 0;				\
		  --(table->insertedElements);				\
	       }							\
	       else							\
	       {							\
		  previous->next = element->next;			\
		  free(element);					\
		  --(table->insertedElements);				\
	       }							\
	    }								\
	    else							\
	    {								\
	       previous = element;					\
	       element = element->next;					\
	       first = 0;						\
	    }								\
	 }								\
      }									\
   }									\
									\
   void									\
   FN##_for_each_key_ind(SN* table,					\
			 int (*func) (K*) )				\
   {									\
      for (unsigned index = 0; index < table->tableSize; ++index)	\
      {									\
	 int first = 1;							\
	 SN##Element* element = &table->data[index];			\
	 SN##Element* previous = NULL;					\
	 while(element && element->inUse)				\
	 {								\
	    if (func( & element->key ))					\
	    {								\
	       if (first)						\
	       {							\
		  if (element->next)					\
		  {							\
		     SN##Element* next = element->next;			\
		     *element = *(element->next);			\
		     free(next);					\
		  }							\
		  else							\
		     element->inUse = 0;				\
		  --(table->insertedElements);				\
	       }							\
	       else							\
	       {							\
		  previous->next = element->next;			\
		  free(element);					\
		  --(table->insertedElements);				\
	       }							\
	    }								\
	    else							\
	    {								\
	       previous = element;					\
	       element = element->next;					\
	       first = 0;						\
	    }								\
	 }								\
      }									\
   }									\

#endif
