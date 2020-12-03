#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#ifndef __CSS__
#define __CSS__

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#endif


#define OFFSETOF(struct_name, fld_name)     \
    (unsigned long)&(((struct_name *)0)->fld_name)

#define FIELD_SIZE(struct_name, fld_name)   \
    sizeof(((struct_name *)0)->fld_name)

#define MAX_FIELD_NAME_SIZE 128
#define MAX_STRUCTURE_NAME_SIZE 128

/*
   This macro help populate structure members with paremtter pass in.
   eg:
    fld name is emp_name -> fname
    FIELD_SIZE(struct_name, fld_name) ->offset
    printf("filed name is %s\n",emp_fields[0].fname); -> emp_name
    printf("size is %d\n",emp_fields[0].size);        -> 30
    printf("offset is %d\n",emp_fields[0].offset);    -> 0 first structure member 
*/
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

typedef struct student_{

    char stud_name[32];
    unsigned int rollno;
    unsigned int age;
    float aggregate;
    struct student_ *best_colleage;
} student_t;


/*
    NOTE:struct_db not reli doing anything but just pass to add_structure_to_struct_db
    This macro merely just populate struct_db_rec_t *struct_rec memebers.
*/
#define REG_STRUCT(struct_db, usr_struc_name, fields_arr)                               \
    do{                                                                                 \
        struct_db_rec_t *struct_rec = calloc(1, sizeof(struct_db_rec_t));               \
        strncpy(struct_rec->struct_name, #usr_struc_name, MAX_STRUCTURE_NAME_SIZE);     \
        struct_rec->ds_size = sizeof(usr_struc_name);                                   \
        struct_rec->n_fields = sizeof(fields_arr)/sizeof(field_info_t);                 \
        struct_rec->fields = fields_arr;                                                \
        if(add_structure_to_struct_db(struct_db, struct_rec,0)){                          \
            assert(0);                                                                  \
        }                                                                               \
    }while(0);


typedef struct _struct_db_rec_ struct_db_rec_t;

struct _struct_db_rec_ {
    struct _struct_db_rec_ *next;  /*Pointer to the next structure in the linked list*/
    char struct_name [MAX_STRUCTURE_NAME_SIZE];  // key
    unsigned int ds_size;   /*Size of the structure*/ 
    unsigned int n_fields;  /*No of fields in the structure*/
    field_info_t *fields;   /*pointer to the array of fields*/
};

typedef struct _struct_db_{
    struct _struct_db_rec_ *head;
    unsigned int count;
} struct_db_t;

/*Object Database structure definitions Starts here*/

typedef struct _object_db_rec_ object_db_rec_t;

struct _object_db_rec_{
    object_db_rec_t *next;
    void *ptr;
    unsigned int units;
    struct_db_rec_t *struct_rec;
  //  mld_boolean_t is_visited; /*Used for Graph traversal*/
    //mld_boolean_t is_root;    /*Is this object is Root object*/
};

typedef struct _object_db_{
    struct_db_t *struct_db;
    object_db_rec_t *head;
    unsigned int count;
} object_db_t;

/*Dumping functions*/
void print_structure_db(struct_db_t *struct_db);

void print_object_rec(object_db_rec_t *obj_rec, int i);

void print_object_db(object_db_t *object_db);

/*API to malloc the object*/
void* xcalloc(object_db_t *object_db, char *struct_name, int units);

int add_structure_to_struct_db(struct_db_t *struct_db, 
                               struct_db_rec_t *struct_rec,
                               int start_with_new_struct);
