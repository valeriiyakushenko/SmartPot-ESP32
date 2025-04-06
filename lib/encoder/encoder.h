#ifndef ENCODER_H
#define ENCODER_H

#include <EncButton.h>
#include <config.h>
#include <../../src/constants.h>

extern int currentPage;

bool isEncoderButtonPressed();
void initEncoder();

#endif