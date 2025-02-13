// URL: http://www.koders.com/c/fid67F09A5A42BB1F6B563434398602BF78C930F0C0.aspx?s=TV+Raman
// Released under the GPL as part of the Viewmol project

/*******************************************************************************
*                                                                              *
*                                   Viewmol                                    *
*                                                                              *
*                              S C A N D I R . C                               *
*                                                                              *
*                 Copyright (c) Joerg-R. Hill, October 2003                    *
*                                                                              *
********************************************************************************
*
* $Id: scandir.c,v 1.3 2003/11/07 11:15:53 jrh Exp $
* $Log: scandir.c,v $
* Revision 1.3	2003/11/07 11:15:53	jrh
* Release 2.4
*
* Revision 1.2	2000/12/10 15:37:02	jrh
* Release 2.3
*
* Revision 1.1	1999/05/24 01:29:43	jrh
* Initial revision
*
*/
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>

// This function is for Windows only, Linux already supports it

int scandir(const char *dir, struct dirent ***namelist,
						int (*select)(const struct dirent *),
						int (*compar)(const void *, const void *))
{
	DIR *d;
	struct dirent *entry;
	register int i=0;
	size_t entrysize;

	if ((d=opendir(dir)) == NULL)
		 return(-1);

	*namelist=NULL;
	while ((entry=readdir(d)) != NULL)
	{
		if (select == NULL || (select != NULL && (*select)(entry)))
		{
			*namelist=(struct dirent **)realloc((void *)(*namelist),
								 (size_t)((i+1)*sizeof(struct dirent *)));
	if (*namelist == NULL) return(-1);
	entrysize=sizeof(struct dirent)-sizeof(entry->d_name)+strlen(entry->d_name)+1;
	(*namelist)[i]=(struct dirent *)malloc(entrysize);
	if ((*namelist)[i] == NULL) return(-1);
	memcpy((*namelist)[i], entry, entrysize);
	i++;
		}
	}
	if (closedir(d)) return(-1);
	if (i == 0) return(-1);
	if (compar != NULL)
		qsort((void *)(*namelist), (size_t)i, sizeof(struct dirent *), compar);

	return(i);
}

int alphasort(const void *a, const void *b)
{
    char *t1 = ((*(struct dirent**)a))->d_name;
    char *t2 = ((*(struct dirent**)b))->d_name;
	return(strcmp(t1, t2));
}
