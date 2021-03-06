/****************************************************************************
 **             PC-LISP (C) 1986 Peter Ashwood-Smith                       **
 **             MODULE : BUFUNC2                                           **
 **========================================================================**
 **    More built in functions for PC-LISP. Again the module install.c is  **
 ** called to install all the functions in this module.                    **
 ****************************************************************************/

#include        <stdio.h>
#include        <math.h>
#include        "lisp.h"

/*************************************************************************
 ** (intern atom) Will take an atom and put it on the oblist. This is   **
 ** done by simply toggling its 'interned' bit so that it is INTERNED.  **
 ** This way any property etc goes along with the interned atom.        **
 *************************************************************************/
struct conscell *buintern(form)
struct conscell *form;
{      struct alphacell *at;
       if ((form != NULL)&&(form->carp != NULL)&&(form->cdrp == NULL))
       {   at = ALPHA(form->carp);
           if (at->celltype == ALPHAATOM)
           {   at->interned = INTERNED;
               return(LIST(at));
           };
       };
       ierror("intern");  /*  doesn't return  */
       return NULL;   /*  keep compiler happy  */
}
