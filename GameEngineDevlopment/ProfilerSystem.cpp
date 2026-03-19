#include "ProfilerSystem.h"
#include <fstream>
#include <string>

FrameMap& ProfilerSystem::GetFrameData() const
{
	return *frameData;
}

int ProfilerSystem::GetCurrentFrame()
{
	return currentFrame;
}

FrameMap& ProfilerSystem::GetLastFrameData() const
{
	return *lastFramesFrameData;
}

std::vector<float>& ProfilerSystem::GetFrameTimes()
{
	return totalFrameTimes;
}

void ProfilerSystem::WriteDataToCSV()
{
    std::ofstream CSVFile;
    CSVFile.open("../Assets/Profile.csv");

    for (auto const& [name, samples] : *frameData)
    {
        std::string frameTime = "";
        std::string frameRef = "";

        CSVFile << name << "\n";

        for (SampleData sample : samples)
        {
            frameRef += std::to_string(sample.frameReferance) + ",";
            frameTime += std::to_string(sample.frameTime) + ",";
        }

        CSVFile << "\n";
        CSVFile << frameRef << "\n";
        CSVFile << frameTime;
    }

    CSVFile << "\n";
    CSVFile.close();
}

ProfilerSystem::ProfilerSystem()
{
    frameData = new FrameMap();
    thisFramesFrameData = new FrameMap();
    lastFramesFrameData = new FrameMap();
}

ProfilerSystem::~ProfilerSystem()
{
    delete frameData;
    delete thisFramesFrameData;
    delete lastFramesFrameData;
}

void ProfilerSystem::StartFrame()
{
    currentFrame++;
    thisFramesTotalTime = 0;
}

void ProfilerSystem::StoreSample(const char* name, int64_t elapsedTime)
{
    
    SampleData sample;
    sample.frameReferance = currentFrame;
    sample.frameTime = elapsedTime;

    thisFramesTotalTime += elapsedTime;

   
    (*frameData)[name].push_back(sample);
    (*thisFramesFrameData)[name].push_back(sample);
}

void ProfilerSystem::EndFrame()
{
    totalFrameTimes.push_back(thisFramesTotalTime);

    
    *lastFramesFrameData = *thisFramesFrameData;

   
    thisFramesFrameData->clear();
}
