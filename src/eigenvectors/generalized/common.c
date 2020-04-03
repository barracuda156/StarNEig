///
/// @file
///
/// @author Carl Christian K. Mikkelsen (spock@cs.umu.se), Umeå University
///
/// @section LICENSE
///
/// Copyright (c) 2019, Umeå Universitet
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
///
/// 1. Redistributions of source code must retain the above copyright notice,
///    this list of conditions and the following disclaimer.
///
/// 2. Redistributions in binary form must reproduce the above copyright notice,
///    this list of conditions and the following disclaimer in the documentation
///    and/or other materials provided with the distribution.
///
/// 3. Neither the name of the copyright holder nor the names of its
///    contributors may be used to endorse or promote products derived from this
///    software without specific prior written permission.
///
/// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
/// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
/// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
/// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
/// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
/// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
/// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
/// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
/// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
/// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
/// POSSIBILITY OF SUCH DAMAGE.
///

#include <starneig_config.h>
#include <starneig/configuration.h>
#include "common.h"
#include <time.h>

// Solver for small shifted linear systems
void starneig_eigvec_gen_dlaln2(
    int ltrans, int na, int nw, double smin, double ca, double *a, size_t lda,
    double d1, double d2, double *b, size_t ldb, double wr, double wi,
	double *x, size_t ldx, double *scale, double *xnorm, int *info)
{
    int ilda=(int)lda;
    int ildb=(int)ldb;
    int ildx=(int)ldx;
    dlaln2_(&ltrans, &na, &nw, &smin, &ca,
	  	  a, &ilda, &d1, &d2,
	  	  b, &ildb, &wr, &wi,
	  	  x, &ildx, scale, xnorm, info);
}


// Copy matrices
void starneig_eigvec_gen_dlacpy(
    char *uplo, int m, int n, double *a, size_t lda, double *b, size_t ldb)
{
    int ilda=(int)lda;
    int ildb=(int)ldb;
    dlacpy_(uplo, &m, &n,
	  	  a, &ilda,
	  	  b, &ildb);
}

// Compute norms
double starneig_eigvec_gen_dlange(
    char *norm, int m, int n, double *a, size_t lda, double *work)
{
    int ilda=(int)lda;
    return dlange_(norm, &m, &n, a, &ilda, work);
}

// Matrix matrix multiplication
void starneig_eigvec_gen_dgemm(
    char *transa, char *transb, int m, int n, int k, double alpha, double *a,
    size_t lda, double* b, size_t ldb, double beta, double* c, size_t ldc)
{
    int ilda=(int)lda;
    int ildb=(int)ldb;
    int ildc=(int)ldc;

    dgemm_(transa, transb, &m, &n, &k, &alpha,
	 	 a, &ilda,
	 	 b, &ildb, &beta,
	 	 c, &ildc);

}

// Generalised eigenvalues of 2-by-2 matrices
void starneig_eigvec_gen_dlag2(
    double *a, size_t lda, double *b, size_t ldb, double safemin,
    double *scale1, double *scale2, double *wr1, double *wr2, double *wi)
{
    int ilda=(int)lda;
    int ildb=(int)ldb;
    dlag2_(a, &ilda,
	 	 b, &ildb, &safemin, scale1, scale2, wr1, wr2, wi);
}

// Generalized eigenvectors
void starneig_eigvec_gen_dtgevc(
    char *side, char *howmany, int *select, int m, double *s, size_t lds,
	double *t, size_t ldt, double *x, size_t ldx, double *y, size_t ldy,
	int n, int *used, double *work, int *info)
{
    // Convert leading dimensions to int
    int ilds=(int)lds;
    int ildt=(int)ldt;
    int ildx=(int)ldx;
    int ildy=(int)ldy;
    dtgevc_(side, howmany, select, &m,
	  	  s, &ilds,
	  	  t, &ildt,
	  	  x, &ildx,
	  	  y, &ildy, &n, used, work, info);
}
