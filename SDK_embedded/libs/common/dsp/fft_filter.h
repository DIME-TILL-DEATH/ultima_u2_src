/*
 * fft_filter.h
 *
 *  Created on: 23 дек. 2016 г.
 *      Author: klen
 */

#ifndef __FFT_FILTER_H__
#define __FFT_FILTER_H__


/*
* фильтрация с помощью БПФ
* алгоритм взят из
* Романюк Ю.А. Основы цифровой обработки сигналов.
* 5.4 Секционированная свёртка, Метод перекрытия с накоплением.
*/

class FFTfilter1
{

 //  импульсная характеристика после преобразования в частотную область

 private:
      float* m_response;

      // буфер для накопления нужного числа входных данных
      int16_t* m_buffer;
      int16_t  m_buffer_length;


      // указатель для сохранения входных данных в буфер
      int m_s;

      // размер буфера, степень числа 2
      int m_power;

      // длина импульсной характеристики фильтра - 1
      int m_imp_length1;

 public:

      FFTfilter1() {}

//  инициализация параметров
//  @param imp - импульсная характеристика фильтра


 void init(float* imp, int imp_length)
 {

         // преобразуем импульсную характеристику в частотную область
         // подбираем размер буфера для свёртки.
         // (L - 1) отсчётов будут отбрасываться,
         // длину буфера выбираем минимум 32768.

         int i;

         m_power = 0;

         for( i = 1; i < imp_length; m_power++ ) i = i << 1;

         // если степень меньше 15, возрастают искажения
         if( ++m_power < 15 ) m_power = 15;

         // создаём буфер для преобразования и дополняем его нулями
         m_response = new float[1 << m_power];// уже обнулён

         for( i = 0; i < imp_length; i++ ) m_response[i] = imp[i];
         //for( ; i < (1 << m_power); i++ ) m_response[i] = 0.0;

         // переводим в частотную область
         FFT.realFastFourierTransform( m_response, m_power, false );

         // вспомогательный буфер для хранения входных данных
         m_buffer = new int16_t[1 << m_power];
         m_buffer_length = 1 << m_power ;

         m_imp_length1 = imp_length - 1;

         m_s = m_imp_length1;// компенсируем начальное смещение влево

         // обнуляем кусок буфера, в java он уже обнулён
         //for( i = 0; i < m_s; i++ ) m_buffer[i] = 0;

         delete m_response ;

 }

/**
* фильтрация
* выходной сигнал имеет задержку на L/2 сэмплов
* @param sample - отсчёт звука
* @return результат фильтрации, если не null
*/

int16_t* proc(int16_t sample) {

         m_buffer[m_s++] = sample;

         if( m_s < m_buffer_length )
                 return 0;

         // переносим данные во временный буфер
         float* buf = new float[m_buffer_length];

         for( int i = 0; i < m_buffer_length; i++ )
                 buf[i] = (float)m_buffer[i];

         // сохраняем последние (L - 1) значений для следующего преобразования

         for( int i = m_buffer_length - m_imp_length1, m = 0; i < m_buffer_length; i++ )
                 m_buffer[m++] = m_buffer[i];

         m_s = m_imp_length1;

         // выполняем БПФ
         FFT.realFastFourierTransform( buf, m_power, false );

         // перемножаем частотные характеристики
         /* постоянная составляющая
         buf[0] = buf[0] * m_response[0];
         buf[1] = buf[1] * m_response[1];
         for( int m = 2; m < buf.length; m += 2 )
         */

         for( int m = 0; m < m_buffer_length; m += 2 ) {

                 // от способа перемножения зависит,

                 // какая часть данных будет отбрасываться

                 float a = buf[m];
                 float b = buf[m + 1];

                 // вариант для отбрасывания последних (L-1) отсчётов
                 buf[m]     = a * m_response[m] + b * m_response[m + 1];
                 buf[m + 1] = b * m_response[m] - a * m_response[m + 1];

                 /* вариант для отбрасывания первых (L-1) отсчётов
                 buf[m]     = a * m_response[m] - b * m_response[m + 1];
                 buf[m + 1] = b * m_response[m] + a * m_response[m + 1];
                 */

         }

         // преобразуем обратно во временную область
         FFT.realFastFourierTransform( buf, m_power, true );
         // переписываем часть данных в выходной буфер
         int16_t* out = new int16_t[m_buffer_length - m_imp_length1];

         // отбрасываем последние (L-1) отсчётов

         for( int i = 0; i < m_buffer_length; i++ )
           {
                 if( buf[i] > 32767 )
                     out[i] = 32767;
                 else
                   {
                      if( buf[i] < -32768 )
                        out[i] = -32768;
                      else
                        out[i] = (int16_t)buf[i];
                   }
           }

         /* или отбрасываем первые (L-1) отсчётов
         for( int i = 0; i < out.length; i++ ) {
                 if( buf[i + m_imp_length1] > 32767 ) out[i] = 32767;
                 else if( buf[i + m_imp_length1] < -32768 ) out[i] = -32768;
                 else out[i] = (short)buf[i + m_imp_length1];
         }
         */

         delete buf ;

         return out;
 }
};


#endif /* __FFT_FILTER_H__ */
