#include "join.hpp"

std::string     utils::join(std::vector<std::string> v, std::string j)
{
  std::string   result = "";
  int           count = 0;
  int           size = v.size();

  for (auto it = v.begin(); it != v.end(); it++) {
    result += *it;
    if (count < size - 1)
      result += j;
    count++;
  }
  return result;
}
