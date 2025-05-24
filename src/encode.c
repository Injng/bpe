#include "../lib/encode.h"
#include "../lib/freq.h"
#include "../lib/stb_ds.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

unsigned int *bpe_text_to_arr(char *text)
{
  // get length of text
  int length = strlen(text);

  // initialize new dynamic array
  unsigned int *text_arr = NULL;

  // iterate through characters and add to array
  for (int i = 0; i < length; i++) {
    arrput(text_arr, (unsigned int)(unsigned char)text[i]);
  }

  return text_arr;
}

unsigned int bpe_next_encoding(struct encoding **encodings)
{
  // check if any encodings are assigned already, otherwise, start at 256
  unsigned int start_encoding = 256;
  if (hmlen(*encodings) > 0) {
    start_encoding = (*encodings)[hmlen(*encodings) - 1].value + 1;
  }
  return start_encoding;
}

unsigned int bpe_assign_encoding(struct encoding **encodings, struct pair p)
{
  // get the next assignable encoding
  unsigned int start_encoding = bpe_next_encoding(encodings);

  // ensure that an encoding has not already been assigned
  if (hmgeti(*encodings, p) >= 0)
    return hmget(*encodings, p);

  // assign the next integer to the pair
  hmput(*encodings, p, start_encoding);
  return start_encoding;
}

unsigned long bpe_get_size(unsigned int *text, struct encoding *encodings)
{
  unsigned long ts = arrlen(text) * sizeof(unsigned int);
  unsigned long ks = hmlen(encodings) * sizeof(struct encoding);
  return ts + ks;
}

int bpe_encode(struct encoded *encoded)
{
  // get the most frequent pair from the frequency table and its encoding
  struct pair p = encoded->freqs[0].key;
  unsigned int encoding = bpe_next_encoding(&encoded->encodings);
  unsigned long prev_size = bpe_get_size(encoded->text, encoded->encodings);

  // create new, encoded version of the text with a dynamic array
  unsigned int *new_text = NULL;

  // implement a sliding window of size 2 to check each pair of characters
  int idx = 0;
  while (idx < arrlen(encoded->text) - 1) {
    // get the current pair
    unsigned int first = encoded->text[idx];
    unsigned int second = encoded->text[idx + 1];

    // check if the pairs match
    if (first == p.first && second == p.second) {
      // if they match, replace with encoding in new text
      arrput(new_text, encoding);

      // jump to next pair
      idx += 2;
    } else {
      // otherwise, copy the character over to the new array
      arrput(new_text, first);

      // go to next character
      idx++;
    }
  }

  // check if last character needs to be added to array
  if (idx < arrlen(encoded->text)) {
    arrput(new_text, encoded->text[arrlen(encoded->text) - 1]);
  }

  // get new size and compare
  unsigned long new_size = bpe_get_size(new_text, encoded->encodings);
  new_size += sizeof(struct encoding);
  if (new_size > prev_size) {
    arrfree(new_text);
    return -1;
  }

  // replace old text array with new text array and add encoding
  arrfree(encoded->text);
  encoded->text = new_text;
  bpe_assign_encoding(&encoded->encodings, p);

  // recalculate frequencies
  encoded->freqs = bpe_get_freqs_from_arr(&encoded->freqs, new_text);

  return 0;
}
