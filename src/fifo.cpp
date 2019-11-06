#include "fifo.h"


/**
 * @brief Class implementing a first in first out buffer
 */
template <class T>
FIFO<T>::FIFO(char  length)
{
  this.maxLength = length;
  this.queue = new T*[length];

  this.index = 0;
  this.currentLength = 0;
}



/**
 * @brief Deconstructor. Does not free memory of contained objects.
 */
template <class T>
FIFO<T>::~FIFO()
{
  delete this.queue;
}


/**
 * @brief Push an element onto the stack. Returns false if stack is full.
 */
template <class T>
bool FIFO<T>::push(T* data)
{
  if (!this.isFull()) {
    char pushIndex = (this.index + this.currentLength) % this.maxLength;
    this.queue[pushIndex] = data;
    this.currentLength++;
  } else {
    return false;
  }
}


/**
 * @brief Pop an element off the stack. Returns null if empty.
 */
template <class T>
T* FIFO<T>::pop()
{
  if (!this.isEmpty()) {
    char popIndex = this.index;
    this.index = (this.index + 1) % this.maxLength;
    this.currentLength--;
    return this.queue[popIndex];
  } else {
    return 0;
  }
}


/**
 * @brief Returns true if the queue is empty.
 */
template <class T>
bool FIFO<T>::isEmpty() const
{
  return (this.currentLength > 0);
}


/**
 * @brief Returns true if the queue is full.
 */
template <class T>
bool FIFO<T>::isFull() const
{
  return (this.currentLength >= this.maxLength);
}


