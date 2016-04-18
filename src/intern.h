
/* Different op kinds */
typedef enum corto_t_opKind {
    CORTO_T_TEXT,
    CORTO_T_VAR,
} corto_t_opKind;

/* A slice of the template string */
typedef struct corto_t_slice {
    char *ptr;
    corto_int32 len;
} corto_t_slice;

/* Single template operation */
typedef struct corto_t_op {
    corto_t_opKind kind;
    union {
        struct {
            corto_t_slice t;
        } text;
        struct {
            corto_t_slice key;
        } var;
    } data;
} corto_t_op;

/* Block of n operations */
typedef struct corto_t_opbuffer {
    corto_t_op ops[CORTO_T_OP_BUFF_COUNT];
    corto_uint32 opcount;
    struct corto_t_opbuffer *next;
} corto_t_opbuffer;

struct corto_t {
    corto_string template;
    corto_t_opbuffer ops;
    corto_t_opbuffer *current;
};

void corto_t_print(corto_t *t);
