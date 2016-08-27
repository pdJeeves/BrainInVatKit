#ifndef _tract_h_
#define _tract_h_
#include "lobe.h"
extern "C" {
#include <stdlib.h>
#include <stdio.h>

struct TractData
{
	char origin_lobe[16];
	char data_source[16];
	char mirror[16];
	
	uint16_t origin_lobe_first, data_source_first;
	uint16_t origin_lobe_last,  data_source_last;
	
	uint8_t data_source_max_synapses;
	uint8_t origin_lobe_max_synapses;

	uint8_t flags;
	uint8_t threshold;

	uint8_t min_ltw, max_ltw;
	uint8_t min_str, max_str;
	
	uint8_t min_add;
	uint8_t max_add;
	uint8_t spread;
	
	uint8_t relax_suscept,
			relax_state,
			relax_stw,
			relax_ltw,

			relax_str;
	uint8_t gain,
			lose;
};

typedef enum {
	MIN_WEIGHT = 64,
	MID_WEIGHT = 64,
	MAX_WEIGHT = 128
} tract_weights;

struct TractCell
{
	struct LobeCell  * origin_lobe;
	struct LobeCell  * data_source;

	struct TractCell * input_tract;
	struct TractCell * output_tract;

	struct TractData data;

//synapse data, unused by flat tracts.
	uint8_t * strength;	
	int16_t * data_source_from_origin_lobe;
	
//generated data
	uint8_t  * data_source_loose;
	uint8_t  * origin_lobe_loose;
	int16_t * origin_lobe_from_data_source;

//used by all tracts
	uint8_t * stw;
	uint8_t * ltw;
	
//how long ago did we fire?
	uint8_t  * suscept;
//how long ago did we anticipate firing?
	uint8_t  * prev;

	uint8_t  * data_source_prev;
	int16_t * data_source_recent;

	uint16_t  * excitation;
	uint16_t * inhibition;

	uint32_t synapses;

	uint16_t segments;

	uint8_t		origin_lobe_width;
	uint8_t		origin_lobe_height;

	uint8_t     origin_lobe_depth;

	uint8_t		data_source_width;
	uint8_t		data_source_height;
	uint8_t     data_source_depth;
};

static inline
__attribute((always_inline))
__attribute((pure))
uint16_t data_source_range(const struct TractCell * tract)
{
	return tract->data.data_source_last - tract->data.data_source_first;
}

static inline
__attribute((always_inline))
__attribute((pure))
uint16_t origin_lobe_range(const struct TractCell * tract)
{
	return tract->data.origin_lobe_last - tract->data.origin_lobe_first;
}

static inline
__attribute((always_inline))
__attribute((pure))
uint16_t data_source_cells(const struct TractCell * tract)
{
	return data_source_range(tract) * tract->data_source_depth;
}

static inline
__attribute((always_inline))
__attribute((pure))
uint16_t origin_lobe_cells(const struct TractCell * tract)
{
	return origin_lobe_range(tract) * tract->origin_lobe_depth;
}

static inline
__attribute((always_inline))
__attribute((pure))
int data_source_dens(const struct TractCell * tract)
{
	return (int) data_source_cells(tract) * tract->data.data_source_max_synapses;
}

static inline
__attribute((always_inline))
__attribute((pure))
int origin_lobe_dens(const struct TractCell * tract)
{
	return (int) origin_lobe_cells(tract) * tract->data.origin_lobe_max_synapses;
}

int get_loose_dens(const struct TractCell * tract, uint16_t i);
void tract_cell_create(struct TractCell * tract, const struct TractData * gene);
void tract_cell_set_origin_lobe(struct TractCell * tract, struct LobeCell * cell);
void tract_cell_set_data_source(struct TractCell * tract, struct LobeCell * cell);
void tract_cell_set_temporal_lobe(struct TractCell * tract, struct LobeCell * cell);
int  tract_cell_can_mirror(const struct TractCell * tract, const struct TractCell * mirror);
void tract_cell_set_mirror(struct TractCell * tract, struct TractCell * mirror);
void tract_cell_clear(struct TractCell * tract);
void tract_cell_free(struct TractCell * tract);

void tract_cell_read_data(struct TractCell * tract, FILE * file);
void tract_cell_write_data(struct TractCell * tract, FILE * file);
void tract_cell_initialize(struct TractCell * tract);

void tract_cell_process_tick(struct TractCell * cell);
void tract_cell_advance_time(struct TractCell * cell, int tick);
void tract_cell_update_weights(struct TractCell * list, uint8_t reward, uint8_t punishment);

int32_t get_synapse_from_data_source(const struct TractCell * tract, uint32_t synapse);

int16_t origin_lobe_cell_from_data_source_synapse(const struct TractCell * tract, uint16_t cell, uint8_t synapse);
int16_t data_source_cell_from_origin_lobe_synapse(const struct TractCell * tract, uint16_t cell, uint8_t synapse);
int16_t flat_connect(uint16_t c,	 //cell that is connecting
uint16_t r1, //number of cells in lobe 1 that will connect
uint8_t w1,	 //width of lobe 1
uint8_t h1,  //height of lobe 1
uint16_t f1,  //first cell in lobe 1 that will connect.
uint16_t r2, //number of cells in lobe 2 that will connect
uint8_t w2,  //width of lobe 2
uint8_t h2,  //height of lobe 2
uint16_t f2,  //first cell in lobe 2 that will connect.
uint8_t s	 //the sth connection that cell c will make.
);

};

#endif

