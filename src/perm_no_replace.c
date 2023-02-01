/* Copyright 2023 by Roger S. Bivand. */

#include "spdep.h"

/* nsim, n, k */

SEXP draw_no_replace(int n, int crsi);

SEXP perm_no_replace(SEXP nsim0, SEXP n0, SEXP crsi0) {
    SEXP y, yk;
    int nsim = INTEGER_POINTER(nsim0)[0];
    int n = INTEGER_POINTER(n0)[0];
    int crsi = INTEGER_POINTER(crsi0)[0];
Rprintf("%d %d %d\n", nsim, n, crsi);
    GetRNGstate();
    PROTECT(y = allocVector(INTSXP, crsi*nsim));
    for (int k = 0; k < nsim; k++) {
        yk = draw_no_replace(n, crsi);
        for (int i = 0; i < crsi; i++) {
            INTEGER_POINTER(y)[k + (i*nsim)] = INTEGER_POINTER(yk)[i];
        }
    }
    PutRNGstate();
    UNPROTECT(1);
    return y;
}

SEXP draw_no_replace(int n, int crsi) {
    SEXP y;
    PROTECT(y = allocVector(INTSXP, crsi));
    int *iy = INTEGER(y);
    int *x = (int *)R_alloc(n, sizeof(int));
    for (int i = 0; i < n; i++) x[i] = i;
    for (int i = 0; i < crsi; i++) {
        int j = (int)(R_unif_index(n));
        iy[i] = x[j] + ROFFSET;
        x[j] = x[--n];
    }
    UNPROTECT(1);
    return y;
} 
