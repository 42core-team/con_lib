#include "parse_json.h"

static void apply_obj_to_arr(t_obj obj, t_obj ***arr)
{
	bool objInserted = false;

	printf("a\n"); fflush(stdout);

	for (size_t i = 0; (*arr)[i] != NULL; i++)
		if ((*arr)[i]->state == STATE_ALIVE)
			(*arr)[i]->state = STATE_DEAD;

	printf("b\n"); fflush(stdout);

	// 1. LOOP: Id Matching
	size_t index = 0;
	while ((*arr)[index] != NULL)
	{
		if ((*arr)[index]->id == obj.id)
		{
			*((*arr)[index]) = obj;
			objInserted = true;
			break;
		}
		index++;
	}
	if (objInserted)
		return ;

	printf("c\n"); fflush(stdout);

	// 2. LOOP: Placeholder matching
	index = 0;
	while ((*arr)[index] != NULL)
	{
		if ((*arr)[index]->id == 0)
		{
			*((*arr)[index]) = obj;
			objInserted = true;
			break;
		}
		index++;
	}
	if (objInserted)
		return ;

	printf("d\n"); fflush(stdout);

	// 3. Add to the back
	size_t arrLen = 0;
	while ((*arr)[arrLen] != NULL)
		arrLen++;
	(*arr) = realloc((*arr), sizeof(t_obj *) * (arrLen + 2));
	(*arr)[arrLen + 1] = NULL;
	(*arr)[arrLen] = malloc(sizeof(t_obj));
	*((*arr)[arrLen]) = obj;
	(*arr)[arrLen]->state = STATE_ALIVE;

	printf("e\n"); fflush(stdout);
}

void ft_parse_cores(int token_ind, int token_len, jsmntok_t *tokens, char *json)
{
	int	index = 0;

	token_ind = ft_find_token_one("cores", token_ind, token_len, tokens, json);
	if (token_ind == -1)
		return ;
	int cores_count = tokens[token_ind].size;

	if (game.cores == NULL)
	{
		game.cores = malloc(sizeof(t_obj *) * 1);
		game.cores[0] = NULL;
	}

	token_ind++;
	while (index < cores_count && token_ind < token_len)
	{
		if (tokens[token_ind].type != JSMN_OBJECT)
		{
			token_ind++;
			continue;
		}

		t_obj readCore;
		readCore.type = OBJ_CORE;
		readCore.state = STATE_ALIVE;
		readCore.id = ft_find_parse_ulong("id", &token_ind, token_len, tokens, json);
		readCore.s_core.team_id = ft_find_parse_ulong("team_id", &token_ind, token_len, tokens, json);
		int pos_token_ind = ft_find_token_one("pos", token_ind, token_len, tokens, json);
		if (pos_token_ind != -1)
		{
			readCore.x = ft_find_parse_ulong("x", &pos_token_ind, token_len, tokens, json);
			readCore.y = ft_find_parse_ulong("y", &pos_token_ind, token_len, tokens, json);
		}
		readCore.hp = ft_find_parse_ulong("hp", &token_ind, token_len, tokens, json);

		apply_obj_to_arr(readCore, &game.cores);

		index++;
	}
}

void	ft_parse_resources(int token_ind, int token_len, jsmntok_t *tokens, char *json)
{
	int	index = 0;

	token_ind = ft_find_token_one("resources", token_ind, token_len, tokens, json);
	if (token_ind == -1)
		return ;
	int resource_count = tokens[token_ind].size;

	if (game.resources == NULL)
	{
		game.resources = malloc(sizeof(t_obj *) * 1);
		game.resources[0] = NULL;
	}

	token_ind++;
	while (index < resource_count && token_ind < token_len)
	{
		if (tokens[token_ind].type != JSMN_OBJECT)
		{
			token_ind++;
			continue;
		}

		t_obj readResource;
		readResource.type = OBJ_RESOURCE;
		readResource.state = STATE_ALIVE;
		readResource.id = ft_find_parse_ulong("id", &token_ind, token_len, tokens, json);
		int pos_token_ind = ft_find_token_one("pos", token_ind, token_len, tokens, json);
		if (pos_token_ind != -1)
		{
			readResource.x = ft_find_parse_ulong("x", &pos_token_ind, token_len, tokens, json);
			readResource.y = ft_find_parse_ulong("y", &pos_token_ind, token_len, tokens, json);
		}
		readResource.hp = ft_find_parse_ulong("hp", &token_ind, token_len, tokens, json);

		apply_obj_to_arr(readResource, &game.resources);

		index++;
	}
}

void	ft_parse_units(int token_ind, int token_len, jsmntok_t *tokens, char *json)
{
	int	index = 0;

	printf("1\n"); fflush(stdout);

	token_ind = ft_find_token_one("units", token_ind, token_len, tokens, json);
	if (token_ind == -1)
		return ;
	int unit_count = tokens[token_ind].size;

	printf("2\n"); fflush(stdout);

	if (game.units == NULL)
	{
		game.units = malloc(sizeof(t_obj *) * 1);
		game.units[0] = NULL;
	}

	printf("3\n"); fflush(stdout);

	token_ind++;
	while (index < unit_count && token_ind < token_len)
	{
		printf("3.5\n"); fflush(stdout);

		if (!tokens)
			return ;
		if (tokens[token_ind].type != JSMN_OBJECT)
		{
			token_ind++;
			continue;
		}

		printf("4\n"); fflush(stdout);

		t_obj readUnit;
		readUnit.type = OBJ_UNIT;
		readUnit.state = STATE_ALIVE;
		readUnit.id = ft_find_parse_ulong("id", &token_ind, token_len, tokens, json);
		readUnit.s_unit.team_id = ft_find_parse_ulong("team_id", &token_ind, token_len, tokens, json);
		readUnit.s_unit.type_id = ft_find_parse_ulong("type_id", &token_ind, token_len, tokens, json);
		int pos_token_ind = ft_find_token_one("pos", token_ind, token_len, tokens, json);
		if (pos_token_ind != -1)
		{
			int temp_pos = pos_token_ind;
			readUnit.x = ft_find_parse_ulong("x", &temp_pos, token_len, tokens, json);
			readUnit.y = ft_find_parse_ulong("y", &temp_pos, token_len, tokens, json);
		}
		readUnit.hp = ft_find_parse_ulong("hp", &token_ind, token_len, tokens, json);

		printf("5\n"); fflush(stdout);

		apply_obj_to_arr(readUnit, &game.units);

		printf("6\n"); fflush(stdout);

		index++;
	}
}

#define TEAM_COUNT 2
void ft_parse_teams(int token_ind, int token_len, jsmntok_t *tokens, char *json)
{
	int		last_json_index, next_token_ind;

	token_ind = ft_find_token_one("teams", token_ind, token_len, tokens, json);
	if (token_ind == -1)
		return ;
	last_json_index = tokens[token_ind].end;

	if (game.teams == NULL)
	{
		game.teams = malloc(sizeof(t_team *) * (TEAM_COUNT + 1));
		game.teams[TEAM_COUNT] = NULL;

		for (size_t i = 0; i < TEAM_COUNT; i++)
		{
			game.teams[i] = malloc(sizeof(t_team));
			game.teams[i]->id = 0;
			game.teams[i]->balance = 0;
		}
	}

	int index = 0;
	while (token_ind != -1)
	{
		next_token_ind = ft_find_token_one("id", token_ind, token_len, tokens, json);
		if (next_token_ind == -1 || tokens[next_token_ind].end > last_json_index)
			break;

		game.teams[index]->id = ft_find_parse_ulong("id", &token_ind, token_len, tokens, json);
		game.teams[index]->balance = ft_find_parse_ulong("balance", &token_ind, token_len, tokens, json);

		index++;
	}
}
