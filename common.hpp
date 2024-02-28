#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cstring>

constexpr bool odd_less(const unsigned char& a, const unsigned char& b) {
  return a < b;
}

constexpr bool even_less(const unsigned char& a, const unsigned char& b) {
  return a > b;
}

size_t computePeriod(const std::string& p) {
  std::vector<size_t> border(p.size() + 1, 0);
  border[0] = -1;
  border[1] = 0;
  signed long j = 0;
  for (size_t i = 2; i <= p.size(); i++) {
    while (j > -1 && p[i - 1] != p[j]) {
      j = border[j];
    }
    j++;
    border[i] = j;
  }
  return p.size() - border[border.size() - 1];
}


std::string read_input(std::istream& is = std::cin) {
  return std::string(std::istreambuf_iterator<char>(is), std::istreambuf_iterator<char>());
}

void write_output(const std::string& s, FILE* outfile = stdout) {
  std::freopen(nullptr, "wb", outfile);
  if(std::ferror(outfile)) {
    throw std::runtime_error(std::strerror(errno));
  }
  std::fwrite(s.c_str(), 1, s.length(), outfile);
  if(std::ferror(outfile)) {
    throw std::runtime_error(std::strerror(errno));
  }
}


bool is_galois(const std::string& t) {
  // size_t i = 0;
  size_t po = 1;
  size_t pe = 2;
  for (size_t j = 1; j < t.size(); j++) {
    const bool is_odd = (j % 2 == 0);
    auto smaller_than = is_odd ? odd_less : even_less;
    if (pe <= j) {
      if (smaller_than(t[j], t[j - pe])) {
        return false;
      } else if (smaller_than(t[j - pe], t[j])) {
        pe = j + 1 +(is_odd ? 1 : 0);
      }
    }
    if (po <= j) {
      if (smaller_than(t[j], t[j - po])) {
        po = j + 1 + (is_odd ? 0 : 1);
      } else if (smaller_than(t[j - po], t[j])) {
        return false;
      }
    }
  }
  if (po == t.size()) {
    return true;
  } else if (pe == t.size() && pe != 2 * po) {
    return true;
  }
  return false;
}

bool galois_comp(const std::string& a, const std::string& b) {
  const size_t n = 2*std::max(a.size(), b.size());
  if (a == b) {
    return false;
  }
  for (size_t i = 0; i < n; i++) {
    auto smaller_than = (i % 2 == 0) ? odd_less : even_less;
    if (smaller_than(b[i % b.size()], a[i % a.size()])) {
      return false;
    } else if (smaller_than(a[i % a.size()], b[i % b.size()])) {
      return true;
    }
  }
  throw std::runtime_error(std::string("Input seems not to be primitive: ") + a + " <-> " + b);
}
