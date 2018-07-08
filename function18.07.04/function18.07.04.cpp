// function18.07.04.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//



#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<vector>
#include "WavaFile.h"
using namespace std;

#define PH_2 6.28318530717958647693
#define DURATION 1
#define SAMPLE_RATE 44100 
#define CHANNEL 1 
#define BIT_RATE_16 16
#define BIT_RATE_32 32

#define amplitude_16 32767
#define amplitude_32 2147483647

int main()
{
	FILE * f_out_16, * f_out_32; 
	fopen_s(&f_out_16, "test_16.wav", "wb"); 
	fopen_s(&f_out_32, "test_32.wav", "wb");
	WAVE_HEADER header_16; 
	WAVE_HEADER header_32;
	// header_16
	memcpy(header_16.Riff.ChunkID, "RIFF", 4);
	header_16.Riff.ChunkSize = DURATION * SAMPLE_RATE * CHANNEL * BIT_RATE_16 / 8 + 36;
	memcpy(header_16.Riff.Format, "WAVE", 4); memcpy(header_16.Fmt.ChunkID, "fmt ", 4);
	header_16.Fmt.ChunkSize = 0x10;
	header_16.Fmt.AudioFormat = WAVE_FORMAT_PCM;
	header_16.Fmt.NumChannels = CHANNEL;
	header_16.Fmt.SampleRate = SAMPLE_RATE;
	header_16.Fmt.AvgByteRate = SAMPLE_RATE * CHANNEL * BIT_RATE_16 / 8;
	header_16.Fmt.BlockAlign = CHANNEL * BIT_RATE_16 / 8;
	header_16.Fmt.BitPerSample = BIT_RATE_16;
	memcpy(header_16.Data.ChunkID, "data", 4);
	header_16.Data.ChunkSize = DURATION * SAMPLE_RATE * CHANNEL * BIT_RATE_16 / 8;

	//header_32
	memcpy(header_32.Riff.ChunkID, "RIFF", 4);
	header_32.Riff.ChunkSize = DURATION * SAMPLE_RATE * CHANNEL * BIT_RATE_32 / 8 + 36;
	memcpy(header_32.Riff.Format, "WAVE", 4); memcpy(header_32.Fmt.ChunkID, "fmt ", 4);
	header_32.Fmt.ChunkSize = 0x10;
	header_32.Fmt.AudioFormat = WAVE_FORMAT_PCM;
	header_32.Fmt.NumChannels = CHANNEL;
	header_32.Fmt.SampleRate = SAMPLE_RATE;
	header_32.Fmt.AvgByteRate = SAMPLE_RATE * CHANNEL * BIT_RATE_32 / 8;
	header_32.Fmt.BlockAlign = CHANNEL * BIT_RATE_32 / 8;
	header_32.Fmt.BitPerSample = BIT_RATE_32;
	memcpy(header_32.Data.ChunkID, "data", 4);
	header_32.Data.ChunkSize = DURATION * SAMPLE_RATE * CHANNEL * BIT_RATE_32 / 8;

	fwrite(&header_16, sizeof(header_16), 1, f_out_16);
	fwrite(&header_32, sizeof(header_32), 1, f_out_32);

	int samplecount = SAMPLE_RATE * DURATION;
	int frequency = 1000;

	vector<int16_t> data_16bit;
	vector<int32_t> data_32bit;

	data_16bit.reserve(samplecount);
	data_32bit.reserve(samplecount);

	for (int i = 0; i < samplecount; i++)
	{
		double time = static_cast<double>(i)/ SAMPLE_RATE;
		data_16bit.push_back(static_cast<int16_t>(amplitude_16 * (sin(PH_2 * frequency * time))));
		data_32bit.push_back(static_cast<int32_t>(amplitude_32*(sin(PH_2*frequency*time))));
		
	}
	fwrite(&data_16bit[0], sizeof(data_16bit[0]), samplecount, f_out_16);
	fwrite(&data_32bit[0], sizeof(data_32bit[0]), samplecount, f_out_32);

	fclose(f_out_16);
	fclose(f_out_32);

	return 0;
}

