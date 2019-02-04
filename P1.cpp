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
  using std::istringstream;

//FUNCTION PROTOTYPES  
bool Compare(string Clause); 
///////////////////////

vector <bool> answers;
vector <bool> userinp;
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

  vector <string> Raw; //Raw data from config file
  vector <string> Con; //Conjunctive Clauses
  vector <string> Dis; //Disjunctive Clauses

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
  ifl.open(argv[1]);
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
  In = strtol(intbuf.c_str(), &ep, 10); //Read Inputs
      if (*ep != '\0')
      {
        cout << "The configurtion file does not have the proper format" << endl;
        exit(0);
      }
  getline(iss, intbuf, ',');
  Out = strtol(intbuf.c_str(), &ep, 10); //Read Outputs
      if (*ep != '\0')
      {
        cout << "The configurtion file does not have the proper format" << endl;
        exit(0);
      }
  getline(iss, intbuf);
  Clauses = strtol(intbuf.c_str(), &ep, 10); //Read number of clauses
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
  
string buff;
//CREATING THE LOGIC

cout << "Please insert " << In << " inputs on binary form (1 and 0) or ctrl-D to quit" << endl;
	while (getline(cin, buff))
	{
	
		if (buff.length() != In)
		{
			cout << "The number of inputs is: " << In << " so you can only enter that number of inputs." << endl;
			break;
		}
		
		for (int i = 0; i < buff.length(); i++)
		{
			if ((buff[i] != '0') && (buff[i] != '1'))
			{
				cout << "It is on the binary form, which means '1' and '0' are the only valid digits" << endl;
				break;
			}
		
			for (int i = 0; i < buff.length(); i++)
			{
			if (buff[i] == '0')
			{
				userinp.push_back(0);
			}
			else if (buff[i] == '1')
			{ 
				userinp.push_back(1);
			}
			}
			
  		}
  			for (int i = 0; i < Con.size(); i++)
  			{
    		answers.push_back(Compare(Con[i]));
  			}
			for (int i = 0; i < answers.size(); i++)
  			{
  		 	cout << answers[i];
  			}
  			cout << endl;
  	cout << "Please insert " << In << " inputs on binary form (1 and 0) or ctrl-D to quit" << endl;

	}
	

}

bool Compare (string Clause)
{
  int index;
  for (int i = 0; i < Clause.length(); i++)
  {
    //Char is false - 0
    if (islower(Clause[i]))
    {
      index = Clause[i] - 'a'; //What index the letter refers to
      if (userinp[index] == 1) //If index is wrong return false
      {
        return 0;
      }
    }
    //Char is true - 1
    else if (isupper(Clause[i]))
    {
      index = Clause[i] - 'A'; //What index the letter refers to
    }
    if (userinp[index] == 0) //If index is wrong return false
      {
        return 0;
      }
  }
    //If through for loop without returning, all inputs are correct, return true
    return 1;
}