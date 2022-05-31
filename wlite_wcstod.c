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

#include <errno.h>          // errno, EILSEQ, ERANGE / FIXME: freestanding
#include <locale.h>         // FIXME: freestanding
#include <float.h>
#include <limits.h>         // INT_MIN, ULONG_MAX, LONG_MIN

#include "wlite_config.h"   // wchar_t, NULL, size_t

#include "wlite_wchar.h"    // prototypes
#include "wlite_wctype.h"
#include "wlite_stdlib.h"

#include "wlite_xmath.h"

#define  SIG_MAX    32

double
wlite_wcstod(const wchar_t *s, wchar_t **endptr) {
    /* convert string to double, with checking */

    const wchar_t point = localeconv()->decimal_point[0];
    const wchar_t *sc;
    wchar_t buf[SIG_MAX], sign;
    double x;
    int ndigit, nsig, nzero, olead, opoint;

    for (sc = s; isspace(*sc); ++sc)
        ;
    sign = *sc == '-' || *sc == '+' ? *sc++ : '+';
    olead = -1, opoint = -1;
    for (ndigit = 0, nsig = 0, nzero = 0; ; ++sc)
        if (*sc == point)
            if (0 <= opoint)
                break;              /* already seen point */
            else
                opoint = ndigit;
        else if (*sc == '0')
            ++nzero, ++ndigit;
        else if (!isdigit(*sc))
            break;
        else {                      /* got a nonzero digit */
            if (olead < 0)
                olead = nzero, nzero = 0;
            else                    /* deliver zeros */
                for (; 0 < nzero && nsig < SIG_MAX; --nzero)
                    buf[nsig++] = 0;
            ++ndigit;
            if (nsig < SIG_MAX)     /* deliver digit */
                buf[nsig++] = *sc - '0';
        }
    if (ndigit == 0) {              /* set endptr */
        if (endptr)
            *endptr = (wchar_t *) s;
        return 0.0;
    }
    for (; 0 < nsig && buf[nsig - 1] == 0; --nsig)
        ;                           /* skip trailing digits */
}
