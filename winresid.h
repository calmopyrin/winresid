#pragma once

#ifdef DLL_EXPORT
#define DLL_EXPORT __declspec(dllimport)
#else
#define DLL_EXPORT __declspec(dllexport)
#endif

extern "C" {

	void DLL_EXPORT sidCreate(unsigned int clock_type, unsigned int model, unsigned int replayFreq);
	void DLL_EXPORT sidDestroy();
	void DLL_EXPORT sidSetSampleRate(unsigned int sampleRate_);
	void DLL_EXPORT sidSetModel(unsigned int model);
	void DLL_EXPORT sidReset();
	void DLL_EXPORT sidPause();
	void DLL_EXPORT sidWriteReg(unsigned int reg, unsigned char value);
	unsigned char DLL_EXPORT sidReadReg(unsigned int reg);
	void DLL_EXPORT sidCalcSamples(short* buf, long count);
	short DLL_EXPORT sidCalcSample();
	void DLL_EXPORT sidSetAmp(unsigned int amp);
	const DLL_EXPORT char* sidGetLibVersion();
};
