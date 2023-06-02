#include <defs.h>
#include <debug.h>

struct config game_config = {};

error_t config_init() {
	FILE *config_fp = fopen("config.txt", "r");
	if (!config_fp) return FILE_OPEN_ERROR;
	char buf[256];
	while (fgets(buf, 256, config_fp) != 0) {
		buf[strlen(buf) - 1] = '\0'; // get rid of the end \n
		int equal_idx;
		for (int i = 0; buf[i]; i++) {
			if (buf[i] == '=') {
				equal_idx = i;
				break;
			}
		}
		char config_name[32];
		char config_val[128];
		strncpy(config_name, buf, equal_idx);	
		config_name[equal_idx] = '\0';
		strcpy(config_val, buf + equal_idx + 1);	
		if (strcmp(config_name, "window_w") == 0) {
			game_config.window_w = atoi(config_val);	
		} 
		else if (strcmp(config_name, "window_h") == 0) {
			game_config.window_h = atoi(config_val);	
		} 
		else if (strcmp(config_name, "fps") == 0) {
			game_config.fps = atoi(config_val);	
		}
		else if (strcmp(config_name, "debug") == 0) {
			game_config.debug = atoi(config_val);	
		}
		else {
			printf("do not have config %s\n", config_name);
		}
	}
	fclose(config_fp);
	return NO_ERROR;
}