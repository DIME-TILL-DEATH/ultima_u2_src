#include "stdint.h"
#include "supc++.h"
#include "stm32++.h"

//-------------------------------------------------------------------------

// c++ error handler , that is invoked when in function calls exceptions caused
extern "C" void __attribute__((weak,noreturn,used))  abort()
{
  while (1)
        nop() ;
}

//  normal main() return handler stab
extern "C" void __attribute__((weak,noreturn)) __main_exit_handler(int retval)
{
  (void)  retval ;
   while (1)
     {
       nop();
       // wfi();  // on shoot devices
     } ;
}
// _init stub
extern "C" void __attribute__ ((weak)) _init(void)
{

}
// _fini stub
extern "C" void __attribute__ ((weak)) _fini(void)
{

}

#include "irq++.h"


// ----------- интерфейс системных вызовов ------------------

typedef void (*sycall_proc)(uint32_t*) ;

extern "C" __attribute__((weak)) void default_svc_handler(uint32_t* svc_args)
   {
     *svc_args = -1;

     // v1
     //volatile register uint8_t syscall_num asm ("r1");

     // v2
     uint8_t syscall_num = 0;
     asm volatile ( "str r1, %[syscall_num]" :: [syscall_num]"m"(syscall_num) : "r1", "memory"  );

     std::__throw_unhandled_sycall(syscall_num);
   }

#if defined __USE_FREERTOS__

  // объявлене SVC обработчика FreeRTOS (используется при запуске )
  extern "C" void vPortSVCHandler(void);

#else

  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_0_handler(uint32_t* svc_args);

#endif

  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_1_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_2_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_3_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_4_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_5_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_6_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_7_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_8_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_9_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_10_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_11_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_12_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_13_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_14_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_15_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_16_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_17_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_18_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_19_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_20_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_21_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_22_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_23_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_24_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_25_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_26_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_27_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_28_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_29_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_30_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_31_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_32_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_33_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_34_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_35_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_36_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_37_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_38_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_39_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_40_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_41_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_42_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_43_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_44_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_45_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_46_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_47_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_48_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_49_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_50_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_51_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_52_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_53_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_54_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_55_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_56_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_57_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_58_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_59_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_60_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_61_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_62_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_63_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_64_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_65_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_66_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_67_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_68_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_69_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_70_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_71_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_72_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_73_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_74_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_75_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_76_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_77_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_78_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_79_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_80_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_81_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_82_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_83_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_84_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_85_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_86_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_87_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_88_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_89_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_90_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_91_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_92_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_93_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_94_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_95_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_96_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_97_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_98_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_99_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_100_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_101_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_102_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_103_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_104_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_105_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_106_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_107_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_108_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_109_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_110_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_111_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_112_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_113_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_114_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_115_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_116_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_117_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_118_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_119_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_120_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_121_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_122_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_123_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_124_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_125_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_126_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_127_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_128_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_129_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_130_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_131_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_132_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_133_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_134_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_135_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_136_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_137_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_138_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_139_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_140_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_141_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_142_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_143_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_144_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_145_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_146_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_147_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_148_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_149_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_150_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_151_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_152_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_153_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_154_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_155_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_156_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_157_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_158_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_159_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_160_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_161_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_162_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_163_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_164_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_165_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_166_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_167_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_168_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_169_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_170_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_171_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_172_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_173_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_174_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_175_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_176_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_177_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_178_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_179_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_180_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_181_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_182_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_183_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_184_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_185_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_186_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_187_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_188_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_189_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_190_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_191_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_192_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_193_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_194_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_195_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_196_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_197_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_198_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_199_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_200_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_201_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_202_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_203_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_204_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_205_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_206_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_207_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_208_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_209_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_210_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_211_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_212_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_213_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_214_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_215_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_216_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_217_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_218_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_219_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_220_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_221_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_222_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_223_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_224_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_225_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_226_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_227_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_228_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_229_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_230_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_231_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_232_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_233_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_234_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_235_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_236_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_237_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_238_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_239_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_240_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_241_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_242_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_243_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_244_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_245_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_246_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_247_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_248_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_249_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_250_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_251_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_252_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_253_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_254_handler(uint32_t* svc_args);
  extern "C" __attribute__((weak,noinline,alias("default_svc_handler"))) void svc_255_handler(uint32_t* svc_args);

const __attribute__((used)) sycall_proc svc_handler_table[] =
      {
         #if defined __USE_FREERTOS__
	     (sycall_proc)vPortSVCHandler,
         #else
	     svc_0_handler,
         #endif
	                       svc_1_handler,  svc_2_handler,   svc_3_handler,   svc_4_handler,   svc_5_handler,   svc_6_handler,   svc_7_handler,   svc_8_handler,   svc_9_handler,   svc_10_handler,  svc_11_handler,  svc_12_handler,  svc_13_handler,  svc_14_handler,  svc_15_handler,
	     svc_16_handler,  svc_17_handler,  svc_18_handler,  svc_19_handler,  svc_20_handler,  svc_21_handler,  svc_22_handler,  svc_23_handler,  svc_24_handler,  svc_25_handler,  svc_26_handler,  svc_27_handler,  svc_28_handler,  svc_29_handler,  svc_30_handler,  svc_31_handler,
	     svc_32_handler,  svc_33_handler,  svc_34_handler,  svc_35_handler,  svc_36_handler,  svc_37_handler,  svc_38_handler,  svc_39_handler,  svc_40_handler,  svc_41_handler,  svc_42_handler,  svc_43_handler,  svc_44_handler,  svc_45_handler,  svc_46_handler,  svc_47_handler,
	     svc_48_handler,  svc_49_handler,  svc_50_handler,  svc_51_handler,  svc_52_handler,  svc_53_handler,  svc_54_handler,  svc_55_handler,  svc_56_handler,  svc_57_handler,  svc_58_handler,  svc_59_handler,  svc_60_handler,  svc_61_handler,  svc_62_handler,  svc_63_handler,
	     svc_64_handler,  svc_65_handler,  svc_66_handler,  svc_67_handler,  svc_68_handler,  svc_69_handler,  svc_70_handler,  svc_71_handler,  svc_72_handler,  svc_73_handler,  svc_74_handler,  svc_75_handler,  svc_76_handler,  svc_77_handler,  svc_78_handler,  svc_79_handler,
	     svc_80_handler,  svc_81_handler,  svc_82_handler,  svc_83_handler,  svc_84_handler,  svc_85_handler,  svc_86_handler,  svc_87_handler,  svc_88_handler,  svc_89_handler,  svc_90_handler,  svc_91_handler,  svc_92_handler,  svc_93_handler,  svc_94_handler,  svc_95_handler,
	     svc_96_handler,  svc_97_handler,  svc_98_handler,  svc_99_handler,  svc_100_handler, svc_101_handler, svc_102_handler, svc_103_handler, svc_104_handler, svc_105_handler, svc_106_handler, svc_107_handler, svc_108_handler, svc_109_handler, svc_110_handler, svc_111_handler,
	     svc_112_handler, svc_113_handler, svc_114_handler, svc_115_handler, svc_116_handler, svc_117_handler, svc_118_handler, svc_119_handler, svc_120_handler, svc_121_handler, svc_122_handler, svc_123_handler, svc_124_handler, svc_125_handler, svc_126_handler, svc_127_handler,
	     svc_128_handler, svc_129_handler, svc_130_handler, svc_131_handler, svc_132_handler, svc_133_handler, svc_134_handler, svc_135_handler, svc_136_handler, svc_137_handler, svc_138_handler, svc_139_handler, svc_140_handler, svc_141_handler, svc_142_handler, svc_143_handler,
	     svc_144_handler, svc_145_handler, svc_146_handler, svc_147_handler, svc_148_handler, svc_149_handler, svc_150_handler, svc_151_handler, svc_152_handler, svc_153_handler, svc_154_handler, svc_155_handler, svc_156_handler, svc_157_handler, svc_158_handler, svc_159_handler,
	     svc_160_handler, svc_161_handler, svc_162_handler, svc_163_handler, svc_164_handler, svc_165_handler, svc_166_handler, svc_167_handler, svc_168_handler, svc_169_handler, svc_170_handler, svc_171_handler, svc_172_handler, svc_173_handler, svc_174_handler, svc_175_handler,
	     svc_176_handler, svc_177_handler, svc_178_handler, svc_179_handler, svc_180_handler, svc_181_handler, svc_182_handler, svc_183_handler, svc_184_handler, svc_185_handler, svc_186_handler, svc_187_handler, svc_188_handler, svc_189_handler, svc_190_handler, svc_191_handler,
	     svc_192_handler, svc_193_handler, svc_194_handler, svc_195_handler, svc_196_handler, svc_197_handler, svc_198_handler, svc_199_handler, svc_200_handler, svc_201_handler, svc_202_handler, svc_203_handler, svc_204_handler, svc_205_handler, svc_206_handler, svc_207_handler,
	     svc_208_handler, svc_209_handler, svc_210_handler, svc_211_handler, svc_212_handler, svc_213_handler, svc_214_handler, svc_215_handler, svc_216_handler, svc_217_handler, svc_218_handler, svc_219_handler, svc_220_handler, svc_221_handler, svc_222_handler, svc_223_handler,
	     svc_224_handler, svc_225_handler, svc_226_handler, svc_227_handler, svc_228_handler, svc_229_handler, svc_230_handler, svc_231_handler, svc_232_handler, svc_233_handler, svc_234_handler, svc_235_handler, svc_236_handler, svc_237_handler, svc_238_handler, svc_239_handler,
	     svc_240_handler, svc_241_handler, svc_242_handler, svc_243_handler, svc_244_handler, svc_245_handler, svc_246_handler, svc_247_handler, svc_248_handler, svc_249_handler, svc_250_handler, svc_251_handler, svc_252_handler, svc_253_handler, svc_254_handler, svc_255_handler
      } ;

 IRQ_HANDLER(svc)
 {

   #if defined  (__ARM_ARCH_7M__) || defined(__ARM_ARCH_7EM__)
        asm volatile (
                       "tst     lr, #0x04              \n\
                   	ite 	eq                     \n\
 	                mrseq   r0, msp                \n\
                        mrsne   r0, psp                \n\
 			ldr     r1, [r0,#24]           \n\
 			ldrb    r1, [r1,#-2]           \n\
 			ldr     pc, [ %0, r1, lsl #2 ] \n"
                      :: "r"(svc_handler_table) :"r0","r1"
	             );
   #elif defined (__ARM_ARCH_6M__)
        asm volatile (
  	               "mov  r0, lr       \n\
                        movs r1, #4       \n\
  	                tst  r0, r1       \n\
                        beq  .1           \n\
  	                mrs   r0, psp     \n\
  	                b    .2           \n\
  	             .1:                   \n\
  	                mrs   r0, msp     \n\
                     .2:                   \n\
                        ldr  r1, [r0,#24] \n\
  	                sub  r1, #2       \n\
                        ldrb r1, [r1]     \n\
  	                lsl  r1, #2       \n\
  	                ldr  r1, [%0, r1] \n\
                        bx   r1           \n"
                      :: "r"(svc_handler_table) :"r0","r1"
		     );
                       
   #endif

        // состояние стека вызывающей svc функции:
        // - R0 = svc_args[0]
        // - R1 = svc_args[1]
        // - R2 = svc_args[2]
        // - R3 = svc_args[3]
        // - R12= svc_args[4]
        // - LR = svc_args[5]
        // - PC = svc_args[6]
        // - xPSR=svc_args[7]


 }
