#ifndef PERMISSIONS_EDITOR_H_
#define PERMISSIONS_EDITOR_H_

#include "../../utils/utils.h"
#include <sys/types.h>

mode_t*
get_mode(mode_t mode);

void
add_mode(mode_t* mode, mode_t mask);

void
remove_mode(mode_t* mode, mode_t mask);

void
equal_mode(mode_t* mode, mode_t mask);

char*
permissions_editor_menu();

void
process_permissions(mode_t* mask,
                    const char* token,
                    CommandEntry* commands);

void
process_user_group(mode_t* mask, char* user_group_token);

void
process_type_permissions(mode_t* mask,
                         const char* type_permissions_token);

void
apply_mode_change(mode_t* mode, mode_t mask, char sign);

void
permissions_editor(mode_t* mode);

#endif // PERMISSIONS_EDITOR_H_
