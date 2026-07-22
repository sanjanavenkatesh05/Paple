#include <stdio.h>

int main() {
    int frames, pages, frame[10], page[30];
    int i, j, k = 0, faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &pages);

    printf("Enter page reference string:\n");
    for (i = 0; i < pages; i++)
        scanf("%d", &page[i]);

    // Clear input buffer to discard any extra numbers on the line
    while ((getchar()) != '\n');

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    // Initialize frames
    for (i = 0; i < frames; i++)
        frame[i] = -1;

    for (i = 0; i < pages; i++) {
        int flag = 0;

        // Check if page already exists
        for (j = 0; j < frames; j++)
            if (frame[j] == page[i])
                flag = 1;

        if (flag == 0) {
            frame[k] = page[i];  
            k = (k + 1) % frames; // FIFO pointer
            faults++;
        }

        printf("\nFor page %d: ", page[i]);
        for (j = 0; j < frames; j++)
            printf("%d ", frame[j]);
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}
