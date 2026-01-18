
#include <iostream>

struct MonthData { int month; double income; double expense; };

const std::string monthNames[13] = { "January", "February", "March", "April", "May", "June",
"July", "August", "September", "October", "November", "December","\0" };

const std::string monthNamesShort[13] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
"Jul", "Aug", "Sep", "Oct", "Nov", "Dec","\0" };

const int measure = 500;

int getMonthIndex(MonthData* monthData, int numberOfMonths, int month) {
    for (int i = 0; i < numberOfMonths; i++) {
        if (monthData[i].month == month) {
            return i;
        }
    }
    return -1;
}

MonthData* setup(int& numberOfMonths) {
    std::cout << "Enter the number of months: ";
    std::cin >> numberOfMonths;
    if (numberOfMonths < 1 || numberOfMonths>12) {
        std::cout << "Error!";
        return 0;
    }
    MonthData* monthData = new MonthData[numberOfMonths];
    for (int i = 0; i < numberOfMonths; i++) {
        monthData[i].month = 0; 
        monthData[i].income = 0;
        monthData[i].expense = 0;
    }
    return monthData;
}
void add(MonthData* monthData, int numberOfMonths) {
    if (monthData == nullptr) {
        std::cout << "Error!";
        return;
    }
    int monthInput;
    std::cout << "Month: ";
    std::cin >> monthInput;
    if (monthInput < 1 || monthInput > 12) {
        std::cout << "Invalid month!";
        return;
    }
    int entryIndex = -1;
    for (int i = 0; i < numberOfMonths; i++) {
        if (monthData[i].month == monthInput) {
            entryIndex = i;
            break;
        }
    }
    if (entryIndex == -1) {
        for (int i = 0; i < numberOfMonths; i++) {
            if (monthData[i].month == 0) {
                entryIndex = i;
                break;
            }
        }
    }
    if (entryIndex == -1) {
        std::cout << "Error!" << std::endl;
        return;
    }
    monthData[entryIndex].month = monthInput;
    std::cout << "Enter income: ";
    std::cin >> monthData[entryIndex].income;
    std::cout << "Enter expense: ";
    std::cin >> monthData[entryIndex].expense;
    double result = monthData[entryIndex].income - monthData[entryIndex].expense;
    std::cout << "Result: Balance for " << monthNames[monthInput - 1] << ": " << (result >= 0 ? "+" : "") << result << std::endl;
}

void report(MonthData* monthData, int numberOfMonths) {
    if (!monthData) {
        std::cout << "Error!";
        return;
    }
    double totalIncome = 0;
    double totalExpense = 0;
    double totalBalance = 0;
    std::cout << " Month | Income | Expense | Balance " << std::endl;
    for (int i = 0; i < numberOfMonths; i++) {
        if (monthData[i].month == 0) {
            continue;
        }
        double balance = monthData[i].income - monthData[i].expense;
        totalIncome += monthData[i].income;
        totalExpense += monthData[i].expense;
        totalBalance += balance;
        std::cout << monthNamesShort[monthData[i].month - 1] << " | " << monthData[i].income << " | " << monthData[i].expense << " | " <<
            (balance >= 0 ? "+" : "") << balance << std::endl;
    }
    for (int i = 0; i < 30; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
    std::cout << "Total income: " << totalIncome << std::endl;
    std::cout << "Total expense: " << totalExpense << std::endl;
    std::cout << "Average balance: " << ((totalBalance / numberOfMonths) >= 0 ? "+" : "") <<
        (totalBalance / numberOfMonths) << std::endl;
}

void search(MonthData* monthData, int numberOfMonths, const std::string& monthName) {
    if (!monthData) {
        std::cout << "Error!";
        return;
    }
    std::string monthNamesLocal[13] = { "January", "February", "March", "April", "May", "June",
                                   "July", "August", "September", "October", "November", "December","\0" };
    int index = -1;
    for (int i = 0; i < numberOfMonths; i++) {
        if (monthNamesLocal[monthData[i].month - 1] == monthName) {
            index = i;
            break;
        }
        if (monthNamesLocal[monthData[i].month - 1] == monthName) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        std::cout << "No data for this month!" << std::endl;
        return;
    }
    double income = monthData[index].income;
    double expense = monthData[index].expense;
    double balance = income - expense;
    double ratio = (income > 0) ? (expense / income) * 100 : 0;
    std::cout << "Income: " << income << std::endl;
    std::cout << "Expense: " << expense << std::endl;
    std::cout << "Balance: " << (balance >= 0 ? "+" : "") << balance << std::endl;
    std::cout << "Expense ratio: " << ratio << "%" << std::endl;
}

void sort(MonthData* monthData, int numberOfMonths, std::string criteria) {
    if (!monthData) {
        std::cout << "Error!";
        return;
    }
    for (int i = 0; i < numberOfMonths - 1; i++) {
        for (int j = 0; j < numberOfMonths - i - 1; j++) {
            if (monthData[j].month == 0) {
                continue;
            }
            if (monthData[j].month == 0 || monthData[j + 1].month == 0) {
                continue;
            }
            double value1 = 0;
            double value2 = 0;
            if (criteria == "income") {
                value1 = monthData[j].income;
                value2 = monthData[j + 1].income;
            }
            else if (criteria == "expense") {
                value1 = monthData[j].expense;
                value2 = monthData[j + 1].expense;
            }
            else if (criteria == "balance") {
                value1 = monthData[j].income - monthData[j].expense;
                value2 = monthData[j + 1].income - monthData[j + 1].expense;
            }
            else {
                std::cout << "Invalid criteria!";
                return;
            }
            if (value1 < value2) {
                MonthData temp = monthData[j];
                monthData[j] = monthData[j + 1];
                monthData[j + 1] = temp;
            }
        }
    }
    std::cout << "Sorted by montly " << criteria << " (descending):" << std::endl;
    for (int i = 0; i < numberOfMonths && i < 3; i++) {
        double val = 0;
        if (criteria == "income") {
            val = monthData[i].income;
        }
        else if (criteria == "expense") {
            val = monthData[i].expense;
        }
        else if (criteria == "balance") {
            val = monthData[i].income - monthData[i].expense;
        }
        std::cout << monthNames[monthData[i].month - 1] << ": " << (criteria == "balance" && val >= 0 ? "+" : "") << val << std::endl;
    }
}

void forecast(MonthData* monthData, int numberOfMonths) {
    if (!monthData) {
        std::cout << "Error!" << std::endl;
        return;
    }
    double totalBalance = 0;
    int count = 0;
    for (int i = 0; i < numberOfMonths; i++) {
        if (monthData[i].month == 0) {
            continue;
        }
        double balance = monthData[i].income - monthData[i].expense;
        totalBalance += balance;
        count++;
    }
    if (count == 0) {
        std::cout << "Error! No data available for forecast!";
        return;
    }
    double averageChange = totalBalance / count;
    int months;
    std::cin >> months;
    std::cout << "Current savings: " << totalBalance << std::endl;
    std::cout << "Average monthly change: " << (averageChange >= 0 ? "+" : "") << averageChange << std::endl;
    if (averageChange >= 0) {
        double predicted = totalBalance + months * averageChange;
        std::cout << "Predicted savings after " << months << " months: ";
        std::cout << "+" << predicted << std::endl;
    }
    else {
        int monthsLeft = 0;
        double temp = totalBalance;
        while (temp > 0) {
            temp += averageChange;
            monthsLeft++;
        }
        std::cout << "Expected to run out of money after " << monthsLeft << " months" << std::endl;
    }
}

void chart(MonthData* monthData, int numberOfMonths) {
    if (!monthData) {
        std::cout << "Error!";
        return;
    }
    std::string monthNamesLocal[13] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
        "Aug", "Sep", "Oct", "Nov", "Dec", "\0" };
    double incomeByMonth[12] = { 0 };
    double expenseByMonth[12] = { 0 };
    for (int i = 0; i < numberOfMonths; i++) {
        if (monthData[i].month == 0)
            continue;

        int month = monthData[i].month - 1;
        incomeByMonth[month] = monthData[i].income;
        expenseByMonth[month] = monthData[i].expense;
    }
    double max = 0;
    for (int i = 0; i < 12; i++) {
        if (incomeByMonth[i] > max) {
            max = incomeByMonth[i];
        }
        if (expenseByMonth[i] > max) {
            max = expenseByMonth[i];
        }
    }
    if (max == 0) {
        std::cout << "No data to display.";
        return;
    }
    int maxHeight = (int)(max / measure) + 1;
    std::cout << "\n\n=== YEARLY FINANCIAL CHART ===\n\n";
    for (int i = maxHeight; i >= 1; i--) {
        std::cout << measure * i << " | ";
        for (int j = 0; j < 12; j++) {
            if (incomeByMonth[j] >= measure * i) {
                std::cout << "#";
            }
            else {
                std::cout << " ";
            }
            if (expenseByMonth[j] >= measure * i) {
                std::cout << "# ";
            }
            else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "      ";
    for (int i = 0; i < 50; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
    std::cout << "       ";
    for (int i = 0; i < 12; i++) {
        std::cout << monthNamesLocal[i] << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::string command;
    int numberOfMonths = 0;
    MonthData* monthData = nullptr;
    while (true) {
        std::cin >> command;
        if (command == "setup") {
            if (monthData != nullptr) {
                delete[]monthData;
            }
            monthData = setup(numberOfMonths);
        }
        else if (command == "add") {
            add(monthData, numberOfMonths);
        }
        else if (command == "report") {
            report(monthData, numberOfMonths);
        }
        else if (command == "search") {
            std::string monthName;
            std::cin >> monthName;
            search(monthData, numberOfMonths, monthName);
        }
        else if (command == "sort") {
            std::string criteria;
            std::cin >> criteria;
            sort(monthData, numberOfMonths, criteria);
        }
        else if (command == "forecast") {
            forecast(monthData, numberOfMonths);
        }
        else if (command == "chart") {
            chart(monthData, numberOfMonths);
        }
        else if (command == "exit") {
            std::cout << "Goodbye!";
            break;
        }
        else {
            std::cout << "Unknown command!";
        }
    }
    delete[]monthData;
    return 0;
}


