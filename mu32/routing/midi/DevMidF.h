// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krauße
// MIDI-File als Device
// ------------------------------------------------------------------

#ifndef DEVMIDF_H
#define DEVMIDF_H

#include <fstream>

#include "Device.h"

#ifdef WX
#include "mhArray.h"
WX_DEFINE_ARRAY_INT(BYTE, TBYTEBase1);
DEF_MHARRAY(BYTE, TByteArray, TBYTEBase1);
#else
#include <classlib/arrays.h>
typedef TArray<BYTE> TByteArray;
#endif

// Track ------------------------------------------------------------

class Track
{

public:
	DWORD Time;
	TByteArray *Data;
	Track()
	{
		Time = 0;
		Data = new TByteArray(100, 0, 100);
	}

	~Track()
	{
		delete Data;
	}

	void WriteDelta();
	void MidiOut3(BYTE c1, BYTE c2, BYTE c3)
	{
		WriteDelta();
		Data->Add(c1);
		Data->Add(c2);
		Data->Add(c3);
	}

	void MidiOut2(BYTE c1, BYTE c2)
	{
		WriteDelta();
		Data->Add(c1);
		Data->Add(c2);
	}

	void Save(mutOFstream &os);
	void Add(BYTE c)
	{
		Data->Add(c);
	}
};

typedef struct TAK1
{
	int taste;
	int key;
	int fine;
	DWORD id;         // (channel << 24) +(Route->Id << 16) + (Box << 8) + Taste
	// zum Identifizieren fürs korrekte Ausschalten
}

TonAufKanal1;

// OutMidiFile ------------------------------------------------------

class OutMidiFile : public OutDevice
{
	int bending_range;
public:

        OutMidiFile(): OutDevice(), bending_range (2) {}

	OutMidiFile(const wxString &name, int devId, int bendingRange = 2)
			: OutDevice(devId, name)
	{
		bending_range = bendingRange;
	}

	virtual ~OutMidiFile()
	{};
	
	/// Save current device settings in a tree storage
	/** \argument config (tree_storage) storage class, where the data will be saved.
	 */
	virtual void Save (tree_storage & config);
	
	/// Save route settings (filter settings) for a given route
	/** Some route settings (e.g. filter settings) are device type 
	 * specific. This function saves them in a tree storage.
	 * \argument config (tree_storage *) Storage class, where the data will be saved.
	 * \argument route (Route *) Route whos data shall be saved.
	 */
	virtual void Save (tree_storage & config, const Route * route);
	
	
	/// Load current device settings from a tree storage
	/** \argument config (tree_storage) storage class, where the data will be loaded from.
	 */
	virtual void Load (tree_storage & config);
	
	/// Loade route settings (filter settings) for a given route
	/** Some route settings (e.g. filter settings) are device type 
	 * specific. This function loads them from a tree storage.
	 * \argument config (tree_storage *) Storage class, where the data will be restored from.
	 * \argument route (Route *) Route whos data shall be loaded.
	 */
	virtual void Load (tree_storage & config, Route * route);

	
	virtual bool Open();
	virtual void Close();
	virtual void NoteOn(int box, int taste, int velo, Route *r, int channel, ChannelData *cd);
	virtual void NoteOff(int box, int taste, int velo, Route *r, int channel);
	virtual void NotesCorrect(int box);
	virtual void Sustain(char on, int channel);
	virtual int  GetChannel(int taste)
	{
		return -1;
	} // hier kˆnnte man auch den richtigen Wett ausgeben, macht aber nixcht so viel Sinn

	virtual void Gis(GisToken *token, char turn)
	{};

	virtual void AddTime(frac time)
	{};

	virtual void MidiOut(DWORD data, char n);
	virtual void MidiOut(BYTE *p, char n);
	virtual void Quite(Route *r);

        void SetBendingRange(const int i)
	{
		bending_range = i;
	}

        int GetBendingRange () const 
	{
		return bending_range;
	}

	virtual DevType GetType() const
	{
		return DTMidiFile;
	}

	
	virtual int GetMaxChannel() const { return 15; }
	virtual int GetMinChannel() const { return 0; }
	
	virtual mutString GetTypeName () const {
		return _("MIDI output file");
	}

#ifdef WX
	virtual wxString TowxString() const {
		wxString s = OutDevice::TowxString() +
		wxString::Format(_T("\n  Name = %s\n  DevId = %d\n  Bending Range = %d\n  nKeyOn"),
				 Name.c_str(), DevId, bending_range, nKeyOn);
		s.Printf(_T("\n  KeyDir = [ %d"), KeyDir[0]);
		for (int i = 1; i<16; i++)
			s.Printf(_T(", %d"),KeyDir[i]);
		s.Printf(_T("]\n  ton_auf_kanal = [ %d"), ton_auf_kanal[0]);
		for (int i = 1; i<16; i++)
			s.Printf(_T(", %d"), ton_auf_kanal[i]);
		s+=_T("]");
		return s;
	}
#endif
	virtual void ReadData(wxConfigBase * config);
	virtual void WriteData(wxConfigBase * config);
	
protected:

	Track Tracks;
	ChannelData Cd[16];
	char KeyDir[16];
	TonAufKanal1 ton_auf_kanal[16];
	int nKeyOn;
};

// InMidiFile -------------------------------------------------------



class InMidiFile : public InDevice
{

        class MidiTimer : public wxTimer
	{
		InMidiFile * file;

	public:
		MidiTimer(InMidiFile * f) : wxTimer(),file(f)
		{}

		void Notify()
		{
			file->IncDelta();
		}
	};

	MidiTimer timer;
public:

        InMidiFile(): InDevice(),timer (this),Track(NULL), TrackPos(NULL),curDelta(NULL),StatusByte(NULL) { }

	InMidiFile(wxString name, int devId): InDevice(devId, name),timer(this),Track(NULL),TrackPos(NULL),curDelta(NULL),StatusByte(NULL) {}

	virtual ~InMidiFile()
	{};
	
	/// Save current device settings in a tree storage
	/** \argument config (tree_storage) storage class, where the data will be saved.
	 */
	virtual void Save (tree_storage & config);
	
	/// Save route settings (filter settings) for a given route
	/** Some route settings (e.g. filter settings) are device type 
	 * specific. This function saves them in a tree storage.
	 * \argument config (tree_storage *) Storage class, where the data will be saved.
	 * \argument route (Route *) Route whos data shall be saved.
	 */
	virtual void Save (tree_storage & config, const Route * route);
	
	
	/// Load current device settings from a tree storage
	/** \argument config (tree_storage) storage class, where the data will be loaded from.
	 */
	virtual void Load (tree_storage & config);

	/// Loade route settings (filter settings) for a given route
	/** Some route settings (e.g. filter settings) are device type 
	 * specific. This function loads them from a tree storage.
	 * \argument config (tree_storage *) Storage class, where the data will be restored from.
	 * \argument route (Route *) Route whos data shall be loaded.
	 */
	virtual void Load (tree_storage & config, Route * route);

	
	virtual bool Open();
	virtual void Close();
	virtual void Stop();
	virtual void Play();
	virtual void Pause();
//	   void Proceed(GisReadArtHead *h, char turn, Route *route) {};
//	   void ProceedRoute(GisReadArtHead *h, char turn) {};
	virtual frac ReadOn(frac time)
	{
		return frac(0, 1);
	}

	virtual DevType GetType() const
	{
		return DTMidiFile;
	}


	void IncDelta();
	
	virtual int GetMaxChannel() const { return 15; }
	virtual int GetMinChannel() const { return 0; }
	virtual int GetMaxTrack() const { return 0xFFFF; }
	virtual int GetMinTrack() const { return 0; }

        virtual mutString GetTypeName () const {
                return _("MIDI input file");
        }
	
#ifdef WX
	virtual wxString TowxString() const {
		return InDevice::TowxString() +
		wxString::Format(_T("\n  FileType = %d\n  nTrack = %d\n  Speed = %d\n  TrackPos = %d\n  curDelta = %ld"
				    "\n  minDelta = %ld\n  actDelta = %ld\n  StatusByte = %x\n  Busy = %d"
				    "\n  TicksPerQuater = %d\n  MMSPerQuater = %ld"),
				 FileType, nTrack, Speed, (Track?(*Track?**Track:-1):-2), 
				 (TrackPos?*TrackPos:-1), (curDelta?*curDelta:-1), 
				 minDelta, actDelta, (StatusByte?*StatusByte:-1), Busy, TicksPerQuater, MMSPerQuater);
	}
#endif
protected:
	BYTE FileType;
	size_t nTrack;
	int Speed;
	BYTE **Track;
	DWORD *TrackPos;
	long *curDelta;
	long minDelta;
	long actDelta;
	BYTE *StatusByte;
	ChannelData Cd[16];
	//  UINT TimerId;
	BOOL Busy;
	DWORD TicksPerQuater;
	long MMSPerQuater;
	void Proceed(DWORD midiCode, int track);
	void ProceedRoute(DWORD midiCode, Route *route);
	long ReadMidiProceed(size_t nr, long time);
};

// Function ---------------------------------------------------------


#endif

/*
timeSetEvent

The timeSetEvent function starts a specified timer event. The multimedia timer runs in its own thread. After the event is activated, it calls the specified callback function or sets or pulses the specified event object.

This function is obsolete. New applications should use CreateTimerQueueTimer to create a timer-queue timer.

MMRESULT timeSetEvent(
  UINT           uDelay,
  UINT           uResolution,
  LPTIMECALLBACK lpTimeProc,
  DWORD_PTR      dwUser,
  UINT           fuEvent
);

Parameters

uDelay

Event delay, in milliseconds. If this value is not in the range of the minimum and maximum event delays supported by the timer, the function returns an error.

uResolution

Resolution of the timer event, in milliseconds. The resolution increases with smaller values; a resolution of 0 indicates periodic events should occur with the greatest possible accuracy. To reduce system overhead, however, you should use the maximum value appropriate for your application.

lpTimeProc

Pointer to a callback function that is called once upon expiration of a single event or periodically upon expiration of periodic events. If fuEvent specifies the TIME_CALLBACK_EVENT_SET or TIME_CALLBACK_EVENT_PULSE flag, then the lpTimeProc parameter is interpreted as a handle to an event object. The event will be set or pulsed upon completion of a single event or periodically upon completion of periodic events. For any other value of fuEvent, the lpTimeProc parameter is interpreted as a function pointer with the following signature: void (CALLBACK)(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);

dwUser

User-supplied callback data.

fuEvent

Timer event type. This parameter may include one of the following values.
Value 	Meaning
TIME_ONESHOT 	Event occurs once, after uDelay milliseconds.
TIME_PERIODIC 	Event occurs every uDelay milliseconds.

The fuEvent parameter may also include one of the following values.
Value 	Meaning
TIME_CALLBACK_FUNCTION 	When the timer expires, Windows calls the function pointed to by the lpTimeProc parameter. This is the default.
TIME_CALLBACK_EVENT_SET 	When the timer expires, Windows calls the SetEvent function to set the event pointed to by the lpTimeProc parameter. The dwUser parameter is ignored.
TIME_CALLBACK_EVENT_PULSE 	When the timer expires, Windows calls the PulseEvent function to pulse the event pointed to by the lpTimeProc parameter. The dwUser parameter is ignored.
TIME_KILL_SYNCHRONOUS 	Passing this flag prevents an event from occurring after the timeKillEvent() function is called.

Return Values

Returns an identifier for the timer event if successful or an error otherwise. This function returns NULL if it fails and the timer event was not created. (This identifier is also passed to the callback function.)

Remarks

Each call to timeSetEvent for periodic timer events requires a corresponding call to the timeKillEvent function.

Creating an event with the TIME_KILL_SYNCHRONOUS and the TIME_CALLBACK_FUNCTION flag prevents the event from occurring after the timeKillEvent function is called.

Requirements

  Windows XP: Included in Windows XP only.
  Header: Declared in Mmsystem.h; include Windows.h.
  Library: Use Winmm.lib.


 */