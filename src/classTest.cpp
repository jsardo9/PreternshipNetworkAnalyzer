#include "../include/Period.h"

int main() {
  std::vector<Flag> flags;

  Flag testFlag1 = Flag(121, std::vector<int>(7,3), 7);
  std::cout << "---Testing Flag Class---\n";
  std::cout << testFlag1;
  std::cout << "\n";


  Flag testFlag2 = Flag(200, std::vector<int>(7,4), 7);
  Flag testFlag3 = Flag(270, std::vector<int>(7,5), 7);
  Flag testFlag4 = Flag(400, std::vector<int>(7,6), 7);


  flags.push_back(testFlag1);
  flags.push_back(testFlag2); 
  flags.push_back(testFlag3);
  flags.push_back(testFlag4);


  std::cout << "---Testing Period Class---\n";
  Period testPeriod = Period(1, flags);
  std::cout << testPeriod;

  return 0;
}
