/** \file 
 ********************************************************************
 * Description: Collect all properties, which are used by boxes
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/src/kernel/box.h,v 1.6 2011/09/27 20:13:21 keinstein Exp $
 * Copyright:   (c) 2008 TU Dresden
 * \author  Tobias Schlemmer <keinstein@users.berlios.de>
 * \date 
 * $Date: 2011/09/27 20:13:21 $
 * \version $Revision: 1.6 $
 * \license GPL
 *
 * $Log: box.h,v $
 * Revision 1.6  2011/09/27 20:13:21  keinstein
 * * Reworked route editing backend
 * * rewireing is done by RouteClass/GUIRoute now
 * * other classes forward most requests to this pair
 * * many bugfixes
 * * Version change: We are reaching beta phase now
 *
 * Revision 1.5  2011-09-08 18:50:41  keinstein
 * Fix some further update bug
 *
 * Revision 1.4  2011-09-08 16:51:21  keinstein
 * Set foreground color in box status windows
 * Fix updating box status windows
 * update RtMidi (includes Jack compilation mode)
 *
 * Revision 1.3  2011-09-07 13:06:50  keinstein
 * Get rid of WinAttr and Fix window opening and closing
 *
 * Revision 1.2  2011-09-05 11:30:07  keinstein
 * Some code cleanups moving some global box arrays into class mutaborGUI::BoxData
 * Restore perspective on logic start
 *
 * Revision 1.1  2011-07-27 20:48:32  keinstein
 * started to move arrays using MAX_BOX into struct mutabor_box_type
 *
 *
 *
 ********************************************************************
 * \addtogroup kernel
 * \{
 ********************************************************************/


/* we guard a little bit complicated to ensure the references are set right
 */

#if (!defined(MU32_BOX_H) && !defined(PRECOMPILE)) \
	|| (!defined(MU32_BOX_H_PRECOMPILED))
#ifndef PRECOMPILE
#define MU32_BOX_H
#endif

// ---------------------------------------------------------------------------
// headers
// ---------------------------------------------------------------------------

#include "Defs.h"
#include "Global.h"
#include "Interpre.h"

#ifndef MU32_BOX_H_PRECOMPILED
#define MU32_BOX_H_PRECOMPILED

// system headers which do seldom change


enum BoxType
{
	NewBox = -3,
	NoBox,
	GmnBox,
	Box0 = 0
};
	

#define MIN_BOX NewBox

/** Mutabor box type. */
typedef struct {
        int id;
	int next_used;
	void * userdata;
	/** pattern structure in current box */
	PATTERNN pattern;
	/** tone system.  
	    we use pointers here, since this enables us
	    to quickly change the tone sytem. This saves us 
	    a copy operation.
	 */
	tone_system * tonesystem;
        // flags
        int used:1; //< box currently in use or wasting memory
        int keys_changed:1;
        int logic_changed:1;
        int action_changed:1;
} mutabor_box_type;



extern tone_system * free_tonesystem;
extern mutabor_box_type mut_box[MAX_BOX];
extern int laufzeit_meldungen_erlaubt;
extern int aktuelles_midi_instrument;
extern int aktuelle_keyboard_box;
extern size_t minimal_box_used;

extern int keys_changed_sum;

void initialize_boxes();


#endif
#endif


///\}