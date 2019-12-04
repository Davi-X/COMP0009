#include <stdio.h> 
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */

int Fsize = 50; /* max string length of formulas*/
int inputs = 10;

int i;
int j;

char *prop = "pqr";
char *BC = "v^>";

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

char *parttwo(char *g)
{
    // only left part two and ')'
    g+= (strlen(partone(g)) + 2);

    // Copy to a new string to delete ')'
    char *pt_two = malloc(strlen(g));
    strcpy(pt_two, g);
    pt_two[strlen(pt_two) - 1] = '\0'; 

    return pt_two;
}

int main()
{ /*input 10 strings from "input.txt" */

  char *name = malloc(Fsize);
  FILE *fp, *fpout;
 
  /* reads from input.txt, writes to output.txt*/
  if ((  fp    = fopen("input.txt" ,"r")) == NULL)  { printf("Error opening file"); exit(1);}
  if ((  fpout = fopen("output.txt","w")) == NULL)  { printf("Error opening file"); exit(1);}

  int j;
  for( j = 0; j < inputs; j++)
    {
      fscanf(fp, "%s",name);/*read formula*/
      switch (parse(name))
      {
          case(0): 
                fprintf(fpout, "%s is not a formula.  \n", name); break;
          case(1): 
                fprintf(fpout, "%s is a proposition. \n ", name); break;
          case(2): 
                fprintf(fpout, "%s is a negation.  \n", name); break;
          case(3): 
                fprintf(fpout, "%s is a binary. The first part is %s and the second part is %s  \n", name, partone(name), parttwo(name)) ;break;
          default: 
                fprintf(fpout, "What the f***!  ");
       }
    }

  fclose(fp);
  fclose(fpout);
  free(name);

  return(0);
}