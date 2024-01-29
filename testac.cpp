#include "autocomplete.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void testAC01() {
  cout << "Starting AC test01" << endl;
  cout << "* Testing basic autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("small.txt");
  auto v = ac.complete("hel");
  assert(v.size() == 2);
  assert(v[0].first == "help");
  assert(v[0].second == 20);
  assert(v[1].first == "hello");
  assert(v[1].second == 10);
  cout << "Ending tesAC01" << endl;
}

void testAC02() {
  cout << "Starting AC test02" << endl;
  cout << "* Testing cities autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("cities.txt");
  auto v = ac.complete("Sea");

  assert(v.size() == 47);
  assert(v[0].first == "Seattle, Washington, United States");
  assert(v[0].second == 608660);
  assert(v[46].first == "Seabeck, Washington, United States");
  assert(v[46].second == 1105);
  cout << "Ending testAC02" << endl;
}

void testAC03() {
  cout << "Starting AC test03" << endl;
  cout << "* Testing cities autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("cities.txt");
  auto v = ac.complete("Tai");

  assert(v.size() == 34);
  assert(v[0].first == "Taipei, Taiwan");
  assert(v[0].second == 7871900);
  assert(v[29].first == "Taipa, New Zealand");
  assert(v[29].second == 1731);
  cout << "Ending testAC03" << endl;
}

void testAC04() {
  cout << "Starting AC test04" << endl;
  cout << "* Testing cities autocomplete" << endl;
  Autocomplete ac;
  ac.readFile("cities.txt");
  auto v = ac.complete("Los");

  assert(v.size() == 106);
  assert(v[0].first == "Los Angeles, California, United States");
  assert(v[0].second == 3792621);
  assert(v[14].first == "Los Altos, California, United States");
  assert(v[14].second == 28976);
  assert(v[98].first == "Los Conquistadores, Argentina");
  assert(v[98].second == 1214);
  cout << "Ending testAC04" << endl;
}

// // Calling all test functions
void testACAll() {
  testAC01();
  testAC02();
  testAC03();
  testAC04();
}