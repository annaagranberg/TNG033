#include "set.hpp"
// std::size_t is defined in the C++ standard library
// std::size_t is an unsigned integer type that can store the maximum size of any possible object
// sizes are non-negative integers -- i.e. unsigned integer type

// Initialize the counter of the total number of existing nodes
std::size_t Set::Node::count_nodes = 0;

// Used only for debug purposes
// Return number of existing nodes
std::size_t Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

/* ******************************************************** */

// Default constructor
Set::Set() : head(new Node{0, nullptr }), counter(0) {
}

// Constructor for creating a set from an int
Set::Set(int v) : Set{} {
    insert(v);
    counter++;
}

// Constructor: create a set with the elements in V
// V is not sorted and may contain repeated elements

Set::Set(const std::vector<int>& V) : Set{}{
    //{2,1,4,9}
    for(int i: V) {
        Node* ptr = head;
        
        while(ptr){
            if(!ptr->next || ptr->next->value > i){
                insert(i);
                counter++;
                break;
            }
            else if(ptr->next->value < i) {
                ptr = ptr->next;
            }
            else {
                break;
            }
        }
    }
}

// copy constructor
Set::Set(const Set& source) : Set(){
    Node* ptr1 = source.head->next; //S
    Node* ptr2 = head; //R
    
    while(ptr1 != nullptr){
        // Copy of Node* ptr1 and add it after *ptr2
        insert(ptr2, ptr1->value);
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    counter = source.counter;
}

// Assignment operator: copy-and-swap idiom
// Uses the copy constructor and the destructor
Set& Set::operator=(Set s) {
    std::swap(head,s.head); //Pointers pekar på varandras Set
    std::swap(counter, s.counter); //Byter counters för att va säker på att hela raderas.

    return *this; //Tydligen är destructorn called
}

// Destructor: deallocate all nodes
Set::~Set() {
    Node* p = head;
    while (p != nullptr) {
        head = p->next;
        remove(p);
        p = head;
    }
    counter = 0;
}


// Return number of elements in the set
std::size_t Set::cardinality() const {
    return counter ;  // delete if needed
}

// Test if set is empty
bool Set::empty() const {
    return(counter == 0);
}

// Test if x is an element of the set
bool Set::member(int x) const {
    
    Node* temp = head->next;
    
    while(temp != nullptr && x != temp->value){
        temp = temp->next;
    }
    
    if(temp == nullptr){
        return false;
    }
    else {
        return true;
    }
}

bool Set::operator<=(const Set& b) const {
    Node* lhs = head->next;
    
    while(lhs != nullptr){
        if(!b.member(lhs->value)){
            return false;
        }
        lhs = lhs->next;
    }

    return true;  // delete if needed
}

bool Set::operator==(const Set& b) const {
    
    if(operator<=(b)){
        if(b.operator<=(*this)){
            return true;
        }
    }
    return false;  // delete if needed
}

bool Set::operator!=(const Set& b) const {
    
    if(operator==(b)){
        return false;
    }
    return true;  // delete if needed
}

bool Set::operator<(const Set& b) const {
    
    if(operator<=(b)){
        if(b.counter < counter){
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

// Set union
// Repeated values are not allowed
Set Set::operator+(const Set& b) const {
    std::vector<int> comp;
    Node* ptr1 = b.head->next;
    Node* ptr2 = head->next;
    
    while(ptr1){
        comp.push_back(ptr1->value);
        ptr1 = ptr1->next;
    }
    while(ptr2){
        comp.push_back(ptr2->value);
        ptr2 = ptr2->next;
    }
    
    return Set{comp};;  // delete if needed
}

// Set intersection
Set Set::operator*(const Set& b) const {
    std::vector<int> arg;
    Node* ptr1 = head->next;
    
    while(ptr1){
        if(b.member(ptr1->value)){
            arg.push_back(ptr1->value);
        }
        ptr1 = ptr1->next;
    }
    
    return Set{arg};  // delete if needed
}

// Set difference
Set Set::operator-(const Set& b) const {
    std::vector<int> arg;
    Node* ptr1 = head ->next;
    
    while(ptr1){
        if(!b.member(ptr1->value)){
            arg.push_back(ptr1->value);
        }
        ptr1 = ptr1->next;
    }

    return Set{arg};  // delete if needed
}

// set difference with set {x}
Set Set::operator-(int x) const {
    return Set::operator-(Set{x}); // delete if needed
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& os, const Set& theSet) {
    if (theSet.empty()) {
        os << "Set is empty!";
    }
    else {
        Set::Node* temp = theSet.head->next;
        os << "{ ";

        while (temp != nullptr) {
            os << temp->value << " ";
            temp = temp->next;
        }
        os << "}";
    }
    return os;
}

/********** Private member functions ************/

void Set::insert(Node* ptr, int value) const {
    Node* newNode = new Node(value,ptr->next);
    ptr->next = newNode;
}

void Set::insert(int value) const{
    Node* ptr = head;
    
    while((ptr->next != nullptr) && (ptr->next->value <  value)) { //största längst bak
        ptr = ptr -> next;
    }
    if(ptr->next == nullptr || ptr->next->value != value ){
        insert(ptr, value); //sätta in en ny node mellan
    }
}

void Set::remove(Node* ptr) {
    delete(ptr);
}
