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
#define BIT_RATE 16

int main()
{
	FILE * f_out; 
	fopen_s(&f_out, "test.wav", "wb"); 
	WAVE_HEADER header; 
	memcpy(header.Riff.ChunkID, "RIFF", 4);
	header.Riff.ChunkSize = DURATION * SAMPLE_RATE * CHANNEL * BIT_RATE / 8 + 36; 
	memcpy(header.Riff.Format, "WAVE", 4); memcpy(header.Fmt.ChunkID, "fmt ", 4); 
	header.Fmt.ChunkSize = 0x10; 
	header.Fmt.AudioFormat = WAVE_FORMAT_PCM; 
	header.Fmt.NumChannels = CHANNEL; 
	header.Fmt.SampleRate = SAMPLE_RATE; 
	header.Fmt.AvgByteRate = SAMPLE_RATE * CHANNEL * BIT_RATE / 8; 
	header.Fmt.BlockAlign = CHANNEL * BIT_RATE / 8; 
	header.Fmt.BitPerSample = BIT_RATE; 
	memcpy(header.Data.ChunkID, "data", 4); 
	header.Data.ChunkSize = DURATION * SAMPLE_RATE * CHANNEL * BIT_RATE / 8; 
	fwrite(&header, sizeof(header), 1, f_out);

	int samplerate = 44100;
	int duration = 1;
	int samplecount = samplerate * duration;
	int frequency = 1000;
	vector<int16_t> data_16bit;
	static int amplitude = 32767; 

	for (int i = 0; i < samplecount; i++)
	{
		double time = static_cast<double>(i)/ samplerate;
		data_16bit.push_back(static_cast<int16_t>(amplitude * (sin(PH_2 * frequency * time))));
		fwrite(&data_16bit[i], sizeof(int16_t),2,f_out);

	}

	fclose(f_out);
	return 0;
}

