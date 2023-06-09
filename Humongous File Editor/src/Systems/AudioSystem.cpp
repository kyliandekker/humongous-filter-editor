#include "Systems/AudioSystem.h"

#include <xaudio2.h>
#include <iostream>

HumongousFileEditor::AudioSystem HumongousFileEditor::audioSystem;

namespace HumongousFileEditor
{
	AudioSystem::AudioSystem()
	{
		if (m_Engine != nullptr)
			return;

		HRESULT hr;

		m_Engine = nullptr;
		if (FAILED(hr = XAudio2Create(&m_Engine, 0, XAUDIO2_DEFAULT_PROCESSOR)))
		{
			std::cout << "Creating XAudio2 failed." << std::endl;
			return;
		}

		m_MasterVoice = nullptr;
		if (FAILED(hr = m_Engine->CreateMasteringVoice(&m_MasterVoice)))
		{
			std::cout << "Creating XAudio2 Mastering Voice failed." << std::endl;
			return;
		}

		WAVEFORMATEX wfx;

		wfx.wFormatTag = 1;
		wfx.nChannels = 1;
		wfx.nSamplesPerSec = 11025;
		wfx.nAvgBytesPerSec = 11025;
		wfx.nBlockAlign = 1;
		wfx.wBitsPerSample = 8;
		wfx.cbSize = 0;

		if (FAILED(hr = m_Engine->CreateSourceVoice(&m_SourceVoice, &wfx)))
			return;

		if (FAILED(hr = m_SourceVoice->Start(0)))
			return;
	}

	AudioSystem::~AudioSystem()
	{
		m_MasterVoice->DestroyVoice();
		m_Engine->Release();

		CoUninitialize();
	}

	void AudioSystem::Play(unsigned char* data, uint32_t size)
	{
		m_SourceVoice->Stop(0);
		m_SourceVoice->FlushSourceBuffers();
		m_SourceVoice->Start(0);

		HRESULT hr;

		XAUDIO2_BUFFER xaBuffer{};
		xaBuffer.pAudioData = data;
		xaBuffer.AudioBytes = size;
		if (FAILED(hr = m_SourceVoice->SubmitSourceBuffer(&xaBuffer)))
			std::cout << "Failed to play." << std::endl;
	}

	void AudioSystem::Stop()
	{
		m_SourceVoice->Stop(0);
		m_SourceVoice->FlushSourceBuffers();
		m_SourceVoice->Start(0);
	}
}