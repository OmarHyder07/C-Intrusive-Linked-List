#define list_entry(ELEM, TYPE, MEMBER) \
	((TYPE *) ((char *) (ELEM) - offsetof(TYPE, MEMBER)))

struct list_elem { 
	struct list_elem *prev;
	struct list_elem *next;
};

typedef struct {
	int priority;
	char name[16];
	struct list_elem elem;
} task;

typedef struct {
	struct list_elem head;
	struct list_elem tail;
} list;

void list_init(list *l);
void print_task(task *t);
void print_list(list *l);
void list_insert(struct list_elem *before, struct list_elem *elem);
void list_push_front(list *l, struct list_elem *elem);
void list_push_back(list *l, struct list_elem *elem);
struct list_elem *list_remove(struct list_elem *elem);
struct list_elem *list_begin(list *l);
struct list_elem *list_end(list *l);
bool list_empty(list *l);
struct list_elem *list_next(struct list_elem *elem);

typedef bool list_less_func(const struct list_elem *a, const struct list_elem *b, void *aux);
void list_insert_ordered(list *l, struct list_elem *elem, list_less_func lt, void *aux);
bool list_lt(const struct list_elem *a, const struct list_elem *b, void *aux);
