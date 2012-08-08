/** \file  -*- C++ -*-
 ********************************************************************
 * Description
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/routing/midi/DevMidF.h,v 1.8 2011/11/02 14:31:58 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/11/02 14:31:58 $
 * \version $Revision: 1.8 $
 * \license GPL
 *
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * $Log: DevMidF.h,v $
 * Revision 1.8  2011/11/02 14:31:58  keinstein
 * fix some errors crashing Mutabor on Windows
 *
 * Revision 1.7  2011-10-02 16:58:41  keinstein
 * * generate Class debug information when compile in debug mode
 * * InputDeviceClass::Destroy() prevented RouteClass::Destroy() from clearing references -- fixed.
 * * Reenable confirmation dialog when closing document while the logic is active
 * * Change debug flag management to be more debugger friendly
 * * implement automatic route/device deletion check
 * * new debug flag --debug-trace
 * * generate lots of tracing output
 *
 * Revision 1.6  2011-09-30 09:10:24  keinstein
 * Further improvements in the routing system.
 *
 * Revision 1.5  2011-09-27 20:13:22  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.4  2011-02-20 22:35:56  keinstein
 * updated license information; some file headers have to be revised, though
 *
 *
 *
 ********************************************************************
 * \addtogroup route
 * \{
 ********************************************************************/
// ------------------------------------------------------------------
// Mutabor 3, 1998, R.Krauße
// MIDI-File als Device
// ------------------------------------------------------------------

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_ROUTING_MIDI_DEVMIDF_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_ROUTING_MIDI_DEVMIDF_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_ROUTING_MIDI_DEVMIDF_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "src/kernel/routing/Device.h"

#ifdef WX
#include "src/wxGUI/generic/mhArray.h"
#endif

#ifndef MU32_ROUTING_MIDI_DEVMIDF_H_PRECOMPILED
#define MU32_ROUTING_MIDI_DEVMIDF_H_PRECOMPILED

// system headers which do seldom change

#include <fstream>
#include "wx/timer.h"

#ifdef WX
WX_DEFINE_ARRAY_INT(BYTE, TBYTEBase1);
DEF_MHARRAY(BYTE, TByteArray, TBYTEBase1);
#else
#include <classlib/arrays.h>
typedef TArray<BYTE> TByteArray;
#endif



namespace mutabor {

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
	} TonAufKanal1;

	// OutMidiFile ------------------------------------------------------

	class MidiFileFactory;
	class OutputMidiFile : public OutputDeviceClass
	{
		friend class MidiFileFactory;
	protected:
		int bending_range;
		OutputMidiFile(): OutputDeviceClass(), bending_range (2) {}

		OutputMidiFile(int devId, 
			       const mutStringRef name, 
			       int id = -1, 
			       int bendingRange = 2)
			: OutputDeviceClass(devId, name, id)
			{
				bending_range = bendingRange;
			}
	public:
		virtual ~OutputMidiFile() {};
	
		/// Save current device settings in a tree storage
		/** \argument config (tree_storage) storage class, where the data will be saved.
		 */
		virtual void Save (tree_storage & config);
	
		/// Save route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type 
		 * specific. This function saves them in a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be saved.
		 * \argument route (Route ) Route whos data shall be saved.
		 */
		virtual void Save (tree_storage & config, const RouteClass * route);
	
	
		/// Load current device settings from a tree storage
		/** \argument config (tree_storage) storage class, where the data will be loaded from.
		 */
		virtual void Load (tree_storage & config);
	
		/// Loade route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type 
		 * specific. This function loads them from a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be restored from.
		 * \argument route (Route ) Route whos data shall be loaded.
		 */
		virtual void Load (tree_storage & config, RouteClass * route);

	
		virtual bool Open();
		virtual void Close();
		virtual void NoteOn(int box, int taste, int velo, 
				    RouteClass * r, int channel, ChannelData *cd);
		virtual void NoteOff(int box, int taste, int velo, 
				     RouteClass * r, int channel);
		virtual void NotesCorrect(int box);
		virtual void Sustain(char on, int channel);

#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif

		virtual int  GetChannel(int taste)
			{
				return -1;
			} // it would be possible to return the real value, but this is not very useful

		virtual void Gis(GisToken * token, char turn)
			{};

		virtual void AddTime(frac time)
			{};

#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif 

		virtual void MidiOut(DWORD data, char n);
		virtual void MidiOut(BYTE *p, char n);
		virtual void Quite(RouteClass * r);

		virtual void SetName(const wxString & s) 
			{
				if (s != Name) {
					bool reopen = IsOpen();
					if (reopen) 
						Close();

					Name = s;

					if (reopen)
						Open();
				}
			}
		

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
			return N_("MIDI output file");
		}

#ifdef WX
		virtual wxString TowxString() const;
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
#if 0
	/**
	 * Multimedia Timer
	 *
	 * Timer Interrupttion per interval[ms]
	 */
     
#include<windows.h>
#include<mmsystem.h>
     
#pragma comment(lib, "winmm.lib")
     
	void CALLBACK TimeProc(UINT uTimerID, UINT uMsg,
			       DWORD dwUser, DWORD dw1, DWORD dw2)
	{
		/**
		 * Timer Interruption
		 */
	}
     
	void main()
	{
		UINT uDelay = 1000;
		UINT uResolution = 1;
		DWORD dwUser = NULL;
		UINT fuEvent = TIME_PERIODIC; //You also choose TIME_ONESHOT;
     
		MMRESULT FTimerID;
		timeBeginPeriod(1);
		FTimerID = timeSetEvent(uDelay, uResolution, TimeProc, dwUser, fuEvent);
		if(FTimerID==NULL){
			printf("Failed to generate multimedia timer.\n");
		}
     
		Sleep(10000);
     
		timeKillEvent(FTimerID);
		timeEndPeriod(1);
	}
#endif


	class InputMidiFile : public InputDeviceClass
	{
		friend class MidiFileFactory;
	protected:
		class MidiTimer : public wxTimer
		{
			InputMidiFile * file;

		public:
			MidiTimer(InputMidiFile * f) : wxTimer(),file(f)
				{}

			void Notify()
				{
					file->IncDelta();
				}
		};

		MidiTimer timer;

		InputMidiFile(): InputDeviceClass(),
				 timer (this),
				 Track(NULL), 
				 TrackPos(NULL),
				 curDelta(NULL),
				 StatusByte(NULL) { }

		InputMidiFile(int devId,
			      wxString name, 
			      MutaborModeType mode,
			      int id): InputDeviceClass(devId, 
							name, 
							mode, 
							id),
					  timer(this),
					  Track(NULL),
					  TrackPos(NULL),
					  curDelta(NULL),
					  StatusByte(NULL) {}

	public:
		virtual ~InputMidiFile()
			{};
	
		/// Save current device settings in a tree storage
		/** \argument config (tree_storage) storage class, where the data will be saved.
		 */
		virtual void Save (tree_storage & config);
	
		/// Save route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type 
		 * specific. This function saves them in a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be saved.
		 * \argument route (Route ) Route whos data shall be saved.
		 */
		virtual void Save (tree_storage & config, const RouteClass * route);
	
	
		/// Load current device settings from a tree storage
		/** \argument config (tree_storage) storage class, where the data will be loaded from.
		 */
		virtual void Load (tree_storage & config);

		/// Loade route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type 
		 * specific. This function loads them from a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be restored from.
		 * \argument route (Route ) Route whos data shall be loaded.
		 */
		virtual void Load (tree_storage & config, RouteClass * route);

	
		virtual bool Open();
		virtual void Close();
		virtual void Stop();
		virtual void Play();
		virtual void Pause();
//	   void Proceed(GisReadArtHead *h, char turn, Route route) {};
//	   void ProceedRoute(GisReadArtHead *h, char turn) {};

#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif

		virtual frac ReadOn(frac time)
			{
				return frac(0, 1);
			}

#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif 
		virtual void SetName(const wxString & s) 
			{
				if (s != Name) {
					bool reopen = IsOpen();
					if (reopen) 
						Close();

					Name = s;

					if (reopen) 
						Open();
				}
			}

		virtual DevType GetType() const
			{
				return DTMidiFile;
			}


		virtual void IncDelta();
	
		virtual int GetMaxChannel() const { return 15; }
		virtual int GetMinChannel() const { return 0; }
		virtual int GetMaxTrack() const { return 0xFFFF; }
		virtual int GetMinTrack() const { return 0; }

		virtual mutString GetTypeName () const {
			return N_("MIDI input file");
		}
	
#ifdef WX
		virtual wxString TowxString() const;
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
		void ProceedRoute(DWORD midiCode, Route route);
		long ReadMidiProceed(size_t nr, long time);
	};


	class MidiFileFactory:public DeviceFactory { 
	public:
		MidiFileFactory(size_t id = 0):
			DeviceFactory(id) {}
		virtual ~MidiFileFactory();

	protected:
		virtual size_t GetType() const
			{
				return DTMidiFile;
			}


		virtual mutabor::OutputDeviceClass * DoCreateOutput() const = 0;
		
		virtual mutabor::InputDeviceClass * DoCreateInput() const = 0;
		virtual mutabor::OutputDeviceClass * DoCreateOutput(int devId,
							     const mutStringRef name, 
							     int id = -1) const = 0;
		
		virtual mutabor::InputDeviceClass * DoCreateInput(int devId,
							   const mutStringRef name, 
							   int id = -1) const = 0;

		virtual mutabor::OutputDeviceClass * DoCreateOutput(int devId,
							     const mutStringRef name, 
							     mutabor::MutaborModeType mode, 
							     int id = -1) const = 0;
		
		virtual mutabor::InputDeviceClass * DoCreateInput(int devId,
							   const mutStringRef name, 
							   mutabor::MutaborModeType mode, 
							   int id = -1) const = 0;
	};


// Function ---------------------------------------------------------

}

#endif  /* precompiled */
#endif

///\}