#ifndef ARRAY_H
#define ARRAY_H

#include <Arduino.h>

#define ARRAY_MAX_SIZE 100

template <class T>
class Array
{
    private:
        T data[ARRAY_MAX_SIZE];
        int size;

    public:
    
        /**
         * Creates array of ARRAY_MAX_SIZE with all values initialized to NULL
         */ 
        Array()
        {
            clear();
        }

        /**
         * Inserts value into next element in array, does nothing if array is full
         * 
         * @param value data to be inserted
         */
        void insert(T value)
        {
            if (size < ARRAY_MAX_SIZE)
            {
                data[size] = value;
                size++;
            }
        }

        /**
         * @return current size (number of elements inserted)
         */
        int getSize()
        {
            return size;
        }

        /**
         * @param element element to read from
         * @return value of array at requested element
         */
        T read(int element)
        {
            if (element >= 0 && element < ARRAY_MAX_SIZE)
            {
                return data[element];
            }
            else
            {
                return NULL;
            }
        }

        /**
         * Sets all elements to NULL
         */ 
        void clear()
        {
            size = 0;
            for (int i = 0; i < ARRAY_MAX_SIZE; i++)
            {
                data[i] = NULL;
            }
        }
};

#endif