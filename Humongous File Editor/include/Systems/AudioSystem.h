#pragma once

#include <cstdint>

class IXAudio2;
class IXAudio2MasteringVoice;
class IXAudio2SourceVoice;

namespace HumongousFileEditor
{
	class AudioSystem
	{
	public:
		AudioSystem();
		~AudioSystem();

		/// <summary>
		/// Plays a piece of pcm data.
		/// </summary>
		/// <param name="data">The pcm data.</param>
		/// <param name="size">The size of the data.</param>
		void Play(unsigned char* data, uint32_t size);
		/// <summary>
		/// Stops the playback of the source voice.
		/// </summary>
		void Stop();

	private:
		IXAudio2* m_Engine = nullptr;
		IXAudio2MasteringVoice* m_MasterVoice = nullptr;
		IXAudio2SourceVoice* m_SourceVoice = nullptr;
	};
	extern AudioSystem audioSystem;
}