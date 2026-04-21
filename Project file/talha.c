#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int choice;
    char name[30][30];
    int id[30];
    float marks[30][8]; // 8 subjects
    float totalMarks[30], obtainedMarks[30], percentage[30];
    char grade[30][3];
    int next = 1;
    int i = 0;
    char line[256];

    const char *subjectNames[8] = {
        "ICT Theory",
        "ICT Lab",
        "Programming Fund.",
        "Prog. Fund. Lab",
        "Functional English",
        "Calculus & Geometry",
        "Physics Theory",
        "Physics Lab"
    };

    do {
        printf("-------Student Record System-------\n");
        printf("1. Enter New Student Record\n");
        printf("2. View Report of All Students\n");
        printf("3. Load Student Records from File\n");
        printf("4. Search Student by ID\n");
        printf("0. Exit\n\n");
        printf("Enter your Choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        printf("\n");

        switch (choice) {
            case 1:
                do {
                    if (i >= 30) {
                        printf("Maximum number of student records reached.\n");
                        break;
                    }

                    printf("Enter Name of the Student:\t");
                    scanf(" %[^\n]", name[i]);  // Accept full name with spaces

                    printf("Enter ID of the Student:\t");
                    scanf("%d", &id[i]);

                    totalMarks[i] = 800.0;
                    obtainedMarks[i] = 0;

                    for (int j = 0; j < 8; j++) {
                        do {
                            printf("Enter marks for %s (0–100):\t", subjectNames[j]);
                            scanf("%f", &marks[i][j]);
                            if (marks[i][j] < 0 || marks[i][j] > 100) {
                                printf("Invalid input. Please enter marks between 0 and 100.\n");
                            }
                        } while (marks[i][j] < 0 || marks[i][j] > 100);

                        obtainedMarks[i] += marks[i][j];
                    }

                    percentage[i] = (obtainedMarks[i] / totalMarks[i]) * 100;

                    if (percentage[i] >= 90)
                        strcpy(grade[i], "A+");
                    else if (percentage[i] >= 80)
                        strcpy(grade[i], "A");
                    else if (percentage[i] >= 70)
                        strcpy(grade[i], "B");
                    else if (percentage[i] >= 60)
                        strcpy(grade[i], "C");
                    else if (percentage[i] >= 50)
                        strcpy(grade[i], "D");
                    else
                        strcpy(grade[i], "F");

                    printf("Student Record Saved Successfully.\n\n");

                    printf("1. Next\n2. Exit\n");
                    scanf("%d", &next);
                    getchar();
                    i++;

                } while (next == 1 && i < 30);
                break;

            case 2:
                if (i == 0) {
                    printf("No student records found.\n\n");
                    break;
                }
                printf("Summary of Student Records:\n\n");
                for (int j = 0; j < i; j++) {
                    printf("Name: %s\t ID: %d\n", name[j], id[j]);
                    for (int k = 0; k < 8; k++) {
                        printf("%s: %.2f\n", subjectNames[k], marks[j][k]);
                    }
                    printf("Total: %.2f / 800\t Percentage: %.2f%%\t Grade: %s\n\n",
                           obtainedMarks[j], percentage[j], grade[j]);
                }
                break;

            case 3: {
                FILE *fp = fopen("students.txt", "r");
                if (fp == NULL) {
                    printf("Error: Could not open file.\n\n");
                    break;
                }

                while (fgets(line, sizeof(line), fp) && i < 30) {
                    char *token;
                    token = strtok(line, ",");
                    if (token == NULL) continue;
                    strcpy(name[i], token);

                    token = strtok(NULL, ",");
                    if (token == NULL) continue;
                    id[i] = atoi(token);

                    obtainedMarks[i] = 0;
                    totalMarks[i] = 800.0;

                    for (int j = 0; j < 8; j++) {
                        token = strtok(NULL, ",");
                        if (token == NULL) break;
                        marks[i][j] = atof(token);
                        obtainedMarks[i] += marks[i][j];
                    }

                    percentage[i] = (obtainedMarks[i] / totalMarks[i]) * 100;

                    if (percentage[i] >= 90)
                        strcpy(grade[i], "A+");
                    else if (percentage[i] >= 80)
                        strcpy(grade[i], "A");
                    else if (percentage[i] >= 70)
                        strcpy(grade[i], "B");
                    else if (percentage[i] >= 60)
                        strcpy(grade[i], "C");
                    else if (percentage[i] >= 50)
                        strcpy(grade[i], "D");
                    else
                        strcpy(grade[i], "F");

                    i++;
                }

                fclose(fp);
                printf("Student records loaded from file successfully.\n\n");
                break;
            }

            case 4: {
                if (i == 0) {
                    printf("No student records to search.\n\n");
                    break;
                }
                int searchId, found = 0;
                printf("Enter Student ID to Search: ");
                scanf("%d", &searchId);

                for (int j = 0; j < i; j++) {
                    if (id[j] == searchId) {
                        found = 1;
                        printf("\nStudent Found:\n");
                        printf("Name: %s\t ID: %d\n", name[j], id[j]);
                        for (int k = 0; k < 8; k++) {
                            printf("%s: %.2f\n", subjectNames[k], marks[j][k]);
                        }
                        printf("Total: %.2f / 800\t Percentage: %.2f%%\t Grade: %s\n\n",
                               obtainedMarks[j], percentage[j], grade[j]);
                        break;
                    }
                }

                if (!found) {
                    printf("No student found with ID: %d\n\n", searchId);
                }
                break;
            }

            case 0:
                printf("Exiting the system.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n\n");
                break;
        }

    } while (choice != 0);

    return 0;
}

