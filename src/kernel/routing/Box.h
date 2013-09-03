// -*- C++ -*-

/** \file
 ********************************************************************
 * Mutabor Box for C++. Mutoabor Core.
 *
 * \author Tobias Schlemmer <keinstein@users.berlios.de>
 * \license GPL
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
 *
 ********************************************************************
 *\addtogroup route
 *\{
 ********************************************************************/

/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(ROUTING_BOX_H) && !defined(PRECOMPILE)) \
	|| (!defined(ROUTING_BOX_H_PRECOMPILED))
#ifndef PRECOMPILE
#define ROUTING_BOX_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#define HIDE_MUTABOR_C_API

#include "src/kernel/Defs.h"
#include "src/kernel/treestorage.h"
#include "src/kernel/routing/thread.h"
#include "src/kernel/routing/Route.h"
#include "src/kernel/Execute.h"

#ifndef ROUTING_BOX_H_PRECOMPILED
#define ROUTING_BOX_H_PRECOMPILED

// system headers which do seldom change
#include <boost/intrusive_ptr.hpp>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdarg.h>
#include <stdio.h>


namespace mutaborGUI {
	class BoxData;
}

namespace mutabor {
	namespace hidden {
		extern "C" {
			struct mutabor_box_type;
			struct keyboard_ereignis;
			typedef struct keyboard_ereignis keyboard_action;
			struct midiliste;
		}
	}
	using hidden::mutabor_box_type;
	using hidden::keyboard_ereignis;
	using hidden::keyboard_action;
	using hidden::midiliste;


	enum BoxType
	{
		MIN_BOX = -3,
		NewBox = -3,
		NoBox,
		GmnBox,
		Box0 = 0
	};

	class BoxClass;
	typedef boost::intrusive_ptr<BoxClass> Box;
	typedef std::vector<Box> BoxListType;
	

	class BoxClass
	{
	public:
		enum  boxidtype {
			IDTypeSession,
			IDTypeFile
		};

		struct ChangedCallback {
			typedef mutabor::hidden::do_aktion action;
			Box box;
			enum ChangedFlags {
				BoxChanged = 1,
				LogicChanged = 2,
				KeysChanged = 4,
				ActionChanged = 8
			};
			ChangedCallback(Box & b):box(b) {
				if (b) b->Register(this);
			}
			~ChangedCallback() {
				if (box) 
					box->Unregister(this);
			}
			virtual void SetBox(Box & b) {
				if (b == box) return;
				if (box)
					box->Unregister(this);
				box = b;
				if (box) 
					box->Register(this);
			}
			virtual void BoxChangedAction(int flags) = 0;
			virtual void BoxChangedAction(action * a) {}
		};

		typedef BoxListType listtype;

		virtual ~BoxClass();

		size_t get_session_id() const {
			return session_id;
		}

		virtual BoxType GetType() {
			return routefile_id >= Box0 ? Box0 : (BoxType) routefile_id;
		}

		virtual mutString GetTypeName() {
			switch (GetType()) {
			case NewBox:
				return _("New box");
				break;
			case NoBox:
				return _("No box");
				break;
			case GmnBox:
				return _("GUIDO Music Notation box");
				break;
			case Box0:
				return _("Mutabor box");
				break;
			}
			return _("Unknown box type");
		}

		virtual mutString GetLabel() {
			switch (GetType()) {
			case NewBox:
				return _("New box");
				break;
			case NoBox:
				return _("No box");
				break;
			case GmnBox:
				return _("GUIDO box");
				break;
			case Box0:
				return mutString::Format(_("Box %d"),get_routefile_id());
				break;
			}
			return _("Unknown box type");
		}

		bool IsNormal() {
			return routefile_id >= Box0;
		}

		int get_routefile_id() const {
			return routefile_id;
		}

		virtual void set_routefile_id(int id);
	
		static int GetNextFreeBox() {
			return nextboxid;
		}

		/// Save current device settings in a tree storage
		/** \argument config (tree_storage) storage class, where the data will be saved.
		 */
		virtual void Save (tree_storage & config);
	
		/// Save route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type 
		 * specific. This function saves them in a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be saved.
		 * \argument route (Route) Route whos data shall be saved.
		 */
		virtual void Save (tree_storage & config, 
				   const RouteClass * route);
	
		/// Load current device settings from a tree storage
		/** \argument config (tree_storage) storage class, where the data will be loaded from.
		 */
		virtual void Load (tree_storage & config);
	
		/// Load route settings (filter settings) for a given route
		/** Some route settings (e.g. filter settings) are device type 
		 * specific. This function loads them from a tree storage.
		 * \argument config (tree_storage *) Storage class, where the data will be restored from.
		 * \argument route (Route) Route whos data shall be loaded.
		 */
		virtual void Load (tree_storage & config, 
				   RouteClass * route);
	

		/// add a route
		virtual void Add(Route & route);
		/// replace a route
		virtual bool Replace(Route & oldRoute, Route & newRoute);
                /// remove a route
		virtual bool Remove(Route & route);
		/// Move routes to another device 
		virtual bool MoveRoutes (Box & newclass);

		virtual	int MoveInList(int count);

		const routeListType & GetRoutes() const {
			return routes;
		}

		routeListType & GetRoutes() {
			return routes;
		}


		static const listtype & GetBoxList() { 
			return boxList ; 
		}



		/// Scan the list of Boxes for a given id.
		/** \argument id (int) id to scan for
		 *  \return (Box) pointer to the input device with the given id if found, NULL else.
		 */
		static Box GetBox(int id, boxidtype kind);

		
		/** 
		 * Return the box that is associated with the corrent id. In case such a box does not 
		 * exist the box is created
		 * 
		 * \param id  Id to be fetched.
		 * 
		 * \return Box that has been found or created
		 */
		static Box GetOrCreateBox(int id);

		static void ClearBoxList() {
			while (!boxList.empty()) {
#ifdef DEBUG
				Box d = boxList.front();
#endif
				boxList.front()->Destroy();
#ifdef DEBUG
				mutASSERT(boxList.empty() || 
					 d != boxList.front());
#endif
			}
		}

		/** 
		 * Disconnect the device from all pairings with routes GUI data or something else. 
		 *
		 * This function should be extended in subclasses so
		 * that after calling it only temporary pointers
		 * (variables in functions or temporary objects) point
		 * to the object.
		 */
		virtual void DisconnectFromAll();


		/// reset the device if requested
		virtual void Panic();
		virtual void Reset();

#if defined(_MSC_VER)
#pragma warning(push) // Save warning settings.
#pragma warning(disable : 4100) // Disable unreferenced formal parameter warnings
#endif
		virtual void ReadData(wxConfigBase * config) {};
		virtual void WriteData(wxConfigBase * config) {};	
#if defined(_MSC_VER)
#pragma warning(pop) // Restore warnings to previous state.
#endif 

		virtual bool Open();
		virtual void Close();
		bool IsOpen() { return open; }

		/** 
		 * Close all boxes.
		 * This function deactivates all boxes.
		 * 
		 */
		static void CloseAll();

		/** 
		 * Activate all boxes. This resets the action traces of all boxes.
		 * \note Code should be taken from MutFrame::DoActivate
		 * 
		 * \param isRealtime Shall non-realtime devices (e.g.,
		 * file devices) act in realtime mode or not
		 * 
		 * \retval true if Activation succeeded
		 * \retval false otherwise
		 */
		static bool ActivateAll(bool isRealtime);

		/** 
		 * Stop all boxes. This resets the action traces of all boxes.
		 * \note Code should be taken from Stop()
		 */
		static void StopAll();

		struct logic_entry {
			bool isLogic;
			mutString name;
			mutString startTuning;
			int key;
			keyboard_action * logic;
		};
		
		typedef std::list<logic_entry> logic_list;

		/** 
		 * Get a list of currently defined logics.
		 * \note: this function replaces GetMutTag() from Runtime.cpp
		 * 
		 * \return List of logic descriptions.
		 */
		logic_list GetLogics();

		// this mimics Com4pDlg
		struct CompileCallback {
			virtual void Refresh() = 0;
			virtual void SetStatus(mutString status) = 0;
			virtual void SetMessage(mutString message) = 0;
			virtual void SetStatus(int logics, 
					       int tones, 
					       int tunings,
					       int tone_systems,
					       int intervals,
					       int characters) = 0;
			virtual void SetLine(int number) = 0;
		};
		
		bool Compile(CompileCallback * callback, const char * logic);
		static void compile_callback(struct mutabor_box_type * b, int line_number);

		void MidiAnalysis(uint8_t midiByte) {
			BoxLock lock(this);
			hidden::MidiAnalysis(box, midiByte);
		}

		void MidiOut(struct midiliste * outliste);
		static void MidiOutCallback(struct mutabor::hidden::mutabor_box_type * b,
				     struct mutabor::hidden::midiliste * outliste);
		/** 
		 * Update the currently playing tones to the current tone system.
		 * \note this function was formerly defined as \c NotesCorrect
		 * 
		 */
		void UpdateTones();

		/** 
		 * Get the MIDI channel of a given tone
		 * 
		 * \param note     Note that has been received
		 * \param channel  Internal unique channel id
		 * \param id       Internal unique Note id
		 * 
		 * \return MIDI channel of the note
		 */
		int GetChannel(int key, size_t channel, size_t id);


		void AddNote(int note, size_t id, size_t channel, void * userdata) {
			BoxLock lock(this);
			hidden::AddKey(box, note, id, channel, userdata);
		}

		void DeleteNote(int note, size_t id, int channel) {
			BoxLock lock(this);
			hidden::DeleteKey(box, note, id, channel);
		}

		enum KeyboardFlags {
			KeyboardNoLogic,              // Execute only logics
			KeyboardLogic,                // Execute only tone systems
			KeyboardAny                   // Any possible action
		};

		bool IsLogicKey(int key);

		/** 
		 * Execute the action associated with a key that is
		 * pressed on the computer keyboard
		 * 
		 * \param key    Key that has been pressed.
		 * \param flags  Flags which type of action should be taken.
		 */
		void KeyboardAnalysis(int key, KeyboardFlags flags) {
			BoxLock lock(this);
			switch (flags) {
			case KeyboardNoLogic:
			case KeyboardLogic:
				hidden::KeyboardAnalyse(box,key,flags == KeyboardLogic);
				break;
			case KeyboardAny:
				hidden::KeyboardAnalyseSimple(box, key);
				break;
			}
		}

		/** 
		 * Execute the actions that are associated with the
		 * characters of a string.  \note: The character “&”
		 * denotes that the following character will not be a
		 * logic.
		 * 
		 * \param keys 
		 */
		void KeyboardAnalysis(const mutStringRef keys) {
			BoxLock lock(this);
			hidden::KeyboardIn(box,keys.ToUTF8());
		}

		long get_frequency(int note);
		int get_index(int note);
		int get_distance(int note);

		void SetLogic(Box b) {
			hidden::mutabor_set_logic(box,b->box->file);
		}

#if 0
		/// Sets the name of the currently active logic
		/** \param s wxString name of the logic
		*/
		void SetLogicName(const wxString & s) { current_logic = s; }
		/// Returns the name of the currently active logic
		/** \return wxString name of the logic
		 */
		wxString GetLogicName() const { return current_logic; }

		
		
		/// Sets the name of the currently active tone system
		/** \param s wxString name of the tone system
		*/
		void SetTonesystem(const wxString & s) { current_tonesystem = s; }
		/// Returns the name of the currently active tone system
		/** \return wxString name of the tone system
		 */
		wxString GetTonesystem() const { return current_tonesystem; }

		/// Sets the key of the currently active tone system
		/** \param nr int number of the key
		*/
		void SetKeyTonesystem(int nr) { current_key_tonesystem = nr; }
		/// Returns the key of the currently active tone system
		/** \return int number of the key
		 */
		int GetKeyTonesystem() const { return current_key_tonesystem; }

		/// Sets the key of the currently active logic
		/** \param nr int number of the key
		*/
		void SetKeyLogic(int nr) { current_key_logic = nr; }
		/// Returns the key of the currently active tone system
		/** \return int key of the tone system
		 */
		int GetKeyLogic() const { return current_key_logic; }
#endif

		/** 
		 * Destroy the current object.  
		 * This function is
		 * called when an object shall be deleted. It clears
		 * up all references to itself so that it will be deleted if it is not needed anymore.
		 * 
		 * This functions detatches the device from all routes and calls DoDestroy() afterwards. 
		 * Finally the Device is going to removed from the device list.
		 */
		virtual void Destroy();

		/// Initialize the internal device identifiers.
		/** This function sets the internal device ids of 
		 *  all output devices, starting from 0 and 
		 *  incrementing by 1
		 */
		static void InitializeIds();

#ifdef WX
		wxString TowxString() const;
#endif

		/// Process an error message (doing the real work)
		virtual void runtime_error(bool iswarning, const char * message);

	        /// Return the collected errors and warnings.
		/** 
		 * This function is a prototype for potential error message collection in 
		 * the GUI part.
		 * 
		 * \return a string containing the collected error messages
		 */
		virtual const mutStringRef get_errors() { 
			static mutString nothing = mutEmptyString;
			return nothing; 
		}
		static void log_action(mutabor_box_type * box, struct mutabor::hidden::do_aktion * action);
		static void UpdateCallback(struct mutabor_box_type * b, unsigned int flags);
	protected:
		struct BoxLock: public ScopedLock {
			Box box;
			BoxLock(BoxClass * b):ScopedLock(b->mutex),
					      box(b) {
				mutASSERT(IsOk());
			}
			~BoxLock() {
				box->UpdateTones();
				box->ExecuteCallbacks(box->updateflags);
			}
		};
	        static listtype boxList;
		static int nextboxid;
		friend class ::mutaborGUI::BoxData;
		friend class BoxFactory;
		friend void initialize_box_data();
		struct mutabor_box_type * box;
		idtype<BoxClass> session_id;
		int routefile_id;
		routeListType routes;
		bool open ;
		mutString current_logic;
		mutString current_tonesystem;
		int current_key_tonesystem; // 0
		int current_key_logic; // 1
		unsigned int updateflags;
		std::list<ChangedCallback *> callbacks;
		class set_callback {
			BoxClass * box;
		public:
			set_callback(BoxClass * b,
				     CompileCallback * callback):box(b) {
				box->current_compile_callback = callback;
			}
			~set_callback() {
				box->current_compile_callback = NULL;
			}
		};
		CompileCallback * current_compile_callback;
		static mutabor::hidden::mutabor_callback_type backend_callbacks;
		Mutex mutex;
	
		BoxClass(int id = -1);

		virtual void set_file_id(int id) {
			routefile_id = id;
		}

		void Register(ChangedCallback * callback) {
			callbacks.push_back(callback);
		}
		void Unregister(ChangedCallback * callback) {
			callbacks.remove(callback);
		}

		void ExecuteCallbacks(unsigned int flags);
		void ExecuteCallbacks(ChangedCallback::action * action);
		

		static void AppendToBoxList (Box dev);
		static void RemoveFromBoxList (Box  dev);
		static typename listtype::iterator FindInBoxList (Box b) {
			typename listtype::iterator i = 
				std::find(boxList.begin(),
					  boxList.end(),
					  b);
			return i;
		}
		static bool IsInBoxList (const Box b) {
			return FindInBoxList(b) != boxList.end();
		}
		static void TruncateBoxList (Box dev);


	private:
		REFPTR_INTERFACE
	};
		


	class BoxFactory { 
	public:
		struct BoxNotCreated:public std::exception {};
		struct FactoryNotFound:public std::exception {
			int id;
			std::string message_;
			FactoryNotFound(int i):std::exception(), id(i) {
				std::ostringstream writer(message_);
				writer << "Factory for box type " << i << " has not been registered.";
				message_ = writer.str();
			}

			virtual ~FactoryNotFound() throw () {}

			//! Returns the thrown error message as a c-style string.
			virtual const char* what( void ) const throw() { return message_.c_str(); }
			
		};

		BoxFactory(size_t id = 0);
		virtual ~BoxFactory();

		static Box Create(int type, int id = NewBox) {
			if (id == NewBox && type != Box0) {
				id = type;
			}

			if (type < 0) type = 0;
			mutASSERT(type >= 0);
			if (factories.size() <=(size_t) type) {
				throw FactoryNotFound(type);
				UNREACHABLECT(BoxFactory);
				return NULL;
			}
			if (!factories[type]) 
				throw FactoryNotFound(type);
			return factories[type]->DoCreateBox(id);
		}

		static void Destroy() {
			if (!factories.empty()) {
				for (factorylist::iterator i = factories.begin();
				     i != factories.end(); i++) {
				        BoxFactory * factory = *i;
					if (factory)
						delete factory;
				}
				factories.clear();
			} else 
				UNREACHABLECT(BoxFactory);
		}


		/// load the routes from a tree based configuration
		/** \param config conifiguration to be read from
		 */
		static void LoadBoxes(tree_storage & config);

		/// write the routes to the configuration
		/** \param config configuration to be written to
		 */ 
		static void SaveBoxes(tree_storage & config);

	protected:
		typedef std::vector<BoxFactory *> factorylist;
		static factorylist factories;
	
		virtual size_t GetType() { return Box0; };

		virtual BoxClass * DoCreateBox (int id = -1) const;
		
		/// load the routes from a tree based configuration
		/** \param config conifiguration to be read from
		 */
		virtual void DoLoadBoxes(tree_storage & config) const;

		/// write the routes to the configuration
		/** \param config configuration to be written to
		 */ 
		virtual void DoSaveBoxes(tree_storage & config) const;
	};

	//	void InitBoxFactories();

	class ScopedBox: public Box {
	public:
		~ScopedBox() { 
			if (get())
				get()->Destroy();
		}

		ScopedBox & operator = (BoxClass * rhs) {
			(*(static_cast<Box *>(this))) = rhs;
			return *this;
		}
		ScopedBox & operator = (const Box & rhs) {
			(*(static_cast<Box *>(this))) = rhs;
			return *this;
		}
	};


	inline Box BoxClass::GetOrCreateBox(int id) {
		Box b = GetBox(id,IDTypeFile);
		if (b) return b;
		else if (id > Box0) 
			return BoxFactory::Create(Box0,id);
		else return BoxFactory::Create(id);
	}

	void  Panic();

	inline void BoxClose()
	{
		const BoxListType& list = BoxClass::GetBoxList(); 
		for (BoxListType::const_iterator b = list.begin();
		     b != list.end(); b++)
			(*b)->Close();
	}

	bool OpenAll();
	void initialize_box_data();
}

#endif /* precompiled */
#endif

/*
 * \}
 */
