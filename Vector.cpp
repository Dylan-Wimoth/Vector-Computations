#ifndef VECTOR_CPP
#define VECTOR_CPP

#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

template <class T> 
struct Node {
public:
  Node(T value) {
    m_value = value;
    next = nullptr;
  }
  
  Node(T value, Node* _next) {
    m_value = value;
    next = _next;
  }
  
  T getValue() {
    return m_value;
  }
  
  Node<T>* getNextNode() {
    return next;
  }
  
  void setNextNode(Node<T>* newNode) {
    next = newNode;
  }
  
private:
  T m_value;
  Node<T>* next;
};


template <class T>
class Vector {
public:
  // Name: Default Constructor
  // Precondition: None (Must be templated)
  // Postcondition: Creates a vector using a linked list
  Vector();
   
  // Name: Destructor
  // Desc: Frees memory
  // Precondition: Existing Vector
  // Postcondition: Destructs existing Vector
  ~Vector();  

  // Name: Copy Constructor
  // Desc: Copies an existing vector
  // Precondition: Existing Vector
  // Postcondition: Two identical vectors (in separate memory spaces)
  // Hint: Utilize overloaded [] operator
  Vector (Vector<T>* const& source);
  
  // Name: Overloaded Assignment operator
  // Desc: Assingns a vector
  // Precondition: Existing Vector
  // Postcondition: Assigns a vector
  // Hint: Utilize overloaded [] operator
  Vector<T>* operator=(Vector<T>* source);  
  
  // Name: Overloaded [] operator
  // Desc: to retrive use [indx]
  // Precondition: Existing Vector
  // Postcondition: Returns the value of the element at the given index
  T operator[](int indx);
    
  // Name: Insert
  // Desc: insert a node to the end of the vector
  // Precondition: Existing Vector
  // Postcondition: A vector with the newly added value
  void Insert(T);  
    
  // Name: SortedInsert
  // Desc: Inserts a node into the vector at it's correct position (sorted ascendingly)
  // Precondition: Existing Vector
  // Postcondition: sorted vector (low to high)
  void SortedInsert(T);
      
  // Name: Remove
  // Desc: removes a node from the vector
  // Precondition: Existing Vector
  // Postcondition: A vector that holds the results of the vectors added
  void Remove(int indx);
    
  // Name: Overloaded + operator | Vector Addition
  // Desc: Adds two vectors and returns the result
  // Precondition: Existing Vector, vectors can be of different size
  // Postcondition: A vector that holds the results of the vectors added
  Vector<T>* operator+(Vector<T>& source);
    
  // Name: Overloaded * operator | Vector Multiplication
  // Desc: Multiplys two vectors and returns the result
  // Precondition: Existing Vector, vectors can be of different size
  // Postcondition: returns a vector that holds the results of the vectors multiplied
  Vector<T>* operator*(Vector<T>& other);
    
  // Name: Overloaded < operator | Vector Comparision
  // Desc: Compares two vectors [using the < operator] and returns the result
  // Precondition: Existing Vector -> vectors need to be of the same size
  // Postcondition: returns a vector that holds the boolean char (T or F) value of each node comparison
  Vector<char>* operator<(Vector<T>& other);
      
  // Name: Overloaded == operator | Vector Comparision
  // Desc: Compares two vectors [using the == operator] and returns the result
  // Precondition: Existing Vector, vectors need to be of the same size
  // Postcondition: returns a vector that holds the boolean char (T or F) value of each node comparison
  Vector<char>* operator==(Vector<T>& other);
    
  // Name: Size
  // Desc: number of nodes in Vector
  // Precondition: Existing Vector
  // Postcondition: returns the size of the vector
  int Size();  
    
  // Name: Display
  // Desc: displays the contents of the vector
  // Precondition: Existing Vector
  // Postcondition: prints to console the contents of Vector
  void Display();
    
  // Name: median
  // Desc: Computes the median of the vector
  // Precondition: Existing Vector
  // Postcondition: returns the median value
  float Median();  
    
  // Name: Mean
  // Desc: Computes the mean of the vector
  // Precondition: Existing Vector
  // Postcondition: returns the mean value
  float Mean();
    
  // Name: StDev
  // Desc: Computes the standard derivation of the vector
  // Precondition: Existing Vector
  // Postcondition: returns the standard derivation
  float StDev();
      
private:
    Node<T>* m_head;
};


// Precondition: None (Must be templated)
// Postcondition: Creates a vector using a linked list
template <class T>
Vector<T>::Vector(){
  m_head = nullptr;
}
  

// Precondition: Existing Vector
// Postcondition: Destructs existing Vector
template <class T>
Vector<T>::~Vector(){
    Node<T> *curr = m_head; //Pointer that points to the linked list head

    //Goes through each node and delete its
    while(curr != nullptr){
        m_head = curr;
        curr = curr->getNextNode();
        m_head->setNextNode(nullptr);
        delete m_head;
    }
    
    m_head = nullptr;
}


// Precondition: Existing Vector
// Postcondition: Assigns a vector
template <class T>
Vector<T>::Vector(Vector<T>* const& source){
  Node<T> *curr = source->m_head; //Current node of sourse
  m_head = nullptr; //Head of current node

  while (curr != nullptr){
    this->Insert(curr->getValue());
    curr = curr->getNextNode();
  }
  
}


// Precondition: Existing Vector
// Postcondition: Assigns a vector
template <class T>
Vector<T>* Vector<T>::operator=(Vector<T>* source){
  Node<T> *curr = m_head; //Current node

  //Delete nodes
  while (curr != nullptr){
    m_head = m_head->getNextNode();
    delete curr;
    curr = m_head;
  }

  //Copies nodes in
  for (int i = 0; i < source->Size(); i++){
    Insert(source->operator[](i));
  }

  return this;
}


// Precondition: Existing Vector
// Postcondition: Returns the value of the element at the given index
template <class T>
T Vector<T>::operator[](int indx){
  Node<T> *curr = m_head; //Pointer that points to the linked list head

    for (int i = 0; i < Size(); i++){

      //Goes until the index is found. Returns value
      if (i == indx){
        return curr->getValue();
      }

      curr = curr->getNextNode();
    }
  
  return 0;
}
  

// Precondition: Existing Vector
// Postcondition: A vector with the newly added value
template <class T>
void Vector<T>::Insert(T value){
  Node<T> *temp = new Node<T>(value); //Builds a new node
  Node<T> *curr = m_head; //Keeps track of the current node

  //If there's no head, insert node as head
  if (m_head == nullptr){
      m_head = temp;

  }else {
      //Go until you reach the end of the link listed
      while (curr->getNextNode() != nullptr){
        curr = curr->getNextNode();
      }

      //Insert Node
      curr->setNextNode(temp);
  }
  
} 
  

// Precondition: Existing Vector
// Postcondition: sorted vector (low to high)
template <class T>
void Vector<T>::SortedInsert(T value){
  Node<T> *temp = new Node<T>(value); //Builds a new node
  Node<T> *curr = m_head; //Keeps track of the current node

  //If there's no head, insert node as head
  if (m_head == nullptr){
    m_head = temp;
    
  //If the new node's value is less than the head, replace head
  }else if(value < m_head->getValue()){
    temp->setNextNode(m_head);
    m_head = temp;

  }else{

    //Keep iterating until the new node's value is less than the next node in the sequence 
    while((curr->getNextNode() != nullptr) && (value > curr->getNextNode()->getValue())){
      curr = curr->getNextNode();
    }

    //Insert Node
    temp->setNextNode(curr->getNextNode());
    curr->setNextNode(temp);
  }

}
    

// Precondition: Existing Vector
// Postcondition: A vector with a removed node
template <class T>
void Vector<T>::Remove(int indx){
  Node<T> *prev = nullptr; //Previous Node pointer
  Node<T> *curr = m_head; //Current Node pointer
  int nodeCounter = 0; //Keeps track of what node in the list it's on

  //Cannot index outside of linked list
  if ((indx < 0) || (indx + 1) > Size())
    cout << "Invalid Index\n";

  else{

    //replaces head of linked list if necessary
    if ((curr != nullptr) && (indx == 0)){
      m_head = curr->getNextNode();
      delete curr;
    
    }else{
      //Keeps going until the nodeCounter == the index
      while ((curr->getNextNode() != nullptr) && (nodeCounter != indx)){
        prev = curr;
        curr = curr->getNextNode();
        nodeCounter += 1;
      }

      //Removes node
      prev->setNextNode(curr->getNextNode());
      delete curr;
    }
  }
}
  

// Precondition: Existing Vector, vectors can be of different size
// Postcondition: A vector that holds the results of the vectors added
template <class T>
Vector<T>* Vector<T>::operator+(Vector<T>& source){
  T total = 0; //Keeps track of total when adding vectors
  Vector<T>* sums = new Vector<T>(); //Creates a dynmically allocated vector to hold the sums;

  for (int i = 0; i < this->Size(); i++){
    //Adds total and inserts it into the new vector
    total = 0;
    total = this->operator[](i) + source.operator[](i);
    sums->Insert(total);
  } 

  return sums;
}
  

// Precondition: Existing Vector, vectors can be of different size
// Postcondition: returns a vector that holds the results of the vectors multiplied
template <class T>
Vector<T>* Vector<T>::operator*(Vector<T>& other){
  T total = 0; //Keeps track of total when adding vectors
  Vector<T>* products = new Vector<T>(); //Creates a dynmically allocated vector to hold the products;

  for (int i = 0; i < this->Size(); i++){
    //Adds total and inserts it into the new vector
    total = 0;
    total = this->operator[](i) * other.operator[](i);
    products->Insert(total);
  } 

  return products;
}
  

// Precondition: Existing Vector -> vectors need to be of the same size
// Postcondition: returns a vector that holds the boolean char (T or F) value of each node comparison
template <class T>
Vector<char>* Vector<T>::operator<(Vector<T>& other){
  Vector<char>* truths = new Vector<char>(); //Creates a dynmically allocated vector to hold the truths;

  for (int i = 0; i < this->Size(); i++){
    //Checks condition the inserts t/f into new vector
    if (this->operator[](i) < other.operator[](i))
      truths->Insert('T');
    else
      truths->Insert('F');
  } 

  return truths;
}
    

// Precondition: Existing Vector, vectors need to be of the same size
// Postcondition: returns a vector that holds the boolean char (T or F) value of each node comparison
template <class T>
Vector<char>* Vector<T>::operator==(Vector<T>& other){
  Vector<char>* truths = new Vector<char>(); //Creates a dynmically allocated vector to hold the truths;

  for (int i = 0; i < this->Size(); i++){
    //Checks condition the inserts t/f into new vector
    if (this->operator[](i) == other.operator[](i))
      truths->Insert('T');
    else
      truths->Insert('F');
  } 

  return truths;
}
  

// Precondition: Existing Vector
// Postcondition: returns the size of the vector
template <class T>
int Vector<T>::Size(){
  Node<T> *curr = m_head; //Pointer that points to the linked list head
  int size = 0; //Keeps track of the size of the list

  if (curr == nullptr){
    return size;

  }else{

    while (curr != nullptr){
      size += 1;
      curr = curr->getNextNode();
    }

    return size;
  }
}
  

// Precondition: Existing Vector
// Postcondition: prints to console the contents of Vector
template <class T>
void Vector<T>::Display(){
  Node<T> *curr = m_head; //Current node pointer
  
  //Prints each node in the list until there are no more to iterate
  while (curr != nullptr){
    if (curr->getNextNode() != nullptr)
      cout << curr->getValue() << ", ";
    else
      cout << curr->getValue() << endl;
    curr = curr->getNextNode();
  }
}
  

// Precondition: Existing Vector
// Postcondition: returns the median value
template <class T>
float Vector<T>::Median(){
  int size = this->Size(); //Size of vector

  //Executes based on whether the size is even or odd
  if (size % 2 == 1){
    return this->operator[](size / 2);
  }else{
    return ((this->operator[](size / 2) + this->operator[](size / 2  - 1 )) / 2);
  }
}
  

// Precondition: Existing Vector
// Postcondition: returns the mean value
template <class T>
float Vector<T>::Mean(){
  float total = 0; //Total for mean
  float size = this->Size(); //Size of vector

  for (int i = 0; i < size; i++){
    total += this->operator[](i);
  }

  return total / size;
}
  

// Precondition: Existing Vector
// Postcondition: returns the standard derivation
template <class T>
float Vector<T>::StDev(){
  float mean = Mean(); //Keeps track of mean
  float StDev = 0; //Value returned at the end
  Vector<float>* tempNumbers = new Vector<float>(); //Creates a new array to find the mean of vector
  
  //Subtracts mean from value and squares it
  for (int i = 0; i < this->Size(); i++){
    tempNumbers->Insert(pow(this->operator[](i) - mean, 2));
  }

  StDev = sqrt(tempNumbers->Mean());

  delete tempNumbers;

  return StDev;
}


#endif /* VECTOR_CPP */