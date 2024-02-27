#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cstring>

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


// from https://stackoverflow.com/questions/39757354/best-way-to-read-binary-file-c-though-input-redirection
std::string read_input(FILE* infile = stdin) {
  static const std::size_t INIT_BUFFER_SIZE = 1024;
  // on some systems you may need to reopen stdin in binary mode
  // this is supposed to be reasonably portable
  std::freopen(nullptr, "rb", infile);

  if(std::ferror(infile)) {
    throw std::runtime_error(std::strerror(errno));
  }

  std::size_t len;
  std::array<char, INIT_BUFFER_SIZE> buf;

  // somewhere to store the data
  std::vector<char> input;

  // use std::fread and remember to only use as many bytes as are returned
  // according to len
  while((len = std::fread(buf.data(), sizeof(buf[0]), buf.size(), infile)) > 0) {
    // whoopsie
    if(std::ferror(infile) && !std::feof(infile)) {
      throw std::runtime_error(std::strerror(errno));
    }
    // use {buf.data(), buf.data() + len} here
    input.insert(input.end(), buf.data(), buf.data() + len); // append to std::vector
  }
  return std::string(input.begin(), input.end());
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
    if (j % 2 == 0) {  // odd position
      // size_t p = t.size() + 1;
      if (pe <= j) {
        if (t[j] < t[j - pe]) {
          return false;
        } else if (t[j] > t[j - pe]) {
          pe = j + 2;
        }
      }
      if (po <= j) {
        if (t[j] < t[j - po]) {
          po = j + 1;
        } else if (t[j] > t[j - po]) {
          return false;
        }
      }
    } else {  // even position
      // size_t p = t.size() + 1;
      if (pe <= j) {
        if (t[j] > t[j - pe]) {
          return false;
        } else if (t[j] < t[j - pe]) {
          pe = j + 1;
        }
      }
      if (po <= j) {
        if (t[j] > t[j - po]) {
          po = j + 2;
        } else if (t[j] < t[j - po]) {
          return false;
        }
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
    if (i % 2 == 0) {
      if (a[i % a.size()] > b[i % b.size()]) {
        return false;
      } else if (a[i % a.size()] < b[i % b.size()]) {
        return true;
      }
    } else {
      if (a[i % a.size()] < b[i % b.size()]) {
        return false;
      } else if (a[i % a.size()] > b[i % b.size()]) {
        return true;
      }
    }
  }
  throw std::runtime_error(std::string("Input seems not to be primitive: ") + a + " <-> " + b);
}
