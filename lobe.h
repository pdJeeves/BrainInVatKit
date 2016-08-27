#ifndef _lobe_h_
#define _lobe_h_
extern "C" {
#include <stdint.h>

struct LobeWaypoint
{
	uint8_t lobe_id;
	uint8_t activity, anomaly;
	int16_t reward, punishment;

	uint8_t set;
};


struct Temporal;

/*
extern int is_input_lobe(uint8_t lobe_no);
extern int is_output_lobe(uint8_t lobe_no);

extern void read_lobe_data(uint8_t * buffer, uint16_t length, uint16_t lobe_no, void * freeture);
extern void write_lobe_data(uint8_t * buffer, uint16_t length, uint16_t lobe_no, void * freeture);
*/
/*! This struct is used to load data from the genetics file */
struct LobeData
{
/*! The position of the lobe, does nothing, possible useful if you want to render the brain.
	In the original game there was a limited number of neurons on a grid, I suspect this was to make it more straightforward to load the neuron states from a file. But the numbers of dendrites allowed contradict this.
	To be investigated. */
	uint8_t posx, posy;	
/*! The dimensions of the lobe, used by tracts: if lobe A has a width of 1 and a height of 16, lobe B has a width of 64 and a height of 16, and a tract is set from one to the other, with a flat spread and 64 dendrites, the first neuron in lobe A will connect to every neuron in the first row of B, etc. Also works rotated.  */
	uint8_t width, height, depth;
	uint8_t red, green, blue;
	
//lobe dynamics, used to ensure that all the neurons are used
	struct 
	{
		uint8_t activity;
		uint16_t period;
	} duty_cycle;
	
	uint8_t activity;
	uint8_t max_boost;
	
/*! if a neuron has a state greater than the threshold it is said to be firing */
	uint8_t threshold;
/*! the rate at which the neuron's state falls to zero, lower = faster */
	uint8_t relax_state;
	uint8_t relax_prev;
};

//contains genetic and state data, along with anything we would need to generate every tick.
struct LobeCell
{
	struct TractCell *	input;
	struct TractCell *	output;

	struct LobeData  	  data;
	struct LobeWaypoint   waypoint;

//state data
	int16_t  * learn_indicies;
	int16_t	 * recent;
	uint16_t * active_cycle;
	
	uint8_t * excitation;
	uint8_t * inhibition;
	uint8_t * firing;
	uint8_t * prev;

//generated data
	uint8_t * boost;
	uint8_t * sorted_output;

	uint16_t learn_alloc;
	
	struct TemporalCell * temporal;
};

void lobe_cell_create(struct LobeCell * cell, const struct LobeData * data);
void lobe_cell_free(struct LobeCell * cell);

void lobe_cell_add_input_tract(struct LobeCell * cell, struct TractCell * tract);
void lobe_cell_erase_input_tract(struct LobeCell * cell, struct TractCell * tract);
void lobe_cell_add_output_tract(struct LobeCell * cell, struct TractCell * tract);
void lobe_cell_erase_output_tract(struct LobeCell * cell, struct TractCell * tract);

void lobe_cell_interpolate_tick(struct LobeCell * cell);
int16_t * lobe_cell_process_tick(struct LobeCell * cell);
void lobe_cell_advance_time(struct LobeCell * cell, int tick);

static inline 
int __attribute__ ((pure)) total_neurons(const struct LobeCell * self)
{
	return self->data.width * self->data.height;
}

static inline  
float __attribute__ ((pure)) state_relax_rate(const struct LobeCell * self)
{
	return (self->data.relax_state - 1.0) / self->data.relax_state;
}

static inline 
float __attribute__ ((pure)) prev_relax_rate(const struct LobeCell * self)
{
	return (self->data.relax_prev - 1.0) / self->data.relax_prev;
}

static inline 
double __attribute__ ((pure)) period_dec(const struct LobeCell * self)
{
	return (self->data.duty_cycle.period - 1) / self->data.duty_cycle.period;
}

static inline 
double __attribute__ ((pure)) moving_average(int average, int value, int period)
{
	return (average * (period - 1) + 2 * value) / period;
}

static inline
uint8_t __attribute((always_inline)) __attribute((const)) cap_uint8_t(int input)
{
	return input < 0? 0 : input < 255? input : 255;
}

};

#endif

