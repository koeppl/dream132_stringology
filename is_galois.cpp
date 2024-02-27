#include "common.hpp"
#include "dcheck.hpp"



bool is_galois_naive(const std::string& s) {
  std::vector<std::string> rot;
  for (size_t i = 0; i < s.size(); i++) {
    rot.push_back(s.substr(i) + s.substr(0, i));
  }
  std::sort(rot.begin(), rot.end(), galois_comp);
  if (rot[0] == s) {
    if (rot.size() == 1 || rot[0] != rot[1])
      return true;
  }
  return false;
}




int main() {
  const auto text = read_input();
  const auto ret = is_galois(text);
  DCHECK_EQ(ret, is_galois_naive(text));
  std::cout << ret;
}
