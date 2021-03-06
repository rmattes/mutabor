/** \file               -*- C++ -*-
 ********************************************************************
 * Watchdog timer.
 *
 * Copyright:   (c) 2013 Tobias Schlemmer
 * \author  Tobias Schlemmer <keinstein@users.sourceforge.net>
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
 * \addtogroup route
 * \{
 ********************************************************************/
/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(SRC_KERNEL_ROUTING_WATCHDOG_H) && !defined(PRECOMPILE)) \
	|| (!defined(SRC_KERNEL_ROUTING_WATCHDOG_H_PRECOMPILED))
#ifndef PRECOMPILE
#define SRC_KERNEL_ROUTING_WATCHDOG_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "src/kernel/Defs.h"
#include "wx/thread.h"
//#include "thread.h"
#include "timing.h"

#ifndef SRC_KERNEL_ROUTING_WATCHDOG_H_PRECOMPILED
#define SRC_KERNEL_ROUTING_WATCHDOG_H_PRECOMPILED

// system headers which do seldom change
#include <wx/version.h>

namespace mutabor {
	/**
	 * A watchdog timer class. It will periodically check whether
	 * a certain object is still active.
	 * 
	 */
	
	template <class T>
	class watchdog: public Thread {
		typedef T targettype;
	public:
		watchdog(T t,
			 mutint64 to):Thread(wxTHREAD_JOINABLE),
							      mutex(),
							      cond(mutex),
							      target(t),
							      timeout(to),
							      exit(false) {}
		virtual ~watchdog() {
			ScopedLock lock(mutex);
			targettype tmp = const_cast<targettype&>(target);
			if (tmp) {
				const_cast<targettype &>(target) = NULL;
				tmp->remove_watchdog(this);
			}
		}
		
		ExitCode Entry() {
			ScopedLock lock(mutex);
			cond.Sleep(timeout);
			while (!exit && const_cast<targettype&>(target)) {
				targettype tmp = const_cast<targettype&>(target);
				if (tmp)
					tmp->dog_watching();
				cond.Sleep(timeout);
			}
			return (ExitCode)0;
		}
		
		void OnExit() {
			ScopedLock lock(mutex);
			targettype tmp = const_cast<targettype&>(target);
			if (tmp) {
				const_cast<targettype &>(target).reset();
				tmp->remove_watchdog(this);
			}
		}
		
		void request_exit() {
			exit = true;
			{
				ScopedLock lock(mutex);
				cond.Broadcast();
			}
#if wxCHECK_VERSION(2,9,2)
			Wait(wxTHREAD_WAIT_BLOCK);
#else
			Wait();
#endif
 		}
	protected:
		Mutex mutex;
		ThreadCondition cond;
		mutable targettype target;
		mutint64 timeout;
		boost::atomic<bool> exit;
	};
}

#endif // precompiled
#endif // header loaded


///\}
