#include "common.hpp"
#include "dcheck.hpp"


std::string galois_rotation(const std::string& t) {
  if(t.empty()) { return t; }
  size_t per = computePeriod(t);
  if (per == t.size() || t.size() % per != 0) {
    size_t i = 0;
    size_t n = t.size();
    while (i < 3 * t.size()) {
      size_t po = 1;
      size_t pe = 2;
      for (size_t j = 1; j < 3 * t.size() - i; j++) {
        if (j % 2 == 0) {  // odd position
          size_t p = 3 * t.size() + 1;
          size_t pe2 = pe;
          size_t po2 = po;
          if (pe <= j) {
            if (t[(i + j) % n] < t[(i + j - pe) % n]) {
              p = std::min(p, pe);
            } else if (t[(i + j) % n] > t[(i + j - pe) % n]) {
              pe2 = j + 2;
            }
          }
          if (po <= j) {
            if (t[(i + j) % n] < t[(i + j - po) % n]) {
              po2 = j + 1;
            } else if (t[(i + j) % n] > t[(i + j - po) % n]) {
              p = std::min(p, po);
            }
          }
          if (p != 3 * t.size() + 1) {
            while (j >= p) {
              i += p;
              j -= p;
              p = pe;
            }
            break;
          }
          pe = pe2;
          po = po2;
          if (pe >= n && po >= n) {
            return t.substr(i) + t.substr(0, i);
          }
        } else {  // even position
          size_t p = 3 * t.size() + 1;
          size_t pe2 = pe;
          size_t po2 = po;
          if (pe <= j) {
            if (t[(i + j) % n] > t[(i + j - pe) % n]) {
              p = std::min(p, pe);
            } else if (t[(i + j) % n] < t[(i + j - pe) % n]) {
              pe2 = j + 1;
            }
          }
          if (po <= j) {
            if (t[(i + j) % n] > t[(i + j - po) % n]) {
              po2 = j + 2;
            } else if (t[(i + j) % n] < t[(i + j - po) % n]) {
              p = std::min(p, po);
            }
          }
          if (p != 3 * t.size() + 1) {
            while (j >= p) {
              i += p;
              j -= p;
              p = pe;
            }
            break;
          }
          pe = pe2;
          po = po2;
          if (pe >= n && po >= n) {
            return t.substr(i) + t.substr(0, i);
          }
        }
      }
    }
  }
  throw std::runtime_error(std::string("Input seems not to be primitive: ") + t);
}

int main() {
  const auto text = read_input();
  const auto out = galois_rotation(text);
  DCHECK(is_galois(out));
  write_output(out);
    // try {
    //   // const std::string text = read_input();
    //   // const std::string galois = linearGaloisRotation(text);
    //   // write_output(galois);
    // }
    // catch(std::exception const& e) {
    //     std::cerr << e.what() << '\n';
    // }
  return 0;
}
