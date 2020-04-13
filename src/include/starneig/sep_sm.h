///
/// @file
///
/// @brief This file contains shared memory interface functions for standard
/// eigenvalue problems.
///
/// @author Mirko Myllykoski (mirkom@cs.umu.se), Umeå University
/// @author Lars Karlsson (larsk@cs.umu.se), Umeå University
///
/// @section LICENSE
///
/// Copyright (c) 2019-2020, Umeå Universitet
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

#ifndef STARNEIG_SEP_SM_H
#define STARNEIG_SEP_SM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <starneig/configuration.h>
#include <starneig/error.h>
#include <starneig/expert.h>

///
/// @defgroup starneig_sm_sep Shared Memory / Standard EVP
///
/// @brief Functions for solving non-symmetric standard eigenvalue problems on
/// shared memory systems.
///
/// @{
///

///
/// @name Computational functions
/// @{
///

///
/// @brief Computes a Hessenberg decomposition of a general matrix.
///
/// @param[in] n
///         The order of \f$A\f$ and \f$Q\f$.
///
/// @param[in,out] A
///         On entry, the general matrix \f$A\f$.
///         On exit, the upper Hessenberg matrix \f$H\f$.
///
/// @param[in] ldA
///         The leading dimension of \f$A\f$.
///
/// @param[in,out] Q
///         On entry, the orthogonal matrix \f$Q\f$.
///         On exit, the product matrix \f$Q * U\f$.
///
/// @param[in] ldQ
///         The leading dimension of \f$Q\f$.
///
/// @return @ref STARNEIG_SUCCESS (0) on success. Negative integer -i when i'th
/// argument is invalid. Positive error code otherwise.
///
starneig_error_t starneig_SEP_SM_Hessenberg(
    int n,
    double A[], int ldA,
    double Q[], int ldQ);

///
/// @brief Computes a Schur decomposition given a Hessenberg decomposition.
///
/// @param[in] n
///         The order of \f$H\f$ and \f$Q\f$.
///
/// @param[in,out] H
///         On entry, the upper Hessenberg matrix \f$H\f$.
///         On exit, the Schur matrix \f$S\f$.
///
/// @param[in] ldH
///         The leading dimension of \f$H\f$.
///
/// @param[in,out] Q
///         On entry, the orthogonal matrix \f$Q\f$.
///         On exit, the product matrix \f$Q * U\f$.
///
/// @param[in] ldQ
///         The leading dimension of \f$Q\f$.
///
/// @param[out] real
///         An array of the same size as \f$H\f$ containing the real parts of
///         the computed eigenvalues.
///
/// @param[out] imag
///         An array of the same size as \f$H\f$ containing the imaginary parts
///         of the computed eigenvalues.
///
/// @return @ref STARNEIG_SUCCESS (0) on success. Negative integer -i when i'th
/// argument is invalid. Positive error code otherwise.
/// @ref STARNEIG_DID_NOT_CONVERGE if the QR algorithm failed to converge.
///
starneig_error_t starneig_SEP_SM_Schur(
    int n,
    double H[], int ldH,
    double Q[], int ldQ,
    double real[], double imag[]);

///
/// @brief Reorders selected eigenvalues to the top left corner of a Schur
/// decomposition.
///
/// @param[in] n
///         The order of \f$S\f$ and \f$Q\f$.
///
/// @param[in,out] selected
///         The selection array.
///         On entry, the initial positions of the selected eigenvalues.
///         On exit, the final positions of all correctly placed selected
///         eigenvalues. In case of failure, the number of 1's in the output
///         may be less than the number of 1's in the input.
///
/// @param[in,out] S
///         On entry, the Schur matrix \f$S\f$.
///         On exit, the updated Schur matrix \f$\hat{S}\f$.
///
/// @param[in] ldS
///         The leading dimension of \f$S\f$.
///
/// @param[in,out] Q
///         On entry, the orthogonal matrix \f$Q\f$.
///         On exit, the product matrix \f$Q * U\f$.
///
/// @param[in] ldQ
///         The leading dimension of \f$Q\f$.
///
/// @param[out] real
///         An array of the same size as \f$S\f$ containing the real parts of
///         the computed eigenvalues.
///
/// @param[out] imag
///         An array of the same size as \f$S\f$ containing the imaginary parts
///         of the computed eigenvalues.
///
/// @return @ref STARNEIG_SUCCESS (0) on success. Negative integer -i when i'th
/// argument is invalid. Positive error code otherwise.
/// @ref STARNEIG_PARTIAL_REORDERING if the  Schur form is not fully reordered.
///
/// @see starneig_SEP_SM_Select
///
starneig_error_t starneig_SEP_SM_ReorderSchur(
    int n,
    int selected[],
    double S[], int ldS,
    double Q[], int ldQ,
    double real[], double imag[]);

///
/// @brief Computes a (reordered) Schur decomposition of a general matrix.
///
/// @param[in] n
///         The order of \f$A\f$ and \f$Q\f$.
///
/// @param[in,out] A
///         On entry, the general matrix \f$A\f$.
///         On exit, the Schur matrix \f$S\f$.
///
/// @param[in] ldA
///         The leading dimension of \f$A\f$.
///
/// @param[in,out] Q
///         On entry, the orthogonal matrix \f$Q\f$.
///         On exit, the product matrix \f$Q * U\f$.
///
/// @param[in] ldQ
///         The leading dimension of \f$Q\f$.
///
/// @param[out] real
///         An array of the same size as \f$A\f$ containing the real parts of
///         the computed eigenvalues.
///
/// @param[out] imag
///         An array of the same size as \f$A\f$ containing the imaginary parts
///         of the computed eigenvalues.
///
/// @param[in] predicate
///         A function that takes a (complex) eigenvalue as input and returns
///         non-zero if it should be selected. For complex conjugate pairs of
///         eigenvalues, the predicate is called only for the eigenvalue with
///         positive imaginary part and the corresponding \f$2 \times 2\f$ block
///         is either selected or deselected. The reordering step is skipped if
///         the argument is a NULL pointer.
///
/// @param[in] arg
///         An optional argument for the predicate function.
///
/// @param[out] selected
///         The final positions of all correctly placed selected eigenvalues.
///
/// @param[out] num_selected
///         The number of selected eigenvalues (a complex conjugate pair is
///         counted as two selected eigenvalues).
///
/// @return @ref STARNEIG_SUCCESS (0) on success. Negative integer -i when i'th
/// argument is invalid. Positive error code otherwise.
/// @ref STARNEIG_DID_NOT_CONVERGE if the QR algorithm failed to converge.
/// @ref STARNEIG_PARTIAL_REORDERING if the Schur form is not fully reordered.
///
starneig_error_t starneig_SEP_SM_Reduce(
    int n,
    double A[], int ldA,
    double Q[], int ldQ,
    double real[], double imag[],
    int (*predicate)(double real, double imag, void *arg),
    void *arg,
    int selected[],
    int *num_selected);

///
/// @brief Computes an eigenvector for each selected eigenvalue.
///
/// @param[in] n
///         The order of \f$S\f$ and \f$Q\f$ and the number of rows of \f$X\f$.
///
/// @param[in] selected
///         The selection array specifying the locations of the selected
///         eigenvalues. The number of 1's in the array is the same as the
///         number of columns in \f$X\f$.
///
/// @param[in] S
///         The Schur matrix \f$S\f$.
///
/// @param[in] ldS
///         The leading dimension of \f$S\f$.
///
/// @param[in] Q
///         The orthogonal matrix \f$Q\f$.
///
/// @param[in] ldQ The
///         The leading dimension of \f$Q\f$.
///
/// @param[out] X
///         A matrix with \f$n\f$ rows and one column for each selected
///         eigenvalue. The columns represent the computed eigenvectors as
///         previously described.
///
/// @param[in] ldX
///         The leading dimension of \f$X\f$.
///
/// @return @ref STARNEIG_SUCCESS (0) on success. Negative integer -i when i'th
/// argument is invalid. Positive error code otherwise.
///
/// @see starneig_SEP_SM_Select
///
starneig_error_t starneig_SEP_SM_Eigenvectors(
    int n,
    int selected[],
    double S[], int ldS,
    double Q[], int ldQ,
    double X[], int ldX);

///
/// @}
///

///
/// @name Helper functions
/// @{

///
/// @brief Generates a selection array for a Schur matrix using a user-supplied
/// predicate function.
///
/// @param[in] n
///         The order of \f$S\f$.
///
/// @param[in] S
///         The Schur matrix \f$S\f$.
///
/// @param[in] ldS
///         The leading dimension of \f$S\f$.
///
/// @param[in] predicate
///         A function that takes a (complex) eigenvalue as input and returns
///         non-zero if it should be selected. For complex conjugate pairs of
///         eigenvalues, the predicate is called only for the eigenvalue with
///         positive imaginary part and the corresponding \f$2 \times 2\f$ block
///         is either selected or deselected.
///
/// @param[in] arg
///         An optional argument for the predicate function.
///
/// @param[out] selected
///         The selection array. Both elements of a selected complex conjugate
///         pair are set to 1.
///
/// @param[out] num_selected
///         The number of selected eigenvalues (a complex conjugate pair is
///         counted as two selected eigenvalues).
///
/// @return @ref STARNEIG_SUCCESS (0) on success. Negative integer -i when i'th
/// argument is invalid. Positive error code otherwise.
///
starneig_error_t starneig_SEP_SM_Select(
    int n,
    double S[], int ldS,
    int (*predicate)(double real, double imag, void *arg),
    void *arg,
    int selected[],
    int *num_selected);

///
/// @}
///

///
/// @name Expert computational functions
/// @{
///

///
/// @brief Computes a Hessenberg decomposition of a general matrix.
///
/// @param[in] conf
///         Configuration structure.
///
/// @param[in] n
///         The order of \f$A\f$ and \f$Q\f$.
///
/// @param[in] begin
///         First column to be reduced.
///
/// @param[in] end
///         Last column to be reduced.
///
/// @param[in,out] A
///         On entry, the general matrix \f$A\f$.
///         On exit, the upper Hessenberg matrix \f$H\f$.
///
/// @param[in] ldA
///         The leading dimension of \f$A\f$.
///
/// @param[in,out] Q
///         On entry, the orthogonal matrix \f$Q\f$.
///         On exit, the product matrix \f$Q * U\f$.
///
/// @param[in] ldQ
///         The leading dimension of \f$Q\f$.
///
/// @return @ref STARNEIG_SUCCESS (0) on success. Negative integer -i when i'th
/// argument is invalid. Positive error code otherwise.
///
/// @see starneig_SEP_SM_Hessenberg
/// @see starneig_hessenberg_conf
/// @see starneig_hessenberg_init_conf
///
starneig_error_t starneig_SEP_SM_Hessenberg_expert(
    struct starneig_hessenberg_conf *conf,
    int n, int begin, int end,
    double A[], int ldA,
    double Q[], int ldQ);

///
/// @brief Computes a Schur decomposition given a Hessenberg decomposition.
///
/// @param[in] conf
///         Configuration structure.
///
/// @param[in] n
///         The order of \f$H\f$ and \f$Q\f$.
///
/// @param[in,out] H
///         On entry, the upper Hessenberg matrix \f$H\f$.
///         On exit, the Schur matrix \f$S\f$.
///
/// @param[in] ldH
///         The leading dimension of \f$H\f$.
///
/// @param[in,out] Q
///         On entry, the orthogonal matrix \f$Q\f$.
///         On exit, the product matrix \f$Q * U\f$.
///
/// @param[in] ldQ
///         The leading dimension of \f$Q\f$.
///
/// @param[out] real
///         An array of the same size as \f$H\f$ containing the real parts of
///         the computed eigenvalues.
///
/// @param[out] imag
///         An array of the same size as \f$H\f$ containing the imaginary parts
///         of the computed eigenvalues.
///
/// @return @ref STARNEIG_SUCCESS (0) on success. Negative integer -i when i'th
/// argument is invalid. Positive error code otherwise.
///
/// @see starneig_SEP_SM_Schur
/// @see starneig_schur_conf
/// @see starneig_schur_init_conf
///
starneig_error_t starneig_SEP_SM_Schur_expert(
    struct starneig_schur_conf *conf,
    int n,
    double H[], int ldH,
    double Q[], int ldQ,
    double real[], double imag[]);

///
/// @brief Reorders selected eigenvalues to the top left corner of a Schur
/// decomposition.
///
/// @param[in] conf
///         Configuration structure.
///
/// @param[in] n
///         The order of \f$S\f$ and \f$Q\f$.
///
/// @param[in,out] selected
///         The selection array.
///
/// @param[in,out] S
///         On entry, the Schur matrix \f$S\f$.
///         On exit, the updated Schur matrix \f$\hat{S}\f$.
///
/// @param[in] ldS
///         The leading dimension of \f$S\f$.
///
/// @param[in,out] Q
///         On entry, the orthogonal matrix \f$Q\f$.
///         On exit, the product matrix \f$Q * U\f$.
///
/// @param[in] ldQ
///         The leading dimension of \f$Q\f$.
///
/// @param[out] real
///         An array of the same size as \f$S\f$ containing the real parts of
///         the computed eigenvalues.
///
/// @param[out] imag
///         An array of the same size as \f$S\f$ containing the imaginary parts
///         of the computed eigenvalues.
///
/// @return @ref STARNEIG_SUCCESS (0) on success. Negative integer -i when i'th
/// argument is invalid. Positive error code otherwise.
///
/// @see starneig_SEP_SM_ReorderSchur
/// @see starneig_SEP_SM_Select
/// @see starneig_reorder_conf
/// @see starneig_reorder_init_conf
///
starneig_error_t starneig_SEP_SM_ReorderSchur_expert(
    struct starneig_reorder_conf *conf,
    int n,
    int selected[],
    double S[], int ldS,
    double Q[], int ldQ,
    double real[], double imag[]);

///
/// @brief Computes an eigenvector for each selected eigenvalue.
///
/// @param[in] conf
///         Configuration structure.
///
/// @param[in] n
///         The order of \f$S\f$ and \f$Q\f$ and the number of rows of \f$X\f$.
///
/// @param[in] selected
///         The selection array specifying the locations of the selected
///         eigenvalues. The number of 1's in the array is the same as the
///         number of columns in \f$X\f$.
///
/// @param[in] S
///         The Schur matrix \f$S\f$.
///
/// @param[in] ldS
///         The leading dimension of \f$S\f$.
///
/// @param[in] Q
///         The orthogonal matrix \f$Q\f$.
///
/// @param[in] ldQ The
///         The leading dimension of \f$Q\f$.
///
/// @param[out] X
///         A matrix with \f$n\f$ rows and one column for each selected
///         eigenvalue. The columns represent the computed eigenvectors as
///         previously described.
///
/// @param[in] ldX
///         The leading dimension of \f$X\f$.
///
/// @return @ref STARNEIG_SUCCESS (0) on success. Negative integer -i when i'th
/// argument is invalid. Positive error code otherwise.
///
/// @see starneig_SEP_SM_Select
///
starneig_error_t starneig_SEP_SM_Eigenvectors_expert(
    struct starneig_eigenvectors_conf *conf,
    int n,
    int selected[],
    double S[], int ldS,
    double Q[], int ldQ,
    double X[], int ldX);

///
/// @}
///

///
/// @}
///

#ifdef __cplusplus
}
#endif

#endif // STARNEIG_SEP_SM_H
