/*
 * wlite: A 16-bit Unicode based tiny <wchar.h> library with CJK features
 * Copyright (C) 2022 Eido INOUE
 * 
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Lesser Public License for more
 * details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdbool.h>
#include <errno.h>          // errno, EILSEQ, ERANGE / FIXME: freestanding
#include <locale.h>         // FIXME: freestanding

#include "wlite_config.h"   // wchar_t, NULL, size_t

#include "wlite_wchar.h"    // prototypes
#include "wlite_wctype.h"
#include "wlite_stdlib.h"

double
wlite_wcstod(const wchar_t *str, wchar_t **endptr) {
    double result = 0.0;
    wchar_t signedResult = L'\0';
    wchar_t signedExponent = L'\0';
    int decimals = 0;
    bool isExponent = false;
    bool hasExponent = false;
    bool hasResult = false;
    // exponent is logically int but is coded as double so that its eventual
    // overflow detection can be the same as for double result
    double exponent = 0;
    wchar_t c;

    for (; L'\0' != (c = *str); ++str) {
        if ((c >= L'0') && (c <= L'9')) {
            int digit = c - L'0';
            if (isExponent) {
                exponent = (10 * exponent) + digit;
                hasExponent = true;
            }
            else if (decimals == 0) {
                result = (10 * result) + digit;
                hasResult = true;
            }
            else {
                result += (double) digit / decimals;
                decimals *= 10;
            }
            continue;
        }
        if (c == L'.') {
            if (!hasResult) {
                // don't allow leading '.'
                break;
            }
            if (isExponent) {
                // don't allow decimal places in exponent
                break;
            }
            if (decimals != 0) {
                // this is the 2nd time we've found a '.'
                break;
            }
            decimals = 10;
            continue;
        }
        if ((c == L'-') || (c == L'+')) {
            if (isExponent) {
                if (signedExponent || (exponent != 0))
                    break;
                else
                    signedExponent = c;
            }
            else {
                if (signedResult || (result != 0))
                    break;
                else
                    signedResult = c;
            }
            continue;
        }
        if (c == L'E') {
            if (!hasResult) {
                // don't allow leading 'E'
                break;
            }
            if (isExponent)
                break;
            else
                isExponent = true;
            continue;
        }
        // else unexpected character
        break;
    }
    if (isExponent && !hasExponent) {
        while (*str != L'E')
            --str;
    }
    if (!hasResult && signedResult)
        --str;

    if (endptr)
        *endptr = (wchar_t *) str;
    for (; exponent != 0; --exponent) {
        if (signedExponent == L'-')
            result /= 10;
        else
            result *= 10;
    }
    if (signedResult == L'-') {
        if (result != 0)
            result = -result;
        // else I'm not used to working with double-precision numbers so I
        // was surprised to find my assert for "-0" failing, saying -0 != +0.
    }
    return result;
}
