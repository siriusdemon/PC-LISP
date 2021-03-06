

/*
 | PC-LISP (C) 1984-1989 Peter J.Ashwood-Smith
 */
#include <stdio.h>
#include <math.h>
#include "lisp.h"

/*************************************************************************
 ** buexp :Returns e to the power of the single double parameter.       **
 *************************************************************************/
struct conscell *buexp(form)
struct conscell *form;
{      double f;
       if ((form != NULL)&&(form->cdrp == NULL))
          if (GetFloat(form->carp,&f))
              return(newrealop(exp(f)));
       ierror("exp");  /*  doesn't return  */
       return NULL;   /*  keep compiler happy  */
}
