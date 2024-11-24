// Erik Wood
// Banker's problem without a deadlock

#include <iostream>
#include <vector>

using namespace std;

const int NUM_PROCESSES = 5;
const int NUM_RESOURCES = 3;

// Calculates need matrix
void calculateNeedMatrix(int need[NUM_PROCESSES][NUM_RESOURCES],
                         int max[NUM_PROCESSES][NUM_RESOURCES],
                         int allocation[NUM_PROCESSES][NUM_RESOURCES]) {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            need[i][j] = max[i][j] - allocation[i][j]; // Basic subtraction
        }
    }
}

// checks system safe state or not
bool isSystemSafe(int available[NUM_RESOURCES],
                  int max[NUM_PROCESSES][NUM_RESOURCES],
                  int allocation[NUM_PROCESSES][NUM_RESOURCES]) {
    int need[NUM_PROCESSES][NUM_RESOURCES];
    calculateNeedMatrix(need, max, allocation);

    bool finished[NUM_PROCESSES] = {false};
    int work[NUM_RESOURCES];
    for (int i = 0; i < NUM_RESOURCES; i++) {
        work[i] = available[i];
    }

    int safeSequence[NUM_PROCESSES];
    int count = 0;

    while (count < NUM_PROCESSES) {
        bool progressMade = false;

        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (!finished[i]) {
                bool canAllocate = true;
                for (int j = 0; j < NUM_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < NUM_RESOURCES; j++) {
                        work[j] += allocation[i][j]; // add allocated back
                    }
                    safeSequence[count++] = i;
                    finished[i] = true;
                    progressMade = true;
                }
            }
        }

        if (!progressMade) {
            cout << "system is not safe" << endl;
            return false;
        }
    }

    cout << "System is safe." << endl;
    cout << "Safe sequence: ";
    for (int i = 0; i < NUM_PROCESSES; i++) {
        cout << "P" << safeSequence[i] << (i < NUM_PROCESSES - 1 ? " -> " : "\n");
    }
    return true;
}

int main() {
    int allocation[NUM_PROCESSES][NUM_RESOURCES] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int max[NUM_PROCESSES][NUM_RESOURCES] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int available[NUM_RESOURCES] = {3, 3, 2};

    isSystemSafe(available, max, allocation);

    return 0;
}
