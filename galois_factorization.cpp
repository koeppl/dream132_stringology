#include "common.hpp"
#include "dcheck.hpp"


std::vector<std::string> galois_factorization(const std::string& s) {
  if(s.find('\0') != std::string::npos) {
    throw std::runtime_error(std::string("input string must not contain NULL byte"));
  }
  std::string text = s;
  text += '\0';
  std::vector<std::string> ans;
  size_t i = 0;
  while (i < text.size() - 1) {
    period_pair per; 
    per.o = 1; per.e = 2;
    for (size_t j = 1; j < text.size() - i; j++) {
      size_t p = text.size() + 1;
      const auto newper = galois_step(text, i, j, per, p);
      if (p != text.size() + 1) {
        while (j >= p) {
          if (p == per.e && per.e == 2 * per.o) {
            ans.push_back(text.substr(i, per.o));
            ans.push_back(text.substr(i + per.o, per.o));
          } else {
            ans.push_back(text.substr(i, p));
          }
          i += p;
          j -= p;
          p = per.e;
        }
        j = text.size();
      }
      per = newper;
    }
  }
  return ans;
}

void showFactorization(const std::vector<std::string> factor) {
  for (size_t i = 0; i < factor.size(); i++) {
    for (size_t j = 0; j < factor[i].size(); j++) {
      if (j % 2 == 0) {
        std::cout << "\033[32m" + factor[i].substr(j, 1) + "\033[0m";
      } else {
        std::cout << "\033[31m" + factor[i].substr(j, 1) + "\033[0m";
      }
    }
    std::cout << "|";
  }
  std::cout << std::endl;
}

bool check_factorization(const std::vector<std::string> factor) {
  for (size_t i = 0; i < factor.size(); i++) {
    DCHECK(is_galois(factor[i]));
    if(i > 0){ 
      if(factor[i] != factor[i-1]) {
        DCHECK(galois_comp(factor[i], factor[i-1]));
      }
    }
  }
  return true;
}
#include <fstream>


int main(int argc, char *argv[]) {
  if(argc > 2 && std::string(argv[1]) == "-i") {
    std::ifstream f(argv[2], std::ios::binary);
    const auto factors = galois_factorization(read_input(f));
    DCHECK(check_factorization(factors));
    if(argc > 3 && std::string(argv[3]) == "count") {
      std::cout << factors.size();
    } else {
      showFactorization(factors);
    }
    return 0;
  }
  const auto factors = galois_factorization(read_input());
  DCHECK(check_factorization(factors));
  if(argc > 1 && std::string(argv[1]) == "count") {
    std::cout << factors.size();
  } else {
  showFactorization(factors);
  }
  return 0;
}
