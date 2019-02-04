  #include <iostream>
  #include <string>
  #include <fstream>
  #include <iomanip>
  #include <cstdlib>
  #include <vector>
  #include <cctype>

  using std::cin;
  using std::cout;
  using std::endl;
  using std::string;
  using std::ifstream;
  using std::ofstream;
  using std::ios;
  using std::vector;

int main (int argc, char *argv[])
{
  bool logfile;

  // GUARDS //
  if (argc != 2 && argc != 3)
  {
    cout << "USAGE: Please enter at least the name of a configuraiton file \n"
    << "The program also takes an optional log file name" << endl;
    exit (0);
  }

  // Check for the existance of logfile
  if (argc == 2)
    logfile = false;
  else
    logfile = true;


}