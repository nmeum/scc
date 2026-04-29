#include <assert.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>

/*
output:
testing
done
end:
*/

int
main(void)
{
	struct lconv *lconv;
	int ret;

	puts("testing");
	lconv = localeconv();
	assert(lconv && strcmp(lconv->decimal_point, ".") == 0);
	assert(lconv && *lconv->thousands_sep == '\0');
	assert(lconv && *lconv->grouping == '\0');
	assert(lconv && *lconv->mon_decimal_point == '\0');
	assert(lconv && *lconv->mon_thousands_sep == '\0');
	assert(lconv && *lconv->mon_grouping == '\0');
	assert(lconv && *lconv->positive_sign == '\0');
	assert(lconv && *lconv->negative_sign == '\0');
	assert(lconv && *lconv->currency_symbol == '\0');
	assert(lconv && *lconv->int_curr_symbol == '\0');
	assert(lconv && lconv->frac_digits == CHAR_MAX);
	assert(lconv && lconv->p_cs_precedes == CHAR_MAX);
	assert(lconv && lconv->n_cs_precedes == CHAR_MAX);
	assert(lconv && lconv->p_sep_by_space == CHAR_MAX);
	assert(lconv && lconv->n_sep_by_space == CHAR_MAX);
	assert(lconv && lconv->p_sign_posn == CHAR_MAX);
	assert(lconv && lconv->n_sign_posn == CHAR_MAX);
	assert(lconv && lconv->int_frac_digits == CHAR_MAX);
	assert(lconv && lconv->int_p_cs_precedes == CHAR_MAX);
	assert(lconv && lconv->int_n_cs_precedes == CHAR_MAX);
	assert(lconv && lconv->int_p_sep_by_space == CHAR_MAX);
	assert(lconv && lconv->int_n_sep_by_space == CHAR_MAX);
	assert(lconv && lconv->int_p_sign_posn == CHAR_MAX);
	assert(lconv && lconv->int_n_sign_posn == CHAR_MAX);
	puts("done");

	return 0;
}
