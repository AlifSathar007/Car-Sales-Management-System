#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARS 15
#define MAX_SALES 50
#define MAX_FEEDBACK 50

typedef struct {
    char customerName[100];
    int customerAge;
    int carIndex;
    float salePrice;
    int numberOfCars;
    char dateOfPurchase[11]; // The format is DD-MM-YYYY
    float discountValue;
    int discountGiven; // 0 for no discount, 1 for discount given
} Sale;

typedef struct {
    char carModel[50];
    int rating;
    char comment[200];
} Feedback;

// Arrays to store car information
char carModels[MAX_CARS][50] = {
        "Lamborghini Urus",
        "Mclaren P1",
        "Bugatti Chiron",
        "Pagani Huayra"
};

float carPrices[MAX_CARS] = {
        200000, 1500000, 3000000, 2500000
};

int carYears[MAX_CARS] = {
        2021, 2019, 2022, 2020
};

int carStock[MAX_CARS] = {
        5, 3, 2, 4
};

Sale sales[MAX_SALES];
Feedback feedbacks[MAX_FEEDBACK];

int carCount = 4; // Initial cars count
int saleCount = 0;
int feedbackCount = 0;

void viewCarsStock() {
    printf("\nCars in Stock:\n");
    for (int i = 0; i < carCount; i++) {
        printf("%d. Model: %s, Price: %.2f, Year: %d, Stock: %d\n",
               i + 1, carModels[i], carPrices[i], carYears[i], carStock[i]);
    }
}

void buyCar() {
    int carIndex, quantity;
    float discount;
    printf("\nEnter the index of the car you wish to purchase: ");
    scanf("%d", &carIndex);
    carIndex--;

    if (carIndex >= 0 && carIndex < carCount && carStock[carIndex] > 0) {
        printf("Enter customer name: ");
        scanf(" %[^\n]%*c", sales[saleCount].customerName);

        printf("Enter customer age: ");
        scanf("%d", &sales[saleCount].customerAge);

        printf("Enter the number of cars: ");
        scanf("%d", &quantity);

        if (quantity <= carStock[carIndex]) {
            printf("Have you received a discount? (0 for no, 1 for yes): ");
            scanf("%d", &sales[saleCount].discountGiven);

            if (sales[saleCount].discountGiven) {
                printf("Enter discount value: ");
                scanf("%f", &discount);
                sales[saleCount].discountValue = discount;
            } else {
                sales[saleCount].discountValue = 0;
            }

            printf("Enter date of purchase (DD-MM-YYYY): ");
            scanf("%s", sales[saleCount].dateOfPurchase);

            sales[saleCount].carIndex = carIndex;
            sales[saleCount].numberOfCars = quantity;
            sales[saleCount].salePrice = (carPrices[carIndex] - sales[saleCount].discountValue) * quantity;
            carStock[carIndex] -= quantity;

            saleCount++;

            printf("Car(s) purchased successfully!\n");

            // Customer feedback
            printf("Please leave your feedback (rating out of 5 and a short comment):\n");
            printf("Rating (1-5): ");
            scanf("%d", &feedbacks[feedbackCount].rating);

            printf("Comment: ");
            scanf(" %[^\n]%*c", feedbacks[feedbackCount].comment);
            strcpy(feedbacks[feedbackCount].carModel, carModels[carIndex]);

            feedbackCount++;
        } else {
            printf("Not enough cars in stock.\n");
        }
    } else {
        printf("Invalid choice or car out of stock.\n");
    }
}

void viewSalesData() {
    float totalSales[MAX_CARS] = {0};
    int totalUnitsSold[MAX_CARS] = {0};

    // Calculate total sales and units sold for each car model
    for (int i = 0; i < saleCount; i++) {
        totalSales[sales[i].carIndex] += sales[i].salePrice;
        totalUnitsSold[sales[i].carIndex] += sales[i].numberOfCars;
    }

    // Display individual sales data
    printf("\nIndividual Sales Data:\n");
    for (int i = 0; i < saleCount; i++) {
        printf("Customer: %s, Age: %d, Car Model: %s, Number of Cars: %d, Sale Price: %.2f, Discount: %.2f, Date: %s\n",
               sales[i].customerName, sales[i].customerAge, carModels[sales[i].carIndex], sales[i].numberOfCars, sales[i].salePrice, sales[i].discountValue, sales[i].dateOfPurchase);
    }

    // Display total sales and units sold for each model
    printf("\nTotal Sales Data by Car Model:\n");
    for (int i = 0; i < carCount; i++) {
        if (totalUnitsSold[i] > 0) {
            printf("Model: %s, Units Sold: %d, Total Sales: %.2f\n",
                   carModels[i], totalUnitsSold[i], totalSales[i]);
        }
    }
}

void viewCustomerFeedback() {
    printf("\nCustomer Feedback:\n");
    for (int i = 0; i < feedbackCount; i++) {
        printf("Car Model: %s, Rating: %d, Comment: %s\n",
               feedbacks[i].carModel, feedbacks[i].rating, feedbacks[i].comment);
    }
}

int main() {
    int choice;

    do {
        printf("\nCar Sales System\n");
        printf("1. View Cars Stock\n");
        printf("2. Buy Car\n");
        printf("3. View Sales Data\n");
        printf("4. Customer Feedback\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewCarsStock();
                break;
            case 2:
                buyCar();
                break;
            case 3:
                viewSalesData();
                break;
            case 4:
                viewCustomerFeedback();
                break;
            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
