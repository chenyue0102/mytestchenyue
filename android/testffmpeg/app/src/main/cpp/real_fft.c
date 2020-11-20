#include "real_fft.h"
#include <malloc.h>
#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif
#include <math.h>

void my_init_fft(size_t fftlen, FFTParam *h) {
	int temp;
	h->Points = fftlen / 2;
	h->SinTable = malloc(2 * h->Points * sizeof(fft_type));
	h->BitReversed = malloc(h->Points * sizeof(int));

	for (size_t i = 0; i < h->Points; i++) {
		temp = 0;
		for (size_t mask = h->Points / 2; mask > 0; mask >>= 1) {
			temp = (temp >> 1) + (i & mask ? h->Points : 0);
		}
		h->BitReversed[i] = temp;
	}

	for (size_t i = 0; i < h->Points; i++) {
		h->SinTable[h->BitReversed[i]] = (fft_type)-sin(2 * M_PI * i / (2 * h->Points));
		h->SinTable[h->BitReversed[i] + 1] = (fft_type)-cos(2 * M_PI * i / (2 * h->Points));
	}
}

FFTParam* fftparam_alloc(size_t fftlen) {
	FFTParam *p = malloc(sizeof(FFTParam));
	my_init_fft(fftlen, p);
	return p;
}

void fftparam_free(FFTParam* p) {
	if (NULL != p) {
		free(p->BitReversed);
		free(p->SinTable);
		free(p);
	}
}

/*
*  Forward FFT routine.  Must call GetFFT(fftlen) first!
*
*  Note: Output is BIT-REVERSED! so you must use the BitReversed to
*        get legible output, (i.e. Real_i = buffer[ h->BitReversed[i] ]
*                                  Imag_i = buffer[ h->BitReversed[i]+1 ] )
*        Input is in normal order.
*
* Output buffer[0] is the DC bin, and output buffer[1] is the Fs/2 bin
* - this can be done because both values will always be real only
* - this allows us to not have to allocate an extra complex value for the Fs/2 bin
*
*  Note: The scaling on this is done according to the standard FFT definition,
*        so a unit amplitude DC signal will output an amplitude of (N)
*        (Older revisions would progressively scale the input, so the output
*        values would be similar in amplitude to the input values, which is
*        good when using fixed point arithmetic)
*/
void RealFFTf(fft_type *buffer, const FFTParam *h)
{
	fft_type *A, *B;
	const fft_type *sptr;
	const fft_type *endptr1, *endptr2;
	const int *br1, *br2;
	fft_type HRplus, HRminus, HIplus, HIminus;
	fft_type v1, v2, sin, cos;

	auto ButterfliesPerGroup = h->Points / 2;

	/*
	*  Butterfly:
	*     Ain-----Aout
	*         \ /
	*         / \
	*     Bin-----Bout
	*/

	endptr1 = buffer + h->Points * 2;

	while (ButterfliesPerGroup > 0)
	{
		A = buffer;
		B = buffer + ButterfliesPerGroup * 2;
		sptr = h->SinTable;

		while (A < endptr1)
		{
			sin = *sptr;
			cos = *(sptr + 1);
			endptr2 = B;
			while (A < endptr2)
			{
				v1 = *B * cos + *(B + 1) * sin;
				v2 = *B * sin - *(B + 1) * cos;
				*B = (*A + v1);
				*(A++) = *(B++) - 2 * v1;
				*B = (*A - v2);
				*(A++) = *(B++) + 2 * v2;
			}
			A = B;
			B += ButterfliesPerGroup * 2;
			sptr += 2;
		}
		ButterfliesPerGroup >>= 1;
	}
	/* Massage output to get the output for a real input sequence. */
	br1 = h->BitReversed + 1;
	br2 = h->BitReversed + h->Points - 1;

	while (br1 < br2)
	{
		sin = h->SinTable[*br1];
		cos = h->SinTable[*br1 + 1];
		A = buffer + *br1;
		B = buffer + *br2;
		HRplus = (HRminus = *A - *B) + (*B * 2);
		HIplus = (HIminus = *(A + 1) - *(B + 1)) + (*(B + 1) * 2);
		v1 = (sin*HRminus - cos * HIplus);
		v2 = (cos*HRminus + sin * HIplus);
		*A = (HRplus + v1) * (fft_type)0.5;
		*B = *A - v1;
		*(A + 1) = (HIminus + v2) * (fft_type)0.5;
		*(B + 1) = *(A + 1) - HIminus;

		br1++;
		br2--;
	}
	/* Handle the center bin (just need a conjugate) */
	A = buffer + *br1 + 1;
	*A = -*A;
	/* Handle DC bin separately - and ignore the Fs/2 bin
	buffer[0]+=buffer[1];
	buffer[1]=(fft_type)0;*/
	/* Handle DC and Fs/2 bins separately */
	/* Put the Fs/2 value into the imaginary part of the DC bin */
	v1 = buffer[0] - buffer[1];
	buffer[0] += buffer[1];
	buffer[1] = v1;
}

void RealFFT(size_t NumSamples, FFTParam *hFFT, const float *RealIn, float *RealOut, float *ImagOut, float *tmpBuffer) {
	//auto hFFT = GetFFT(NumSamples);
	//Floats pFFT{ NumSamples };
	float* pFFT = tmpBuffer;
	// Copy the data into the processing buffer
	for (size_t i = 0; i < NumSamples; i++)
		pFFT[i] = RealIn[i];

	// Perform the FFT
	RealFFTf(pFFT, hFFT);

	// Copy the data into the real and imaginary outputs
	for (size_t i = 1; i < (NumSamples / 2); i++) {
		RealOut[i] = pFFT[hFFT->BitReversed[i]];
		ImagOut[i] = pFFT[hFFT->BitReversed[i] + 1];
	}
	// Handle the (real-only) DC and Fs/2 bins
	RealOut[0] = pFFT[0];
	RealOut[NumSamples / 2] = pFFT[1];
	ImagOut[0] = ImagOut[NumSamples / 2] = 0;
	// Fill in the upper half using symmetry properties
	for (size_t i = NumSamples / 2 + 1; i < NumSamples; i++) {
		RealOut[i] = RealOut[NumSamples - i];
		ImagOut[i] = -ImagOut[NumSamples - i];
	}
}


/* Description: This routine performs an inverse FFT to real data.
*              This code is for floating point data.
*
*  Note: Output is BIT-REVERSED! so you must use the BitReversed to
*        get legible output, (i.e. wave[2*i]   = buffer[ BitReversed[i] ]
*                                  wave[2*i+1] = buffer[ BitReversed[i]+1 ] )
*        Input is in normal order, interleaved (real,imaginary) complex data
*        You must call GetFFT(fftlen) first to initialize some buffers!
*
* Input buffer[0] is the DC bin, and input buffer[1] is the Fs/2 bin
* - this can be done because both values will always be real only
* - this allows us to not have to allocate an extra complex value for the Fs/2 bin
*
*  Note: The scaling on this is done according to the standard FFT definition,
*        so a unit amplitude DC signal will output an amplitude of (N)
*        (Older revisions would progressively scale the input, so the output
*        values would be similar in amplitude to the input values, which is
*        good when using fixed point arithmetic)
*/
void InverseRealFFTf(fft_type *buffer, const FFTParam *h)
{
	fft_type *A, *B;
	const fft_type *sptr;
	const fft_type *endptr1, *endptr2;
	const int *br1;
	fft_type HRplus, HRminus, HIplus, HIminus;
	fft_type v1, v2, sin, cos;

	auto ButterfliesPerGroup = h->Points / 2;

	/* Massage input to get the input for a real output sequence. */
	A = buffer + 2;
	B = buffer + h->Points * 2 - 2;
	br1 = h->BitReversed + 1;
	while (A < B)
	{
		sin = h->SinTable[*br1];
		cos = h->SinTable[*br1 + 1];
		HRplus = (HRminus = *A - *B) + (*B * 2);
		HIplus = (HIminus = *(A + 1) - *(B + 1)) + (*(B + 1) * 2);
		v1 = (sin*HRminus + cos * HIplus);
		v2 = (cos*HRminus - sin * HIplus);
		*A = (HRplus + v1) * (fft_type)0.5;
		*B = *A - v1;
		*(A + 1) = (HIminus - v2) * (fft_type)0.5;
		*(B + 1) = *(A + 1) - HIminus;

		A += 2;
		B -= 2;
		br1++;
	}
	/* Handle center bin (just need conjugate) */
	*(A + 1) = -*(A + 1);
	/* Handle DC bin separately - this ignores any Fs/2 component
	buffer[1]=buffer[0]=buffer[0]/2;*/
	/* Handle DC and Fs/2 bins specially */
	/* The DC bin is passed in as the real part of the DC complex value */
	/* The Fs/2 bin is passed in as the imaginary part of the DC complex value */
	/* (v1+v2) = buffer[0] == the DC component */
	/* (v1-v2) = buffer[1] == the Fs/2 component */
	v1 = 0.5f*(buffer[0] + buffer[1]);
	v2 = 0.5f*(buffer[0] - buffer[1]);
	buffer[0] = v1;
	buffer[1] = v2;

	/*
	*  Butterfly:
	*     Ain-----Aout
	*         \ /
	*         / \
	*     Bin-----Bout
	*/

	endptr1 = buffer + h->Points * 2;

	while (ButterfliesPerGroup > 0)
	{
		A = buffer;
		B = buffer + ButterfliesPerGroup * 2;
		sptr = h->SinTable;

		while (A < endptr1)
		{
			sin = *(sptr++);
			cos = *(sptr++);
			endptr2 = B;
			while (A < endptr2)
			{
				v1 = *B * cos - *(B + 1) * sin;
				v2 = *B * sin + *(B + 1) * cos;
				*B = (*A + v1) * (fft_type)0.5;
				*(A++) = *(B++) - v1;
				*B = (*A + v2) * (fft_type)0.5;
				*(A++) = *(B++) - v2;
			}
			A = B;
			B += ButterfliesPerGroup * 2;
		}
		ButterfliesPerGroup >>= 1;
	}
}

void ReorderToTime(const FFTParam *hFFT, const fft_type *buffer, fft_type *TimeOut)
{
	// Copy the data into the real outputs
	for (size_t i = 0; i < hFFT->Points; i++) {
		TimeOut[i * 2] = buffer[hFFT->BitReversed[i]];
		TimeOut[i * 2 + 1] = buffer[hFFT->BitReversed[i] + 1];
	}
}

/*
 * InverseRealFFT
 *
 * This function computes the inverse of RealFFT, above.
 * The RealIn and ImagIn is assumed to be conjugate-symmetric
 * and as a result the output is purely real.
 * Only the first half of RealIn and ImagIn are used due to this
 * symmetry assumption.
 *
 * This is merely a wrapper of InverseRealFFTf() from RealFFTf.h.
 */
void InverseRealFFT(size_t NumSamples, FFTParam *hFFT, const float *RealIn, const float *ImagIn,
	float *RealOut, float *tmpBuffer)
{
	//auto hFFT = GetFFT(NumSamples);
	//Floats pFFT{ NumSamples };
	float *pFFT = tmpBuffer;
	// Copy the data into the processing buffer
	for (size_t i = 0; i < (NumSamples / 2); i++)
		pFFT[2 * i] = RealIn[i];
	if (ImagIn == NULL) {
		for (size_t i = 0; i < (NumSamples / 2); i++)
			pFFT[2 * i + 1] = 0;
	}
	else {
		for (size_t i = 0; i < (NumSamples / 2); i++)
			pFFT[2 * i + 1] = ImagIn[i];
	}
	// Put the fs/2 component in the imaginary part of the DC bin
	pFFT[1] = RealIn[NumSamples / 2];

	// Perform the FFT
	InverseRealFFTf(pFFT, hFFT);

	// Copy the data to the (purely real) output buffer
	ReorderToTime(hFFT, pFFT, RealOut);
}