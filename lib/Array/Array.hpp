#ifndef ARRAY_H
#define ARRAY_H

// TODO: Can we dynamically change this size so that we dont waste any space!
#define ARRAY_MAX_SIZE 32

template <class T, int S = ARRAY_MAX_SIZE>
class Array {
 public:
 
  /**
   * Creates array of ARRAY_MAX_SIZE with all values initialized to NULL
   */ 
  Array() {
    clear();
  }
  
  template <int N>
  Array(const T (&initialData)[N]) {
    clear();
    for (int i = 0; i < N; i++) {
      insert(initialData[i]);
    }
  }

  /**
   * Inserts value into next element in array, does nothing if array is full
   * 
   * @param value data to be inserted
   */
  void insert(T value) {
    if (size < ARRAY_MAX_SIZE) {
      data[size] = value;
      size++;
    }
  }

  /**
   * @return current size (number of elements inserted)
   */
  int getSize() const {
   return size;
  }

  /**
   * @param element element to read from
   * @return value of array at requested element
   */
  T read(int element) const {
    if (element >= 0 && element < ARRAY_MAX_SIZE) {
      return data[element];
    } else {
      return NULL;
    }
  }

  /**
   * Sets all elements to NULL
   */ 
  void clear() {
    size = 0;
  }

 private:
  T data[S];
  int size;
};

#endif