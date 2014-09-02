#ifndef DR_INSTANCE_H
#define DR_INSTANCE_H

/*! \file */

#include "kowalski.h"
#include "tinycthread.h"
#include "messagequeue.h"
#include "digger_recorder.h"
#include "level_meter.h"
#include "analyzer.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
  
    #define MAX_NUM_ANALYZER_SLOTS 16
    #define MAX_NUM_INPUT_CHANNELS 1
    #define MAX_NUM_OUTPUT_CHANNELS 2
    
    
    typedef struct drAnalyzerSlot
    {
        void* analyzerData;
        drAnalyzerAudioCallback audioCallback;
        drAnalyzerDeinitCallback deinitCallback;
    } drAnalyzerSlot;
    
    /**
     * A Digger recorder instance.
     */
    typedef struct drInstance
    {
        drAnalyzerSlot inputAnalyzerSlots[MAX_NUM_ANALYZER_SLOTS];
        
        float sampleRate;
        kwlDSPUnitHandle inputDSPUnit;
        kwlDSPUnitHandle outputDSPUnit;
        int firstSampleHasPlayed;
        
        mtx_t sharedEventQueueLock;
        drMessageQueue* outgoingEventQueueShared;
        drMessageQueue* outgoingEventQueueMain;
        drMessageQueue* outgoingEventQueueAudio;
        
        drEventCallback eventCallback;
        void* eventCallbackData;
        
        //Audio analyzers
        drLevelMeter inputLevelMeters[MAX_NUM_INPUT_CHANNELS];
        drLevelMeter outputLevelMeters[MAX_NUM_OUTPUT_CHANNELS];
        
    } drInstance;
    
    void drInstance_init(drInstance* instance, drEventCallback eventCallback, void* eventCallbackUserData);
    
    void drInstance_deinit(drInstance* instance);
    
    void drInstance_update(drInstance* instance, float timeStep);
    
    void drInstance_getInputLevels(drInstance* instance, int channel, int logLevels, drLevels* result);
    
    /**
     * Returns 0 on success, or non-zero if there is no free analyzer slot.
     */
    int drInstance_addInputAnalyzer(drInstance* instance,
                                    void* analyzerData,
                                    drAnalyzerAudioCallback audioCallback,
                                    drAnalyzerDeinitCallback deinitCallback);
    
    /**
     * Must be called <strong>only from the audio thread</strong>!
     */
    void drInstance_enqueueEventFromAudioToMainThread(drInstance* instance, const drEvent* event);
    
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DR_INSTANCE_H */