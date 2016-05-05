
typedef struct corto_t_opbuff corto_t_opbuff;

/* Different op kinds */
typedef enum corto_t_opKind {
    CORTO_T_TEXT,
    CORTO_T_VAR,
    CORTO_T_FUNCTION
} corto_t_opKind;

/* A slice of the template string */
typedef struct corto_t_slice {
    char *ptr;
    corto_int32 len;
} corto_t_slice;

/* Function block */
struct corto_t_block {
    corto_t_opbuff *startBuff;
    corto_uint32 startOp;
    corto_t_opbuff *stopBuff;
    corto_uint32 stopOp;
};

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
        struct {
            corto_t_function function;
            corto_t_slice arg;
            corto_t_block block;
        } function;
    } data;
} corto_t_op;

/* Block of n operations */
struct corto_t_opbuff {
    corto_t_op ops[CORTO_T_OP_BUFF_COUNT];
    corto_uint32 count;
    struct corto_t_opbuff *next;
};

/* Block of n imports */
typedef struct corto_t_importbuff {
    corto_object imports[CORTO_T_IMPORT_BUFF_COUNT];
    corto_uint32 count;
    struct corto_t_importbuff *next;
} corto_t_importbuff;

struct corto_t {
    /* Original template string */
    corto_string template;

    /* Operations */
    corto_t_opbuff ops;

    /* Imported packages */
    corto_t_importbuff imports;
};

void corto_t_copySliceToString(corto_id buf, corto_t_slice slice);
void corto_t_print(corto_t *t);
