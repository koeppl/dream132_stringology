#include "common.hpp"
#include "dcheck.hpp"


std::string galois_rotation(const std::string& text) {
  if(text.empty()) { return text; }
  size_t per = computePeriod(text);
  if(per != text.size() && text.size() % per == 0) {
    throw std::runtime_error(std::string("Input seems not to be primitive: ") + text);
  }
  size_t i = 0;
  const size_t n = text.size();
  while (i < 3 * text.size()) {
    period_pair per; 
    per.o = 1; per.e = 2;
    for (size_t j = 1; j < 3 * text.size() - i; j++) {
      size_t p = 3*text.size() + 1;
      const auto newper = galois_step(text, i, j, per, p);
      if (p != 3 * text.size() + 1) {
        while (j >= p) {
          i += p;
          j -= p;
          p = per.e;
        }
        break;
      }
      per = newper;
      if(per.e >= n && per.o >= n) {
        return text.substr(i) + text.substr(0, i);
      }
    } 
  }
  throw std::runtime_error(std::string("Input seems not to be primitive: ") + text);
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
