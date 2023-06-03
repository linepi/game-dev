#include <defs.h>
#include <debug.h>
#include <cJSON/cJSON.h>

struct config game_config = {};
const char *mouse_ttf_path = "./assets/mouse.ttf";
const char *menu_ttf_path = mouse_ttf_path;
const char *text_ttf_path = mouse_ttf_path;

error_t config_init() {
	FILE *config_fp = fopen("config.json", "r");
	if (!config_fp) return FILE_OPEN_ERROR;
	// get config file string
	char config[1000];
	int config_str_size = fread(config, 1, 1000, config_fp);
	config[config_str_size] = '\0';
	
	cJSON *config_json = cJSON_Parse(config);
	cJSON *window_w = cJSON_GetObjectItemCaseSensitive(config_json, "window_w");
	cJSON *window_h = cJSON_GetObjectItemCaseSensitive(config_json, "window_h");
	cJSON *fps = cJSON_GetObjectItemCaseSensitive(config_json, "fps");
	cJSON *debug = cJSON_GetObjectItemCaseSensitive(config_json, "debug");
	game_config.window_w = cJSON_GetNumberValue(window_w);
	game_config.window_h = cJSON_GetNumberValue(window_h);
	game_config.fps = cJSON_GetNumberValue(fps); 
	game_config.debug = cJSON_GetNumberValue(fps); 
	return NO_ERROR;
}