#include <stdio.h>
double calculateRepayment(double loan, double interestRate, int years, double installment)
{
    if (years == 0 || loan <= 0) 
	{
        if (loan <= 0)
            printf("\nLoan fully paid.\n");
        else
            printf("\nNo years remaining.\n");
        return 0;
    }
    loan = loan + (loan * interestRate / 100.0);
    double payment = (loan < installment ? loan : installment);
    loan -= payment;
    printf("\nYear %d: Remaining loan = %.2f\n", years, loan);

    return payment + calculateRepayment(loan, interestRate, years - 1, installment);
}
double calculateRepaymentExtra(double loan, double interestRate, int years,double installment, double extraPayment)
{
    if (years == 0 || loan <= 0) return 0;

    loan += loan * interestRate / 100.0;

    double payment = installment + extraPayment;
    if (payment > loan) payment = loan;

    loan -= payment;

    printf("\nYear %d (extra payment): Remaining loan = %.2f\n", years, loan);

    return payment + calculateRepaymentExtra(loan, interestRate, years - 1,installment, extraPayment);
}
int main()
{
    double loan = 100000;
    double rate = 5;
    int years = 3;
    double installment = 40000;

    printf("Loan Repayment\n");
    printf("______________\n");

    double totalPaid = calculateRepayment(loan, rate, years, installment);

    printf("\nTotal repayment over %d years = %.2f\n", years, totalPaid);

    return 0;
}

