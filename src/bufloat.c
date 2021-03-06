

/*
 | PC-LISP (C) 1984-1989 Peter J.Ashwood-Smith
 */
#include <stdio.h>
#include <math.h>
#include "lisp.h"

/*************************************************************************
 ** bufloat: (float number) Return a flonum representation of number.   **
 *************************************************************************/
struct conscell *bufloat(form)
struct conscell *form;
{      struct conscell *temp;
       if ((form != NULL)&&(form->cdrp == NULL))
       {  if ((temp = form->carp) != NULL)
          {  if (temp->celltype == REALATOM)
                return(temp);
             if (temp->celltype == FIXATOM)
                return(newrealop((double)FIX(temp)->atom));
          };
       };
       ierror("float");  /*  doesn't return  */
       return NULL;   /*  keep compiler happy  */
}
