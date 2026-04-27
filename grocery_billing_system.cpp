#include <stdio.h>
#include <string.h>
#include <time.h>

struct TotItems {
    char iname[30];
    float iprice;
    int iqty;
};

int main() {
    struct TotItems items[20];
    int n, i, choice;
    float subtotal = 0, discount_p = 0, tax_p = 0, total = 0;
    FILE *fptr;

    time_t t;
    time(&t);

    printf("===== GROCERY STORE MENU =====\n");
    printf("1. Rice        - Rs. 50 per kg\n");
    printf("2. Sugar       - Rs. 40 per kg\n");
    printf("3. Milk        - Rs. 30 per packet\n");
    printf("4. Bread       - Rs. 25 per pack\n");
    printf("5. Eggs        - Rs. 6 per egg\n");
    printf("6. Oil         - Rs. 120 per litre\n");
    printf("7. Tea Powder  - Rs. 150 per pack\n");
    printf("================================\n");

    printf("Enter number of items: ");
    scanf("%d", &n);

    if (n > 20) {
        printf("Maximum 20 items allowed.\n");
        return 0;
    }

    for (i = 0; i < n; i++) {
        printf("\nEnter item number (1-7): ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                strcpy(items[i].iname, "Rice");
                items[i].iprice = 50;
                break;
            case 2:
                strcpy(items[i].iname, "Sugar");
                items[i].iprice = 40;
                break;
            case 3:
                strcpy(items[i].iname, "Milk");
                items[i].iprice = 30;
                break;
            case 4:
                strcpy(items[i].iname, "Bread");
                items[i].iprice = 25;
                break;
            case 5:
                strcpy(items[i].iname, "Eggs");
                items[i].iprice = 6;
                break;
            case 6:
                strcpy(items[i].iname, "Oil");
                items[i].iprice = 120;
                break;
            case 7:
                strcpy(items[i].iname, "Tea Powder");
                items[i].iprice = 150;
                break;
            default:
                printf("Invalid choice! Try again.\n");
                i--;
                continue;
        }

        printf("Enter quantity: ");
        scanf("%d", &items[i].iqty);
    }

    // Calculate subtotal
    for (i = 0; i < n; i++) {
        subtotal += items[i].iprice * items[i].iqty;
    }

    // Discount & Tax
    if (subtotal > 500)
        discount_p = subtotal * 0.05;

    tax_p = (subtotal - discount_p) * 0.05;
    total = subtotal - discount_p + tax_p;

    // Print Bill
    printf("\n\n========= GROCERY BILL =========\n");
    printf("Date & Time: %s", ctime(&t));

    printf("\n%-15s %-10s %-5s %-10s\n", "Item", "Price", "Qty", "Amount");

    for (i = 0; i < n; i++) {
        printf("%-15s %-10.2f %-5d %-10.2f\n",
               items[i].iname,
               items[i].iprice,
               items[i].iqty,
               items[i].iprice * items[i].iqty);
    }

    printf("\nSubtotal : %.2f", subtotal);
    printf("\nDiscount : %.2f", discount_p);
    printf("\nTax      : %.2f", tax_p);
    printf("\nTotal    : %.2f\n", total);

    // Save to file
    fptr = fopen("grocerybill.txt", "a");

    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fptr, "\n========= GROCERY BILL =========\n");
    fprintf(fptr, "Date & Time: %s", ctime(&t));
    fprintf(fptr, "\n%-15s %-10s %-5s %-10s\n", "Item", "Price", "Qty", "Amount");

    for (i = 0; i < n; i++) {
        fprintf(fptr, "%-15s %-10.2f %-5d %-10.2f\n",
                items[i].iname,
                items[i].iprice,
                items[i].iqty,
                items[i].iprice * items[i].iqty);
    }

    fprintf(fptr, "\nSubtotal: %.2f\nDiscount: %.2f\nTax: %.2f\nTotal: %.2f\n",
            subtotal, discount_p, tax_p, total);

    fclose(fptr);

    printf("\nBill saved to grocerybill.txt\n");

    return 0;
}