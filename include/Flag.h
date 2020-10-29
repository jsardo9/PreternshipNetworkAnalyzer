#include <iostream>
#include <vector>

class Flag{
  private:
    std::vector<int> time; // time is split as the following {hour, minute, second}
    int latency;
  public:
//-----------------Constructors-------------------------
//------------------------------------------------------
    Flag() : time(), latency(), traffic() {}

    Flag(std::vector<int> tin, int latin, int trafin) : time(tin), latency(latin) {}

//-----------------Public Methods-----------------------
//------------------------------------------------------
    std::vector<int> getTime() {
      return time;
    }

    int getLatency() {
      return latency;
    }

//-----------------Ostream Overload Function------------
    friend std::ostream& operator<<(std::ostream& output, const Flag& theFlag){
			 output <<  theFlag.time << " | Latency: " << theFlag.latency << std::endl;
		   return output;
		}
};
