#include "fn-trace.h"
#include "x86-64_lde.h"

#include "memalloc.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum {
  CALL_OP = 0xE8,
  RET_FAR_OP = 0xCB,
  RET_FAR_WITH_POP_OP = 0xCA,
  RET_NEAR_OP = 0xC3,
  RET_NEAR_WITH_POP_OP = 0xC2
};

typedef struct FnsData{
	struct FnInfo * pointer = NULL;
	// keep track of size
	int size = 0;
	// current index
	int index = 0;
}fnsData;

static inline bool is_call(unsigned op) { return op == CALL_OP; }
static inline bool is_ret(unsigned op) {
  return
    op == RET_NEAR_OP || op == RET_NEAR_WITH_POP_OP ||
    op == RET_FAR_OP || op == RET_FAR_WITH_POP_OP;
}

// Called by new_fns_data
// Purpose: Add info about function represented by addr (called by rootFn) and all functions called directly or indirectly by the function as long as the functions havent been seen earlier.
void fn_trace(void * addr, FnsData fnsData){
	int curr_index = fnsData.index;
	if(curr_index >= fnsData.size){
		reallocChk(&fnsData, curr_index * sizeof(FnInfo));
		fnsData.size++;
	}
	struct fnInfo newInfo;
	newInfo.address = *addr;
	newInfo.nInCalls = 1;
	unsigned char * start = (unsigned char *)addr;
	int func_length = 0;
	int nOutCalls = 0;
	while(!isret(*start)){
		if(is_call(*start)){
			void *newAddress = 0;
			// if address is already in FnsData
			int exist = 0;
			for(int i = 0; i < fnsData->size; i++){
				if(newAddress==fnsData[i].address){
					fnsData[i].nInCalls++;
					exist = 1;
				}
			}
			if(exits == 0){
				fn_trace(newAddress, fnsData);
			}
			nOutCalls++;
		}
		else{
			// get length of current instruction
			int instr_len = get_op_length(*start);
			// increment address
			start+= instr_len;
			//accumulate total len
			func_len += instr_len;
			// set outCall
			newInfo.nOutCalls = nOutCalls;
			// put in FnsData
			fnsData[currIndex] = newInfo;
		}
}
/** Return pointer to opaque data structure containing collection of
 *  FnInfo's for functions which are callable directly or indirectly
 *  from the function whose address is rootFn.
 */
const FnsData *
new_fns_data(void *rootFn)
{
  //verify assumption used when decoding call address
  assert(sizeof(int) == 4);
  //@TODO
  /*
	typedef struct FnsData{
		//array (a collection of FnInfos)
		FnInfo * pointer = NULL;
		// keep track of size
		int size = 0;
		// current index
		int index = 0;
	}fnsData;
	*/
  // get rootFn to begin, unsigned op to get first step
  unsigned char *op = (unsigned char *)rootFn;
  // realloc for memory
  struct FnInfo firstInfo = reallocChk(*op, sizeof(FnInfo));
  while(!is_ret(*op)){
	  if(is_call(*op)){
		  firstInfo->nOutCalls++;
		  if((firstInfo->nInCalls >= 1){
			  firstInfo->nInCalls++;
			  fnInfo->length += get_op_length(*op);
		  }
		  // if function hasn't been called before
		  if((fnInfo->nInCalls) == 0){
		  	firstInfo->nInCalls++;
			//firstInfo->nOutCalls++;
			// use fn_trace to get data of new function
			 void * new_func = firstInfo->address;
			 fn_trace(new_func, fnsData);
		}
		}
		else{
		// get instr_len
		int instr_len = get_op_length(*op);
		printf("length: %d\n", instr_len);
		firstInfo-> length += instr_len;
		// update pointer
		op+= instr_len
  }
  return NULL;
}


/** Free all resources occupied by fnsData. fnsData must have been
*  returned by new_fns_data().  It is not ok to use to fnsData after
 *  this call.
 */
void
free_fns_data(FnsData *fnsData)
{
  //@TODO
  free(fnsData);
}

/** Iterate over all FnInfo's in fnsData.  Make initial call with NULL
 *  lastFnInfo.  Keep calling with return value as lastFnInfo, until
 *  next_fn_info() returns NULL.  Values must be returned sorted in
 *  increasing order by fnInfoP->address.
 *
 *  Sample iteration:
 *
 *  for (FnInfo *fnInfoP = next_fn_info(fnsData, NULL); fnInfoP != NULL;
 *       fnInfoP = next_fn_info(fnsData, fnInfoP)) {
 *    //body of iteration
 *  }
 *
 */
const FnInfo *
next_fn_info(const FnsData *fnsData, const FnInfo *lastFnInfo)
{
  //@TODO
  for (FnInfo *fnInfoP = next_fn_info(fnsData, NULL); fnInfoP != NULL;       fnInfoP = next_fn_info(fnsData, fnInfoP)) {

  return NULL;
}