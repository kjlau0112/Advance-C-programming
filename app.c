#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "app.h"

int add_structure_to_struct_db(struct_db_t *struct_db, 
                               struct_db_rec_t *struct_rec)
{

    /*Note #struct_db is from  main() and 
    #struct_rec is create dynamically from REG_STRUCT */
    
    struct_db_rec_t *rec_head = struct_db->head;

    if(rec_head == NULL)
    {
        struct_db->head = struct_rec;
        struct_db->count++;

        struct_rec->next = NULL;
        return 0;
    }

    struct_rec->next = rec_head;
    struct_db->head = struct_rec;
    struct_db->count++;
    return 0;
}

void print_structure_rec(struct_db_rec_t *struct_rec){
    if(!struct_rec) return;
    int j = 0;
    field_info_t *field = NULL;
    printf(ANSI_COLOR_CYAN "|------------------------------------------------------|\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "| %-20s | size = %-8d | #flds = %-3d |\n" ANSI_COLOR_RESET, struct_rec->struct_name, struct_rec->ds_size, struct_rec->n_fields);
    printf(ANSI_COLOR_CYAN "|------------------------------------------------------|------------------------------------------------------------------------------------------|\n" ANSI_COLOR_RESET);
    for(j = 0; j < struct_rec->n_fields; j++){
        field = &struct_rec->fields[j];
        printf("  %-20s |", "");
        printf("%-3d %-20s | dtype = %-15s | size = %-5d | offset = %-6d|  nstructname = %-20s  |\n",j, field->fname, DATA_TYPE[field->dtype], field->size, field->offset, field->nested_str_name);
        printf("  %-20s |", "");
        printf(ANSI_COLOR_CYAN "--------------------------------------------------------------------------------------------------------------------------|\n" ANSI_COLOR_RESET);
    }
}


void print_structure_db(struct_db_t *struct_db){
    
    if(struct_db != NULL) return;
    
    printf("printing STRUCURE DATABASE\n");
    int i = 0;
    struct _struct_db_rec_ *struct_rec = NULL;
    struct_rec = struct_db->head;
    printf("No of Structures Registered = %d\n", struct_db->count);
    while(struct_rec)
    {
        printf("structure No : %d (%p)\n", i++, struct_rec);
        print_structure_rec(struct_rec);
        struct_rec = struct_rec->next;
    }
}

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

    struct_db_t *struct_db = calloc(1, sizeof(struct_db_t));

    if(struct_db->head == NULL)
    {
        printf("struct_db->head is NULL\n");
    }

    REG_STRUCT(struct_db, emp_t, emp_fields);
    
    print_structure_db(struct_db);
    return 0;
}

