#include <stdio.h>

#define OFFSETOF(struct_name, fld_name)     \
    (unsigned long)&(((struct_name *)0)->fld_name)

#define FIELD_SIZE(struct_name, fld_name)   \
    sizeof(((struct_name *)0)->fld_name)

#define MAX_FIELD_NAME_SIZE 128

#define FIELD_INFO(struct_name, fld_name, dtype, nested_struct_name)    \
   {#fld_name, dtype, FIELD_SIZE(struct_name, fld_name),                \
        OFFSETOF(struct_name, fld_name), #nested_struct_name} 

typedef enum {
    UINT8,
    UINT32,
    INT32,
    CHAR,
    OBJ_PTR,
    VOID_PTR, /*New Data type added to identify void * pointers*/
    FLOAT,
    DOUBLE,
    OBJ_STRUCT
} data_type_t;

typedef struct _field_info_{
    char fname [MAX_FIELD_NAME_SIZE];   /*Name of the field*/
    data_type_t dtype;                  /*Data type of the field*/
    unsigned int size;                  /*Size of the field*/
    unsigned int offset;                /*Offset of the field*/
    // Below field is meaningful only if dtype = OBJ_PTR, Or OBJ_STRUCT
    char nested_str_name[MAX_FIELD_NAME_SIZE];
} field_info_t;


typedef struct emp_ {

    char emp_name[30];
    unsigned int emp_id;
    unsigned int age;
    struct emp_ *mgr;
    float salary;
    int *p;
} emp_t;

int  main(int argc, char* argv[])
{

    static field_info_t emp_fields[] = 
    {
        FIELD_INFO(emp_t, emp_name, CHAR,    0),
        FIELD_INFO(emp_t, emp_id,   UINT32,  0),
        FIELD_INFO(emp_t, age,      UINT32,  0),
        FIELD_INFO(emp_t, mgr,      OBJ_PTR, emp_t),
        FIELD_INFO(emp_t, salary,   FLOAT, 0),
        FIELD_INFO(emp_t, p, OBJ_PTR, 0)
    };

    printf("filed name is %s\n",emp_fields[1].fname);
    printf("size is %d\n",emp_fields[1].size);
    printf("offset is %d\n",emp_fields[0].offset);


return 0;
}

