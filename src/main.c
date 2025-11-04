#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_COUNT 50
#define MAX_SUCCESSOR_COUNT (MAX_WORD_COUNT / 10)

char book[] = {
#embed "pg84.txt"
    , '\0'};

/// Array of tokens registered so far
/// No duplicates are allowed.
char *tokens[MAX_WORD_COUNT];
/// `tokens`'s current size
size_t tokens_size = 0;

/// Array of successor tokens
/// One token can have many successor tokens. `succs[x]` corresponds to
/// `token[x]`'s successors.
/// We store directly tokens instead of token_ids, because we will directly
/// print them. If we wanted to delete the book, then it would make more sense
/// to store `token_id`s
char *succs[MAX_WORD_COUNT][MAX_SUCCESSOR_COUNT];
/// `succs`'s size
size_t succs_sizes[MAX_WORD_COUNT];

/// Overwrites non-printable characters in `book` with a space.
/// Non-printable characters may lead to duplicates like
/// `"\xefthe" != "the"` even both print `the`.
void replace_non_printable_chars_with_space() {
  char *src = book;

  while (*src) {
    if (!isprint((unsigned char)*src) && !isspace((unsigned char)*src)) {
      // replace with a space
      *src = ' ';
    }
    // move to next char
    src++;
  }
}

/// Returns token id if token is known, otherwise creates a new entry and
/// returns the new token id
size_t token_id(char *token) {
  for (size_t i = 0; i < tokens_size; i++) {
    if (strcmp(tokens[i], token) == 0) {
      // return token's index
      return i;
    }
  }
  // add new/unknown token
  tokens[tokens_size] = token;
  tokens_size++;
  return tokens_size - 1;
}

/// Appends a token to the successors list of a `token`
void append_to_succs(char *token, char *succ) {
  size_t id = token_id(token);
  size_t amount_of_succs = succs_sizes[id];

  for (size_t i = 0; i < amount_of_succs; i++) {
    char *word = succs[id][i];
    if (strcmp(word, succ) == 0) {
      // the succ is already in the successor list
      return;
    }
  }
  // add succ as last element in successor list
  succs[id][amount_of_succs] = succ;
  succs_sizes[id] = amount_of_succs + 1;
}

/// Creates tokens from the `book` and fills `tokens` and `succs` arrays using
/// the `token`s.
void tokenize_and_fill_succs(char *delimiters, char *str) {
  char *prev_token = NULL;
  char *current_token = strtok(str, delimiters);

  while (current_token != NULL) {
    // Register token if it's new
    size_t id = token_id(current_token);

    if (prev_token != NULL) {
      // Link previous token → current token
      append_to_succs(prev_token, current_token);
    }

    prev_token = current_token;
    current_token = strtok(NULL, delimiters);
  }
}

/// Returns last character of a string
char last_char(char *str) {
  size_t len = strlen(str);
  return str[len - 1];
}

/// Returns whether the token ends with `!`, `?` or `.`.
bool token_ends_a_sentence(char *token) {
  // YOUR CODE HERE
  char *punctuations[] = {"!", "?", "."};
}

/// Returns a random `token_id` that corresponds to a `token` that starts with a
/// capital letter.
/// Uses `tokens`, `tokens_size.
size_t random_token_id_that_starts_a_sentence() {
  // YOUR CODE HERE
}

/// Generates a random sentence using `tokens`, `succs`, and `succs_sizes`.
/// The sentence array will be filled up to `sentence_size-1` characters using
/// random tokens until:
/// - a token is found where `token_ends_a_sentence()`
/// - or more tokens cannot be concatenated to the `sentence` anymore.
///  Returns the filled sentence array.
char *generate_sentence(char *sentence, size_t sentence_size) {
  size_t current_token_id = random_token_id_that_starts_a_sentence();
  auto char *token = tokens[current_token_id];

  strcat(sentence, token);
  if (token_ends_a_sentence(token))
    return sentence;

  // Calculated sentence length for the next iteration.
  // Used to stop the loop if the length exceeds sentence size
  size_t sentence_len_next;
  // Concatenates random successors to the sentence as long as
  // `sentence` can hold them.
  do {
    // YOUR CODE HERE
  } while (sentence_len_next < sentence_size - 1);
  return sentence;
}

int main() {
  replace_non_printable_chars_with_space();

  char *delimiters = " \n\r";
  tokenize_and_fill_succs(delimiters, book);

  char sentence[1000];
  srand(time(NULL));

  // Initialize `sentence` and then find a question sentence.
  do {
    // YOUR CODE HERE
    generate_sentence(sentence, sizeof sentence);
  } while (last_char(sentence) != '?');
  puts(sentence);
  puts("");

  // Initialize `sentence` and then find a sentence ending with exclamation
  // mark.
  do {
    // YOUR CODE HERE
    generate_sentence(sentence, sizeof sentence);
  } while (last_char(sentence) != '!');
  puts(sentence);
}