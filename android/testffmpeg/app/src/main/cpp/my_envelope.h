#pragma once
#include "my_vector.h"
typedef struct _EnvPoint {
	double mT;
	double mVal;
}EnvPoint;

typedef struct _my_envelope_t {
	struct _my_vector_t *mEnv;
	double mOffset;
	double mMinValue, mMaxValue;
	double mDefaultValue;
	double mTrackLen;
	int mDB;
	int mSearchGuess;
}my_envelope_t;

struct _my_envelope_t *my_envelope_alloc(double minValue, double maxValue, double defaultValue);

void my_envelope_free(struct _my_envelope_t* p);

void my_envelope_reassign(struct _my_envelope_t* p, double when, double value);

void my_envelope_insert(struct _my_envelope_t* p, double when, double value);

void my_envelope_flatten(struct _my_envelope_t* p, double value);

void my_envelope_set_track_len(struct _my_envelope_t* p, double trackLen, double sampleDur);

double my_envelope_get_value(struct _my_envelope_t* p, double t, double sampleDur);