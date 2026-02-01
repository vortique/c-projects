#ifndef PERMS_H
#define PERMS_H

#include <stdint.h>
#include <stdbool.h>

#define BIT(n) (1u << (n))

#define READ_PERM BIT(0)
#define WRITE_PERM BIT(1)
#define EXEC_PERM BIT(2)

void perm_add(uint8_t *perms, uint8_t perm);
void perm_remove(uint8_t *perms, uint8_t perm);
int perm_has(uint8_t *perms, uint8_t perm);

#endif
