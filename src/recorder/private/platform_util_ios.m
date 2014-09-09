#include "platform_util.h"
#include "raw_encoder.h"
#include "opus_encoder.h"
#include "mem.h"

#include <Foundation/Foundation.h>

void drCreateEncoder(drEncoder* encoder)
{
    //TODO: aac encoder
    if (0)
    {
        //raw
        drRawEncoder* rawEncoder = DR_MALLOC(sizeof(drRawEncoder), "raw encoder");
        memset(rawEncoder, 0, sizeof(drRawEncoder));
        encoder->encoderData = rawEncoder;
        encoder->cancelCallback = drRawEncoder_cancel;
        encoder->finishCallback = drRawEncoder_finish;
        encoder->initCallback = drRawEncoder_init;
        encoder->writeCallback = drRawEncoder_write;
    }
    else
    {
        //opus
        drOpusEncoder* opusEncoder = DR_MALLOC(sizeof(drOpusEncoder), "opus encoder");
        memset(opusEncoder, 0, sizeof(drOpusEncoder));
        encoder->encoderData = opusEncoder;
        encoder->cancelCallback = drOpusEncoder_cancel;
        encoder->finishCallback = drOpusEncoder_finish;
        encoder->initCallback = drOpusEncoder_init;
        encoder->writeCallback = drOpusEncoder_write;
    }
}