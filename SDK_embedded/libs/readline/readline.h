#ifndef __READLINE_H__
#define __READLINE_H__

#include "supc++.h"
#include "supstl.h"
#include "string.h"

#include <map>
//#include <unordered_map>
#include <list>

using namespace std ;

//TODO http://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html#cursor-navigation

#define RL_COLOR_BLACK  "\033[30m" //чёрный цвет знаков
#define RL_COLOR_RED    "\033[31m" //красный цвет знаков
#define RL_COLOR_GREEN  "\033[32m" //зелёный цвет знаков
#define RL_COLOR_YELLOW "\033[33m" //желтый цвет знаков
#define RL_COLOR_BLUE   "\033[34m" //синий цвет знаков
#define RL_COLOR_UV     "\033[35m" //фиолетовый цвет знаков
#define RL_COLOR_OCEAN  "\033[36m" //морской волны цвет знаков


#define RL_CURSOR_UP(y)    "\u001b["#y"A"
#define RL_CURSOR_DOWN(y)  "\u001b["#y"B"
#define RL_CURSOR_RIGHT(x) "\u001b["#x"C"
#define RL_CURSOR_LEFT(x)  "\u001b["#x"D"

#define RL_CURSOR_HPOS(x)  "\u001b["#x"G"
#define RL_CURSOR_VPOS(y)  "\u001b[;"#y"H"

#define RL_CURSOR_POS(y,x)  "\u001b["#y";"#x"H"

#define RL_CURSOR_H_BEGIN  "\u001b[1000D" //курсор в начало строки
#define RL_CURSOR_H_END    "\u001b[1000C" //курсор в конец строки

#define RL_CURSOR_V_BEGIN  "\u001b[1000A" //курсор в верхнюю строку
#define RL_CURSOR_V_END    "\u001b[1000B" //курсор в нижнию строку



#include "emb_string.h"

class TReadLine
{
	public:

		typedef char symbol_type_t ;
		typedef const symbol_type_t const_symbol_type_t ;

		typedef symbol_type_t* 	symbol_type_ptr_t ;
		typedef const_symbol_type_t* const_symbol_type_ptr_t ;

		typedef void (*command_handler_t)( TReadLine* rl, const_symbol_type_ptr_t* argv , const size_t argc ) ;
		typedef struct
		{
		  command_handler_t handler ;
		  const_symbol_type_ptr_t description ;
		  bool is_internal ; // false - application command, true - internal
		} command_t ;


		typedef pair< const const_symbol_type_ptr_t, command_t >  command_map_pair_t ;
		typedef map < const_symbol_type_ptr_t, command_t, compare , malloc_allocator<command_map_pair_t> > command_handler_map_t ;
		typedef command_handler_map_t::iterator command_handler_map_iterator_t ;


		typedef void (*symbol_handler_t)( TReadLine* rl ) ;
	        typedef pair< const const_symbol_type_t,symbol_handler_t>  symbol_map_pair_t ;
		typedef map < const_symbol_type_t,symbol_handler_t, compare, malloc_allocator<symbol_map_pair_t> > symbol_handler_map_t ;
		typedef symbol_handler_map_t::iterator symbol_handler_map_iterator_t ;

                //typedef unordered_map<const char, symbol_process, std::hash<const char> , compareT , malloc_allocator<sym_proces_pair_t> > symbol_process_map_t ;

		typedef int (*send_char_fnc) (const int c) ;
		typedef int (*recv_char_fnc) (int& c) ;

		typedef char* (*send_string_fnc) (const_symbol_type_ptr_t s, const size_t len) ;
		typedef size_t (*recv_string_fnc) (emb_string& s) ;

		typedef size_t (*send_buf_fnc) (const_symbol_type_ptr_t buf , size_t len ) ;
		typedef size_t (*recv_buf_fnc) (symbol_type_ptr_t buf , size_t len ) ;
/*
		static constexpr char COLOR_BLACK[]  = "\033[30m" ; //чёрный цвет знаков
		static constexpr char COLOR_RED[]    = "\033[31m" ; //красный цвет знаков
		static constexpr char COLOR_GREEN[]  = "\033[32m" ; //зелёный цвет знаков
		static constexpr char COLOR_YELLOW[] = "\033[33m" ; //желтый цвет знаков
		static constexpr char COLOR_BLUE[]   = "\033[34m" ; //синий цвет знаков
		static constexpr char COLOR_UV[]     = "\033[35m" ; //фиолетовый цвет знаков
		static constexpr char COLOR_OCEAN[]  = "\033[36m" ; //морской волны цвет знаков


*/              inline const void* Owner() const { return owner ; }

                typedef void (*sem_fnc) (const void* owner);

	protected:





		typedef list<symbol_type_ptr_t, malloc_allocator<symbol_type_ptr_t> > history_t ;

		static void enter(TReadLine* rl) ;
		static void tab(TReadLine* rl) ;
		static void backspace(TReadLine* rl);
		static void escape(TReadLine* rl) ;

		static symbol_type_ptr_t TrimStr(symbol_type_ptr_t s);
		static size_t StrWordCount  (const_symbol_type_ptr_t s) ;
		static void MakeArgv( symbol_type_ptr_t s, const_symbol_type_ptr_t* argv );

		const void* owner ; // handle of owner console task

	private:

		symbol_handler_map_t symbol_handler_map ; // ���� ������������ �������� ��������
		symbol_handler_map_t escape_symbol_handler_map ;
		command_handler_map_t command_handler_map ; // ���� ������������ ���������������� ������

		history_t history ;   // ��������� �������
		history_t::iterator current ; // �������� ���������� �������
		size_t pos ;
		size_t length ;

		send_char_fnc send_char ;
		recv_char_fnc recv_char ;


                send_string_fnc send_string ;
		recv_string_fnc recv_string ;
		recv_string_fnc recv_line ;

		send_buf_fnc send_buf ;
		recv_buf_fnc recv_buf ;

		command_handler_t command_not_found ;

		const_symbol_type_ptr_t promt ;

		sem_fnc take ;
		sem_fnc give ;

		bool echo ;

	public:
			inline TReadLine (const void* owner ) { this->owner = owner ; echo = true; } ;
			inline ~TReadLine() { symbol_handler_map.clear(); } ;
			int Init(size_t history_depth , size_t line_len );
			void Process();
			void inline AddCommandHandler( const_symbol_type_ptr_t command , command_handler_t handler , bool internal, const_symbol_type_ptr_t description = "" )
				{
			             command_handler_map.insert ( command_map_pair_t(command, { handler,description,internal } ) ) ;
				}
			void inline RemoveCommandHandler( const_symbol_type_ptr_t command )
				{
					command_handler_map.erase ( command_handler_map.find(command)) ;
				}
			void inline GetCommandHandlerMapIterators( command_handler_map_iterator_t& begin, command_handler_map_iterator_t& end )
				{
					begin = command_handler_map.begin() ;
					end = command_handler_map.end();
				}

			 bool inline GetCommandHandlerIterator( const_symbol_type_ptr_t command, command_handler_map_iterator_t& it )
			        {
			           const command_handler_map_iterator_t& tmp = command_handler_map.find(command) ;
			           if ( tmp != command_handler_map.end())
			             {
			               it = tmp ;
			               return true ;
			             }
			           return false ;
			        }



			void inline AddSymbolHandler( const_symbol_type_t symbol , symbol_handler_t handler )
				{
			            symbol_handler_map.insert ( symbol_map_pair_t(symbol,handler) ) ;
				}
			void inline RemoveSymbolHandler( const_symbol_type_t symbol )
				{
			            symbol_handler_map.erase ( symbol_handler_map.find(symbol)) ;
				}
			void inline GetSymbolHandlerMapIterator( symbol_handler_map_iterator_t& begin, symbol_handler_map_iterator_t& end )
				{
					begin = symbol_handler_map.begin() ;
					end = symbol_handler_map.end();
				}

			void inline AddEscapeSymbolHandler( const_symbol_type_t symbol , symbol_handler_t handler )
				{
					escape_symbol_handler_map.insert ( symbol_map_pair_t(symbol,handler) ) ;
				}
			void inline RemoveEscapeSymbolHandler( const_symbol_type_t symbol )
				{
			                escape_symbol_handler_map.erase ( symbol_handler_map.find(symbol)) ;
				}
			void inline GetEscapeSymbolHandlerMapIterator( symbol_handler_map_iterator_t& begin, symbol_handler_map_iterator_t& end )
				{
					begin = escape_symbol_handler_map.begin() ;
					end = escape_symbol_handler_map.end();
				}

			inline void RecvChar( recv_char_fnc recv_char ) { this->recv_char = recv_char ; }
			inline recv_char_fnc RecvChar() { return recv_char ; }
			inline int RecvChar( int& c ) { return recv_char(c); } ;

			inline void RecvBuf( recv_buf_fnc recv_buf ) { this->recv_buf = recv_buf ; }
                        inline recv_buf_fnc RecvBuf() { return recv_buf ; }
                        inline size_t UnsafeRecvBuf( symbol_type_ptr_t buf , size_t size ) { return recv_buf(buf,size) ; }
                        size_t RecvBuf( symbol_type_ptr_t buf , size_t size );

                        inline void RecvString( recv_string_fnc recv_string ) { this->recv_string = recv_string ; }
			inline recv_string_fnc RecvString() { return recv_string ; }
                        inline size_t RecvString( emb_string& dest ) { return recv_string(dest); } ;

			inline void RecvLine( recv_string_fnc recv_line ) { this->recv_line = recv_line ; }
                        inline recv_string_fnc RecvLine() { return recv_line ; }
                        inline size_t RecvLine( emb_string& dest ) { return recv_line(dest); } ;

			inline void SendChar( send_char_fnc send_char ) { this->send_char = send_char ; }
			inline send_char_fnc SendChar() {  return send_char ; }
			inline int SendChar(const int c) { return send_char(c); }

                        inline void SendBuf( send_buf_fnc send_buf ) { this->send_buf = send_buf ; }
                        inline send_buf_fnc SendBuf() { return send_buf ; }
                        inline int UnsafeSendBuf( const_symbol_type_ptr_t buf , size_t size ) { return send_buf(buf , size); }
                        int SendBuf( const_symbol_type_ptr_t buf , size_t size );

                        void inline SendString( send_string_fnc send_string ) { this->send_string = send_string ; }
			inline send_string_fnc SendString() { return send_string ; }
			inline symbol_type_ptr_t SendString( const_symbol_type_ptr_t dest, size_t len=-1 ) { return send_string(dest,len); } ;
			inline symbol_type_ptr_t SendString( emb_string& dest, size_t len=-1 ) { return send_string(dest.c_str(),len); } ;





			void inline SetCommandNotFound( command_handler_t command_not_found ) { this->command_not_found = command_not_found ; }
			inline void SetPromt(const_symbol_type_ptr_t promt) { this->promt = promt ; } ;

			inline void SetTakeSem( sem_fnc take ) { this->take = take ; }
			inline sem_fnc GetTakeSem() { return take ; }
			inline void SetGiveSem( sem_fnc give ) { this->give = give ; }
			inline sem_fnc GetGiveSem() { return give ; }

			inline command_handler_map_t& CommandHahdlerMap() { return command_handler_map ; } ;

			inline void Print (const size_t len, const emb_string& str)        { take(owner); send_string(str.c_str(),len); give(owner); } ;
			inline void Print (                  const emb_string& str)        { take(owner); send_string(str.c_str(),-1) ; give(owner); } ;
			inline void Print (const size_t len, const_symbol_type_ptr_t  str) { take(owner); send_string(str,len);         give(owner); } ;
			inline void Print (                  const_symbol_type_ptr_t  str) { take(owner); send_string(str,-1) ;         give(owner); } ;
			inline void Print (const_symbol_type_t c ) { take(owner);  send_char(c); give(owner); } ;

			inline void UnsafePrint (const size_t len, const emb_string& str)        { send_string(str.c_str(),len) ; } ;
			inline void UnsafePrint (                  const emb_string& str)        { send_string(str.c_str(),-1) ; } ;
			inline void UnsafePrint (const size_t len, const_symbol_type_ptr_t  str) { send_string(str,len); } ;
			inline void UnsafePrint (                  const_symbol_type_ptr_t  str) { send_string(str,-1); } ;
			inline void UnsafePrint (const_symbol_type_t c ) { send_char(c); } ;



			inline void Clear () {  Print("\033[2J\033[H"); } ;
			inline void CursorUp () {  Print("\033[1A"); } ;
			inline void CursorLeft () {  Print("\033[200D"); } ;
			inline void SetColorRed() { Print("\033[31m") ; } ;
			inline void SetColorGreen() { Print("\033[32m") ; } ;


			inline void UnsafeSetColorRed() { UnsafePrint("\033[31m") ; } ;
			inline void UnsafeSetColorGreen() { UnsafePrint("\033[32m") ; } ;

			inline void Echo(bool state) { echo = state ; }
			inline bool Echo() { return echo ; }

			//--------------------------------------------------------------------------------

};

#endif /*__READLINE_H__*/
