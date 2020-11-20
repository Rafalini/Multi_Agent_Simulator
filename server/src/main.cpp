#include "Server_Core.hpp"
#include <iostream>

using namespace std;

int main()
{
  Server_Core *s = new Server_Core();
  cout << *s << endl;
  cout << "Server running..."<<endl;
  s->idiotic_respond();
  return 0;
}
