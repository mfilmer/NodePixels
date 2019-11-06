#ifndef __FIFO_H__
#define __FINO_H__


template <class T>
class FIFO
{
public:
  FIFO(char length);
  ~FIFO();

  bool push(T* data);
  T* pop();

  bool isEmpty() const;
  bool isFull() const;

private:
  char maxLength;
  char index;
  char currentLength;

  T *queue;
};



#endif
