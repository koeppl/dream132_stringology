#include "common.hpp"


int main() {
  const auto& text = read_input();
  const auto& period = computePeriod(text);
  return period == text.length() || (text.length() % computePeriod(text)) > 0;
}
