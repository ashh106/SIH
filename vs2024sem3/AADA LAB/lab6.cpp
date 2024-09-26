#include <stdio.h>
#include <stdlib.h>

// Structure to represent a job
struct Job {
    int deadline;
    int profit;
    int id; // Job number
};

// Comparison function to sort jobs by profit in descending order
int compare(const void *a, const void *b) {
    struct Job *job1 = (struct Job *)a;
    struct Job *job2 = (struct Job *)b;
    return job2->profit - job1->profit;
}

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

void jobScheduling(struct Job jobs[], int n) {
    // Step 1: Sort jobs by profit in descending order
    qsort(jobs, n, sizeof(struct Job), compare);

    // Step 2: Find the maximum deadline to determine the size of the schedule array
    int maxDeadline = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline) {
            maxDeadline = jobs[i].deadline;
        }
    }

    // Step 3: Create an array to keep track of free time slots
    int result[maxDeadline + 1]; // Array to store the result (job sequence)
    int slot[maxDeadline + 1];   // To keep track of free time slots

    // Initialize all slots to be free (-1)
    for (int i = 0; i <= maxDeadline; i++) {
        slot[i] = -1;
    }

    int totalProfit = 0; // Store total profit
    int jobCount = 0;    // Store count of jobs selected

    // Step 4: Assign jobs to slots
    for (int i = 0; i < n; i++) {
        // Find a free slot for this job (starting from the last possible slot)
        for (int j = jobs[i].deadline; j > 0; j--) {
            if (slot[j] == -1) {
                // Assign this job to slot j
                slot[j] = i;
                result[jobCount++] = jobs[i].id; // Save the job ID in result
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    // Step 5: Output the result
    printf("Selected Jobs: ");
    for (int i = 0; i < jobCount; i++) {
        printf("%d ", result[i]);
    }
    printf("\nMaximum Profit: %d\n", totalProfit);
}

int main() {
    int n;
    printf("Enter number of jobs: ");
    scanf("%d", &n);

    struct Job jobs[n];
    printf("Enter deadline and profit of each job:\n");
    for (int i = 0; i < n; i++) {
        jobs[i].id = i + 1; // Job ID starts from 1
        scanf("%d %d", &jobs[i].deadline, &jobs[i].profit);
    }

    jobScheduling(jobs, n);
    
    return 0;
}
