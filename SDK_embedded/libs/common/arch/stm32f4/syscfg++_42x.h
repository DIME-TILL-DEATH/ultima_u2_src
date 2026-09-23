/*
 * syscfg++.h
 *
 *  Created on: 30 окт. 2017 г.
 *      Author: klen
 */

#ifndef __SYSCFG_42X_H__
#define __SYSCFG_42X_H__

#include "types++.h"

namespace stm32f4
{

struct syscfg_t
{
  struct memory_remap_t : public read_write_32_t
	{
	    struct mem_mode_t { enum enum_t{ offset=0, mask=0b111, main_flash=0, system_flash, fmc_sram_bank1, embedded_sram,  fmc_sdram_bank1 };};
	    struct flash_bank_mode_t { enum enum_t{ offset=8, mask=1, flash_bank_1=0, flash_bank_2 };};
	    struct fmc_memory_mapping_swap_t { enum enum_t{ offset=10, mask=0b11, disable=0, enable };};
	};

  inline  void mem_mode(const memory_remap_t::mem_mode_t::enum_t val){  memory_remap.rmw(val) ;}
  inline  void mem_mode_main_flash() {  memory_remap.rmw( memory_remap_t::mem_mode_t::main_flash) ;}
  inline  void mem_mode_system_flash() {  memory_remap.rmw( memory_remap_t::mem_mode_t::system_flash) ;}
  inline  void mem_mode_fmc_sram_bank1() {  memory_remap.rmw( memory_remap_t::mem_mode_t::fmc_sram_bank1) ;}
  inline  void mem_mode_embedded_sram() {  memory_remap.rmw( memory_remap_t::mem_mode_t::embedded_sram) ;}
  inline  void mem_mode_fmc_sdram_bank1() {  memory_remap.rmw( memory_remap_t::mem_mode_t::fmc_sdram_bank1) ;}
  inline  auto mem_mode()const {  return memory_remap.rd<memory_remap_t::mem_mode_t>();}

  inline  void flash_bank_mode(const memory_remap_t::flash_bank_mode_t::enum_t val){  memory_remap.rmw(val) ;}
  inline  void flash_bank_mode_flash_bank_1() {  memory_remap.rmw( memory_remap_t::flash_bank_mode_t::flash_bank_1) ;}
  inline  void flash_bank_mode_flash_bank_2() {  memory_remap.rmw( memory_remap_t::flash_bank_mode_t::flash_bank_2) ;}
  inline  auto flash_bank_mode()const {  return memory_remap.rd<memory_remap_t::flash_bank_mode_t>();}

  inline  void fmc_memory_mapping_swap(const memory_remap_t::fmc_memory_mapping_swap_t::enum_t val){  memory_remap.rmw(val) ;}
  inline  void fmc_memory_mapping_swap_disable() {  memory_remap.rmw( memory_remap_t::fmc_memory_mapping_swap_t::disable) ;}
  inline  void fmc_memory_mapping_swap_enable() {  memory_remap.rmw( memory_remap_t::fmc_memory_mapping_swap_t::enable) ;}
  inline  auto fmc_memory_mapping_swap()const {  return memory_remap.rd<memory_remap_t::fmc_memory_mapping_swap_t>();}



  struct peripheral_mode_configuration_t : public read_write_32_t
	{
           struct adc_dc2_t       { enum enum_t{ offset=16, mask=0b111, disable=0, all=0b111, adc1=0b001, adc2=0b010, adc3=0b100  };};
           struct ethernet_phy_t  { enum enum_t{ offset=23, mask=1, mii=0, rmii  };};
	};

  inline  void adc_dc2(const peripheral_mode_configuration_t::adc_dc2_t::enum_t val){  peripheral_mode_configuration.rmw(val) ;}
  inline  void adc_dc2_disable() {  peripheral_mode_configuration.rmw( peripheral_mode_configuration_t::adc_dc2_t::disable) ;}
  inline  void adc_dc2_all() {  peripheral_mode_configuration.rmw( peripheral_mode_configuration_t::adc_dc2_t::all) ;}
  inline  void adc_dc2_adc1() {  peripheral_mode_configuration.rmw( peripheral_mode_configuration_t::adc_dc2_t::adc1) ;}
  inline  void adc_dc2_adc2() {  peripheral_mode_configuration.rmw( peripheral_mode_configuration_t::adc_dc2_t::adc2) ;}
  inline  void adc_dc2_adc3() {  peripheral_mode_configuration.rmw( peripheral_mode_configuration_t::adc_dc2_t::adc3) ;}
  inline  auto adc_dc2()const {  return peripheral_mode_configuration.rd<peripheral_mode_configuration_t::adc_dc2_t>();}

  inline  void ethernet_phy(const peripheral_mode_configuration_t::ethernet_phy_t::enum_t val){  peripheral_mode_configuration.rmw(val) ;}
  inline  void ethernet_phy_mii() {  peripheral_mode_configuration.rmw( peripheral_mode_configuration_t::ethernet_phy_t::mii) ;}
  inline  void ethernet_phy_rmii() {  peripheral_mode_configuration.rmw( peripheral_mode_configuration_t::ethernet_phy_t::rmii) ;}
  inline  auto ethernet_phy()const {  return peripheral_mode_configuration.rd<peripheral_mode_configuration_t::ethernet_phy_t>();}

  enum pin_index_t { i0=0,     i1,       i2,       i3,       i4,       i5,       i6,       i7,       i8,       i9,       i10,        i11,        i12,        i13,        i14,        i15 } ;
  struct pin_port_t  { enum enum_t {mask=0b1111, pa=0, pb, pc, pd, pe, pf, pg, ph, pi, pj };} ;

  struct external_interrupt_configuration_t : public read_write_32_t
	{
	};

  inline  void exti0(const pin_port_t::enum_t val){  external_interrupt_configuration[0].rmw(val,0) ;}
  inline  void exti0_pa() {  external_interrupt_configuration[0].rmw( pin_port_t::pa , 0) ;}
  inline  void exti0_pb() {  external_interrupt_configuration[0].rmw( pin_port_t::pb , 0) ;}
  inline  void exti0_pc() {  external_interrupt_configuration[0].rmw( pin_port_t::pc , 0) ;}
  inline  void exti0_pd() {  external_interrupt_configuration[0].rmw( pin_port_t::pd , 0) ;}
  inline  void exti0_pe() {  external_interrupt_configuration[0].rmw( pin_port_t::pe , 0) ;}
  inline  void exti0_pf() {  external_interrupt_configuration[0].rmw( pin_port_t::pf , 0) ;}
  inline  void exti0_pg() {  external_interrupt_configuration[0].rmw( pin_port_t::pg , 0) ;}
  inline  void exti0_ph() {  external_interrupt_configuration[0].rmw( pin_port_t::ph , 0) ;}
  inline  void exti0_pi() {  external_interrupt_configuration[0].rmw( pin_port_t::pi , 0) ;}
  inline  void exti0_pj() {  external_interrupt_configuration[0].rmw( pin_port_t::pj , 0) ;}
  inline  auto exti0()const {  return external_interrupt_configuration[0].rd<pin_port_t>(0);}

  inline  void exti1(const pin_port_t::enum_t val){  external_interrupt_configuration[0].rmw(val,4) ;}
  inline  void exti1_pa() {  external_interrupt_configuration[0].rmw( pin_port_t::pa , 4) ;}
  inline  void exti1_pb() {  external_interrupt_configuration[0].rmw( pin_port_t::pb , 4) ;}
  inline  void exti1_pc() {  external_interrupt_configuration[0].rmw( pin_port_t::pc , 4) ;}
  inline  void exti1_pd() {  external_interrupt_configuration[0].rmw( pin_port_t::pd , 4) ;}
  inline  void exti1_pe() {  external_interrupt_configuration[0].rmw( pin_port_t::pe , 4) ;}
  inline  void exti1_pf() {  external_interrupt_configuration[0].rmw( pin_port_t::pf , 4) ;}
  inline  void exti1_pg() {  external_interrupt_configuration[0].rmw( pin_port_t::pg , 4) ;}
  inline  void exti1_ph() {  external_interrupt_configuration[0].rmw( pin_port_t::ph , 4) ;}
  inline  void exti1_pi() {  external_interrupt_configuration[0].rmw( pin_port_t::pi , 4) ;}
  inline  void exti1_pj() {  external_interrupt_configuration[0].rmw( pin_port_t::pj , 4) ;}
  inline  auto exti1()const {  return external_interrupt_configuration[0].rd<pin_port_t>(4);}

  inline  void exti2(const pin_port_t::enum_t val){  external_interrupt_configuration[0].rmw(val,8) ;}
  inline  void exti2_pa() {  external_interrupt_configuration[0].rmw( pin_port_t::pa , 8) ;}
  inline  void exti2_pb() {  external_interrupt_configuration[0].rmw( pin_port_t::pb , 8) ;}
  inline  void exti2_pc() {  external_interrupt_configuration[0].rmw( pin_port_t::pc , 8) ;}
  inline  void exti2_pd() {  external_interrupt_configuration[0].rmw( pin_port_t::pd , 8) ;}
  inline  void exti2_pe() {  external_interrupt_configuration[0].rmw( pin_port_t::pe , 8) ;}
  inline  void exti2_pf() {  external_interrupt_configuration[0].rmw( pin_port_t::pf , 8) ;}
  inline  void exti2_pg() {  external_interrupt_configuration[0].rmw( pin_port_t::pg , 8) ;}
  inline  void exti2_ph() {  external_interrupt_configuration[0].rmw( pin_port_t::ph , 8) ;}
  inline  void exti2_pi() {  external_interrupt_configuration[0].rmw( pin_port_t::pi , 8) ;}
  inline  void exti2_pj() {  external_interrupt_configuration[0].rmw( pin_port_t::pj , 8) ;}
  inline  auto exti2()const {  return external_interrupt_configuration[0].rd<pin_port_t>(8);}

  inline  void exti3(const pin_port_t::enum_t val){  external_interrupt_configuration[0].rmw(val,12) ;}
  inline  void exti3_pa() {  external_interrupt_configuration[0].rmw( pin_port_t::pa , 12) ;}
  inline  void exti3_pb() {  external_interrupt_configuration[0].rmw( pin_port_t::pb , 12) ;}
  inline  void exti3_pc() {  external_interrupt_configuration[0].rmw( pin_port_t::pc , 12) ;}
  inline  void exti3_pd() {  external_interrupt_configuration[0].rmw( pin_port_t::pd , 12) ;}
  inline  void exti3_pe() {  external_interrupt_configuration[0].rmw( pin_port_t::pe , 12) ;}
  inline  void exti3_pf() {  external_interrupt_configuration[0].rmw( pin_port_t::pf , 12) ;}
  inline  void exti3_pg() {  external_interrupt_configuration[0].rmw( pin_port_t::pg , 12) ;}
  inline  void exti3_ph() {  external_interrupt_configuration[0].rmw( pin_port_t::ph , 12) ;}
  inline  void exti3_pi() {  external_interrupt_configuration[0].rmw( pin_port_t::pi , 12) ;}
  inline  void exti3_pj() {  external_interrupt_configuration[0].rmw( pin_port_t::pj , 12) ;}
  inline  auto exti3()const {  return external_interrupt_configuration[0].rd<pin_port_t>(12);}

  inline  void exti4(const pin_port_t::enum_t val){  external_interrupt_configuration[1].rmw(val,0) ;}
  inline  void exti4_pa() {  external_interrupt_configuration[1].rmw( pin_port_t::pa , 0) ;}
  inline  void exti4_pb() {  external_interrupt_configuration[1].rmw( pin_port_t::pb , 0) ;}
  inline  void exti4_pc() {  external_interrupt_configuration[1].rmw( pin_port_t::pc , 0) ;}
  inline  void exti4_pd() {  external_interrupt_configuration[1].rmw( pin_port_t::pd , 0) ;}
  inline  void exti4_pe() {  external_interrupt_configuration[1].rmw( pin_port_t::pe , 0) ;}
  inline  void exti4_pf() {  external_interrupt_configuration[1].rmw( pin_port_t::pf , 0) ;}
  inline  void exti4_pg() {  external_interrupt_configuration[1].rmw( pin_port_t::pg , 0) ;}
  inline  void exti4_ph() {  external_interrupt_configuration[1].rmw( pin_port_t::ph , 0) ;}
  inline  void exti4_pi() {  external_interrupt_configuration[1].rmw( pin_port_t::pi , 0) ;}
  inline  void exti4_pj() {  external_interrupt_configuration[1].rmw( pin_port_t::pj , 0) ;}
  inline  auto exti4()const {  return external_interrupt_configuration[1].rd<pin_port_t>(0);}

  inline  void exti5(const pin_port_t::enum_t val){  external_interrupt_configuration[1].rmw(val,4) ;}
  inline  void exti5_pa() {  external_interrupt_configuration[1].rmw( pin_port_t::pa , 4) ;}
  inline  void exti5_pb() {  external_interrupt_configuration[1].rmw( pin_port_t::pb , 4) ;}
  inline  void exti5_pc() {  external_interrupt_configuration[1].rmw( pin_port_t::pc , 4) ;}
  inline  void exti5_pd() {  external_interrupt_configuration[1].rmw( pin_port_t::pd , 4) ;}
  inline  void exti5_pe() {  external_interrupt_configuration[1].rmw( pin_port_t::pe , 4) ;}
  inline  void exti5_pf() {  external_interrupt_configuration[1].rmw( pin_port_t::pf , 4) ;}
  inline  void exti5_pg() {  external_interrupt_configuration[1].rmw( pin_port_t::pg , 4) ;}
  inline  void exti5_ph() {  external_interrupt_configuration[1].rmw( pin_port_t::ph , 4) ;}
  inline  void exti5_pi() {  external_interrupt_configuration[1].rmw( pin_port_t::pi , 4) ;}
  inline  void exti5_pj() {  external_interrupt_configuration[1].rmw( pin_port_t::pj , 4) ;}
  inline  auto exti5()const {  return external_interrupt_configuration[1].rd<pin_port_t>(4);}

  inline  void exti6(const pin_port_t::enum_t val){  external_interrupt_configuration[1].rmw(val,8) ;}
  inline  void exti6_pa() {  external_interrupt_configuration[1].rmw( pin_port_t::pa , 8) ;}
  inline  void exti6_pb() {  external_interrupt_configuration[1].rmw( pin_port_t::pb , 8) ;}
  inline  void exti6_pc() {  external_interrupt_configuration[1].rmw( pin_port_t::pc , 8) ;}
  inline  void exti6_pd() {  external_interrupt_configuration[1].rmw( pin_port_t::pd , 8) ;}
  inline  void exti6_pe() {  external_interrupt_configuration[1].rmw( pin_port_t::pe , 8) ;}
  inline  void exti6_pf() {  external_interrupt_configuration[1].rmw( pin_port_t::pf , 8) ;}
  inline  void exti6_pg() {  external_interrupt_configuration[1].rmw( pin_port_t::pg , 8) ;}
  inline  void exti6_ph() {  external_interrupt_configuration[1].rmw( pin_port_t::ph , 8) ;}
  inline  void exti6_pi() {  external_interrupt_configuration[1].rmw( pin_port_t::pi , 8) ;}
  inline  void exti6_pj() {  external_interrupt_configuration[1].rmw( pin_port_t::pj , 8) ;}
  inline  auto exti6()const {  return external_interrupt_configuration[1].rd<pin_port_t>(8);}

  inline  void exti7(const pin_port_t::enum_t val){  external_interrupt_configuration[1].rmw(val,12) ;}
  inline  void exti7_pa() {  external_interrupt_configuration[1].rmw( pin_port_t::pa , 12) ;}
  inline  void exti7_pb() {  external_interrupt_configuration[1].rmw( pin_port_t::pb , 12) ;}
  inline  void exti7_pc() {  external_interrupt_configuration[1].rmw( pin_port_t::pc , 12) ;}
  inline  void exti7_pd() {  external_interrupt_configuration[1].rmw( pin_port_t::pd , 12) ;}
  inline  void exti7_pe() {  external_interrupt_configuration[1].rmw( pin_port_t::pe , 12) ;}
  inline  void exti7_pf() {  external_interrupt_configuration[1].rmw( pin_port_t::pf , 12) ;}
  inline  void exti7_pg() {  external_interrupt_configuration[1].rmw( pin_port_t::pg , 12) ;}
  inline  void exti7_ph() {  external_interrupt_configuration[1].rmw( pin_port_t::ph , 12) ;}
  inline  void exti7_pi() {  external_interrupt_configuration[1].rmw( pin_port_t::pi , 12) ;}
  inline  void exti7_pj() {  external_interrupt_configuration[1].rmw( pin_port_t::pj , 12) ;}
  inline  auto exti7()const {  return external_interrupt_configuration[1].rd<pin_port_t>(12);}

  inline  void exti8(const pin_port_t::enum_t val){  external_interrupt_configuration[2].rmw(val,0) ;}
  inline  void exti8_pa() {  external_interrupt_configuration[2].rmw( pin_port_t::pa , 0) ;}
  inline  void exti8_pb() {  external_interrupt_configuration[2].rmw( pin_port_t::pb , 0) ;}
  inline  void exti8_pc() {  external_interrupt_configuration[2].rmw( pin_port_t::pc , 0) ;}
  inline  void exti8_pd() {  external_interrupt_configuration[2].rmw( pin_port_t::pd , 0) ;}
  inline  void exti8_pe() {  external_interrupt_configuration[2].rmw( pin_port_t::pe , 0) ;}
  inline  void exti8_pf() {  external_interrupt_configuration[2].rmw( pin_port_t::pf , 0) ;}
  inline  void exti8_pg() {  external_interrupt_configuration[2].rmw( pin_port_t::pg , 0) ;}
  inline  void exti8_ph() {  external_interrupt_configuration[2].rmw( pin_port_t::ph , 0) ;}
  inline  void exti8_pi() {  external_interrupt_configuration[2].rmw( pin_port_t::pi , 0) ;}
  inline  void exti8_pj() {  external_interrupt_configuration[2].rmw( pin_port_t::pj , 0) ;}
  inline  auto exti8()const {  return external_interrupt_configuration[2].rd<pin_port_t>(0);}

  inline  void exti9(const pin_port_t::enum_t val){  external_interrupt_configuration[2].rmw(val,4) ;}
  inline  void exti9_pa() {  external_interrupt_configuration[2].rmw( pin_port_t::pa , 4) ;}
  inline  void exti9_pb() {  external_interrupt_configuration[2].rmw( pin_port_t::pb , 4) ;}
  inline  void exti9_pc() {  external_interrupt_configuration[2].rmw( pin_port_t::pc , 4) ;}
  inline  void exti9_pd() {  external_interrupt_configuration[2].rmw( pin_port_t::pd , 4) ;}
  inline  void exti9_pe() {  external_interrupt_configuration[2].rmw( pin_port_t::pe , 4) ;}
  inline  void exti9_pf() {  external_interrupt_configuration[2].rmw( pin_port_t::pf , 4) ;}
  inline  void exti9_pg() {  external_interrupt_configuration[2].rmw( pin_port_t::pg , 4) ;}
  inline  void exti9_ph() {  external_interrupt_configuration[2].rmw( pin_port_t::ph , 4) ;}
  inline  void exti9_pi() {  external_interrupt_configuration[2].rmw( pin_port_t::pi , 4) ;}
  inline  void exti9_pj() {  external_interrupt_configuration[2].rmw( pin_port_t::pj , 4) ;}
  inline  auto exti9()const {  return external_interrupt_configuration[2].rd<pin_port_t>(4);}

  inline  void exti10(const pin_port_t::enum_t val){  external_interrupt_configuration[2].rmw(val,8) ;}
  inline  void exti10_pa() {  external_interrupt_configuration[2].rmw( pin_port_t::pa , 8) ;}
  inline  void exti10_pb() {  external_interrupt_configuration[2].rmw( pin_port_t::pb , 8) ;}
  inline  void exti10_pc() {  external_interrupt_configuration[2].rmw( pin_port_t::pc , 8) ;}
  inline  void exti10_pd() {  external_interrupt_configuration[2].rmw( pin_port_t::pd , 8) ;}
  inline  void exti10_pe() {  external_interrupt_configuration[2].rmw( pin_port_t::pe , 8) ;}
  inline  void exti10_pf() {  external_interrupt_configuration[2].rmw( pin_port_t::pf , 8) ;}
  inline  void exti10_pg() {  external_interrupt_configuration[2].rmw( pin_port_t::pg , 8) ;}
  inline  void exti10_ph() {  external_interrupt_configuration[2].rmw( pin_port_t::ph , 8) ;}
  inline  void exti10_pi() {  external_interrupt_configuration[2].rmw( pin_port_t::pi , 8) ;}
  inline  void exti10_pj() {  external_interrupt_configuration[2].rmw( pin_port_t::pj , 8) ;}
  inline  auto exti10()const {  return external_interrupt_configuration[2].rd<pin_port_t>(8);}

  inline  void exti11(const pin_port_t::enum_t val){  external_interrupt_configuration[2].rmw(val,12) ;}
  inline  void exti11_pa() {  external_interrupt_configuration[2].rmw( pin_port_t::pa , 12) ;}
  inline  void exti11_pb() {  external_interrupt_configuration[2].rmw( pin_port_t::pb , 12) ;}
  inline  void exti11_pc() {  external_interrupt_configuration[2].rmw( pin_port_t::pc , 12) ;}
  inline  void exti11_pd() {  external_interrupt_configuration[2].rmw( pin_port_t::pd , 12) ;}
  inline  void exti11_pe() {  external_interrupt_configuration[2].rmw( pin_port_t::pe , 12) ;}
  inline  void exti11_pf() {  external_interrupt_configuration[2].rmw( pin_port_t::pf , 12) ;}
  inline  void exti11_pg() {  external_interrupt_configuration[2].rmw( pin_port_t::pg , 12) ;}
  inline  void exti11_ph() {  external_interrupt_configuration[2].rmw( pin_port_t::ph , 12) ;}
  inline  void exti11_pi() {  external_interrupt_configuration[2].rmw( pin_port_t::pi , 12) ;}
  inline  void exti11_pj() {  external_interrupt_configuration[2].rmw( pin_port_t::pj , 12) ;}
  inline  auto exti11()const {  return external_interrupt_configuration[2].rd<pin_port_t>(12);}

  inline  void exti12(const pin_port_t::enum_t val){  external_interrupt_configuration[3].rmw(val,0) ;}
  inline  void exti12_pa() {  external_interrupt_configuration[3].rmw( pin_port_t::pa , 0) ;}
  inline  void exti12_pb() {  external_interrupt_configuration[3].rmw( pin_port_t::pb , 0) ;}
  inline  void exti12_pc() {  external_interrupt_configuration[3].rmw( pin_port_t::pc , 0) ;}
  inline  void exti12_pd() {  external_interrupt_configuration[3].rmw( pin_port_t::pd , 0) ;}
  inline  void exti12_pe() {  external_interrupt_configuration[3].rmw( pin_port_t::pe , 0) ;}
  inline  void exti12_pf() {  external_interrupt_configuration[3].rmw( pin_port_t::pf , 0) ;}
  inline  void exti12_pg() {  external_interrupt_configuration[3].rmw( pin_port_t::pg , 0) ;}
  inline  void exti12_ph() {  external_interrupt_configuration[3].rmw( pin_port_t::ph , 0) ;}
  inline  void exti12_pi() {  external_interrupt_configuration[3].rmw( pin_port_t::pi , 0) ;}
  inline  void exti12_pj() {  external_interrupt_configuration[3].rmw( pin_port_t::pj , 0) ;}
  inline  auto exti12()const {  return external_interrupt_configuration[3].rd<pin_port_t>(0);}

  inline  void exti13(const pin_port_t::enum_t val){  external_interrupt_configuration[3].rmw(val,4) ;}
  inline  void exti13_pa() {  external_interrupt_configuration[3].rmw( pin_port_t::pa , 4) ;}
  inline  void exti13_pb() {  external_interrupt_configuration[3].rmw( pin_port_t::pb , 4) ;}
  inline  void exti13_pc() {  external_interrupt_configuration[3].rmw( pin_port_t::pc , 4) ;}
  inline  void exti13_pd() {  external_interrupt_configuration[3].rmw( pin_port_t::pd , 4) ;}
  inline  void exti13_pe() {  external_interrupt_configuration[3].rmw( pin_port_t::pe , 4) ;}
  inline  void exti13_pf() {  external_interrupt_configuration[3].rmw( pin_port_t::pf , 4) ;}
  inline  void exti13_pg() {  external_interrupt_configuration[3].rmw( pin_port_t::pg , 4) ;}
  inline  void exti13_ph() {  external_interrupt_configuration[3].rmw( pin_port_t::ph , 4) ;}
  inline  void exti13_pi() {  external_interrupt_configuration[3].rmw( pin_port_t::pi , 4) ;}
  inline  void exti13_pj() {  external_interrupt_configuration[3].rmw( pin_port_t::pj , 4) ;}
  inline  auto exti13()const {  return external_interrupt_configuration[3].rd<pin_port_t>(4);}

  inline  void exti14(const pin_port_t::enum_t val){  external_interrupt_configuration[3].rmw(val,8) ;}
  inline  void exti14_pa() {  external_interrupt_configuration[3].rmw( pin_port_t::pa , 8) ;}
  inline  void exti14_pb() {  external_interrupt_configuration[3].rmw( pin_port_t::pb , 8) ;}
  inline  void exti14_pc() {  external_interrupt_configuration[3].rmw( pin_port_t::pc , 8) ;}
  inline  void exti14_pd() {  external_interrupt_configuration[3].rmw( pin_port_t::pd , 8) ;}
  inline  void exti14_pe() {  external_interrupt_configuration[3].rmw( pin_port_t::pe , 8) ;}
  inline  void exti14_pf() {  external_interrupt_configuration[3].rmw( pin_port_t::pf , 8) ;}
  inline  void exti14_pg() {  external_interrupt_configuration[3].rmw( pin_port_t::pg , 8) ;}
  inline  void exti14_ph() {  external_interrupt_configuration[3].rmw( pin_port_t::ph , 8) ;}
  inline  void exti14_pi() {  external_interrupt_configuration[3].rmw( pin_port_t::pi , 8) ;}
  inline  void exti14_pj() {  external_interrupt_configuration[3].rmw( pin_port_t::pj , 8) ;}
  inline  auto exti14()const {  return external_interrupt_configuration[3].rd<pin_port_t>(8);}

  inline  void exti15(const pin_port_t::enum_t val){  external_interrupt_configuration[3].rmw(val,12) ;}
  inline  void exti15_pa() {  external_interrupt_configuration[3].rmw( pin_port_t::pa , 12) ;}
  inline  void exti15_pb() {  external_interrupt_configuration[3].rmw( pin_port_t::pb , 12) ;}
  inline  void exti15_pc() {  external_interrupt_configuration[3].rmw( pin_port_t::pc , 12) ;}
  inline  void exti15_pd() {  external_interrupt_configuration[3].rmw( pin_port_t::pd , 12) ;}
  inline  void exti15_pe() {  external_interrupt_configuration[3].rmw( pin_port_t::pe , 12) ;}
  inline  void exti15_pf() {  external_interrupt_configuration[3].rmw( pin_port_t::pf , 12) ;}
  inline  void exti15_pg() {  external_interrupt_configuration[3].rmw( pin_port_t::pg , 12) ;}
  inline  void exti15_ph() {  external_interrupt_configuration[3].rmw( pin_port_t::ph , 12) ;}
  inline  void exti15_pi() {  external_interrupt_configuration[3].rmw( pin_port_t::pi , 12) ;}
  inline  void exti15_pj() {  external_interrupt_configuration[3].rmw( pin_port_t::pj , 12) ;}
  inline  auto exti15()const {  return external_interrupt_configuration[3].rd<pin_port_t>(12);}

  inline  void exti(const pin_index_t pin_index, const pin_port_t::enum_t pin_port)
     {
       external_interrupt_configuration[ pin_index >> 2].rmw( pin_port , (pin_index % 4)<<2 ) ;
     }
  inline  auto exti(const pin_index_t pin_index)const
     {
    external_interrupt_configuration[ pin_index >> 2].rd<pin_port_t>(  (pin_index % 4)<<2 );
     }

  struct compensation_cell_control_t : public read_write_32_t
	{
           struct state_t { enum enum_t{ offset=0,  mask=1, disable=0, enable };};
           struct ready_t { enum enum_t{ offset=8,  mask=1, not_ready=0, ready };};
	};

  inline  void compensation_cell(const compensation_cell_control_t::state_t::enum_t val){  compensation_cell_control.rmw(val) ;}
  inline  void compensation_cell_disable() {  compensation_cell_control.rmw( compensation_cell_control_t::state_t::disable) ;}
  inline  void compensation_cell_enable() {  compensation_cell_control.rmw( compensation_cell_control_t::state_t::enable) ;}
  inline  auto compensation_cell()const {  return compensation_cell_control.rd<compensation_cell_control_t::state_t>();}

  inline  auto compensation_cell_ready()const {  return compensation_cell_control.rd<compensation_cell_control_t::ready_t>();}
  inline  void compensation_cell_wait_ready() { while ( compensation_cell_ready() == compensation_cell_control_t::ready_t::not_ready)  {} ; }


  memory_remap_t                       memory_remap ;                       // MEMRMP;       /*!< SYSCFG memory remap register,                      Address offset: 0x00      */
  peripheral_mode_configuration_t      peripheral_mode_configuration;       // PMC;          /*!< SYSCFG peripheral mode configuration register,     Address offset: 0x04      */
  external_interrupt_configuration_t external_interrupt_configuration[4];   // EXTICR[4];    /*!< SYSCFG external interrupt configuration registers, Address offset: 0x08-0x14 */
  uint32_t : 32 ;                                                         // RESERVED[2];  /*!< Reserved, 0x18-0x1C                                                          */
  uint32_t : 32 ;
  compensation_cell_control_t          compensation_cell_control;           // CMPCR;        /*!< SYSCFG Compensation cell control register,         Address offset: 0x20      */

  inline void clock_enable() {  rcc.syscfg_enable() ; }
  inline void clock_disable() {  rcc.syscfg_disable() ; }
  inline void reset() { rcc.syscfg_reset() ; }
};

static syscfg_t& syscfg = *((syscfg_t *) syscfg_addr);

}  // stm32f4

using namespace stm32f4 ;

#endif /* __SYSCFG_42X_H__ */
