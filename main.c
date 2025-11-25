#include <stdio.h>
#include <string.h>

double zakatgold(double weightofgold);
double zakatsilver(double weightofsilver);
double zakatsavings(double savings);
void display_conversion();
double income_tax(double annual_income);
double sales_tax(double amount, double rate);
void save_report(const char *description, double value, double user_input);

int main() {
    int choice = 0;
    while(choice != 3){ // MAIN MENU
        printf("\n--------MAIN MENU--------\n");
        printf("1. CALCULATE ZAKAT\n");
        printf("2. CALCULATE TAX\n");
        printf("3. EXIT\n");
        printf("Choose your option: ");
        scanf("%d", &choice);

        switch(choice) {
        case 1: {
            int option = 0;
            while(option != 5){ // ZAKAT MENU
                printf("\n--------ZAKAT MENU--------\n");
                printf("1. CALCULATE ZAKAT BY GOLD\n");
                printf("2. CALCULATE ZAKAT BY SILVER\n");
                printf("3. CALCULATE ZAKAT BY SAVINGS\n");
                printf("4. DISPLAY CONVERSION RATES\n");
                printf("5. RETURN TO MAIN MENU\n");
                printf("Choose your option: ");
                scanf("%d", &option);

                double value, input;
                switch(option) {
                    case 1: // Gold
                        printf("Enter gold weight in grams: ");
                        scanf("%lf", &input);
                        value = zakatgold(input);
                        if(value > 0) {
                            printf("Zakat on gold = %.2f PKR\n", value);
                            save_report("Zakat on Gold", value, input);
                        }
                        break;
                    case 2: // Silver
                        printf("Enter silver weight in grams: ");
                        scanf("%lf", &input);
                        value = zakatsilver(input);
                        if(value > 0) {
                            printf("Zakat on silver = %.2f PKR\n", value);
                            save_report("Zakat on Silver", value, input);
                        }
                        break;
                    case 3: // Savings
                        printf("Enter savings in PKR: ");
                        scanf("%lf", &input);
                        value = zakatsavings(input);
                        if(value > 0) {
                            printf("Zakat on savings = %.2f PKR\n", value);
                            save_report("Zakat on Savings", value, input);
                        }
                        break;
                    case 4:
                        display_conversion();
                        break;
                    case 5:
                        printf("Returning to the Main Menu...\n");
                        break;
                    default:
                        printf("Invalid Choice, TRY AGAIN!\n");
                        break;
                }
            }
            break;
        }

        case 2: {
            int option = 0;
            while(option != 3) { // TAX MENU
                printf("\n--------TAX MENU--------\n");
                printf("1. CALCULATE INCOME TAX\n");
                printf("2. CALCULATE SALES TAX\n");
                printf("3. RETURN TO MAIN MENU\n");
                printf("Choose your option: ");
                scanf("%d", &option);

                double value, input;
                switch(option) {
                    case 1: // Income Tax
                        printf("Enter annual income in PKR: ");
                        scanf("%lf", &input);
                        value = income_tax(input);
                        if(value >= 0) {
                            printf("Income Tax = %.2f PKR\n", value);
                            save_report("Income Tax", value, input);
                        }

                        break;
                    case 2: // Sales Tax
                        {
                            double rate;
                            printf("Enter total sales amount in PKR: ");
                            scanf("%lf", &input);
                            printf("Enter sales tax rate in percent: ");
                            scanf("%lf", &rate);
                            value = sales_tax(input, rate);
                            if(value > 0) {
                                printf("Sales Tax = %.2f PKR\n", value);
                                save_report("Sales Tax", value, input);
                            }
                        }
                        break;
                    case 3:
                        printf("Returning to Main Menu....\n");
                        break;
                    default:
                        printf("Invalid Option, Try Again!\n");
                        break;
                }
            }
            break;
        }

        case 3:
            printf("Exiting the program. GOODBYE!\n");
            break;
        default:
            printf("Invalid Option, Try Again!\n");
            break;
        }
    }

    return 0;
}

// Conversion rates
const double GOLD_STANDARD_PRICE = 37852;
const double SILVER_STANDARD_PRICE = 460.83;

void display_conversion() {
    printf("\n--- Current Standard Rates ---\n");
    printf("Gold: %.2f PKR per gram\n", GOLD_STANDARD_PRICE);
    printf("Silver: %.2f PKR per gram\n", SILVER_STANDARD_PRICE);
    printf("-----------------------------\n");

    double weight;
    int choice;
    printf("Do you want to convert a weight to PKR?\n1) Gold\n2) Silver\n3) Exit\nChoice: ");
    scanf("%d", &choice);

    if(choice == 1) {
        printf("Enter gold weight in grams: ");
        scanf("%lf", &weight);
        printf("Value of gold = %.2f PKR\n", weight * GOLD_STANDARD_PRICE);
    }
    else if(choice == 2) {
        printf("Enter silver weight in grams: ");
        scanf("%lf", &weight);
        printf("Value of silver = %.2f PKR\n", weight * SILVER_STANDARD_PRICE);
    }
    else {
        printf("Exiting conversion display.\n");
    }
}

// Income tax calculation
double income_tax(double annual_income) {
    double tax = 0.0;
     if (annual_income <= 600000)
        tax = 0;
    else if (annual_income <= 1200000)
        tax = (annual_income - 600000) * 0.01;
    else if (annual_income <= 2200000)
        tax = (annual_income - 1200000) * 0.11 + 600000 * 0.01;
    else if (annual_income <= 3000000)
        tax = (annual_income - 2200000) * 0.16 + 116000; // 116,000 = 6,000 + 110,000
    else if (annual_income <= 4000000)
        tax = (annual_income - 3000000) * 0.21 + 244000;
    else if (annual_income <= 6000000)
        tax = (annual_income - 4000000) * 0.26 + 455000;
    else if (annual_income <= 12000000)
        tax = (annual_income - 6000000) * 0.31 + 965000;
    else
        tax = (annual_income - 12000000) * 0.35 + 2845000;

    return tax;
}

// Sales tax
double sales_tax(double amount, double rate) {
    return amount * (rate / 100.0);
}

// Save report
void save_report(const char *description, double value, double user_input) {
    static int counter = 1;
    char filename[50];
    sprintf(filename, "Report%d.txt", counter++);
    
    FILE *fp = fopen(filename, "w");
    if(!fp) {
        printf("Error opening file for writing!\n");
        return;
    }

    fprintf(fp, "==============================\n");
    fprintf(fp, "     ZAKAT & TAX REPORT\n");
    fprintf(fp, "==============================\n\n");
    fprintf(fp, "Type: %s\n", description);

    if(strstr(description, "Gold") != NULL)
        fprintf(fp, "Gold Weight: %.2f grams\nZakat: %.2f PKR\n", user_input, value);
    else if(strstr(description, "Silver") != NULL)
        fprintf(fp, "Silver Weight: %.2f grams\nZakat: %.2f PKR\n", user_input, value);
    else if(strstr(description, "Savings") != NULL)
        fprintf(fp, "Savings Amount: %.2f PKR\nZakat: %.2f PKR\n", user_input, value);
    else if(strstr(description, "Income Tax") != NULL)
        fprintf(fp, "Income Amount: %.2f PKR\nTax Due: %.2f PKR\n", user_input, value);
    else if(strstr(description, "Sales Tax") != NULL)
        fprintf(fp, "Sales Amount: %.2f PKR\nTax Due: %.2f PKR\n", user_input, value);

    fprintf(fp, "\n------------------------------\n");
    fprintf(fp, "This is a computer-generated report.\n");
    fprintf(fp, "==============================\n");
    fclose(fp);

    printf("Report saved as '%s'\n", filename);
}

// Zakat calculations
const double goldnisaab = 87.48;
const double goldprice = 37852;
double zakatgold(double weightofgold) {
    if(weightofgold < goldnisaab) {
        printf("Gold weight below Nisab (%.2f grams). No Zakat due.\n", goldnisaab);
        return 0.0;
    }
    return weightofgold * goldprice * 0.025;
}

const double silvernisaab = 612.36;
const double silverprice = 460.83;
double zakatsilver(double weightofsilver) {
    if(weightofsilver < silvernisaab) {
        printf("Silver weight below Nisab (%.2f grams). No Zakat due.\n", silvernisaab);
        return 0.0;
    }
    return weightofsilver * silverprice * 0.025;
}

const double cashnisab = 87.48 * 37852;
double zakatsavings(double savings) {
    if(savings < cashnisab) {
        printf("Savings below Nisab (%.2f PKR). No Zakat due.\n", cashnisab);
        return 0.0;
    }
    return savings * 0.025;
}
