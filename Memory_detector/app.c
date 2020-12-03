#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "app.h"

int  main(int argc, char* argv[])
{
    int i =0;
    static field_info_t emp_fields[] = 
    {
        FIELD_INFO(emp_t, emp_name, CHAR,    0),
        FIELD_INFO(emp_t, emp_id,   UINT32,  0),
        FIELD_INFO(emp_t, age,      UINT32,  0),
        FIELD_INFO(emp_t, mgr,      OBJ_PTR, emp_t),
        FIELD_INFO(emp_t, salary,   FLOAT, 0),
        FIELD_INFO(emp_t, p, OBJ_PTR, 0)
    };
    

    struct_db_t *struct_db = calloc(1, sizeof(struct_db_t));

    REG_STRUCT(struct_db, emp_t, emp_fields);

    // printf("%s\n", struct_db->head->struct_name);
    print_structure_db(struct_db);

    static field_info_t stud_fiels[] = 
    {
        FIELD_INFO(student_t, stud_name, CHAR, 0),
        FIELD_INFO(student_t, rollno,    UINT32, 0),
        FIELD_INFO(student_t, age,       UINT32, 0),
        FIELD_INFO(student_t, aggregate, FLOAT, 0),
        FIELD_INFO(student_t, best_colleage, OBJ_PTR, student_t)
    };
    REG_STRUCT(struct_db, student_t, stud_fiels);

    print_structure_db(struct_db);
    
    /*Working with object database*/
    /*Step 1 : Initialize a new Object database */
    object_db_t *object_db = calloc(1, sizeof(object_db_t));
    
    //This is keypoint, at this instant object_db edi have the information of populated struct_db
    object_db->struct_db = struct_db;
    
    /*Step 2 : Create some sample objects, equivalent to standard 
     * calloc(1, sizeof(student_t))*/
    emp_t * kj = xcalloc(object_db, "emp_t", 1); 
    print_object_db(object_db);

    student_t *abhishek = xcalloc(object_db, "student_t", 1);
    print_object_db(object_db);
    return 0;
}

