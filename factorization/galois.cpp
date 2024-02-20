#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int computePeriod(const string& p) {
  vector<int> border(p.size() + 1, 0);
  border[0] = -1;
  border[1] = 0;
  int j = 0;
  for (int i = 2; i <= p.size(); i++) {
    while (j > -1 && p[i - 1] != p[j]) {
      j = border[j];
    }
    j++;
    border[i] = j;
  }
  return p.size() - border[border.size() - 1];
}

bool galoisComp(string a, string b) {
  int n = min(a.size(), b.size());
  if (a == b) {
    return false;
  }
  bool flag = true;
  int i = 0;
  while (flag) {
    if (i % 2 == 0) {
      if (a[i % a.size()] > b[i % b.size()]) {
        return false;
      } else if (a[i] % a.size() < b[i % b.size()]) {
        return true;
      }
    } else {
      if (a[i % a.size()] < b[i]) {
        return false;
      } else if (a[i % a.size()] > b[i % b.size()]) {
        return true;
      }
    }
  }

  for (int i = 0; i < n; i++) {
  }
  if (n == a.size()) {
    return false;
  }
  return true;
}

bool galoisCompRev(string a, string b) {
  int n = min(a.size(), b.size());
  if (a == b) {
    return false;
  }
  bool flag = true;
  int i = 0;
  while (flag) {
    if (i % 2 == 0) {
      if (a[i % a.size()] > b[i % b.size()]) {
        return true;
      } else if (a[i] % a.size() < b[i % b.size()]) {
        return false;
      }
    } else {
      if (a[i % a.size()] < b[i]) {
        return true;
      } else if (a[i % a.size()] > b[i % b.size()]) {
        return false;
      }
    }
  }

  for (int i = 0; i < n; i++) {
  }
  if (n == a.size()) {
    return false;
  }
  return true;
}

bool naiveCheckGalois(string& s) {
  vector<string> rot;
  for (int i = 0; i < s.size(); i++) {
    rot.push_back(s.substr(i) + s.substr(0, i));
  }
  sort(rot.begin(), rot.end(), galoisComp);
  if (rot[0] == s) {
    if (rot.size() == 1 || rot[0] != rot[1])
      return true;
  }
  return false;
}

bool linearCheckGalois(string& t) {
  int i = 0;
  int po = 1;
  int pe = 2;
  for (int j = 1; j < t.size(); j++) {
    if (j % 2 == 0) {  // odd position
      int p = t.size() + 1;
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
      int p = t.size() + 1;
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

vector<string> linearGaloisFactorization(string& s) {
  string t = s;
  t += '$';
  vector<string> ans;
  int i = 0;
  while (i < t.size() - 1) {
    int po = 1;
    int pe = 2;
    for (int j = 1; j < t.size() - i; j++) {
      if (j % 2 == 0) {  // odd position
        int p = t.size() + 1;
        int pe2 = pe;
        int po2 = po;
        if (pe <= j) {
          if (t[i + j] < t[i + j - pe]) {
            p = min(p, pe);
          } else if (t[i + j] > t[i + j - pe]) {
            pe2 = j + 2;
          }
        }
        if (po <= j) {
          if (t[i + j] < t[i + j - po]) {
            po2 = j + 1;
          } else if (t[i + j] > t[i + j - po]) {
            p = min(p, po);
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
        int p = t.size() + 1;
        int pe2 = pe;
        int po2 = po;
        if (pe <= j) {
          if (t[i + j] > t[i + j - pe]) {
            p = min(p, pe);
          } else if (t[i + j] < t[i + j - pe]) {
            pe2 = j + 1;
          }
        }
        if (po <= j) {
          if (t[i + j] > t[i + j - po]) {
            po2 = j + 2;
          } else if (t[i + j] < t[i + j - po]) {
            p = min(p, po);
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

string linearGaloisRotation(const string& t) {
  int per = computePeriod(t);
  if (per == t.size() || t.size() % per != 0) {
    int i = 0;
    int n = t.size();
    while (i < 3 * t.size()) {
      int po = 1;
      int pe = 2;
      for (int j = 1; j < 3 * t.size() - i; j++) {
        if (j % 2 == 0) {  // odd position
          int p = 3 * t.size() + 1;
          int pe2 = pe;
          int po2 = po;
          if (pe <= j) {
            if (t[(i + j) % n] < t[(i + j - pe) % n]) {
              p = min(p, pe);
            } else if (t[(i + j) % n] > t[(i + j - pe) % n]) {
              pe2 = j + 2;
            }
          }
          if (po <= j) {
            if (t[(i + j) % n] < t[(i + j - po) % n]) {
              po2 = j + 1;
            } else if (t[(i + j) % n] > t[(i + j - po) % n]) {
              p = min(p, po);
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
          int p = 3 * t.size() + 1;
          int pe2 = pe;
          int po2 = po;
          if (pe <= j) {
            if (t[(i + j) % n] > t[(i + j - pe) % n]) {
              p = min(p, pe);
            } else if (t[(i + j) % n] < t[(i + j - pe) % n]) {
              pe2 = j + 1;
            }
          }
          if (po <= j) {
            if (t[(i + j) % n] > t[(i + j - po) % n]) {
              po2 = j + 2;
            } else if (t[(i + j) % n] < t[(i + j - po) % n]) {
              p = min(p, po);
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
  return "dummy";
}

void showFactorization(vector<string> factor) {
  for (int i = 0; i < factor.size(); i++) {
    for (int j = 0; j < factor[i].size(); j++) {
      if (j % 2 == 0) {
        cout << "\033[32m" + factor[i].substr(j, 1) + "\033[0m";
      } else {
        cout << "\033[31m" + factor[i].substr(j, 1) + "\033[0m";
      }
    }
    cout << "|";
  }
  cout << endl;
}

int main() {
  string T;
  cin >> T;
  vector<string> factor = linearGaloisFactorization(T);
  showFactorization(factor);
  string G = linearGaloisRotation(T);
  cout << G << endl;
  return 0;
}