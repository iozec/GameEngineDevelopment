#pragma once
#include <cstdint>
#include <map>
#include <vector>
#include <SDL3/SDL_timer.h>
#include <ctime>


// SampleData and FrameMap

struct SampleData
{
    int64_t frameTime;
    int frameReferance;
};

typedef std::map<const char*, std::vector<SampleData>> FrameMap;


// ProfilerSystem CLASS

class ProfilerSystem
{
public:
    static ProfilerSystem& Instance()
    {
        static ProfilerSystem INSTANCE;
        return INSTANCE;
    }

    ProfilerSystem();
    ~ProfilerSystem();

    void StartFrame();
    void StoreSample(const char* name, int64_t elapsedTime);
    void EndFrame();
    void WriteDataToCSV();

    FrameMap& GetFrameData() const;
    int GetCurrentFrame();
    FrameMap& GetLastFrameData() const;
    std::vector<float>& GetFrameTimes();

private:
    int currentFrame;
    FrameMap* frameData;
    std::vector<float> totalFrameTimes;
    float thisFramesTotalTime = 0;
    FrameMap* thisFramesFrameData;
    FrameMap* lastFramesFrameData;
};


// Profile struct

struct Profile
{
    Profile(const char* name)
        : _name(name)
    {
        startTime = std::clock();
    }

    ~Profile()
    {
        std::clock_t endTime = std::clock();
        std::clock_t elapsedTime = endTime - startTime;

        ProfilerSystem::Instance().StoreSample(
            _name,
            elapsedTime * (1000.0 / CLOCKS_PER_SEC)
        );
    }

    const char* _name;
    std::clock_t startTime;
};


#define PROFILE(name) Profile p(name)