#include <iostream>

class Flag{
  private:
    int time[3]; // time is split as the following {hour, minute, second}
    int latency;
  public:
//-----------------Constructors-------------------------
//------------------------------------------------------
    Flag() : time(), latency(), traffic() {}

    Flag(int tin[3], int latin, int trafin) : time(tin), latency(latin) {}
//------------------------------------------------------


//-----------------Public Methods-----------------------
//------------------------------------------------------
    int* getTime() {
      return time;
    }

    int getLatency() {
      return latency;
    }

//------------------------------------------------------


//-----------------Ostream Overload Function------------
    friend std::ostream& operator<<(std::ostream& output, const Flag& theFlag){
			 output <<  theFlag.time << " | Latency: " << theFlag.latency << std::endl;
		   return output;
		}
};
