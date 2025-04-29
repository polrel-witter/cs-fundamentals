#include <stdio.h>
#include <stdlib.h>

// Constants to improve loop performance
#define IDENT 1
#define OP *

// Abstract data types for vector
typedef int data_t;

typedef struct {
    long int len;
    data_t *data;
} vec_rec, *vec_ptr;

// Create a vector of specified length
vec_ptr new_vec(long int len)
{
    // Allocate header structure
    vec_ptr result = (vec_ptr) malloc(sizeof(vec_rec));
    if (!result)
        return NULL; // No memory allocation
    result->len = len;
    // Allocate array
    if (len > 0) {
        data_t *data = (data_t *)calloc(len, sizeof(data_t));
        if (!data) {
            free((void *) result);
            return NULL; // No memory allocation
        }
        result->data = data;
    }
    else
        result->data = NULL;
    return result;
}

// Get start of vecotor
data_t* get_vec_start(vec_ptr v)
{
    return v->data;
}

// Get vector length
long int vec_length(vec_ptr v)
{
    return v->len;
}

// Combine elements in an array using pointer as accumulator
void combine3(vec_ptr v, data_t *dest)
{
    long int i;
    long int length = vec_length(v);
    data_t *data = get_vec_start(v);

    *dest = IDENT;
    for (i = 0; i < length; i++) {
        *dest = *dest OP data[i];
    }
}

// Combine elements in an array using a separate accumulator
void combine4(vec_ptr v, data_t *dest)
{
    long int i;
    long int length = vec_length(v);
    data_t *data = get_vec_start(v);
    data_t acc = IDENT;

    for (i = 0; i < length; i++) {
        acc = acc OP data[i];
    }
    *dest = acc;
}

// Combine elements: unroll loop by 2, 2-way parallelism
//     makes use of pipelining capability of the functional units in the underlying Execution Unit (EU)
void combine5(vec_ptr v, data_t *dest)
{
    long int i;
    long int length = vec_length(v);
    long int limit = length-1;
    data_t *data = get_vec_start(v);
    data_t acc0 = IDENT;
    data_t acc1 = IDENT;

    // Combine 2 elements at a time
    for (i = 0; i < limit; i+=2) {
        acc0 = acc0 OP data[i];
        acc1 = acc1 OP data[i+1];
    }

    // Finish any remaining elements
    for (; i < length; i++) {
        acc0 = acc0 OP data[i];
    }
    *dest = acc0 OP acc1;
}

// Print vector to terminal
void print_vector(vec_ptr v) {
    long int length = v->len;
    data_t *data = v->data;

    if (!v) {
        printf("Vector is NULL\n");
        return;
    }
    printf("Vector length: %ld\n", length);
    printf("Elements: ");
    for (long int i = 0; i < length; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

// Test combine functions
int main()
{
    vec_ptr v = new_vec(5);
    data_t *dest = get_vec_start(v);

    // Init with some values to test
    for (long int i = 0; i < v->len; i++) {
        v->data[i] = i + 1;
    }

    // Test combine3()
    printf("combine3():\n");
    print_vector(v);
    combine3(v, dest);
    printf("Accumulated value: %d\n", *dest);

    // TODO: need to reset dest and first element

    // Test combine4()
    printf("combine4():\n");
    print_vector(v);
    combine4(v, dest);
    printf("Accumulated value: %d\n", *dest);

    // Test combine5()
    printf("combine5():\n");
    print_vector(v);
    combine5(v, dest);
    printf("Accumulated value: %d\n", *dest);

    free(v->data);
    free(v);
    return 0;
}
