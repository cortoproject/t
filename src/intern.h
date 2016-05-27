
typedef struct corto_t_opbuff corto_t_opbuff;

/* Different operation kinds. The first three kinds are masks that can be
 * applied to any operator, and determine where the output of the operation is
 * stored */
typedef enum corto_t_opKind {

    /* By default, instructions write to buffer */
    CORTO_T_TOBUFF = 0,

    /* Indicates that instruction should write to register */
    CORTO_T_TOREG = 1,

    /* Operations */
    CORTO_T_TEXT = 2,
    CORTO_T_VAL = 4,
    CORTO_T_FUNCTION = 6,
    CORTO_T_FUNCTION_CHAIN = 8,
    CORTO_T_COMPARATOR = 10,
    CORTO_T_FILTER = 12
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
    CORTO_T_OBJECT,
    CORTO_T_IDENTIFIER_MEMBER,
    CORTO_T_OBJECT_MEMBER,
    CORTO_T_LITERAL
} corto_t_exprKind;

typedef struct corto_t_expr {
    corto_t_exprKind kind;
    union {
        corto_t_slice identifier;
        corto_object object;
        struct {
            corto_t_slice identifier;
            corto_uint32 idLen; /* Length of identifier without members */
        } identifier_member;
        struct {
            corto_object object;
            corto_t_slice member;
        } object_member;
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
            corto_t_expr expr;
        } val;
        struct {
            corto_t_function function;
            corto_t_block block;
        } function;
        struct {
            corto_t_comparator comparator;
            corto_t_expr arg;
        } comparator;
        struct {
            corto_function filter;
        } filter;
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
