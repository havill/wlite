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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wlite_wchar.h"
#include "wlite_stdlib.h"

#define test(expr) check((expr),__FILE__,__LINE__,#expr)

void check(int expr, const char *file, unsigned line, const char *s) {
    const char *ok = "PASS (%s:%u) ** %d == %s\n";
    const char *ng = "FAIL (%s:%u) ** %d == %s\n";

    if (fprintf(stderr, (expr ? ok : ng), file, line, expr, s) < 0) abort();
    if (!expr) exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    wchar_t *s, wcs[10];
    char mbs[10];

    test(1 <= MB_CUR_MAX && MB_CUR_MAX <= MB_LEN_MAX);

    // test(wcstod(L"28G", &s) == 28.0 && s != NULL && *s == L'G');

    test(wcstol(L"-a0", &s, 11) == -110 && s != NULL && *s == L'\0');
    test(wcstoul(L"54", &s, 4) == 0 && s != NULL && *s == L'5');
    test(wcstoul(L"0xFfg", &s, 16) == 255 && s != NULL && *s == L'g');

/*
    assert("0", 0, "");
    assert("12", 12, "");
    assert("23.5", 23.5, "");
    assert("-14", -14, "");
    assert("-", 0, "-");
    assert("-2-a", -2, "-a");
    assert("-2a", -2, "a");
    assert("0.036", 0.036, "");
    assert("12.5E2", 12.5E2, "");
    assert("12.5E-3", 12.5E-3, "");
    assert("12.5E0", 12.5E0, "");
    assert("12.5E", 12.5, "E");
    assert("12.5E-", 12.5, "E-");
    assert("", 0, "");
    assert("a", 0, "a");
    assert("E10", 0, "E10");
    assert("-E10", 0, "-E10");
    assert("-0E10", 0, "");
    assert(".3", 0, ".3");
    assert("-.3", 0, "-.3");
    strtod("42C", 0); // tests endptr == null
    assert("+12", 12, "");
    assert("+-12", 0, "+-12");
    assert("12.5E+3", 12.5E+3, "");
    assert("12.5E+-3", 12.5, "E+-3");

assert("12.", 12., "");
double pz = 0.0;
double nz = -0.0;
assert(memcmp(&test_result, &pz, sizeof pz) == 0); // test if canonically the same as +0.0
assert(memcmp(&test_result, &nz, sizeof nz) == 0); // test if canonically the same as -0.0
    */

    test(mbstowcs(wcs, "abc", 4) == 3 && wcs[1] == L'b');
    test(wcstombs(mbs, wcs, 10) == 3 && strcmp(mbs, "abc") == 0);

    mblen(NULL, 0);
    wctomb(NULL, 0);

    test(mblen("abc", 4) == 1);
    test(mbtowc(&wcs[0], "abc", 4) == 1 && wcs[0] == L'a');
    test(wctomb(mbs, wcs[0]) == 1 && mbs[0] == L'a');
    test(mblen("", 1) == 0);
    test(mbtowc(&wcs[0], "", 1) == 0 && wcs[0] == 0);
    test(wctomb(mbs, wcs[0]) == 1 && mbs[0] == '\0');

    printf("MB_CUR_MAX = %u\n", (unsigned) MB_CUR_MAX);
    puts(mbtowc(NULL, NULL, 0) ? "mbs shift states" : "mbs stateless");

    return 0;
}
