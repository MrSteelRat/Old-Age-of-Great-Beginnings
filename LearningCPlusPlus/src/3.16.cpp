#include <iostream>
#include <vector>
#include <string>

template <typename T> 
void printVector(const std::vector<T>& vec, const std::string& name)
{
  std::cout << name << ":";
  for (const T& value : vec)
  {
    std::cout << " " << value;
  }
  std::cout << std::endl;
}

int main()
  { 
  std::vector<int> v1;
  std::vector<int> v2(10);
  std::vector<int> v3(10, 42);
  std::vector<int> v4{10};
  std::vector<int> v5{10, 42};
  std::vector<std::string> v6{10};
  std::vector<std::string> v7{10, "hi"};

  printVector(v1, "v1");
  printVector(v2, "v2");
  printVector(v3, "v3");
  printVector(v4, "v4");
  printVector(v5, "v5");
  printVector(v6, "v6");
  printVector(v7, "v7");
  }