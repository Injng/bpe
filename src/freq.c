#include "../lib/freq.h"
#include "../lib/stb_ds.h"
#include <stdlib.h>
#include <string.h>

void bpe_add_freq(struct freq **freqs, struct pair p) {
    // check if the key exists in the hash map
    if (hmgeti(*freqs, p) >= 0) {
        // if so, get and update the frequency
        int value = hmget(*freqs, p);
        hmput(*freqs, p, ++value);
    } else {
        // otherwise, create a new key-value pair
        hmput(*freqs, p, 1);
    }
}

void bpe_get_freqs(struct freq **freqs, char *text) {
    // get the length of the text
    int length = strlen(text);

    // extract all pairs of characters from the text
    for (int i = 0; i < length - 1; i++) {
        // define the pair of characters to be used as the key
        struct pair p = {
            .first = (unsigned int) text[i],
            .second = (unsigned int) text[i+1]
        };

        // add the pair to the frequency hash map
        bpe_add_freq(freqs, p);
    }
}

int bpe_compare_freqs(const void *p1, const void *p2) {
    struct freq *f1 = (struct freq *) p1;
    struct freq *f2 = (struct freq *) p2;
    return f2->value - f1->value;
}

void bpe_sort_freqs(struct freq **freqs) {
    qsort(*freqs, hmlen(*freqs), sizeof(struct freq), bpe_compare_freqs);
}
