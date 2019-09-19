#include <iostream>

#include "dynamic_array.h"

using namespace std;

dynamic_array::dynamic_array() {
	//set sizes
	size = 0;
	allocated_size = 0;
	try {
		array = new int [size + BLOCK_SIZE]; //create dynamic array
	} catch (bad_alloc){
		throw exception (MEMORY_EXCEPTION);
	}
}

dynamic_array::dynamic_array(dynamic_array &a) {
	size = a.get_size();
	allocated_size = a.get_allocated_size();
	
	//create new array
	try {
		array = new int[allocated_size];
	} catch (bad_alloc){
		throw exception (MEMORY_EXCEPTION);
	}
	
	//copy a[i..size-1]
	for (int i = 0; i < size; i++){
		array[i] = a[i];
	}
}

dynamic_array &dynamic_array::operator=(const dynamic_array &a) {
	//get sizes
	size = a.get_size();
	allocated_size = a.get_allocated_size();
	
	//create new array
	try {
        array = new int[allocated_size];
    } catch (bad_alloc){
        throw exception (MEMORY_EXCEPTION);
    }

   	//copy a[i..size-1]
	for (int i = 0; i < size; i++){
		array[i] = a[i];
	}


    return *this; //reference to the object
}

dynamic_array::~dynamic_array() {
	delete []array;
}

int dynamic_array::get_size(void) const {
	return size;
}

int dynamic_array::get_allocated_size(void) const {
	return allocated_size;
}

int& dynamic_array::operator[](unsigned int i) {
	if (i >= (unsigned)size){
		throw exception(SUBSCRIPT_RANGE_EXCEPTION);
	}
	return array[i]; //reference to index i
}

const int& dynamic_array::operator[](unsigned int i) const {
	if (i < 0 || i >= (unsigned)size){
		throw exception(SUBSCRIPT_RANGE_EXCEPTION);
	}
	return array[i]; //reference to index i
}

void dynamic_array::insert(int x, int i) {
	if (i < 0 or i > size){ //range check
		throw exception(SUBSCRIPT_RANGE_EXCEPTION);
	}

	if (size == allocated_size) { //new space needed
		int *new_array;
		
		//get more space
		try {
			new_array = new int[allocated_size + BLOCK_SIZE];
		} catch (bad_alloc){
			throw exception (MEMORY_EXCEPTION);
		}
		
		//copy array[0..i-1]
		for (int j = 0; j < i; j++) {
			new_array[j] = array[j];
		}

		//copy x
		new_array[i] = x;
		
		//copy array[i..size-1]
		for (int j = i; j < size; j++) {
			new_array[j+1] = array[j];
		}

		//update sizes

		allocated_size = allocated_size + BLOCK_SIZE;
		size++;
		delete []array;
		array = new_array;
	} else { //no new space needed
		shift_right(i, size, 1);
		array[i] = x;
		size++;
	}
}

void dynamic_array::insert(dynamic_array &a, int i) {
	if (i < 0 or i > size){ //range check
		throw exception(SUBSCRIPT_RANGE_EXCEPTION);
	}
	
	int range = a.get_size();

	if (size + range > allocated_size) { //new space needed
		int *new_array;
		int blocks_needed = (size + range) / BLOCK_SIZE;
		
		if (size % BLOCK_SIZE > 0) { //not multiple of BLOCK_SIZE
			blocks_needed = blocks_needed + 1;
		}
		allocated_size = blocks_needed * BLOCK_SIZE;
		
		//get more space
		try {
			new_array = new int[allocated_size];
		} catch (bad_alloc){
			throw exception (MEMORY_EXCEPTION);
		}
		
		//copy array[0..i-1]
		for (int j = 0; j < i; j++) {
			new_array[j] = array[j];
		}

		//copy a
		for (int m = i; m < i+range; m++){
			new_array[m] = a[m - i];
		}
		
		//copy array[i..size-1]
		for (int k = i; k < size; k++) {
			new_array[k+range] = array[k];
		}

		//update size
		size = size + range;
		delete []array; //free old array
		array = new_array;
	} else { //no new space needed
		shift_right(i, size, range);
		for (int z = i; z < range+i; z++){
			array[z] = a[z - i];
		}
		size = size + range;
	}
}

void dynamic_array::remove(int i) {
	if (i < 0 or i >= size){ //range check
		throw exception(SUBSCRIPT_RANGE_EXCEPTION);
	}
	
	int *new_array;

	if (size - 1 == allocated_size - BLOCK_SIZE){ //too much space
		
		//remove space
		try {
			new_array = new int[allocated_size - BLOCK_SIZE];
		} catch (bad_alloc){
			throw exception (MEMORY_EXCEPTION);
		}
		
		//copy array[0..i-1]
		for (int j = 0; j < i; j++){
			new_array[j] = array[j];
		}
		
		//delete array[i]
		array[i] = 0;
		
		//copy array[i..size-1]
		for (int j = i; j < size; j++){
			new_array[j-1] = array[j];
		}
		
		//update sizes
		allocated_size = allocated_size - BLOCK_SIZE;
		size--;
		delete []array;
		array = new_array;
	} else { //no space removal required
		shift_left(i+1, size, 1);
		size--;
	}
}

void dynamic_array::remove(int start, int end) {
	if (!(start >= 0 && start < end && end <= size)){
		throw exception(SUBSCRIPT_RANGE_EXCEPTION);
	}
	
	int range = (end - start); //number of elements removed
	
	if (size - range <= allocated_size - BLOCK_SIZE){ //too much space
		int *new_array;
		int empty_blocks = (size - range) / BLOCK_SIZE;
	
		if ((size - range) % BLOCK_SIZE > 0) { //not multiple of BLOCK_SIZE
			empty_blocks = empty_blocks + 1;
		}
		allocated_size = empty_blocks * BLOCK_SIZE;

		//remove space
		try {
			new_array = new int[allocated_size];
		} catch (bad_alloc){
			throw exception (MEMORY_EXCEPTION);
		}
		
		//copy array[0..start-1]
		for (int j = 0; j < start; j++){
			new_array[j] = array[j];
		}
		
		//delete array[start..end-1]
		for (int k = start; k < end; k++){
			array[k] = 0;
		}
		
		//copy array[end..size-1]
		for (int z = end; z < size; z++){
			new_array[z-range] = array[z];
		}
		
		//update size
		size = size - range;
		delete []array;
		array = new_array;
	} else { //no space deletion required
		shift_left(end, size, range);
		size = size - range;
	}
}

void dynamic_array::shift_left(int start, int end, int delta) {
		for(int i=start; i<=end; i++){ //traverse [start..end]
			array[i-delta] = array[i];
		}
	return;
}

void dynamic_array::shift_right(int start, int end, int delta){
		for(int i=end; i>=start; i--){ //traverse [end..start]
			array[i+delta] = array[i];
		}
	return;
}
