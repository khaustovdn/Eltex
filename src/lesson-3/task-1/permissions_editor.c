#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "permissions_editor.h"

mode_t*
get_mode(mode_t mode)
{
  mode_t* mode_ptr = (mode_t*)malloc(sizeof(mode_t));
  *mode_ptr = mode;
  return mode_ptr;
}

void
add_mode(mode_t* mode, mode_t mask)
{
  *mode |= mask;
}

void
remove_mode(mode_t* mode, mode_t mask)
{
  *mode &= ~mask;
}

char*
permissions_editor_menu()
{
  output_wrapped_title("Permissions Editor Menu", 30, '-');

  fputs("Before using this command, learn how to apply "
        "\e]8;;https://www.opennet.ru/"
        "man.shtml?topic=chmod\e\\chmod\e]8;;\e\\\n"
        "Input: ",
        stdout);
  return input_string();
}

typedef void (*operation)(mode_t* mode, mode_t mask);

void
process_permissions(mode_t* mask,
                    const char* token,
                    CommandEntry* commands)
{
  for (int i = 0; token[i] != '\0'; i++) {
    for (int j = 0; commands[j].name != NULL; j++) {
      if (token[i] == commands[j].name[0]) {
        *mask |= *(mode_t*)commands[j].property;
      }
    }
  }
}

void
process_user_group(mode_t* mask, char* user_group_token)
{
  CommandEntry user_group_commands[] = {
    { "a", (mode_t*)get_mode(S_IRWXU | S_IRWXG | S_IRWXO) },
    { "u", (mode_t*)get_mode(S_IRWXU) },
    { "g", (mode_t*)get_mode(S_IRWXG) },
    { "o", (mode_t*)get_mode(S_IRWXO) },
    { NULL, NULL }
  };

  process_permissions(
    mask, user_group_token, user_group_commands);
}

void
process_type_permissions(mode_t* mask,
                         const char* type_permissions_token)
{
  CommandEntry type_permissions_commands[] = {
    { "r", (mode_t*)get_mode(S_IRUSR | S_IRGRP | S_IROTH) },
    { "w", (mode_t*)get_mode(S_IWUSR | S_IWGRP | S_IWOTH) },
    { "x", (mode_t*)get_mode(S_IXUSR | S_IXGRP | S_IXOTH) },
    { NULL, NULL }
  };

  process_permissions(mask,
                      type_permissions_token,
                      type_permissions_commands);
}

void
apply_mode_change(mode_t* mode, mode_t mask, char sign)
{
  CommandEntry commands[] = { { "+", add_mode },
                              { "-", remove_mode },
                              { NULL, NULL } };

  for (int k = 0; commands[k].name != NULL; k++)
    if (commands[k].name[0] == sign) {
      ((operation)commands[k].property)(mode, mask);
      break;
    }
}

void
permissions_editor(mode_t* mode)
{
  char* action_choice = permissions_editor_menu();
  if (strncmp(action_choice, "q", MAX_LEN) == 0) {
    free(action_choice);
    return;
  }

  char sign = '\0';
  if (strstr(action_choice, "+") != NULL) {
    sign = '+';
  } else if (strstr(action_choice, "-") != NULL) {
    sign = '-';
  } else
    return;

  mode_t user_group_mask = 0;
  mode_t type_permissions_mask = 0;

  char* user_group_token = strtok(action_choice, "+-");
  if (user_group_token != NULL) {
    process_user_group(&user_group_mask, user_group_token);
  }
  char* type_permissions_token = strtok(NULL, "+-");
  if (type_permissions_token != NULL) {
    process_type_permissions(&type_permissions_mask,
                             type_permissions_token);
  }

  apply_mode_change(
    mode, user_group_mask & type_permissions_mask, sign);

  free(action_choice);
}
