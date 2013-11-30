#ifndef __IRR_EXTENSION_MIDI_UTILS_H__
#define __IRR_EXTENSION_MIDI_UTILS_H__

/// Irrlicht-Engine
#include <irrlicht.h>

namespace irr
{
	class MidiTools
	{
	public:
		virtual core::stringc getNameFromNote( s32 midiNote, bool major = true) const;
		virtual s32 getNoteFromName( const irr::core::stringc& name ) const;
		virtual bool isBlackKey( s32 midiNote ) const;
		virtual bool isBlackKey( const irr::core::stringc& name ) const;
		virtual bool isWhiteKey( s32 midiNote ) const;
		virtual bool isWhiteKey( const irr::core::stringc& name ) const;
		virtual s32 getNoteCount( s32 startNote, s32 endNote ) const;
		virtual s32 getNoteCount( const irr::core::stringc& startNote, const irr::core::stringc& endNote ) const;
		virtual f32 getFrequencyFromNote( s32 midiNote ) const;
		virtual s32	getNoteFromFrequency( f32 frequency ) const;
		virtual s32 getWhiteKeyCount( s32 startNote, s32 endNote ) const;
		virtual s32 getWhiteKeyCount( const irr::core::stringc& startNote, const irr::core::stringc& endNote ) const;
		virtual s32 getBlackKeyCount( s32 startNote, s32 endNote ) const;
		virtual s32 getBlackKeyCount( const irr::core::stringc& startNote, const irr::core::stringc& endNote ) const;
	};

	void TestMidi(ITimer* timer, ILogger* logger);

} // end namespace irr

#endif // IRRMIDI_H
