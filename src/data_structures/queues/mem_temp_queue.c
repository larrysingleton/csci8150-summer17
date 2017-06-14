#include <main.h>

//this link always point to first Link
struct node *headMemTemp = NULL;
//this link always point to lastMemTemp Link
struct node *lastMemTemp = NULL;

//is list empty
struct node* frontMemTemp() {
    return headMemTemp;
}

//insert link at the lastMemTemp location
void insertLastMemTemp(char* data, char* address, int64_t instruction, int opCode, int delay) {

    //create a link
    struct node *link = (struct node*) malloc(sizeof(struct node));
    link->address = address;
    link->data = data;
    link->instruction = instruction;
    link->opCode = opCode;
    link->delay = delay;
    link->next = NULL;

    if(frontMemTemp() == NULL) {
        //make it the lastMemTemp link
        headMemTemp = link;
        lastMemTemp = link;
    } else {
        //make link a new lastMemTemp link
        lastMemTemp->next = link;

        //mark old lastMemTemp node as prev of new link
        link->prev = lastMemTemp;
    }

    //point lastMemTemp to new lastMemTemp node
    lastMemTemp = link;
}

//delete a link with given key
struct node* deleteMemTemp(char* address) {

    //start from the first link
    struct node* current = headMemTemp;
    struct node* previous = NULL;

    //if list is empty
    if(headMemTemp == NULL) {
        return NULL;
    }

    //navigate through list
    while(strcmp(current->address, address) != 0) {
        //if it is lastMemTemp node

        if(current->next == NULL) {
            return NULL;
        } else {
            //store reference to current link
            previous = current;

            //move to next link
            current = current->next;
        }
    }

    //found a match, update the link
    if(current == headMemTemp) {
        //change first to point to next link
        headMemTemp = headMemTemp->next;
    } else {
        //bypass the current link
        current->prev->next = current->next;
    }

    if(current == lastMemTemp) {
        //change lastMemTemp to point to prev link
        lastMemTemp = current->prev;
    } else {
        current->next->prev = current->prev;
    }

    return current;
}