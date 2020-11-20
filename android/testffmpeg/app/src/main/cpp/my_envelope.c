#include "my_envelope.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <memory.h>
#include "my_vector.h"





static double ClampValue(my_envelope_t *p, double v) {
	return max(p->mMinValue, min(p->mMaxValue, v));
}

struct _my_envelope_t *my_envelope_alloc(double minValue, double maxValue, double defaultValue) {
	my_envelope_t *p = malloc(sizeof(my_envelope_t));
	memset(p, 0, sizeof(my_envelope_t));
	p->mMinValue = minValue;
	p->mMaxValue = maxValue;
	p->mDefaultValue = ClampValue(p, defaultValue);
	p->mEnv = my_vector_alloc(sizeof(EnvPoint), 180);
	p->mSearchGuess = -2;
	return p;
}

void my_envelope_free(struct _my_envelope_t* p) {
	if (NULL != p) {
		my_vector_free(p->mEnv);
		free(p);
	}
}

static double get_env_t(struct _my_vector_t *mEnv, size_t index) {
	double d = 0.;
	EnvPoint *env_point = my_vector_at(mEnv, index);
	if (NULL != env_point) {
		memcpy(&d, &env_point->mT, sizeof(double));
	}
	return d;
}

static double get_env_v(struct _my_vector_t *mEnv, size_t index) {
	double d = 0.;
	EnvPoint *env_point = my_vector_at(mEnv, index);
	if (NULL != env_point) {
		memcpy(&d, &env_point->mVal, sizeof(double));
	}
	return d;
}

static void set_env_v(struct _my_vector_t *mEnv, size_t index, double v) {
	EnvPoint *env_point = my_vector_at(mEnv, index);
	if (NULL != env_point) {
		memcpy(&env_point->mVal, &v, sizeof(double));
	}
}

void my_envelope_reassign(struct _my_envelope_t* p, double when, double value) {
	when -= p->mOffset;

	int len = my_vector_size(p->mEnv);
	if (len == 0)
		return;

	int i = 0;
	while (i < len && when > get_env_t(p->mEnv, i))
		i++;

	if (i >= len || when < get_env_t(p->mEnv, i))
		return;

	set_env_v(p->mEnv, i, value);
	return;
}

void my_envelope_insert(struct _my_envelope_t* p, double when, double value) {
	EnvPoint env_point = { when, value };
	my_vector_push_back(p->mEnv, &env_point);
}

void my_envelope_flatten(struct _my_envelope_t* p, double value) {
	my_vector_clear(p->mEnv);
	p->mDefaultValue = ClampValue(p, value);
}

typedef struct _envelop_range_t {
	int first;
	int second;
}envelop_range_t;

static int bsearch_compare(const void *key, const void *data) {
	const EnvPoint *point1 = key, *point2 = data;
	return (int)(point1->mT - point2->mT);
}

void* bs_upper_bound(const void *begin, size_t num, size_t width, const void *key, int(__cdecl *compare) (const void *, const void *)) {
	int l = 0;
	int h = num; // Not n - 1
	while (l < h) {
		size_t mid = l + (h - l) / 2;
		int c = compare(key, (unsigned char*)begin + (mid * width));
		if (c >= 0) {
			l = mid + 1;
		}
		else {
			h = mid;
		}
	}
	return (unsigned char*)begin + l;
}

//¿ÉÄÜ·µ»Øbegin+num
void* bs_lower_bound(const void *begin, size_t num, size_t width, const void *key, int(__cdecl *compare) (const void *, const void *)) {
	size_t l = 0, h = num;
	while (l < h) {
		size_t mid = l + (h - l) / 2;
		int c = compare(key, (unsigned char*)begin + (mid * width));
		if (c <= 0) {
			h = mid;
		}
		else {
			l = mid + 1;
		}
	}
	return (unsigned char*)begin + l;
}

static envelop_range_t EqualRange(struct _my_vector_t *mEnv, double when, double sampleDur)
{
	envelop_range_t range = {0};
	// Find range of envelope points matching the given time coordinate
	// (within an interval of length sampleDur)
	// by binary search; if empty, it still indicates where to
	// insert.
	const double tolerance = sampleDur / 2;
	void *begin = my_vector_begin(mEnv);
	void *end = my_vector_end(mEnv);

	EnvPoint key = { when - tolerance, 0.0 };
	void *first = bs_lower_bound(begin, my_vector_size(mEnv), sizeof(EnvPoint), &key, &bsearch_compare);
	EnvPoint *after = first;
	while (after != end && after->mT <= when + tolerance)
		++after;

	range.first = (EnvPoint*)first - (EnvPoint*)begin;
	range.second = (EnvPoint*)after - (EnvPoint*)begin;
	return range;
}


// relative time
/// @param Lo returns last index before this time, maybe -1
/// @param Hi returns first index at or after this time, maybe past the end
void BinarySearchForTime_LeftLimit(struct _my_envelope_t* p, int *Lo, int *Hi, double t)
{
	*Lo = -1;
	*Hi = my_vector_size(p->mEnv);

	// Invariants:  Lo is not less than -1, Hi not more than size
	while (*Hi > (*Lo + 1)) {
		int mid = (*Lo + *Hi) / 2;
		// mid must be strictly between Lo and Hi, therefore a valid index
		if (t <= get_env_t(p->mEnv, mid))
			*Hi = mid;
		else
			*Lo = mid;
	}
	assert(*Hi == (*Lo + 1));

	p->mSearchGuess = *Lo;
}

// relative time
/// @param Lo returns last index at or before this time, maybe -1
/// @param Hi returns first index after this time, maybe past the end
void BinarySearchForTime(struct _my_envelope_t* p, int *Lo, int *Hi, double t)
{
	// Optimizations for the usual pattern of repeated calls with
	// small increases of t.
	{
		if (p->mSearchGuess >= 0 && p->mSearchGuess < (int)my_vector_size(p->mEnv)) {
			if (t >= get_env_t(p->mEnv, p->mSearchGuess) &&
				(1 + p->mSearchGuess == (int)my_vector_size(p->mEnv) ||
					t < get_env_t(p->mEnv, 1 + p->mSearchGuess))) {
				*Lo = p->mSearchGuess;
				*Hi = 1 + p->mSearchGuess;
				return;
			}
		}

		++(p->mSearchGuess);
		if (p->mSearchGuess >= 0 && p->mSearchGuess < (int)my_vector_size(p->mEnv)) {
			if (t >= get_env_t(p->mEnv, p->mSearchGuess) &&
				(1 + p->mSearchGuess == (int)my_vector_size(p->mEnv) ||
					t < get_env_t(p->mEnv, 1 + p->mSearchGuess))) {
				*Lo = p->mSearchGuess;
				*Hi = 1 + p->mSearchGuess;
				return;
			}
		}
	}

	*Lo = -1;
	*Hi = my_vector_size(p->mEnv);

	// Invariants:  Lo is not less than -1, Hi not more than size
	while (*Hi > (*Lo + 1)) {
		int mid = (*Lo + *Hi) / 2;
		// mid must be strictly between Lo and Hi, therefore a valid index
		if (t < get_env_t(p->mEnv, mid))
			*Hi = mid;
		else
			*Lo = mid;
	}
	assert(*Hi == (*Lo + 1));

	p->mSearchGuess = *Lo;
}


/// GetInterpolationStartValueAtPoint() is used to select either the
/// envelope value or its log depending on whether we are doing linear
/// or log interpolation.
/// @param iPoint index in env array to look at.
/// @return value there, or its (safe) log10.
double GetInterpolationStartValueAtPoint(struct _my_envelope_t* p, int iPoint)
{
	double v = get_env_v(p->mEnv, iPoint);
	if (!p->mDB)
		return v;
	else
		return log10(v);
}


void GetValuesRelative(struct _my_envelope_t* p, double *buffer, int bufferLen, double t0, double tstep, int leftLimit)
{
	// JC: If bufferLen ==0 we have probably just allocated a zero sized buffer.
	// wxASSERT( bufferLen > 0 );

	const double epsilon = tstep / 2;
	int len = my_vector_size(p->mEnv);

	double t = t0;
	double increment = 0;
	if (len > 1 && t <= get_env_t(p->mEnv, 0) && get_env_t(p->mEnv, 0) == get_env_t(p->mEnv, 1))
		increment = leftLimit ? -epsilon : epsilon;

	double tprev, vprev, tnext = 0, vnext, vstep = 0;

	for (int b = 0; b < bufferLen; b++) {

		// Get easiest cases out the way first...
		// IF empty envelope THEN default value
		if (len <= 0) {
			buffer[b] = p->mDefaultValue;
			t += tstep;
			continue;
		}

		double tplus = t + increment;

		// IF before envelope THEN first value
		if (leftLimit ? tplus <= get_env_t(p->mEnv, 0) : tplus < get_env_t(p->mEnv, 0)) {
			buffer[b] = get_env_v(p->mEnv, 0);
			t += tstep;
			continue;
		}
		// IF after envelope THEN last value
		if (leftLimit
			? tplus > get_env_t(p->mEnv, len - 1) : tplus >= get_env_t(p->mEnv, len - 1)) {
			buffer[b] = get_env_v(p->mEnv, len - 1);
			t += tstep;
			continue;
		}

		// be careful to get the correct limit even in case epsilon == 0
		if (b == 0 ||
			(leftLimit ? tplus > tnext : tplus >= tnext)) {

			// We're beyond our tnext, so find the next one.
			// Don't just increment lo or hi because we might
			// be zoomed far out and that could be a large number of
			// points to move over.  That's why we binary search.

			int lo, hi;
			if (leftLimit)
				BinarySearchForTime_LeftLimit(p, &lo, &hi, tplus);
			else
				BinarySearchForTime(p, &lo, &hi, tplus);

			// mEnv[0] is before tplus because of eliminations above, therefore lo >= 0
			// mEnv[len - 1] is after tplus, therefore hi <= len - 1
			assert(lo >= 0 && hi <= len - 1);

			tprev = get_env_t(p->mEnv, lo);
			tnext = get_env_t(p->mEnv, hi);

			if (hi + 1 < len && tnext == get_env_t(p->mEnv, hi + 1))
				// There is a discontinuity after this point-to-point interval.
				// Usually will stop evaluating in this interval when time is slightly
				// before tNext, then use the right limit.
				// This is the right intent
				// in case small roundoff errors cause a sample time to be a little
				// before the envelope point time.
				// Less commonly we want a left limit, so we continue evaluating in
				// this interval until shortly after the discontinuity.
				increment = leftLimit ? -epsilon : epsilon;
			else
				increment = 0;

			vprev = GetInterpolationStartValueAtPoint(p, lo);
			vnext = GetInterpolationStartValueAtPoint(p, hi);

			// Interpolate, either linear or log depending on mDB.
			double dt = (tnext - tprev);
			double to = t - tprev;
			double v;
			if (dt > 0.0)
			{
				v = (vprev * (dt - to) + vnext * to) / dt;
				vstep = (vnext - vprev) * tstep / dt;
			}
			else
			{
				v = vnext;
				vstep = 0.0;
			}

			// An adjustment if logarithmic scale.
			if (p->mDB)
			{
				v = pow(10.0, v);
				vstep = pow(10.0, vstep);
			}

			buffer[b] = v;
		}
		else {
			if (p->mDB) {
				buffer[b] = buffer[b - 1] * vstep;
			}
			else {
				buffer[b] = buffer[b - 1] + vstep;
			}
		}

		t += tstep;
	}
}


static void GetValues(struct _my_envelope_t* p, double *buffer, int bufferLen, double t0, double tstep) {
	// Convert t0 from absolute to clip-relative time
	t0 -= p->mOffset;
	GetValuesRelative(p, buffer, bufferLen, t0, tstep, 0);
}

static double GetValueRelative(struct _my_envelope_t* p, double t, double sampleDur) {
	// t is absolute time
	double temp;

	GetValues(p, &temp, 1, t, sampleDur);
	return temp;
}


// This is used only during construction of an Envelope by complete or partial
// copy of another, or when truncating a track.
void AddPointAtEnd(struct _my_vector_t *mEnv, double t, double val)
{
	EnvPoint env_point = { t, val };
	my_vector_push_back(mEnv, &env_point);
	//mEnv.push_back(EnvPoint{ t, val });

	// Assume copied points were stored by nondecreasing time.
	// Allow no more than two points at exactly the same time.
	// Maybe that happened, because extra points were inserted at the boundary
	// of the copied range, which were not in the source envelope.
	size_t nn = my_vector_size(mEnv) - 1;
	while (nn >= 2 && get_env_t(mEnv, nn - 2) == t) {
		// Of three or more points at the same time, erase one in the middle,
		// not the one newly added.
		my_vector_erase(mEnv, nn - 1);
		--nn;
	}
}

void my_envelope_set_track_len(struct _my_envelope_t* p, double trackLen, double sampleDur) {
	// Preserve the left-side limit at trackLen.
	envelop_range_t range = EqualRange(p->mEnv, trackLen, sampleDur);
	int needPoint = (range.first == range.second && trackLen < p->mTrackLen);
	double value = 0.0;
	if (needPoint)
		value = GetValueRelative(p, trackLen, 0.0);

	p->mTrackLen = trackLen;

	// Shrink the array.
	// If more than one point already at the end, keep only the first of them.
	int newLen = min(1 + range.first, range.second);
	my_vector_resize(p->mEnv, newLen);

	if (needPoint)
		AddPointAtEnd(p->mEnv, p->mTrackLen, value);
}

double my_envelope_get_value(struct _my_envelope_t* p, double t, double sampleDur) {
	// t is absolute time
	double temp;

	GetValues(p, &temp, 1, t, sampleDur);
	return temp;
}