#include <xc.h>
#include <inttypes.h>
#include <stdio.h>

//Module Includes Here

#define NUM_ITERATIONS 100000
#define NUM_REPS 10
uint8_t buffer[64];

void test_uint8_mult(){
    uint32_t i;
    double i1,i2,i3;
    i1 = 1.1234567812;
    i2 = 2.9876543213;
    for (i=0; i < NUM_ITERATIONS; i++){
      i3 = i1*i2;
      i3 = i1*i2;
      i3 = i1*i2;
      i3 = i1*i2;
      i3 = i1*i2;
      i3 = i1*i2;
      i3 = i1*i2;
      i3 = i1*i2;
      i3 = i1*i2;
      i3 = i1*i2;
    }
}

void test_uint8_div(){
    uint32_t i;
    double i1,i2,i3;
    i1 = 1.1234567812;
    i2 = 2.9876543213;
    for (i=0; i < NUM_ITERATIONS; i++){
      i3 = i1/i2;
      i3 = i1/i2;
      i3 = i1/i2;
      i3 = i1/i2;
      i3 = i1/i2;
      i3 = i1/i2;
      i3 = i1/i2;
      i3 = i1/i2;
      i3 = i1/i2;
      i3 = i1/i2;
    }
}

void test_uint8_add(){
    uint32_t i;
    double i1,i2,i3;
    i1 = 1.1234567812;
    i2 = 2.9876543213;
    for (i=0; i < NUM_ITERATIONS; i++){
      i3 = i1+i2;
      i3 = i1+i2;
      i3 = i1+i2;
      i3 = i1+i2;
      i3 = i1+i2;
      i3 = i1+i2;
      i3 = i1+i2;
      i3 = i1+i2;
      i3 = i1+i2;
      i3 = i1+i2;
    }
}

void test_uint8_sub(){
    uint32_t i;
    double i1,i2,i3;
    i1 = 1.1234567812;
    i2 = 2.9876543213;
    for (i=0; i < NUM_ITERATIONS; i++){
      i3 = i1-i2;
      i3 = i1-i2;
      i3 = i1-i2;
      i3 = i1-i2;
      i3 = i1-i2;
      i3 = i1-i2;
      i3 = i1-i2;
      i3 = i1-i2;
      i3 = i1-i2;
      i3 = i1-i2;
    }
}
