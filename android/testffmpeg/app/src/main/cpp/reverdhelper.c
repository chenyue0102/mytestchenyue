#include "reverdhelper.h"
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include "libavformat/avformat.h"
#include "reverb2.h"

extern sf_sample_st earlyref_step(sf_rv_earlyref_st *earlyref, sf_sample_st input);
extern float delay_step(sf_rv_delay_st *delay, float v);
extern void oversample_stepup(sf_rv_oversample_st *oversample, float input, float *output);
extern float dccut_step(sf_rv_dccut_st *dccut, float v);
extern float noise_step(sf_rv_noise_st *noise);
extern float lfo_step(sf_rv_lfo_st *lfo);
extern float iir1_step(sf_rv_iir1_st *iir1, float v);
extern float allpassm_step(sf_rv_allpassm_st *allpassm, float v, float mod, float fbmod);
extern float allpass_step(sf_rv_allpass_st *allpass, float v);
extern float delay_getlast(sf_rv_delay_st *delay);
extern float biquad_step(sf_rv_biquad_st *biquad, float v);
extern float allpass3_step(sf_rv_allpass3_st *allpass3, float v, float mod);
extern float delay_get(sf_rv_delay_st *delay, int offset);
extern float allpass2_get1(sf_rv_allpass2_st *allpass2, int offset);
extern float allpass2_get2(sf_rv_allpass2_st *allpass2, int offset);
extern float allpass3_get3(sf_rv_allpass3_st *allpass3, int offset);
extern float comb_step(sf_rv_comb_st *comb, float v, float feedback);
extern float oversample_stepdown(sf_rv_oversample_st *oversample, float *input);
extern float allpass2_step(sf_rv_allpass2_st *allpass2, float v);
extern float allpass3_get1(sf_rv_allpass3_st *allpass3, int offset);
extern float allpass3_get2(sf_rv_allpass3_st *allpass3, int offset);

float uint16_to_float(uint16_t n)
{
	int16_t tmp = (int16_t)n;
	if (tmp < 0)
		return (float)tmp / 32768.0f;
	else
		return (float)tmp / 32767.0f;
}

int16_t float_to_uint16(float n)
{
	if (n < 0)
		return (int16_t)(n * 32768.0f);
	else
		return (int16_t)(n * 32767.0f);
}

reverb_state_st alloc_reverb_state()
{
	reverb_state_st state = malloc(sizeof(sf_reverb_state_st));
	return state;
}

int set_reverb(reverb_state_st rv, const char * preset, int rate)
{
	sf_reverb_preset p;
	if (strcmp(preset, "default") == 0) p = SF_REVERB_PRESET_DEFAULT;
	else if (strcmp(preset, "smallhall1") == 0) p = SF_REVERB_PRESET_SMALLHALL1;
	else if (strcmp(preset, "smallhall2") == 0) p = SF_REVERB_PRESET_SMALLHALL2;
	else if (strcmp(preset, "mediumhall1") == 0) p = SF_REVERB_PRESET_MEDIUMHALL1;
	else if (strcmp(preset, "mediumhall2") == 0) p = SF_REVERB_PRESET_MEDIUMHALL2;
	else if (strcmp(preset, "largehall1") == 0) p = SF_REVERB_PRESET_LARGEHALL1;
	else if (strcmp(preset, "largehall2") == 0) p = SF_REVERB_PRESET_LARGEHALL2;
	else if (strcmp(preset, "smallroom1") == 0) p = SF_REVERB_PRESET_SMALLROOM1;
	else if (strcmp(preset, "smallroom2") == 0) p = SF_REVERB_PRESET_SMALLROOM2;
	else if (strcmp(preset, "mediumroom1") == 0) p = SF_REVERB_PRESET_MEDIUMROOM1;
	else if (strcmp(preset, "mediumroom2") == 0) p = SF_REVERB_PRESET_MEDIUMROOM2;
	else if (strcmp(preset, "largeroom1") == 0) p = SF_REVERB_PRESET_LARGEROOM1;
	else if (strcmp(preset, "largeroom2") == 0) p = SF_REVERB_PRESET_LARGEROOM2;
	else if (strcmp(preset, "mediumer1") == 0) p = SF_REVERB_PRESET_MEDIUMER1;
	else if (strcmp(preset, "mediumer2") == 0) p = SF_REVERB_PRESET_MEDIUMER2;
	else if (strcmp(preset, "platehigh") == 0) p = SF_REVERB_PRESET_PLATEHIGH;
	else if (strcmp(preset, "platelow") == 0) p = SF_REVERB_PRESET_PLATELOW;
	else if (strcmp(preset, "longreverb1") == 0) p = SF_REVERB_PRESET_LONGREVERB1;
	else if (strcmp(preset, "longreverb2") == 0) p = SF_REVERB_PRESET_LONGREVERB2;
	else {
		assert(0);
		return -1;
	}
	sf_presetreverb(rv, rate, p);

	return 0;
}

void reverb_float(reverb_state_st rv, float left, float right, float * outleft, float * outright)
{
	assert(NULL != rv && NULL != outleft && NULL != outright);
	// extra hardcoded constants
	const float modnoise1 = 0.09f;
	const float modnoise2 = 0.06f;
	const float crossfeed = 0.4f;

	// oversample buffer
	float osL[SF_REVERB_OF], osR[SF_REVERB_OF];

	//for (int i = 0; i < size; i++)
	{
		sf_sample_st input = { left, right };
		// early reflection
		sf_sample_st er = earlyref_step(&rv->earlyref, input);
		float erL = er.L * rv->ertolate + input.L;
		float erR = er.R * rv->ertolate + input.R;

		// oversample the single input into multiple outputs
		oversample_stepup(&rv->oversampleL, erL, osL);
		oversample_stepup(&rv->oversampleR, erR, osR);

		// for each oversampled sample...
		for (int i2 = 0; i2 < rv->oversampleL.factor; i2++) {
			// dc cut
			float outL = dccut_step(&rv->dccutL, osL[i2]);
			float outR = dccut_step(&rv->dccutR, osR[i2]);

			// noise
			float mnoise = noise_step(&rv->noise);
			float lfo = (lfo_step(&rv->lfo1) + modnoise1 * mnoise) * rv->wander;
			lfo = iir1_step(&rv->lfo1_lpf, lfo);
			mnoise *= modnoise2;

			// diffusion
			for (int i = 0, s = -1; i < 10; i++, s = -s) {
				outL = allpassm_step(&rv->diffL[i], outL, lfo * s, mnoise);
				outR = allpassm_step(&rv->diffR[i], outR, lfo, mnoise * s);
			}

			// cross fade
			float crossL = outL, crossR = outR;
			for (int i = 0; i < 4; i++) {
				crossL = allpass_step(&rv->crossL[i], crossL);
				crossR = allpass_step(&rv->crossR[i], crossR);
			}
			outL = iir1_step(&rv->clpfL, outL + crossfeed * crossR);
			outR = iir1_step(&rv->clpfR, outR + crossfeed * crossL);

			// bass boost
			crossL = delay_getlast(&rv->cdelayL);
			crossR = delay_getlast(&rv->cdelayR);
			outL += rv->loopdecay *
				(crossR + rv->bassb * biquad_step(&rv->basslpL, biquad_step(&rv->bassapL, crossR)));
			outR += rv->loopdecay *
				(crossL + rv->bassb * biquad_step(&rv->basslpR, biquad_step(&rv->bassapR, crossL)));

			// dampening
			outL = allpassm_step(&rv->dampap2L,
				delay_step(&rv->dampdL,
					allpassm_step(&rv->dampap1L,
						iir1_step(&rv->damplpL, outL), lfo, mnoise)),
				-lfo, -mnoise);
			outR = allpassm_step(&rv->dampap2R,
				delay_step(&rv->dampdR,
					allpassm_step(&rv->dampap1R,
						iir1_step(&rv->damplpR, outR), -lfo, -mnoise)),
				lfo, mnoise);

			// update cross fade bass boost delay
			delay_step(&rv->cdelayL,
				allpass3_step(&rv->cbassap2L,
					delay_step(&rv->cbassd2L,
						allpass2_step(&rv->cbassap1L,
							delay_step(&rv->cbassd1L, outL))),
					lfo));
			delay_step(&rv->cdelayR,
				allpass3_step(&rv->cbassap2R,
					delay_step(&rv->cbassd2R,
						allpass2_step(&rv->cbassap1R,
							delay_step(&rv->cbassd1R, outR))),
					-lfo));

			//
			float D1 =
				delay_get(&rv->cbassd1L, rv->outco[0]);
			float D2 =
				delay_get(&rv->cbassd2L, rv->outco[1]) -
				delay_get(&rv->cbassd2R, rv->outco[2]) +
				delay_get(&rv->cbassd2L, rv->outco[3]) -
				delay_get(&rv->cdelayR, rv->outco[4]) -
				delay_get(&rv->cbassd1R, rv->outco[5]) -
				delay_get(&rv->cbassd2R, rv->outco[6]);
			float D3 =
				delay_get(&rv->cdelayL, rv->outco[7]) +
				allpass2_get1(&rv->cbassap1L, rv->outco[8]) +
				allpass2_get2(&rv->cbassap1L, rv->outco[9]) -
				allpass2_get2(&rv->cbassap1R, rv->outco[10]) +
				allpass3_get1(&rv->cbassap2L, rv->outco[11]) +
				allpass3_get2(&rv->cbassap2L, rv->outco[12]) +
				allpass3_get3(&rv->cbassap2L, rv->outco[13]) -
				allpass3_get2(&rv->cbassap2R, rv->outco[14]);
			float D4 =
				delay_get(&rv->cdelayL, rv->outco[15]);

			float B1 =
				delay_get(&rv->cbassd1R, rv->outco[16]);
			float B2 =
				delay_get(&rv->cbassd2R, rv->outco[17]) -
				delay_get(&rv->cbassd2L, rv->outco[18]) +
				delay_get(&rv->cbassd2R, rv->outco[19]) -
				delay_get(&rv->cdelayL, rv->outco[20]) -
				delay_get(&rv->cbassd1L, rv->outco[21]) -
				delay_get(&rv->cbassd2L, rv->outco[22]);
			float B3 =
				delay_get(&rv->cdelayR, rv->outco[23]) +
				allpass2_get1(&rv->cbassap1R, rv->outco[24]) +
				allpass2_get2(&rv->cbassap1R, rv->outco[25]) -
				allpass2_get2(&rv->cbassap1L, rv->outco[26]) +
				allpass3_get1(&rv->cbassap2R, rv->outco[27]) +
				allpass3_get2(&rv->cbassap2R, rv->outco[28]) +
				allpass3_get3(&rv->cbassap2R, rv->outco[29]) -
				allpass3_get2(&rv->cbassap2L, rv->outco[30]);
			float B4 =
				delay_get(&rv->cdelayR, rv->outco[31]);

			float D = D1 * 0.469f + D2 * 0.219f + D3 * 0.064f + D4 * 0.045f;
			float B = B1 * 0.469f + B2 * 0.219f + B3 * 0.064f + B4 * 0.045f;

			lfo = iir1_step(&rv->lfo2_lpf, lfo_step(&rv->lfo2) * rv->wander);
			outL = comb_step(&rv->combL, D, lfo);
			outR = comb_step(&rv->combR, B, -lfo);

			outL = delay_step(&rv->lastdelayL, biquad_step(&rv->lastlpfL, outL));
			outR = delay_step(&rv->lastdelayR, biquad_step(&rv->lastlpfR, outR));

			osL[i2] = outL * rv->wet1 + outR * rv->wet2 +
				delay_step(&rv->inpdelayL, osL[i2]) * rv->dry;
			osR[i2] = outR * rv->wet1 + outL * rv->wet2 +
				delay_step(&rv->inpdelayR, osR[i2]) * rv->dry;
		}

		float outL = oversample_stepdown(&rv->oversampleL, osL);
		float outR = oversample_stepdown(&rv->oversampleR, osR);
		outL += er.L * rv->erefwet + input.L * rv->dry;
		outR += er.R * rv->erefwet + input.R * rv->dry;
		sf_sample_st output = (sf_sample_st) { outL, outR };

		*outleft = output.L;
		*outright = output.R;
	}
}

void reverb_uint16(reverb_state_st rv, uint16_t left, uint16_t right, uint16_t * outleft, uint16_t * outright)
{
	assert(NULL != outleft && NULL != outright);
	float fl = uint16_to_float(left), fr = uint16_to_float(right);
	float outl, outr;
	reverb_float(rv, fl, fr, &outl, &outr);
	*outleft = float_to_uint16(outl);
	*outright = float_to_uint16(outr);
}

void reverb_frame(reverb_state_st rv, struct AVFrame *frame) {
	assert(2 == frame->channels);
	if (frame->format == AV_SAMPLE_FMT_FLTP) {
		float *l = (float*)frame->data[0], *r = (float*)frame->data[1];
		float outl, outr;
		for (int i = 0; i < frame->nb_samples; i++) {
			reverb_float(rv, l[i], r[i], &outl, &outr);
			l[i] = outl;
			r[i] = outr;
		}
	}
	else if (frame->format == AV_SAMPLE_FMT_S16P) {
		uint16_t *l = (uint16_t*)frame->data[0], *r = (uint16_t*)frame->data[1];
		uint16_t outl, outr;
		for (int i = 0; i < frame->nb_samples; i++) {
			reverb_uint16(rv, l[i], r[i], &outl, &outr);
			l[i] = outl;
			r[i] = outr;
		}
	}
	else {
		assert(0);
	}
}

void free_reverb_state(reverb_state_st rv)
{
	free(rv);
}
