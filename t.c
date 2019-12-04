#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i = 0, j = 0;

char *prop = "pqr";
char *BC = "v^>";


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

char *simplify(char *fmla){
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
                    binary = malloc(length - i);
                    if (leftP % 2 == 0) binary[j] = fmla[i];
                    binary[0] = '-';
                    binary[1] = fmla[length - 1];
                }
            }
            // even no. '-'
            else {
                binary = malloc(1);
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

                if(fmla[i] == '(') {
                    leftP = i;
                    if (i == 1) return fmla;
                    detected = 1;
                    binary = malloc(length - i);
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

char *partone(char *g)
{
    char *pt_one;

    int ln = 0, rn = 0;
    char fst = g[1];

    for (i = 0; i < strlen(prop); i++)  {
        if (fst == prop[i]) 
        {   
            pt_one = malloc(1);
            pt_one[0] = fst;
            return pt_one;
        }
    }

    if(fst == '-') {
        // remove '-'
        g++;

        char *nega = malloc(1);
        nega[0] = '-';

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

    pt_one = malloc(BC_index);
    for(i = 0; i < BC_index; i++)  pt_one[i] = g[i];
    return pt_one;
}

int closed(struct tableau *t)
{
    int i = 0,j = 0;
    struct set *set = malloc(sizeof(struct set));
    struct tableau *temp = malloc(sizeof(struct tableau));

    temp = t;

    int closed = 1;
    
    while(temp)
    {
        int branch_closed = 0;
        int literal_index = 0;

        char *branch = malloc(sizeof(char)*(1000));
        printf("Size of branch %lu\n", sizeof(branch));

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
                    char *negated = malloc(2);
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
        free(branch);
    }

    // free(set);
    // free(temp);

    return closed;
}

int main()
{
    char *name = "(-(rv-q)>((-qv-q)>-(rv-q)))";
    
    struct set * S= malloc(sizeof(struct set));
    struct tableau * t= malloc(sizeof(struct tableau));
    S->item = name;
    S->tail = NULL;
    t->S = S;
    t->rest = NULL;
    printf("%s\n",partone(t->S->item));
    printf("%lu", strlen(partone(t->S->item)));
    // complete(t);

    
}

// // (((p>q)>(q>p))^-q)
// (--pv-p)
// ((p^q)vr)