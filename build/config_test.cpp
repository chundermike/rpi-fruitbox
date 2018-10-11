#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define NUM_PARAMS  3
#define MAX_STR_LEN 256

typedef enum {
  FRUITBOX_CFG,
  ANY_SKIN_CFG,
  SINGLE_SKIN_CFG,
  ALBUM_SKIN_CFG
} param_group_t;

typedef struct {
  int x;
  int y;
} int2_t;

typedef struct config_param_t config_param_t;

struct config_param_t {
  param_group_t group;
  const char *section;
  const char *name;
  const char *defaults;
  int (*parse)(config_param_t *param);
  void *var;
};

int GetFont(config_param_t *param) {
  return 0;
}

int GetStr(config_param_t *param) {
  char *var = (char*)param->var;
  sscanf(param->defaults, "%s", var); 
  // printf("GetStr [%s]\n", param->defaults);
  return 0;
}

int Get2Ints(config_param_t *param) {
  int2_t *var = (int2_t*)param->var;
  sscanf(param->defaults, "%d %d", &var->x, &var->y); 
  printf("Get2Ints [%s]\n", param->defaults);
}

char x[MAX_STR_LEN];
char y[MAX_STR_LEN];
int2_t z={4,3};

config_param_t param[NUM_PARAMS] = {
  {FRUITBOX_CFG, "general", "database", "fruitbox.db", GetStr, (void*)&x},
  {FRUITBOX_CFG, "general", "music path", "\\mnt\\usb", GetStr, (void*)&y},
  {FRUITBOX_CFG, "general", "screen size", "1280 1024", Get2Ints, (void*)&z}
};

int main(void) {
  param[1].parse(&param[1]);  
  printf("z.x=%d, z.y=%d\n", z.x, z.y);
  param[2].parse(&param[2]);  
  printf("z.x=%d, z.y=%d\n", z.x, z.y);
  printf("y='%s'\n", y);
  return 0;
}
