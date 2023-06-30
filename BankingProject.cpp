#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip> // Required for std::setprecision and std::fixed

class InvestmentCalculator {
private:
    double initialInvestment;
    double monthlyDeposit;
    double annualInterest;
    int numberOfYears;
    std::vector<double> yearEndBalancesWithContributions;
    std::vector<double> yearEndBalancesWithoutContributions;
    std::vector<double> yearEndInterestsWithContributions;
    std::vector<double> yearEndInterestsWithoutContributions;

public:
    InvestmentCalculator(double initialInvestment, double monthlyDeposit, double annualInterest, int numberOfYears)
        : initialInvestment(initialInvestment), monthlyDeposit(monthlyDeposit), annualInterest(annualInterest), numberOfYears(numberOfYears) {
    }

    void calculateCompoundInterestWithContributions() {
        double balance = initialInvestment;
        double monthlyInterestRate = annualInterest / 12 / 100.0;

        for (int i = 1; i <= numberOfYears; ++i) {
            double yearEndBalance = balance;
            double yearEndInterest = 0.0;

            for (int j = 0; j < 12; ++j) {
                balance += balance * monthlyInterestRate;
                yearEndInterest += balance * monthlyInterestRate;
            }
            balance += monthlyDeposit * 12;

            yearEndBalancesWithContributions.push_back(balance);
            yearEndInterestsWithContributions.push_back(yearEndInterest);
        }
    }

    void calculateCompoundInterestWithoutContributions() {
        double balance = initialInvestment;
        double annualInterestRate = annualInterest / 100.0;

        for (int i = 1; i <= numberOfYears; ++i) {
            double yearEndBalance = balance;
            double yearEndInterest = balance * annualInterestRate;

            yearEndBalancesWithoutContributions.push_back(balance);
            yearEndInterestsWithoutContributions.push_back(yearEndInterest);

            balance += balance * annualInterestRate;
        }
    }

    void printResultsWithContributions() const {
        std::cout << "Year\t\t\tBalance\t\t\t\tInterest" << std::endl << std::endl;
        for (int i = 0; i < numberOfYears; ++i) {
            int year = i + 1;
            std::cout << year << "\t\t\t$" << std::fixed << std::setprecision(2)
                      <<  yearEndBalancesWithContributions[i] << "   " << "\t\t\t$" << yearEndInterestsWithContributions[i] << std::endl;
        }
    }

    void printResultsWithoutContributions() const {
        std::cout << "Year\t\t\tBalance\t\t\t\tInterest" << std::endl << std::endl;
        for (int i = 0; i < numberOfYears; ++i) {
            int year = i + 1;
            std::cout << year << "\t\t\t$" << std::fixed << std::setprecision(2)
                      << yearEndBalancesWithoutContributions[i] << "   " << "\t\t\t$" << yearEndInterestsWithoutContributions[i] << std::endl;
        }
    }
};

void getUserInput(double& initialInvestment, double& monthlyDeposit, double& annualInterest, int& numberOfYears) {
    std::string annualInterestStr;
    std::cout << "*********************************" << std::endl;
    std::cout << "*********** Data Input **********" << std::endl;
    std::cout << "Initial investment: $";
    std::cin >> initialInvestment;

    std::cout << "Monthly deposit: $";
    std::cin >> monthlyDeposit;

    std::cout << "Annual interest: %";
    std::cin >> annualInterest;

    std::cout << "Number of years: ";
    std::cin >> numberOfYears;

    std::cout << "Press any key to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining newline character
    std::cin.get(); // Wait for user to press a key
}

int main() {
    double initialInvestment;
    double monthlyDeposit;
    double annualInterest;
    int numberOfYears;

    getUserInput(initialInvestment, monthlyDeposit, annualInterest, numberOfYears);

    InvestmentCalculator calculator(initialInvestment, monthlyDeposit, annualInterest, numberOfYears);
    calculator.calculateCompoundInterestWithContributions();
    calculator.calculateCompoundInterestWithoutContributions();

    system("clear");

    std::cout << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
    std::cout << "             " << "Balance and Interest With Contributions" << std::endl;
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;

    calculator.printResultsWithContributions();

    std::cout << "------------------------------------------------------------------------" << std::endl;
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
    std::cout << "            " << "Balance and Interest Without contributions" << std::endl;
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;

    calculator.printResultsWithoutContributions();

    std::cout << "------------------------------------------------------------------------" << std::endl;
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl;


    return 0;
}
