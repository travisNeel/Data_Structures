/*
 Name: Travis Neel
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Linked List Data Structure

typedef char itemType;

class Node {
private:
    Node* next=nullptr;
    itemType payload='x';
public:
    Node(itemType input){
        cout<<"creating new node...\n";
        payload=input;
        next=nullptr;
    }
    
    Node(){
        payload='';
        next=nullptr;
    }
    
    itemType getPayload()const {
        return payload;
    }
    
    Node* getNext()const {
        return next;
    }
    
    void setNext(Node * newNext){
        next=newNext;
    }
    
    void setPayload(itemType input){
        payload=input;
    }
    
    Node(const Node &original_node) { // copy constructor
        payload=original_node.getPayload(); // use this in the copy constructor of the list??
        next=original_node.getNext();
    }
    
    const Node &operator=(const Node & rightHandSide){

            this->payload=rightHandSide.getPayload();
            this->next=rightHandSide.getNext();

        return *this;
    }
    
};

class List {
private:
    Node * head=nullptr;
    Node * tail=nullptr;// pointer to newest node in list
    int nodesInList=0;
    vector<itemType>node_payload_vector;
    
public:
    List();
    virtual ~List();
    
    List(const List & origList);// copy constructor
    
    const List & operator=(const List & rightHandSide); // assignment operator
    
    bool is_empty() const; // is it empty?
    
    void insert(itemType item, int position); // insert item at postion
    
    void insert(itemType item); // insert into list in sorted order (smallest to largest)
    
    // if you cannot get insertion into sorted order to work, insert where you want and explain in comments.
    
    void remove(int position);  // remove element at position
    
    void display(ostream & out) const; // display entire contents of list on one line, separate by spaces

    Node* getPhead() const {
        return head;
    }
    
    int getNumberOfNodes() const {
        return nodesInList;
    }
    
    void clear();
    
    void add_at_end(itemType item);

    
};


// ~~~~~~~ List Method Implementation ~~~~~~~~~~



const List & List::operator=(const List & rhs){
    cout<<"assignemnt called.."<<endl;
    if (&rhs==this) return *this;
        Node* runner=head;
    while (runner) {
        Node* next_runner=runner->getNext();
        if (DEBUG) cout<<"destructing lhs Node...("<<runner->getPayload()<<")\n";
        delete runner;
        runner=next_runner;
    }
    if (DEBUG) cout<<"destruction of lhs complete!\n\n";
    
    Node* source_list_runner=rhs.getPhead();  // start of source
    head=new Node(source_list_runner->getPayload()); // duplicate the first existing Node
    Node* destination_list_runner=head;  // start of destination
    if (DEBUG) cout<<"made copy of Node...("<<source_list_runner->getPayload()<<")\n";
    // this completes making and placing a copy of the first node on new list
    
    source_list_runner=source_list_runner->getNext();
    // move to the next node in the existing source list
    if (DEBUG) cout<<"next source Node is... ("<<source_list_runner->getPayload()<<")\n";
    
    while (source_list_runner) { // if there are more Nodes on the source list...
        destination_list_runner->setNext(new Node(source_list_runner->getPayload()));
        // made a copy of Node on source list, appended to destination list
        
        if (DEBUG) cout<<"made copy of Node... ("<<source_list_runner->getPayload()<<")\n";
        
        source_list_runner=source_list_runner->getNext();
        // move to the next node in the source list
        
        destination_list_runner=destination_list_runner->getNext();
        // move to the next node in the new destination list    this->head=nullptr; // for now, set lhs
    }
    return *this;;
}



List::List(const List & origList){ // copy constructor based on class example
    cout<<"copyc called.."<<endl;
    if (origList.head==nullptr) {
        this->head=nullptr; return;    // do nothing if the list is empty
    }
    
    Node* source_list_runner=origList.getPhead();  // start of source
    head=new Node(source_list_runner->getPayload()); // duplicate the first existing Node
    Node* destination_list_runner=head;  // start of destination
    if (DEBUG) cout<<"made copy of Node...("<<source_list_runner->getPayload()<<")\n";
    // this completes making and placing a copy of the first node on new list
    
    source_list_runner=source_list_runner->getNext();
    // move to the next node in the existing source list
    if (DEBUG) cout<<"next source Node is... ("<<source_list_runner->getPayload()<<")\n";
    
    while (source_list_runner) { // if there are more Nodes on the source list...
        destination_list_runner->setNext(new Node(source_list_runner->getPayload()));
        // made a copy of Node on source list, appended to destination list
        
        if (DEBUG) cout<<"made copy of Node... ("<<source_list_runner->getPayload()<<")\n";
        
        source_list_runner=source_list_runner->getNext();
        // move to the next node in the source list
        
        destination_list_runner=destination_list_runner->getNext();
        // move to the next node in the new destination list    this->head=nullptr; // for now, set lhs

    }
    return *this;
}

bool List::is_empty()const{
    if (head==nullptr) return true;
    else return false;
}


ostream & operator<< (ostream & out, const List & aList){
    
    auto temp = aList.getPhead();
    auto nodes = aList.getNumberOfNodes();

    for (int i=0; i<nodes; i++){
        out << temp->getPayload();
        temp=temp->getNext();
    }
    return out;
}

List::List(){
    cout<<"Creating new list...\n";
    this->head=nullptr;
    this->nodesInList=0;
}

void List::insert(itemType item) {
    
    if (this->head==nullptr) {
        head=new Node(item);
        head->setPayload(item);
        head->setNext(nullptr);
        tail=head;
        tail->setNext(nullptr);
    }
    
    else if (nodesInList==1){
        tail=new Node(item);
        head->setNext(tail);
        tail->setPayload(item);
        tail->setNext(nullptr);
    }
    
    else {
        tail->setNext(new Node(item));
        tail=tail->getNext();
        tail->setPayload(item);
    }
    nodesInList++;
};


//void List::insert1(itemType item){
//    if (head==nullptr){
//        head=new Node(item);
//    }
//    else{
//        Node* nodeptr = head;
//        while (head!=nullptr) {
//            nodeptr=nodeptr->getNext();
//        }
//        nodeptr->setNext(new Node(item));
//    }
//    nodesInList++;
//}

List::~List(){
    clear();
}

void List::clear(){
    auto temp=head;
    
    while (head) {
        temp=head->getNext();
        cout<<"deleting node...\n";
        delete head;
        head=temp;
    }
}

void List::remove(int pos){
    
    auto node_to_remove=head;
    auto node_to_replace=head;
    
    if (pos==1) {
        cout<<"deleting 1";
        head=head->getNext();
        delete node_to_remove;
    }
    else {
        for (int i=0; i<pos; i++) {
            node_to_replace=node_to_replace->getNext();
        }
        node_to_replace->setPayload(head->getPayload());
        node_to_replace->setNext(head->getNext());
    }
    head=head->getNext();
    delete head;
    node_to_remove=nullptr;
    node_to_replace=nullptr;
}


int main() { // main is done for you. You should not have to modify main.
    cout<<"COSC 2436 Lab 4\n";
    // Test class List...
    cout<<"Testing class List\n";
    List listA, listB;

    listA.insert('C'); listA.insert('O'); listA.insert('S'); listA.insert('C');
    listA.insert('2'); listA.insert('4'); listA.insert('3'); listA.insert('6');
    listB=listA;
    cout<<"listA: " << listA <<endl; // sorted list is expected
    cout<<"listB: " << listB <<endl; // should be same as listA
    List listC=listB; // construct a new list, initialize with previous list
    listC.insert('_'); listC.insert('Z'); listC.insert('Y'); listC.insert('X');
    cout<<"listC: " << listC <<endl;

    
    for (int position=1; position<4; ++position) {
        listC.remove(position);
        cout<<"listC: " << listC <<endl;
    }
    
    cout<<"\nGoodbye!\n";
    
    return 0;
}


