#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "app.h"



int add_structure_to_struct_db(struct_db_t *struct_db, 
                               struct_db_rec_t *struct_rec,
                               int start_with_new_struct)
{

    /*Note #struct_db was instantized at main() but doing nothing at REG_STRUCT 
    and #struct_rec is create dynamically from REG_STRUCT */
    
    struct_db_rec_t *rec_head = struct_db->head;

    if(rec_head == NULL) // same as if(struct_db->head == NULL)
    {
        //point the struct_db  to struct_rec
        //struct_rec contain fileds of information of structure
        
        struct_db->head = struct_rec;
        struct_db->count++;

        struct_rec->next = NULL;
    }
    else // at line 24 struct_db->head is updated to struct_rec thus struct_db->head & rec_head != NULL
    {
        if(start_with_new_struct == 0)
        {
            //we have new structure add in , let move registered structure(emp_t) to the next 
            struct_rec->next = rec_head;

            //start the structure head with the new structure student_t
            struct_db->head = struct_rec;

        }
        else
        {
            //head always start with registered/added structure
            struct_db->head = rec_head;

            //append newly added structure into next
            struct_db->head->next =struct_rec;
        }


        struct_db->count++;
    }

    return 0;
}

void print_structure_rec( struct _struct_db_rec_ *struct_rec)
{
    char *DATA_TYPE[] = {"UINT8", "UINT32", "INT32",
                     "CHAR", "OBJ_PTR", "VOID_PTR", "FLOAT",
                     "DOUBLE", "OBJ_STRUCT"};

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
    
    if(!struct_db) return;
    printf("printing STRUCURE DATABASE\n");
    int i = 0;
    struct_db_rec_t *struct_rec = NULL;
    struct_rec = struct_db->head;
    printf("No of Structures Registered = %d\n", struct_db->count);
    while(struct_rec != NULL){
        printf("structure No : %d (%p)\n", i++, struct_rec);
        //print_structure_rec(struct_db->head);
        print_structure_rec(struct_rec);
        struct_rec = struct_rec->next;
    }
}

void print_object_db(object_db_t *object_db)
{
    object_db_rec_t *head = object_db->head;
    unsigned int i = 0;
    printf(ANSI_COLOR_CYAN "Printing OBJECT DATABASE\n");
    for(; head; head = head->next){
        print_object_rec(head, i++);
    }
}

void print_object_rec(object_db_rec_t *obj_rec, int i)
{    
    if(!obj_rec) return;
    printf(ANSI_COLOR_MAGENTA "-----------------------------------------------------------------------------------------------------|\n"ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "%-3d ptr = %-10p | next = %-10p | units = %-4d | struct_name = %-10s | is_root = %s\n"ANSI_COLOR_RESET, 
        i, obj_rec->ptr, obj_rec->next, obj_rec->units, obj_rec->struct_rec->struct_name,obj_rec->is_root ? "TRUE " : "FALSE"); 
    printf(ANSI_COLOR_MAGENTA "-----------------------------------------------------------------------------------------------------|\n"ANSI_COLOR_RESET);
}

static object_db_rec_t *object_db_look_up(object_db_t *object_db, void *ptr)
{
    object_db_rec_t *head = object_db->head;
    if(!head) return NULL;
    
    for(; head; head = head->next){
        if(head->ptr == ptr)
        {
            printf("not gonna happend\n");
            return head;    
        }

    }
    return NULL;
}

static struct_db_rec_t *struct_db_look_up(struct_db_t *struct_db, char *struct_name)
{    
    struct_db_rec_t *head = struct_db->head;
    if(!head) return NULL;
    
    for(; head; head = head->next)
    {
        if(strncmp(head->struct_name, struct_name, MAX_STRUCTURE_NAME_SIZE) ==0)
            return head;
    }
    return NULL;
}

/*Working with objects*/
/*#object_db is from main() line 45, #struct_rec was instanized but do nothing and passed from xcalloc()*/
static void add_object_to_object_db(object_db_t *object_db, void *parameter_ptr, int units,struct_db_rec_t *parameter_struct_rec, mld_boolean_t is_root)
{       
    //object_db_rec_t *obj_rec = object_db_look_up(object_db, ptr);
    /*Dont add same object twice*/
    // assert(!obj_rec); 
    // ignore these code, complex in nature and don't thing it can happended.

    object_db_rec_t *obj_rec = calloc(1, sizeof(object_db_rec_t));

    obj_rec->next = NULL;
    obj_rec->ptr = parameter_ptr; //parameter_ptr isdynamic object, it was from calloc
    obj_rec->units = units;
    obj_rec->struct_rec = parameter_struct_rec; //parameter_struct_rec is dynamic object, it was from calloc
    obj_rec->is_visited = MLD_FALSE;
    obj_rec->is_root = is_root;

    object_db_rec_t *head = object_db->head;
        
    if(head == NULL)
    {
        object_db->head = obj_rec;
        obj_rec->next = NULL;
        object_db->count++;
        return;
    }
    else
    {
        //new structure add in , let move registered structureto the next
        obj_rec->next = head;
        // start the head with newly registered structure.
        object_db->head = obj_rec;
        object_db->count++;
    }
}

void* xcalloc(object_db_t *object_db, char *struct_name, int units)
{
    //This denitely is a checking before we proceed further
    //check for the name of structure, only proceed if align.
    struct_db_rec_t *struct_rec = struct_db_look_up(object_db->struct_db, struct_name);
    
    void *ptr = calloc(units, struct_rec->ds_size);
    
    if(struct_rec != NULL)
    {
        add_object_to_object_db(object_db, ptr, units, struct_rec,MLD_FALSE);
    }
    else
    {
        return (void*)(-1);
    }
     /*xcalloc by default set the object as non-root*/
    return ptr;
}

/* Application might create an object using xcalloc , but at the same time the object
* can be root object. Use this API to override the object flags for the object already
* preent in object db*/
void mld_set_dynamic_object_as_root(object_db_t *object_db, void *obj_ptr)
{
    object_db_rec_t *obj_rec = object_db_look_up(object_db, obj_ptr);
    assert(obj_rec);
    
    obj_rec->is_root = MLD_TRUE;
}

void run_mld_algorithm(object_db_t *object_db)
{
    /*Step 1 : Mark all objects in object databse as unvisited*/
    init_mld_algorithm(object_db);

    /* Step 2 : Get the first root object from the object db, it could be 
     * present anywhere in object db. If there are multiple roots in object db
     * return the first one, we can start mld algorithm from any root object*/

    object_db_rec_t *root_obj = get_next_root_object(object_db, NULL);

    while(root_obj)
    {        
        if(root_obj->is_visited)
        {
            printf("root_obj->is_visited\n");
            /* It means, all objects reachable from this root_obj has already been
             * explored, no need to do it again, else you will end up in infinite loop.
             * Remember, Application Data structures are cyclic graphs*/
            root_obj = get_next_root_object(object_db, root_obj);
            if(root_obj == NULL)
            {
                printf("root_obj is null\n");
            }
            // if no further root obeject is found, root_obj will be NULL, thus end it with continue to quit the while.
            continue;
        }
        else
        {
            printf("run_mld_algorithm else\n");
            /*root objects are always reachable since application holds the global
            * variable to it*/ 
            root_obj->is_visited = MLD_TRUE;
        
            /*Explore all reachable objects from this root_obj recursively*/
            // mld_explore_objects_recursively(object_db, root_obj);

            //root_obj = get_next_root_object(object_db, root_obj);
        }
        

    } 

}