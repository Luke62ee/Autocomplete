#include "autocomplete.h"
#include <algorithm>
#include <fstream>

using namespace std;

void testBSTAll();

// Reads city data from a specified file and uses it to populate the BST map
void Autocomplete::readFile(const string &fileName) {
  ifstream ifs(fileName);
  if (!ifs) {
    cerr << "Error opening file: " << fileName << endl;
  }

  int fileSize = 0;
  vector<BSTMap::value_type> vec;
  BSTMap::value_type temp;
  string str;

  ifs >> fileSize;
  vec.reserve(fileSize);

  while (fileSize-- > 0) {
    ifs >> temp.second;
    getline(ifs, str);

    // Remove the leading space and store the city name.
    temp.first = str.substr(1);
    vec.push_back(temp);
  }

  // Iterate over the vector and insert each key-value pair into the BST map.
  for (const auto &element : vec) {
    phrases.insert(element);
  }
  ifs.close();
  phrases.rebalance();
  // cout << phrases << endl;
}

bool Autocomplete::sortByWeight(BSTMap::value_type &a, BSTMap::value_type &b) {
  return a.second > b.second;
}

// A list of all key-value pairs in the BST map where the keys start with
// a given prefix. The returned list is sorted based on the value (weight) of
// the pair, in descending order (higher values first).
vector<BSTMap::value_type>
Autocomplete::complete(const BSTMap::key_type &prefix) const {
  vector<BSTMap::value_type> v;
  v = phrases.getAll(prefix);

  // Define a lambda function for comparing two key-value pairs
  // based on their values. This comparator will be used to sort
  // the pairs in descending order of their values.
  auto weightComparator = [](const BSTMap::value_type &a,
                             const BSTMap::value_type &b) {
    return a.second > b.second;
  };

  sort(v.begin(), v.end(), weightComparator);
  return v;
}
