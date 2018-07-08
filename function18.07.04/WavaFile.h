#pragma once
#define WAVE_FORMAT_PCM 0X0001; 

typedef struct {
	unsigned char ChunkID[4]; // Contains the letters "RIFF" in ASCII form unsigned 
	int ChunkSize; // This is the size of the rest of the chunk following this number unsigned 
	char Format[4]; // Contains the letters "WAVE" in ASCII form 
} RIFF;
//-------------------------------------------
// [Channel]
// - streo : [left][right]
// - 3 channel : [left][right][center]
// - quad : [front left][front right][rear left][reat right]
// - 4 channel : [left][center][right][surround] 
// - 6 channel : [left center][left][center][right center][right][surround] 
//------------------------------------------- 

typedef struct { 
unsigned char ChunkID[4]; // Contains the letters "fmt " in ASCII form 
unsigned int ChunkSize; // 16 for PCM. This is the size of the rest of the Subchunk which follows this number. 
unsigned short AudioFormat; // PCM = 1 
unsigned short NumChannels; // Mono = 1, Stereo = 2, etc.
unsigned int SampleRate; // 8000, 44100, etc. 
unsigned int AvgByteRate; // SampleRate * NumChannels * BitsPerSample/8 
unsigned short BlockAlign; // NumChannels * BitsPerSample/8 
unsigned short BitPerSample; // 8 bits = 8, 16 bits = 16, etc 
} FMT; 
typedef struct { 
	char ChunkID[4]; // Contains the letters "data" in ASCII form 
	unsigned int ChunkSize; // NumSamples * NumChannels * BitsPerSample/8
} DATA; 
typedef struct { 
	RIFF Riff;
	FMT	Fmt; 
	DATA Data; 
} WAVE_HEADER; 


class WavaFile
{
public:
	WavaFile();
	~WavaFile();
};

