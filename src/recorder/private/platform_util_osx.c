#include "platform_util.h"
#include "raw_encoder.h"
#include "opus_encoder.h"
#include "mem.h"
#include "assert.h"

void wave_create_encoder(WaveEncoder* encoder, WaveSettings* settings)
{
    if (settings->encoderFormat == WAVE_ENCODER_FORMAT_RAW)
    {
        //raw
        WaveRawEncoder* rawEncoder = WAVE_MALLOC(sizeof(WaveRawEncoder), "raw encoder");
        memset(rawEncoder, 0, sizeof(WaveRawEncoder));
        encoder->encoderData = rawEncoder;
        encoder->stopCallback = wave_raw_encoder_stop;
        encoder->initCallback = wave_raw_encoder_init;
        encoder->writeCallback = wave_raw_encoder_write;
    }
    else if (settings->encoderFormat == WAVE_ENCODER_FORMAT_OPUS)
    {
        //opus
        WaveOpusEncoder* opusEncoder = WAVE_MALLOC(sizeof(WaveOpusEncoder), "opus encoder");
        memset(opusEncoder, 0, sizeof(WaveOpusEncoder));
        encoder->encoderData = opusEncoder;
        encoder->stopCallback = wave_opus_encoder_stop;
        encoder->initCallback = wave_opus_encoder_init;
        encoder->writeCallback = wave_opus_encoder_write;
    }
    else
    {
        assert(0 && "unknown encoder type");
    }
}
