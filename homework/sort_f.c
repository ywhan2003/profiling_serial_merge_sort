/**
 * Copyright (c) 2012 MIT License by 6.172 Staff
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 **/


#include "./util.h"

static const int BASE_NUMBER = 10;
data_t* temporary = 0;

// Function prototypes
static void merge_f(data_t* A, int p, int q, int r);
static void copy_f(data_t* source, data_t* dest, int n);
static void base_f(data_t* A, int p, int r);
static void recursive_f(data_t* A, int p, int r);

// A basic merge sort routine that sorts the subarray A[p..r]
void sort_f(data_t* A, int p, int r) {
  mem_alloc(&temporary, r - p + 1);
  recursive_f(A, p, r);
  mem_free(&temporary);
}

// A merge routine. Merges the sub-arrays A [p..q] and A [q + 1..r].
// Uses two arrays 'left' and 'right' in the merge operation.
static void merge_f(data_t* A, int p, int q, int r) {
  assert(A);
  assert(p <= q);
  assert((q + 1) <= r);
  int n1 = q - p + 1;
  int n2 = r - q;

  data_t* left = temporary, * right = A + q + 1;

  copy_f(A + p, left, n1);

  int i = 0; // Current index of the left part
  int j = 0; // Current index of the right part
  int k = p; // Current index of the previous array

  for (; k <= r && i < n1 && j < n2; k++) {
    if (*(left + i) <= *(right + j)) {
      *(A + k) = *(left + i);
      i++;
    } else {
      *(A + k) = *(right + j);
      j++;
    }
  }

  if (k > r) {
    return;
  }

  if (i >= n1) {
    copy_f(right + j, A + k, n2 - j);
  }

  copy_f(left + i, A + k, n1 - i);
}

static void copy_f(data_t* source, data_t* dest, int n) {
  assert(dest);
  assert(source);

  for (int i = 0 ; i < n ; i++) {
    *(dest + i) = *(source + i);
  }
}

static void base_f(data_t* A, int p, int r) {
  assert(A);
  assert(p < r);

  data_t* cur = A + p + 1;
  data_t* begin = A + p;
  data_t* end = A + r;

  while (cur <= end) {
    data_t val = *cur;
    data_t* index = cur - 1;

    while (index >= begin && *index > val) {
      *(index + 1) = *index;
      index--;
    }

    *(index + 1) = val;
    cur++;
  }
}

void recursive_f(data_t* A, int p, int r) {
  assert(A);
  if (p >= r) {
    return;
  }
  
  int num_element = r - p + 1;
  if (num_element < BASE_NUMBER) {
    base_f(A, p, r);
    return;
  }

  int q = (p + r) / 2;
  recursive_f(A, p, q);
  recursive_f(A, q + 1, r);
  merge_f(A, p, q, r);
}