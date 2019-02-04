  #include <iostream>
  #include <string>
  #include <fstream>
  #include <sstream>
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
//USAGE GUARD
  if (argc != 2 && argc != 3)
  {
    cout << "USAGE: Please enter at least the name of a configuraiton file \n"
    << "The program also takes an optional log file name" << endl;
    exit (0);
  }


// VARIABLES & STREAMS
  bool logfile;

  string sbuf,
  intbuf;
  
  ifstream ifl;

  istringstream iss;

  vector <int> Raw; //Raw data from config file
  vector <string> Con; //Conjunctive Clauses
  vector <int> Dis; //Disjunctive Clauses

  int In,
  Out,
  Clauses;

  char *ep;


//CHECK FOR LOG FILE
  if (argc == 2)
    logfile = false;
  else
    logfile = true;


// READING CONFIG FILE
  ifl.opem(argv[1]);
  //Guard
    if (!ifl)
    {
      cout << "This Config File does not exist. Please enter a valid text file" << endl;
      exit(0);
    }
  
  //Read in the whole file
  while (getline(ifl, sbuf))
      {
        Raw.push_back(sbuf);
      }
  
  //Define Inputs, Outputs, and Clauses
  string firstline = Raw[0] + '\n';
  iss.str(firstline); //Open first line to iss to manipulate it
  getline(iss, intbuf, ',');
  In = strtol(intbuf.c_str(), &ep, 10)); //Read Inputs
      if (*ep != '\0')
      {
        cout << "The configurtion file does not have the proper format" << endl;
        exit(0);
      }
  getline(iss, intbuf, ',');
  Out = strtol(intbuf.c_str(), &ep, 10)); //Read Outputs
      if (*ep != '\0')
      {
        cout << "The configurtion file does not have the proper format" << endl;
        exit(0);
      }
  getline(iss, intbuf);
  Clauses = strtol(intbuf.c_str(), &ep, 10)); //Read number of clauses
      if (*ep != '\0')
      {
        cout << "The configurtion file does not have the proper format" << endl;
        exit(0);
      }

  //Fill in Con and Dis Vectors
  for (int i = 1; i < Clauses + 1; i++)
  {
    Con.push_back(Raw[i]);
  }
  for (int i = Clauses + 1; i < Raw.size(); i++)
  {
    Dis.push_back(Raw[i]);
  }
  

//CREATING THE LOGIC
}