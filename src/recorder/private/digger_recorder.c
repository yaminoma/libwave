#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "assert.h"
#include "kowalski.h"

#include "digger_recorder.h"
#include "messagequeue.h"
#include "tinycthread.h"
#include "instance.h"
#include "mem.h"

const char* drNotificationTypeToString(drNotificationType type)
{
    switch (type)
    {
        case DR_DID_START_AUDIO_STREAM:
        {
            return "audio stream started";
        }
        case DR_RECORDING_STARTED:
        {
            return "recording started";
        }
        case DR_RECORDING_PAUSED:
        {
            return "recording paused";
        }
        case DR_RECORDING_RESUMED:
        {
            return "recording resumed";
        }
        case DR_RECORDING_FINISHED:
        {
            return "recording finished";
        }
        case DR_RECORDING_CANCELED:
        {
            return "recording canceled";
        }
        default:
        {
            break;
        }
    }
    
    return "unknown notification type";
}

static drInstance* instance = NULL;

drError drInitialize(drNotificationCallback notificationCallback, void* notificationCallbackUserData)
{
    if (instance)
    {
        return DR_ALREADY_INITIALIZED;
    }
    
    instance = DR_MALLOC(sizeof(drInstance), "Digger recorder instance");
    drInstance_init(instance, notificationCallback, notificationCallbackUserData);
    
    
    return DR_NO_ERROR;
}

drError drDeinitialize()
{
    if (!instance)
    {
        return DR_NOT_INITIALIZED;
    }
    
    drInstance_deinit(instance);
    DR_FREE(instance);
    
    return DR_NO_ERROR;
}

drError drUpdate(float timeStep)
{
    if (!instance)
    {
        return DR_NOT_INITIALIZED;
    }
    
    drInstance_update(instance, timeStep);
    
    return DR_NO_ERROR;
}

drError drGetInputLevels(int channel, int logLevels, drLevels* result)
{
    if (!instance)
    {
        return DR_NOT_INITIALIZED;
    }
    
    drInstance_getInputLevels(instance, channel, logLevels, result);
    
    return DR_NO_ERROR;
}

drError drStartRecording()
{
    if (!instance)
    {
        return DR_NOT_INITIALIZED;
    }
    
    drInstance_enqueueControlEventOfType(instance, DR_START_RECORDING);
    
    return DR_NO_ERROR;
}

drError drCancelRecording()
{
    if (!instance)
    {
        return DR_NOT_INITIALIZED;
    }
    
    drInstance_enqueueControlEventOfType(instance, DR_CANCEL_RECORDING);
    
    return DR_NO_ERROR;
}

drError drFinishRecording()
{
    if (!instance)
    {
        return DR_NOT_INITIALIZED;
    }
    
    drInstance_enqueueControlEventOfType(instance, DR_FINISH_RECORDING);
    
    return DR_NO_ERROR;
}

drError drPauseRecording()
{
    if (!instance)
    {
        return DR_NOT_INITIALIZED;
    }
    
    drInstance_enqueueControlEventOfType(instance, DR_PAUSE_RECORDING);
    
    return DR_NO_ERROR;
}

drError drResumeRecording()
{
    if (!instance)
    {
        return DR_NOT_INITIALIZED;
    }
    
    drInstance_enqueueControlEventOfType(instance, DR_RESUME_RECORDING);
    
    return DR_NO_ERROR;
}