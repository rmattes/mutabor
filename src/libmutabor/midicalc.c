/** \file
 ********************************************************************
 * Alles zu MIDI-Berechnungen.
 *
 * $Header: /home/tobias/macbookbackup/Entwicklung/mutabor/cvs-backup/mutabor/mutabor/libmutabor/midicalc.c,v 1.4 2005/11/03 14:51:01 keinstein Exp $
 * \author Tobias Schlemmer <keinstein_junior@gmx.net>
 * \date $Date: 2005/11/03 14:51:01 $
 * \version $Revision: 1.4 $
 *
 * $Log: midicalc.c,v $
 * Revision 1.4  2005/11/03 14:51:01  keinstein
 * interpreter group for doxygen
 * interpreter functions
 *
 * Revision 1.3  2005/07/20 12:03:38  keinstein
 * Kopf korrigiert
 * Includes bereinigt.
 * config.h
 * Header ausgemistet
 *
 * Revision 1.2  2005/07/19 15:15:27  keinstein
 * Using own Templates
 *
 ********************************************************************/
#ifdef HAVE_CONFIG_H
#  include "config.h"
/* für HAVE_STDDEF_H, size_t */
#endif
#ifdef HAVE_STDDEF_H
#  include <stddef.h>
#endif
#include <stdio.h>
/* midicalc.h ist in umstimmung.h enthalten */
#include "mutabor/umstimmung.h"
#include "mutabor/heap.h"

/** Zählen der Elemente einer einfach verketteten MIDI-Liste.
 * \param list MIDI-Liste 
 * \return Anzahl der Elemente von \a list
 */
int midi_list_laenge (struct midiliste *list)
{ if (list) return 1 + midi_list_laenge (list -> next);
  return 0;
}

/********* Einleseroutine fuer Integerliste          *********/
/*         Es wird einfach eine Liste of Integer aufgebaut       **/
/*         die allgemein verwendbar ist.                       **/

/** universell nutzbare Ganzzahlenliste */
static struct midiliste * list_of_integers;

/** Setzt Integersequenz auf NULL.
 * \warning Die Integersequenz wird nicht gelöscht. 
 *          Das muss gegebenenfalls vor der Initialiserung manuell erledigt werden.
 */
void init_integersequenz (void)
{
    list_of_integers = NULL;
}

/** Hängt einen Wert an \a list_of_integers an.
 * \param[in] wert Anzuhängende ganze Zahl
 * \note Es wird immer die gesamte Liste durchsucht. Effektivität?
 */
void get_new_integer_in_integersequenz (int wert)
{
    struct midiliste * * lauf;
    for (lauf= & list_of_integers; * lauf; lauf= & (*lauf)->next) {
    }
    
    (* lauf) = (struct midiliste*) xmalloc ((size_t) sizeof (struct midiliste));
    (* lauf) -> midi_code     = wert;
    (* lauf) -> next          = NULL;
}

/** Gibt die Wurzel von \a list_of_integers zurück.
 */
struct midiliste * get_last_integersequenz (void)
{
    return list_of_integers;
}

/** Gibt eine Integersequenz aus. 
 * \param[in] this_ Sequenz 
 */
void print_integersequenz (struct midiliste * this_)
{
  if (this_) {
      printf (" %d ",this_->midi_code);
      print_integersequenz (this_->next);
  }
}



/** Baut \c tmp_umstimmung zu einer MIDI-Ausgabe aus.
 * Dabei wird die letzte eingelesene Ganzzahlen-Liste verwendet.
 */
void get_umstimmung_midi_out (void)
{
    tmp_umstimmung -> umstimmung_typ = umstimmung_midi_out;
    tmp_umstimmung -> u.umstimmung_midi_out.out_liste
                                = get_last_integersequenz ();
}

/** \}
 * \defgroup Interpreter 
 * \{
 */

/** Wandelt eine einfach verkettete MIDI-Liste in ein Ganzzahlen-(\c int)-Feld
 * um.
 * \return Ganzzahlenfeld. Der Letzte Eintrag enthält quasi als Wächter den Wert -1.
 */
int * create_midi_scan_liste (struct midiliste * lauf)
{
    int j, k, * ret;

    j = midi_list_laenge (lauf);
    
    ret = (int*) xcalloc((size_t)(j+1), sizeof(int));

    for (k=0; lauf; lauf=lauf->next, k++) 
        ret [k] = lauf->midi_code;
    ret [k] = -1;
    return ret;
}

/** \} */
