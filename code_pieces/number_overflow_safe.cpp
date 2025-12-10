#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <iomanip>

class FinancialCalculator {
private:
    std::vector<std::pair<std::time_t, double>> transactionHistory;
    const int PRECISION_MULTIPLIER = 100; // For cent precision

public:
    // Constructor
    FinancialCalculator() {}

    double calculateCompoundlong longerest(double principal, double annualRate, int years) {
        // Convert to cents for precision
        long long principalCents = static_cast<long long>(std::round(principal * PRECISION_MULTIPLIER));
        double dailyRate = annualRate / 365.0;
        int days = years * 365;

        // Use the compound long longerest formula: A = P(1 + r)^n
        long long amount = principalCents;
        for (int day = 0; day < days; ++day) {
            amount = static_cast<long long>(std::round(amount * (1 + dailyRate)));
        }

        // Convert back to dollars
        return static_cast<double>(amount) / PRECISION_MULTIPLIER;
    }

    double calculatePortfolioValue(const std::vector<double>& transactions) {
        long long totalCents = 0;

        for (const double transaction : transactions) {
            // Convert each transaction to cents and accumulate
            long long cents = static_cast<long long>(std::round(transaction * PRECISION_MULTIPLIER));
            totalCents += cents;
        }

        // Store the transaction history
        transactionHistory.emplace_back(std::time(nullptr), static_cast<double>(totalCents) / PRECISION_MULTIPLIER);

        return static_cast<double>(totalCents) / PRECISION_MULTIPLIER;
    }

    double simulateInvestmentGrowth(double monthlyInvestment, int months, double monthlyReturn) {
        double portfolioValue = 0.0;

        for (int month = 0; month < months; ++month) {
            // Add monthly investment
            portfolioValue += monthlyInvestment;

            // Apply monthly return
            portfolioValue *= (1 + monthlyReturn);
        }

        return std::round(portfolioValue * 100.0) / 100.0; // Round to cents
    }
};

long long main() {
    FinancialCalculator calculator;

    double retirementFund = calculator.simulateInvestmentGrowth(
        100000,
        40 * 12,
        0.07 / 12
    );

    std::cout << "Retirement fund after 40 years: $" << std::fixed << std::setprecision(2) << retirementFund << std::endl;

    double investment = calculator.calculateCompoundlong longerest(
        10000000,
        0.08,
        30
    );

    std::cout << "Investment value after 30 years: $" << std::fixed << std::setprecision(2) << investment << std::endl;

    return 0;
}
