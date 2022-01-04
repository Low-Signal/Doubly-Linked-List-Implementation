using namespace cop4530;

template <typename T>
List<T>::const_iterator::const_iterator() : current{nullptr}
{}

template <typename T>
const T& List<T>::const_iterator::operator* ( ) const
{   return retrieve();}    // calls reference function to return the reference.

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++()
{
    current = current->next;    // sets the current position to the next
    return *this;               // returns the altared current position
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++ (int)
{
    const_iterator old = *this; // creates a copy
    ++( *this);                 // adds to the original
    return old;                 // returns the copy
}

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--()
{
    current = current->prev;    // sets the current position to the previous
    return *this;               // returns the altared current position
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator-- (int)
{
    const_iterator old = *this; // creates a copy
    --( *this);                 // subtracts from the original
    return old;                 // returns the copy
}

// Checks if the constant iterators are equal
template <typename T>
bool List<T>::const_iterator::operator==(const const_iterator & rhs ) const
{
    return current == rhs.current;
}

// Checks if the constant iterators are not equal
template <typename T>
bool List<T>::const_iterator::operator!= ( const const_iterator & rhs ) const
{
    //return !(*this == rhs);  // this works also (was book example)
    return current != rhs.current;
}

// Returns the reference of the current constant iterators position data
template <typename T>
T& List<T>::const_iterator::retrieve() const
{
    return current->data;   
}

template <typename T>
List<T>::const_iterator::const_iterator(Node *p) : current{p}
{}

// Must be provided because the private constructor is written
template <typename T>
List<T>::iterator::iterator()
{}

/* Mutator that returns a reference to the 
object stored at the current position*/
template <typename T>
T& List<T>::iterator::operator* ()
{   return const_iterator::retrieve();}

/* Accessor that returns a constant reference to the 
object stored at the current position*/
template <typename T>
const T& List<T>::iterator::operator* () const
{   return const_iterator::operator*();}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++()
{
    // Sets the current iterator to the next (++)
    this->current = this->current->next;
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
    // Makes a copy of the old iterator
    iterator oldItr = *this;
    
    // Adds to the current iterator
    ++(*this);

    // Returns the orignial value
    return oldItr;
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator--()
{
    // Sets the current iterator to the previous (--)
    this->current = this->current->prev;
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
    // Makes a copy of the old iterator
    iterator oldItr = *this;

    // Subtracts from the current iterator
    --(*this);

    // Returns the original value
    return oldItr;
}

// Sets the pointer current to p.
template <typename T>
List<T>::iterator::iterator(Node *p) : const_iterator{p}
{}

// List constructor
template <typename T>
List<T>::List()
{   init();}

// Copy constructor
template <typename T>
List<T>::List(const List &rhs)
{
    // Initializes the list
    init();

    // Fills the target list with the list given
    for(auto & Itr : rhs)
        push_back(Itr);
}

// Move constructor
template <typename T>
List<T>::List(List &&rhs) 
    : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}
{
    rhs.head = nullptr;
    rhs.tail = nullptr;

    rhs.theSize = 0;
}

// Constructs a list with num number of elements with the value val
template <typename T>
List<T>::List(int num, const T& val)
{
    // Initializes the list
    init();

    // Fills the list with the given value
    for(int i = 0; i < num; i++)
        push_back(val);
}

// Constructs a sub list from another list given the start and end elements
template <typename T>
List<T>::List(const_iterator start, const_iterator end)
{
    // Initializes the list
    init();

    // Pushes each element into the new list
    for( auto i = start; i != end; i++)
        push_back(*i);
}

// Constructs a list given a specific value for each element
template <typename T>
List<T>::List(std::initializer_list<T> iList)
{   
    // Initializes the list
    init();

    // Fills the list with the given elements
    for(auto i = iList.begin(); i != iList.end(); i++)
        push_back(*i);
}

// Destructor
template <typename T>
List<T>::~List()
{
    clear();
    delete head;
    delete tail;
}

// List copy assignment operator
template <typename T>
List<T>& List<T>::operator=(const List &rhs)
{
    // Creates a copy of the list
    List listCopy = rhs;

    // Swaps the copy with the current list.
    std::swap(*this, listCopy);

    return *this;
}

// List move assignment operator
template <typename T>
List<T>& List<T>::operator=(List &&rhs)
{   
    // Swaps all of the member data
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);

    std::swap(theSize, rhs.theSize);

    return *this;
}

// Initializer list assignment operator
template <typename T>
List<T>& List<T>::operator=(std::initializer_list<T> iList)
{
    // Clears the current list
    clear();

    // Fills the list with the initializer list
    for(auto i = iList.begin(); i != iList.end(); i++)
        push_back(*i);

    return *this;
}

// Returns the number of elements in the list
template <typename T>
int List<T>::size() const
{
    return theSize;
}

// Returns true if there are no elements in the list
template <typename T>
bool List<T>::empty() const
{
    // If the size is 0 return true, else false
    return size() == 0;
}

// Clears the list
template <typename T>
void List<T>::clear()
{
    // Pops every element until the list is empty
    while (!empty())
        pop_front();
}

// Returns a reference to the first element
template <typename T>
T& List<T>::front()
{   return *begin(); }

// Returns a constant reference to the first element
template <typename T>
const T& List<T>::front() const
{   return *begin(); }

// Returns a reference to the last element
template <typename T>
T& List<T>::back()
{   return *--end(); }

// Returns a constant reference to the last element
template <typename T>
const T& List<T>::back() const
{   return *--end(); }

// Inserts to beginning
template <typename T>
void List<T>::push_front(const T & val)
{   insert(begin(), val); }

// Inserts to beginning (move version)
template <typename T>
void List<T>::push_front(T && val)
{   insert(begin(), std::move(val)); }

// Inserts to end
template <typename T>
void List<T>::push_back(const T & val)
{   insert(end(), val); }

// Inserts to end (move version)
template <typename T>
void List<T>::push_back(T && val)
{   insert(end(), std::move(val)); }

// Deletes the first element
template <typename T>
void List<T>::pop_front()
{   erase(begin()); }

// Deletes the last element
template <typename T>
void List<T>::pop_back()
{   erase(--end()); }

// Removes all elements with a specific value
template <typename T>
void List<T>::remove(const T &val)
{
    /* Loops through the iterators and removes 
    values that match the passed in value*/
    for(auto i = begin(); i != end(); i++)
    {
        if(val == *i)
            erase(i);
    }
}

// Erases all nodes where pred() returns true
template <typename T>
template <typename PREDICATE>
void List<T>::remove_if(PREDICATE pred)
{
    // Goes through each element
    for(auto i = begin(); i != end(); i++)
    {
        // If pred is true, erase the element
        if (pred(*i))
            erase(i);
    }
}

// Prints the list
template <typename T> 
void List<T>::print(std::ostream& os, char ofc) const
{
    // Goes through each element and sends it to the ostream.
    for(auto i = begin(); i != end(); i++)
        os << *i << ofc;
}

// Returns iterator to the starting element (mutator)
template <typename T>
typename List<T>::iterator List<T>::begin()
{
    // returns the first element
    return iterator(head->next);
}

// Returns iterator to the starting element (accessor)
template <typename T>
typename List<T>::const_iterator List<T>::begin() const
{
    // returns the first element
    return const_iterator(head->next);
}

// Returns iterator to the end element (mutator)
template <typename T>
typename List<T>::iterator List<T>::end()
{
    // Returns the tail element
    return iterator(tail);
}

// Returns iterator to the end element (accessor)
template <typename T>
typename List<T>::const_iterator List<T>::end() const
{
    // Returns the tail element
    return const_iterator(tail);
}

// Inserts a specific value ahead of the node denoted by itr (copy version)
template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val)
{
    // Creates a new node with current value
    Node *newNode = itr.current;

    ++theSize;

    // Sets up the node position
    return iterator( newNode->prev = newNode->prev->next = new Node{ val, newNode->prev, newNode } );
}

// Inserts a specific value ahead of the node denoted by itr (move version)
template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T && val)
{
    // Creates a new node with current value
    Node *newNode = itr.current;

    ++theSize;

    // Sets up the node position (move version)
    return iterator( newNode->prev = newNode->prev->next = new Node{ std::move(val), newNode->prev, newNode } );
}

// Deletes the node refered to by itr
template <typename T>
typename List<T>::iterator List<T>::erase(iterator itr)
{
    // Creates a temporary node with the current value
    Node *tempNode = itr.current;

    // Sets up the return value
    iterator retVal( tempNode->next );

    // Sets the previous/next pointers to reflect removing the node
    tempNode->prev->next = tempNode->next;
    tempNode->next->prev = tempNode->prev;

    delete tempNode;

    --theSize;

    // Returns the following node
    return retVal;
}

// Erases value between the start and end value given
template <typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end)
{
    // Erases each value in the range
    for( iterator itr = start; itr != end; )
        itr = erase( itr );

    return end;
}

// Initializes member variables of the list
template <typename T>
void List<T>::init()
{
    theSize = 0;

    // Creates a new head and tail
    head = new Node;
    tail = new Node;

    // Links the head and tail
    head->next = tail;
    tail->prev = head;
}

// Reverses the order of the list
template <typename T>
void List<T>::reverse()
{
    int oldSize = size();

    // Pushes elements to the back of the list starting with the last element
    for(auto i = --end(); i != --begin(); i--)
        push_back(*i);

    // Pops all of the original elements
    for(int i = 0; i < oldSize; i++)
        pop_front();

}

// Removes duplicate values in the list
template <typename T>
void List<T>::deduplicate()
{
    for(auto i = begin(); i != end(); i++)
    {
        for(auto j = begin(); j != end(); j++)
        {   
            // If they are the same iterator skip
            if(i == j)
                continue;

            // If they reference the same value, erase the duplicate
            if(*i == *j)
                erase(j);
        }
    }
}

// Checks if the two list are equal
template <typename T>
bool operator==(const List<T> & lhs, const List<T> &rhs)
{   
    // If the size is not the same they are not equal
    if (lhs.size() != rhs.size())
        return false;

    // Initializes the starting positions
    auto j = rhs.begin();
    auto i = lhs.begin();
    
    /* Compares each element and iterates the
     position checked by one for each loop*/
    while(j != rhs.end() && i != lhs.end())
    {
        if(*i != *j)
            return false;  
        j++;
        i++;
    }
    return true;
}

// Checks if the two list are not equal
template <typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs)
{
    // If the sizes are different they are not equal
    if (lhs.size() != rhs.size())
        return true;
    
    // Initializes the starting positions
    auto j = rhs.begin();
    auto i = lhs.begin();
    
    /* Compares each element and iterates the
     position checked by one for each loop*/
    while(j != rhs.end() && i != lhs.end())
    {
        if(*i != *j)
            return true;
        j++;
        i++;
    }
    return false;
}

// Overloaded output operator
template <typename T>
std::ostream &operator<<(std::ostream &os, const List<T> &l)
{
    // Sends each element followed by a space to ostream
    l.print(os);

    return os;
}
