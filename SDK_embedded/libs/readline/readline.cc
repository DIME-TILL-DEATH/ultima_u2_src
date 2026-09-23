#include "readline.h"

#include <algorithm>

__attribute__ ((weak)) void PageUpHandler(TReadLine* rl)
{
  int c ;
  rl->RecvChar(c) ;
  rl->SendString ("page up\r") ;
}

__attribute__ ((weak)) void PageDownHandler(TReadLine* rl)
{
  int c ;
  rl->RecvChar(c) ;
  rl->SendString ("page down\r") ;
}

TReadLine::symbol_type_ptr_t TReadLine::TrimStr(symbol_type_ptr_t s)
{
	//trim string left
	while ( (*s == ' ') ) s++ ;
	//trim string right
	char* tmp = s + strlen(s) -1 ;
	while ( (*tmp == ' ') ) *(tmp--) = 0 ;
	return s ;
}

//-----------------------------------------------------
size_t __attribute__ ((noinline)) TReadLine::StrWordCount(const_symbol_type_ptr_t s)
{
	size_t count = 0 ;
	if ( !*s ) return 0 ;
	count++ ;
	while(*s)
		{
			if ( (*s == ' ') &&  (*(s+1) != ' ') && *s )
				count++ ;
			s++ ;
		}
	return count ;
}
//-----------------------------------------------------
void __attribute__ ((noinline)) TReadLine::MakeArgv( symbol_type_ptr_t s, const_symbol_type_ptr_t* argv )
{
	size_t argc = 0 ;
	argv[argc] = s ;

	while ( *s )
			{
				while ( (*s != ' ') && *s) s++ ;
				if ( !(*s) ) break ;
				// terminate current arg sring
				*s = 0 ;
				s++ ;
				// serch next alfabetical symbol
				while ( *s == ' ' ) s++ ;
				argc++ ;
				argv[argc] = s++ ;
			}
}
//-----------------------------------------------------

void TReadLine::enter(TReadLine* rl )
{
        rl->send_char ( '\r' ) ;
	symbol_type_ptr_t command_line = *(rl->current) ;

        // обновление списка истории
        if ( (++rl->current) == rl->history.end())
                rl->current = rl->history.begin() ;

        // в качестве буфера используется обновленная текущая строка списка истории
        strcpy( *(rl->current), command_line) ;
        command_line = *(rl->current) ;

	if ( (*command_line) )
		{
			command_line = TrimStr( command_line) ;

			// ������ �� ������ ��� ��������� ����� ����������
			size_t argc = StrWordCount(command_line);
			const_symbol_type_ptr_t argv[argc] ;
			MakeArgv( command_line , argv) ;
			command_handler_map_t::iterator it = rl->command_handler_map.find( argv[0]) ;

			if ( it != rl->command_handler_map.end())
				(*it).second.handler( rl , argv , argc ) ;
			else
				if ( rl->command_not_found ) rl->command_not_found( rl, (const_symbol_type_ptr_t*)argv , argc ) ;

		}

	rl->send_string ( "\033[33m", -1 ) ;
	rl->send_string (rl->promt, -1) ;
	rl->send_string ("\033[32m", -1) ;

	(*rl->current)[0] = 0 ;
	rl->pos = 0 ;
}
//-------------------------------------------------------------------------
void TReadLine::tab( TReadLine* rl)
{
	rl->send_string ( "call tab\r", -1 ) ;
}

//-------------------------------------------------------------------------
void TReadLine::backspace( TReadLine* rl)
{
     rl->send_string("\b\033[K", -1);
     if (rl->pos)
       (*rl->current)[--rl->pos] = 0 ;
}

void __attribute__ ((weak))  read_line_end_handler(const TReadLine* rl ) {}
void __attribute__ ((weak))  read_line_home_handler(const TReadLine* rl) {}

//-------------------------------------------------------------------------
void TReadLine::escape( TReadLine* rl  )
{
	int  c ;
	rl->recv_char(c) ;
	if ( c == 'O' )
	{
		switch ( rl->recv_char(c))
		{
			case 'F':
				//rl->send_string ("end\r") ;
			        read_line_end_handler(rl);
				break ;
			case 'H':
				//rl->send_string ("home\r") ;
			        read_line_home_handler(rl);
				break ;
			default :
				break ;
		}

		return ;
	}
	if ( c == '[')
	{
	        symbol_handler_map_t::iterator it ;
		switch(  rl->recv_char(c) )
			{
				case 'A' :  //arrow up
                                       /*  почемуто не работает
				        if ( rl->current == rl->history.begin())
				          rl->current = rl->history.end();

				        rl->current -- ;

				        // стирание строки
				        // установка курсора в начало строки
				        //вывод (*rl->current);

				        rl->UnsafePrintF ("%s%d%c%s" , "\033\[2K\033\[", rl->length,  'D' , *rl->current) ;
				        */
					break ;
				case 'B' :  //arrow down
					it = rl->escape_symbol_handler_map.find('B') ;
					if ( it != rl->escape_symbol_handler_map.end())
					(*it).second( rl ) ;
					break ;
				case 'D' :
					it = rl->escape_symbol_handler_map.find('D') ;
					if ( it != rl->escape_symbol_handler_map.end())
					(*it).second( rl ) ;
					break ;
				case 'C' :
					it = rl->escape_symbol_handler_map.find('C') ;
					if ( it != rl->escape_symbol_handler_map.end())
					(*it).second( rl ) ;
					break ;
				case '2' :
					rl->recv_char(c) ;
				        it = rl->escape_symbol_handler_map.find('2') ;
				        if ( it != rl->escape_symbol_handler_map.end())
		                            (*it).second( rl ) ;
					break ;
				case '3' :
					rl->recv_char(c) ;
					it = rl->escape_symbol_handler_map.find('3') ;
					if ( it != rl->escape_symbol_handler_map.end())
					    (*it).second( rl ) ;
					break ;
				case '5' :  // PageUp
				        it = rl->escape_symbol_handler_map.find('5') ;
				        if ( it != rl->escape_symbol_handler_map.end())
		                            (*it).second( rl ) ;
					break ;
				case '6' : // PageDown
				        it = rl->escape_symbol_handler_map.find('6') ;
				 	if ( it != rl->escape_symbol_handler_map.end())
				 	    (*it).second( rl ) ;
					break ;
				case '7':

				case '8':

					break ;
				default :
					break ;
			}
	}
}
//-------------------------------------------------------------------------
int TReadLine::Init(size_t history_depth , size_t length )
{
	//send_string = 0 ;

	this->length = length ;
	pos = 0 ;

	// init history list
	for ( size_t hi = 0 ; hi < history_depth ; hi++ )
	  {
	    symbol_type_ptr_t history_item = new  symbol_type_t [length+1]  ;
	    if ( !history_item )
	        abort();
	    // init to zero string
	    history_item[0] = 0 ;
	    //history_item[length] = 0 ;

	    history.push_front(history_item) ;
	  }

	current = history.begin() ;

	//init symbol handler
	AddSymbolHandler( '\r',enter ) ;
	AddSymbolHandler( '\t',tab ) ;
	AddSymbolHandler( '\b',backspace) ;
	AddSymbolHandler( '\033',escape ) ;

	return 1 ;
}
//--------------------------------------------------------------------------
void TReadLine::Process()
{
	int c;
	while ( recv_char(c) != -1 )
          {
	    // call handler for symbol c
            symbol_handler_map_t::iterator it = symbol_handler_map.find(c) ;
            if ( it != symbol_handler_map.end())
            	{
                    take(owner);
                    (*it).second( this ) ;
                    give(owner);
            	}
		{
			if ( c < 32 ) return ;
			if (echo)
			    send_char (c) ;
			if ( pos < length )
				{
					(*current)[pos++] = c ;
					(*current)[pos] = 0 ;
				}

		}
          }
}
//--------------------------------------------------------------------------
int TReadLine::SendBuf( const_symbol_type_ptr_t buf , size_t size )
{
        take(owner);
  	int result = UnsafeSendBuf ( buf , size ) ;
  	give(owner);
  	return result ;
}

size_t TReadLine::RecvBuf( symbol_type_ptr_t buf , size_t size )
{
	take(owner);
	size_t result = UnsafeRecvBuf ( buf , size ) ;
	give(owner);
	return result ;
}


