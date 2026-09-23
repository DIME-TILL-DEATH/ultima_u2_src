/*
Author: Samoylov Eugene aka Helius (ghelius@gmail.com)
BUGS and TODO:
-- add echo_off feature
-- rewrite history for use more than 256 byte buffer
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "microrl.h"

//#define DBG(...) fprintf(stderr, "\033[33m");fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\033[0m");

char * prompt_default = _PROMPT_DEFAUTL;

#ifdef _USE_HISTORY

#ifdef _HISTORY_DEBUG
//*****************************************************************************
// print buffer content on screen
static void print_hist (ring_history_t * cxt)
{
	printf ("\n");
	for (int i = 0; i < _RING_HISTORY_LEN; i++) {
		if (i == cxt->begin)
			printf ("b");
		else 
			printf (" ");
	}
	printf ("\n");
	for (int i = 0; i < _RING_HISTORY_LEN; i++) {
		if (isalpha(cxt->ring_buf[i]))
			printf ("%c", cxt->ring_buf[i]);
		else 
			printf ("%d", cxt->ring_buf[i]);
	}
	printf ("\n");
	for (int i = 0; i < _RING_HISTORY_LEN; i++) {
		if (i == cxt->end)
			printf ("e");
		else 
			printf (" ");
	}
	printf ("\n");
}
#endif

//*****************************************************************************
// remove older message from ring buffer
static void hist_erase_older (ring_history_t * cxt)
{
	int new_pos = cxt->begin + cxt->ring_buf [cxt->begin] + 1;
	if (new_pos >= _RING_HISTORY_LEN)
		new_pos = new_pos - _RING_HISTORY_LEN;
	
	cxt->begin = new_pos;
}

//*****************************************************************************
// check space for new line, remove older while not space
static int hist_is_space_for_new (ring_history_t * cxt, int len)
{
	if (cxt->ring_buf [cxt->begin] == 0)
		return true;
	if (cxt->end >= cxt->begin) {
		if (_RING_HISTORY_LEN - cxt->end + cxt->begin - 1 > len)
			return true;
	}	else {
		if (cxt->begin - cxt->end - 1> len)
			return true;
	}
	return false;
}

//*****************************************************************************
// put line to ring buffer
static void hist_save_line (ring_history_t * cxt, char * line, int len)
{
	if (len > _RING_HISTORY_LEN - 2)
		return;
	while (!hist_is_space_for_new (cxt, len)) {
		hist_erase_older (cxt);
	}
	// if it's first line
	if (cxt->ring_buf [cxt->begin] == 0) 
		cxt->ring_buf [cxt->begin] = len;
	
	// store line
	if (len < _RING_HISTORY_LEN-cxt->end-1)
		memcpy (cxt->ring_buf + cxt->end + 1, line, len);
	else {
		int part_len = _RING_HISTORY_LEN-cxt->end-1;
		memcpy (cxt->ring_buf + cxt->end + 1, line, part_len);
		memcpy (cxt->ring_buf, line + part_len, len - part_len);
	}
	cxt->ring_buf [cxt->end] = len;
	cxt->end = cxt->end + len + 1;
	if (cxt->end >= _RING_HISTORY_LEN)
		cxt->end -= _RING_HISTORY_LEN;
	cxt->ring_buf [cxt->end] = 0;
	cxt->cur = 0;
#ifdef _HISTORY_DEBUG
	print_hist (cxt);
#endif
}

//*****************************************************************************
// copy saved line to 'line' and return size of line
static int hist_restore_line (ring_history_t * cxt, char * line, int dir)
{
	int cnt = 0;
	// count history record	
	int header = cxt->begin;
	while (cxt->ring_buf [header] != 0) {
		header += cxt->ring_buf [header] + 1;
		if (header >= _RING_HISTORY_LEN)
			header -= _RING_HISTORY_LEN; 
		cnt++;
	}

	if (dir == _HIST_UP) {
		if (cnt >= cxt->cur) {
			int header = cxt->begin;
			int j = 0;
			// found record for 'cxt->cur' index
			while ((cxt->ring_buf [header] != 0) && (cnt - j -1 != cxt->cur)) {
				header += cxt->ring_buf [header] + 1;
				if (header >= _RING_HISTORY_LEN)
					header -= _RING_HISTORY_LEN;
				j++;
			}
			if (cxt->ring_buf[header]) {
					cxt->cur++;
				// obtain saved line
				if (cxt->ring_buf [header] + header < _RING_HISTORY_LEN) {
					memcpy (line, cxt->ring_buf + header + 1, cxt->ring_buf[header]);
				} else {
					int part0 = _RING_HISTORY_LEN - header - 1;
					memcpy (line, cxt->ring_buf + header + 1, part0);
					memcpy (line + part0, cxt->ring_buf, cxt->ring_buf[header] - part0);
				}
				return cxt->ring_buf[header];
			}
		}
	} else {
		if (cxt->cur > 0) {
				cxt->cur--;
			int header = cxt->begin;
			int j = 0;

			while ((cxt->ring_buf [header] != 0) && (cnt - j != cxt->cur)) {
				header += cxt->ring_buf [header] + 1;
				if (header >= _RING_HISTORY_LEN)
					header -= _RING_HISTORY_LEN;
				j++;
			}
			if (cxt->ring_buf [header] + header < _RING_HISTORY_LEN) {
				memcpy (line, cxt->ring_buf + header + 1, cxt->ring_buf[header]);
			} else {
				int part0 = _RING_HISTORY_LEN - header - 1;
				memcpy (line, cxt->ring_buf + header + 1, part0);
				memcpy (line + part0, cxt->ring_buf, cxt->ring_buf[header] - part0);
			}
			return cxt->ring_buf[header];
		}
	}
	return 0;
}
#endif








//*****************************************************************************
// split cmdline to tkn array and return nmb of token
static int split (microrl_t * cxt, int limit)
{
	int i = 0;
	int ind = 0;
	while (1) {
		// go to the first whitespace (zerro for us)
		while ((cxt->cmdline [ind] == '\0') && (ind < limit)) {
			ind++;
		}
		if (!(ind < limit)) return i;
		cxt->tkn_arr[i++] = cxt->cmdline + ind;
		if (i >= _COMMAND_TOKEN_NMB) {
			return -1;
		}
		// go to the first NOT whitespace (not zerro for us)
		while ((cxt->cmdline [ind] != '\0') && (ind < limit)) {
			ind++;
		}
		if (!(ind < limit)) return i;
	}
	return i;
}


//*****************************************************************************
inline static void print_prompt (microrl_t * cxt)
{
	cxt->print (cxt->prompt_str);
}

//*****************************************************************************
inline static void terminal_backspace (microrl_t * cxt)
{
		cxt->print ("\033[D \033[D");
}

//*****************************************************************************
inline static void terminal_newline (microrl_t * cxt)
{
	cxt->print ("\n");
}

//*****************************************************************************
// set cursor at position from begin cmdline (after prompt) + offset
static void terminal_move_cursor (microrl_t * cxt, int offset)
{
	char str[16] = "\033[" ;
	if (offset > 0) {
		snprintf (str, 16, "\033[%dC", offset);
	} else if (offset < 0) {
		snprintf (str, 16, "\033[%dD", -(offset));
	}
	cxt->print (str);
}

//*****************************************************************************
static void terminal_reset_cursor (microrl_t * cxt)
{
	char str[16] = {0};
	snprintf (str, 16, "\033[%dD\033[%dC", _COMMAND_LINE_LEN + _PROMPT_LEN + 2,	_PROMPT_LEN);
	cxt->print (str);
}

//*****************************************************************************
// print cmdline to screen, replace '\0' to wihitespace 
static void terminal_print_line (microrl_t * cxt, int pos, int cursor)
{
	cxt->print ("\033[K");    // delete all from cursor to end

	char nch [] = {0,0};
	for (int i = pos; i < cxt->cmdlen; i++) {
		nch [0] = cxt->cmdline [i];
		if (nch[0] == '\0')
			nch[0] = ' ';
		cxt->print (nch);
	}
	
	terminal_reset_cursor (cxt);
	terminal_move_cursor (cxt, cursor);
}

//*****************************************************************************
void microrl_init (microrl_t * cxt, void (*print) (char *)) 
{
	memset(cxt->cmdline, 0, _COMMAND_LINE_LEN);
#ifdef _USE_HISTORY
	memset(cxt->ring_hist.ring_buf, 0, _RING_HISTORY_LEN);
	cxt->ring_hist.begin = 0;
	cxt->ring_hist.end = 0;
	cxt->ring_hist.cur = 0;
#endif
	cxt->cmdlen =0;
	cxt->cursor = 0;
	cxt->execute = NULL;
	cxt->get_completion = NULL;
#ifdef _USE_CTLR_C
	cxt->sigint = NULL;
#endif
	cxt->prompt_str = prompt_default;
	cxt->print = print;
//	print_prompt (cxt);
}

//*****************************************************************************
void microrl_set_complite_callback (microrl_t * cxt, char ** (*get_completion)(int, const char* const*))
{
	cxt->get_completion = get_completion;
}

//*****************************************************************************
void microrl_set_execute_callback (microrl_t * cxt, int (*execute)(int, const char* const*))
{
	cxt->execute = execute;
}
#ifdef _USE_CTLR_C
//*****************************************************************************
void microrl_set_sigint_callback (microrl_t * cxt, void (*sigintf)(void))
{
	cxt->sigint = sigintf;
}
#endif

#ifdef _USE_ESC_SEQ
static void hist_search (microrl_t * cxt, int dir)
{
int len = hist_restore_line (&cxt->ring_hist, cxt->cmdline, dir);
if (len) {
	cxt->cursor = cxt->cmdlen = len;
	terminal_reset_cursor (cxt);
	terminal_print_line (cxt, 0, cxt->cursor);
}
}

//*****************************************************************************
// handling escape sequences
static int escape_process (microrl_t * cxt, char ch)
{
	static int seq = 0;

	if (ch == '[') {
		seq = _ESC_BRACKET;	
	} else if (seq == _ESC_BRACKET) {
		if (ch == 'A') {
#ifdef _USE_HISTORY
			hist_search (cxt, _HIST_UP);
#endif
			return 1;
		} else if (ch == 'B') {
#ifdef _USE_HISTORY
			hist_search (cxt, _HIST_DOWN);
#endif
			return 1;
		} else if (ch == 'C') {
			if (cxt->cursor < cxt->cmdlen) {
				terminal_move_cursor (cxt, 1);
				cxt->cursor++;
			}
			return 1;
		} else if (ch == 'D') {
			if (cxt->cursor > 0) {
				terminal_move_cursor (cxt, -1);
				cxt->cursor--;
			}
			return 1;
		} else if (ch == '7') {
			seq = _ESC_HOME;
			return 0;
		} else if (ch == '8') {
			seq = _ESC_END;
			return 0;
		} 
	} else if (ch == '~') {
			if (seq == _ESC_HOME) {
				terminal_reset_cursor (cxt);
				cxt->cursor = 0;
				return 1;
			} else if (seq == _ESC_END) {
				terminal_move_cursor (cxt, cxt->cmdlen-cxt->cursor);
				cxt->cursor = cxt->cmdlen;
				return 1;
			}
		
	}
	return 0;
}
#endif

//*****************************************************************************
// insert len char of text at cursor position
static int microrl_insert_text (microrl_t * cxt, char * text, int len)
{
	if (cxt->cmdlen + len < _COMMAND_LINE_LEN) {
		memmove (cxt->cmdline + cxt->cursor + len,
						 cxt->cmdline + cxt->cursor,
						 cxt->cmdlen - cxt->cursor);
		for (int i = 0; i < len; i++) {
			cxt->cmdline [cxt->cursor + i] = text [i];
			if (cxt->cmdline [cxt->cursor + i] == ' ') {
				cxt->cmdline [cxt->cursor + i] = 0;
			}
		}
		cxt->cursor += len;
		cxt->cmdlen += len;
		cxt->cmdline [cxt->cmdlen] = '\0';
		return true;
	}
	return false;
}

//*****************************************************************************
// remove one char at cursor
static void microrl_backspace (microrl_t * cxt)
{
	if (cxt->cursor > 0) {
		terminal_backspace (cxt);
		memmove (cxt->cmdline + cxt->cursor-1,
						 cxt->cmdline + cxt->cursor,
						 cxt->cmdlen-cxt->cursor+1);
		cxt->cursor--;
		cxt->cmdline [cxt->cmdlen] = '\0';
		cxt->cmdlen--;
	}
}


#ifdef _USE_COMPLETE

//*****************************************************************************
static int common_len (char ** arr)
{
	int len = 0;
	int i = 1;
	while (1) {
		while (arr[i]!=NULL) {
			if ((arr[i][len] != arr[i-1][len]) || 
					(arr[i][len] == '\0') || 
					(arr[i-1][len]=='\0')) 
				return len;
			len++;
		}
		i++;
	}
	return 0;
}

//*****************************************************************************
static void microrl_get_complite (microrl_t * cxt) 
{
	char ** compl_token; 
	
	if (cxt->get_completion == NULL) // callback was not set
		return;
	
	int status = split (cxt, cxt->cursor);
	if (cxt->cmdline[cxt->cursor-1] == '\0')
		cxt->tkn_arr[status++] = "";
	compl_token = cxt->get_completion (status, cxt->tkn_arr);
	if (compl_token[0] != NULL) {
		int i = 0;
		int len;

		if (compl_token[1] == NULL) {
			len = strlen (compl_token[0]);
		} else {
			len = common_len (compl_token);
			terminal_newline (cxt);
			while (compl_token [i] != NULL) {
				cxt->print (compl_token[i]);
				cxt->print (" ");
				i++;
			}
			terminal_newline (cxt);
			print_prompt (cxt);
		}
		
		if (len) {
			microrl_insert_text (cxt, compl_token[0] + strlen(cxt->tkn_arr[status-1]), 
																	len - strlen(cxt->tkn_arr[status-1]));
			if (compl_token[1] == NULL) 
				microrl_insert_text (cxt, " ", 1);
		}
		terminal_reset_cursor (cxt);
		terminal_print_line (cxt, 0, cxt->cursor);
	} 
}
#endif

//*****************************************************************************


void microrl_insert_char (microrl_t * cxt, int ch)
{
	int status;
	
#ifdef _USE_ESC_SEQ
	static int escape = false;
	
	if (escape) {
		if (escape_process(cxt, ch))
			escape = 0;
	} else {
#endif
		switch (ch) {
			//-----------------------------------------------------
			case KEY_CR:
			case KEY_LF:
				terminal_newline (cxt);
#ifdef _USE_HISTORY
				if (cxt->cmdlen > 0)
					hist_save_line (&cxt->ring_hist, cxt->cmdline, cxt->cmdlen);
#endif
				status = split (cxt, cxt->cmdlen);
				if (status == -1)
//					cxt->print ("ERROR: Max token amount exseed\n");
					cxt->print ("ERROR:tokens too much\n\r");
				if ((status > 0) && (cxt->execute != NULL)) 
					cxt->execute (status, cxt->tkn_arr);
				print_prompt (cxt);
				cxt->cmdlen = 0;
				cxt->cursor = 0;
				memset(cxt->cmdline, 0, _COMMAND_LINE_LEN);
#ifdef _USE_HISTORY
				cxt->ring_hist.cur = 0;
#endif
			
			break;
			//-----------------------------------------------------
#ifdef _USE_COMPLETE
			case KEY_HT:
				microrl_get_complite (cxt);
			break;
#endif
			//-----------------------------------------------------
			case KEY_ESC:
#ifdef _USE_ESC_SEQ
				escape = 1;
#endif
			break;
			//-----------------------------------------------------
			case KEY_NAK: // ^U
					while (cxt->cursor > 0) {
					microrl_backspace (cxt);
				}
				terminal_print_line (cxt, 0, cxt->cursor);
			break;
			//-----------------------------------------------------
			case KEY_VT:  // ^K
				cxt->print ("\033[K");
				cxt->cmdlen = cxt->cursor;
			break;
			//-----------------------------------------------------
			case KEY_ENQ: // ^E
				terminal_move_cursor (cxt, cxt->cmdlen-cxt->cursor);
				cxt->cursor = cxt->cmdlen;
			break;
			//-----------------------------------------------------
			case KEY_SOH: // ^A
				terminal_reset_cursor (cxt);
				cxt->cursor = 0;
			break;
			//-----------------------------------------------------
			case KEY_ACK: // ^F
			if (cxt->cursor < cxt->cmdlen) {
				terminal_move_cursor (cxt, 1);
				cxt->cursor++;
			}
			break;
			//-----------------------------------------------------
			case KEY_STX: // ^B
			if (cxt->cursor) {
				terminal_move_cursor (cxt, -1);
				cxt->cursor--;
			}
			break;
			//-----------------------------------------------------
			case KEY_DLE: //^P
#ifdef _USE_HISTORY
			hist_search (cxt, _HIST_UP);
#endif
			break;
			//-----------------------------------------------------
			case KEY_SO: //^N
#ifdef _USE_HISTORY
			hist_search (cxt, _HIST_DOWN);
#endif
			break;
			//-----------------------------------------------------
			case KEY_DEL: // Backspace
			case KEY_BS: // ^U
				microrl_backspace (cxt);
				terminal_print_line (cxt, cxt->cursor, cxt->cursor);
			break;
#ifdef _USE_CTLR_C
			case KEY_ETX:
			if (cxt->sigint != NULL)
				cxt->sigint();
			break;
#endif
			//-----------------------------------------------------
			default:
			if ((ch == ' ') && (cxt->cmdlen == 0)) 
				break;
			if (microrl_insert_text (cxt, (char*)&ch, 1))
				terminal_print_line (cxt, cxt->cursor-1, cxt->cursor);
			
			break;
		}
#ifdef _USE_ESC_SEQ
	}
#endif
}

