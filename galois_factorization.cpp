#include "common.hpp"
#include "dcheck.hpp"

std::vector<std::string> linearGaloisFactorization(const std::string& s) {
  std::string t = s;
  t += '$';
  std::vector<std::string> ans;
  size_t i = 0;
  while (i < t.size() - 1) {
    size_t po = 1;
    size_t pe = 2;
    for (size_t j = 1; j < t.size() - i; j++) {
      if (j % 2 == 0) {  // odd position
        size_t p = t.size() + 1;
        size_t pe2 = pe;
        size_t po2 = po;
        if (pe <= j) {
          if (t[i + j] < t[i + j - pe]) {
            p = std::min(p, pe);
          } else if (t[i + j] > t[i + j - pe]) {
            pe2 = j + 2;
          }
        }
        if (po <= j) {
          if (t[i + j] < t[i + j - po]) {
            po2 = j + 1;
          } else if (t[i + j] > t[i + j - po]) {
            p = std::min(p, po);
          }
        }
        if (p != t.size() + 1) {
          while (j >= p) {
            if (p == pe && pe == 2 * po) {
              ans.push_back(t.substr(i, po));
              ans.push_back(t.substr(i + po, po));
            } else {
              ans.push_back(t.substr(i, p));
            }
            i += p;
            j -= p;
            p = pe;
          }
          j = t.size();
        }
        pe = pe2;
        po = po2;
      } else {  // even position
        size_t p = t.size() + 1;
        size_t pe2 = pe;
        size_t po2 = po;
        if (pe <= j) {
          if (t[i + j] > t[i + j - pe]) {
            p = std::min(p, pe);
          } else if (t[i + j] < t[i + j - pe]) {
            pe2 = j + 1;
          }
        }
        if (po <= j) {
          if (t[i + j] > t[i + j - po]) {
            po2 = j + 2;
          } else if (t[i + j] < t[i + j - po]) {
            p = std::min(p, po);
          }
        }
        if (p != t.size() + 1) {
          while (j >= p) {
            if (p == pe && pe == 2 * po) {
              ans.push_back(t.substr(i, po));
              ans.push_back(t.substr(i + po, po));
            } else {
              ans.push_back(t.substr(i, p));
            }
            i += p;
            j -= p;
            p = pe;
          }
          j = t.size();
        }
        pe = pe2;
        po = po2;
      }
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

int main() {
  const auto factors = linearGaloisFactorization(read_input());
  showFactorization(factors);
  DCHECK(check_factorization(factors));
  return 0;
}
