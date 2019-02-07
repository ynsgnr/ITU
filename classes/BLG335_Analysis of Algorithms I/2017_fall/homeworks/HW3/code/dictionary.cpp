#ifdef DEBUG
#define DEBUGMODE(code) code
#else
#define DEBUGMODE(code)
#endif

#ifndef DICTIONARY_CPP
#define DICTIONARY_CPP

#include "dictionary.h"
#include "bookChar.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>

#define H(key) floor((float)HASHTABLESIZE*fmod((float)key*0.618,1.0))
#define H2(h,i) ((long)h+7*i+3*i*i)%HASHTABLESIZE

int dictionary::insert(bookChar character){
  unsigned long collisionCounter=0;
  int h = H(character.key);
  DEBUGMODE(printf("Calculated hash %d for key %d\n",h,character.key);)
  while(hashTable[h].page!=0 || hashTable[h].line!=0 || hashTable[h].index!=0){
    //detect Collison
    collisionCounter++;
    DEBUGMODE(printf("Collison occured on hash %d with key %d. This is %ld. time\n",h,hashTable[h].key,collisionCounter);)
    h=H2(h,collisionCounter);
    DEBUGMODE(printf("Calculated hash %d for key %d\n",h,character.key);)
  }
  //insert
  hashTable[h]=character;
  return collisionCounter;
}

bookChar dictionary::lookup(int key){
  unsigned long i=0;
  int h = H(key);
  DEBUGMODE(std::cout << "Calculated hash as "<< h <<" for key "<< key << '\n';)
  if(h>HASHTABLESIZE || hashTable[h].page==0)
    return bookChar();
  while(hashTable[h].key!=key){
    DEBUGMODE(std::cout << "Collusion with key "<< hashTable[h].key << " on hash "<< h << " looking for" << key <<'\n';)
    i++;
    h=H2(h,i);
  }
  if (h>=HASHTABLESIZE)
    return bookChar();

  return hashTable[h];
}

#endif
