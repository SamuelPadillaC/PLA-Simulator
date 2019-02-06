/*******************************************
Created by SamuelitoPerro and Jorgito Loredo

This program simulates a PLA (Programmable
Logic Array) by reading a configuration file.
********************************************/

#include <iostream>
  #include <string>
  #include <fstream>
  #include <sstream>
  #include <iomanip>
  #include <cstdlib>
  #include <vector>
  #include <cctype>
  #include <ctime>
  #include <chrono>

  using std::cin;
  using std::cout;
  using std::endl;
  using std::string;
  using std::ifstream;
  using std::ofstream;
  using std::ios;
  using std::chrono::system_clock;
  using std::vector;
  using std::istringstream;

//FUNCTION PROTOTYPES  
bool Compare(string Clause); 
///////////////////////
//GLOBAL VECTORS
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
  disbuf,
  intbuf;
  
  ifstream ifl;

  ofstream ofl;

  istringstream iss,
  iss2;

  vector <string> Raw; //Raw data from config file
  vector <string> Con; //Conjunctive Clauses
  vector <string> Dis; //Disjunctive Clauses
  vector <int> intDis; // Int vector holding single Dis clauses
  vector <bool> Output; 

  int In,
  Out,
  Clauses;

  char *ep;


//CHECK FOR LOG FILE
  if (argc == 2)
    logfile = false;
  else
  {
    logfile = true;
    ofl.open(argv[2], ios::app);
    cout << "*Writing out to log file named: \'" << argv[2] << "\'\n" << endl;
    // Define time
    time_t rawTime = system_clock::to_time_t(system_clock::now());
    struct tm *pTime = std::localtime(&rawTime);
    //Output log time
    ofl << "--------------------" << endl;
    ofl << "Log made on: " << std::put_time(pTime, "%A %D %R") << endl;
  }


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
  for (int i = 1; i < Clauses + 1; i++) //From second line to clauses
  {
    Con.push_back(Raw[i]);
  }
  for (int i = Clauses + 1; i < Raw.size(); i++) // From clauses to end
  {
    Dis.push_back(Raw[i]);
  }
  
//CREATING THE LOGIC
string buff;
//Prompt for Input
cout << "Please insert " << In << " inputs on binary form (1 and 0) or ctrl-D to quit" << endl;
	while (getline(cin, buff))
	{
    //Clear vecotrs to start
    userinp.clear();
    answers.clear();
    Output.clear();

    //Input guard
		if (buff.length() != In)
		{
			cout << "The number of inputs is " << In << ", please only enter that number of inputs.\n" << endl;
		}

		else
    {
    /// CONJUNCTIVE CLAUSES ///
      // Check string and fill userinp vector
      for (int i = 0; i < buff.length(); i++)
      {
        if ((buff[i] != '0') && (buff[i] != '1'))
        {
          cout << "Please enter input in binary form ('1' or '0')" << endl;
          exit(0);
        }	
        if (buff[i] == '0')
        {
          userinp.push_back(0);
        }
        else if (buff[i] == '1')
        { 
          userinp.push_back(1);
        }
      }

      //Call Compare function and fill answers
      for (int i = 0; i < Con.size(); i++)
      {
        answers.push_back(Compare(Con[i]));
      }
      
    /// DISJUNCTIVE CLAUSES ///
      for (int i = 0; i < Dis.size(); i++)
      {
        Dis[i] += ',';
        iss2.str(Dis[i]); //Open clause string to manipulate it
        while (getline(iss2, disbuf, ',')) //Read until there are no more commas
        {
          intDis.push_back(strtol(disbuf.c_str(), &ep, 10)); //Push num as int
        }
        
        // Compare each disjunctive clause to answers //
        int counter = 0;
        for (int z = 0; z < intDis.size(); z++)
        {
          if (answers[intDis[z]] == 1) //If one is true, the disjunctive clause is true
          {
            Output.push_back(1);
            break;
          }
          else
            counter++;
        }
        if (counter == intDis.size()) //This means all were false. So clause is false
            Output.push_back(0);

        intDis.clear(); //Clear vector
        iss2.str(""); //Clear string buffer
        iss2.clear(); //Clear error state
      }

    /// OUTPUT ///
      cout << "\nResult of the conjunctive clauses: " << endl;
      for (int i = 0; i < answers.size(); i++)
      {
        cout << answers[i]; 
      }
      cout << endl;
      cout << "\nFinal Output: " << endl;
      for (int i = 0; i < Output.size(); i++)
      {
        cout << Output[i]; 
      }
      cout << endl;
      cout << endl;
      
      // Write to log file if exists //
      if (logfile == 1)
      {
        ofl << "-----" << endl;
        ofl << "Input: ";
        for (int i = 0; i < userinp.size(); i++)
        {
          ofl << userinp[i]; 
        }
        ofl << "\nOutput: ";
        for (int i = 0; i < Output.size(); i++)
        {
          ofl << Output[i]; 
        }
        ofl << endl;
      }
    }
  	//Prompt for more input
    cout << "Please insert " << In << " inputs on binary form (1 and 0) or ctrl-D to quit" << endl;
	}
}
//////////////////////////////////////



//////// FUNCTION DEFINITIONS ///////
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
    if (userinp[index] == 0) //If index is wrong return false
      {
        return 0;
      }
    }
  }
    //If through for loop without returning, all inputs are correct, return true
    return 1;
}