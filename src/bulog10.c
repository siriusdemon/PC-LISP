/* EDITION AB01, APFUN MR.68 (90/04/18 09:23:40) -- CLOSED */                   
/* --- */

/*
 | PC-LISP (C) 1984-1989 Peter J.Ashwood-Smith
 */
#include <stdio.h>
#include <math.h>
#include "lisp.h"

/*************************************************************************
 ** bulog10 :Returns the base 10 log of the single double parameter.    **
 *************************************************************************/
struct conscell *bulog10(form)
struct conscell *form;
{      double f;
       if ((form != NULL)&&(form->cdrp == NULL))
          if (GetFloat(form->carp,&f))
              return(newrealop(log10(f)));
       ierror("log10");
}
