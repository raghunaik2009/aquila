/**
 * @file WaveFile.h
 *
 * Handling WAVE files - header.
 *
 * WaveFile class enables .wav file header and data access, either
 * per sample or per frame.
 *
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @version 2.5.0
 * @since 0.0.7
 */

#ifndef WAVEFILE_H_
#define WAVEFILE_H_

#include "global.h"
#include "Frame.h"
#include <string>
#include <vector>

// FIXME: safer 8b and 16b types!
#ifndef _WORD
typedef unsigned int _DWORD;
typedef unsigned short _WORD;
#endif

namespace Aquila
{
    /**
     * .wav file header structure.
     */
    struct AQUILA_EXPORT WaveHeader
    {
        char   RIFF[4];
        _DWORD  DataLength;
        char   WAVE[4];
        char   fmt_[4];
        _DWORD  SubBlockLength;
        _WORD   formatTag;
        _WORD   Channels;
        _DWORD  SampFreq;
        _DWORD  BytesPerSec;
        _WORD   BytesPerSamp;
        _WORD   BitsPerSamp;
        char   data[4];
        _DWORD  WaveSize;
    };


    /**
     * Which channel to use when reading stereo recordings.
     */
    enum StereoDataSource { LEFT_CHANNEL, RIGHT_CHANNEL };


    /**
     * Wave file data access.
     */
    class AQUILA_EXPORT WaveFile
    {
    public:
        /**
         * Audio channel representation as an integer vector.
         */
        typedef std::vector<int> channelType;

        /**
         * Data from both channels.
         */
        channelType LChTab, RChTab;

        /**
         * Pointers to signal frames.
         */
        std::vector<Frame*> frames;

        explicit WaveFile(unsigned int frameLengthMs = 0,
                double frameOverlap = 0.66);
        ~WaveFile();

        void load(const std::string& file);

        /**
         * Returns the filename.
         *
         * @return full path to currently loaded file
         */
        std::string getFilename() const { return filename; }

        /**
         * Returns number of channels.
         *
         * @return 1 for mono, 2 for stereo, other types are not recognized
         */
        unsigned short getChannelsNum() const { return hdr.Channels; }

        /**
         * Returns signal sample frequency.
         *
         * @return sample frequency in Hz
         */
        unsigned int getSampleFrequency() const { return hdr.SampFreq; }

        /**
         * Returns the number of bytes per second.
         *
         * @return product of sample frequency and bytes pare sample
         */
        unsigned int getBytesPerSec() const { return hdr.BytesPerSec; }

        /**
         * Returns number of bytes per sample.
         *
         * @return 1 for 8b-mono, 2 for 8b-stereo or 16b-mono, 4 dor 16b-stereo
         */
        unsigned int getBytesPerSamp() const { return hdr.BytesPerSamp; }

        /**
         * Returns number of bits per sample
         *
         * @return 8 or 16
         */
        unsigned int getBitsPerSamp() const { return hdr.BitsPerSamp; }

        /**
         * Returns the recording size (without header).
         *
         * The return value is a raw byte count. To know the real sample count,
         * it must be divided by bytes per sample.
         *
         * @return byte count
         */
        unsigned int getWaveSize() const { return hdr.WaveSize; }

        /**
         * Returns the real data length.
         *
         * @return left channel vector size
         */
        unsigned int getSamplesCount() const { return LChTab.size(); }

        unsigned int getAudioLength() const;

        /**
         * Returns a pointer to data table.
         *
         * Because vector guarantees to be contiguous in memory, we can
         * return the address of the first element in the vector.
         * It is valid only before next operation which modifies the vector,
         * but as we use it only to copy that memory to another buffer,
         * we can do that safely.
         *
         * @return address of the first element
         */
        int* getData() { return &LChTab[0]; }

        /**
         * Returns a const reference to channel source.
         *
         * @param source which channel to use as a source
         * @return source vector
         */
        const channelType& getDataVector(StereoDataSource source = LEFT_CHANNEL) const
            { return (source == LEFT_CHANNEL) ? LChTab : RChTab; }

        void saveFrames(const std::string& filename,
                        unsigned int begin,
                        unsigned int end) const;

        /**
         * Returns number of frames in the file.
         *
         * @return frame vector length
         */
        unsigned int getFramesCount() const { return frames.size(); }


        /**
         * Returns number of samples in a single frame.
         *
         * @return samples per frame = bytes per frame / bytes per sample
         */
        unsigned int getSamplesPerFrame() const
        {
            unsigned int bytesPerFrame = static_cast<unsigned int>(
                    hdr.BytesPerSec * frameLength / 1000.0);

            return bytesPerFrame / hdr.BytesPerSamp;
        }

        /**
         * Returns frame length (in samples) after zero padding (ZP).
         *
         * @return padded frame length is a power of 2
         */
        unsigned int getSamplesPerFrameZP() const { return zeroPaddedLength; }

        void recalculate(unsigned int newFrameLength = 0, double newOverlap = 0.66);

    private:
        /**
         * Full path of the .wav file.
         */
        std::string filename;

        /**
         * Header structure.
         */
        WaveHeader hdr;

        /**
         * Number of samples per frame.
         */
        unsigned int samplesPerFrame;

        /**
         * Frame length (in milliseconds).
         */
        unsigned int frameLength;

        /**
         * Overlap between frames - fraction of frame length (0 < overlap < 1).
         */
        double overlap;

        /**
         * Next power of 2 larger than number of samples per frame.
         */
        unsigned int zeroPaddedLength;

        void loadHeader(std::fstream& file);
        void loadRawData(std::fstream& file, short* buffer, int bufferLength);
        void convert16Stereo(short* data, unsigned int channelSize);
        void convert16Mono(short* data, unsigned int channelSize);
        void convert8Stereo(short* data, unsigned int channelSize);
        void convert8Mono(short* data, unsigned int channelSize);
        void splitBytes(short twoBytes, unsigned char& lb, unsigned char& hb);

        void divideFrames(const channelType& source);
        void clearFrames();
    };
}

#endif
