#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GUESTS 100
#define MAX_NAME_LENGTH 50

typedef struct {
    int bookingId;
    char guestName[MAX_NAME_LENGTH];
    int roomNumber;
    int duration;
    float amountPaid;
    float totalAmount;
    int isCheckedOut;
} Booking;

Booking bookingList[MAX_GUESTS];
int bookingCount = 0;

void bookAccommodation() {
    if (bookingCount >= MAX_GUESTS) {
        printf("Accommodation fully booked. Cannot accept more bookings.\n");
        return;
    }

    Booking newBooking;
    printf("Enter guest name: ");
    scanf("%s", newBooking.guestName);
    printf("Enter room number: ");
    scanf("%d", &newBooking.roomNumber);
    printf("Enter duration of stay (in days): ");
    scanf("%d", &newBooking.duration);
    printf("Enter amount paid: ");
    scanf("%f", &newBooking.amountPaid);

    newBooking.bookingId = bookingCount + 1;
    newBooking.totalAmount = newBooking.duration * 1000.0; // Assuming the charge is 1000 per day
    newBooking.isCheckedOut = 0;
    bookingList[bookingCount++] = newBooking;

    printf("Accommodation booked successfully!\n");
}

void displayBookings() {
    if (bookingCount == 0) {
        printf("No bookings found.\n");
        return;
    }

    printf("Booking List:\n");
    printf("Booking ID\tGuest Name\tRoom Number\tDuration\tAmount Paid\tTotal Amount\tChecked Out\n");
    for (int i = 0; i < bookingCount; i++) {
        printf("%-12d%-16s%-14d%-12d%.2f\t\t%.2f\t\t%s\n", bookingList[i].bookingId, bookingList[i].guestName,
               bookingList[i].roomNumber, bookingList[i].duration, bookingList[i].amountPaid,
               bookingList[i].totalAmount, bookingList[i].isCheckedOut ? "Yes" : "No");
    }
}

void calculateBalance() {
    int bookingId;

    printf("Enter the booking ID: ");
    scanf("%d", &bookingId);

    int bookingIndex = -1;
    for (int i = 0; i < bookingCount; i++) {
        if (bookingList[i].bookingId == bookingId) {
            bookingIndex = i;
            break;
        }
    }

    if (bookingIndex == -1) {
        printf("Booking with ID %d not found.\n", bookingId);
        return;
    }

    Booking *booking = &bookingList[bookingIndex];
    float remainingAmount = booking->totalAmount - booking->amountPaid;

    printf("Guest Name: %s\n", booking->guestName);
    printf("Booking ID: %d\n", booking->bookingId);
    printf("Room Number: %d\n", booking->roomNumber);
    printf("Total Amount: %.2f\n", booking->totalAmount);
    printf("Amount Paid: %.2f\n", booking->amountPaid);
    printf("Remaining Amount: %.2f\n", remainingAmount);
}

void checkoutBooking() {
    int bookingId;

    printf("Enter the booking ID to checkout: ");
    scanf("%d", &bookingId);

    int bookingIndex = -1;
    for (int i = 0; i < bookingCount; i++) {
        if (bookingList[i].bookingId == bookingId) {
            bookingIndex = i;
            break;
        }
    }

    if (bookingIndex == -1) {
        printf("Booking with ID %d not found.\n", bookingId);
        return;
    }

    Booking *booking = &bookingList[bookingIndex];
    if (booking->isCheckedOut) {
        printf("Booking with ID %d is already checked out.\n", bookingId);
        return;
    }

    float remainingAmount = booking->totalAmount - booking->amountPaid;

    printf("Guest Name: %s\n", booking->guestName);
    printf("Booking ID: %d\n", booking->bookingId);
    printf("Room Number: %d\n", booking->roomNumber);
    printf("Total Amount: %.2f\n", booking->totalAmount);
    printf("Amount Paid: %.2f\n", booking->amountPaid);
    printf("Remaining Amount: %.2f\n", remainingAmount);

    if (remainingAmount > 0) {
        float payment;
        printf("Enter the amount to pay: ");
        scanf("%f", &payment);

        if (payment > remainingAmount) {
            printf("Invalid payment amount. Please try again.\n");
            return;
        }

        booking->amountPaid += payment;
        remainingAmount -= payment;
        printf("Payment successful!\n");
    }

    booking->isCheckedOut = 1;
    printf("Booking successfully checked out!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\nPaying Guest Accommodation System\n");
        printf("1. Book Accommodation\n");
        printf("2. Display Bookings\n");
        printf("3. Calculate Balance\n");
        printf("4. Checkout Booking\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                bookAccommodation();
                break;
            case 2:
                displayBookings();
                break;
            case 3:
                calculateBalance();
                break;
            case 4:
                checkoutBooking();
                break;
            case 5:
                printf("Exiting... Thank you!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
