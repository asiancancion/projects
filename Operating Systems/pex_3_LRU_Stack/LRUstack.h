
//a node for use in an LRU stick, which is a doubly linked list
typedef struct s_node{
    struct s_node* prev;
    struct s_node* next;
    unsigned long pagenum;

} node;

/*An LRU stack consisting of head and tail pointers as well as
  a current size and a max size. Keep the stack limited to the
  max size or you will run out of memory trying to run the simulation.
*/

typedef struct s_lrus{
    node* head;
    node* tail;
    unsigned int size;
    unsigned int maxSize;

} lrustack;

//initiailize LRU stack
void intialize(lrustack* lrus, unsigned int maxSize);
/* use pagenum when creating a new node, which will be pushed onto
   the LRU stack; make sure to keep track of the LRU stack's size
   and free and reset the tial as necessary to limit to max size
*/
void push (lrustack* lrus, unsigned long pagenum);
/* seek pagenum in lrus and remove it if found; return the depth
   at which pagenum was found or -1 if not
*/
int seek_and_remove(lrustack* lrus, unsigned long pagenum);