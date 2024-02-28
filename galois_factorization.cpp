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
    size_t po = 1;
    size_t pe = 2;
    for (size_t j = 1; j < text.size() - i; j++) {
      const bool is_odd = (j % 2 == 0);
      auto smaller_than = is_odd ? odd_less : even_less;

      size_t p = text.size() + 1;
      size_t pe2 = pe;
      size_t po2 = po;
      if (pe <= j) {
        if (smaller_than(text[i + j], text[i + j - pe])) {
          p = std::min(p, pe);
        } else if (smaller_than(text[i + j - pe], text[i + j])) {
          pe2 = j + 1 + (is_odd ? 1 : 0);
        }
      }
      if (po <= j) {
        if (smaller_than(text[i + j], text[i + j - po])) {
          po2 = j + 1 + (is_odd ? 0 : 1);
        } else if (smaller_than(text[i + j - po], text[i + j])) {
          p = std::min(p, po);
        }
      }
      if (p != text.size() + 1) {
        while (j >= p) {
          if (p == pe && pe == 2 * po) {
            ans.push_back(text.substr(i, po));
            ans.push_back(text.substr(i + po, po));
          } else {
            ans.push_back(text.substr(i, p));
          }
          i += p;
          j -= p;
          p = pe;
        }
        j = text.size();
      }
      pe = pe2;
      po = po2;
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
