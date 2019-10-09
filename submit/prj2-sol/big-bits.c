
#include "big-bits.h"
#include "hex-util.h"
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

/** Provide concrete definition for struct BigBits to flesh out
 *  abstract BigBits data type.
 */
struct BigBits {
  //@TODO
  // pointer to the array
  char *c;
  // int that keeps track of size
  int size;
};

/** Return a pointer to a representation of a big integer with value
 *  corresponding to the non-empty hexadecimal string hex.  Note that
 *  hex will only contain hexadecimal characters '0' - '9', 'a' - 'f'
 *  and 'A' - 'F' terminated by a NUL '\0' char.
 *
 *  The string hex may not remain valid after this function returns.
 *
 *  Returns NULL on error with errno set "appropriately".
 */
// TA: get string in, convert to bigBits according to data types, and then return pointer to that bigBit

const BigBits *
newBigBits(const char *hex)
{
  // error checking
  assert(CHAR_BIT == 8);

  //@TODO
  // tret hex as array (pointer)
  // while hex is not ending in null
  // get size of hex
  int size = 0;
  while(hex[size] != '\0'){
	  size++;
  }
  // can i just get the size of above using sizeof() here
  // use int size = strlen(hex) + 1;

  // using size, go through and break into array
  // Big Endian order
  char * bigBit = (char *) malloc(size+1);

  for(int j = 0; j <= size; j++){
	  bigBit[j] = hex[j];
  }
 char *pointer = bigBit;
  // Make struct object with attributes
  // any memory that you use inside a function disappears when the function is done
 // size of struct: fixed -> only consists of a pointer to a char array and an int
 // 8 bytes + 4 bytes = 12 bytes
  struct BigBits * big  = (struct BigBits *) malloc(sizeof(struct BigBits));
  // initializes on the heap
  big->c = pointer;
  big->size = size;
  return  big;
}

/** Frees all resources used by currently valid bigBits.  bigBits
 *  is not valid after this function returns.
 */

// TA:  free memory on heap and memory
void
freeBigBits(BigBits *bigBits)
{
  //@TODO
  // HEAP:
  free(bigBits->c);
  free(bigBits);
}


/** Return a lower-case hex string representing bigBits. Returned
 *  string should not contain any non-significant leading zeros.
 *  Returns NULL on error with errno set "appropriately".  (Note that
 *  th:c
 */
// TA: return formatted resulting bigBit
const char *
stringBigBits(const BigBits *bigBits)
{
  //@TODO
  int i = 0;
  while(bigBits->c[i] == '0' || bigBits->c[i] == 'x'){
	  i++;
  }
  
 // updated pointer to bigBits without leading zeros
 const char* new_bigBits = &(bigBits->c[i]);
 return new_bigBits;
}


/** Return a new BigBits which is the bitwise-& of bigBits1 and bigBits2.
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
andBigBits(const BigBits *bigBits1, const BigBits *bigBits2)
{
  //@TODO
  // steps:
  //  determine shorter operand & create a bigBit of that length
  // malloc for returnBigBits
  //  iterate through each array and & each element to eachother
  // create pointer to returnBigBits
 
  // get size of shorter array
  int returnSize = bigBits1->size;
  if(bigBits2->size < returnSize) returnSize = bigBits2->size;
  // malloc for returnBigBits
  struct BigBits * returnBigBits = (struct BigBits *) malloc(sizeof(struct BigBits));
  // declare an array equal to returnSize (make sure to set = returnBigBits.c
 // char returnArray[returnSize];
  returnBigBits->c = (char *) malloc(returnSize+1);
 // returnBigBits->c = returnArray;

  // iterate through each array and change to numbers to and to eachother
  for(int i = 0; i < returnSize; i++){
	bigBits1->c[i] =  ifChar(bigBits1->c[i]);
  }
  for(int j = 0; j < returnSize; j++){
	  bigBits2->c[j] = ifChar(bigBits2->c[j]);
  }
  // go through each array and & each one to eachother
  for(int k = 0; k < returnSize; k++){
	  returnBigBits->c[k] = bigBits1->c[k] & bigBits2->c[k];
  }
  // convert all the numbers back to characters
  for(int t = 0; t < returnSize; t++){
	  returnBigBits->c[t] = ifNum(returnBigBits->c[t]);
  }
  // set returnBigBits to returnSize
  returnBigBits->size = returnSize;
  return returnBigBits;
}


int ifChar(char c){
	// check type 
	if(c >= '0' && c <= '9'){
		return c - '0';
	}
	// check letter and return appropriate integer
	else if (c == 'a' || c == 'A'){
		return 10;
	}
	else if (c == 'b' || c == 'B'){
		return 11;
	}
	else if (c == 'c' || c == 'C'){
		return 12;
	}
	else if (c == 'd' || c == 'D'){
		return 13;
	}
	else if (c == 'e' || c == 'E'){
		return 14;
	}
	else{ //(if c == 'f'){
		return 15;
	}
}

char ifNum(int i){
	// check type 
	if(i >= 0 && i <= 9){
		return i + '0';
	}
	// check letter and return appropriate integer
	else if (i == 10){
		return 'a';
	}
	else if (i == 11){
		return 'b';
	}
	else if (i == 12){
		return 'c';
	}
	else if (i == 13){
		return 'd';
	}
	else if (i == 14){
		return 'e';
	}
	else{// if (i == 15){
		return 'f';
	}
}



/** Return a new BigBits which is the bitwise-| of bigBits1 and bigBits2.
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
orBigBits(const BigBits *bigBits1, const BigBits *bigBits2)
{
  //@TODO
  //steps:
  // 1. determine LONGER operand and create bigBit of that lenght
  // 2. malloc for pointer and struct
  // find out shorter array and | with zeroes to equal length of other ar	ray
  // 3. iterate through each array and | each element to eachotehr
  // 4. translate back to numb
  
  _Bool isLarger = bigBits1->size > bigBits2->size;
  int returnSize = bigBits2->size;
  int shorterSize = bigBits1->size;
  if(isLarger){
 	returnSize = bigBits1->size;
       	shorterSize = bigBits2->size;
  }

  //malloc for return val
  struct BigBits * returnBigBits = (struct BigBits *) malloc(sizeof(struct BigBits));
  // malloc for returnBigBits->c
  returnBigBits->c = (char *) malloc(returnSize+1);
  // find out length of shorter array
  for(int i = 0; i < returnSize; i++){
	  bigBits1->c[i] = ifChar(bigBits1->c[i]);
  }
  for(int j = 0; j < returnSize; j++){
	  bigBits2->c[j] = ifChar(bigBits2->c[j]);
  }
  // go through all the filled-in numbers and or them
  if(isLarger){
	  for(int k = 0; k < (returnSize - shorterSize); k++){
		  returnBigBits->c[k] = bigBits1->c[k] | 0;
	  }
	  for(int a = 0; a < returnSize; a++){
		  returnBigBits->c[a + (returnSize - shorterSize)] = bigBits1->c[a +(returnSize - shorterSize)] | bigBits2->c[a];
  }
  }
  else if(!isLarger){
	  for(int h = 0; h < (returnSize - shorterSize); h++){
		  returnBigBits->c[h] = bigBits2->c[h] | 0;
	  }
	  for(int g = 0; g < returnSize; g++){
		  returnBigBits->c[g + (returnSize - shorterSize)] = bigBits2->c[g + (returnSize - shorterSize)] | bigBits1->c[g];
  }
  }
  for(int n = 0; n < returnSize; n++){
	  returnBigBits->c[n] = ifNum(returnBigBits->c[n]);
  }
  returnBigBits->size = returnSize;
  return returnBigBits;

}

/** Return a new BigBits which is the bitwise-^ of bigBits1 and bigBits2.
 *  Returns NULL on error with errno set "appropriately".
 */
const BigBits *
xorBigBits(const BigBits *bigBits1, const BigBits *bigBits2)
{
  //@TODO
   _Bool isLarger = bigBits1->size > bigBits2->size;
  int returnSize = bigBits2->size;
  int shorterSize = bigBits1->size;
  if(isLarger){
 	returnSize = bigBits1->size;
       	shorterSize = bigBits2->size;
  }

  //malloc for return val
  struct BigBits * returnBigBits = (struct BigBits *) malloc(sizeof(struct BigBits));
  // malloc for returnBigBits->c
  returnBigBits->c = (char *) malloc(returnSize+1);
  // find out length of shorter array
  for(int i = 0; i < returnSize; i++){
	  bigBits1->c[i] = ifChar(bigBits1->c[i]);
  }
  for(int j = 0; j < returnSize; j++){
	  bigBits2->c[j] = ifChar(bigBits2->c[j]);
  }
  // go through all the filled-in numbers and or them
  if(isLarger){
	  for(int k = 0; k < (returnSize - shorterSize); k++){
		  returnBigBits->c[k] = bigBits1->c[k] ^ 0;
	  }
	  for(int a = 0; a < returnSize; a++){
		  returnBigBits->c[a + (returnSize - shorterSize)] = bigBits1->c[a +(returnSize - shorterSize)] ^ bigBits2->c[a];
  }
  }
	else if(!isLarger){
		  for(int h = 0; h < (returnSize - shorterSize); h++){
			  returnBigBits->c[h] = bigBits2->c[h] ^ 0;
	  }
		  for(int g = 0; g < returnSize; g++){
			  returnBigBits->c[g + (returnSize - shorterSize)] = bigBits2->c[g + (returnSize - shorterSize)] ^ bigBits1->c[g];
  	}
  	}
  for(int n = 0; n < returnSize; n++){
	  returnBigBits->c[n] = ifNum(returnBigBits->c[n]);
  }
  returnBigBits->size = returnSize;
  return returnBigBits;


}
