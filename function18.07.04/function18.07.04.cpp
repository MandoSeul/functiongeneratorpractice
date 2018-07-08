// function18.07.04.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//



#include "stdafx.h"
#include<fstream>
#include<iostream>
#include<vector>
#include "WavaFile.h"
#include<dmusicc.h>
using namespace std;

#define PH_2 6.28318530717958647693
#define DURATION 1
#define SAMPLE_RATE 44100 
#define CHANNEL 1 

int main()
{
	WAVE_HEADER header;
	FILE * f_out;
	int BIT_RATE = 24;
	int amplitude = 0;
	string shape = "square";
	int samplecount = SAMPLE_RATE * DURATION;
	int frequency = 1000;

	fopen_s(&f_out, "test_2.wav", "wb");

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

	vector<int32_t> data_bit;

	data_bit.reserve(samplecount);

	for (int i = 0; i < samplecount; i++)
	{
		double time = static_cast<double>(i)/ SAMPLE_RATE;

		if (BIT_RATE == 16) {
			amplitude = 32767;
			
			if(shape=="sin")
				data_bit.push_back(static_cast<int16_t>(amplitude * (sin(PH_2 * frequency * time))));
			else if (shape == "triangle") {
			
			}		
			else if (shape == "square") {
				if ((amplitude * sin(PH_2 * frequency * time) >= 0))
					data_bit.push_back(static_cast<int16_t>(amplitude));
				else
					data_bit.push_back(static_cast<int16_t>(-amplitude));
			}
			

		}
		else if (BIT_RATE == 24) {
			amplitude = 8388607;
			data_bit.push_back(static_cast<int8_t>(amplitude * (sin(PH_2 * frequency * time))));
			data_bit.push_back(static_cast<int8_t>(amplitude * (sin(PH_2 * frequency * time)))<<8);
			data_bit.push_back(static_cast<int8_t>(amplitude * (sin(PH_2 * frequency * time)))<<16);

		}
		else {
			amplitude = 2147483647;
			data_bit.push_back(static_cast<int32_t>(amplitude * (sin(PH_2 * frequency * time))));
		}
	}
	
		fwrite(&data_bit[0], sizeof(data_bit[0]), samplecount, f_out);

	fclose(f_out);

	return 0;
}
