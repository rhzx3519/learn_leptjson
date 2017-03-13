#ifndef LEARN_JSON_H
#define LEARN_JSON_H

#include <stddef.h> /* size_t */

typedef enum {
	LEPT_NULL,
	LEPT_NUMBER,
	LEPT_TRUE,
	LEPT_FALSE,
	LEPT_STRING,
	LEPT_ARRAY,
	LEPT_OBJECT,
}lept_type;

typedef struct lept_value lept_value; //���� lept_value ��ʹ�����������͵�ָ�룬���Ǳ���ǰ��������forward declare��������
typedef struct lept_member lept_member;


struct lept_value {
	union {
		struct { lept_member *m; size_t msize; };
		struct { lept_value* e; size_t size; };    /* array:  elements, element count */
		struct { char* s; size_t len; };           /* string: null-terminated string, string length */
		double n;                                   /* number */
	};
	lept_type type;
};

struct lept_member {
	char *k; size_t klen;	/* member key string, key string length */
	lept_value v;			/* member value */
};

// �������
enum {
	LEPT_PARSE_OK,
	LEPT_PARSE_EXPECT_VALUE,
	LEPT_PARSE_INVALID_VALUE,
	LEPT_PARSE_ROOT_NOT_SINGULAR,
	LEPT_PARSE_NUMBER_TOO_BIG,
	LEPT_PARSE_MISS_QUOTATION_MARK,
	LEPT_PARSE_INVALID_STRING_ESCAPE,
	LEPT_PARSE_INVALID_STRING_CHAR,
	LEPT_PARSE_INVALID_UNICODE_HEX,
	LEPT_PARSE_INVALID_UNICODE_SURROGATE,
	LEPT_PARSE_MISS_COMMA_OR_SQUARE_BRACKET,
	LEPT_PARSE_MISS_KEY,
	LEPT_PARSE_MISS_COLON,
	LEPT_PARSE_MISS_COMMA_OR_CURLY_BRACKET,
};

#define lept_init(v) do {(v)->type = LEPT_NULL;} while (0)
#define lept_set_null(v) lept_free(v)

// ����json
int lept_parse(lept_value *v, const char *c);
char* lept_stringify(const lept_value* v, size_t* length); // ����json�ַ���

// ��ȡ���ʽ��
lept_type lept_get_type(lept_value *v);

int lept_get_boolean(const lept_value* v);
void lept_set_boolean(lept_value* v, int b);

double lept_get_number(lept_value *v);
void lept_set_number(lept_value* v, double n);

void lept_set_string(lept_value *v, const char *s, size_t len);
const char* lept_get_string(const lept_value* v);
size_t lept_get_string_length(const lept_value* v);

void lept_free(lept_value *v);

// array
size_t lept_get_array_size(const lept_value* v);
lept_value* lept_get_array_element(const lept_value* v, size_t index);

size_t lept_get_object_size(const lept_value* v);
const char* lept_get_object_key(const lept_value* v, size_t index);
size_t lept_get_object_key_length(const lept_value* v, size_t index);
lept_value* lept_get_object_value(const lept_value* v, size_t index);

#endif /*LEARN_JSON_H*/