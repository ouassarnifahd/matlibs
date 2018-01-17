#ifndef FRACTION_H
#define FRACTION_H

#include "polynome.h"

typedef struct fraction *fraction_t;

#define SIZE_FRACTION sizeof(struct fraction)

root_t fraction_racines(const fraction_t fraction);

void fraction_print(const fraction_t fraction);

#endif /* end of include guard: FRACTION_H */
