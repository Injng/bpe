#ifndef FREQ_H
#define FREQ_H

/**
 * struct pair - Defines a pair of characters representing a single unit in
 * byte pair encoding.
 * @first: The first in the pair of characters.
 * @second: The second in the pair of characters.
 *
 * The pair structure is used to encode information about a pair of characters
 * used in byte pair encoding. It is created to be used as the key in a
 * key-value pair for a hash map implementation.
 */
struct pair {
    unsigned int first;
    unsigned int second;
};

/**
 * struct freq - Defines a key-value pair with the key as a pair of characters
 * and the value as the frequency of that pair.
 * @key: The pair of characters as the key.
 * @value: The frequency as the value.
 *
 * The freq structure is used to encode information about the frequency a pair
 * of characters appear in a set of text. The pair of characters is the key
 * used to access the key-value pair, and the frequency is the value. This
 * structure is meant to be used as a key-value pair in the stb hash map
 * implementation.
 */
struct freq {
    struct pair key;
    int value;
};

/**
 * bpe_add_freq() - Adds the frequency of a character pair to the hash map.
 * @freqs - The pointer to the hash map.
 * @p - The character pair to add.
 *
 * This function takes in a reference to a hash map implementation, freqs, and
 * a character pair, p. It will then attempt to retrieve the current frequency
 * of that character pair from freqs. If it exists, it will increment the
 * frequency by 1; if it doesn't exist, the pair will be added to the hash
 * map and the frequency will be set to 1.
 */
void bpe_add_freq(struct freq **freqs, struct pair p);

/**
 * bpe_get_freq() - Extracts the frequencies of character pairs in a text to a
 * hash map implementation.
 * @freqs - The pointer to the hash map.
 * @text - The text to extract frequencies from.
 *
 * This function takes in a reference to a hash map implementation, freqs, and
 * a text, text. It will then iterate through all pairs in the text, updating
 * the frequency in the hash map accordingly.
 */
void bpe_get_freqs(struct freq **freqs, char *text);

/**
 * bpe_compare_freqs() - A comparator function for sorting frequencies.
 * @p1 - A pointer to the first frequency.
 * @p2 - A pointer to the second frequency.
 *
 * This function is meant to be used with qsort, to sort the frequencies with
 * the most frequent pair first.
 */
int bpe_compare_freqs(const void *p1, const void *p2);

 /**
  * bpe_sort_freqs() - A function to sort a frequency hash map.
  * @freqs - The frequency hash map.
  *
  * This function uses qsort to sort the frequency hash map, putting the most
  * frequent pair first.
  */
void bpe_sort_freqs(struct freq **freqs);

#endif
