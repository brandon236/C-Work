using namespace std;

class dynamic_array {
public:
	enum {
		BLOCK_SIZE = 5,
		SUBSCRIPT_RANGE_EXCEPTION = 1,
		MEMORY_EXCEPTION = 2,
	};

	/*Purpose
	*	create an array with size 0
	* Preconditions
	*	none
	* Exceptions
	*	if there is not enough dynamic memory available
	*		throw exception(MEMORY_EXCEPTION)
	*/
	dynamic_array();

	/*Purpose
	*	create an array containing a copy of the elements in a
	* Preconditions
	*	none
	* Exceptions
	*	if there is not enough dynamic memory available
	*		throw exception(MEMORY_EXCEPTION)
	*/
	dynamic_array(dynamic_array &a);

	/*Purpose
	*	copy the contents of a
	*	return a reference to this object
	* Preconditions
	*	none
	* Exceptions
	*	if there is not enough dynamic memory available
	*		throw exception(MEMORY_EXCEPTION)
	*/
	dynamic_array &operator=(const dynamic_array &a);

	/*Purpose
	*	delete all dynamically allocated memory
	* Preconditions
	*	none
	* Exceptions
	*	none
	*/
	~dynamic_array();

	/*Purpose
	*	return the size of the array
	* Preconditions
	*	none
	* Exceptions
	*	none
	*/
	int get_size(void) const;

	/*Purpose
	*	return the allocated size of the array
	* Preconditions
	*	none
	* Exceptions
	*	none
	*/
	int get_allocated_size() const;

	/*Purpose
	*	return a reference to the element with index i
	* Preconditions
	*	none
	* Exceptions
	*	if i >= get_size()
	*		throw exception(SUBSCRIPT_RANGE_EXCEPTION)
	*/
	int& operator[](unsigned int i);
	/*Purpose
	*	return a reference to the element with index i
	* Preconditions
	*	none
	* Exceptions
	*	if i >= get_size()
	*		throw exception(SUBSCRIPT_RANGE_EXCEPTION)
	*/
	const int& operator[](unsigned int i) const;

	/*Purpose
	*	insert x at postion i
	*	shift elements at positions i and higher one position to the right
	* Preconditions
	*	none
	* Exceptions
	*	if i < 0 or i > get_size()
	*		throw exception(SUBSCRIPT_RANGE_EXCEPTION)
	*	if there is not enough dynamic memory available
	*		throw exception(MEMORY_EXCEPTION)
	*/
	void insert(int x, int i);

	/*Purpose
	*	insert the elements of a at postion i
	*	shift elements at positions i and higher n positions to the right
	*		where n is the size of a
	* Preconditions
	*	none
	* Exceptions
	*	if i < 0 or i > get_size()
	*		throw exception(SUBSCRIPT_RANGE_EXCEPTION)
	*	if there is not enough dynamic memory available
	*		throw exception(MEMORY_EXCEPTION)
	*/
	void insert(dynamic_array &a, int i);

	/*Purpose
	*	remove the element at postion i
	*	shift elements i..n-1 one position to the left,
	*		where n is the size of the array
	* Preconditions
	*	none
	* Exceptions
	*	if i < 0 or i >= get_size()
	*		throw exception(SUBSCRIPT_RANGE_EXCEPTION)
	*	if there is not enough dynamic memory available
	*		throw exception(MEMORY_EXCEPTION)
	*/
	void remove(int i);

	/*Purpose
	*	remove the elements at postions start..end-1
	*	shift array[end..size-1] end-start positions to the left
	* Preconditions
	*	none
	* Exceptions
	*	if not (0 <= start <= end < size
	*		throw exception(SUBSCRIPT_RANGE_EXCEPTION)
	*	if there is not enough dynamic memory available
	*		throw exception(MEMORY_EXCEPTION)
	*/
	void remove(int start, int end);

	class exception {
		public:
			exception(int n0) { n = n0; };
			int n;
	};
private:
	/*purpose
	*	shift array[start..end-1] delta positions to the left
	* preconditions
	*	0 <= start <= end <= size
	*	array[start-delta..end-delta-1] legally addressable
	* examples
	*	given array with contents {0,2,4,6,8, 10,12,14,16,18}:
	*		shift(2,4,2)
	*			changes the contents to {4,6,4,6,8, 10,12,14,16,18}
	*		shift(2,2,1)
	*			leaves array unchanged
	*/
	void shift_left(int start, int end, int delta);

	/*purpose
	*	shift array[start..end-1] delta positions to the right
	* preconditions
	*	0 <= start <= end <= size
	*	array[start+delta..end+delta-1] legally addressable
	* examples
	*	given array with contents {0,2,4,6,8, 10,12,14,16,18}
	*		shift(2,4,3)
	*			changes the contents to {0,2,4,6,8, 4,6,14,16,18}
	*		shift(2,2,1)
	*			leaves array unchanged
	*/
	void shift_right(int start, int end, int delta);

	int *array; // pointer to dynamically allocated memory
	int allocated_size; // total number of elements in allocated memory
	int size; // number of active elements
};
