#include "src/sid.h"
#include "winresid.h"

using namespace reSID;

#define SOUND_FREQ_PAL_C64 (985248)
#define SOUND_FREQ_PAL_TED (886724)
unsigned int model = 0;
unsigned int master_clock = SOUND_FREQ_PAL_C64;
SID* sid = 0;
cycle_count cycles_remained = 0;

void DLL_EXPORT sidCreate(unsigned int clock_type, unsigned int model, unsigned int replayFreq)
{
	if (!sid)
		sid = new reSID::SID();// model, 0);
	master_clock = clock_type;
	sid->set_sampling_parameters(master_clock, SAMPLE_RESAMPLE_FASTMEM, replayFreq);
	sid->set_chip_model((chip_model)(model & 1));
	cycles_remained = 0;
}

void DLL_EXPORT sidDestroy()
{
	if (sid) {
		delete sid;
		sid = 0;
	}
}

void DLL_EXPORT sidSetSampleRate(unsigned int sampleRate_)
{
	if (sid)
		sid->set_sampling_parameters(master_clock, SAMPLE_RESAMPLE_FASTMEM, sampleRate_);
}

void DLL_EXPORT sidReset()
{
	if (sid)
		sid->reset();
}

void DLL_EXPORT sidPause()
{
	//
}

void DLL_EXPORT sidWriteReg(unsigned int reg, unsigned char value)
{
	if (sid)
		sid->write(reg & 0x1F, value);
}

unsigned char DLL_EXPORT sidReadReg(unsigned int reg)
{
	if (sid)
		return sid->read(reg & 0x1F);
	return 0xff;
}

void DLL_EXPORT sidCalcSamples(short* buf, long count)
{
	if (sid) {
		const cycle_count cycles_per_sample = sid->get_cycles_per_sample();

		while (count--) {
			cycle_count cycles_to_do = (cycles_per_sample + cycles_remained) >> 16;
			cycles_remained += cycles_per_sample - (cycles_to_do << 16);
			sid->clock(cycles_to_do);
			*buf++ = sid->output() >> 1;
		}
	}
	else {
		while (count--)
			buf[count] = 0;
	}
}
