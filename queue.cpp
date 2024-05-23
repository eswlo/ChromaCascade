/**
 * @file        queue.cpp
 * @description Implementation of the Queue class.
 *
 *              SUBMIT THIS FILE WITH YOUR MODIFICATIONS
 */

//////////////////////////////////////
///stack_1 for enq, stack_2 for deq///
//////////////////////////////////////

/**
 * Adds the parameter object to the back of the Queue.
 *
 * NOTE: This fuction should have O(1) behavior over n operations!
 *
 * @param item - object to be added to the Queue.
 */
template <class T>
void Queue<T>::Enqueue(T const& item)
{
	//if items are in stack2 due to Dequeue, then put them back into stack1
	if (!stack_2.IsEmpty()) {
		while (!stack_2.IsEmpty()) {
			stack_1.Push(stack_2.Pop());
		}
		stack_1.Push(item);
	} else {
		stack_1.Push(item);
	}
	
}

/**
 * Removes the object at the front of the Queue, and returns it to
 * the caller. You may assume that this function is only called
 * when the Queue is non-empty.
 *
 * NOTE: This function should have O(1) behavior over n operations!
 *
 * @return the item that used to be at the front of the Queue.
 */
template <class T>
T Queue<T>::Dequeue()
{
	// if stack2 is empty, put items from stack1 to stack2 for deq
	if (stack_2.IsEmpty()) {
		while (!stack_1.IsEmpty()) {
			stack_2.Push(stack_1.Pop());
		}
	}
	T item = stack_2.Pop();     
	return item;
}

/**
 * Adds an element to the ordering structure.
 *
 * See OrderingStructure::Add()
 */
template <class T>
void Queue<T>::Add(const T& item)
{
	Enqueue(item);	
}

/*
*  Removes an element from the ordering structure.
*
*  See OrderingStructure::Remove()
*/
template <class T>
T Queue<T>::Remove()
{
	// complete your implementation below
	// Hint: this function should call a Queue
	// function to remove an element from the Queue and return it. You will
	// need to replace the following lines.

	T item = Dequeue();
	return item; // REPLACE THESE LINES
}

/*
*  Finds the object at the front of the Queue, and returns it to
*  the caller. Unlike Dequeue(), this operation does (conceptually!) not alter the
*  Queue; however, you may need to alter the internal representation of the Queue.
*  You may assume that this function is only called when the
*  Queue is non-empty.
*
*  NOTE: This function should have O(1) behavior over n operations!
*
*  @return the item at the front of the queue.
*/
template <class T>
T Queue<T>::Peek()
{
	//in enq state, queue order is reverse of stack order
	if (!stack_1.IsEmpty()) {
		//put items in stack2
		while (!stack_1.IsEmpty()) {
			stack_2.Push(stack_1.Pop());
		}
		T item = stack_2.Peek();
		//return items back to stack1
		while (!stack_2.IsEmpty()) {
			stack_1.Push(stack_2.Pop());
		}
		return item;
	} else if (!stack_2.IsEmpty()) {
		//in deq state, stack order == queue order
		T item = stack_2.Peek();
		return item;
	} else {
		throw std::runtime_error("Peek() called on an empty queue");
	}
}

/*
*  Determines if the Queue is empty.
*
*  @return true if the stack is empty,
*          false otherwise.
* 
*  NOTE: This function must always run in O(1) time!
*/
template <class T>
bool Queue<T>::IsEmpty() const
{
	if (stack_1.IsEmpty() && stack_2.IsEmpty()) {
		return true;
	} else {
		return false;
	}
}
