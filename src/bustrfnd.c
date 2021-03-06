/* */
/*
 | PC-LISP
 */
#include <stdio.h>
#include "lisp.h"
#ifdef __APPLE__
#include <regex.h>
#endif

/*
 |  The regular expression utility. We use either the SYSTEMV 'regcmp' stuff
 |  or the BERKELEY re_comp routines. We do not pass patterns back to LISP
 |  because SYSV only handles a static pattern of its own hence we must be
 |  compatible with the minimum system.
 */
#ifdef __APPLE__
static regex_t pattern;
static int reUsed = 0;
#else
#if RE_COMP
    extern char *re_comp();
    extern int   re_exec();
#else
    extern char *regcmp();
    extern char *regex();
    static char *pattern = NULL;
#endif
#endif
 
/*
 |  t <- (strsetpat string [nil]))
 |  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 |  Establish the search pattern for future strfndpat calls. We modify the search
 |  pattern to allow wild card '*' searches such as 'a*b' etc and to escape some
 |  of the special search characters '$, . and +'. If the caller passes nil second
 |  argument then we do NOT perform the substitution and just pass the expr raw to
 |  the expression matcher.
 */
struct conscell *bustrsetpat(form)
   struct conscell *form;
{
#ifndef _MSC_VER
   char *s,*p; char expr[MAXATOMSIZE + 4];
   int modify;

   if (form != NULL) {
      if (GetString(form->carp, &s)) {
         modify = 1;
         form = form->cdrp;
         if (form != NULL) {
             if (form->cdrp != NULL) goto er;
             if (form->carp == NULL)
             modify = (form->carp != NULL);
         }
         if (modify) {
             p = expr;
             *p++ = '^';                         /* start of string '^' */
             while (*s != '\0') {
                switch (*s) {
                   case '$':
                   case '.':
                   case '+':  *p++ = '\\';
                              break;
                   case '*':  *p++ = '.';        /* expand '*' into '.*' expr */
                              break;
                }
                *p++ = *s++;
             }
             *p++ = '$'; *p = '\0';              /* match end of string '$' */
         } else
             strcpy(expr, s);
#ifdef __APPLE__
	 if (reUsed)
             regfree(&pattern);
	 if (!regcomp(&pattern, expr, 0))  return(LIST(thold));
#else
#        if RE_COMP
            if (re_comp(expr) == NULL) return(LIST(thold));
#        else
            if (pattern) free(pattern);
            if ((pattern = regcmp(expr, NULL)) != NULL) return(LIST(thold));
#        endif
#endif
      }
   }
#endif
er:ierror("strsetpat");  /*  doesn't return  */
   return NULL;   /*  keep compiler happy  */
}

/*
 |  t | nil <- (strfndpat string)
 |  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 |  Return True if the string matches the previously establish search
 |  pattern.
 */
struct conscell *bustrfndpat(form)
   struct conscell *form;
{
#ifndef _MSC_VER
   char *s;
   if ((form != NULL)&&(form->cdrp == NULL)) {
      if (GetString(form->carp, &s)) {
#ifdef __APPLE__
	return( regexec(&pattern, s, 0, NULL, 0) ? NULL : LIST(thold) );
#else
#        if RE_COMP
            return( (re_exec(s) == 1) ? LIST(thold) : NULL );
#        else
            char junk[MAXATOMSIZE + 4];
            if (pattern)
                return( (regex(pattern, s, junk) != NULL) ? LIST(thold) : NULL );
#        endif
#endif
      }
   }
#endif
   ierror("strfndpat");  /*  doesn't return  */
   return NULL;   /*  keep compiler happy  */
}

