#include <iostream>
#include <string>
#include "Runner.cpp"
using namespace std;

// Prototypes
void loadData(string);


int main(int argc, const char * argv[]) {
  cout << "Vector Computations" << endl;
  loadData(argv[1]);
  return 0;
}


void loadData(string filename) {
  ifstream inputStream;
  inputStream.open(filename);
  
  string dataType, size, number;
  
  Vector<int>* vector1_int = new Vector<int>();
  Vector<int>* vector2_int = new Vector<int>();
  Vector<float>* vector1_float = new Vector<float>();
  Vector<float>* vector2_float = new Vector<float>();
  
  if (inputStream.is_open()) {
    getline(inputStream, dataType, ',');
    getline(inputStream, size, '\n');
    
    if (dataType == "int") {
      for (int i = 0; i < stoi(size); i++) {
	if (i == stoi(size)-1) getline(inputStream, number, '\n');
	else getline(inputStream, number, ',');
	vector1_int->SortedInsert(stoi(number));
      }
      for (int i = 0; i < stoi(size); i++) {
	if (i == stoi(size)-1) getline(inputStream, number, '\n');
	else getline(inputStream, number, ',');
	vector2_int->SortedInsert(stoi(number));
      }
    } else if (dataType == "float") {
      for (int i = 0; i < stoi(size); i++) {
	if (i == stoi(size)-1) getline(inputStream, number, '\n');
	else getline(inputStream, number, ',');
	vector1_float->SortedInsert(stof(number));
      }
      for (int i = 0; i < stoi(size); i++) {
	if (i == stoi(size)-1) getline(inputStream, number, '\n');
	else getline(inputStream, number, ',');
	vector2_float->SortedInsert(stof(number));
      }
    }
  }
  inputStream.close();

  if (dataType == "int") {
    Runner<int>(vector1_int, vector2_int);
  } else {
    Runner<float>(vector1_float, vector2_float);
  }
  

  delete vector1_int;
  delete vector2_int;
  delete vector1_float;
  delete vector2_float;

  cout << "Thank you for using the Vector Tool" << endl;
}


