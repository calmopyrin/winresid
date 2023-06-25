# winreSID

## MOS 6581 / 8580 SID software emulation

This repository is a fork of the venerable reSID MOS6581 / MOS8580 
SID emulator by Dag Lem, widely used in different incarnations.

## Windows library

winreSID adds a simple C wrapper interface around reSID (C++) that
makes it possible to conveniently use it in different emulators and
applications as an optional DLL add-on.

## Interface

### sidCreate(unsigned int clock_type, unsigned int model, unsigned int replayFreq)

Create a SID  instance with given clock_type (master clock frequency), model and 
replay frequency.

### sidDestroy()

Destroy the SID instance

### sidSetSampleRate(unsigned int sampleRate_)

Change replay frequency to sampleRate_. Note, this is the sound replay frequency of 
the host application.

### sidSetModel(unsigned int model)

Set SID model to either 6581 (=0) or 8580 (!=0).

### sidReset()

Resets the SID.
### sidPause()

Pause the engine

### sidWriteReg(unsigned int reg, unsigned char value)

Write 'value' to the SID register 'reg'.

### unsigned char sidReadReg(unsigned int reg)

Read SID register 'reg'. Note, some SID registers are write-only.
The A/D ports are not implemented.

### sidCalcSamples(short* buf, long count)

Render 'count' samples to the sound buffer provided.

### short sidCalcSample()

Clock the SID engine and return one SID sound sample with the original SID frequency.

### sidSetAmp(unsigned int amp)

Set the amplification. Original SID output will be right shifted by this amount.

### const char* sidGetLibVersion()

Get the reSID library version string.

## Future plans

Plans include:
- implement support for multiple instances
- make it work as a Linux library
- add proper library support for cycle based rendering into a buffer
