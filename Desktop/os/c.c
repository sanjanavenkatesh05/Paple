#include <stdio.h>

int main() {
    int frames, pages, page[30], frame[10], counter[10];
    int i, j, faults = 0, time = 0;

    printf("Enter number of pages: ");
    scanf("%d", &pages);

    printf("Enter page reference string:\n");
    for (i = 0; i < pages; i++)
        scanf("%d", &page[i]);

    // Clear input buffer to discard any extra numbers on the line
    while ((getchar()) != '\n');

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    for (i = 0; i < frames; i++) {
        frame[i] = -1;
        counter[i] = 0;
    }

    for (i = 0; i < pages; i++) {
        int flag = 0;

        // Check if page already exists
        for (j = 0; j < frames; j++)
            if (frame[j] == page[i]) {
                flag = 1;
                counter[j] = ++time; // update recent use time
            }

        // Insert page
        if (flag == 0) {
            
            // Should check for empty slots first before replacing via LRU?
            // The provided code blindly finds min counter.
            // If frame is initialized to -1 and counter to 0. 
            // Slots with -1 will have counter 0 (or low). 
            // But if all counters are 0 (start), it will pick index 1?
            
            // Let's refine the logic slightly to fill empty frames first if needed, 
            // OR checks if the provided logic handles it. 
            // Provided logic: min = 0. loop j=1..frames. if counter[j] < counter[min] min=j.
            // Initially all counters are 0. So min remains 0. Replaces frame[0].
            // Next time, counter[0] is high. min will be 1 (since counter[1] is 0).
            // It seems to implicitly handle filling empty slots sequentially if counters are 0.
            
            int min = 0;

            // Find LRU frame
            for (j = 1; j < frames; j++)
                if (counter[j] < counter[min])
                    min = j;

            frame[min] = page[i];
            counter[min] = ++time;
            faults++;
        }

        printf("\nFor page %d: ", page[i]);
        for (j = 0; j < frames; j++)
            printf("%d ", frame[j]);
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}
