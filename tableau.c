#include <stdio.h> 
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>   /* malloc, free, rand */



int Fsize = 50;   /* maximum formula length                   */
int inputs = 20;  /* number of formulas expected in input.txt */
int i, j;
int ThSize = 100;  /* maximum size of set of formulas */
int TabSize = 500; /* maximum length of tableau queue */

char *prop = "pqr";
char *BC = "v^>"

;

/* A set will contain a list of words. Use NULL for emptyset.  */

struct set{
    char *item;         /* first word of non-empty set */
    struct set *tail;   /* remaining words in the set  */
};

/* A tableau will contain a list of pointers to sets (of words).  Use NULL for empty list.*/

struct tableau {
    struct set *S;         /* pointer to first set in non-empty list */
    struct tableau *rest;   /* list of pointers to other sets         */
};

int parse(char *g) 
{
    int i = 0;
    int left = -1, right = 0;
    int ln = 0, rn = 0;

    char fst = g[0];

    // Check the first char, prop condition
    
    for (i = 0; i < strlen(prop); i++)  {
        if (fst == prop[i]) {
            // 1st char is a prop, it has more than one char
            if (strlen(g) > 1) return 0;
            // only 1 char which is prop
            else return 1;
        }
    }

    if (fst != '(' && fst != '-') return 0;

    // Check if negation
    if (fst == '-') {
        // remove '-' sign
        g++;

        if(parse(g) != 0) return 2;
        else return 0;
    }

    // Check Binary Propositional statement
    if (fst == '(')
    {
        int BC_show = 0;

        g++;
        if (g[strlen(g) - 1] != ')') return 0;
        else for(i = 0; i < strlen(g) - 1; i++)
        {
            // And no.'(' and no.')'
            if (g[i] == '(') 
            {
                ln++;
                left = i;
                continue;
            }
            else if (g[i] == ')') 
            {
                rn++;
                right = i;
                continue;
            }
            
            for (j = 0; j < strlen(BC); j++)
            {
                if (g[i] == BC[j]) {
                    if(i < 1) return 0;
                    if(g[i - 1] == '-' || g[i - 1] == '(') return 0;
                    if(g[i + 1] == ')') return 0;
                    // p^q^r condition
                    if(BC_show == 1 && ln == rn) return 0; 
                }
            }

            // Check if main connective
            if (ln == rn && BC_show == 0)
            {
                for(j = 0 ; j < strlen(BC); j++)
                {
                    if (g[i] == BC[j]) 
                    {
                        BC_show = 1;
                        break;
                    }
                }
            }
        }
        if (ln != rn) return 0;
        else if(left >= right) return 0; 
        else return 3;
    }
    return 0;
}

char *partone(char *g)
{
    char *pt_one;

    int ln = 0, rn = 0;
    char fst = g[1];

    for (i = 0; i < strlen(prop); i++)  {
        if (fst == prop[i]) 
        {   
            pt_one = malloc(sizeof(char)*2);
            pt_one[0] = fst;
            pt_one[1] = '\0';
            return pt_one;
        }
    }

    if(fst == '-') {
        // remove '-'
        g++;

        char *nega = malloc(sizeof(char)*2);
        nega[0] = '-';
        nega[1] = '\0';

        return strcat(nega,partone(g));
    }
    

    // remove '(' 
    g++;

    // If main connective shows
    int BC_show = 0;
    int BC_index = 0;
    int break_sign = 0;
    for(i = 0; i < strlen(g) - 1; i++)
    {
        if(g[i] == '(' && BC_show == 0) ln++;
        else if (g[i] == ')' && BC_show == 0) {
            rn++;
            continue;
        }

        if (ln == rn)
        {
            for(j = 0 ; j < strlen(BC); j++)
            {
                if (g[i] == BC[j]) 
                {
                    BC_show = 1;
                    BC_index = i;
                    break_sign = 1;
                    break;
                }
            }
            if(break_sign == 1) break;
        }
    }

    pt_one = malloc(sizeof(char)*(BC_index + 1));
    for(i = 0; i < BC_index; i++)  pt_one[i] = g[i];
    pt_one[BC_index] = '\0'; 
    return pt_one;
}

char *parttwo(char *g)
{
    // only left part two and ')'
    g+= (strlen(partone(g)) + 2);

    // Copy to a new string to delete ')'
    char *pt_two = malloc(sizeof(char)*strlen(g));
    strcpy(pt_two, g);
    pt_two[strlen(pt_two) - 1] = '\0'; 

    return pt_two;
}

struct tableau *clone(struct tableau g)
{
    struct set *set_copy = malloc(sizeof(struct set));
    struct tableau *copy = malloc(sizeof(struct tableau));
    copy->S = set_copy;

    struct set *temp_copy_set = malloc(sizeof(struct set));
    struct tableau *temp_copy_tableau = malloc(sizeof(struct tableau));
    temp_copy_tableau = copy;
    temp_copy_set = temp_copy_tableau->S;

    struct set *temp_set = malloc(sizeof(struct set));
    struct tableau *temp_tableau = malloc(sizeof(struct tableau));
    // temp_set = temp_tableau->S;
    temp_tableau = &g;

 
        temp_set = temp_tableau->S;
        // clone the S part of each tableau
        while (temp_set) {
            temp_copy_set->item = malloc(sizeof(char)*(strlen(temp_set->item) + 1));
            strcpy(temp_copy_set->item, temp_set->item);
            temp_set = temp_set->tail;
            if (!temp_set)break;

            if (!temp_copy_set->tail) temp_copy_set->tail = malloc(sizeof(struct set));
            temp_copy_set = temp_copy_set->tail;
        }

        // switch temp_tableau to the rest part of t
        temp_tableau = temp_tableau->rest;
        if (temp_tableau) temp_copy_tableau = temp_copy_tableau->rest;

    // free(temp_set);
    // free(temp_tableau);
    // free(temp_copy_set);
    // free(temp_copy_tableau);
    return copy;
}

char *simplify(char *fmla){
    int j = 0;
    int leftP;
    int detected = 0;
    char *binary;

    int length = strlen(fmla);

    /* Simplify the statement here (i.e. reduce Redundant negation symbols)*/
        // end with literal
        if(fmla[strlen(fmla) - 1] != ')') 
        {
            // odd no. '-' 
            if (length % 2 == 0){
                if (length == 2) return fmla;
                else {
                    binary = malloc(sizeof(char)*(length - i));
                    if (leftP % 2 == 0) binary[j] = fmla[i];
                    binary[0] = '-';
                    binary[1] = fmla[length - 1];
                }
            }
            // even no. '-'
            else {
                binary = malloc(sizeof(char)*1);
                binary[0] = fmla[length - 1];
            }
        }
        else 
        { 
            for(i = 0; i < length; i++)
            {
                if (detected == 1) {
                    binary[++j] = fmla[i];
                }

                if(fmla[i] == '(' && !detected) {
                    leftP = i;
                    if (i == 1) return fmla;
                    detected = 1;
                    binary = malloc(sizeof(char)*(length - i));
                    if (leftP % 2 == 0) binary[j] = fmla[i];
                    else {
                        binary[0] = '-'; 
                        binary[++j] = '(';
                    }
                }    
            }
        }
    return binary;
}

void swap(struct tableau *t, struct set *s)
{
    char *tmp_string = s->item;
    char *fmla = t->S->item;
    s->item = fmla;
    t->S->item = tmp_string;
}

int closed(struct tableau *t)
{
    int i = 0,j = 0;
    char branch[1000];
    struct set *set = malloc(sizeof(struct set));
    struct tableau *temp = malloc(sizeof(struct tableau));

    temp = t;

    int closed = 1;
    
    while(temp)
    {
        int branch_closed = 0;
        int literal_index = 0;

        memset(branch, 0, 1000);

        set = temp->S;

        while(set)
        {
            if(set->item) {
                if (set->item[0] == '-') {
                    branch[literal_index++] = set->item[0];
                    branch[literal_index++] = set->item[1];
                }
                else branch[literal_index++] = *(set->item);

                set = set->tail;
            }
            else set = set->tail;
        }

        if (branch[0])
        {

            for (i = 0; i < 1000; i++)
            {
                if (!branch_closed)
                {
                    char literal = branch[i];
                    char negated[2];
                    if (literal != '-')  {
                        negated[0] = '-';
                        negated[1] = literal;
                    }
                    else negated[0] = branch[++i];

                    for(j = 0 ; j < i; j++)
                    {
                        char literal = branch[j];
                        if (literal != '-')
                        {
                            if (negated[0] == literal) {
                                branch_closed = 1;
                                break;
                            }
                            else continue;
                        } 
                        else {
                            if (i != j + 1)
                            {
                                if  (negated[0] == '-' && negated[1] == branch[j + 1])
                                {
                                    branch_closed = 1;
                                    break;
                                }
                                j++;
                            }
                        }
                    }
                }
                else break;
            }
        }
        if (!branch_closed) closed = 0; 
        temp = temp->rest;
    }

    // free(set);
    // free(temp);

    return closed;
}

void complete(struct tableau *t) {

    char *fmla = t->S->item;
    int type   = parse(fmla);
    int length = strlen(fmla);

    int j;
    int leftP;
    int end = 0;
    int detected = 0;
    char *binary;

    int change_o_NULL = 0;

    if (type == 2)
    {
        binary = simplify(fmla);
        if (binary[0] != '-') type = 3; 
        t->S->item = binary;
        fmla = t->S->item;
        length = strlen(binary);
        if (length < 3) type = 1;
    }

    struct set *temp_set         = malloc(sizeof(struct set));
    struct tableau *temp_tableau = malloc(sizeof(struct tableau));

    switch(type)
    {
        case 1: {
            int is_swap = 0;
            char *tmp_string;
            if (!t->S->tail) break;
            else {
                temp_set = t->S;
                while(temp_set->tail) 
                {
                    temp_set = temp_set->tail;
                    int sub_type = parse(temp_set->item);
                    if (sub_type == 2) {
                        temp_set->item = simplify(temp_set->item);
                        if (strlen(temp_set->item) > 3){
                            swap(t,temp_set);
                            is_swap = 1;
                            break;
                        }
                    }
                    else if (sub_type == 3){
                        swap(t,temp_set);
                        is_swap = 1;
                        break;
                    }
                }
                if (is_swap) complete(t);

                break;
            }
            break;
        }
        case 2:
                // binary = simplify(fmla);
                // t->S->item = binary;
                // fmla = t->S->item;  
                // length = strlen(fmla);

            { 
                char *n_PartOne;
                char *n_PartTwo;

                // Tableaux (only with binary) possibly with negation
                    
                    fmla++;
                    length--;
                    char *o_PartOne = partone(fmla);
                    char *o_PartTwo = parttwo(fmla);
                    switch(fmla[strlen(o_PartOne) + 1])
                    {
                        case '^': 
                        {
                                // Add '-' at the start of the partone
                                n_PartOne = malloc(strlen(o_PartOne) + 1);
                                n_PartOne[0] = '-';
                                for (i = 0; i < strlen(o_PartOne); i++) n_PartOne[i + 1] = o_PartOne[i];

                                // Add '-' at the start of the parttwo
                                n_PartTwo = malloc(strlen(o_PartTwo) + 1);
                                n_PartTwo[0] = '-';
                                for (i = 0; i < strlen(o_PartTwo); i++) n_PartTwo[i + 1] = o_PartTwo[i];
                                struct set *S0 = malloc(sizeof(struct set));
                                struct set *S1 = malloc(sizeof(struct set));
                                struct tableau *t1 = malloc(sizeof(struct tableau));

                                if (t->S->tail)
                                {
                                    t->S = t->S->tail;
                                    change_o_NULL = 1;
                                    t1 = clone(*t);
                                }
                                
                                if (!t->S->tail) 
                                {
                                    t->S->tail = S0;
                                    S0->item = n_PartOne;
                                }
                                else 
                                { 
                                    temp_set = t->S->tail;
                                    while(temp_set->tail) temp_set = temp_set->tail;
                                    temp_set->tail = S0;
                                    S0->item = n_PartOne;
                                }

                                if (t1->S)
                                {
                                    temp_set = t1->S;
                                    while(temp_set->tail) temp_set = temp_set->tail;
                                    temp_set->tail  = S1;
                                }
                                else t1->S = S1;

                                S1->item = n_PartTwo;

                                if(!change_o_NULL) t->S = t->S->tail;
                                complete(t);

                                // connect t1 to t
                                if (!t->rest) t->rest = t1;
                                else {
                                    // Dive to the deepest tableau
                                    temp_tableau = t->rest;
                                    while(temp_tableau->rest) temp_tableau = temp_tableau->rest;
                                    temp_tableau->rest = t1;
                                }

                                complete(t1);
                                break;
                                
                        }

                        case '>': 
                        {
                                struct set *n_S1 = malloc(sizeof(struct set));
                                struct set *n_S2 = malloc(sizeof(struct set));

                                temp_set = t->S;
                                while(temp_set->tail) temp_set = temp_set->tail;
                                temp_set->tail = n_S1;
                                temp_set->tail->tail = n_S2;

                                n_PartTwo = malloc(strlen(o_PartTwo) + 1);
                                n_PartTwo[0] = '-';
                                for (i = 0; i < strlen(o_PartTwo); i++) n_PartTwo[i + 1] = o_PartTwo[i];

                                // Tick and Assign
                                n_S1->item = o_PartOne;
                                n_S2->item = n_PartTwo;
                                t->S = t->S->tail;
                              
                                complete(t);
                                break;
                        }

                        case 'v': 
                        {
                                // Add '-' at the start of the partone
                                n_PartOne = malloc(strlen(o_PartOne) + 1);
                                n_PartOne[0] = '-';
                                for (i = 0; i < strlen(o_PartOne); i++) n_PartOne[i + 1] = o_PartOne[i];

                                // Add '-' at the start of the parttwo
                                n_PartTwo = malloc(strlen(o_PartTwo) + 1);
                                n_PartTwo[0] = '-';
                                for (i = 0; i < strlen(o_PartTwo); i++) n_PartTwo[i + 1] = o_PartTwo[i];

                                struct set *n_S1 = malloc(sizeof(struct set));
                                struct set *n_S2 = malloc(sizeof(struct set));

                                temp_set = t->S;
                                while(temp_set->tail != NULL) temp_set = temp_set->tail;
                                temp_set->tail = n_S1;
                                temp_set->tail->tail = n_S2;

                                // Tick and Assign
                                t->S->item = NULL;
                                n_S1->item = n_PartOne;
                                n_S2->item = n_PartTwo;

                                t->S = t->S->tail;
                              
                                complete(t);
                                break;
                        }
                    }
                    break;
            }
        case 3:
        {
                char *o_PartOne = partone(fmla);
                char *o_PartTwo = parttwo(fmla);
                char *n_PartOne;
                char *n_PartTwo;

                switch (fmla[strlen(o_PartOne) + 1]){
                    case '^': 
                    {   
                            struct set *n_S1 = malloc(sizeof(struct set));
                            struct set *n_S2 = malloc(sizeof(struct set));

                            temp_set = t->S;
                            while(temp_set->tail) temp_set = temp_set->tail;
                            temp_set->tail = n_S1;
                            temp_set->tail->tail = n_S2;

                            // Tick and Assign
                            n_S1->item = o_PartOne;
                            n_S2->item = o_PartTwo;
                            t->S = t->S->tail;
                              
                            complete(t);
                            break;
                    }

                    case '>':
                    { 
                            struct set *S0 = malloc(sizeof(struct set));
                            struct set *S1 = malloc(sizeof(struct set));
                            struct tableau *t1 = malloc(sizeof(struct tableau));

                            n_PartOne = malloc(strlen(o_PartOne) + 1);
                            for(i = 0;i < strlen(o_PartOne) + 1; i++)
                            {
                                if (i == 0){
                                    n_PartOne[0] = '-';
                                    continue;
                                }
                                n_PartOne[i] = o_PartOne[i-1];
                            }

                            if (t->S->tail)
                            {
                                t->S = t->S->tail;
                                change_o_NULL = 1;
                                t1 = clone(*t);
                            }
                            
                            if (!t->S->tail) 
                            {
                                t->S->tail = S0;
                                S0->item = n_PartOne;
                            }
                            else 
                            {   
                                temp_set = t->S->tail;
                                while(temp_set->tail) temp_set = temp_set->tail;
                                temp_set->tail = S0;
                                S0->item = n_PartOne;
                            }


                            if (t1->S)
                            {
                                temp_set = t1->S;
                                while(temp_set->tail) temp_set = temp_set->tail;
                                temp_set->tail  = S1;
                            }
                            else t1->S = S1;

                            S1->item = o_PartTwo;

                            if (!change_o_NULL) t->S = t->S->tail;
                            complete(t);

                            // connect t1 to t
                            if (!t->rest) t->rest = t1;
                            else {
                                // Dive to the deepest tableau
                                temp_tableau = t->rest;
                                while(temp_tableau->rest) temp_tableau = temp_tableau->rest;
                                temp_tableau->rest = t1;
                            }

                            complete(t1);
                            break;
                    }
                    case 'v':
                    {
                            struct set *S0 = malloc(sizeof(struct set));
                            struct set *S1 = malloc(sizeof(struct set));
                            struct tableau *t1 = malloc(sizeof(struct tableau));
                            
                            if (t->S->tail)
                            {
                                t->S = t->S->tail;
                                change_o_NULL = 1;
                                t1 = clone(*t);
                            }

                            if (!t->S->tail) 
                            {
                                t->S->tail = S0;
                                S0->item = o_PartOne;
                            }
                            else 
                            {
                                temp_set = t->S->tail;
                                while(temp_set->tail) temp_set = temp_set->tail;
                                temp_set->tail = S0;
                                S0->item = o_PartOne;
                            }

                            if (t1->S)
                            {
                                temp_set = t1->S;
                                while(temp_set->tail) temp_set = temp_set->tail;
                                temp_set->tail  = S1;
                            }
                            else t1->S = S1;
                
                            S1->item = o_PartTwo;

                            if(!change_o_NULL) t->S = t->S->tail;
                            complete(t);

                            // connect t1 to t
                            if (!t->rest) t->rest = t1;
                            else {
                                // Dive to the deepest tableau
                                temp_tableau = t->rest;
                                while(temp_tableau->rest) temp_tableau = temp_tableau->rest;
                                temp_tableau->rest = t1;
                            }

                            complete(t1);
                            break;
                    }
                }
        }
   
    }
}


int main()

{ /*input 10 strings from "input.txt" */


  char *name = malloc(Fsize);

  FILE *fp, *fpout;
  /* reads from input.txt, writes to output.txt*/
  if ((  fp=fopen("input.txt","r"))==NULL){printf("Error opening file");exit(1);}
  if ((  fpout=fopen("output.txt","w"))==NULL){printf("Error opening file");exit(1);}

  int j;
  for(j=0;j<inputs;j++)
  {
    fscanf(fp, "%s",name);/*read formula*/
    switch (parse(name))
    {
      case(0): fprintf(fpout, "%s is not a formula.  \n", name);break;
      case(1): fprintf(fpout, "%s is a proposition. \n ", name);break;
      case(2): fprintf(fpout, "%s is a negation.  \n", name);break;
      case(3): {char *pone = partone(name);
                char *ptwo = parttwo(name);
                fprintf(fpout, "%s is a binary. The first part is %s and the second part is %s  \n", name, partone(name), parttwo(name));break;}
      default:fprintf(fpout, "What the f***!  ");
              
    }

    
    if (parse(name)!=0)
    {
      struct set *S = malloc(sizeof(struct set));
      struct tableau *t= malloc(sizeof(struct tableau));
      S->item = name;
      S->tail = NULL;
      t->S = S;
      t->rest = NULL;
      complete(t);
      if (closed(t))  fprintf(fpout, "%s is not satisfiable.\n", name);
      else fprintf(fpout, "%s is satisfiable.\n", name);
      free(S);
      free(t);
    }
    else  fprintf(fpout, "I told you, %s is not a formula.\n", name);
  } 
  
  fclose(fp);
  fclose(fpout);
  free(name);

  return(0);
}