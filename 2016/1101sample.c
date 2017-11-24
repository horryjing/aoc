#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define FLOORS_NUM 4
#define ELEMENTS_NUM 4
#define OK 0
#define DEAD 1
#define ELEMENT_TYPE 2
#define H_TYPE 0
#define L_TYPE 1
#define MAP_SIZE FLOORS_NUM*ELEMENTS_NUM*3
#define UP 1
#define DOWN -1

typedef struct node_t {
	int cost;
	int elevator;
	int status; /*0: OK, 1: DEAD*/
	char map[FLOORS_NUM][ELEMENTS_NUM][3];
	struct node_t *parent;
	struct node_t *brother;
}node;

void print_map(node *p);
void init_head();
node *move(node *p);
node *check_valid(node *p);
node *add_node(node *parent, char map[FLOORS_NUM][ELEMENTS_NUM][3], int updown);

int min_cost = 12;
node *head = NULL;

int main()
{
	node *p = NULL;
    node *ret = 0;

	init_head();
	//print_map(head);

	p = head;
	ret = move(p);

	return 0;
}

void print_map(node *p)
{
	int elevator = p->elevator;
	int i = 0;
	int j = 0;
	char map[FLOORS_NUM][ELEMENTS_NUM][3];
	memcpy(map, p->map, MAP_SIZE);
    static int try = 0;

	for (i = FLOORS_NUM - 1; i >= 0; i--)
	{
		printf("F%d ", i + 1);
		if (elevator != i) 
		{
			printf(". ");
		}
		else
		{
			printf("E ");
		}
        printf("| ");
		for (j = 0; j < ELEMENTS_NUM; j++)
		{
			printf("%s ", map[i][j]);
		}
		printf("\n");
	}

	printf("%s %d %d\n", p->status ? "DEAD" : "OK", p->cost, try++);
}

node *add_node(node *parent, 
				char map[FLOORS_NUM][ELEMENTS_NUM][3],
				int updown)
{
	node *p = NULL;

	p = (node *)malloc(sizeof(node));
	memset(p, 0, sizeof(node));
	memcpy(p->map, map, MAP_SIZE);
	p->cost = parent->cost + 1;
	p->elevator = parent->elevator + updown;
	p->status = OK;
	p->parent = parent;
	p->brother = NULL;

	return p;
}

void init_head()
{
	node *p = NULL;

	char map[FLOORS_NUM][ELEMENTS_NUM][3] = {
		". ", "HM", ". ", "LM",
		"HG", ". ", ". ", ". ",
		". ", ". ", "LG", ". ",
		". ", ". ", ". ", ". ",
	};

	p = (node *)malloc(sizeof(node));
	memset(p, 0, sizeof(node));
	memcpy(p->map, map, MAP_SIZE);
	p->cost = 0;
	p->elevator = 0;
	p->status = OK;
	p->parent = NULL;
	p->brother = NULL;
	head = p;
}

node  *move(node *parent)
{
	int i = 0;
    int j = 0;
	int f = parent->elevator;
	int updown = UP;
	char map[FLOORS_NUM][ELEMENTS_NUM][3];
	memcpy(map, parent->map, MAP_SIZE);
	node *p = NULL;
    node *ret = NULL;

	if (parent->status == DEAD)
	{
        free(parent);
		return 0;
	}

	/*1st floor, only go up*/
    if (f == 0)
    {
	    updown = UP;
    }
    /*top floor, only go down*/
    else if (f == FLOORS_NUM-1)
    {
        updown = DOWN;
    }
    /*middle floor, first go up, later go down*/
    else
    {
        updown = UP;
    }
START_MOV:
	for (i = 0; i<ELEMENTS_NUM; i++)
	{
        memcpy(map, parent->map, MAP_SIZE);
        if (map[f][i][0] == '.')
        {
            continue;
        }
        for (j=i; j<ELEMENTS_NUM; j++)
        {
            memcpy(map, parent->map, MAP_SIZE);
		    if (map[f][j][0] == '.')
	    	{
			    continue;
		    }
		    strcpy(map[f + updown][i], map[f][i]);
            strcpy(map[f + updown][j], map[f][j]);
		    strcpy(map[f][i], ". ");
            strcpy(map[f][j], ". ");
		    p = add_node(parent, map, updown);
		    if ((ret = check_valid(p)) != 0)
            { 
                free(p);
                return ret;
            }
            if (p->status == DEAD)
            {
                free(p);
                continue;
            }
            if ((ret = move(p)) != 0)
            {
              return ret;
            }
        }
	}
    /*if middle floor, now go down*/
    if ((f > 0) && (f < FLOORS_NUM-1)
        && (updown == UP))
    {
        updown = DOWN;
        goto START_MOV;
    }

    parent->status = DEAD;
    free(parent);
    sleep(1);

    return 0;
}

node * check_valid(node *p)
{
#if 0
    int i = 0;
    int f = p->elevator;
    int j = 0;
    print_map(p);
    if (p->elevator == FLOORS_NUM-1)
    {
        for (j=0; j<ELEMENTS_NUM; j++)
        {
            if (p->map[f][j][0] == '.')
            {
                break;
            }
        }
        if (j == ELEMENTS_NUM)
        {
            printf("************finish************\n");
            return 0;
        }
    }
    printf("OK(0) or DEAD(1): ");
    scanf("%d", &i);
    p->status = i;
    return 0;
#endif
	int i = 0;
	int j = 0;
    int k = 0;
    int f = p->elevator;
	int exist_gen = 0;
	int exist_chip = 0;
	int pair_gen[ELEMENT_TYPE] = { 0 };
	int pair_chip[ELEMENT_TYPE] = { 0 };
	char map[FLOORS_NUM][ELEMENTS_NUM][3];
	memcpy(map, p->map, MAP_SIZE);
    node *tmp = NULL;

    if (p->cost < 4)
    {
        print_map(p);
    }
    printf("%d\n", p->cost);
	if (p->status == DEAD)
	{
		return 0;
	}

    if (p->cost >= min_cost)
    {
        p->status = DEAD;
        return 0;
    }

	p->status = OK;

	for (i = 0; i < FLOORS_NUM; i++)
	{
		exist_gen = 0;
		exist_chip = 0;
		memset(pair_gen, 0, sizeof(pair_gen));
		memset(pair_chip, 0, sizeof(pair_chip));

		for (j = 0; j < ELEMENTS_NUM; j++)
		{
			// ignore "."
			if (map[i][j][0] == '.')
			{
				continue;
			}
			// check gen
			if (map[i][j][1] == 'G')
			{
				exist_gen = 1;
				if (map[i][j][0] == 'H')
				{
					pair_gen[H_TYPE] = 1;
				}
				else if (map[i][j][0] == 'L')
				{
					pair_gen[L_TYPE] = 1;
				}
				else
				{
					printf("error1\n");
				}
			}
			// check chip
			else if (map[i][j][1] == 'M')
			{
				exist_chip = 1;
				if (map[i][j][0] == 'H')
				{
					pair_chip[H_TYPE] = 1;
				}
				else if (map[i][j][0] == 'L')
				{
					pair_chip[L_TYPE] = 1;
				}
				else
				{
					printf("error3\n");
				}
			}
			else
			{
				printf("error2\n");
			}
		}
		//check pair
		if ((exist_gen == 0)
			|| (exist_chip == 0))
		{
			continue;
		}
		for (k = 0; k < ELEMENT_TYPE; k++)
		{
			if ((pair_chip[k] != 0)
				&& (pair_gen[k] != pair_chip[k]))
			{
				// chip is not pair with gen, dead step
				p->status = DEAD;
                //print_map(p);
                return 0;
			}
		}
	}

    //check same as parent or not
    tmp = p->parent;
    while (tmp!=NULL)
    {
        if (memcmp(p->map, tmp->map, MAP_SIZE) == 0)
        {
            break;
        }
        tmp = tmp->parent;
    }
    if (tmp != NULL)
    {
        p->status = DEAD;
        //print_map(p);
        return 0;
    }

    //check finish
    if (p->elevator == FLOORS_NUM-1)
    {
        for (j=0; j<ELEMENTS_NUM; j++)
        {
            if (p->map[f][j][0] == '.')
            {
                break;
            }
        }
        if (j == ELEMENTS_NUM)
        {
            printf("************finish************\n");
            if (p->cost < min_cost)
            {
                min_cost = p->cost;
            }
            p->status = DEAD;
            print_map(p);
            return 0;
        }
    }
	//print_map(p);
	return 0;
}
