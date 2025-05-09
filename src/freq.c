#include "../lib/freq.h"
#include "../lib/stb_ds.h"
#include <stdlib.h>

/**
 * bpe_get_freq() - Extracts the frequencies of character pairs in a text to a hash map implementation.
 * @freqs - The pointer to the hash map.
 * @text - The text to extract frequencies from.
 *
 * This function takes in a reference to a hash map implementation, freqs, and a text, text.
 * It will then iterate through all pairs in the text, updating the frequency in the hash map accordingly.
 */
void bpe_get_freq(struct freq **freqs, char *text) {
    // get the length of the text
    int length = strlen(text);

    // extract all pairs of characters from the text
    for (int i = 0; i < length - 1; i++) {
        // define the pair of characters to be used as the key
        struct pair p = {
            .first = text[i],
            .second = text[i+1]
        };

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
}

/**
 * bpe_compare_freqs() - A comparator function for sorting frequencies.
 * @p1 - A pointer to the first frequency.
 * @p2 - A pointer to the second frequency.
 *
 * This function is meant to be used with qsort, to sort the frequencies with the most frequent pair first.
 */
int bpe_compare_freqs(const void *p1, const void *p2) {
    struct freq *f1 = (struct freq *) p1;
    struct freq *f2 = (struct freq *) p2;
    return f2->value - f1->value;
}

/**
 * bpe_sort_freqs() - A function to sort a frequency hash map.
 * @freqs - The frequency hash map.
 *
 * This function uses qsort to sort the frequency hash map, putting the most frequent pair first.
 */
void bpe_sort_freqs(struct freq **freqs) {
    qsort(*freqs, hmlen(*freqs), sizeof(struct freq *), bpe_compare_freqs);
}
