/* libSoX effect: stereo reverberation
 * Copyright (c) 2007 robs@users.sourceforge.net
 * Filter design based on freeverb by Jezar at Dreampoint.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "sox_i.h"
#include "fifo.h"

#define lsx_zalloc(var, n) var = lsx_calloc(n, sizeof(*var))
#define filter_advance(p) if (--(p)->ptr < (p)->buffer) (p)->ptr += (p)->size
#define filter_delete(p) free((p)->buffer)

typedef struct {
	size_t  size;
	float   * buffer, *ptr;
	float   store;
} filter_t;

static float comb_process(filter_t * p,  /* gcc -O2 will inline this */
	float const * input, float const * feedback, float const * hf_damping)
{
	float output = *p->ptr;
	p->store = output + (p->store - output) * *hf_damping;
	*p->ptr = *input + p->store * *feedback;
	filter_advance(p);
	return output;
}

static float allpass_process(filter_t * p,  /* gcc -O2 will inline this */
	float const * input)
{
	float output = *p->ptr;
	*p->ptr = *input + output * .5;
	filter_advance(p);
	return output - *input;
}

static const size_t /* Filter delay lengths in samples (44100Hz sample-rate) */
comb_lengths[] = { 1116, 1188, 1277, 1356, 1422, 1491, 1557, 1617 },
allpass_lengths[] = { 225, 341, 441, 556 };
#define stereo_adjust 12

typedef struct { double b0, b1, a1, i1, o1; } one_pole_t;

typedef struct {
	filter_t comb[array_length(comb_lengths)];
	filter_t allpass[array_length(allpass_lengths)];
	one_pole_t one_pole[2];
} filter_array_t;

static void filter_array_create(filter_array_t * p, double rate,
	double scale, double offset, double fc_highpass, double fc_lowpass)
{
	size_t i;
	double r = rate * (1 / 44100.); /* Compensate for actual sample-rate */

	for (i = 0; i < array_length(comb_lengths); ++i, offset = -offset)
	{
		filter_t * pcomb = &p->comb[i];
		pcomb->size = (size_t)(scale * r * (comb_lengths[i] + stereo_adjust * offset) + .5);
		pcomb->ptr = lsx_zalloc(pcomb->buffer, pcomb->size);
	}
	for (i = 0; i < array_length(allpass_lengths); ++i, offset = -offset)
	{
		filter_t * pallpass = &p->allpass[i];
		pallpass->size = (size_t)(r * (allpass_lengths[i] + stereo_adjust * offset) + .5);
		pallpass->ptr = lsx_zalloc(pallpass->buffer, pallpass->size);
	}
	{ /* EQ: highpass */
		one_pole_t * q = &p->one_pole[0];
		q->a1 = -exp(-2 * M_PI * fc_highpass / rate);
		q->b0 = (1 - q->a1) / 2, q->b1 = -q->b0;
	}
	{ /* EQ: lowpass */
		one_pole_t * q = &p->one_pole[1];
		q->a1 = -exp(-2 * M_PI * fc_lowpass / rate);
		q->b0 = 1 + q->a1, q->b1 = 0;
	}
}

static void filter_array_process(filter_array_t * p,
	size_t length, float const * input, float * output,
	float const * feedback, float const * hf_damping, float const * gain)
{
	while (length--) {
		float out = 0, in = *input++;

		size_t i = array_length(comb_lengths) - 1;
		do out += comb_process(p->comb + i, &in, feedback, hf_damping);
		while (i--);

		i = array_length(allpass_lengths) - 1;
		do out = allpass_process(p->allpass + i, &out);
		while (i--);

		*output++ = out * *gain;
	}
}

static void filter_array_delete(filter_array_t * p)
{
	size_t i;

	for (i = 0; i < array_length(allpass_lengths); ++i)
		filter_delete(&p->allpass[i]);
	for (i = 0; i < array_length(comb_lengths); ++i)
		filter_delete(&p->comb[i]);
}

typedef struct _reverb_t {
	float feedback;
	float hf_damping;
	float gain;
	fifo_t input_fifo;
	filter_array_t chan[2];
	float * out[2];
} reverb_t;

static void reverb_create(reverb_t * p, double sample_rate_Hz,
	double wet_gain_dB,
	double room_scale,     /* % */
	double reverberance,   /* % */
	double hf_damping,     /* % */
	double pre_delay_ms,
	double stereo_depth,
	double tone_low,       /* % */
	double tone_high,      /* % */
	size_t buffer_size,
	float * * out)
{
	size_t i, delay = pre_delay_ms / 1000 * sample_rate_Hz + .5;
	double scale = room_scale / 100 * .9 + .1;
	double depth = stereo_depth / 100;
	double a = -1 / log(1 - /**/.3 /**/);           /* Set minimum feedback */
	double b = 100 / (log(1 - /**/.98/**/) * a + 1);  /* Set maximum feedback */
	double fc_highpass = midi_to_freq(72 - tone_low / 100 * 48);
	double fc_lowpass = midi_to_freq(72 + tone_high / 100 * 48);

	memset(p, 0, sizeof(*p));
	p->feedback = 1 - exp((reverberance - b) / (a * b));
	p->hf_damping = hf_damping / 100 * .3 + .2;
	p->gain = dB_to_linear(wet_gain_dB) * .015;
	fifo_create(&p->input_fifo, sizeof(float));
	memset(fifo_write(&p->input_fifo, delay, 0), 0, delay * sizeof(float));
	for (i = 0; i <= ceil(depth); ++i) {
		filter_array_create(p->chan + i, sample_rate_Hz, scale, i * depth, fc_highpass, fc_lowpass);
		out[i] = lsx_zalloc(p->out[i], buffer_size);
	}
}

static void reverb_process(reverb_t * p, size_t length)
{
	size_t i;
	for (i = 0; i < 2 && p->out[i]; ++i)
		filter_array_process(p->chan + i, length, (float *)fifo_read_ptr(&p->input_fifo), p->out[i], &p->feedback, &p->hf_damping, &p->gain);
	fifo_read(&p->input_fifo, length, NULL);
}

static void reverb_delete(reverb_t * p)
{
	size_t i;
	for (i = 0; i < 2 && p->out[i]; ++i) {
		free(p->out[i]);
		filter_array_delete(p->chan + i);
	}
	fifo_delete(&p->input_fifo);
}

/********************wrap*******************************/
#include <assert.h>
#include "reverb.h"
#include "Log.h"
#ifdef _WIN32
#include <time.h>
#include <Windows.h>
#include <stdint.h>
int gettimeofday(struct timeval *tp, void *tzp)
{
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;
	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	clock = mktime(&tm);
	tp->tv_sec = clock;
	tp->tv_usec = wtm.wMilliseconds * 1000;
	return (0);
}
#else
#include <sys/time.h>
#endif

typedef struct {
	reverb_t reverb;
	float *dry, *wet[2];
}my_reverb_chan_t;

typedef struct _my_reverb_t {
	size_t buffer_size;
	size_t channels;
	my_reverb_chan_t *chan;
	double dry_gain_dB;
	int wet_only;
}my_reverb_t;
struct _my_reverb_t* create_reverb(
	size_t channels,
	double sample_rate_Hz,
	double wet_gain_dB,
	double dry_gain_dB,
	double room_scale,     /* % */
	double reverberance,   /* % */
	double hf_damping,     /* % */
	double pre_delay_ms,
	double stereo_depth,
	double tone_low,       /* % */
	double tone_high,      /* % */
	int wet_only,
	size_t buffer_size) {
	my_reverb_t *reverb = malloc(sizeof(my_reverb_t));
	size_t i = 0;
	if (NULL == reverb) {
		assert(0);
		exit(2);
	}
	memset(reverb, 0, sizeof(my_reverb_t));
	reverb->buffer_size = buffer_size;
	reverb->channels = channels;
	reverb->chan = malloc(sizeof(my_reverb_chan_t) * channels);
	reverb->wet_only = wet_only;
	reverb->dry_gain_dB = dry_gain_dB;
	for (i = 0; i < channels; i++) {
		reverb_create(&reverb->chan[i], sample_rate_Hz, wet_gain_dB, room_scale, reverberance, hf_damping, pre_delay_ms, stereo_depth, tone_low, tone_high,buffer_size, reverb->chan[i].wet);
	}
	return reverb;
}

void delete_reverb(struct _my_reverb_t *reverb) {
	size_t i = 0;
	if (NULL != reverb) {
		for (i = 0; i < reverb->channels; i++) {
			reverb_delete(&reverb->chan[i]);
		}
		free(reverb->chan);
		free(reverb);
	}
}

int getdiff(struct timeval *tv1, struct timeval *tv2){
	int64_t i = (int64_t)tv2->tv_sec * 1000 * 1000 + tv2->tv_usec - (tv1->tv_sec  *  1000 * 1000 + tv1->tv_usec);
	return i;
}

void process_reverb(struct _my_reverb_t *p, float* in[], float *obuf[], size_t len) {
	size_t i = 0, w = 0;
	assert(len <= p->buffer_size);
	struct timeval tv1, tv2, tv3, tv4, tv5;
	gettimeofday(&tv1, NULL);
	for (i = 0; i < p->channels; i++) {
		p->chan[i].dry = fifo_write(&p->chan[i].reverb.input_fifo, len, NULL);
	}
	gettimeofday(&tv2, NULL);
	for (i = 0; i < p->channels; i++) {
		memcpy(p->chan[i].dry, in[i], len * sizeof(float));
	}
	gettimeofday(&tv3, NULL);
	for (i = 0; i < p->channels; i++) {
		reverb_process(&p->chan[i].reverb, len);
	}
	gettimeofday(&tv4, NULL);

	const double dryMult = p->wet_only != 0 ? 0 : dB_to_linear(p->dry_gain_dB);

	if (p->channels == 2) {
		for (i = 0; i < len; ++i) for (w = 0; w < 2; ++w) {
			float out = dryMult * p->chan[w].dry[i] +
				.5 * (p->chan[0].wet[w][i] + p->chan[1].wet[w][i]);
			obuf[w][i] = out;
			//*obuf++ = SOX_FLOAT_32BIT_TO_SAMPLE(out, effp->clips);
		}
	}
	else {
		for (i = 0; i < len; ++i) for (w = 0; w < p->channels; ++w) {
			float out = dryMult * p->chan[0].dry[i] + p->chan[0].wet[w][i];
			obuf[w][i] = out;
			//*obuf++ = SOX_FLOAT_32BIT_TO_SAMPLE(out, effp->clips);
		}
	}
	gettimeofday(&tv5, NULL);
	mylog_i("step1:%d step2:%d step3:%d step4:%d", getdiff(&tv1, &tv2), getdiff(&tv2, &tv3)
			, getdiff(&tv3, &tv4), getdiff(&tv4, &tv5));
}