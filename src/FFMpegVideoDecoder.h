/*
 obs-ios-camera-source
 Copyright (C) 2018    Will Townsend <will@townsend.io>
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License along
 with this program. If not, see <https://www.gnu.org/licenses/>
 */

#include <chrono>

#include "VideoDecoder.h"
#include "ffmpeg-decode.h"

class Decoder
{
    struct ffmpeg_decode decode;
    
public:
    inline Decoder() { memset(&decode, 0, sizeof(decode)); }
    inline ~Decoder() { ffmpeg_decode_free(&decode); }
    
    inline operator ffmpeg_decode *() { return &decode; }
    inline ffmpeg_decode *operator->() { return &decode; }
};

class FFMpegVideoDecoderCallback {
public:
    virtual ~FFMpegVideoDecoderCallback() {}
    
//    virtual void VideoToolboxDecodedFrame(CVPixelBufferRef aImage, CMVideoFormatDescriptionRef formatDescription) = 0;
};

class FFMpegVideoDecoder: public VideoDecoder
{
public:
    FFMpegVideoDecoder();
    ~FFMpegVideoDecoder();
    
    void Init() override;
    
    void Input(std::vector<char> packet) override;
    
    void Flush() override;
    void Drain() override;
    void Shutdown() override;
        
//    FFMpegVideoDecoderCallback *mDelegate;
    
    obs_source_t *source;

private:
    
    obs_source_frame frame;
    Decoder video_decoder;
    
};