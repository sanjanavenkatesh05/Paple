#include <stdio.h>

int main() {
    int frames, pages, frame[10], page[30];
    int i, j, k, faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &pages);

    printf("Enter page reference string:\n");
    for (i = 0; i < pages; i++)
        scanf("%d", &page[i]);

    // Clear input buffer to discard any extra numbers on the line
    while ((getchar()) != '\n');

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    // Initialize frames to empty (-1)
    for (i = 0; i < frames; i++)
        frame[i] = -1;

    // Process each page
    for (i = 0; i < pages; i++) {
        int flag = 0; // 1 if page found, else 0

        // Check if page is already present in a frame
        for (j = 0; j < frames; j++)
            if (frame[j] == page[i])
                flag = 1;

        // If page is NOT found -> Page Fault
        if (flag == 0) {

            // If there is an empty frame, fill it first
            int empty = -1;
            for (j = 0; j < frames; j++)
                if (frame[j] == -1) {
                    empty = j;
                    break;
                }

            // If empty frame found -> directly insert
            if (empty != -1) {
                frame[empty] = page[i];
            }
            else {
                // Apply OPTIMAL Page Replacement

                int farthest = -1;
                int index = -1;

                // For each frame, find when it will be used next
                for (j = 0; j < frames; j++) {
                    int nextUse = -1;

                    for (k = i + 1; k < pages; k++) {
                        if (frame[j] == page[k]) {
                            nextUse = k;  // next time page appears
                            break;
                        }
                    }

                    // If not found in future -> best to replace this frame
                    if (nextUse == -1) {
                        index = j;
                        break;
                    }

                    // Select page with farthest future use
                    if (nextUse > farthest) {
                        farthest = nextUse;
                        index = j;
                    }
                }

                frame[index] = page[i];
            }

            faults++;
        }

        // Print frame table
        printf("\nFor page %d: ", page[i]);
        for (j = 0; j < frames; j++)
            printf("%d ", frame[j]);
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}
