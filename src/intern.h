
typedef struct corto_t_opbuff corto_t_opbuff;

/* Different op kinds */
typedef enum corto_t_opKind {
    CORTO_T_TEXT,
    CORTO_T_VAR,
    CORTO_T_FUNCTION,
    CORTO_T_FUNCTION_COMPARATOR,
    CORTO_T_COMPARATOR
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

typedef enum corto_t_exprKind {
    CORTO_T_IDENTIFIER,
    CORTO_T_LITERAL,
    CORTO_T_OBJECT
} corto_t_exprKind;

typedef struct corto_t_expr {
    corto_t_exprKind kind;
    union {
        corto_t_slice identifier;
        struct {
            corto_type type;
            union {
                corto_bool _bool;
                corto_uint64 _uint;
                corto_int64 _int;
                corto_float64 _float;
                corto_t_slice _string;
            } value;
        } literal;
        corto_object object;
    } expr;
} corto_t_expr;

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
            corto_t_expr arg;
            corto_t_block block;
            corto_bool keepResult;
        } function;
        struct {
            corto_t_comparator comparator;
            struct corto_t_op *function; /* arg1 is stored in function */
            corto_t_expr arg;
        } comparator;
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
