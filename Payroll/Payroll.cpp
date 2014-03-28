#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//Function prototypes
int processEmployee(ifstream& inFile, int& employeeNumber, float& hourWage, int& hoursWorked);
void processPayroll(ofstream& outFile, float& grossPay, float& netTotal, float& fedTaxTotal, float& stateTaxTotal, float& socialSecurityTotal);
void printSummary(ofstream& outFile, float grossPay, float netTotal, float fedTaxTotal, float stateTaxTotal, float socialSecurityTotal);

int main()
{
// Local Declarations
	float grossPay = 0, netTotal = 0, fedTaxTotal = 0, stateTaxTotal = 0, socialSecurityTotal = 0;
	ofstream outFile; //Creates output file

//Statements
	outFile.open("payroll.txt"); //Opens output file

	cout << "Output file:" << endl;
	if (!outFile)
	{
		cout << " Failed to open/create file" << endl << endl;
		return 0;
	}
	else
		cout << " Successfully opened/created file" << endl << endl; //This if-else statement checks to see if the file is opened/created

//Function Calls
	processPayroll(outFile, grossPay, netTotal, fedTaxTotal, stateTaxTotal, socialSecurityTotal);
	printSummary(outFile, grossPay, netTotal, fedTaxTotal, stateTaxTotal, socialSecurityTotal);

	outFile.close();
	system("pause");
	return 0;
}

/*processPayroll
This function calculates employee pay and taxes and writes it to the file.
*/

void processPayroll(ofstream& outFile, float& grossPay, float& netTotal, float& fedTaxTotal, float& stateTaxTotal, float& socialSecurityTotal)
{
//Local Declarations
	int employeeNumber, hoursWorked;
	float hourWage, wageBonus, gross, net, fedtax, stateTax, socialSecTax;
	const float STATE_TAX = 0.0542, SO_SEC_TAX = 0.07, FED_TAX = 0.16;

	ifstream inFile;

//Statements
	inFile.open("Employee Data.txt"); //Opens input file

	cout << "Input File:" << endl;
	if (!inFile)
	{
		cout << " Failed to open" << endl << endl;
		return;
	}
	else
		cout << " Successfully opened" << endl << endl; //Checks if the input file opened or not.

//Starts writing to the file
	outFile << "Employee Payroll" << endl << endl;
	outFile << "Employee\tHours\t Rate\t  Gross Pay\t    Net Pay\t    Federal Tax\t  State Tax\t Soc Sec Tax\n";

//Makes a line for each employee and their data
	while (processEmployee(inFile, employeeNumber, hourWage, hoursWorked))
	{
		outFile << setw(8) << employeeNumber << "\t" << setw(4) << hoursWorked;

		//Checks for which bonus should be applied, if any
		if (hoursWorked <= 35) //If they worked for 35 hours or less, an asterisk is placed next to their hours
		{
			outFile << "*";
			wageBonus = 1;
		}
		else if (hoursWorked > 40) //If they worked 40 or more, a dollar sign is places next to their hours
		{
			outFile << "$";
			wageBonus = 2;
		}
		else
			wageBonus = 0;

		//Calculates gross pay depending on current employee's bonus
		if (wageBonus == 1) //If they worked 35 hours or less
			gross = hoursWorked * (hourWage + 0.15);
		else if (wageBonus == 2) //If they worked for more than 40 hours
			gross = 40 * hourWage + (hoursWorked - 40) * (hourWage * 1.5);
		else
			gross = hoursWorked * hourWage;

		//Calculates net pay and taxes for current employee
		stateTax = gross * STATE_TAX;
		fedtax = gross * FED_TAX;
		socialSecTax = gross * SO_SEC_TAX;
		net = gross - stateTax - fedtax - socialSecTax;

		//Writes down remaining data
		outFile << fixed << setprecision(2) << "\t" << setw(5) << hourWage << "\t" << setw(7) << gross << "\t"
			<< setw(7) << net << "\t" << setw(7) << fedtax << "\t" << setw(7) << stateTax << "\t" << setw(8) << socialSecTax << endl;

		// Updates totals with current employee's data
		grossPay += gross;
		netTotal += net;
		fedTaxTotal += fedtax;
		stateTaxTotal += stateTax;
		socialSecurityTotal += socialSecTax;
	}

	outFile << endl << endl;
	inFile.close();
	return;
}

/*processEmployee
Reads data from the input, updates the data and returns 1 if it was successful and 0 if it failed.
*/

int processEmployee(ifstream& inFile, int& employeeNumber, float& hourWage, int& hoursWorked)
{
	// Reads from file
	if (inFile >> employeeNumber >> hourWage >> hoursWorked)
		return 1; // If succesful the program returns 1
	else
		return 0; // If unsuccesful the program returns 0
}

/*printSummary
Writes summary of totals to file.
*/

void printSummary(ofstream& outFile, float grossPay, float netTotal, float fedTaxTotal, float stateTaxTotal, float socialSecurityTotal)
{
	//Writes totals to the file

	outFile << "SUMMARY - Totals for all employees" << endl << endl;
	outFile << "Gross Pay\tNet Pay\t\tFederal Tax\tState Tax\tSoc Security" << endl;
	outFile << fixed << setprecision(2) << setw(9) << grossPay << "\t" << setw(7) << netTotal << "\t\t"
		<< setw(11) << fedTaxTotal << "\t" << setw(9) << stateTaxTotal << "\t" << setw(12) << socialSecurityTotal << endl;

	return;
}
