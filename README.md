# PLA-Simulator
This is a digital simulator for a Progammable Logic Array.

This program runs on the terminal and works by reading a configuration file and writing out the output to a text file (if given).
ConfigTest.txt is an example of a configuration file.


# The configuration file has the following format: #
- The first line has three numbers separated by comas.
- Each of the first two numbers is in the range 1-10. The lastnumber is in the range 1-100.
- The first number is the number of inputs and the second number is the number ofoutputs.
- The third number is the number of conjunctive clauses used by the PLA.

- After the first line, there is one line for each conjunctive clause.
- The length of each clause is at least 1 and at mostthe number of inputs.
- Each  character  in  a  clause  is  either  a  lowercase  letter  (representing  a  negated  input)  or  an  uppercase  letter (representing a non-negated input).
- The letters must be in alphabetical order.

- The lines holding conjunctive clauses are followed by lines holding disjunctive clauses, one clause per line.
- The number of outputs is also the number of disjunctive clauses used by the PLA.
- The first disjunctive clause determinesthe value (0 or 1) of the first output, the second clause the value of the second output, and so on.
- A disjunctive clause line has one or more numbers, separated by commas only (no spaces).
- Each number is in therange 1 through the third number on the first line of the file.
- Each  number  in  a  disjunctive  clause  references  a  conjunctive  clause.
- The last line holding a disjunctive clause is the last line of the file.
