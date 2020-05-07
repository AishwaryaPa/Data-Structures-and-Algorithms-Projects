// File: joke.h
//
// CMSC 341 Spring 2017 Project 0
//
// Header file for knock-knock jokes
//
// Do not make any changes to this file.
//

#ifndef _JOKE_H_
#define _JOKE_H_

#include <string>
using namespace std ;

// Name: opening()
// Pre-condition: Starts the joke
// Post-condition: Returns an opening string for the knock knock joke 
string opening() ;

// Name: setup()
// Pre-condition: Opening has to be called first from the driver
// Post-condition: Returns a setup string for the knock knock joke
string setup() ;

// Name: punchline()
// Pre-condition: Last part of the joke, so has to be called after opening and setup
// Post-condition: Returns a punchline joke for the knock knock joke 
string punchline() ;

#endif
