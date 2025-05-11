#define STB_DS_IMPLEMENTATION

#include "../lib/encode.h"
#include "../lib/freq.h"
#include "../lib/stb_ds.h"
#include <stdio.h>

#define DEBUG 1

int main(void) {
    // Robert Frost, The Road Not Taken
    char *text = "Two roads diverged in a yellow wood, And sorry I could not travel both And be one traveler, long I stood And looked down one as far as I could To where it bent in the undergrowth; Then took the other, as just as fair, And having perhaps the better claim, Because it was grassy and wanted wear; Though as for that the passing there Had worn them really about the same, And both that morning equally lay In leaves no step had trodden black. Oh, I kept the first for another day! Yet knowing how way leads on to way, I doubted if I should ever come back. I shall be telling this with a sigh Somewhere ages and ages hence: Two roads diverged in a wood, and I— I took the one less traveled by, And that has made all the difference.";

    // define the hash map implementations
    struct freq *freqs = NULL;
    struct encoding *encodings = NULL;

    // get the frequencies of each pair of characters into the hash map
    bpe_get_freqs(&freqs, text);

    // sort the hash map
    bpe_sort_freqs(&freqs);

    // initialize the encoded struct
    struct encoded encoded = {
        .encodings = encodings,
        .freqs = freqs,
        .text = bpe_text_to_arr(text)
    };

    // encode the text
    for (int i = 0; i < 20; i++) {
        if (i % 10 == 0 && DEBUG) {
            printf("---------- Iteration %d ----------\n", i);
            for (int i = 0; i < arrlen(encoded.text); i++) {
                printf("%u ", encoded.text[i]);
            }
            unsigned long ts = arrlen(encoded.text) * sizeof(unsigned int);
            unsigned long ks = hmlen(encoded.encodings) * sizeof(struct encoding);
            printf("\nText size: %lu\n", ts);
            printf("Key size: %lu\n", ks);
            printf("Key length: %lu\n", hmlen(encoded.encodings));
            printf("Total size: %lu\n", ts + ks);
        }
        bpe_encode(&encoded);
        bpe_sort_freqs(&encoded.freqs);
    }

    // free
    arrfree(encoded.text);
    hmfree(encoded.freqs);
    hmfree(encoded.encodings);

    return 0;
}
