#ifndef ENEMY_C
#define ENEMY_C

typedef struct enemy {
	int level;
	float def_reduce;
	float def_ignore;
	float physical_res;
	float pyro_res;
	float hydro_res;
	float electro_res;
	float cryo_res;
	float dendro_res;
	float anemo_res;
	float geo_res;
} Enemy;

#endif
